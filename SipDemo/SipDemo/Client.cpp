#include"stdafx.h"
#include"Client.h"
#include<hpr/HPR_Utils.h>
#include<hlog/logdef.h>
#include"Markup.h"
#include"ClientMgr.h"

#define XML_VERSION "<?xml version=\"1.0\"?>\r\n"

Client::Client( /* arguments*/ )
: mRegStatus(offlineStatus)
, mRegTime(0)
, mCallTime(0)
{

}

Client::Client( const char* number )
: mNumber(number)
, mRegStatus(offlineStatus)
, mRegTime(0)
, mCallTime(0)
{

}

Client::~Client()
{

}

int Client::formRegMessage( char** msg, int* msgLen, HPR_ADDR_T& addr )
{
    osip_message_t* message = NULL;
    char from[128] = {0};
    char contact[128] = {0};
    char proxy[128] = {0};
    char clientIp[32];
    memset(clientIp, 0, 32);
    guessIpForVia(clientIp, 32);
    const char* serverIp = HPR_GetAddrString(&addr);
    HPR_INT32 serverPort = HPR_GetAddrPort(&addr);
    HPR_Snprintf(from, sizeof(from), "\"%s\"<sip:%s@%s:%d>", mNumber.c_str(), mNumber.c_str(), serverIp, serverPort);
    HPR_Snprintf(contact, sizeof(contact), "sip:%s@%s:%d", mNumber.c_str(), clientIp, 5068 );
    HPR_Snprintf(proxy, sizeof(proxy), "sip:%s@%s:%d", mNumber.c_str(), serverIp, serverPort );
    if (0 != formMessage(&message, "REGISTER", NULL, NULL, from, proxy) )
    {
        return -1;
    }

    osip_message_set_contact (message, contact);
    {
        char exp[10];               /* MUST never be ouside 1 and 3600 */

        sprintf (exp, "%i", 3600);
        osip_message_set_expires (message, exp);
    }

    osip_message_set_content_length (message, "0");
    if (message != NULL)
    {
        osip_message_to_str(message, msg, (size_t*)msgLen);
        osip_message_free(message);
    }
    return 0;
}

int Client::formMessage( osip_message_t** dest, const char* method, const char *to, const char *transport, const char *from, const char *proxy )
{
  /* Section 8.1:
     A valid request contains at a minimum "To, From, Call-iD, Cseq,
     Max-Forwards and Via
   */
  int i;
  osip_message_t *request;
  char locip[65];
  int doing_register;

  *dest = NULL;

  if (!method || !*method)
    return -2;

  /*guess the local ip since req uri is known */
  memset (locip, '\0', sizeof (locip));
  guessIpForVia(locip, 49);
  if (locip[0] == '\0') {
    return -10;
  }

  i = osip_message_init (&request);
  if (i != 0)
    return i;

  /* prepare the request-line */
  osip_message_set_method (request, osip_strdup (method));
  osip_message_set_version (request, osip_strdup ("SIP/2.0"));
  osip_message_set_status_code (request, 0);
  osip_message_set_reason_phrase (request, NULL);

  doing_register = 0 == strcmp ("REGISTER", method);

  if (doing_register) {
    i = osip_uri_init (&(request->req_uri));
    if (i != 0) {
      osip_message_free (request);
      return i;
    }
    i = osip_uri_parse (request->req_uri, proxy);
    if (i != 0) {
      osip_message_free (request);
      return i;
    }
    i = osip_message_set_to (request, from);
    if (i != 0 || request->to == NULL) {
      if (i >= 0)
        i = OSIP_SYNTAXERROR;
      osip_message_free (request);
      return i;
    }

    /* REMOVE ALL URL PARAMETERS from to->url headers and add them as headers */
    if (request->to != NULL && request->to->url != NULL) {
      osip_uri_t *url = request->to->url;

      while (osip_list_size (&url->url_headers) > 0) {
        osip_uri_header_t *u_header;

        u_header = (osip_uri_param_t *) osip_list_get (&url->url_headers, 0);
        if (u_header == NULL)
          break;

        if (osip_strcasecmp (u_header->gname, "from") == 0) {
        }
        else if (osip_strcasecmp (u_header->gname, "to") == 0) {
        }
        else if (osip_strcasecmp (u_header->gname, "call-id") == 0) {
        }
        else if (osip_strcasecmp (u_header->gname, "cseq") == 0) {
        }
        else if (osip_strcasecmp (u_header->gname, "via") == 0) {
        }
        else if (osip_strcasecmp (u_header->gname, "contact") == 0) {
        }
        else if (osip_strcasecmp (u_header->gname, "route") == 0) {
          osip_message_set_route (request, u_header->gvalue);
        }
        else if (osip_strcasecmp (u_header->gname, "call-info") == 0) {
          osip_message_set_call_info (request, u_header->gvalue);
        }
        else if (osip_strcasecmp (u_header->gname, "accept") == 0) {
          osip_message_set_accept (request, u_header->gvalue);
        }
        else if (osip_strcasecmp (u_header->gname, "accept-encoding") == 0) {
          osip_message_set_accept_encoding (request, u_header->gvalue);
        }
        else if (osip_strcasecmp (u_header->gname, "accept-language") == 0) {
          osip_message_set_accept_language (request, u_header->gvalue);
        }
        else if (osip_strcasecmp (u_header->gname, "alert-info") == 0) {
          osip_message_set_alert_info (request, u_header->gvalue);
        }
        else if (osip_strcasecmp (u_header->gname, "allow") == 0) {
          osip_message_set_allow (request, u_header->gvalue);
        }
        else if (osip_strcasecmp (u_header->gname, "content-type") == 0) {
          osip_message_set_content_type (request, u_header->gvalue);
        }
        else
          osip_message_set_header (request, u_header->gname, u_header->gvalue);
        osip_list_remove (&url->url_headers, 0);
        osip_uri_param_free (u_header);
      }
    }
  }
  else {
    /* in any cases except REGISTER: */
    i = osip_message_set_to (request, to);
    if (i != 0 || request->to == NULL) {
      if (i >= 0)
        i = OSIP_SYNTAXERROR;
      OSIP_TRACE (osip_trace (__FILE__, __LINE__, OSIP_ERROR, NULL, "ERROR: callee ip does not seems to be a sipurl: %s\n", to));
      osip_message_free (request);
      return i;
    }

    /* REMOVE ALL URL PARAMETERS from to->url headers and add them as headers */
    if (request->to != NULL && request->to->url != NULL) {
      osip_uri_t *url = request->to->url;

      while (osip_list_size (&url->url_headers) > 0) {
        osip_uri_header_t *u_header;

        u_header = (osip_uri_param_t *) osip_list_get (&url->url_headers, 0);
        if (u_header == NULL)
          break;

        if (osip_strcasecmp (u_header->gname, "from") == 0) {
        }
        else if (osip_strcasecmp (u_header->gname, "to") == 0) {
        }
        else if (osip_strcasecmp (u_header->gname, "call-id") == 0) {
        }
        else if (osip_strcasecmp (u_header->gname, "cseq") == 0) {
        }
        else if (osip_strcasecmp (u_header->gname, "via") == 0) {
        }
        else if (osip_strcasecmp (u_header->gname, "contact") == 0) {
        }
        else if (osip_strcasecmp (u_header->gname, "route") == 0) {
          osip_message_set_route (request, u_header->gvalue);
        }
        else if (osip_strcasecmp (u_header->gname, "call-info") == 0) {
          osip_message_set_call_info (request, u_header->gvalue);
        }
        else if (osip_strcasecmp (u_header->gname, "accept") == 0) {
          osip_message_set_accept (request, u_header->gvalue);
        }
        else if (osip_strcasecmp (u_header->gname, "accept-encoding") == 0) {
          osip_message_set_accept_encoding (request, u_header->gvalue);
        }
        else if (osip_strcasecmp (u_header->gname, "accept-language") == 0) {
          osip_message_set_accept_language (request, u_header->gvalue);
        }
        else if (osip_strcasecmp (u_header->gname, "alert-info") == 0) {
          osip_message_set_alert_info (request, u_header->gvalue);
        }
        else if (osip_strcasecmp (u_header->gname, "allow") == 0) {
          osip_message_set_allow (request, u_header->gvalue);
        }
        else if (osip_strcasecmp (u_header->gname, "content-type") == 0) {
          osip_message_set_content_type (request, u_header->gvalue);
        }
        else
          osip_message_set_header (request, u_header->gname, u_header->gvalue);
        osip_list_remove (&url->url_headers, 0);
        osip_uri_param_free (u_header);
      }
    }

    if (proxy != NULL && proxy[0] != 0) {       /* equal to a pre-existing route set */
      /* if the pre-existing route set contains a "lr" (compliance
         with bis-08) then the req_uri should contains the remote target
         URI */
      osip_uri_param_t *lr_param;
      osip_route_t *o_proxy;

      osip_route_init (&o_proxy);
      i = osip_route_parse (o_proxy, proxy);
      if (i != 0) {
        osip_route_free (o_proxy);
        osip_message_free (request);
        return i;
      }

      osip_uri_uparam_get_byname (o_proxy->url, "lr", &lr_param);
      if (lr_param != NULL) {   /* to is the remote target URI in this case! */
        i = osip_uri_clone (request->to->url, &(request->req_uri));
        if (i != 0) {
          osip_route_free (o_proxy);
          osip_message_free (request);
          return i;
        }

        /* "[request] MUST includes a Route header field containing
           the route set values in order." */
        osip_list_add (&request->routes, o_proxy, 0);
      }
      else
        /* if the first URI of route set does not contain "lr", the req_uri
           is set to the first uri of route set */
      {
        request->req_uri = o_proxy->url;
        o_proxy->url = NULL;
        osip_route_free (o_proxy);
        /* add the route set */
        /* "The UAC MUST add a route header field containing
           the remainder of the route set values in order.
           The UAC MUST then place the remote target URI into
           the route header field as the last value
         */
        osip_message_set_route (request, to);
      }
    }
    else {                      /* No route set (outbound proxy) is used */

      /* The UAC must put the remote target URI (to field) in the req_uri */
      i = osip_uri_clone (request->to->url, &(request->req_uri));
      if (i != 0) {
        osip_message_free (request);
        return i;
      }
    }
  }

  /* set To and From */
  i = osip_message_set_from (request, from);
  if (i != 0 || request->from == NULL) {
    if (i >= 0)
      i = OSIP_SYNTAXERROR;
    osip_message_free (request);
    return i;
  }

  /* REMOVE ALL URL PARAMETERS from from->url headers and add them as headers */
  if (doing_register && request->from != NULL && request->from->url != NULL) {
    osip_uri_t *url = request->from->url;

    while (osip_list_size (&url->url_headers) > 0) {
      osip_uri_header_t *u_header;

      u_header = (osip_uri_param_t *) osip_list_get (&url->url_headers, 0);
      if (u_header == NULL)
        break;

      osip_list_remove (&url->url_headers, 0);
      osip_uri_param_free (u_header);
    }
  }

  if (request->to != NULL && request->to->url != NULL) {
    int pos = 0;
    size_t pname_len;
    osip_uri_param_t *u_param;

    pname_len = strlen ("method");
    while (!osip_list_eol (&request->to->url->url_params, pos)) {
      size_t len;

      u_param = (osip_uri_param_t *) osip_list_get (&request->to->url->url_params, pos);
      len = strlen (u_param->gname);
      if (pname_len == len && osip_strncasecmp (u_param->gname, "method", pname_len) == 0 && u_param->gvalue != NULL) {
        osip_list_remove (&request->to->url->url_params, pos);
        osip_uri_param_free (u_param);
        break;
      }
      pos++;
    }
  }

  if (request->from != NULL && request->from->url != NULL) {
    int pos = 0;
    size_t pname_len;
    osip_uri_param_t *u_param;

    pname_len = strlen ("method");
    while (!osip_list_eol (&request->from->url->url_params, pos)) {
      size_t len;

      u_param = (osip_uri_param_t *) osip_list_get (&request->from->url->url_params, pos);
      len = strlen (u_param->gname);
      if (pname_len == len && osip_strncasecmp (u_param->gname, "method", pname_len) == 0 && u_param->gvalue != NULL) {
        osip_list_remove (&request->from->url->url_params, pos);
        osip_uri_param_free (u_param);
        break;
      }
      pos++;
    }
  }

  if (request->req_uri) {
    int pos = 0;
    size_t pname_len;
    osip_uri_param_t *u_param;

    pname_len = strlen ("method");
    while (!osip_list_eol (&request->req_uri->url_params, pos)) {
      size_t len;

      u_param = (osip_uri_param_t *) osip_list_get (&request->req_uri->url_params, pos);
      len = strlen (u_param->gname);
      if (pname_len == len && osip_strncasecmp (u_param->gname, "method", pname_len) == 0 && u_param->gvalue != NULL) {
        osip_list_remove (&request->req_uri->url_params, pos);
        osip_uri_param_free (u_param);
        break;
      }
      pos++;
    }
  }

  /* add a tag */
  osip_from_set_tag (request->from, mallocNewRandom ());

  /* set the cseq and call_id header */
  {
    osip_call_id_t *callid;
    osip_cseq_t *cseq;
    char *num;
    char *cidrand;

    /* call-id is always the same for REGISTRATIONS */
    i = osip_call_id_init (&callid);
    if (i != 0) {
      osip_message_free (request);
      return i;
    }
    cidrand = mallocNewRandom ();
    osip_call_id_set_number (callid, cidrand);

    request->call_id = callid;

    i = osip_cseq_init (&cseq);
    if (i != 0) {
      osip_message_free (request);
      return i;
    }
    num = osip_strdup (doing_register ? "1" : "20");
    osip_cseq_set_number (cseq, num);
    osip_cseq_set_method (cseq, osip_strdup (method));
    request->cseq = cseq;

    if (cseq->method == NULL || cseq->number == NULL) {
      osip_message_free (request);
      return OSIP_NOMEM;
    }
  }

  i = addVia (request, transport, locip);
  if (i != 0) {
    osip_message_free (request);
    return i;
  }

  /* always add the Max-Forward header */
  osip_message_set_max_forwards (request, "70");        /* a UA should start a request with 70 */

  if (0 == strcmp ("REGISTER", method)) {
  }
  else if (0 == strcmp ("INFO", method)) {
  }
  else if (0 == strcmp ("OPTIONS", method)) {
    osip_message_set_accept (request, "application/sdp");
  }

  osip_message_set_user_agent (request, "SIP DEMO");
  /*  else if ... */
  *dest = request;

  return OSIP_SUCCESS;
}

char* Client::mallocNewRandom()
{
  char *tmp = (char *) osip_malloc (33);
  unsigned int number = osip_build_random_number ();

  if (tmp == NULL)
    return NULL;

  sprintf (tmp, "%u", number);
  return tmp;
}

int Client::addVia( osip_message_t * request, const char *transport, const char *locip )
{
  char tmp[200];
  const char *ip = NULL;
  char firewall_ip[65];
  char firewall_port[10];

  if (request == NULL)
    return OSIP_BADPARAMETER;

  if (request->call_id == NULL)
    return OSIP_SYNTAXERROR;

  if (locip == NULL && request->call_id->host == NULL)
    return OSIP_SYNTAXERROR;

  if (locip != NULL)
    ip = locip;
  else if (request->call_id->host != NULL)
    ip = request->call_id->host;

  firewall_ip[0] = '\0';
  firewall_port[0] = '\0';

  if (firewall_port[0] == '\0') {
    _snprintf (firewall_port, sizeof (firewall_port), "5068");
  }

  _snprintf (tmp, 200, "SIP/2.0/%s %s:%s;rport;branch=z9hG4bK%u", "UDP", ip, firewall_port, osip_build_random_number ());

  osip_message_set_via (request, tmp);

  return OSIP_SUCCESS;
}

int Client::guessIpForVia( char* ip, int size )
{
  SOCKET sock;

  SOCKADDR_STORAGE local_addr;

  int local_addr_len;

  struct addrinfo *addrf = NULL;

  ip[0] = '\0';

  sock = socket (AF_INET, SOCK_DGRAM, 0);

  getAddrInfo ( &addrf, "217.12.3.11", 0, IPPROTO_UDP);

  if (addrf == NULL) {
      getAddrInfo ( &addrf, "217.12.3.11", 0, IPPROTO_UDP);
  }

  if (addrf == NULL) {
    closesocket (sock);
    _snprintf (ip, size, "127.0.0.1");
    return OSIP_NO_NETWORK;
  }

  if (WSAIoctl (sock, SIO_ROUTING_INTERFACE_QUERY, addrf->ai_addr, addrf->ai_addrlen, &local_addr, sizeof (local_addr), (LPDWORD)&local_addr_len, NULL, NULL) != 0) {
    closesocket (sock);
    freeaddrinfo (addrf);
    _snprintf (ip, size, "127.0.0.1");
    return OSIP_NO_NETWORK;
  }

  closesocket (sock);
  freeaddrinfo (addrf);

  if (getnameinfo ((const struct sockaddr *) &local_addr, local_addr_len, ip, size, NULL, 0, NI_NUMERICHOST)) {
    _snprintf (ip, size, "127.0.0.1");
    return OSIP_NO_NETWORK;
  }

  return OSIP_SUCCESS;
}

int Client::getAddrInfo( struct addrinfo **addrinfo, const char *hostname, int service, int protocol )
{
  struct addrinfo hints;
  char portbuf[10];
  int error;
  //int i;

  if (hostname == NULL)
    return OSIP_BADPARAMETER;

  if (service == -1) {          /* -1 for SRV record */
    /* obsolete code: make an SRV record? */
    OSIP_TRACE (osip_trace (__FILE__, __LINE__, OSIP_INFO1, NULL, "_eXosip_get_addrinfo: obsolete code?\n"));
    return -1;
  }

  _snprintf (portbuf, sizeof (portbuf), "%i", service);

  memset (&hints, 0, sizeof (hints));

  hints.ai_flags = 0;

  hints.ai_family = PF_INET;  /* ipv4 only support */

  if (protocol == IPPROTO_UDP)
    hints.ai_socktype = SOCK_DGRAM;
  else
    hints.ai_socktype = SOCK_STREAM;

  hints.ai_protocol = protocol; /* IPPROTO_UDP or IPPROTO_TCP */
  error = getaddrinfo (hostname, portbuf, &hints, addrinfo);
  if (osip_strcasecmp (hostname, "0.0.0.0") != 0) {
    OSIP_TRACE (osip_trace (__FILE__, __LINE__, OSIP_INFO2, NULL, "DNS resolution with %s:%i\n", hostname, service));
  }

  if (error || *addrinfo == NULL) {
    OSIP_TRACE (osip_trace (__FILE__, __LINE__, OSIP_INFO2, NULL, "getaddrinfo failure. %s:%s (%d)\n", hostname, portbuf, error));
    return OSIP_UNKNOWN_HOST;
  }
  else {
    struct addrinfo *elem;

    char tmp[INET6_ADDRSTRLEN];

    char porttmp[10];

    for (elem = *addrinfo; elem != NULL; elem = elem->ai_next) {
      getnameinfo (elem->ai_addr, elem->ai_addrlen, tmp, sizeof (tmp), porttmp, sizeof (porttmp), NI_NUMERICHOST | NI_NUMERICSERV);
      OSIP_TRACE (osip_trace (__FILE__, __LINE__, OSIP_INFO2, NULL, "getaddrinfo returned: %s port %s\n", tmp, porttmp));
    }
  }

  /* only one address (?) */
  (*addrinfo)->ai_next = 0;

  return OSIP_SUCCESS;
}

int Client::onRegister()
{
    return setOnlineStatus();
}

int Client::onUnRegister()
{
    return setOfflineStatus();
}

void Client::setRegTime()
{
    mRegTime = HPR_GetTimeTick();
}

HPR_UINT32 Client::getRegTime()
{
    return mRegTime;
}

bool Client::isOnline()
{
    return (onlineStatus == getRegStatus())?true:false;
}

int Client::formHbMessage( char** msg, int* msgLen, HPR_ADDR_T& addr )
{
    osip_message_t* message = NULL;
    char from[128] = {0};
    char to[128] = {0};
    const char* serverIp = HPR_GetAddrString(&addr);
    HPR_INT32 serverPort = HPR_GetAddrPort(&addr);
    HPR_Snprintf(from, sizeof(from), "sip:%s@%s:%d", mNumber.c_str(), serverIp, serverPort);
    HPR_Snprintf(to, sizeof(to), "sip:%s@%s:%d", mNumber.c_str(), serverIp, serverPort);
    formMessage(&message, "MESSAGE", to, NULL, from, NULL);
    std::string bodyXml;
    buildHeartbeatBody(bodyXml);
    osip_message_set_content_type(message, "Application/MANSCDP+xml");
    osip_message_set_body (message, bodyXml.c_str(), bodyXml.length());
    if (message != NULL)
    {
        osip_message_to_str(message, msg, (size_t*)msgLen);
        osip_message_free(message);
    }
    return 0;
}

int Client::buildHeartbeatBody( std::string& body )
{
    CMarkup xml;
    xml.SetDoc(XML_VERSION);
    xml.AddElem("videoIntercomMsg");
    xml.IntoElem();
    xml.AddElem("header");
    xml.IntoElem();
    xml.AddElem("method", 1);
    xml.AddElem("action", 1);
    body = xml.GetDoc();
    return HPR_OK;
}

int Client::onCalling()
{
    //setBusyStatus();
    setCallTime();
    return 0;
}

int Client::onEnding()
{
    //setIdleStatus();
    //setCallTimeZero();
    return 0;
}

int Client::onCalled()
{
    //setBusyStatus();
    return 0;
}

void Client::setCallTime()
{
    mCallTime = HPR_GetTimeTick();
    LOG_ERROR("number:%s, calltime:%u", mNumber.c_str(), mCallTime);
}

void Client::setCallTimeZero()
{
    mCallTime = 0;
}

HPR_UINT32 Client::getCallTime()
{
    return mCallTime;
}

int Client::checkCallTimeOut()
{
    if ( (HPR_GetTimeTick()-mCallTime)>3*1000 )
    {
        LOG_ERROR("phone:%s, calltime is :%u, now:%u", mNumber.c_str(), mCallTime, HPR_GetTimeTick());
        ClientMgr::getInstance()->addDelayNumber();
        return -1;
    }
    //LOG_ERROR("hehehehehehehehephone:%s, calltime is :%u, now:%u", mNumber.c_str(), mCallTime, HPR_GetTimeTick());
    return 0;
}

//bool Client::isBusy()
//{
//    return (busyStatus == getRegStatus())?true:false;
//}

#include"stdafx.h"
#include<hpr/HPR_Guard.h>
#include<hlog/logdef.h>
#include<hpr/HPR_Utils.h>
#include"ClientMgr.h"

ClientMgr* ClientMgr::mInstance = NULL;

ClientMgr::ClientMgr( /* arguments*/ )
: mOnlineNum(0)
, mDelayNumber(0)
{

}

ClientMgr::~ClientMgr()
{

}

int ClientMgr::init( HPR_UINT64 startNo, HPR_INT32 totalNum )
{
    mStartNo = startNo;
    mTotalNum = totalNum;

    Client* client = NULL;
    char phone_no[16];

    HPR_INT64 j = mStartNo;
    for (int i=0; i<mTotalNum; i++)
    {
        memset(phone_no, 0, 16);
        sprintf(phone_no, "%06d", j);
        client = new(std::nothrow) Client(phone_no);
        if (client != NULL)
        {
            addClient(std::string(phone_no), client);
        }
        else
        {
            LOG_ERROR("No enough memory.");
        }
        j++;
    }

    return 0;
}

void ClientMgr::fini()
{
    clearClients();
}

int ClientMgr::sendRegister(Network& networkObject)
{
    //HPR_Guard lock(&mLockClients);
    std::map<std::string,Client*>::iterator it = mClients.begin();
    char* bufToSend = NULL;
    int bufLen = 0;
    for (; it!=mClients.end(); ++it)
    {
        if (!it->second->isOnline())
        {
            if (-1 == it->second->formRegMessage(&bufToSend, &bufLen, networkObject.getServerAddr()) )
            {
                LOG_ERROR("Form msg failed.");
                continue;
            }
            if (-1 == networkObject.sendMessage(bufToSend, bufLen))
            {
                LOG_ERROR("Send msg failed.");
            }
            osip_free(bufToSend);
        }

    }

    return 0;
}

ClientMgr* ClientMgr::createInstance()
{
    if (mInstance == NULL)
    {
        mInstance = new(std::nothrow) ClientMgr;
        if (mInstance == NULL)
        {
            LOG_ERROR("No enough memory.");
        }
    }
    return mInstance;
}

ClientMgr* ClientMgr::getInstance()
{
    return mInstance;
}

void ClientMgr::delInstance()
{
    if (mInstance != NULL)
    {
        delete mInstance;
        mInstance = NULL;
    }
}

int ClientMgr::getClient( std::string& number, Client** client )
{
    //HPR_Guard lock(&mLockClients);
    std::map<std::string,Client*>::iterator it = mClients.find(number);
    if (it != mClients.end())
    {
        *client = it->second;
        return 0;
    }
    return -1;
}

void ClientMgr::clearClients()
{
    //HPR_Guard lock(&mLockClients);
    if (mClients.size() != 0)
    {
        std::map<std::string,Client*>::iterator it = mClients.begin();
        for (; it!=mClients.end();++it)
        {
            delete it->second;
            mClients.erase(it);
        }
    }

}

int ClientMgr::addClient( std::string& number, Client* client )
{
    //HPR_Guard lock(&mLockClients);
    mClients[number] = client;
    return 0;
}

int ClientMgr::sendHeartbeat( Network& networkObject )
{
    //HPR_Guard lock(&mLockClients);
    std::map<std::string,Client*>::iterator it = mClients.begin();
    char* bufToSend = NULL;
    int bufLen = 0;
    for (; it!=mClients.end(); ++it)
    {
        if (it->second->isOnline())
        {
            if (-1 == it->second->formHbMessage(&bufToSend, &bufLen, networkObject.getServerAddr()) )
            {
                LOG_ERROR("Form msg failed.");
                continue;
            }
            if (-1 == networkObject.sendMessage(bufToSend, bufLen))
            {
                LOG_ERROR("Send msg failed.");
            }
            osip_free(bufToSend);
        }

    }

    return 0;
}

void ClientMgr::AddOnlineNum()
{
    HPR_AtomicInc(&mOnlineNum);
}

void ClientMgr::DelOnlineNum()
{
    HPR_AtomicDec(&mOnlineNum);
}

HPR_INT32 ClientMgr::getOnlineNum()
{
    return HPR_AtomicCas(&mOnlineNum, 0, 0);
}

void ClientMgr::checkOnline()
{
    //HPR_Guard lock(&mLockClients);
    std::map<std::string,Client*>::iterator it = mClients.begin();
    for (; it!=mClients.end(); ++it)
    {
        if (it->second->isOnline())
        {
            if (10*60*1000 <= (HPR_GetTimeTick() - it->second->getRegTime()) )
            {
                LOG_ERROR("KeepLive Timeout, no:%s.", it->first.c_str());
                if (0 != it->second->onUnRegister() )
                {
                    DelOnlineNum();
                }
            }
        }

    }
}

int ClientMgr::sendCalling( Network& networkObject, UINT callHz )
{
    char* bufToSend = NULL;
    int bufLen = 0;
    //HPR_Guard lock(&mLockClients);
    std::map<std::string,Client*>::iterator it = mClients.begin();
    int numbers = 1;
    for (; it != mClients.end(); ++it)
    {
        //if (it->second->isBusy())
        //{
        //    continue;
        //}
        if (numbers > callHz)
        {
            break;
        }
        if (-1 == formCallMessage(&bufToSend, &bufLen, networkObject.getServerAddr(), numbers) )
        {
            LOG_ERROR("Form msg failed.");
            continue;
        }
        if (-1 == networkObject.sendMessage(bufToSend, bufLen))
        {
            LOG_ERROR("Send msg failed.");
            osip_free(bufToSend);
            continue;
        }
        osip_free(bufToSend);
        it->second->onCalling();
        ++numbers;
    }

    return 0;
}

int ClientMgr::formCallMessage( char** msg, int* msgLen, HPR_ADDR_T& addr, int number )
{
    osip_message_t* message = NULL;
    char from[128] = {0};
    char to[128] = {0};
    const char* serverIp = HPR_GetAddrString(&addr);
    HPR_INT32 serverPort = HPR_GetAddrPort(&addr);
    HPR_Snprintf(from, sizeof(from), "sip:%06d@%s:%d", number, serverIp, serverPort);
    HPR_Snprintf(to, sizeof(to), "sip:%06d@%s:%d", number+5000, serverIp, serverPort);
    if (0 != formMessage(&message, "INVITE", to, NULL, from, NULL) )
    {
        LOG_ERROR("form message fail.");
        return -1;
    }
    addContact(message);

    if (message != NULL)
    {
        osip_message_to_str(message, msg, (size_t*)msgLen);
        osip_message_free(message);
    }
    return 0;
}

int ClientMgr::formMessage( osip_message_t** dest, const char* method, const char *to, const char *transport, const char *from, const char *proxy )
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

char* ClientMgr::mallocNewRandom()
{
  char *tmp = (char *) osip_malloc (33);
  unsigned int number = osip_build_random_number ();

  if (tmp == NULL)
    return NULL;

  sprintf (tmp, "%u", number);
  return tmp;
}

int ClientMgr::addVia( osip_message_t * request, const char *transport, const char *locip )
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

int ClientMgr::guessIpForVia( char* ip, int size )
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

int ClientMgr::getAddrInfo( struct addrinfo **addrinfo, const char *hostname, int service, int protocol )
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

int ClientMgr::addContact( osip_message_t * request )
{
  osip_via_t *via;
  osip_from_t *a_from;
  char *contact = NULL;
  char locip[65];
  char firewall_ip[65];
  char firewall_port[10];
  int len;

  if (request == NULL)
    return OSIP_BADPARAMETER;

  firewall_ip[0] = '\0';
  firewall_port[0] = '\0';
  itoa(5068, firewall_port, 10);

  /* search for topmost Via which indicate the transport protocol */
  via = (osip_via_t *) osip_list_get (&request->vias, 0);
  if (via == NULL || via->protocol == NULL) {
    OSIP_TRACE (osip_trace (__FILE__, __LINE__, OSIP_ERROR, NULL, "eXosip: missing via header\n"));
    return OSIP_SYNTAXERROR;
  }

  a_from = request->from;

  if (a_from == NULL || a_from->url == NULL)
    return OSIP_SYNTAXERROR;

  /*guess the local ip since req uri is known */
  memset (locip, '\0', sizeof (locip));

  if (a_from->url->username != NULL)
    len = (int) (2 + 4 + (strlen (a_from->url->username) * 3) + 1 + 100 + 6 + 10 + strlen ("UDP"));
  else
    len = (int) (2 + 4 + 100 + 6 + 10 + strlen ("UDP"));

  contact = (char *) osip_malloc (len + 1);
  if (contact == NULL)
    return OSIP_NOMEM;

  memcpy (locip, firewall_ip, sizeof (locip));

  if (locip[0] == '\0') {
    guessIpForVia(locip, 49);
    if (locip[0] == '\0') {
      OSIP_TRACE (osip_trace (__FILE__, __LINE__, OSIP_ERROR, NULL, "eXosip: no default interface defined\n"));
      osip_free (contact);
      return OSIP_NO_NETWORK;
    }
  }


  if (a_from->url->username != NULL) {
    char *tmp2 = __osip_uri_escape_userinfo (a_from->url->username);

    HPR_Snprintf(contact, len, "<sip:%s@%s:%s>", tmp2, locip, firewall_port);
    osip_free (tmp2);
  }
  else
    HPR_Snprintf(contact, len - strlen ("UDP") - 10, "<sip:%s:%s>", locip, firewall_port);

  osip_message_set_contact (request, contact);
  osip_free (contact);

  return OSIP_SUCCESS;
}

int ClientMgr::sendAck( Network* networkObject, osip_message_t* rsp )
{
    osip_message_t* ack = NULL;
    char* from = NULL;
    char* to = NULL;
    char* buffer = NULL;
    int bufLen = 0;
    osip_from_to_str(rsp->from, &from);
    osip_to_to_str(rsp->to, &to);
    if (0 != formMessage(&ack, "ACK", to, NULL, from, NULL) )
    {
        LOG_ERROR("form message fail.");
        osip_free(from);
        osip_free(to);
        return -1;
    }
    osip_free(from);
    osip_free(to);
    osip_free(ack->call_id->number);
    ack->call_id->number = osip_strdup(rsp->call_id->number);
    //int seqNum = atoi(rsp->cseq->number);
    //char strSeqNum[16];
    //itoa(seqNum+1, strSeqNum, 10);
    //osip_free(ack->cseq->number);
    //ack->cseq->number = osip_strdup(strSeqNum);

    if (ack != NULL)
    {
        osip_message_to_str(ack, &buffer, (size_t*)&bufLen);
        osip_message_free(ack);
        ack = NULL;
    }
    else
    {
        return -1;
    }

    if (-1 == networkObject->sendMessage(buffer, bufLen))
    {
        LOG_ERROR("Send msg failed.");
        osip_free(buffer);
        return -1;
    }
    osip_free(buffer);

    return 0;
}

void ClientMgr::addDelayNumber()
{
    mDelayNumber++;
}

int ClientMgr::sendBye( Network* networkObject, osip_message_t* rsp )
{
    osip_message_t* bye = NULL;
    char* from = NULL;
    char* to = NULL;
    char* buffer = NULL;
    int bufLen = 0;
    osip_from_to_str(rsp->from, &from);
    osip_to_to_str(rsp->to, &to);
    if (0 != formMessage(&bye, "BYE", to, NULL, from, NULL) )
    {
        LOG_ERROR("form message fail.");
        osip_free(from);
        osip_free(to);
        return -1;
    }
    osip_free(from);
    osip_free(to);
    osip_free(bye->call_id->number);
    bye->call_id->number = osip_strdup(rsp->call_id->number);
    //int seqNum = atoi(rsp->cseq->number);
    //char strSeqNum[16];
    //itoa(seqNum+1, strSeqNum, 10);
    //osip_free(bye->cseq->number);
    //bye->cseq->number = osip_strdup(strSeqNum);

    if (bye != NULL)
    {
        osip_message_to_str(bye, &buffer, (size_t*)&bufLen);
        osip_message_free(bye);
        bye = NULL;
    }
    else
    {
        return -1;
    }

    if (-1 == networkObject->sendMessage(buffer, bufLen))
    {
        LOG_ERROR("Send msg failed.");
        osip_free(buffer);
        return -1;
    }
    osip_free(buffer);

    return 0;
}

HPR_INT32 ClientMgr::getDelayNumber()
{
    return mDelayNumber;
}

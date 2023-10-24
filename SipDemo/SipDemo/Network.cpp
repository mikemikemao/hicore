#include"stdafx.h"
#include<hpr/HPR_Utils.h>
#include<osipparser2/osip_parser.h>
#include<hlog/logdef.h>
#include"Network.h"
#include"Client.h"
#include"ClientMgr.h"

HPR_VOIDPTR CALLBACK bufReceiver(HPR_VOIDPTR p)
{
    Network* o = static_cast<Network*>(p);
    o->recvWorker();
    return NULL;
}

HPR_VOIDPTR CALLBACK workProccessor(HPR_VOIDPTR p)
{
    TaskData* buf = static_cast<TaskData*>(p);
    Network* o = static_cast<Network*>(buf->userData);
    char* bufAfterProc = NULL;
    HPR_INT32 bufLenAfterProc = 0;

    do
    {
        HPR_INT32 rt = o->handleIncomingMessage(buf->buffer, buf->bufLen, &bufAfterProc, &bufLenAfterProc);
        if (HPR_ERROR == rt)
        {
            //释放资源
            o->freeMemFromOut(buf->buffer);
            delete buf;
            break;
        }
        else
        {
            //if (bufLenAfterProc > 0)
            //{
            //    o->sendRsp(bufAfterProc, bufLenAfterProc);
            //}
            o->freeMemFromOut(buf->buffer);
            osip_free(bufAfterProc);
            delete buf;
        }

    } while (0);

    return NULL;
}

Network::Network( /* arguments*/ )
: mStopEvent(HPR_INVALID_HANDLE)
, mSock(HPR_INVALID_SOCKET)
, mRecvThread(HPR_INVALID_THREAD)
{

}

Network::~Network()
{

}

int Network::start(DWORD serverIp, int serverPort)
{
    int r = -1;
    HPR_ADDR_T sockAddr;
    do 
    {
        HPR_MakeAddr4ByInt(ntohl(serverIp), serverPort, &mServerAddr);

        mStopEvent = HPR_CreateEvent(HPR_FALSE);
        if (mStopEvent == HPR_INVALID_HANDLE)
        {
            LOG_ERROR("HPR_CreateEvent failed.");
            break;
        }

        if (-1 == mMemoryPool.init(MAX_RECV_LEN+1, 10000))
        {
            break;
        }

        if (-1 == mThreadPool.start(2*HPR_GetCPUNumber() + 2) )
        {
            LOG_ERROR("mThreadPool.start failed.");
            break;
        }

        mSock = HPR_CreateSocket(AF_INET, SOCK_DGRAM, 0);
        if (mSock == HPR_INVALID_SOCKET)
        {
            LOG_ERROR("HPR_CreateSocket failed.");
            break;
        }

        HPR_MakeAddrByString(AF_INET, NULL, 5068, &sockAddr);

        if (HPR_ERROR == HPR_Bind(mSock, &sockAddr))
        {
            LOG_ERROR("HPR_Bind failed.");
            break;
        }

        mRecvThread = HPR_Thread_Create(bufReceiver, this, 0);
        if (mRecvThread == HPR_INVALID_THREAD)
        {
            break;
        }

        r = 0;
    } while (0);

    if (r == -1)
    {
        stop();
    }

    return r;
}

void Network::stop()
{
    if (mStopEvent != HPR_INVALID_HANDLE)
    {
        HPR_SetEvent(mStopEvent);
    }

    if (mSock != HPR_INVALID_SOCKET)
    {
        HPR_CloseSocket(mSock);
        mSock = HPR_INVALID_SOCKET;
    }

    if (mRecvThread != HPR_INVALID_THREAD)
    {
        HPR_Thread_Wait(mRecvThread);
        mRecvThread = HPR_INVALID_THREAD;
    }

    mThreadPool.stop();
    mMemoryPool.fini();

    if (mStopEvent != HPR_INVALID_HANDLE)
    {
        HPR_CloseEvent(mStopEvent);
        mStopEvent = HPR_INVALID_HANDLE;
    }
}

void Network::recvWorker()
{
    TaskData* data = NULL;
    char* buf = NULL;
    HPR_INT32 bytes = -1;
    HPR_ADDR_T clientAddr;
    while (WAIT_OBJECT_0 != HPR_WaitForSingleObject(mStopEvent, 0))
    {
        buf = static_cast<char*>(mMemoryPool.getMemory());
        if (buf == NULL)
        {
            //若内存申请失败，则等待50ms后继续申请
            LOG_ERROR("Memory pool empty.");
            HPR_Sleep(5);
            continue;
        }

        bytes = HPR_RecvFrom(mSock, buf, MAX_RECV_LEN, &clientAddr);

        if (bytes > 5)
        {
            //合法请求
            //设置最后一个字节为0
            buf[bytes] = '\0';

            data = new(std::nothrow) TaskData;
            if (data == NULL)
            {
                mMemoryPool.freeMemory(buf);
                continue;
            }

            data->buffer = buf;
            data->bufLen = bytes;
            memcpy(&data->clientAddr, &clientAddr, sizeof(HPR_ADDR_T));
            data->userData = this;

            //收到的信令，放入任务列表中
            //LOG_INFO("recvbuf:\r\n%s", buf);
            WorkData wData;
            wData.workInfo = data;
            wData.workRoute = workProccessor;
            //wData.clearRoute = clear_routine;
            mThreadPool.pushWorkToList(wData);
        }
        else if (bytes == HPR_ERROR)
        {
            mMemoryPool.freeMemory(buf);
        }
        else
        {
            mMemoryPool.freeMemory(buf);
        }
    }
}

int Network::handleIncomingMessage(char* buffer, HPR_INT32 bufLen, char** bufAfterHandle, HPR_INT32* bufLenAfterHandle)
{
    HPR_INT32 rt = HPR_ERROR;
    osip_message_t* message = NULL;

    do
    {
        if (0 != osip_message_init(&message) )
        {
            break;
        }

        if (0 != osip_message_parse(message, buffer, bufLen))
        {
            break;
        }

        if (MSG_IS_REQUEST(message))
        {
            if (message->sip_method == NULL || message->req_uri == NULL)
            {
                break;
            }

            if (MSG_IS_INVITE(message))
            {
                osip_message_t* answer = NULL;
                char* msg = NULL;
                int msgLen = 0;
                //发送100 trying
                buildResponse(&answer, 100, message);
                if (answer != NULL)
                {
                    osip_message_to_str(answer, &msg, (size_t*)&msgLen);
                }
                sendMessage(msg, msgLen);
                if (answer != NULL)
                {
                    osip_message_free(answer);
                    osip_free(msg);
                    msg = NULL;
                    answer = NULL;
                }

                Client* client = NULL;
                if (-1 == ClientMgr::getInstance()->getClient(std::string(message->to->url->username), &client) )
                {
                    LOG_ERROR("cant find client, number:%s", message->to->url->username);
                    break;
                }
                //client->onCalled();

                //发送 180 ringing
                buildResponse(&answer, 180, message);
                if (answer != NULL)
                {
                    osip_message_to_str(answer, &msg, (size_t*)&msgLen);
                }
                sendMessage(msg, msgLen);
                if (answer != NULL)
                {
                    osip_message_free(answer);
                    osip_free(msg);
                    msg = NULL;
                    answer = NULL;
                }

                //发送 200 OK
                buildResponse(&answer, 200, message);
                if (answer != NULL)
                {
                    osip_message_to_str(answer, &msg, (size_t*)&msgLen);
                }
                sendMessage(msg, msgLen);
                if (answer != NULL)
                {
                    osip_message_free(answer);
                    osip_free(msg);
                    answer = NULL;
                    msg = NULL;
                }
            }
            else if (MSG_IS_ACK(message))
            {

            }
            else if (MSG_IS_BYE(message))
            {
                Client* client = NULL;
                if (-1 == ClientMgr::getInstance()->getClient(std::string(message->to->url->username), &client) )
                {
                    LOG_ERROR("cant find client, number:%s", message->to->url->username);
                    break;
                }
                //client->onEnding();

                osip_message_t* answer = NULL;
                char* msg = NULL;
                int msgLen = 0;
                //发送 200 OK
                buildResponse(&answer, 200, message);
                if (answer != NULL)
                {
                    osip_message_to_str(answer, &msg, (size_t*)&msgLen);
                }
                sendMessage(msg, msgLen);
                if (answer != NULL)
                {
                    osip_message_free(answer);
                    osip_free(msg);
                    msg = NULL;
                    answer = NULL;
                }
            }
        }
        else
        {
            if (message->status_code < 100 || message->status_code > 699)
            {
                break;
            }

            if (MSG_IS_RESPONSE_FOR(message, "REGISTER") )
            {
                Client* client = NULL;
                if (-1 == ClientMgr::getInstance()->getClient(std::string(message->from->url->username), &client) )
                {
                    LOG_ERROR("cant find client, number:%s", message->from->url->username);
                    break;
                }

                if (0 == client->onRegister() )
                {
                    ClientMgr::getInstance()->AddOnlineNum();
                    client->setRegTime();
                }

                //if ((HPR_GetTimeTick() - client->getRegSendTime()) >= 500)
                //{
                //    LOG_WARN("Register timeout, number:%s, sendtime:%u, recvtime:%u", message->from->url->username, client->getRegSendTime(), HPR_GetTimeTick());
                //}
            }
            else if (MSG_IS_RESPONSE_FOR(message, "MESSAGE"))
            {
                Client* client = NULL;
                if (-1 == ClientMgr::getInstance()->getClient(std::string(message->from->url->username), &client) )
                {
                    LOG_ERROR("cant find client, number:%s", message->from->url->username);
                    break;
                }
                client->setRegTime();
            }
            else if (MSG_IS_RESPONSE_FOR(message, "INVITE") )
            {
                if (message->status_code == 200)
                {
                    ClientMgr::getInstance()->sendAck(this, message);
                    ClientMgr::getInstance()->sendBye(this, message);
                    Client* client = NULL;
                    if (-1 == ClientMgr::getInstance()->getClient(std::string(message->from->url->username), &client) )
                    {
                        LOG_ERROR("cant find client, number:%s", message->from->url->username);
                        break;
                    }
                    if (-1 == client->checkCallTimeOut() )
                    {
                        LOG_ERROR("Call timeout, number:%s, call-id:%s", message->from->url->username, message->call_id->number);
                    }
                    //client->onEnding();
                }
            }
        }

        rt = HPR_OK;

    } while (0);

    if (message != NULL)
    {
        osip_message_free(message);
        message = NULL;
    }

    return rt;
}

void Network::freeMemFromOut( HPR_VOIDPTR buf )
{
    mMemoryPool.freeMemory(buf);
}

int Network::sendMessage( char* buffer, HPR_INT32 bufLen )
{
    if (-1 == HPR_SendTo(mSock, buffer, bufLen, &mServerAddr) )
    {
        LOG_ERROR("Send to server failed.");
        return -1;
    }
    return 0;
}

HPR_ADDR_T Network::getServerAddr()
{
    return mServerAddr;
}

HPR_INT32 Network::buildResponse( osip_message_t** rsp, HPR_INT32 status, osip_message_t* req )
{
    HPR_INT32 rt = HPR_ERROR;
    osip_generic_param_t *tag;
    osip_message_t *response;
    int pos;
    int i;

    do
    {
        *rsp = NULL;
        if (req == NULL)
        {
            SIP_SVR_ERROR("request is null.");
            break;
        }

        i = osip_message_init (&response);
        if (i != 0)
        {
            SIP_SVR_ERROR("osip_message_init failed.");
            break;
        }
        /* initialise osip_message_t structure */
        /* yet done... */

        response->sip_version = (char *) osip_malloc (8 * sizeof (char));
        if (response->sip_version == NULL)
        {
            SIP_SVR_ERROR("no memory.");
            osip_message_free (response);
            break;
        }
        sprintf (response->sip_version, "SIP/2.0");
        osip_message_set_status_code (response, status);

        /* handle some internal reason definitions. */
        if (MSG_IS_NOTIFY (req) && status == 481)
        {
            response->reason_phrase = osip_strdup ("Subscription Does Not Exist");
        }
        else if (MSG_IS_SUBSCRIBE (req) && status == 202)
        {
            response->reason_phrase = osip_strdup ("Accepted subscription");
        }
        else
        {
            response->reason_phrase = osip_strdup (osip_message_get_reason (status));
            if (response->reason_phrase == NULL)
            {
                if (response->status_code == 101)
                {
                    response->reason_phrase = osip_strdup ("Dialog Establishement");
                }
                else
                {
                    response->reason_phrase = osip_strdup ("Unknown code");
                }
            }
            response->req_uri = NULL;
            response->sip_method = NULL;
        }

        if (response->reason_phrase == NULL)
        {
            SIP_SVR_ERROR("no memory.");
            osip_message_free (response);
            break;
        }

        i = osip_to_clone (req->to, &(response->to));
        if (i != 0)
        {
            SIP_SVR_ERROR("osip_to_clone fail.");
            osip_message_free (response);
            break;
        }

        i = osip_to_get_tag (response->to, &tag);
        if (i != 0)       //可能有问题
        {                 /* we only add a tag if it does not already contains one! */
            if (status != 100)
            {
                char *tmp = (char *) osip_malloc (33);
                unsigned int number = osip_build_random_number ();

                if (tmp == NULL)
                    return NULL;

                sprintf (tmp, "%u", number);
                osip_to_set_tag (response->to, tmp);
            }
        }

        i = osip_from_clone (req->from, &(response->from));
        if (i != 0)
        {
            SIP_SVR_ERROR("osip_from_clone failed.");
            osip_message_free (response);
            break;
        }

        pos = 0;
        while (!osip_list_eol (&req->vias, pos)) {
            osip_via_t *via;
            osip_via_t *via2;

            via = (osip_via_t *) osip_list_get (&req->vias, pos);
            i = osip_via_clone (via, &via2);
            if (i != 0)
            {
                osip_message_free (response);
                return HPR_ERROR;
            }
            osip_list_add (&response->vias, via2, -1);
            pos++;
        }

        i = osip_call_id_clone (req->call_id, &(response->call_id));
        if (i != 0)
        {
            SIP_SVR_ERROR("osip_call_id_clone failed.");
            osip_message_free (response);
            break;
        }
        i = osip_cseq_clone (req->cseq, &(response->cseq));
        if (i != 0)
        {
            SIP_SVR_ERROR("osip_cseq_clone failed.");
            osip_message_free (response);
            break;
        }

        if (MSG_IS_SUBSCRIBE (req))
        {
            osip_header_t *exp;
            osip_header_t *evt_hdr;

            osip_message_header_get_byname (req, "event", 0, &evt_hdr);
            if (evt_hdr != NULL && evt_hdr->hvalue != NULL)
            {
                osip_message_set_header (response, "Event", evt_hdr->hvalue);
            }
            else
            {
                osip_message_set_header (response, "Event", "presence");
            }
            i = osip_message_get_expires (req, 0, &exp);
            if (exp == NULL)
            {
                osip_header_t *cp;

                i = osip_header_clone (exp, &cp);
                if (cp != NULL)
                {
                    osip_list_add (&response->headers, cp, 0);
                }
            }
        }

        osip_message_set_user_agent (response, "SIP DEMO" );

        *rsp = response;

        rt = HPR_OK;
    } while (0);

    return rt;
}


#ifndef NETWORK_WDMXTFN8
#define NETWORK_WDMXTFN8

#include<hpr/HPR_Socket.h>
#include<hpr/HPR_Event.h>
#include"MultiThreadWork.h"
#include"MemoryPool.h"
#include "osipparser2/osip_message.h"

#define MAX_RECV_LEN    8191

typedef struct TaskData
{
    char* buffer;
    int bufLen;
    HPR_ADDR_T clientAddr;
    void* userData;
}TaskData;

class Network
{
public:
    Network (/* arguments*/);
    virtual ~Network ();

    int start(DWORD serverIp, int serverPort);
    void stop();

    void recvWorker();

    int handleIncomingMessage(char* buffer, HPR_INT32 bufLen, char** bufAfterHandle, HPR_INT32* bufLenAfterHandle);
    int sendMessage(char* buffer, HPR_INT32 bufLen);
    void freeMemFromOut(HPR_VOIDPTR buf);

    HPR_INT32 buildResponse(osip_message_t** rsp, HPR_INT32 status, osip_message_t* req);

    HPR_ADDR_T getServerAddr();
private:
    HPR_HANDLE mStopEvent;
    HPR_SOCK_T mSock;
    HPR_HANDLE mRecvThread;

    MultiThreadWork mThreadPool;
    MemoryPool mMemoryPool;

    HPR_ADDR_T mServerAddr;

} /* Network */;

#endif /* end of include guard: NETWORK_WDMXTFN8 */

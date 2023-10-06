#ifndef CLIENTMGR_BMRV7YD9
#define CLIENTMGR_BMRV7YD9

#include<hpr/HPR_Mutex.h>
#include<string>
#include<map>
#include"Client.h"
#include"Network.h"

class ClientMgr
{
private:
    ClientMgr (/* arguments*/);
    virtual ~ClientMgr ();

public:
    static ClientMgr* createInstance();
    static ClientMgr* getInstance();
    static void delInstance();

    int init(HPR_UINT64 startNo, HPR_INT32 totalNum);
    void fini();

    int sendRegister(Network& networkObject);
    int sendHeartbeat(Network& networkObject);

    int getClient(std::string& number, Client** client);
    void clearClients();
    int addClient(std::string& number, Client* client);

    void AddOnlineNum();
    void DelOnlineNum();
    HPR_INT32 getOnlineNum();

    void checkOnline();

    int sendCalling(Network& networkObject, UINT callHz);
    int formCallMessage( char** msg, int* msgLen, HPR_ADDR_T& addr, int number );
    int formMessage(osip_message_t** dest, const char* method, const char *to, const char *transport, const char *from, const char *proxy);
    char* mallocNewRandom();
    int addVia(osip_message_t * request, const char *transport, const char *locip);
    int guessIpForVia(char* ip, int size);
    int getAddrInfo(struct addrinfo **addrinfo, const char *hostname, int service, int protocol);
    int addContact(osip_message_t * request);
    int sendAck(Network* networkObject, osip_message_t* rsp);
    int sendBye(Network* networkObject, osip_message_t* rsp);

    void addDelayNumber();
    HPR_INT32 getDelayNumber();

private:
    static ClientMgr* mInstance;

    std::map<std::string,Client*> mClients;
    //HPR_Mutex mLockClients;

    HPR_INT64 mStartNo;
    HPR_INT32 mTotalNum;
    HPR_ATOMIC_T mOnlineNum;

    HPR_INT32 mDelayNumber;    //呼叫延时大于3秒的次数

} /* ClientMgr */;

#endif /* end of include guard: CLIENTMGR_BMRV7YD9 */

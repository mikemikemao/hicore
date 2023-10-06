#ifndef CLIENT_AS4EDUC
#define CLIENT_AS4EDUC

#include<string>
#include<hpr/HPR_Atomic.h>
#include<hpr/HPR_Addr.h>
#include<hpr/HPR_Time.h>
#include<osipparser2/osip_parser.h>

class Client
{
public:
    Client (/* arguments*/);
    Client (const char* number);
    virtual ~Client ();

    int onRegister();

    int onUnRegister();

    int formMessage(osip_message_t** dest, const char* method, const char *to, const char *transport, const char *from, const char *proxy);
    char* mallocNewRandom();
    int addVia(osip_message_t * request, const char *transport, const char *locip);
    int guessIpForVia(char* ip, int size);
    int getAddrInfo(struct addrinfo **addrinfo, const char *hostname, int service, int protocol);
    int formRegMessage(char** msg, int* msgLen, HPR_ADDR_T& addr);
    int formHbMessage(char** msg, int* msgLen, HPR_ADDR_T& addr);
    int buildHeartbeatBody(std::string& body);

    void setRegTime();
    HPR_UINT32 getRegTime();

    int onCalling();
    int onCalled();
    int onEnding();

    bool isOnline();
    //bool isBusy();

    void setCallTime();
    void setCallTimeZero();
    HPR_UINT32 getCallTime();

    int checkCallTimeOut();

private:

    static const LONG busyStatus = 2;
    static const LONG onlineStatus = 1;
    static const LONG offlineStatus = 0;
    HPR_ATOMIC_T mRegStatus;    //注册状态
    HPR_UINT32 mRegTime;

    HPR_UINT32 mCallTime;       //呼叫发起时间

    std::string mNumber;        //长号

    inline LONG setOnlineStatus()
    {
        return HPR_AtomicCas(&mRegStatus, onlineStatus, offlineStatus);
    }

    inline LONG setOfflineStatus()
    {
        return HPR_AtomicSet(&mRegStatus, offlineStatus);
    }

    //inline LONG setBusyStatus()
    //{
    //    return HPR_AtomicCas(&mRegStatus, busyStatus, onlineStatus);
    //}

    //inline LONG setIdleStatus()
    //{
    //    return HPR_AtomicCas(&mRegStatus, onlineStatus, busyStatus);
    //}

    inline LONG getRegStatus()
    {
        return HPR_AtomicCas(&mRegStatus, onlineStatus, onlineStatus);
    }
} /* Client */;

#endif /* end of include guard: CLIENT_AS4EDUC */

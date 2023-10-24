#ifndef MULTITHREADWORK_VI7IYRRW
#define MULTITHREADWORK_VI7IYRRW

#include<list>
#include<hpr/HPR_Hpr.h>
#include<hpr/HPR_Semaphore.h>
#include<hpr/HPR_Thread.h>
#include<hpr/HPR_Mutex.h>

#define MAX_THREAD_NUM  128

typedef HPR_VOIDPTR (CALLBACK *WORKROUTINE)(HPR_VOIDPTR);
typedef HPR_VOIDPTR (CALLBACK *CLEARROUTINE)(HPR_VOIDPTR);
typedef struct WorkData
{
    WorkData()
    {
        workInfo = NULL;
        workRoute = NULL;
        clearRoute = NULL;
    }
    HPR_VOIDPTR workInfo;
    WORKROUTINE workRoute;
    CLEARROUTINE clearRoute;
}WorkData;

class MultiThreadWork
{
public:
    MultiThreadWork (/* arguments*/);
    virtual ~MultiThreadWork ();

    virtual HPR_INT32 start(HPR_INT32 threadNum);
    virtual HPR_INT32 stop();

    HPR_VOID pushWorkToList(WorkData& data);
    HPR_BOOL popWorkFromList(WorkData& data);
    HPR_VOID clearWorkList();

    HPR_VOID work();

private:
    HPR_VOID addWork(WorkData& data);
    HPR_BOOL getWork(WorkData& data);

    //�Ƿ��˳�
    HPR_BOOL mQuit;

    //���������
    std::list<WorkData> mWorkList;
    //list֮��
    HPR_Mutex mWorkLock;
    //list�ź���
    HPR_SEM_T mSem;

    //�߳���Ϣ����ָ��
    HPR_HANDLE* mThreads;
    //�߳���
    HPR_INT32 mThreadNum;
} /* MultiThreadWork */;

#endif /* end of include guard: MULTITHREADWORK_VI7IYRRW */


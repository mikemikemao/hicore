#include"stdafx.h"
#include<hpr/HPR_Utils.h>
#include<hpr/HPR_Guard.h>

#include"MultiThreadWork.h"

HPR_VOIDPTR CALLBACK threadCallback(HPR_VOIDPTR data)
{
    do 
    {
        MultiThreadWork* p = static_cast<MultiThreadWork*>(data);
        if (p == NULL)
        {
            break;
        }

        p->work();
    } while (0);

    return NULL;
}

MultiThreadWork::MultiThreadWork( /* arguments*/ )
: mQuit(HPR_TRUE)
, mThreads(NULL)
, mThreadNum(0)
, mSem(NULL)
{

}

MultiThreadWork::~MultiThreadWork()
{

}

HPR_INT32 MultiThreadWork::start( HPR_INT32 threadNum )
{
    if (threadNum <= 0)
    {
        mThreadNum = 2*HPR_GetCPUNumber() + 2;
    }
    else
    {
        mThreadNum = threadNum;
    }

    HPR_INT32 result = HPR_ERROR;

    do 
    {
        if (-1 == HPR_SemCreate(&mSem, 0) )
        {
            break;
        }

        mThreads = new(std::nothrow) HPR_HANDLE[mThreadNum];
        if (mThreads == NULL)
        {
            break;
        }

        mQuit = HPR_FALSE;
        result = HPR_OK;

        for (int i=0; i<mThreadNum; i++)
        {
            mThreads[i] = HPR_Thread_Create(threadCallback, this, 0);
            if (mThreads[i] == HPR_INVALID_THREAD)
            {
                result = HPR_ERROR;
                break;
            }
        }
    } while (0);

    if (result == HPR_ERROR)
    {
        stop();
    }

    return result;
}

HPR_INT32 MultiThreadWork::stop()
{
    mQuit = HPR_TRUE;

    if (mThreads != NULL)
    {
        for (int i=0; i<mThreadNum; i++)
        {
            HPR_SemPost(&mSem);
        }

        for (int i=0; i<mThreadNum; i++)
        {
            if (mThreads[i] != HPR_INVALID_THREAD )
            {
                HPR_Thread_Wait(mThreads[i]);
            }
        }

        delete[] mThreads;
    }

    clearWorkList();

    if (mSem != NULL)
    {
        HPR_SemDestroy(&mSem);
    }

    return HPR_OK;
}

HPR_VOID MultiThreadWork::pushWorkToList( WorkData& data )
{
    addWork(data);
    HPR_SemPost(&mSem);
}

HPR_BOOL MultiThreadWork::popWorkFromList( WorkData& data )
{
    HPR_SemWait(&mSem);
    return getWork(data);
}

HPR_VOID MultiThreadWork::clearWorkList()
{
    WorkData data;
    HPR_Guard lock(&mWorkLock);
    while (!mWorkList.empty())
    {
        data = mWorkList.front();
        mWorkList.pop_front();
        data.clearRoute(data.workInfo);
    }
}

HPR_VOID MultiThreadWork::work()
{
    WorkData data;
    while (mQuit == HPR_FALSE)
    {
        if (HPR_TRUE == popWorkFromList(data) )
        {
            if (data.workRoute != NULL)
            {
                data.workRoute(data.workInfo);
            }
        }
    }
}

HPR_VOID MultiThreadWork::addWork( WorkData& data )
{
    HPR_Guard lock(&mWorkLock);
    mWorkList.push_back(data);
}

HPR_BOOL MultiThreadWork::getWork( WorkData& data )
{
    HPR_Guard lock(&mWorkLock);
    HPR_BOOL status = HPR_FALSE;
    if (!mWorkList.empty())
    {
        data = mWorkList.front();
        mWorkList.pop_front();
        status =  HPR_TRUE;
    }
    return status;
}


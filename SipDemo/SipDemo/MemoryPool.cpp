#include"stdafx.h"
#include"MemoryPool.h"
#include<hpr/HPR_Guard.h>
#include<hpr/HPR_Utils.h>

MemoryPool::MemoryPool()
: mBuffer(NULL)
, mBufferSize(0)
, mFreeList(NULL)
, mUsedNum(0)
, mIsRelease(HPR_TRUE)
{

}

MemoryPool::~MemoryPool()
{
    mBuffer = NULL;
    mFreeList = NULL;
}

HPR_INT32 MemoryPool::init(HPR_UINT32 blockSize, HPR_UINT32 blockNum)
{
    //设置头指针
    HPR_Guard lock(&mMemLock);
    if (mBuffer != NULL)
    {
        return 0;
    }
#if (defined(_WIN32) || defined(_WIN64))
    mBuffer = (HPR_UINT8*)::VirtualAlloc(NULL, blockSize*blockNum, MEM_COMMIT, PAGE_READWRITE);
#else
    //mBuffer = (HPR_UINT8*)vmalloc(blockSize*blockNum);
    mBuffer = (HPR_UINT8*)malloc(blockSize*blockNum);
#endif

    if (mBuffer == NULL)
    {
        return -1;
    }

    mBufferSize = blockSize*blockNum;
    mFreeList = (Link*)mBuffer;

    Link* linkTmp = mFreeList;

    //对前block_num -1个内存块进行设置
    for (HPR_UINT32 i = 0; i < blockNum - 1; ++i)
    {
        linkTmp->freeList = (Link*)(linkTmp->data + blockSize);
        linkTmp = linkTmp->freeList;
    }

    //设置最后一个内存块，指向空指针
    if(linkTmp != NULL)
    {
        linkTmp->freeList = 0;
    }

    mIsRelease = HPR_FALSE;

    return 0;
}

HPR_VOID MemoryPool::fini()
{
    waitFreeAll();

    HPR_Guard lock(&mMemLock);
    if (mBuffer != NULL)
    {
#if (defined(_WIN32) || defined(_WIN64))
        ::VirtualFree(mBuffer, mBufferSize, MEM_RELEASE);
#else
        //mBuffer = (HPR_UINT8*)vfree(mBuffer);
        free(mBuffer);
#endif
        mBuffer = NULL;
    }

    mBufferSize = 0;

    return;
}

HPR_VOID MemoryPool::waitFreeAll()
{
    mIsRelease = HPR_TRUE;

    while (1)
    {
        if (checkAllFree() == HPR_TRUE)
        {
            break;
        }
        else
        {
            HPR_Sleep(300);
        }
    }

    return;
}

HPR_VOIDPTR MemoryPool::getMemory()
{
    HPR_Guard lock(&mMemLock);
    if(mIsRelease == HPR_TRUE)
    {
        return NULL;
    }

    if (mFreeList == NULL)
    {
        return NULL;
    }
    else
    {
        //取链表的第一个元素
        HPR_UINT8* retMem = mFreeList->data;
        mFreeList = mFreeList->freeList;
        ++mUsedNum;
        return retMem;
    }
}

HPR_VOID MemoryPool::freeMemory(HPR_VOIDPTR memAddr)
{
    HPR_Guard lock(&mMemLock);
    //放在链表头部
    ((Link*)memAddr)->freeList = mFreeList;
    mFreeList = (Link*)memAddr;
    --mUsedNum;

    return;
}

HPR_BOOL MemoryPool::checkAllFree()
{
    HPR_Guard lock(&mMemLock);
    return (mUsedNum == 0 ? HPR_TRUE : HPR_FALSE);
}

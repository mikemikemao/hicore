#ifndef MEMORYPOOL_L7ULDMTB
#define MEMORYPOOL_L7ULDMTB

#include<hpr/HPR_Hpr.h>
#include<hpr/HPR_Mutex.h>

class MemoryPool
{
        
    typedef union Link
    {
        union Link* freeList;
        HPR_UINT8 data[1];
    }Link;

public:
    MemoryPool();
    virtual ~MemoryPool();

public:

    /**
     @function:HPR_INT32  init(HPR_UINT32 blockSize, HPR_UINT32 blockNum)
     @brief: 初始化，分配所有内存
     @param: 
             blockSize 每一个内存块的大小
             blockNum  内存块的数量
     @notes:
     **/
    HPR_INT32 init(HPR_UINT32 blockSize, HPR_UINT32 blockNum);

    /**
     @function: HPR_VOID fini();
     @brief: 反初始化
     @param:
     @notes:
     @returns:sucess 0,other -1
     **/
    HPR_VOID fini();

    /**
     @function: HPR_VOIDPTR getMemory()
     @brief: 获取一块内存
     @notes:
     **/
    HPR_VOIDPTR getMemory();

    /**
     @function: HPR_VOID freeMemory(HPR_VOIDPTR memAddr)
     @brief: 释放内存块
     @notes:
     **/
    HPR_VOID freeMemory(HPR_VOIDPTR memAddr);

    /**
     @function: HPR_VOID waitFreeAll()
     @brief: 等待所有的内存都已释放
     @notes:
     **/
    HPR_VOID waitFreeAll();

protected:

    /**
     @function:  HPR_BOOL checkAllFree()
     @brief: 检测是否所有内存块都已释放
     @notes:
     **/
    HPR_BOOL checkAllFree();

private:

    //内存指针
    HPR_UINT8* mBuffer;
    //内存块大小
    HPR_UINT32 mBufferSize;
    //空闲内存块列表
    Link* mFreeList;
    //正在使用的数量
    HPR_UINT32 mUsedNum;
    //内存块锁
    HPR_Mutex mMemLock;
    //是否释放
    HPR_BOOL mIsRelease;

};

#endif /* end of include guard: MEMORYPOOL_L7ULDMTB */


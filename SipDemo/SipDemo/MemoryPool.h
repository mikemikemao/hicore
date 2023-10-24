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
     @brief: ��ʼ�������������ڴ�
     @param: 
             blockSize ÿһ���ڴ��Ĵ�С
             blockNum  �ڴ�������
     @notes:
     **/
    HPR_INT32 init(HPR_UINT32 blockSize, HPR_UINT32 blockNum);

    /**
     @function: HPR_VOID fini();
     @brief: ����ʼ��
     @param:
     @notes:
     @returns:sucess 0,other -1
     **/
    HPR_VOID fini();

    /**
     @function: HPR_VOIDPTR getMemory()
     @brief: ��ȡһ���ڴ�
     @notes:
     **/
    HPR_VOIDPTR getMemory();

    /**
     @function: HPR_VOID freeMemory(HPR_VOIDPTR memAddr)
     @brief: �ͷ��ڴ��
     @notes:
     **/
    HPR_VOID freeMemory(HPR_VOIDPTR memAddr);

    /**
     @function: HPR_VOID waitFreeAll()
     @brief: �ȴ����е��ڴ涼���ͷ�
     @notes:
     **/
    HPR_VOID waitFreeAll();

protected:

    /**
     @function:  HPR_BOOL checkAllFree()
     @brief: ����Ƿ������ڴ�鶼���ͷ�
     @notes:
     **/
    HPR_BOOL checkAllFree();

private:

    //�ڴ�ָ��
    HPR_UINT8* mBuffer;
    //�ڴ���С
    HPR_UINT32 mBufferSize;
    //�����ڴ���б�
    Link* mFreeList;
    //����ʹ�õ�����
    HPR_UINT32 mUsedNum;
    //�ڴ����
    HPR_Mutex mMemLock;
    //�Ƿ��ͷ�
    HPR_BOOL mIsRelease;

};

#endif /* end of include guard: MEMORYPOOL_L7ULDMTB */


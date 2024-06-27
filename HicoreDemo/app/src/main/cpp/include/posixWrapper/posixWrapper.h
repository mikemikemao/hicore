/*  
 * pwrapper.h - This file includes the POSIX wrapper's definitions and function prototypes.
 *  
 * Copyrignt (C) 2008 Hikvision Dig Tech Co.,Ltd
 *
 * Modification History
 * 01a,19Feb2008,Hu Jiexun Written
 *
 */

#ifndef __PWRAPPER_H__
#define __PWRAPPER_H__


#include <stdarg.h>
#include <pthread.h>
#include <semaphore.h>

#if (!defined(ANDROID) || (!ANDROID)) 
    #include <mqueue.h>
#else
    #include "mq/mqFactory.h"
#endif

#ifdef __cplusplus
extern  "C" {
#endif


/* timeout options */
#define NO_WAIT	0
#define WAIT_FOREVER (-1)

/* message priority options */
#define MQ_PRIO_NORMAL	0
#define MQ_PRIO_URGENT  1

/* semaphore options */
#define SEM_EMPTY 0
#define SEM_FULL  1
#define MAX_PTHREAD_NAME 256

#ifndef PTHREAD_STACK_MIN
#define PTHREAD_STACK_MIN (32*1024)
#endif

/*
 * msg queue default msg mode!
 */
#define DEFAULT_MSG_MODE        0600

#define V2PT_TICK 10 /* milliseconds per pthread scheduler tick */
void setPthreadName(char *name);
/*
 * POSIX thread library wrapper functions prototypes
 */
int pthreadGetPriorityScope(int *minPriority, int *maxPriority);
/* a variadic function to create a pthread */
int pthreadSpawnName(pthread_t *ptid, int priority, size_t stacksize, void *funcptr, char *name, unsigned args, ...);
int pthreadSpawnNameJoinable(pthread_t *ptid, int priority, size_t stacksize, void *funcptr, char *name, unsigned args, ...);
int pthreadSpawn(pthread_t *ptid, int priority, size_t stacksize, void *funcptr, unsigned args, ...);
int pthreadCreate(pthread_t	*ptid, int priority, size_t stacksize,
					void* funcptr,
					int arg0, int arg1, int arg2, int arg3, int arg4,
					int arg5, int arg6, int arg7, int arg8, int arg9);
pthread_t pthreadSelf();
int pthreadNormalCreate(pthread_t *tid,void *func, void *arg, char *name);
pid_t gettid(void);
int pthreadIdVerify(pthread_t tid);

/* pthread mutex */
int pthreadMutexInit(pthread_mutex_t *mutex);
int pthreadMutexLock(pthread_mutex_t *mutex, int wait_ms);
int pthreadMutexUnlock(pthread_mutex_t *mutex);
int pthreadMutexDestroy(pthread_mutex_t *mutex);
int pthreadCondWait(pthread_cond_t *cond, pthread_mutex_t *mutex, int wait_ms);

/*
 * POSIX message queue library wrapper functions prototypes
 */

#if (!defined(ANDROID) || (!ANDROID)) 
mqd_t mqOpen(const char *name, int oflag, mode_t mode, struct mq_attr *attr);
int mqSend(mqd_t mqdes, const char *msg_ptr, size_t msg_len, int wait_ms, unsigned msg_prio);
ssize_t mqReceive(mqd_t mqdes, char *msg_ptr, size_t msg_len, int wait_ms, unsigned *msg_prio);
int mqGetattr(mqd_t mqdes, struct mq_attr *mqstat);
int mqSetattr(mqd_t mqdes, const struct mq_attr *mqstat, struct mq_attr *omqstat);
int mqClose(mqd_t mqdes);
int mqUnlink(const char *name);
#endif

/*
 * POSIX semaphore library wrapper functions prototypes
 */
int semInit(sem_t *sem, unsigned value);
int semPost(sem_t *sem);
int semWait(sem_t *sem, int wait_ms);
int semDestroy(sem_t *sem);


#ifndef __FREERTOS__
	int pthreadSuspend(pthread_t tid);
	int pthreadResume(pthread_t tid);
	int pthreadCancel(pthread_t tid);
#endif

#ifdef __cplusplus
}
#endif

#endif//__PWRAPPER_H__


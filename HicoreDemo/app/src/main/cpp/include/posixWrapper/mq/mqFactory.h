//
// Created by zhaozhengqing on 2019/7/19.
//

#ifndef __MQFACTORY_H__
#define __MQFACTORY_H__

#include <sys/types.h>

#ifdef __cplusplus
extern "C"
{
#endif


#define MQ_MAX_COUNT 128


typedef int mqd_t;

struct mq_attr
{
    long mq_flags;    /* message queue flags			*/
    long mq_maxmsg;    /* maximum number of messages		*/
    long mq_msgsize;    /* maximum message size			*/
    long mq_curmsgs;    /* number of messages currently queued	*/
    long __reserved[4];    /* ignored for input, zeroed for output */
};


mqd_t mqOpen ( const char *name, int oflag, mode_t mode, struct mq_attr *attr );

int mqSend ( mqd_t mmq, const char *msg_ptr, size_t msg_len, int wait_ms, unsigned msg_prio );

int mqReceive ( mqd_t mmq, char *msg_ptr, size_t msg_len, int wait_ms, unsigned *msg_prio );

int mqGetattr ( mqd_t mmq, struct mq_attr *mqstat );

int mqSetattr ( mqd_t mqdes, const struct mq_attr *mqstat, struct mq_attr *omqstat );

int mqUnlink ( const char *name );

int mqClose ( mqd_t mmq );


#ifdef __cplusplus
}
#endif

#endif //__MQFACTORY_H__

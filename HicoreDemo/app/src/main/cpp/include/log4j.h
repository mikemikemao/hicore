/**	@file : log4j.h
  *  @note : HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
  *  @brief : 日志公共模块。
  *
  *  @author : JerryD
  *  @date : 2018年12月1日
  *
  *  @note : #
  *  @record : 
  *      2018年12月1日  创建 
  *      #
  *
  *  @warning : 
*/
#ifndef __HK_LOG4J_PLUS_H__
#define __HK_LOG4J_PLUS_H__



#ifdef __cplusplus
extern "C"
{
#endif

#define   LOG4J_UNIX_SOCKET_PATH    "/home/app/log4jS.socket"
#define   LOG4J_LOG_FILE_NAME       "log.4j"
#define   LOG4J_LOG_FILE_ROUTE      "/home/config/log4j/log.4j"

#define   LOG4J_MAX_PROCESS    10

#define LOG4J_CTRL_KEY              (0x6869636F)
#define LOG4J_MSG_MAGIC_NUM         (0x79ab79ab)

#define LOG4J_MSG_TYPE_LOG          (0x1001)
#define LOG4J_MSG_TYPE_CMD          (0x1002)




#define  LOG4J_MAX_LOG_SIZE   (2048)
#define  LOG4J_MAX_MODEL_NAME_SIZE   (28)



#define HK_LOG4J_DBG(model,format,...)      log4j_msg_write_v2(log4j_log_level_dbg,model,"|%s|%d|" format,__func__,__LINE__,##__VA_ARGS__);



#define HK_LOG4J_INFO(model,format,...)     log4j_msg_write_v2(log4j_log_level_info,model,"|%s|%d|" format,__func__,__LINE__,##__VA_ARGS__);



#define HK_LOG4J_WARN(model,format,...)     log4j_msg_write_v2(log4j_log_level_warning,model,"|%s|%d|" format,__func__,__LINE__,##__VA_ARGS__);




#define HK_LOG4J_ERR(model,format,...)      log4j_msg_write_v2(log4j_log_level_error,model,"|%s|%d|" format,__func__,__LINE__,##__VA_ARGS__);


#define HK_LOG4J_RECORD(model,format,...)      log4j_msg_write_v2(log4j_log_level_record,model,"|%s|%d|" format,__func__,__LINE__,##__VA_ARGS__);

#define HK_LOG4J_CMD(cmd)      log4j_msg_write(log4j_log_level_cmd,"CMD",cmd);
#define  LOG4J_CONTROL_CMD_LOG_SYNC               "sync"
#define  LOG4J_SYNC_LOG_FILE    HK_LOG4J_CMD(LOG4J_CONTROL_CMD_LOG_SYNC) 

    


typedef enum{



    log4j_log_level_dbg = 0,
    log4j_log_level_info = 1,
    log4j_log_level_warning = 2,
    log4j_log_level_error = 3,
    log4j_log_level_record = 4,
    log4j_log_level_cmd = 5,

}LOG4J_LOG_LEVEL_E;

typedef enum{

	dbg_none = 0,
	dbg_err = 1,
	dbg_info = 2,
	dbg_hint = 3,
	dbg_seti = 6,

}DBG_LOG_LEVEL_E;


typedef struct{

    LOG4J_LOG_LEVEL_E level;
    unsigned char  name[LOG4J_MAX_MODEL_NAME_SIZE];

}log4j_log_msg_head_context_t,*log4j_log_msg_head_context_p;



typedef struct{

    unsigned char cmd[32];

}log4j_cmd_msg_head_context_t,*log4j_cmd_msg_head_context_p;




typedef struct{

    unsigned int magic;
    unsigned short type;
    unsigned short len;
    union{
        
        log4j_log_msg_head_context_t log;
        log4j_cmd_msg_head_context_t cmd;
    }context;

}log4j_msg_head_t,*log4j_msg_head_p;

typedef struct
{
    int level;
} log4j_ctrl_t;

int log4j_msg_read(int fd,unsigned char *buff, int *rcvLen);
//void  log4j_msg_write(LOG4J_LOG_LEVEL_E level, const char *modelName, const char *format, ...);
void  log4j_msg_write(LOG4J_LOG_LEVEL_E level, const char *modelName, const char *logContext);

void  log4j_msg_write_v2(LOG4J_LOG_LEVEL_E level, const char *modelName, const char *format, ...);



#ifdef __cplusplus
}
#endif



#endif

/*******************************************************************************
        Filename:  sntp.h
     Description:  SNTP lib use head file
         Version:  1.0
         Created:  12/21/2006 CST 51
          Author:  xmq <xiemq@hikvision.com>
         Company:  Hangzhou Hikvision Digital Technology Co.,Ltd
******************************************************************************/

#ifndef _SNTP_H
#define _SNTP_H

#ifdef  __cplusplus
extern "C" {
#endif


typedef struct
{
    char* byNetWorkName;  // 网卡名,空间由sntp组件指定，由应用填写
    int byNameBufferLen; // byNetWorkName 的空间大小，sntp组件指定
    int byNameLen; // 网卡名长度，有应用填写
    char byRes[64];
}SNTP_BIND_NETWORK_T;


// 0:成功  -1失败
typedef int  (* SNTP_BIND_NETWORK_CALL_BACK)(SNTP_BIND_NETWORK_T* pstData);


/* init SNTP lib */
int     init_sntp_lib(void *func_ptr);

/* SNTP client func */
int     sntp_client(char *host, int port);

/* 设置绑定网卡回调 */
int  sntp_set_bing_network_cb(SNTP_BIND_NETWORK_CALL_BACK cb);

/* release SNTP lib */
void    fini_sntp_lib(void);

#ifdef  __cplusplus
}
#endif
#endif	/* _SNTP_H */


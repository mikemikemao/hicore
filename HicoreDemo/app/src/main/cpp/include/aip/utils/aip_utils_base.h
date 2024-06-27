/**
 * @copyright  HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file       aip_utils_base.h
 * @brief      基础函数
**/

#ifndef __AIP_UTILS_BASE_H__
#define __AIP_UTILS_BASE_H__

/************************************************************************
 Included Header
 ************************************************************************/
#include "HPR_Types.h"
#include "common/aip_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 Macros
 ************************************************************************/

#ifndef __FREERTOS__
    #define AIP_INVALID_THREADID -1
    #define AIP_PTHREAD_MUTEX_RECURSIVE PTHREAD_MUTEX_RECURSIVE_NP
#else
    #define AIP_INVALID_THREADID NULL
    #define AIP_PTHREAD_MUTEX_RECURSIVE PTHREAD_MUTEX_RECURSIVE
#endif

/**
 * @brief   取最大值
 * @return  返回输入两个数中的最大值
**/
#ifndef MAX
#define MAX(a, b) ((a) < (b) ? (b) : (a))
#endif

/**
 * @brief   取最小值
 * @return  返回输入两个数中的最小值
**/
#ifndef MIN
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#endif

/**
 * @brief   取绝对值
 * @return  返回输入数字的绝对值
**/
#ifndef ABS
#define ABS(a) ((a) < 0 ? -(a) : (a))
#endif

/**
 * @brief   校验是否是2的幂(前提是一个无符号整形)
 * @return  是：ture; 否：false
**/
#ifndef IS_POW_OF_2
#define IS_POW_OF_2(x) (!(x & (x-1)))
#endif

/**
 * @brief   判断输入数值是否互不相等
 * @return  true : 输入的三个数值互不相等;
 *          false: 输入的三个数值至少有两个相等
**/
#ifndef EACH_UNEQUAL
#define EACH_UNEQUAL(a, b, c) (a == b ? false : (a == c ? false : (b == c ? false : true)))
#endif

/**
 * @brief 安全释放指针
**/
#ifndef SAFE_FREE
#define SAFE_FREE(p) do{if(p){free(p);(p=NULL);}}while(0);
#endif

/**
 * @brief 安全释放描述符
**/
#ifndef SAFE_CLOSE
#define SAFE_CLOSE(fd) do {if(-1!=fd){close(fd);(fd)=-1;} } while(0)
#endif

/**
 * @brief 安全释放文件流
**/
#ifndef SAFE_FCLOSE
#define SAFE_FCLOSE(pFile) do {if(pFile){fclose(pFile);(pFile)=NULL;} } while(0)
#endif

/************************************************************************
 Type Definition
 ************************************************************************/


/************************************************************************
 Function Declaration
 ************************************************************************/

/**
 * @fn         AIP_EXTERN HPR_UINT32 aip_common_checksum_8u(HPR_UINT8 *pbyBuf, HPR_UINT32 dwLen)
 * @brief      对8bit的buffer求和
 * @param[in]  pbyBuf : buffer首地址
 * @param[in]  dwLen : buffer大小(单位字节)
 * @return     成功返回 sum, 失败返回HPR_ERROR
**/
AIP_EXTERN HPR_UINT32 aip_common_checksum_8u(HPR_UINT8 *pbyBuf, HPR_UINT32 dwLen);

/**
 * @fn         AIP_EXTERN HPR_UINT32 aip_common_checksum_16u(HPR_UINT16 *pwBuf, HPR_INT32 dwLen)
 * @brief      对16bit的buffer求和
 * @param[in]  pwBuf : buffer首地址
 * @param[in]  dwLen : buffer大小(单位字节)
 * @return     成功返回 sum, 失败返回HPR_ERROR
**/
AIP_EXTERN HPR_UINT32 aip_common_checksum_16u(HPR_UINT16 *pwBuf, HPR_INT32 dwLen);


/**
 * @fn       : AIP_EXTERN HPR_LONG aip_utils_get_uptime(HPR_VOID)
 * @brief    : 获取系统启动时间(单位s)
 * @return   : 系统启动时间(s)
 */
AIP_EXTERN HPR_LONG aip_utils_get_uptime(HPR_VOID);

/**
 * @fn       : AIP_EXTERN HPR_INT64 aip_utils_get_uptime_in_ms(HPR_VOID)
 * @brief    : 获取系统启动时间(单位ms)
 * @return   : 系统启动时间(ms)
 */
AIP_EXTERN HPR_INT64 aip_utils_get_uptime_in_ms(HPR_VOID);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_utils_system_call(HPR_INT8 *szCmd)
 * @brief      system的封装
 * @param[in]  szCmd： 要执行的shell命令或者进程指令
 * @note       调用子进程前，释放从父进程继承的描述符资源
 * @note       cmd 将会交给sh启动
 * @note       该接口默认阻塞,若希望不等待，可通过追加&让shell后台执行
 * @see        aip_utils_start_process
 * @return     保持和system 返回值一致
 */
AIP_EXTERN HPR_INT32 aip_utils_system_call(HPR_INT8 *szCmd);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_utils_start_process(HPR_INT8 *szCmd, HPR_BOOL bBlock)
 * @brief      启动子进程
 * @param[in]  szCmd： 要执行的shell命令或者进程指令
 * @param[in]  bBlock：是否阻塞等级子进程执行结束
 * @note       调用子进程前，释放从父进程继承的描述符资源
 * @note       该接口将阻塞指导调用的命令结束生命周期
 * @note       注意该接口不会将指令交给shell启动，参数请勿携带&, >> 、> 等shell重定向参数也会和aip_utils_system_call表现不一致
 * @see        aip_utils_system_call
 * @return     成功返回: 子进程pid； fail:-1
 */
AIP_EXTERN HPR_INT32 aip_utils_start_process(HPR_INT8 *szCmd, HPR_BOOL bBlock);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_utils_start_process_low_memory(HPR_INT8 *szCmd, HPR_BOOL bBlock)
 * @brief      vfork启动子进程, 低内存下使用
 * @param[in]  szCmd： 要执行的shell命令或者进程指令
 * @param[in]  bBlock：是否阻塞等级子进程执行结束
 * @note       调用子进程前，释放从父进程继承的描述符资源
 * @note       该接口将阻塞指导调用的命令结束生命周期
 * @note       注意该接口不会将指令交给shell启动，参数请勿携带&, >> 、> 等shell重定向参数也会和aip_utils_system_call表现不一致
 * @see        aip_utils_system_call
 * @return     成功返回: 子进程pid； fail:-1
 */
AIP_EXTERN HPR_INT32 aip_utils_start_process_low_memory(HPR_INT8 *szCmd, HPR_BOOL bBlock);

/**
 * @fn         AIP_EXTERN HPR_INT32 aip_utils_write_file_by_shell(const HPR_INT8 *szCmd, const HPR_INT8 *szFileName)
 * @brief      执行指定的shell命令并将结果输出到指定文件
 * @param[in]  szCmd : 要执行的命令
 * @param[in]  szFileName : 要输出到的文件
 * @return     HPR_OK： success;other :fail
 * @note       若文件不存在会先创建, 若文件已存在则会在文件中追加内容，并保留文件原有数据
**/
AIP_EXTERN HPR_INT32 aip_utils_write_file_by_shell(const HPR_INT8 *szCmd, const HPR_INT8 *szFileName);

/**
 * @fn       : AIP_EXTERN HPR_INT32 aip_utils_gen_randnum(HPR_VOID)
 * @brief    : 获取一个随机数
 * @return   : 随机数
 */
AIP_EXTERN HPR_INT32 aip_utils_gen_randnum(HPR_VOID);

/**
 * @fn       : aip_utils_gen_rand_str
 * @brief    : 随机生成指定长的字符串, 生成随机串会是以数字和小写字母(0-f)组成的字符
 * @param    : pOut [out]: 储存字符串的地址,确保pOut的size满足dwLen
 * @param    : dwLen [in]: 字符串长度
 * @return   : HPR_OK: success ; other: fail
 */
AIP_EXTERN HPR_INT32 aip_utils_gen_rand_str(HPR_INT8 *pbyOut, HPR_INT32 dwLen);


#ifdef __cplusplus
}
#endif
#endif /* __AIP_UTILS_BASE_H__ END */

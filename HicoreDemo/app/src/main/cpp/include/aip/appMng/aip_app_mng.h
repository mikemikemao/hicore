/******************************************************************************
  @note HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 ******************************************************************************
  @file     : aip_app_mng.h
  @brief    : APP管理模块
  @warning  : Special notes that need to pay attention to when using and modifying the file. 
******************************************************************************/

#ifndef __AIP_APP_MNG_H__
#define __AIP_APP_MNG_H__

/*----------------------------------------------*
 * Included Header   
 *----------------------------------------------*/
#include <sys/types.h>
#include "common/aip_common.h"
#include "common/aip_common_event.h"

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------*
 * Macros                                       *
 *----------------------------------------------*/


/*----------------------------------------------*
 * Struct/Enum Definition                       *
 *----------------------------------------------*/
/**
 * @brief      APP管理模块回调类型
**/
typedef enum
{
    E_APP_EVENT_UPDATE_INSTALL_PRECENT       = 1,   // 更新app安装进度
                                      //入参:HPR_UINT32 dwPrecent, 范围0-100
                                      //出参:NULL
                                      //返回值: HPR_OK
                                      //       HPR_ERROR
    E_APP_EVENT_ALL_DEBUG_LICENSE_EXPIRED    = 2,   // 所有Debug证书均到期，间隔1h检测一次
                                    //入参:NULL
                                    //出参:NULL
                                    //返回值: NULL
                                    //        
}APP_EVENT_CMD_E;
/**
 *  @brief APP管理模块事件回调
 */
typedef AIP_EVENT_CALLBACK_FUN APP_EVENT_CALLBACK_FUN ;

/**
 * @brief  错误码
**/
typedef enum
{
    AIP_APP_MNG_ERROR = -1,       // 导入失败
    AIP_APP_MNG_OK = 0,           // 导入成功
    AIP_APP_MNG_NO_MEM_ERR = 1,   // 申请内存超过资源总量
    AIP_APP_MNG_NO_FRESH_ERR,     // 申请FALSH超过资源总量
    AIP_APP_MNG_INVAL_PARAM_ERR,  // 导入解析过程参数有异常
    AIP_APP_MNG_CERT_MISMATCH,    // 证书与设备不匹配
    AIP_APP_MNG_INVALID_APP_ID,   // 无效app id
    AIP_APP_MNG_CERT_HAS_EXPIRED, // 证书已过期
    AIP_APP_MNG_CERT_CONTEXT_ERR, // 证书内容有误
    AIP_APP_MNG_APP_NUM_MAX,      // 有效App数量达到上限
    AIP_APP_MNG_APP_NO_SIGN,      // App未签名
    AIP_APP_MNG_APP_STARING,      // App正在启动中
    AIP_APP_MNG_APP_HAS_STARTED,  // App已启动
    AIP_APP_MNG_APP_STOPPING,     // App正在停止中
    AIP_APP_MNG_APP_HAS_STOPPED,  // App已停止
} AIP_APP_MNG_ERR_CODE_E;

/**
 * @brief  APP类型
**/
typedef enum
{
    APP_MNG_TYPE_HEOP_SANDBOX_APP       = 1,    // heop sanbox app
    APP_MNG_TYPE_ANDROID_APK            = 2,    // Android apk

}AIP_APP_MNG_TYPE_E;

/**
 * @brief  APP类型
**/
typedef enum
{
    APP_RUN_STATUES_STOPPED    = 0,    // 已停止运行
    APP_RUN_STATUES_RUNNING    = 1,    // 运行中
    APP_RUN_STATUES_STARTTING  = 2,    // 正在启动中
    APP_RUN_STATUES_STOPPING   = 3,    // 正在停止
}AIP_APP_RUN_STATUES_E;


/**
 * @brief  android apk 信息
**/
typedef struct
{
    HPR_INT8  byVendor[64 + 1];     // 供应商，如果是海康自己的则是Hikvision
    HPR_INT8  byVersion[64 + 1];    // 版本信息
    HPR_UINT8 byPreInstalled;       // 是否是预装apk，1--预装应用， 0--非预装应用,预装apk Android重新上电会自动拉起
    HPR_INT8  res;
    HPR_INT32 dwMemory;             // 占用内存大小
    HPR_INT32 dwFlash;              // 占用flash大小
    HPR_INT32 dwPermission;         // 第三方应用程序的权限，按位表示，bit0-stream, bit1 - algparam，bit2-默认桌面
    
} ANDROID_APK_INFO_T, *ANDROID_APK_INFO_P;

/**
 * @brief  heop sandbox app 信息
**/
typedef struct
{
    HPR_INT8  byPackageName[32 + 1]; // 第三方应用程序名称
    HPR_INT8  byPlatForm[16 + 1];    // APP所属平台
    HPR_INT8  byShellFile[64 + 1];   // shell 脚本程序名
    HPR_INT8  byStartLogo[64 + 1];   // 启动logo
    HPR_INT8  byAppId[32 + 1];       // 应用程序ID,唯一标识
    HPR_INT8  byLinkPath[128 + 1];   // 页面连接路径
    HPR_INT8  byVersion[64 + 1];     // 版本信息
    HPR_INT8  byVendor[64 + 1];      // 供应商，如果是海康自己的则是Hikvision
    HPR_INT8  byPackagePath[128];    // 第三方应用软件包解包路径
    HPR_INT32 dwAppType;             // 第三方应用程序类型或者启动方式，0--可执行程序，1--shell脚本/以shell脚本方式启动程序
    HPR_INT32 dwLicenceInstalled;    // 0-免费，1-未激活，2-已激活，3-已过期
    HPR_INT32 dwPermission;          // 第三方应用程序的权限，按位表示，bit0-stream, bit1 - algparam
    HPR_INT32 dwMemory;              // 占用内存大小
    HPR_INT32 dwFlash;               // 占用flash大小
    HPR_INT32 dwRecoverTimes;        // APP退出时自动拉起次数。 -1:debug模式APP不重启沙盒不退出 0:app退出沙盒,app处于关闭状态。N:30分钟内app重启超过N次不再重启，未超过则计数清除。N足够大时可以无限重启。
    HPR_UINT8 bStartedOnce;          // 是否开启过
    HPR_UINT8 byuv;                  // 是否需要YUV
    HPR_UINT8 res[2];
    HPR_INT8  byIntroPath[128 + 4];   // APP的介绍路径
    HPR_INT8  byLogoPath[128 + 4];    // APP的展示logo路径
    HPR_INT8  byMD5Signature[32 + 4]; // MD5 加密过的签名
    HPR_INT8  byCopyRight[128 + 4];   // APP的版权信息
    HPR_INT8  byHostName[128 + 4];    // APP的官网域名
    HPR_INT32 dwHoursLeft;            // lisence剩余时长
} HEOP_SANDBOX_APP_INFO_T, *HEOP_SANDBOX_APP_INFO_P;

/**
 * @brief   单个app信息
**/
typedef struct
{
    HPR_INT8  byAppName[64];            //app名称
    HPR_INT8  byAppMngType;             //app类型, 1--heop sandbox app  2--Android apk, 详见AIP_APP_MNG_TYPE_E
    HPR_INT8  byRunStatus;              //运行状态, 0--停止  1--正在运行，其他状态在存储时都属于运行状态，详见AIP_APP_RUN_STATUES_E
    HPR_INT8  byIsPreInstall;           //是否为预装APP, 0--不是预装app  1--是预装app
    HPR_INT8  byRes;
    union
    {
        HEOP_SANDBOX_APP_INFO_T    stHeopSandboxApp;        // heop sandbox app 信息， byAppMngType == 1 (APP_MNG_TYPE_HEOP_SANDBOX_APP)
        ANDROID_APK_INFO_T         stAndroidApk;            // android apk 信息， byAppMngType == 2(APP_MNG_TYPE_ANDROID_APK)
    };
} APP_MNG_APP_INFO_T, *APP_MNG_APP_INFO_P;

/**
 * @brief      app管理模块配置参数
**/
typedef struct
{
    HPR_INT8 byDisclaimer;//免责声明使能 0-未使能，1-使能
    HPR_INT8 byPreinstallFinish;//已完成预装标志位（内部维护，用户不能设置）， 0-未完成，1-已完成
    HPR_INT8 byRes[6];
} APP_MNG_CONFIG_T, *APP_MNG_CONFIG_P;

/**
 *  @brief APP管理模块APP资源使用信息
 */
typedef struct
{
    HPR_UINT32 dwMaxFlash;                         //最大允许使用flash,单位MB,不手动修改，查询HEOP_INSTALL_PATH路径获取磁盘分区空间信息
    HPR_UINT32 dwFlash;                            //已使用flash,单位MB，不手动修改，查询HEOP_INSTALL_PATH路径获取获取磁盘分区空间信息
    HPR_UINT32 dwMaxMemory;                        //最大允许使用内存量,单位MB
    HPR_UINT32 dwMemory;                           //已使用内存量,单位MB
} APP_MNG_RESOURCE_USE_INFO;

/**
 * @brief  APP管理模块的app信息列表
 **/
typedef struct
{
    HPR_UINT32 dwMaxAppNum;        // 支持最大的APP数量
    APP_MNG_APP_INFO_T *pInfoList; // APP信息列表
    HPR_INT8 byRes[8];
} APP_MNG_APP_INFO_LIST_T, *APP_MNG_APP_INFO_LIST_P;

/**
 * @brief      app管理模块初始化结构体
**/
typedef struct
{
    HPR_UINT32 dwMaxAppNum;                        // 支持最大的APP数量
    HPR_INT8 byPreinstallAppPath[COMMON_PATH_LEN]; // 预装APP路径
    HPR_UINT32 dwMaxFlashSize;                     // APP可用flash大小，单位MB
    HPR_UINT32 dwMaxRamSize;                       // APP最大可用内存大小，单位MB
    HPR_INT8 byLicenseDbKey[64];                 // 证书数据库加密秘钥
    HPR_INT8 byRes[8];
} APP_MNG_INIT_T, *APP_MNG_INIT_P;
/*----------------------------------------------*
 * Function Declare                              *
 *----------------------------------------------*/

/**
 * @fn         aip_app_get_resource_used_info
 * @brief      APP管理模块获取当前资源使用情况
 * @param [out]  pstUsedInfo: 当前资源使用情况
 * @return     HPR_OK: success； other:fail
 * @note       pstUsedInfo指针不能为空
**/
AIP_EXTERN HPR_INT32 aip_app_get_resource_used_info(APP_MNG_RESOURCE_USE_INFO *pstUsedInfo);

/**
 * @fn         aip_app_get_app_info_list
 * @brief      APP管理模块获取当前APP信息列表
 * @param [out]  pAppInfoList: 获取APP信息列表
 * @param [in]  dwMaxAppNum: pAppInfo数组大小
 * @return     HPR_OK: success； other:fail
 * @note       
**/
AIP_EXTERN HPR_INT32 aip_app_get_app_info_list(APP_MNG_APP_INFO_T *pAppInfoList, HPR_UINT32 dwMaxAppNum);

/**
 * @fn         aip_app_install
 * @brief      APP管理模块app安装
 * @param  [in]  pPath heop app安装包路径
 * @param  [out] pAppName 安装成功的APP名称
 * @param  [in]  dwLen pAppName缓冲区大小
 * @return       详见AIP_APP_MNG_ERR_CODE_E
 * @note       
**/
AIP_EXTERN HPR_INT32 aip_app_install(HPR_INT8 *pPath, HPR_INT8 *pAppName, HPR_UINT32 dwLen);

/**
 * @fn         aip_app_start
 * @brief      APP管理模块app启动
 * @param  [in]  dwIndex  （dwIndex-1）表示在applist中的索引值
 * @return       HPR_OK 成功/other 失败
 * @note       
**/
AIP_EXTERN HPR_INT32 aip_app_start(HPR_UINT32 dwIndex);

/**
 * @fn         aip_app_stop
 * @brief      APP管理模块app停止
 * @param  [in]  dwIndex  （dwIndex-1）表示在applist中的索引值
 * @return       HPR_OK 成功/other 失败
 * @note       
**/
AIP_EXTERN HPR_INT32 aip_app_stop(HPR_UINT32 dwIndex);

/**
 * @fn         aip_app_uninstall
 * @brief      APP管理模块app卸载
 * @param  [in]  dwIndex  （dwIndex-1）表示在applist中的索引值
 * @param  [in]  dwDelUserDate  用户数据管理  0:不删除 1: 删除
 * @return       HPR_OK 成功/other 失败
 * @note       
**/
AIP_EXTERN HPR_INT32 aip_app_uninstall(HPR_UINT32 dwIndex, HPR_INT32 dwDelUserDate);

/**
 * @fn         aip_app_mng_init
 * @brief      APP管理模块初始化
 * @param[in]  pstInitParam: 初始化参数
 * @param[in]      fnCbFun, 回调函数
 * @return     HPR_OK: success； other:fail
 * @note       
**/
AIP_EXTERN HPR_INT32 aip_app_mng_init(APP_MNG_INIT_T* pstInitParam, APP_EVENT_CALLBACK_FUN fnCbFun);

/**
 * @fn         aip_app_set_app_mng_cfg
 * @brief      APP管理模块设置app管理模块配置
 * @param  [in]  pstAppMngCfg  app管理模块配置
 * @return       HPR_OK 成功/other 失败
 * @note       
**/
AIP_EXTERN HPR_INT32 aip_app_set_app_mng_cfg(APP_MNG_CONFIG_T *pstAppMngCfg);

/**
 * @fn         aip_app_get_app_mng_cfg
 * @brief      APP管理模块获取app管理模块配置
 * @param  [out]  pstAppMngCfg  app管理模块配置
 * @return       HPR_OK 成功/other 失败
 * @note       
**/
AIP_EXTERN HPR_INT32 aip_app_get_app_mng_cfg(APP_MNG_CONFIG_T *pstAppMngCfg);

/**
 * @fn           aip_app_get_app_info
 * @brief        APP管理模块按照索引值获取app信息
 * @param  [in]  dwIndex  （dwIndex-1）表示在applist中的索引值
 * @param [out]  pAppInfo: 获取APP信息
 * @return       HPR_OK: success； other:fail
 * @note       
**/
AIP_EXTERN HPR_INT32 aip_app_get_app_info(HPR_UINT32 dwIndex, APP_MNG_APP_INFO_T *pAppInfo);

/**
 * @fn         aip_app_get_app_info_by_name
 * @brief      APP管理模块按照app名称获取app信息
 * @param [in]  pAppName: app名称
 * @param [out]  pAppInfo: 获取APP信息
 * @return     HPR_OK: success； other:fail
 * @note       
**/
AIP_EXTERN HPR_INT32 aip_app_get_app_info_by_name(HPR_INT8 *pAppName, APP_MNG_APP_INFO_T *pAppInfo);

/**
 * @fn         aip_app_mng_reset
 * @brief      APP管理模块复位
 * @param[in]  NULL
 * @return     NULL
 * @note       
**/
AIP_EXTERN HPR_VOID aip_app_mng_reset(HPR_VOID);

/**
 * @fn           aip_app_import_license
 * @brief        APP管理模块导入证书
 * @param  [in]  pLicenseData: 证书数据
 * @param  [in]  dwLicenseLen: 证书数据长度
 * @return       详见AIP_APP_MNG_ERR_CODE_E
 * @note       
**/
AIP_EXTERN HPR_INT32 aip_app_import_license(HPR_INT8 *pLicenseData, HPR_UINT32 dwLicenseLen);

/**
 * @fn           aip_app_debug_license_get_valid_num
 * @brief        获取有效调试证书数量
 * @param  [in]  NULL
 * @return       当前有效调试证书数量
**/
AIP_EXTERN HPR_UINT32 aip_app_debug_license_get_valid_num(HPR_VOID);

/**
 * @fn         aip_app_mng_set_debug_mode
 * @brief      APP管理模块开启调试模式
 *                  1、android apk安装不进行验签
 * @param [in] byDebug  开启调试模式。 0-不开启调试模式，1-开启调试模式
 * @return     NULL
 * @note       
**/
AIP_EXTERN HPR_VOID aip_app_mng_set_debug_mode(HPR_INT8 byDebug);
#ifdef __cplusplus
}
#endif

#endif
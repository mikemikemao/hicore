/**
 * @copyright HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 * @file      aip_security_user_utils.h
 * @brief     用户安全相关的一些基础接口
**/

#ifndef __AIP_SECURITY_USER_UTILS_H__
#define __AIP_SECURITY_USER_UTILS_H__

/************************************************************************
 Included Header
 ************************************************************************/
#include "common/aip_common.h"

#ifdef __cplusplus
extern "C"{
#endif



/************************************************************************
 Macros
 ************************************************************************/

/************************************************************************
 Type Definition
 ************************************************************************/

/**
 * @brief : 口令安全等级
 */
typedef enum
{
    E_SECURITY_PWD_LEVEL_INVALID   = -1, // 无效口令，非acsii码或其他异常
    E_SECURITY_PWD_LEVEL_RISK      = 0,  // 风险口令：口令长度小于 8 字符，或只包含 4 类字符中的任意一类，或为常用的风险口令
    E_SECURITY_PWD_LEVEL_NORMAL    = 1,  // 普通口令：包含 2 类字符，且长度大于等于 8 字符
    E_SECURITY_PWD_LEVEL_STRONG    = 2,  // 强口令  ：包含 3 类字符及以上，且长度大于等于 8 字符
} SECURITY_PWD_LEVEL_E;

/**
 * @brief : 风险口令
 */
typedef enum
{
    E_SECURITY_RISKPWD_SHORT            =1, // 风险口令：长度小于8
    E_SECURITY_RISKPWD_ONE_TYPE         =2, // 风险口令：只包含 4 类字符中的任意一类
    E_SECURITY_RISKPWD_HIK              =3, // 风险口令：包含公司短语（标配产品）
    E_SECURITY_RISKPWD_USERNAME         =4, // 风险口令：包含用户名
    E_SECURITY_RISKPWD_MIRROR_USERNAME  =5, // 风险口令：包含用户名倒写
    E_SECURITY_RISKPWD_SAME             =6, // 风险口令：包含连续的4个相同字符
    E_SECURITY_RISKPWD_STEP             =7, // 风险口令：包含4个连续字符
    E_SECURITY_RISKPWD_COMMON           =8, // 风险口令：常用风险口令
} SECURITY_RISKPWD_E;

/************************************************************************
  Function Declaration
 ************************************************************************/

/**
 * @fn       AIP_EXTERN HPR_INT32 aip_security_set_system_passwd(const HPR_INT8 *szUserName, const HPR_INT8 *szSalt, const HPR_INT8 *szPasswdHash)
 * @brief    设置系统用户配置文件（ssh登陆认证使用）
 * @param    [in] szUserName       : 用户名，一般固定为 "root"
 * @param    [in] szSalt           : admin 用户的salt值, see USER_SALT_LEN define
 * @param    [in] szPasswdHash     : admin 用户的不可逆密码(注意非原始密码), see USER_IRREVERSIBLE_PWD_LEN define
 * @note
        新的不可逆密码方案：
        1、 salt计算值的约定：
        数据类型：salt计算值由大写字母和数字组成，长度为64个字节；
        保存位置：/etc/passwd文件，以冒号‘：’为分隔符，存放于用户行中第五个字段（原有的第五个字段是对用户信息的简单说明，并没有实际使用价值）。
        2、 不可逆passwd计算值的约定：
        数据类型：passwd计算值由小写字母和数字组成，长度为64个字节；
        保存位置：/etc/shadow文件，以冒号‘：’为分隔符，存放于用户行中第二个字段（原有的第二个字段是对用户密码的加密值，格式为$id$salt$encrypt$）。
 * @return   HPR_OK: 成功； other: 失败
 */
AIP_EXTERN HPR_INT32 aip_security_set_system_passwd(const HPR_INT8 *szUserName, const HPR_INT8 *szSalt, const HPR_INT8 *szPasswdHash);

/**
 * @fn       AIP_EXTERN HPR_INT32 aip_security_user_gen_irreversible_pwd(HPR_INT8 *szUserName, HPR_INT8 *szPwd, HPR_INT8 *pbySalt, HPR_INT8 *pbyPwdIrreversible)
 * @brief    通过原始密码生成不可逆密码
 * @param    [in] szUser             : 用户名, see USER_NAME_LEN define
 * @param    [in] szPwd              : 原始密码, see USER_PWD_LEN define
 * @param    [in/out] pbySalt        : 盐值，buf需要大于64字节长, see USER_SALT_LEN define
 *                                     当需要生成获取新地salt值是，保持strlen(pbySalt)为 0
 *                                     当strlen(pbySalt)为USER_SALT_LEN时，将不更新salt，使用传参作为salt
 * @param    [out] pbyPwdIrreversible: 不可逆密码, bufsize 需要大于64字节长, see USER_IRREVERSIBLE_PWD_LEN define
 * @note     不可逆密码 格式为calc_sha256(user, salt, password)
 * @note     salt 为64位随机数大写和数字组成的字符串
 * @return   success: HPR_OK;   fail:other
 */
AIP_EXTERN HPR_INT32 aip_security_user_gen_irreversible_pwd(HPR_INT8 *szUserName, HPR_INT8 *szPwd, HPR_INT8 *pbySalt, HPR_INT8 *pbyPwdIrreversible);

/**
 * @fn       AIP_EXTERN HPR_INT32 aip_security_user_check_irreversible_pwd(HPR_INT8 *szUserName, HPR_INT8 *szPwd, HPR_INT8 *szSalt, HPR_INT8 *szPwdIrreversible)
 * @brief    验证密码是否合法
 * @param    [in]  szUserName         用户名, see USER_NAME_LEN define
 * @param    [in]  szPwd              原始密码, see USER_PWD_LEN define
 * @param    [in]  szSalt             盐值，see USER_SALT_LEN define
 * @param    [in]  szPwdIrreversible  不可逆密码, see USER_IRREVERSIBLE_PWD_LEN define
 * @return   HPR_OK: 密码校验成功;    other:密码校验失败
 * @note     see security_user_gen_irreversible_pwd
 */
AIP_EXTERN HPR_INT32 aip_security_user_check_irreversible_pwd(HPR_INT8 *szUserName, HPR_INT8 *szPwd, HPR_INT8 *szSalt, HPR_INT8 *szPwdIrreversible);

/**
 * @fn       AIP_EXTERN HPR_INT31 aip_security_user_gen_md5_pwd(HPR_INT8 *szUser, HPR_INT8 *szPwd, HPR_INT8 *pbyDigest)
 * @brief    通过原始密码生成不可逆密码 MD5摘要值
 * @param    [in]  szUser           : 用户名, see USER_NAME_LEN define
 * @param    [in]  szPwd            : 原始密码, see USER_PWD_LEN define
 * @param    [out] pbyDigest        : 不可逆MD5密码摘要值，buff至少大于32字节， see USER_MD5_PWD_LEN define
 * @note     不可逆密码 MD5摘要类型, 用于rtsp 和isapi 认证，不可逆密码格式为 MD5(username:realm:password)
 * @note     realm 为 DS-key, 其中 key为sha256(bootparam.macAddr bootparam.prodNo) 的前8位字符串
 * @return   success: HPR_OK;   fail:other
 */
AIP_EXTERN HPR_INT32 aip_security_user_gen_md5_pwd(HPR_INT8 *szUser, HPR_INT8 *szPwd, HPR_INT8 *pbyDigest);

/**
 * @fn       AIP_EXTERN HPR_INT32 aip_security_user_check_md5_pwd(HPR_INT8 *szUser, HPR_INT8 *szPwd, HPR_INT8 *szDigest)
 * @brief    通过原始密码生成不可逆密码 MD5摘要值
 * @param    [in] szUser              : 用户名
 * @param    [in] pPwd               : 原始密码
 * @param    [in] szDigest           : 不可逆MD5密码摘要值，see USER_MD5_PWD_LEN define
 * @return   HPR_OK: 密码校验成功;    other:密码校验失败
 * @note     see security_user_gen_md5_pwd
 */
AIP_EXTERN HPR_INT32 aip_security_user_check_md5_pwd(HPR_INT8 *szUser, HPR_INT8 *szPwd, HPR_INT8 *szDigest);

/**
 * @fn        AIP_EXTERN HPR_INT32 aip_security_user_gen_reaml(HPR_INT8 *pbyReaml, HPR_INT32 dwBufSize)
 * @brief     通过reaml值
 * @param     pbyReaml [out]   : REAML值
 * @param     dwBufSize [in]   : bufsize 需要大于12字节,see USER_REAML_LEN define
 * @return    success: HPR_OK;   fail:other
 * @note      realm 为 DS-key, 其中 key为sha256(bootparam.macAddr bootparam.prodNo) 的前8位字符串
 */
AIP_EXTERN HPR_INT32 aip_security_user_gen_reaml(HPR_INT8 *pbyReaml, HPR_INT32 dwBufSize);

/**
 * @fn        AIP_EXTERN HPR_INT32 aip_security_user_check_pwd_level(HPR_INT8 *pbyUser,HPR_INT8 *pbyPwd,SECURITY_RISKPWD_E* peRiskReason)
 * @brief     校验密码的安全等级
 * @param     [in] pbyUser             : 用户名，若校验的密码是用户口令时，用户名必须要填，其余譬如超级码等校验，则无需传用户名
 * @param     [in] pPwd                : 原始密码
 * @param     [out] peRiskReason       : 风险口令细化原因
 * @return    密码安全等级 SECURITY_PWD_LEVEL_E
 * @note      
 */
AIP_EXTERN SECURITY_PWD_LEVEL_E aip_security_user_check_pwd_level(HPR_INT8 *pbyUser,HPR_INT8 *pbyPwd,SECURITY_RISKPWD_E* peRiskReason);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //__AIP_SECURITY_USER_UTILS_H__ end

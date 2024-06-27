#ifndef _BSP_HASH_H
#define _BSP_HASH_H

/*******************************************************************************
 * Function      : bsp_create_key_for_digicap
 * Description   : 创建digicap升级包加密密钥，密钥长度256bit。
 * Parameter
 * Input         : @random:           随机数(4bytes)
 * Output        : @key256:           加密密钥(32bytes)
 * Return        : 0                  成功
 *               ：其他               失败
 *******************************************************************************/
int bsp_create_key_for_digicap(unsigned char random[4], unsigned char key256[32]);

#endif  /* _BSP_HASH_H */


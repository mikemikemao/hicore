#ifndef _M1_SECURE_H
#define _M1_SECURE_H

/*******************************************************************************
* Function      : m1_auth_key
* Description   : 这个函数是通过M1卡的UID和扇区号生成扇区对应的认证密钥，
*                 用于扇区加密或者认证。
* Input         : @UID:         M1卡的UID值(4bytes)
                  @sector:      M1卡的扇区号(1byte)
* Output        : @key:         M1卡的扇区的认证密钥
* Return        : 0				成功
*               ：-1            失败
*******************************************************************************/
int m1_auth_key(const unsigned char UID[4], unsigned char sector, unsigned char key[6]);

#endif	/* _M1_SECURE_H */

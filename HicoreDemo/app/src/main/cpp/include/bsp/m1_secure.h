#ifndef _M1_SECURE_H
#define _M1_SECURE_H

/*******************************************************************************
* Function      : m1_auth_key
* Description   : ���������ͨ��M1����UID������������������Ӧ����֤��Կ��
*                 �����������ܻ�����֤��
* Input         : @UID:         M1����UIDֵ(4bytes)
                  @sector:      M1����������(1byte)
* Output        : @key:         M1������������֤��Կ
* Return        : 0				�ɹ�
*               ��-1            ʧ��
*******************************************************************************/
int m1_auth_key(const unsigned char UID[4], unsigned char sector, unsigned char key[6]);

#endif	/* _M1_SECURE_H */

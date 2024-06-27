#ifndef _BSP_DATA_ENCRYPT_
#define _BSP_DATA_ENCRYPT_

enum {
	BSP_ALG_AES128_ECB = 0x0, // 目前只支持AES128-ECB
	BSP_ALG_AES128_CBC = 0x1,
	BSP_ALG_AES128_CFB = 0x2,
	BSP_ALG_AES128_OFB = 0x3,
	BSP_ALG_AES128_CCM = 0x4,
	BSP_ALG_AES128_GCM = 0x5,
}; // 算法类型枚举

int bsp_key_encrypt(const char in_buf[16], char out_key[16]);

int bsp_data_encrypt(const char in_key[16], const char *in_data, char *out_cipher, 
	int data_len, int alg_type);

int bsp_data_decrypt(const char in_key[16], const char *in_cipher, char *out_data, 
	int data_len, int alg_type);

#endif

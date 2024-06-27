#ifndef _HIK_RSA_VERIFY_
#define _HIK_RSA_VERIFY_
int do_hik_rsa_verify(unsigned char hash[32], unsigned char *key,unsigned int key_length);
int do_hik_rsa_decrypt(unsigned char *public_key, int public_key_len,
		                       const unsigned char *input,
		                       unsigned char *output,
		                       int output_max_len);
#endif
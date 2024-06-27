/**
 *  \file util_encrypt.h
 *  \note HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 *  \brief encrypt module interface
 *  \author lvmc
 *  \date  2010-07-20
 *  \note Modify history:
  * \note add function util_hamc_encrypt() 2010-07-22\n
 *  \note creat
 *  \note V0.0.2 first release
**/


#ifndef _HIK_ENCRYPT_H_
#define _HIK_ENCRYPT_H_

#ifdef __cplusplus
extern "C"
{
#endif  /* __cplusplus */

/* modified for oSIP: GCC supports this feature */
#define PROTOTYPES 1

#ifndef PROTOTYPES
#define PROTOTYPES 0
#endif

/*
 *---------------util_MD5 functions-----------------
 */
/**
 * Structure for holding util_MD5 context.
 * @var util_MD5_CTX
 */
typedef struct  _util_MD5_CTX_
{
    unsigned int state[4];             /* state (ABCD) */
    unsigned int count[2];             /* number of bits, modulo 2^64 (lsb first) */
    unsigned char buffer[64];          /* input buffer */
} util_MD5_CTX;

/* 哈希算法枚举 */
typedef enum
{
    ENCRYPT_HMAC_SHA1 = 1,   // SHA-1
    ENCRYPT_HMAC_SHA256 = 2, // SHA-256
} ENCRYPT_HASH_TYPE_E;

/**
 * Function:    util_hamc_encrypt \n
 * Description: encrypt the data with HMAC\n
 *
 * \param[in]  *in  -input string
 * \param[in]  in_len   -bytes of input string
 * \param[in] *key -the key string of encrypt
 * \param[in] key_len -bytes of key string
 * \param[out] key_len -the target output string after encrypt
 * \return  N/A
 */
void hamc_encrypt(unsigned char *in, int in_len, unsigned char *key, int key_len, unsigned char *digest);

/**
 * Function:    util_MD5_string \n
 * Description: encrypt data with md5 \n
 *
 * \param[in]  *in  -input string
 * \param[in]  in_len   -bytes of input string
 * \param[out] *out -output string
 * \return  N/A
 */
extern void util_MD5_string(unsigned char *in, int in_len, unsigned char *out);

/*******************************************************************************
 *         Name: util_MD5toStr 
 *  Description: 将util_MD5加密后的数据转换成可打印的字符串 
 * 
 *       Mode   Type                Name         Description
 * -----------------------------------------------------------------------------
 *        in:   unsigned char *     src         输入数据，为util_MD5加密后的结果
 *              int                 len         输入数据长度
 *    in-out:  
 *       out:   char *              out         转换后的数据
 *    return:   void
 * -----------------------------------------------------------------------------
 *    Author: xmq
 *   Created: 01/08/2008 01 CST
 *  Revision: none
 ******************************************************************************/
extern void util_MD5toStr(unsigned char *src,int len,char *out);

/**
 * Function:    util_string_to_print \n
 * Description: print the string after encrypt by md5 \n
 *
 * \param[in]  *src -input string
 * \param[in]  len  -bytes of input string
 * \param[out] *out -output string
 * \return  N/A
 */
extern void string_to_print(unsigned char *src, int len, char *out);

/**
 * Function:    util_MD5_init \n
 * Description: util_MD5 initialization. Begins an util_MD5 operation, writing a new context. \n
 *
 * \param[in]  *context -object to initialization
 * \param[out] N/A
 * \return  N/A
 */
extern void util_MD5_init(util_MD5_CTX *context);

/**
 * Function:    util_MD5_update \n
 * Description: util_MD5 block update operation. Continues an util_MD5 message-digest \n
                operation, processing another message block, and updating the \n
                context. \n
 *
 * \param[in]  *input -input string
 * \param[in]  inputLen -length of input string 
 * \param[out] *context -output data after update
 * \return  N/A
 */
extern void util_MD5_update(util_MD5_CTX *context, unsigned char *input, unsigned int inputLen);

/**
 * Function:    util_MD5_final \n
 * Description: util_MD5 finalization. Ends an util_MD5 message-digest operation, \n
                writing the message digest and zeroizing the context.\n
 *
 * \param[in]  *context -input data after update
 * \param[out] digest[16] -output data after encrypt by md5
 * \return  N/A
 */
extern void util_MD5_final(unsigned char digest[16], util_MD5_CTX *context);

/*
 *---------------base64 functions-----------------
 */

/**
 * Function:    util_base64_encode \n
 * Description: BASE64加密算法实现\n
 *
 * \param[in]  in_str    -input string
 * \param[in]  in_len    -bytes of input string

 * \param[out] out_str -  Caller-allocated buffer to receive the encoded data
 * \return    length in characters of out_str
 */
int util_base64_encode(const char *in_str, int in_len, char *out_str);



 /**
 * Function:    util_base64_decode \n
 * Description: BASE64解码算法\n
 *
 * \param[in]  in_str    -input string
 * \param[in]  in_len    -bytes of input string

 * \param[out] out_str -  Caller-allocated buffer to receive the decoded data
 * \return    length in characters of out_str
 */
 
int util_base64_decode(const char *in_str, int in_len, char *out_str);

/*
 *---------------des encrypt functions-----------------
 */

#define D2_DES        /* include double-length support */
#define D3_DES        /* include triple-length support */

#ifdef D3_DES
#ifndef D2_DES
#define D2_DES        /* D2_DES is needed for D3_DES */
#endif
#endif

#define EN0    0    /* MODE == encrypt */
#define DE1    1    /* MODE == decrypt */

/* A useful alias on 68000-ish machines, but NOT USED HERE. */

typedef union {
    unsigned long blok[2];
    unsigned short word[4];
    unsigned char byte[8];
} M68K;

extern void d3deskey(unsigned char *, short);
/*              hexkey[8]     MODE
 * Sets the internal key register according to the hexadecimal
 * key contained in the 8 bytes of hexkey, according to the DES,
 * for encryption or decryption according to MODE.
 */

extern void usekey(unsigned long *);
/*            cookedkey[32]
 * Loads the internal key register with the data in cookedkey.
 */

extern void cpkey(unsigned long *);
/*           cookedkey[32]
 * Copies the contents of the internal key register into the storage
 * located at &cookedkey[0].
 */

extern void des(unsigned char *, unsigned char *);
/*            from[8]          to[8]
 * Encrypts/Decrypts (according to the key currently loaded in the
 * internal key register) one block of eight bytes at address 'from'
 * into the block at address 'to'.  They can be the same.
 */

#ifdef D2_DES

#define desDkey(a,b)    des2key((a),(b))
extern void des2key(unsigned char *, short);
/*              hexkey[16]     MODE
 * Sets the internal key registerS according to the hexadecimal
 * keyS contained in the 16 bytes of hexkey, according to the DES,
 * for DOUBLE encryption or decryption according to MODE.
 * NOTE: this clobbers all three key registers!
 */

extern void Ddes(unsigned char *, unsigned char *);
/*            from[8]          to[8]
 * Encrypts/Decrypts (according to the keyS currently loaded in the
 * internal key registerS) one block of eight bytes at address 'from'
 * into the block at address 'to'.  They can be the same.
 */

extern void D2des(unsigned char *, unsigned char *);
/*            from[16]          to[16]
 * Encrypts/Decrypts (according to the keyS currently loaded in the
 * internal key registerS) one block of SIXTEEN bytes at address 'from'
 * into the block at address 'to'.  They can be the same.
 */

extern void makekey(char *, unsigned char *);
/*        *password,    single-length key[8]
 * With a double-length default key, this routine hashes a NULL-terminated
 * string into an eight-byte random-looking key, suitable for use with the
 * d3deskey() routine.
 */

#define makeDkey(a,b)    make2key((a),(b))
extern void make2key(char *, unsigned char *);
/*        *password,    double-length key[16]
 * With a double-length default key, this routine hashes a NULL-terminated
 * string into a sixteen-byte random-looking key, suitable for use with the
 * des2key() routine.
 */

#ifndef D3_DES    /* D2_DES only */

#define useDkey(a)    use2key((a))
#define cpDkey(a)    cp2key((a))

extern void use2key(unsigned long *);
/*            cookedkey[64]
 * Loads the internal key registerS with the data in cookedkey.
 * NOTE: this clobbers all three key registers!
 */

extern void cp2key(unsigned long *);
/*           cookedkey[64]
 * Copies the contents of the internal key registerS into the storage
 * located at &cookedkey[0].
 */

#else    /* D3_DES too */

#define useDkey(a)    use3key((a))
#define cpDkey(a)    cp3key((a))

extern void des3key(unsigned char *, short);
/*              hexkey[24]     MODE
 * Sets the internal key registerS according to the hexadecimal
 * keyS contained in the 24 bytes of hexkey, according to the DES,
 * for DOUBLE encryption or decryption according to MODE.
 */

extern void use3key(unsigned long *);
/*            cookedkey[96]
 * Loads the 3 internal key registerS with the data in cookedkey.
 */

extern void cp3key(unsigned long *);
/*           cookedkey[96]
 * Copies the contents of the 3 internal key registerS into the storage
 * located at &cookedkey[0].
 */

extern void make3key(char *, unsigned char *);
/*        *password,    triple-length key[24]
 * With a triple-length default key, this routine hashes a NULL-terminated
 * string into a twenty-four-byte random-looking key, suitable for use with
 * the des3key() routine.
 */

#endif    /* D3_DES */
#endif    /* D2_DES */

typedef struct
{
    unsigned long total[2];     /*!< number of bytes processed  */
    unsigned long state[5];     /*!< intermediate digest state  */
    unsigned char buffer[64];   /*!< data block being processed */

    unsigned char ipad[64];     /*!< HMAC: inner padding        */
    unsigned char opad[64];     /*!< HMAC: outer padding        */
}sha1_context;

/**
 * \brief          SHA-1 context setup
 *
 * \param ctx      context to be initialized
 */
void sha1_starts( sha1_context *ctx );

/**
 * \brief          SHA-1 process buffer
 *
 * \param ctx      SHA-1 context
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 */
void sha1_update( sha1_context *ctx, const unsigned char *input, int ilen );

/**
 * \brief          SHA-1 final digest
 *
 * \param ctx      SHA-1 context
 * \param output   SHA-1 checksum result
 */
void sha1_finish( sha1_context *ctx, unsigned char output[20] );

/**
 * \brief          Output = SHA-1( input buffer )
 *
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 * \param output   SHA-1 checksum result
 */
void sha1( const unsigned char *input, int ilen, unsigned char output[20] );

/**
 * \brief          Output = SHA-1( file contents )
 *
 * \param path     input file name
 * \param output   SHA-1 checksum result
 *
 * \return         0 if successful, 1 if fopen failed,
 *                 or 2 if fread failed
 */
int sha1_file( const char *path, unsigned char output[20] );

/**
 * \brief          SHA-1 HMAC context setup
 *
 * \param ctx      HMAC context to be initialized
 * \param key      HMAC secret key
 * \param keylen   length of the HMAC key
 */
void sha1_hmac_starts( sha1_context *ctx, const unsigned char *key, int keylen );

/**
 * \brief          SHA-1 HMAC process buffer
 *
 * \param ctx      HMAC context
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 */
void sha1_hmac_update( sha1_context *ctx, const unsigned char *input, int ilen );

/**
 * \brief          SHA-1 HMAC final digest
 *
 * \param ctx      HMAC context
 * \param output   SHA-1 HMAC checksum result
 */
void sha1_hmac_finish( sha1_context *ctx, unsigned char output[20] );

/**
 * \brief          SHA-1 HMAC context reset
 *
 * \param ctx      HMAC context to be reset
 */
void sha1_hmac_reset( sha1_context *ctx );

/**
 * \brief          Output = HMAC-SHA-1( hmac key, input buffer )
 *
 * \param key      HMAC secret key
 * \param keylen   length of the HMAC key
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 * \param output   HMAC-SHA-1 result
 */
void sha1_hmac( const unsigned char *key, int keylen,
                const unsigned char *input, int ilen,
                unsigned char output[20] );

/**
 * \brief          Checkup routine
 *
 * \return         0 if successful, or 1 if the test failed
 */
int sha1_self_test( int verbose );

int base64_encode_custom(const char *in_str, int in_len, char *out_str);

int base64_decode_custom(const char *in_str, int in_len, char *out_str);

void simpleEncrypt(char * dataBuf, unsigned int dataLen);

/**
 * @fn     util_encrypt_HMAC
 * @brief  使用哈希算法加密字符
 * @param  enHashType   加密使用的哈希算法类型，SHA-1 SHA-256
 * @param  pbyInput     输入，加密前的字符串指针，明文
 * @param  dwInputLen   输入的字符长度长度不包含“\0”
 * @param  pSalt     盐值
 * @param  dwSaltlen 盐值长度
 * @param  dwIter  迭代次数
 * @param  pbyOutput    加密后的密文保存地址，由接口调用方申请和释放
 * @param  dwOutputSize 密文缓冲区大小，需要大于相应的哈希算法散列之后的密文长度
 * @return HPR_OK/HPR_ERROR
 **/
int util_encrypt_HMAC(ENCRYPT_HASH_TYPE_E enHashType, const char* pbyInput, int dwInputLen, const unsigned char* pSalt, int dwSaltlen, int dwIter, unsigned char* pbyOutput, int dwOutputLen);
#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* _HIK_ENCRYPT_H_ */



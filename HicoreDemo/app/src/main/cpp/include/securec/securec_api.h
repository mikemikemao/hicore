/******************************************************************************
  @note HangZhou Hikvision Digital Technology Co., Ltd. All Right Reserved.
 ******************************************************************************
  @file : securec_api.h
  @brief : Security Functions  Headers
  @author : ccy
  @date : 2021/11/5
  @note : Create
******************************************************************************/

#ifndef _HIK_SAFE_H_
#define _HIK_SAFE_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */
 
 /*----------------------------------------------*
 * Included Header                              *
 *----------------------------------------------*/
 
#ifdef __KERNEL__

/* linux kernel environment */
#include <linux/stddef.h>
#include <linux/types.h>
#include <linux/errno.h>

#else

#include <stdio.h>
#include <sys/types.h>
#include <inttypes.h>
#include <stdint.h>
#include <errno.h>
#include <stdbool.h>

#endif /* __KERNEL__ */

#include "securec_api_macro.h"

/*----------------------------------------------*
 * Macros                                       *
 *----------------------------------------------*/
 
/* maximum sring length */
#define RSIZE_MAX_STR      ( 5120UL << 10 )      /* 1024KB */

/* error code value definition */
#ifndef ESNULLP
#define ESNULLP EINVAL
#endif

#ifndef ESLEMAX
#define ESLEMAX ERANGE_AND_RESET 
#endif

#ifndef ESZEROL
#define ESZEROL ERANGE
#endif

#ifndef ESOVRLP
#define ESOVRLP EOVERLAP_AND_RESET
#endif

#ifndef ESNOTFND
#define ESNOTFND        ( 409 )       /* not found                   */
#endif

#ifndef ESNODIFF
#define ESNODIFF        ( 408 )       /* no difference               */
#endif

#ifndef ESUNTERM
#define ESUNTERM        ( 407 )       /* unterminated string         */
#endif

#ifndef EOK
#define EOK 0
#endif

/*----------------------------------------------*
 * Type Definition                              *
 *----------------------------------------------*/
#ifdef SAFEFUNC_SNPRINTF_TRUNCATED
#define SECUREC_SNPRINTF_TRUNCATED SAFEFUNC_SNPRINTF_TRUNCATED
#else
#define SECUREC_SNPRINTF_TRUNCATED 0
#endif

typedef enum
{
    SAFE_PL_ERR     = 0,        // ERR
    SAFE_PL_INFO    = 1,        // INFO
    SAFE_PL_HINT    = 2,        // HINT
}SAFE_PRINT_LEVEL;


/*----------------------------------------------*
 * Function Header                              *
 *----------------------------------------------*/
 
/** @fn : strzero_sec
  * @brief :  
  *    Nulls dmax characters of dest.  This function can be used
  *    to clear strings that contained sensitive data.
  * @param [IN] dest : pointer to string that will be nulled.
  * @param [IN] dmax : restricted maximum length of dest
  * @param [OUT] dest : updated string
  * @return : 
  *    EOK        successful operation
  *    ESNULLP    NULL pointer
  *    ESZEROL    zero length
  *    ESLEMAX    length exceeds max limit
*/
SECUREC_API
errno_t strzero_sec (char *dest, size_t dmax);

/** @fn : memcmp_sec
  * @brief :  Compares memory until they differ, and their difference is
  *    returned in diff.  If the block of memory is the same, diff=0.
  * @param [IN] dest : pointer to memory to compare against
  * @param [IN] dmax : maximum length of dest, in bytess
  * @param [IN] src : pointer to the source memory to compare with dest
  * @param [IN] smax : length of the source memory block
  * @param [OUT] *diff : pointer to the diff which is an integer greater
  *              than, equal to or less than zero according to
  *              whether the object pointed to by dest is
  *              greater than, equal to or less than the object
  *              pointed to by src.
  * @notice      smax must large than dmax
  * @return : 
  *    EOK        successful operation
  *    ESNULLP    NULL pointer
  *    ESZEROL    zero length
  *    ESLEMAX    length exceeds max limit
*/

errno_t memcmp_sec (const void *dest, size_t dmax, const void *src,  size_t smax, int *diff);

/** @fn : memcmp_sec
  * @brief :  Compares memory until they differ, and their difference is
  *    returned in diff.  If the block of memory is the same, diff=0.
  * @param [IN] dest : pointer to memory to compare against
  * @param [IN] dmax : maximum length of dest, in bytess
  * @param [IN] src : pointer to the source memory to compare with dest
  * @param [IN] smax : maximum length of src, in bytess
  * @param [IN] count : length of the compare memory block
  * @param [OUT] *diff : pointer to the diff which is an integer greater
  *              than, equal to or less than zero according to
  *              whether the object pointed to by dest is
  *              greater than, equal to or less than the object
  *              pointed to by src.
  * @notice      smax must large than dmax
  * @return : 
  *    EOK        successful operation
  *    ESNULLP    NULL pointer
  *    ESZEROL    zero length
  *    ESLEMAX    length exceeds max limit
*/
SECUREC_API
errno_t memcmp_sec_ex (const void *dest, size_t dmax, const void *src,  size_t smax, size_t count, int *diff);

/** @fn : memzero_sec
  * @brief :  
  *    Zeros len bytes starting at dest.
  * @param [IN] dest : pointer to memory to be zeroed.
  * @param [IN] len : number of bytes to be zeroed
  * @param [OUT] dest : is updated
  * @return : 
  *    EOK        successful operation
  *    ESNULLP    NULL pointer
  *    ESZEROL    zero length
  *    ESLEMAX    length exceeds max limit
*/
SECUREC_API
errno_t memzero_sec (void *dest, size_t len);

/** @fn : strcasecmp_sec
  * @brief :  
  *    Case insensitive string comparison by converting
  *    to uppercase prior to the compare.
  * @param [IN] dest : pointer to string to compare against
  * @param [IN] dmax : restricted maximum length of string dest
  * @param [IN] src :  pointer to the string to be compared to dest
  * @param [IN] indicator :  pointer to result indicator, greater than 0,
  *               equal to 0 or less than 0, if the string pointed
  *               to by dest is greater than, equal to or less
  *               than the string pointed to by src respectively.
  * @param [OUT] none
  * @return : 
  *    EOK          comparison complete
  *    ESNULLP      pointer was null
  *    ESZEROL      length was zero
  *    ESLEMAX      length exceeded max
*/
SECUREC_API
errno_t strcasecmp_sec (const char *dest, size_t dmax, const char *src, int *indicator);

/** @fn : strcasestr_sec
  * @brief :  
  *    The strcasestr_sec() function locates the first occurrence of
  *    the substring pointed to by src which would be located in
  *    the string pointed to by dest.  The comparison is case
  *    insensitive.
  * @param [IN] dest : pointer to string to be searched for the substring
  * @param [IN] dmax : restricted maximum length of dest string
  * @param [IN] src :  pointer to the sub string
  * @param [IN] slen :  maximum length of src string
  * @param [IN] substring :  returned pointer to the substring
  * @param [OUT] substring : pointer to the substring
  * @return : 
  *    EOK        successful operation, substring found.
  *    ESNULLP    NULL pointer
  *    ESZEROL    zero length
  *    ESLEMAX    length exceeds max limit
  *    ESNOTFND   substring not found
*/
SECUREC_API
errno_t strcasestr_sec (char *dest, size_t dmax, const char *src, size_t slen, char **substring);

/** @fn : strcmp_sec
  * @brief :  
  *    Compares string src to string dest.
  * @param [IN] dest : pointer to string to compare against
  * @param [IN] dmax : restricted maximum length of string dest
  * @param [IN] src :  pointer to the string to be compared to dest
  * @param [IN] indicator :  pointer to result indicator, greater than,
  *               equal to or less than 0, if the string pointed
  *               to by dest is greater than, equal to or less
  *               than the string pointed to by src respectively.
  * @param [OUT] indicator : updated result indicator
  * @return : 
  *    EOK
  *    ESNULLP     pointer was null
  *    ESZEROL     length was zero
  *    ESLEMAX     length exceeded max
*/
SECUREC_API
errno_t strcmp_sec (const char *dest, size_t dmax, const char *src, int *indicator);

/** @fn : strcpyfld_sec
  * @brief :  
  *    Compares the character array pointed to by src to the character array
  *    pointed to by dest for dmax characters.  The null terminator does not
  *    stop the comparison.
  * @param [IN] dest : pointer to character array to compare against
  * @param [IN] dmax : restricted maximum length of dest.  The length is
  *                used for the comparison of src against dest.
  * @param [IN] src :  pointer to the character array to be compared to dest
  * @param [IN] indicator :  pointer to result indicator, greater than, equal
  *               to or less than 0, if the character array pointed
  *                to by dest is greater than, equal to or less
  *                than the character array pointed to by src.
  * @param [OUT] indicator : updated result indicator
  * @return : 
  *    EOK
  *    ESNULLP     pointer was null
  *    ESZEROL     length was zero
  *    ESLEMAX     length exceeded max
*/
SECUREC_API
errno_t strcmpfld_sec (const char *dest, size_t dmax, const char *src, int *indicator);

/** @fn : strcpyfld_sec
  * @brief :  
  *    The strcpyfld_sec function copies slen characters from the character
  *    array pointed to by src into the character array pointed to by dest.
  *    The copy operation does not stop on the null character as the
  *    function copies slen characters.
  * @param [IN] dest : pointer to string that will be replaced by src.
  * @param [IN] dmax : restricted maximum length of dest
  * @param [IN] src :  pointer to the character array that will be copied
  *              to dest
  * @param [IN] slen :  maximum length of src
  * @param [OUT] dest : updated
  * @return : 
  *    EOK        successful operation
  *    ESNULLP    NULL pointer
  *    ESZEROL    zero length
  *    ESLEMAX    length exceeds max limit
  *    ESOVRLP    strings overlap
*/ 
SECUREC_API
errno_t strcpyfld_sec (char *dest, size_t dmax, const char *src, size_t slen);

/** @fn : strcpyfldin_sec
  * @brief :  
  *    The strcpyfldin_sec function copies at most slen characters from the
  *    null terminated string pointed to by src into the fixed character
  *    array pointed to by dest. The copy operation stops on the  null
  *    character if encountered and then continues to fill the field
  *    with nulls up to dmax characters.
  * @param [IN] dest : pointer to string that will be replaced by src.
  * @param [IN] dmax : restricted maximum length of dest
  * @param [IN] src :  pointer to the null terminated string that will be copied
  *               into the character array pointed to by dest
  * @param [IN] slen :  length of source
  * @param [OUT] dest : updated
  * @return : 
  *    EOK        successful operation
  *    ESNULLP    NULL pointer
  *    ESZEROL    zero length
  *    ESLEMAX    length exceeds max limit
  *    ESOVRLP    strings overlap
*/
SECUREC_API
errno_t strcpyfldin_sec (char *dest, size_t dmax, const char *src, size_t slen);

/** @fn : strcspn_sec
  * @brief :  
  *    The strcpyfldout_sec function copies slen characters from
  *    the character array pointed to by src into the string
  *    pointed to by dest. A null is included to properly
  *    termiante the dest string. The copy operation does not
  *    stop on the null character as function copies dmax
  *    characters.
  * @param [IN] dest : pointer to string that will be replaced by src.
  * @param [IN] dmax : restricted maximum length of dest
  * @param [IN] src :  pointer to the character array to be copied
  *              to dest and null terminated.
  * @param [IN] slen :  the maximum number of characters that will be
  *              copied from the src field into the dest string.
  * @param [OUT] dest : updated
  * @return : 
  *    EOK        successful operation
  *    ESNULLP    NULL pointer
  *    ESZEROL    zero length
  *    ESLEMAX    length exceeds max limit
  *    ESOVRLP    strings overlap
*/
SECUREC_API
errno_t strcpyfldout_sec (char *dest, size_t dmax, const char *src, size_t slen);

/** @fn : strcspn_sec
  * @brief :  
  *    This function computes the prefix length of the string pointed
  *    to by dest which consists entirely of characters that are
  *    excluded from the string pointed to by src. The scanning stops
  *    at the first null in dest or after dmax characters. The
  *    exclusion string is checked to the null or after slen
  *    characters.
  * @param [IN] dest : pointer to string to determine the prefix
  * @param [IN] dmax : restricted maximum length of string dest
  * @param [IN] src :    pointer to exclusion string
  * @param [IN] slen :  restricted maximum length of string src
  * @param [IN] count :  pointer to a count variable that will be updated
  *              with the dest substring length
  * @param [OUT] count : pointer to a count variable that will be updated
  *              with the dest substring length
  * @return : 
  *    EOK         count
  *    ESNULLP     NULL pointer
  *    ESZEROL     zero length
  *    ESLEMAX     length exceeds max limit
*/
SECUREC_API
errno_t strcspn_sec (const char *dest, size_t dmax, const char *src,  size_t slen, size_t *count);
 
/** @fn : strfirstchar_sec
  * @brief :  
  *    This function returns a pointer to the first occurrence
  *    of character c in dest. The scanning stops at the first null
  *    or after dmax characters.
  * @param [IN] dest : pointer to string to compare against
  * @param [IN] dmax : restricted maximum length of string
  * @param [IN] c :    character to locate
  * @param [IN] first :  returned pointer to first occurrence of c
  * @param [OUT] first : updated pointer to first occurrence of c
  * @return : 
  *    EOK         pointer to first occurrence is returned
  *    ESNULLP     NULL pointer
  *    ESZEROL     zero length
  *    ESLEMAX     length exceeds max limit
*/
SECUREC_API
errno_t strfirstchar_sec (char *dest, size_t dmax, char c, char **first);

/** @fn : strfirstdiff_sec
  * @brief :  
  *    Returns the index of the first character that is different
  *    between dest and src. Index is valid only for OK.
  *    The scanning stops at the first null in dest or src, or
  *    after dmax characters.
  * @param [IN] dest : pointer to string to compare against
  * @param [IN] dmax : restricted maximum length of string dest
  * @param [IN] src : pointer to the string to be compared to dest
  * @param [IN] index : pointer to returned index to first difference
  * @param [OUT] index : returned index to first difference
  * @return : 
  *    EOK         index to first diff is returned
  *    ESNODIFF    no difference
  *    ESNULLP     NULL pointer
  *    ESZEROL     zero length
  *    ESLEMAX     length exceeds max limit
*/
SECUREC_API
errno_t  strfirstdiff_sec (const char *dest, size_t dmax, const char *src, size_t *index);

/** @fn : strfirstsame_sec
  * @brief :  
  *    Returns the index of the first character that is the
  *    same between dest and src.  The scanning stops at the
  *    fisrt null in dest or src, or after dmax characters.
  * @param [IN] dest : pointer to string to compare against
  * @param [IN] dmax : restricted maximum length of string dest
  * @param [IN] src : pointer to the string to be compared to dest
  * @param [IN] index : pointer to returned index
  * @param [OUT] index : updated index
  * @return : 
  *    EOK         index to first same char is returned
  *    ESNULLP     NULL pointer
  *    ESZEROL     zero length
  *    ESLEMAX     length exceeds max limit
  *    ESNOTFND    not found
*/
SECUREC_API
errno_t strfirstsame_sec (const char *dest, size_t dmax, const char *src,  size_t *index);

/** @fn : strisalphanumeric_sec
  * @brief :  
  *    This function checks if the entire string contains
  *    alphanumerics.  The scanning stops at the first null
  *    or after dmax characters.
  * @param [IN] dest : pointer to string
  * @param [IN] dmax : restricted maximum length
  * @param [OUT] none
  * @return : 
  *    true      dest is alphanumeric
  *    false     dest is not alphanumeric or an error occurred
*/
SECUREC_API
bool strisalphanumeric_sec (const char *dest, size_t dmax);

/** @fn : strisascii_sec
  * @brief :  
  *    This function checks if the entire string contains ascii
  *    characters.  The scanning stops at the first null or
  *    at most dmax characters.
  * @param [IN] dest : pointer to string
  * @param [IN] dmax : maximum length of string
  * @param [OUT] none
  * @return : 
  *    true, string is ascii
  *    false, string contains one or more non-ascii or an error occurred
*/
SECUREC_API
bool strisascii_sec (const char *dest, size_t dmax);

/** @fn : strisdigit_sec
  * @brief :  
  *    This function checks that the entire string contains digits.
  *    The scanning stops at the first null or after dmax characters.
  * @param [IN] dest : pointer to string
  * @param [IN] dmax : maximum length of string
  * @param [OUT] none
  * @return : 
  *    true      string is digit
  *    false     string is not digit or an error occurred
*/
SECUREC_API
bool strisdigit_sec (const char *dest, size_t dmax);

/** @fn : strishex_sec
  * @brief :  
  *    This function checks that the entire string contains
  *    hex characters.  The scanning stops at the first null
  *    or after dmax characters.
  * @param [IN] dest : pointer to string
  * @param [IN] dmax : maximum length of string
  * @param [OUT] none
  * @return : 
  *    true      string is hex
  *    false     string is not hex or an error occurred
*/
SECUREC_API
bool strishex_sec (const char *dest, size_t dmax);

/** @fn : strislowercase_sec
  * @brief :  
  *    This function checks if entire string is lowercase.
  *    The scanning stops at the first null or after dmax
  *    characters.
  * @param [IN] dest : pointer to string
  * @param [IN] dmax : maximum length of string
  * @param [OUT] none
  * @return : 
  *    true      string is lowercase
  *    false     string is not lowercase or an error occurred
*/
SECUREC_API
bool strislowercase_sec (const char *dest, size_t dmax);

/** @fn : strismixedcase_sec
  * @brief :  
  *    This function checks that the entire string is mixed
  *    case.  The scanning stops at the first null or after
  *    dmax characters.
  * @param [IN] dest : pointer to string
  * @param [IN] dmax : maximum length of string
  * @param [OUT] none
  * @return : 
  *    true       string is mixed case
  *    false      string is not mixed case or error
*/
SECUREC_API
bool strismixedcase_sec (const char *dest, size_t dmax);

/**
 * NAME
 *    strispassword_sec
 *
 * SYNOPSIS
 *    #include "strlib.h"
 *    bool
 *    strispassword_sec(const char *dest, rsize_t dmax)
 *
 * DESCRIPTION
 *    This function validates the make-up of a password string.
 *    -SAFE_STR_PASSWORD_MIN_LENGTH character minimum
 *    -SAFE_STR_PASSWORD_MAX_LENGTH character maximum
 *    -at least SAFE_STR_MIN_LOWERCASE lower case characters
 *    -at least SAFE_STR_MIN_UPPERCASE upper case characters
 *    -at least SAFE_STR_MIN_NUMBERS number
 *    -at least SAFE_STR_MIN_SPECIALS special
 *
 * EXTENSION TO
 *    ISO/IEC TR 24731, Programming languages, environments
 *    and system software interfaces, Extensions to the C Library,
 *    Part I: Bounds-checking interfaces
 *
 * INPUT PARAMETERS
 *    dest       pointer to string
 *
 *    dmax       length of password string
 *
 * OUTPUT PARAMETERS
 *    none
 *
 * RUNTIME CONSTRAINTS
 *    dest shall not be a null pointer.
 *    length > SAFE_STR_PASSWORD_MIN_LENGTH
 *    length < SAFE_STR_PASSWORD_MAX_LENGTH
 *    dest shall not be unterminated
 *
 * RETURN VALUE
 *    true, string has valid password makeup
 *    false, string does not meet requirements or an error occurred
 *
 * ALSO SEE
 *    strzero_s()
 *
 */
SECUREC_API
bool strispassword_sec (const char *dest, size_t dmax);

/** @fn : strisuppercase_sec
  * @brief :  
  *    This function checks if entire string is uppercase
  *    The scanning stops at the first null or after dmax
  *    characters.
  * @param [IN] dest : pointer to string
  * @param [IN] dmax : maximum length of string
  * @param [OUT] none
  * @return : 
  *    true      string is uppercase
  *    false     string is not uppercase or an error occurred
*/
SECUREC_API
bool strisuppercase_sec (const char *dest, size_t dmax);

/** @fn : strlastchar_sec
  * @brief :  
  *    Returns a pointer to the last occurrence of character c in
  *    dest.  The scanning stops at the first null or after dmax
  *    characters.
  * @param [IN] dest : pointer to string
  * @param [IN] dmax : restricted maximum length of string
  * @param [IN] c : character to locate
  * @param [IN] last : returned pointer to last occurrence
  * @param [OUT] last : updated pointer to last occurrence
  * @return : 
  *    pointer to the last occurrence, when the return code is OK
  *
  *    EOK         pointer to the last occurence is returned
  *    ESNOTFND    c not found in dest
  *    ESNULLP     NULL pointer
  *    ESZEROL     zero length
  *    ESLEMAX     length exceeds max limit
*/
SECUREC_API
errno_t strlastchar_sec(char *dest, size_t dmax, char c, char **last);

/** @fn : strlastdiff_sec
  * @brief :  
  *    Returns the index of the last character that is different
  *    between dest and src.  Index is valid only for EOK.
  *    The scanning stops at the first null in dest or src, or
  *    after dmax characters.
  * @param [IN] dest : pointer to string to compare against
  * @param [IN] dmax : rrestricted maximum length of string dest
  * @param [IN] src : pointer to the string to be compared to dest
  * @param [IN] index : pointer to returned index of last difference
  * @param [OUT] index : updated index of last difference
  * @return : 
  *    index to last difference, when the return code is OK
  *    EOK         index to last diff is returned
  *    ESNODIFF    no difference
  *    ESNULLP     NULL pointer
  *    ESZEROL     zero length
  *    ESLEMAX     length exceeds max limit
*/
SECUREC_API
errno_t strlastdiff_sec(const char *dest, size_t dmax, const char *src, size_t *index);

/** @fn : strlastsame_sec
  * @brief :  
  *    Returns the index of the last character that is the
  *    same between dest and src. The scanning stops at the
  *    first nul in dest or src, or after dmax characters.
  * @param [IN] dest : pointer to string to compare against
  * @param [IN] dmax : rrestricted maximum length of string dest
  * @param [IN] src : pointer to the string to be compared to dest
  * @param [IN] index : pointer to returned index
  * @param [OUT] index : pointer to returned index
  * @return : 
  *    EOK         index to last same char is returned
  *    ESNULLP     NULL pointer
  *    ESZEROL     zero length
  *    ESLEMAX     length exceeds max limit
  *    ESNOTFND    not found
  *    ESUNTERM    string unterminated
*/
SECUREC_API
errno_t strlastsame_sec (const char *dest, size_t dmax, const char *src, size_t *index);

/** @fn : strljustify_sec
  * @brief :  
  *    Removes beginning whitespace from the string pointed to by
  *    dest by shifting the text left over writting the beginning
  *    whitespace, left justifying the text.  The left justified
  *    text is null terminated.
  * @param [IN] dest    pointer to string to left justify
  * @param [IN] dmax    restricted maximum length of string
  * @param [OUT] dest : left justified
  * @return : 
  *    ESNULLP     NULL pointer
  *    ESZEROL     zero length
  *    ESLEMAX     length exceeds max limit
  *    ESUNTERM    dest was not null terminated
*/
SECUREC_API
errno_t strljustify_sec (char *dest, size_t dmax);

/** @fn : strnlen_sec
  * @brief :  
  *    The strnlen_sec function computes the length of the string pointed
  *    to by dest.
  * @param [IN] dest : pointer to string
  * @param [IN] dmax : restricted maximum length
  * @param [OUT] none
  * @return : 
  *    The function returns the string length, excluding  the terminating
  *    null character.  If dest is NULL, then strnlen_sec returns 0.
  *
  *    Otherwise, the strnlen_sec function returns the number of characters
  *    that precede the terminating null character. If there is no null
  *    character in the first dmax characters of dest then strnlen_sec returns
  *    dmax. At most the first dmax characters of dest are accessed
  *    by strnlen_sec.
*/
SECUREC_API
size_t strnlen_sec (const char *dest, size_t dmax);

/** @fn : strnterminate_sec
  * @brief :  
  *    The strnterminate_sec function will terminate the string if a
  *    null is not encountered before dmax characters.
  * @param [IN] dest : pointer to string
  * @param [IN] dmax : restricted maximum length
  * @param [OUT] dest : dest is terminated if needed
  * @return : 
  *    The function returns a terminated string.  If a null is not
  *    encountered prior to dmax characters, the dmax character is
  *    set to null terminating the string. The string length is
  *    also returned.
*/
SECUREC_API
size_t strnterminate_sec (char *dest, size_t dmax);

/** @fn : strpbrk_sec
  * @brief :  
  *    Returns a pointer, first, to the first ocurrence of any character
  *    in src which is contained in dest.
  * @param [IN] dest : pointer to string
  * @param [IN] dmax : restricted maximum length of string dest
  * @param [IN] slen : restricted length of string src
  * @param [IN] src : pointer to string
  * @param [IN] first : returned pointer to first occurence
  * @param [OUT] none
  * @return : 
  *    EOK         count
  *    ESNULLP     NULL pointer
  *    ESZEROL     zero length
  *    ESLEMAX     length exceeds max limit
*/
SECUREC_API
errno_t strpbrk_sec (char *dest, size_t dmax, char *src,  size_t slen, char **first);

/** @fn : strprefix_sec
  * @brief :  
  *    Determines if the prefix pointed to by src is at the
  *    beginning of string pointed to by dest.  The prefix
  *    must be a complete match in dest.  Useful for command
  *    or user input parsing.  The scanning stops at the first
  *    null in dest or src, or after dmax characters.
  * @param [IN] dest : pointer to string to determine the prefix
  * @param [IN] dmax : restricted maximum length of string dest
  * @param [IN] src : pointer to the prefix
  * @param [OUT] none
  * @return : 
  *    EOK        successful operation, prefix present in dest
  *    ESNULLP    NULL pointer
  *    ESZEROL    zero length
  *    ESLEMAX    length exceeds max limit
  *    ESNOTFND   prefix not found in dest
*/
SECUREC_API
errno_t strprefix_sec (const char *dest, size_t dmax, const char *src); 

/** @fn : strremovews_sec
  * @brief :  
  *    Removes beginning and trailing whitespace from the string pointed to by
  *    dest by shifting the text left over writting the beginning whitespace.
  *    The shifted-trimmed text is null terminated.
  * @param [IN] dest : pointer to string to determine the prefix
  * @param [IN] dmax : restricted maximum length of string dest
  * @param [OUT] none
  * @return : 
  *    EOK
  *    ESNULLP     NULL pointer
  *    ESZEROL     zero length
  *    ESLEMAX     length exceeds max limit
  *    ESUNTERM    dest was not null terminated
*/
SECUREC_API
errno_t strremovews_sec (char *dest, size_t dmax);

/** @fn : strspn_sec
  * @brief :  
  *    This function computes the prefix length of the string
  *    pointed to by dest which consists entirely of characters
  *    that are included from the string pointed to by src.
  * @param [IN] dest : pointer to string to determine the prefix
  * @param [IN] dmax : restricted maximum length of string dest
  * @param [IN] src : pointer to exclusion string
  * @param [IN] slen : pointer to a count variable that will be updated
  *              with the dest substring length
  * @param [IN] count : updated count
  * @param [OUT] substring : returned substring pointer
  * @return : 
  *    EOK         count
  *    ESNULLP     NULL pointer
  *    ESZEROL     zero length
  *    ESLEMAX     length exceeds max limit
*/
SECUREC_API
errno_t strspn_sec (const char *dest, size_t dmax, const char *src,  size_t slen, size_t *count);

/** @fn : strstr_sec
  * @brief :  
  *    The strstr_sec() function locates the first occurrence of the
  *    substring pointed to by src which would be located in the
  *    string pointed to by dest.
  * @param [IN] dest : pointer to string to be searched for the substring
  * @param [IN] dmax : restricted maximum length of dest string
  * @param [IN] src : pointer to the sub string
  * @param [IN] slen : the maximum number of characters to copy from src
  * @param [IN] substring : the returned substring pointer
  * @param [OUT] substring : returned substring pointer
  * @return : 
  *     EOK        successful operation, substring found.
  *     ESNULLP    NULL pointer
  *     ESZEROL    zero length
  *     ESLEMAX    length exceeds max limit
  *     ESNOTFND   substring not found
*/
SECUREC_API
errno_t strstr_sec (char *dest, size_t dmax, const char *src, size_t slen, char **substring);

/** @fn : strtolowercase_sec
  * @brief :  
  *    Scans the string converting uppercase characters to
  *    lowercase, leaving all other characters unchanged.
  *    The scanning stops at the first null or after dmax
  *    characters.
  * @param [IN] dest : pointer to string
  * @param [IN] dmax : maximum length of string
  * @param [OUT] dest : updated string
  * @return : 
  *    EOK        successful operation
  *    ESNULLP    NULL pointer
  *    ESZEROL    zero length
  *    ESLEMAX    length exceeds max limit
*/
SECUREC_API
errno_t strtolowercase_sec (char *dest, size_t dmax);

/** @fn : strtouppercase_sec
  * @brief :  
  *    Scans the string converting lowercase characters to
  *    uppercase, leaving all other characters unchanged.
  *    The scanning stops at the first null or after dmax
  *    characters.
  * @param [IN] dest : pointer to string
  * @param [IN] dmax : maximum length of string
  * @param [OUT] dest : updated string
  * @return : 
  *    EOK        successful operation
  *    ESNULLP    NULL pointer
  *    ESZEROL    zero length
  *    ESLEMAX    length exceeds max limit
*/
SECUREC_API
errno_t strtouppercase_sec (char *dest, size_t dmax);

/*
 * Description: The memset_sec function copies the value of c (converted to an unsigned char) into each of
 * the first count characters of the object pointed to by dest.
 * Parameter: dest - destination address
 * Parameter: destMax - The maximum length of destination buffer
 * Parameter: c - the value to be copied
 * Parameter: count - copies count bytes of value to dest
 * Return:    EOK if there was no runtime-constraint violation
 */
SECUREC_API 
errno_t memset_sec(void *dest, size_t destMax, int c, size_t count);

/*
 * Description: The memmove_sec function copies n characters from the object pointed to by src
 * into the object pointed to by dest.
 * Parameter: dest - destination  address
 * Parameter: destMax - The maximum length of destination buffer
 * Parameter: src - source address
 * Parameter: count - copies count bytes from the src
 * Return:    EOK if there was no runtime-constraint violation
 */
SECUREC_API 
errno_t memmove_sec(void *dest, size_t destMax, const void *src, size_t count);

/*
 * Description: The memcpy_sec function copies n characters from the object pointed to
 * by src into the object pointed to by dest.
 * Parameter: dest - destination  address
 * Parameter: destMax - The maximum length of destination buffer
 * Parameter: src - source address
 * Parameter: count - copies count bytes from the  src
 * Return:    EOK if there was no runtime-constraint violation
 */
SECUREC_API 
errno_t memcpy_sec(void *dest, size_t destMax, const void *src, size_t count);

/*
 * Description: The strcpy_sec function copies the string pointed to by strSrc (including
 * the terminating null character) into the array pointed to by strDest
 * Parameter: strDest - destination  address
 * Parameter: destMax - The maximum length of destination buffer(including the terminating null character)
 * Parameter: strSrc - source address
 * Return:    EOK if there was no runtime-constraint violation
 */
SECUREC_API 
errno_t strcpy_sec(char *strDest, size_t destMax, const char *strSrc);

/*
 * Description: The strncpy_sec function copies not more than n successive characters (not including
 * the terminating null character) from the array pointed to by strSrc to the array pointed to by strDest.
 * Parameter: strDest - destination  address
 * Parameter: destMax - The maximum length of destination buffer(including the terminating null character)
 * Parameter: strSrc - source  address
 * Parameter: count - copies count characters from the src
 * Return:    EOK if there was no runtime-constraint violation
 */
SECUREC_API 
errno_t strncpy_sec(char *strDest, size_t destMax, const char *strSrc, size_t count);

/*
 * Description: The strcat_sec function appends a copy of the string pointed to by strSrc (including
 * the terminating null character) to the end of the string pointed to by strDest.
 * Parameter: strDest - destination  address
 * Parameter: destMax - The maximum length of destination buffer(including the terminating null wide character)
 * Parameter: strSrc - source address
 * Return:    EOK if there was no runtime-constraint violation
 */
SECUREC_API 
errno_t strcat_sec(char *strDest, size_t destMax, const char *strSrc);

/*
 * Description: The strncat_sec function appends not more than n successive characters (not including
 * the terminating null character)
 * from the array pointed to by strSrc to the end of the string pointed to by strDest.
 * Parameter: strDest - destination address
 * Parameter: destMax - The maximum length of destination buffer(including the terminating null character)
 * Parameter: strSrc - source address
 * Parameter: count - copies count characters from the src
 * Return:    EOK if there was no runtime-constraint violation
 */
SECUREC_API 
errno_t strncat_sec(char *strDest, size_t destMax, const char *strSrc, size_t count);

/*
 * Description: The sprintf_sec function is equivalent to the sprintf function except for the parameter destMax
 * and the explicit runtime-constraints violation
 * Parameter: strDest -  produce output according to a format ,write to the character string strDest.
 * Parameter: destMax - The maximum length of destination buffer(including the terminating null byte '\0')
 * Parameter: format - format string
 * Return:    the number of characters printed(not including the terminating null byte '\0'),
 * If an error occurred Return: -1.
*/
SECUREC_API 
int sprintf_sec(char *strDest, size_t destMax, const char *format, ...) SECUREC_ATTRIBUTE(3, 4);

/*
 * Description: 
 *    The vsprintf_sec function is equivalent to the vsprintf function
 *    except for the parameter destMax and the explicit runtime-constraints violation
 *    The vsprintf_sec function takes a pointer to an argument list, and then formats
 *    and writes the given data to the memory pointed to by strDest.
 *    The function differ from the non-secure versions only in that the secure
 *    versions support positional parameters
 * Parameter: strDest -  Storage location for the output.
 * Parameter: destMax - Size of strDest
 * Parameter: format - Format specification.
 * Parameter: argList - pointer to list of arguments
 * Return:    return  the number of characters written, not including the terminating null character,
 *    return -1  if an  error occurs.
*/
SECUREC_API 
int vsprintf_sec(char *strDest, size_t destMax, const char *format, va_list argList);

/*
 * Description: The snprintf_sec function is equivalent to the snprintf function except for
 * the parameter destMax/count and the explicit runtime-constraints violation
 * Parameter: strDest - produce output according to a format ,write to the character string strDest.
 * Parameter: destMax - The maximum length of destination buffer(including the terminating null  byte '\0')
 * Parameter: count - do not write more than count bytes to strDest(not including the terminating null  byte '\0')
 * Parameter: format - format string
 * Return:    the number of characters printed(not including the terminating null byte '\0'),
 * If an error occurred Return: -1.Pay special attention to returning -1 when truncation occurs.
 */
SECUREC_API 
int snprintf_sec(char *strDest, size_t destMax, size_t count, const char *format,
                           ...) SECUREC_ATTRIBUTE(4, 5);

#if SECUREC_SNPRINTF_TRUNCATED
/*
 * Description: The snprintf_truncated_sec function is equivalent to the snprintf_sec function except
 * no count parameter and return value
 * Parameter: strDest - produce output according to a format,write to the character string strDest.
 * Parameter: destMax - The maximum length of destination buffer(including the terminating null byte '\0')
 * Parameter: format - format string
 * Return:    the number of characters printed(not including the terminating null byte '\0'),
 * If an error occurred Return: -1.Pay special attention to returning destMax - 1 when truncation occurs.
 */
SECUREC_API 
int snprintf_truncated_sec(char *strDest, size_t destMax,
                                     const char *format, ...) SECUREC_ATTRIBUTE(3, 4);

#endif //SECUREC_SNPRINTF_TRUNCATED

/*
 * Description: The scanf_sec function is equivalent to fscanf_sec with the argument stdin
 * interposed before the arguments to scanf_sec
 * Parameter: format - format string
 * Return:    the number of input items assigned, If an error occurred Return: -1.
 */
SECUREC_API 
int scanf_sec(const char *format, ...);

/*
 * Description: The sscanf_sec function is equivalent to fscanf_sec, except that input is obtained from a
 * string (specified by the argument buffer) rather than from a stream
 * Parameter: buffer - read character from buffer
 * Parameter: format - format string
 * Return:    the number of input items assigned, If an error occurred Return: -1.
 */
SECUREC_API 
int sscanf_sec(const char *buffer, const char *format, ...);

/*
 * Description: The fscanf_sec function is equivalent to fscanf except that the c, s, and [ conversion specifiers
 * apply to a pair of arguments (unless assignment suppression is indicated by a *)
 * Parameter: stream - stdio file stream
 * Parameter: format - format string
 * Return:    the number of input items assigned, If an error occurred Return: -1.
 */
SECUREC_API 
int fscanf_sec(FILE *stream, const char *format, ...);

/*
 * Description: The vfscanf_sec function is equivalent to fscanf_sec, with the variable argument list
 * replaced by argList
 * Parameter: stream - stdio file stream
 * Parameter: format - format string
 * Parameter: argList - instead of a variable number of arguments
 * Return:    the number of input items assigned, If an error occurred Return: -1.
 */
SECUREC_API 
int vfscanf_sec(FILE *stream, const char *format, va_list argList);

/*
 * Description: The strtok_sec function parses a string into a sequence of strToken,
 * replace all characters in strToken string that match to strDelimit set with 0.
 * On the first call to strtok_sec the string to be parsed should be specified in strToken.
 * In each subsequent call that should parse the same string, strToken should be NULL
 * Parameter: strToken - the string to be delimited
 * Parameter: strDelimit - specifies a set of characters that delimit the tokens in the parsed string
 * Parameter: context - is a pointer to a char * variable that is used internally by strtok_sec function
 * Return:  On the first call returns the address of the first non \0 character, otherwise NULL is returned.
 * In subsequent calls, the strtoken is set to NULL, and the context set is the same as the previous call,
 * return NULL if the *context string length is equal 0, otherwise return *context.
 */
SECUREC_API 
char *strtok_sec(char *strToken, const char *strDelimit, char **context);

/*
 * Description: The gets_sec function reads at most one less than the number of characters specified
 * by destMax from the stream pointed to by stdin, into the array pointed to by buffer
 * Parameter: buffer - destination address
 * Parameter: destMax - The maximum length of destination buffer(including the terminating null character)
 * Return:    buffer if there was no runtime-constraint violation,If an error occurred Return: NULL.
 */
SECUREC_API 
char *gets_sec(char *buffer, size_t destMax);

/*
 * Description: The wmemcpy_sec function copies n successive wide characters from the object pointed to
 * by src into the object pointed to by dest.
 * Parameter: dest - destination  address
 * Parameter: destMax - The maximum length of destination buffer
 * Parameter: src - source address
 * Parameter: count - copies count wide characters from the  src
 * Return:    EOK if there was no runtime-constraint violation
 */
SECUREC_API 
errno_t wmemcpy_sec(wchar_t *dest, size_t destMax, const wchar_t *src, size_t count);

/*
 * Description: The wmemmove_sec function copies n successive wide characters from the object
 * pointed to by src into the object pointed to by dest.
 * Parameter: dest - destination  address
 * Parameter: destMax - The maximum length of destination buffer
 * Parameter: src - source address
 * Parameter: count - copies count wide characters from the  src
 * Return:    EOK if there was no runtime-constraint violation
 */
SECUREC_API 
errno_t wmemmove_sec(wchar_t *dest, size_t destMax, const wchar_t *src, size_t count);

/*
 * Description: The wcscpy_sec function copies the wide string pointed to by strSrc(including the terminating
 * null wide character) into the array pointed to by strDest
 * Parameter: strDest - destination address
 * Parameter: destMax - The maximum length of destination buffer
 * Parameter: strSrc - source address
 * Return:    EOK if there was no runtime-constraint violation
 */
SECUREC_API 
errno_t wcscpy_sec(wchar_t *strDest, size_t destMax, const wchar_t *strSrc);

/*
 * Description: The wcsncpy_sec function copies not more than n successive wide characters (not including the
 * terminating null wide character) from the array pointed to by strSrc to the array pointed to by strDest
 * Parameter: strDest - destination address
 * Parameter: destMax - The maximum length of destination buffer(including the terminating wide character)
 * Parameter: strSrc - source address
 * Parameter: count - copies count wide characters from the src
 * Return:    EOK if there was no runtime-constraint violation
 */
SECUREC_API 
errno_t wcsncpy_sec(wchar_t *strDest, size_t destMax, const wchar_t *strSrc, size_t count);

/*
 * Description: The wcscat_sec function appends a copy of the wide string pointed to by strSrc (including the
 * terminating null wide character) to the end of the wide string pointed to by strDest
 * Parameter: strDest - destination  address
 * Parameter: destMax - The maximum length of destination buffer(including the terminating wide character)
 * Parameter: strSrc - source address
 * Return:    EOK if there was no runtime-constraint violation
 */
SECUREC_API 
errno_t wcscat_sec(wchar_t *strDest, size_t destMax, const wchar_t *strSrc);

/*
 * Description: The wcsncat_sec function appends not more than n successive wide characters (not including the
 * terminating null wide character) from the array pointed to by strSrc to the end of the wide string pointed to
 * by strDest.
 * Parameter: strDest - destination  address
 * Parameter: destMax - The maximum length of destination buffer(including the terminating wide character)
 * Parameter: strSrc - source  address
 * Parameter: count - copies count wide characters from the  src
 * Return:    EOK if there was no runtime-constraint violation
 */
SECUREC_API 
errno_t wcsncat_sec(wchar_t *strDest, size_t destMax, const wchar_t *strSrc, size_t count);

/*
 * Description: The wcstok_sec function is the wide-character equivalent of the strtok_sec function
 * Parameter: strToken - the string to be delimited
 * Parameter: strDelimit - specifies a set of characters that delimit the tokens in the parsed string
 * Parameter: context - is a pointer to a char * variable that is used internally by strtok_sec function
 * Return:    a pointer to the first character of a token, or a null pointer if there is no token
 * or there is a runtime-constraint violation.
 */
SECUREC_API 
wchar_t *wcstok_sec(wchar_t *strToken, const wchar_t *strDelimit, wchar_t **context);

/*
 * Description: The swprintf_sec function is the wide-character equivalent of the sprintf_sec function
 * Parameter: strDest - produce output according to a format,write to the character string strDest
 * Parameter: destMax - The maximum length of destination buffer(including the terminating null)
 * Parameter: format - format string
 * Return:    the number of characters printed(not including the terminating null wide character),
 * If an error occurred Return: -1.
 */
SECUREC_API 
int swprintf_sec(wchar_t *strDest, size_t destMax, const wchar_t *format, ...);

/*
 * Description: The fwscanf_sec function is the wide-character equivalent of the fscanf_sec function
 * Parameter: stream - stdio file stream
 * Parameter: format - format string
 * Return:    the number of input items assigned, If an error occurred Return: -1.
 */
SECUREC_API 
int fwscanf_sec(FILE *stream, const wchar_t *format, ...);

/*
 * Description: The wscanf_sec function is the wide-character equivalent of the scanf_sec function
 * Parameter: format - format string
 * Return:    the number of input items assigned, If an error occurred Return: -1.
 */
SECUREC_API 
int wscanf_sec(const wchar_t *format, ...);

/*
 * Description: The swscanf_sec function is the wide-character equivalent of the sscanf_sec function
 * Parameter: buffer - read character from buffer
 * Parameter: format - format string
 * Return:    the number of input items assigned, If an error occurred Return: -1.
 */
SECUREC_API 
int swscanf_sec(const wchar_t *buffer, const wchar_t *format, ...);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


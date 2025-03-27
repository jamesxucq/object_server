/* 
 * File:   encoding.h
 * Author: David
 *
 * Created on 2011
 */

#ifndef ENCODING_H
#define	ENCODING_H

#ifdef	__cplusplus
extern "C" {
#endif

    // chks_str[MD5_TEXT_LENGTH]
    char *reply_auth_chks(char *chks_str, char *user_name, char *password);
    // chks_str[MD5_TEXT_LENGTH]
    char *trans_auth_chks(char *chks_str, unsigned int uid, char *access_key);
    // chks_bin[MD5_DIGEST_LEN]
    unsigned char *salt_auth_chks(unsigned char *chks_bin, unsigned char *plai_valid, char *salt);

    char *encode_base64_text(char *cipher_txt, char *plain_txt, char *salt_value);
    char *decode_base64_text(char *plain_txt, char *cipher_txt, char *salt_value);
    // salt_value[SALT_LENGTH]
    unsigned char *random_salt(unsigned char *salt_value);

#ifdef	__cplusplus
}
#endif

#endif	/* ENCODING_H */


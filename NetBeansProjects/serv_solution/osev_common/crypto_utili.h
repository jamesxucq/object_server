
/* 
 * File:   crypto_utili.h
 * Author: James Xu
 *
 * Created on 2018.2.22, PM 2:04
 */

#ifndef CRYPTO_UTILI_H
#define CRYPTO_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    unsigned char *produ_authen_key(unsigned char *ecb_key,  unsigned char *user_salt);
    unsigned char *crypto_decode_ecb(unsigned char *plain, unsigned char *cipher, unsigned char *ecb_key);
    unsigned char *crypto_encode_ecb(unsigned char *cipher, unsigned char *plain, unsigned char *ecb_key);
    
    //
    void encode_salt_paswd(unsigned char *salt_paswd, unsigned char *salt, unsigned char *paswd);
    void decode_salt_paswd(unsigned char *salt, unsigned char *paswd, unsigned char *salt_paswd);


#ifdef __cplusplus
}
#endif

#endif /* CRYPTO_UTILI_H */


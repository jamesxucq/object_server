#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  

#include "commo_macro.h"
#include "osev_datyp.h"
#include "osev_macro.h"
#include "mbedtls/aes.h"
#include "crypto_utili.h"
#include "osev_macro.h"
#include "stri_utili.h"


//
#define AUTH_MAGIC_STRI "emsaBJLdCi0v9a3D"

unsigned char *produ_authen_key(unsigned char *ecb_key, unsigned char *user_salt) {
    char *magic = AUTH_MAGIC_STRI;
    unsigned char *ekey = ecb_key;
    unsigned char *salt = user_salt;
    //
    unsigned int inde = 0x00;
    for (; KEY_LENGTH > inde; ++inde) {
        ekey[0x00] = salt[0x00]^magic[0x00];
        ++magic;
        ++salt;
        ++ekey;
    }
    //
    return ecb_key;
}

unsigned char *crypto_decode_ecb(unsigned char *plain, unsigned char *cipher, unsigned char *ecb_key) {
    mbedtls_aes_context aes_ctx;
    mbedtls_aes_init(&aes_ctx);
    //
    if (mbedtls_aes_setkey_dec(&aes_ctx, ecb_key, 128))
        return NULL;
    if (mbedtls_aes_crypt_ecb(&aes_ctx, MBEDTLS_AES_DECRYPT, cipher, plain))
        return NULL;
    //
    mbedtls_aes_free(&aes_ctx);
    return plain;
}

//

unsigned char *crypto_encode_ecb(unsigned char *cipher, unsigned char *plain, unsigned char *ecb_key) {
    mbedtls_aes_context aes_ctx;
    mbedtls_aes_init(&aes_ctx);
    //    
    if (mbedtls_aes_setkey_enc(&aes_ctx, ecb_key, 128))
        return NULL;
    if (mbedtls_aes_crypt_ecb(&aes_ctx, MBEDTLS_AES_ENCRYPT, plain, cipher))
        return NULL;
    //
    mbedtls_aes_free(&aes_ctx);
    return cipher;
}

//

void encode_salt_paswd(unsigned char *salt_paswd, unsigned char *salt, unsigned char *paswd) {
    memcpy(salt_paswd, salt, SALT_LENGTH);
    memcpy(salt_paswd + SALT_LENGTH, paswd, PASWD_LENGTH);
}

void decode_salt_paswd(unsigned char *salt, unsigned char *paswd, unsigned char *salt_paswd) {
    memcpy(salt, salt_paswd, SALT_LENGTH);
    memcpy(paswd, salt_paswd + SALT_LENGTH, PASWD_LENGTH);
}
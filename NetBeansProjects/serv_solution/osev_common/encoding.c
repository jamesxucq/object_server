#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "utility/checksum.h"
#include "commo_macro.h"
#include "osev_datyp.h"
#include "osev_macro.h"
#include "utility/base64.h"

#include "encoding.h"
#include "debug_funct_osv.h"

// chks_str[MD5_TEXT_LENGTH]

char *reply_auth_chks(char *chks_str, char *user_name, char *password) {
    char buffer[MID_TLENG];
    //
    if (!password || !user_name || !chks_str)
        return NULL;
    sprintf(buffer, "%s:%s", user_name, password);
    get_md5sum_text(buffer, strlen(buffer), chks_str);
    //
    return chks_str;
}

// chks_str[MD5_TEXT_LENGTH]

char *trans_auth_chks(char *chks_str, unsigned int uid, char *access_key) {
    char buffer[MID_TLENG];
    //
    if (!access_key || !chks_str)
        return NULL;
    sprintf(buffer, "%u:%s", uid, access_key);
    get_md5sum_text(buffer, strlen(buffer), chks_str);
    //
    return chks_str;
}

// chks_bin[MD5_DIGEST_LEN]

unsigned char *salt_auth_chks(unsigned char *chks_bin, unsigned char *plai_valid, char *salt) {
    // OSEVPF("[FUNC]:salt_auth_chks\n");
    char buffe[MID_TLENG];
    if (!plai_valid || !chks_bin)
        return NULL;
    char *last_str = lszcpy(buffe, salt, SALT_LENGTH);
    last_str = lccpy(last_str, ':');
    last_str = lscpy(last_str, (char *) plai_valid);
    last_str = lccpy(last_str, ':');
    lszcpy(last_str, salt, SALT_LENGTH);
    // OSEVPF("authen buffe:|%s|\n", buffe);
    get_md5sum_memo(buffe, strlen(buffe), chks_bin);
    //
    return chks_bin;
}

//

char *decode_base64_text(char *plain_txt, char *cipher_txt, char *salt_value) {
    char buffer[MID_TLENG];
    //
    if (!cipher_txt || !plain_txt || !salt_value || *cipher_txt == '\0')
        return NULL;
    MK_ZERO(buffer);
    int desiz = base64_decode((unsigned char *) buffer, cipher_txt, MID_TLENG);
    int salt_length = strlen(salt_value);
    strncpy(plain_txt, buffer + salt_length, desiz - (salt_length << 1));
    plain_txt[desiz - (salt_length << 1)] = '\0';
    //
    return plain_txt;
}

char *encode_base64_text(char *cipher_txt, char *plain_txt, char *salt_value) {
    char buffer[MID_TLENG];
    //
    if (!cipher_txt || !plain_txt || !salt_value || *plain_txt == '\0')
        return NULL;
    sprintf(buffer, "%s%s%s", salt_value, plain_txt, salt_value);
    if (!base64_encode(cipher_txt, MID_TLENG, (const unsigned char *) buffer, strlen(buffer)))
        return NULL;
    //
    return cipher_txt;
}

// salt_value[SALT_LENGTH]

unsigned char *random_salt(unsigned char *salt_value) {
    unsigned char code_array[62] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    unsigned int last_seed;
    //
    if (!salt_value) return NULL;
    unsigned char *rand_str = salt_value;
    last_seed = time(NULL);
    int tatol = 0x00;
    for (; SALT_LENGTH > tatol; ++tatol, ++rand_str) {
        srand((unsigned int) last_seed);
        last_seed = rand();
        rand_str[0x00] = code_array[last_seed % 62];
    }
    return salt_value;
}
#ifndef CHECKSUM_H_
#define CHECKSUM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utility/md5.h"
#include "utility/adler32.h"

#define MD5_DIGEST_LEN 16
    // #define MD5_TEXT_LENGTH	(MD5_DIGEST_LEN * 2 + 1)
#define MD5_TEXT_LENGTH 33

#define CHKS_CHUNK 4096

    //
#define GET_ADLER32_CHKS(ADLER, BUFF, LENG)              adler32_chksum(ADLER, BUFF, LENG)
#define GET_ADLER32_ROLLING(chks, LENG, C1, C2)          adler32_rolling(chks, LENG, C1, C2);

    // unsigned char chks_mem[MD5_DIGEST_LEN]
#define GET_CHKS_MD5(BUFF, LENG, CHKS) get_md5(BUFF, LENG, CHKS)
    // unsigned char chks[MD5_DIGEST_LEN]

    inline void get_md5(unsigned char *buff, int len, unsigned char *chks) {
        MD5_CTX md;
        MD5Init(&md);
        MD5Update(&md, buff, len);
        MD5Final(&md);
        memcpy(chks, md.digest, MD5_DIGEST_LEN);
    }

    //
    //static int sumresidue;
    extern MD5_CTX gmd;

    inline void sum_init(int seed) {
        MD5Init(&gmd);
    }

    /**
     * Feed data into an MD4 accumulator, md.  The results may be
     * retrieved using sum_end().  md is used for different purposes at
     * different points during execution.
     *
     * @todo Perhaps get rid of md and just pass in the address each time.
     * Very slightly clearer and slower.
     **/
    inline void sum_update(const char *p, int len) {
        MD5Update(&gmd, (unsigned char *) p, len);
    }
    // unsigned char chks[MD5_DIGEST_LEN]

    inline int sum_end(unsigned char *chks) {
        MD5Final(&gmd);
        memcpy(chks, gmd.digest, MD5_DIGEST_LEN);
        return MD5_DIGEST_LEN;
    }


    // char chks_str[MD5_TEXT_LENGTH]

    inline void get_md5sum_text(char *buff, int len, char *chks_str) {
        MD5_CTX md;
        MD5Init(&md);
        MD5Update(&md, (unsigned char *) buff, len);
        MD5Final(&md);
        unsigned char *digest = md.digest;
        unsigned int inde = 0x00;
        for (; inde < MD5_DIGEST_LEN; ++inde, ++digest) {
            sprintf(chks_str, "%02x", *digest);
            ++chks_str;
            ++chks_str;
        }
        // chks_str[0x00] = '\0';
    }

    // unsigned char chks_mem[MD5_DIGEST_LEN]

    inline void get_md5sum_memo(char *buff, int len, unsigned char *chks_mem) {
        MD5_CTX md;
        MD5Init(&md);
        MD5Update(&md, (unsigned char *) buff, len);
        MD5Final(&md);
        memcpy(chks_mem, md.digest, MD5_DIGEST_LEN);
    }
    // unsigned char chks[MD5_DIGEST_LEN]
    int file_chks(unsigned char *chks, char *file_name, unsigned long long offset);
    // char chks_str[MD5_TEXT_LENGTH]
    int file_chks_text(char *chks_str, char *file_name, unsigned long long offset);
    // unsigned char chks[MD5_DIGEST_LEN]
    int file_chks64(unsigned char *chks, char *file_name, unsigned long long offset);

#ifdef __cplusplus
}
#endif

#endif /* CHECKSUM_H_ */

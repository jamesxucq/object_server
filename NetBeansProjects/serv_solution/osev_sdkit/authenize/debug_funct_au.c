
#include "commo_header.h"

#include "debug_funct_au.h"

//

void prin_md5sum(unsigned char *md5sum) {
    char sum_stri[MD5_TEXT_LENGTH];
    char *chks_str = sum_stri;
    unsigned char *digest = md5sum;
    uint32 inde = 0x00;
    for (; inde < MD5_DIGEST_LEN; ++inde, ++digest) {
        sprintf(chks_str, "%02x", *digest);
        ++chks_str;
        ++chks_str;
    }
    printf("md5sum:|%s|\n", sum_stri);
}
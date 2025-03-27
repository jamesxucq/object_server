
#include "commo_header.h"

#include "debug_funct_os.h"

//

void p_md5sum_os(unsigned char *md5sum) {
    char sum_stri[33];
    char *chks_str = sum_stri;
    unsigned char *digest = md5sum;
    uint32 inde = 0x00;
    for (; inde < 16; ++inde, ++digest) {
        sprintf(chks_str, "%02x", *digest);
        ++chks_str;
        ++chks_str;
    }
    printf("md5sum:|%s|\n", sum_stri);
}

//
#define APAM_USER_NAME     0x00
#define APAM_REQU_VALID    0x01
#define APAM_REQU_SALT     0x02
#define APAM_PARAM_POSI    0x03
#define APAM_OSEV_BASE     0x03

void p_authen(inte_value *inval) {
#ifdef _DEBUG
    OSEVPF("[0x00]user_name:|%s|\n", inval->pamvs.pamcon[APAM_USER_NAME]);
    OSEVPF("[0x01]inval->req_valid:");
    PRIN_md5sum_os((unsigned char *) inval->pamvs.pamcon[APAM_REQU_VALID]);
    char temp[33];
    strzcpy(temp, inval->pamvs.pamcon[APAM_REQU_SALT], SALT_LENGTH);
    OSEVPF("[0x02]inval->salt:|%s|\n", temp);
    OSEVPF("[0x03]osev_base:|%s|\n", inval->pamvs.pamcon[APAM_OSEV_BASE]);
#endif
}


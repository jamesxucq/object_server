
#include "hash_mapd_ex.h"


//

uint32_t sax_hash_hmd(char *key, int ksiz) {
    uint32_t hav = 0x00;
    while (ksiz--) hav ^= (hav << 5)+(hav >> 2) + (unsigned char) *key++;
    return hav;
}

//

uint32_t sdbm_hash_hmd(char *key, int ksiz) {
    uint32_t hav = 0x00;
    while (ksiz--) hav = (unsigned char) *key++ + (hav << 6) + (hav << 16) - hav;
    return hav;
}

//

OBIDHMD *creat_temp_ohmd() {
    char hmdn[OHMD_NAME_LENGTH] = {"/tmp/oidhmd.XXXXXX"};
    //   
    OBIDHMD *ohmd = oidhmd_new(HASHMD_DEFAULT_TNUM, HASHMD_DEFAULT_BNUM, HASHMD_DEFAULT_CNUM, sax_hash_hmd, sdbm_hash_hmd);
    if (!ohmd) return NULL;
    if (!mkstemp(hmdn)) {
        oidhmd_dele(ohmd);
        return NULL;
    }
    if (oidhmd_open(ohmd, hmdn)) {
        oidhmd_dele(ohmd);
        return NULL;
    }
    oidhmd_unlink(ohmd);
    //
    return ohmd;
}

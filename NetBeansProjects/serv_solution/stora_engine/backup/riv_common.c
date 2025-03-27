#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "riv_common.h"

//
unsigned int riv_strhash(void *src) {
    int i, l;
    unsigned long ret = 0;
    unsigned short *s;
    char *str = (char *) src;
    if (NULL == str) return (0);
    l = (strlen(str) + 1) / 2;
    s = (unsigned short *) str;

    for (i = 0; i < l; i++)
        ret ^= s[i] << (i & 0x0f);
    //
    return (ret);
}

//
int rive_estr(void *k1, void *k2) {
    return (0 == strcmp((char *) k1, (char *) k2));
}

//
/*
unsigned int riv_oidhash(void *oid) {
    int i, l;
    unsigned long ret = 0;
    unsigned short *s;
    char *str = (char *) oid;
    if (NULL == str) return (0);
    l = (sizeof(osv_oid_t) + 1) / 2;
    s = (unsigned short *) str;

    for (i = 0; i < l; i++)
        ret ^= s[i] << (i & 0x0f);
    //
    return (ret);
}
*/

// int rive_eoid(void *k1, void *k2) {
//    return (0 == strncmp((char *) k1, (char *) k2, sizeof(osv_oid_t)));
// }
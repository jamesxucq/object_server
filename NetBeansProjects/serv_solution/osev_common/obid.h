
/* 
 * File:   obid.h
 * Author: James Xu
 *
 * Created on 2017.2.1, PM 3:40
 */

#ifndef OBID_H
#define OBID_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

//
#include "utility/last_stri.h"
#include "commo_macro.h"
#include "osev_datyp.h"
#include "osev_atomic.h"
#include "stoid.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef OSEV_OBID_I
#define OSEV_OBID_I

#pragma pack(1)

    struct _osv_oid_i_ {
        unsigned int osev_unique; // machine_unique
        unsigned long long stoid;
    };
#pragma pack()

    typedef struct _osv_oid_i_ osv_oid_i;
    //

#endif  /* OSEV_OBID_I */

#ifndef OSEV_OBID_T
#define OSEV_OBID_T

#pragma pack(1)

    struct _osv_oid_t_ {
        unsigned int osev_unique; // machine_unique
        unsigned int time_stamp;
        unsigned int counter;
    };
#pragma pack()

    typedef struct _osv_oid_t_ osv_oid_t;

#endif  /* OSEV_OBID_T */

    //
    extern osv_oid_t INVA_OBID_VALU;

    //
    osv_oid_t *creat_osev_obid(osv_oid_t *osev_obid);
    char *creat_osev_name(char *serv_name);

    //
#define IS_OSEV_BASE_OBID(OBID_T) ((OBID_T).time_stamp || (OBID_T).counter)

    // BLEN = binary length, SLEN = string length, NLEN = NULL-terminated string length
#define OBJE_IDENTI_BLEN      sizeof (osv_oid_t) // 12
#define OBJE_IDENTI_SLEN      24
#define OBJE_IDENTI_ZLEN      (OBJE_IDENTI_SLEN + 0x01)
#define OBID_SEPARATE_SLEN    26
#define OBID_SEPARATE_ZLEN    (OBID_SEPARATE_SLEN + 0x01)

#define PASS_OBIDEN_SECTI(OBJE_DATA)    (OBJE_IDENTI_BLEN + OBJE_DATA)

    //

    inline osv_oid_t *stroid(osv_oid_t *binary_obid, char *obid_stri) {
        char *tokop = (char *) binary_obid;
        char nodchr[0x03];
        nodchr[0x02] = '\0';
        unsigned int inde = 0x00;
        for (; inde < (int) OBJE_IDENTI_BLEN; ++inde) {
            nodchr[0x00] = obid_stri[0x00];
            ++obid_stri;
            nodchr[0x01] = obid_stri[0x00];
            ++obid_stri;
            tokop[0x00] = strtol(nodchr, NULL, 16);
            ++tokop;
        }
        return binary_obid;
    }


    //

    inline char *oidstr(char *obid_stri, osv_oid_t *binary_obid) {
        char *toksp = obid_stri;
        unsigned char *tokop = (unsigned char *) binary_obid;
        unsigned int inde = 0x00;
        for (; inde < (int) OBJE_IDENTI_BLEN; ++inde, ++tokop, ++toksp) {
            sprintf(toksp, "%02x", *tokop);
            ++toksp;
        }
        return obid_stri;
    }

    inline char *unistr(char *plai_uniq, unsigned int *osev_unique) {
        char *toksp = plai_uniq;
        unsigned char *tokop = (unsigned char *) osev_unique;
        unsigned int inde = 0x00;
        for (; inde < (int) UNIQ_OBIDEN_BLEN; ++inde, ++tokop, ++toksp) {
            sprintf(toksp, "%02x", *tokop);
            ++toksp;
        }
        return plai_uniq;
    }

    inline char *oidstr_delim(char *obid_stri, osv_oid_t *binary_obid) {
        unsigned char *tokop = (unsigned char *) binary_obid;
        unsigned int inde = 0x00;
        for (; inde < (int) OBJE_IDENTI_BLEN; ++inde, ++tokop) {
            if (!(0x00000003 & inde) && inde)
                obid_stri = lccpy(obid_stri, '-');
            obid_stri = lsprif(obid_stri, "%02x", *tokop);
        }
        return obid_stri;
    }

    //

    inline osv_oid_t *struniq_obid(osv_oid_t *binary_obid, char *uniq_stri) {
        char *tokop = (char *) &((osv_oid_i *) binary_obid)->osev_unique;
        char nodchr[0x03];
        nodchr[0x02] = '\0';
        unsigned int inde = 0x00;
        for (; inde < (int) UNIQ_OBIDEN_BLEN; ++inde) {
            nodchr[0x00] = uniq_stri[0x00];
            ++uniq_stri;
            nodchr[0x01] = uniq_stri[0x00];
            ++uniq_stri;
            tokop[0x00] = strtol(nodchr, NULL, 16);
            ++tokop;
        }
        ((osv_oid_i *) binary_obid)->stoid = 0x00;
        return binary_obid;
    }

    inline char *oid_uniqstr(char *uniq_stri, osv_oid_t *binary_obid) {
        char *toksp = uniq_stri;
        unsigned char *tokop = (unsigned char *) &((osv_oid_i *) binary_obid)->osev_unique;
        unsigned int inde = 0x00;
        for (; inde < (int) UNIQ_OBIDEN_BLEN; ++inde, ++tokop, ++toksp) {
            sprintf(toksp, "%02x", *tokop);
            ++toksp;
        }
        return uniq_stri;
    }

    //

    inline char *oid_sidstr(char *stoid_stri, osv_oid_t *binary_obid) {
        char *toksp = stoid_stri;
        unsigned char *tokop = (unsigned char *) &((osv_oid_i *) binary_obid)->stoid;
        unsigned int inde = 0x00;
        for (; inde < (int) STOR_IDENTI_BLEN; ++inde, ++tokop, ++toksp) {
            sprintf(toksp, "%02x", *tokop);
            ++toksp;
        }
        return stoid_stri;
    }

    //
#define OBID_STOID_EQUALI(POBID, PSTOID) \
    (((osv_oid_i *)POBID)->stoid == (PSTOID)[0x00])

#define OBID_EQUALI(FIRST_POBID, SECOND_POBID) \
    (((osv_oid_i *)FIRST_POBID)->stoid == ((osv_oid_i *)SECOND_POBID)->stoid \
    && (FIRST_POBID)->osev_unique == (SECOND_POBID)->osev_unique)

#define OBID_BINARY_COPY(DEST_POBID, SORC_POBID) { \
    ((osv_oid_i *)DEST_POBID)->stoid = ((osv_oid_i *)SORC_POBID)->stoid; \
    (DEST_POBID)->osev_unique = (SORC_POBID)->osev_unique; \
}

#define OBID_LASTBIN_COPY(LAST_POTR, SORC_POBID) { \
    ((osv_oid_i *)LAST_POTR)->stoid = ((osv_oid_i *)SORC_POBID)->stoid; \
    ((osv_oid_i *)LAST_POTR)->osev_unique = (SORC_POBID)->osev_unique; \
    LAST_POTR += sizeof(osv_oid_i);\
}

#define PLAIN_BINARY_CPYOID(DEST_POBID, PLAI_OBID, SORC_POBID) { \
    ((osv_oid_i *)DEST_POBID)->stoid = ((osv_oid_i *)SORC_POBID)->stoid; \
    (DEST_POBID)->osev_unique = (SORC_POBID)->osev_unique; \
    char *toksp = PLAI_OBID; \
    unsigned char *tokop = (unsigned char *) DEST_POBID; \
    unsigned int inde = 0x00; \
    for (; inde < OBJE_IDENTI_BLEN; ++inde, ++tokop, ++toksp) { \
        sprintf(toksp, "%02x", *tokop); \
        ++toksp; \
    } \
}

    //
#define IS_INVAL_OBID(POBID) \
    ((INVA_ULOLO_VALU == ((osv_oid_i *)POBID)->stoid) && (INVA_UINT_VALU == (POBID)->osev_unique))

#define MAKE_INVAL_OBID(POBID) { \
    ((osv_oid_i *)POBID)->stoid = INVA_ULOLO_VALU; \
    (POBID)->osev_unique = INVA_UINT_VALU; \
} 

    //
#define IS_ZERO_OBID(POBID) \
    (!((osv_oid_i *)POBID)->stoid && !(POBID)->osev_unique)

#define CHK_ZERO_OBID(POBID) \
    (((osv_oid_i *)POBID)->stoid || (POBID)->osev_unique)

#define MAKE_ZERO_OBID(POBID) { \
    ((osv_oid_i *)POBID)->stoid = 0x00; \
    (POBID)->osev_unique = 0x00; \
} 

    //
    int split_oidst_enco(char *line_oid1, char *line_oid2, char *plain_obid);
    // return obid count
    int comma_stroid(osv_oid_t *binary_obid, char *plain_obid);
    // return obid count
    int param_stroid_sing(osv_oid_t *binary_obid, char *plain_obid);
    int param_stroid_mult(osv_oid_t *binary_obid, char *plain_obid);

    // for test
    
#ifdef __cplusplus
}
#endif

#endif /* OBID_H */


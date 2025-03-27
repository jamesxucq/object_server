
/* 
 * File:   osev_obid.h
 * Author: James Xu
 *
 * Created on 2023.6.14, AM 9:38
 */

#ifndef OSEV_OBID_H
#define OSEV_OBID_H

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
#define OBJE_IDENTI_BLEN      sizeof (osv_oid_t) // 12
#define OBJE_IDENTI_SLEN      24
#define OBJE_IDENTI_ZLEN      (OBJE_IDENTI_SLEN + 0x01)
#define OBID_SEPARATE_SLEN    26
#define OBID_SEPARATE_ZLEN    (OBID_SEPARATE_SLEN + 0x01)

    //

    inline osv_oid_t *stroid(osv_oid_t *obje_obid, char *obid_stri) {
        char *tokop = (char *) obje_obid;
        char nodchr[0x03];
        nodchr[0x02] = '\0';
        unsigned int inde = 0x00;
        for (; inde < OBJE_IDENTI_BLEN; ++inde) {
            nodchr[0x00] = obid_stri[0x00];
            ++obid_stri;
            nodchr[0x01] = obid_stri[0x00];
            ++obid_stri;
            tokop[0x00] = strtol(nodchr, NULL, 16);
            ++tokop;
        }
        return obje_obid;
    }


    //

    inline char *oidstr(char *obid_stri, osv_oid_t *obje_obid) {
        char *toksp = obid_stri;
        unsigned char *tokop = (unsigned char *) obje_obid;
        unsigned int inde = 0x00;
        for (; inde < OBJE_IDENTI_BLEN; ++inde, ++tokop, ++toksp) {
            sprintf(toksp, "%02x", *tokop);
            ++toksp;
        }
        return obid_stri;
    }

    //

#define OBID_BINARY_COPY(DEST_POBID, SORC_POBID) { \
    ((osv_oid_i *)DEST_POBID)->stoid = ((osv_oid_i *)SORC_POBID)->stoid; \
    (DEST_POBID)->osev_unique = (SORC_POBID)->osev_unique; \
}

#define OBID_STOID_BUILD(DEST_POBID, SORC_PSTOID) { \
    ((osv_oid_i *)DEST_POBID)->stoid = ((osv_sid_i *)SORC_PSTOID)->stoid; \
    ((DEST_POBID)->osev_unique = _osev_oid_.osev_unique); \
}

#define IS_INVAL_OBID(POBID) \
    ((INVA_UINT_VALU == ((osv_oid_i *)POBID)->stoid) && (INVA_UINT_VALU == (POBID)->osev_unique))

    //
#define IS_ZERO_OBID(POBID) \
    (!((osv_oid_i *)POBID)->stoid && !(POBID)->osev_unique)

#define CHK_ZERO_OBID(POBID) \
    (((osv_oid_i *)POBID)->stoid || (POBID)->osev_unique)

    //

#define IS_BASE_OBID(OBJE_OBID) ((OBJE_OBID)->osev_unique == _osev_oid_.osev_unique \
    && 0x00 != ((osv_oid_i *) OBJE_OBID)->stoid)

    //
#define MAKE_ZERO_OBID(POBID) { \
    ((osv_oid_i *)POBID)->stoid = 0x00; \
    (POBID)->osev_unique = 0x00; \
} 

#ifdef __cplusplus
}
#endif

#endif /* OSEV_OBID_H */


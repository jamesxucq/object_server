
/* 
 * File:   modoid.h
 * Author: James Xu
 *
 * Created on 2023.10.23, AM 10:04
 */

#ifndef MODOID_H
#define MODOID_H

#include "osev_atomic.h"
//
#include "stoid.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    extern osv_oid_t _osev_oid_;
    extern osv_atomic_t _object_counter_;

    //

#define INSTAN_UNIQUE (_osev_oid_.osev_unique)
#define FILL_UNIQUE_OBID(OBJE_OBID) ((OBJE_OBID)->osev_unique = _osev_oid_.osev_unique)
#define FILL_INVALID_OBID(OBJE_OBID) ((OBJE_OBID)->osev_unique = (unsigned int) - 1)

    //
#define INIT_OSEV_OBID(OSEV_OBID) \
    _osev_oid_.osev_unique = (OSEV_OBID)->osev_unique;

    //

    inline void gener_osev_obid(osv_oid_t *osev_obid) {
        osev_obid->osev_unique = _osev_oid_.osev_unique;
        ((osv_oid_i *) osev_obid)->stoid = 0x00;
    }

    //

#define OSEV_STOBID_TOK       "0000000000000000"

    inline void gener_osev_poid(osv_oid_t *osev_obid, char *obid_stri) {
        osev_obid->osev_unique = _osev_oid_.osev_unique;
        ((osv_oid_i *) osev_obid)->stoid = 0x00;
        char *toksp = obid_stri;
        unsigned char *tokop = (unsigned char *) &_osev_oid_.osev_unique;
        unsigned long long inde = 0x00;
        for (; inde < UNIQ_OBIDEN_BLEN; ++inde, ++tokop, ++toksp) {
            sprintf(toksp, "%02x", *tokop);
            ++toksp;
        }
        memcpy(toksp, OSEV_STOBID_TOK, STOR_IDENTI_SLEN);
    }

    //
#define GET_OSEV_OBID()      &_osev_oid_

    inline void creat_base_obid(osv_oid_t *base_obid) {
        base_obid->osev_unique = _osev_oid_.osev_unique;
        base_obid->time_stamp = 0x00000000FFFFFFFF & time(NULL);
        base_obid->counter = OSV_ATOMIC_ADD_FETCH(&_object_counter_, 0x01);
        if (!base_obid->counter) base_obid->counter = OSV_ATOMIC_ADD_FETCH(&_object_counter_, 0x01);
    }

    //

    inline void creat_class_obid(osv_oid_t *lv2p_obid) {
        lv2p_obid->osev_unique = _osev_oid_.osev_unique;
        lv2p_obid->time_stamp = 0x00000000FFFFFFFF & time(NULL);
        lv2p_obid->counter = 0x00;
    }

    inline void creat_objec_obid(osv_oid_t *enti_obid) {
        enti_obid->osev_unique = _osev_oid_.osev_unique;
        enti_obid->time_stamp = 0x00000000FFFFFFFF & time(NULL);
        enti_obid->counter = OSV_ATOMIC_ADD_FETCH(&_object_counter_, 0x01);
        if (!enti_obid->counter) enti_obid->counter = OSV_ATOMIC_ADD_FETCH(&_object_counter_, 0x01);
    }

    inline void gener_base_obid(osv_oid_t *base_obid, osv_oid_t *osev_obid) {
        base_obid->osev_unique = osev_obid->osev_unique;
        base_obid->time_stamp = 0x00000000FFFFFFFF & time(NULL);
        base_obid->counter = OSV_ATOMIC_ADD_FETCH(&_object_counter_, 0x01);
        if (!base_obid->counter) base_obid->counter = OSV_ATOMIC_ADD_FETCH(&_object_counter_, 0x01);
    }

    //

    inline osv_oid_t *strsid_obid(osv_oid_t *binary_obid, char *stoid_stri) {
        char *tokop = (char *) &((osv_oid_i *) binary_obid)->stoid;
        char nodchr[0x03];
        ((osv_oid_i *) binary_obid)->osev_unique = _osev_oid_.osev_unique;
        nodchr[0x02] = '\0';
        unsigned long long inde = 0x00;
        for (; inde < STOR_IDENTI_BLEN; ++inde) {
            nodchr[0x00] = stoid_stri[0x00];
            ++stoid_stri;
            nodchr[0x01] = stoid_stri[0x00];
            ++stoid_stri;
            tokop[0x00] = strtol(nodchr, NULL, 16);
            ++tokop;
        }
        return binary_obid;
    }

    inline char *sid_stroid(char *obid_stri, osv_sid_t *stoid) {
        char *toksp = obid_stri;
        unsigned char *tokop = (unsigned char *) &_osev_oid_.osev_unique;
        unsigned int inde = 0x00;
        for (; inde < (int) UNIQ_OBIDEN_BLEN; ++inde, ++tokop, ++toksp) {
            sprintf(toksp, "%02x", *tokop);
            ++toksp;
        }
        //
        tokop = (unsigned char *) stoid;
        inde = 0x00;
        for (; inde < STOR_IDENTI_BLEN; ++inde, ++tokop, ++toksp) {
            sprintf(toksp, "%02x", *tokop);
            ++toksp;
        }
        // obid_stri[24] = '\0';
        return obid_stri;
    }

    //
#define OBID_STOID_BUILD(DEST_POBID, SORC_PSTOID) { \
    ((osv_oid_i *)DEST_POBID)->stoid = (SORC_PSTOID)[0x00]; \
    ((DEST_POBID)->osev_unique = _osev_oid_.osev_unique); \
}

    //
#define IS_BASE_OBID(OBJE_OBID) ((OBJE_OBID)->osev_unique == _osev_oid_.osev_unique \
    && 0x00 != ((osv_oid_i *) OBJE_OBID)->stoid)

#ifdef __cplusplus
}
#endif

#endif /* MODOID_H */


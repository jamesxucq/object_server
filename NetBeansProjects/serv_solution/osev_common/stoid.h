
/* 
 * File:   stoid.h
 * Author: James Xu
 *
 * Created on 2022.10.11, AM 10:16
 */

#ifndef STOID_H
#define STOID_H

#include <time.h>
#include "osev_atomic.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef OSEV_STOID_I
#define OSEV_STOID_I

    //
    typedef unsigned long long osv_sid_i;

#endif  /* OSEV_STOID_I */
    //
#ifndef OSEV_STOID_T
#define OSEV_STOID_T

    //
#pragma pack(1)

    struct _osv_sid_t_ {
        unsigned int time_stamp;
        unsigned int counter;
    };
#pragma pack()

    typedef struct _osv_sid_t_ osv_sid_t;

#endif  /* OSEV_STOID_T */

    //

    extern osv_atomic_t _object_counter_;

    //

    inline void creat_objec_stoid(osv_sid_t *stoid) {
        stoid->time_stamp = 0x00000000FFFFFFFF & time(NULL);
        stoid->counter = OSV_ATOMIC_ADD_FETCH(&_object_counter_, 0x01);
        if (!stoid->counter) stoid->counter = OSV_ATOMIC_ADD_FETCH(&_object_counter_, 0x01);
    }

    // BLEN = binary length, SLEN = string length, NLEN = NULL-terminated string length
#define STOR_IDENTI_BLEN        sizeof (osv_sid_t) // 8
#define STOR_IDENTI_SLEN        16
#define STOR_IDENTI_ZLEN        (STOR_IDENTI_SLEN + 0x01)

    //
#define UNIQ_OBIDEN_BLEN        sizeof (unsigned int) // 4
#define UNIQ_OBIDEN_SLEN        8
#define UNIQ_OBIDEN_ZLEN        (UNIQ_OBIDEN_SLEN + 0x01)

    //
#define STOID_EQUALI(FPOBID, SPOBID) (((osv_oid_i *)FPOBID)->stoid == ((osv_oid_i *)SPOBID)->stoid)

#define STOID_BINARY_COPY(DEST_STOID, SORC_PSTOID) \
    (DEST_STOID) = ((osv_sid_i *)SORC_PSTOID)[0x00];

#define STOID_OBID_COPY(DEST_STOID, SORC_POBID) { \
    (DEST_STOID) = ((osv_oid_i *)SORC_POBID)->stoid; \
}

    //
    char *sidstr(char *stoid_stri, osv_sid_t *stoid);

    //
#define IS_ZERO_STOID(PSTOID) \
    (!((osv_sid_i *)PSTOID)[0x00])

#define NOT_ZERO_STOID(PSTOID) \
    (((osv_sid_i *)PSTOID)[0x00])

#define MAKE_ZERO_STOID(PSTOID) \
    ((osv_sid_i *)PSTOID)[0x00] = 0x00;

#ifdef __cplusplus
}
#endif

#endif /* STOID_H */



/* 
 * File:   debug_funct_osv.h
 * Author: James Xu
 *
 * Created on 2022.11.3, PM 10:04
 */

#ifndef DEBUG_FUNCT_OSV_H
#define DEBUG_FUNCT_OSV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "third_party.h"
#include "stoid.h"
#include "obid.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _DEBUG
#define OSEVPF printf
#else 
#define OSEVPF(fmt, ...)
#endif

    //

    struct test {
        osv_oid_i obje_obid;
        int xx;
        int ax;
        int cx;
    };

    //
    void p_test_object(struct test *obje);

#ifdef _DEBUG
#define PRIN_test_object p_test_object
#else
#define PRIN_test_object(...)
#endif

    // for debug
    void p_osv_oid_t_sid_stri(osv_oid_t *obje_obid, int size);
    void p_osv_oid_t_08X(osv_oid_t *obje_obid);
    void p_osv_oid_t_stri(osv_oid_t *obje_obid);
    void p_osv_sid_t_stri(osv_sid_t *obje_stoid);

#ifdef _DEBUG
#define PRIN_osv_oid_t_sid_stri   p_osv_oid_t_sid_stri
#define PRIN_osv_oid_t_08X   p_osv_oid_t_08X
#define PRIN_osv_oid_t_stri(OBJE_OBID)  p_osv_oid_t_stri((osv_oid_t *)OBJE_OBID)
#define PRIN_osv_sid_t_stri(OBJE_OBID)  p_osv_sid_t_stri((osv_sid_t *)OBJE_OBID)
#else
#define PRIN_osv_oid_t_sid_stri(...)
#define PRIN_osv_oid_t_08X(...)
#define PRIN_osv_oid_t_stri(...)
#define PRIN_osv_sid_t_stri(...)
#endif

    // for debug
    void p_stoid_stri(osv_sid_t *sid, int size);

#ifdef _DEBUG
#define PRIN_stoid_stri(SID, SIZE) p_stoid_stri((osv_sid_t *)SID, SIZE)
#else
#define PRIN_stoid_stri(...)
#endif

    // for debut

#ifdef __cplusplus
}
#endif

#endif /* DEBUG_FUNCT_OSV_H */


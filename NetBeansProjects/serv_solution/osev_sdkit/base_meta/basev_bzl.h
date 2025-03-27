
/* 
 * File:   basev_bzl.h
 * Author: James Xu
 *
 * Created on 2017.1.11, PM 2:25
 */

#ifndef BASEV_BZL_H
#define BASEV_BZL_H

#include <pthread.h>

#include "base_utili.h"
#include "base_cache.h"
#include "basev_obje.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int basebzl_create();
    int basebzl_destroy();

    //
    basv_list *open_blist_bzl(char *basen, uint32 lev_valu);
#define FIND_BLISTN_BZL(BASEN)     find_blstn(_base_cache_.base_list, BASEN)
#define FIND_BLISTO_BZL(BASE_OBID)    find_blsto(_base_cache_.base_list, BASE_OBID)

    //
#define CLOSE_BLIST_BZL(BLIST) base_cache_remove(&_base_cache_, BLIST);

    //
#define FIND_BADATN_BZL(BASEN)    FIND_BASEDA_NAME(BASEN)
#define FIND_BADATO_BZL(BASE_OBID)   FIND_BASEDA_OBID(BASE_OBID)

    //
#define GET_BLIST_BZL() _base_cache_.base_list

    // borro givbk
#define BORRO_BLIST_BZL(BLIST) { \
        pthread_mutex_lock(&_base_cache_mutex_); \
        BLIST = _base_cache_.base_list; \
    }

#define GIVBK_BLIST_BZL() \
        pthread_mutex_unlock(&_base_cache_mutex_);

    //
    // 0x00:ok -1:err
    int open_osev_bzl(osv_oid_t *base_obid, char *basen, uint32 lvmsk_code);
    // 0x00:ok -1:err
    int close_osev_bzl(char *basen);
    // 0x00:ok -1:err
    int open_base_bzl(osv_oid_t *base_obid, uint32 lvmsk_code);
    // 0x00:ok -1:err
    int close_base_bzl(osv_oid_t *base_obid);

    //
#define CREAT_OATTRI_BZL(OSEVN, OSEV_OBID, DATA_DIRECTORY) \
                            creat_osev_attri(OSEVN, OSEV_OBID, DATA_DIRECTORY)

#define PARSE_OATTRI_BZL(OSEVN, OSEV_OBID, DATA_DIRECTORY) \
                            parse_osev_attri(OSEVN, OSEV_OBID, DATA_DIRECTORY)

#define VALID_BCLEAN_BZL(BASEN) valid_base_clean(BASEN)

#ifdef __cplusplus
}
#endif

#endif /* BASEV_BZL_H */


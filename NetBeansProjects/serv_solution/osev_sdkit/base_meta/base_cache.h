
/* 
 * File:   base_cache.h
 * Author: James Xu
 *
 * Created on 2023.4.26, AM 10:41
 */

#ifndef BASE_CACHE_H
#define BASE_CACHE_H

#include "commo_header.h"
#include "kcomm_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    struct _basv_listmap_ {
        basv_list *base_list;
        cachemap *lv4pn_hm; // base name map
        cachemap *lv4po_hm; // base object id map
    };

    typedef struct _basv_listmap_ basv_lsmp;

    //

    inline void base_cache_remove(basv_lsmp *basv_ca, basv_list *blist) {
        base_valu *baval = &blist->basval;
        cache_remove(&baval->base_obid, basv_ca->lv4po_hm);
        cache_remove(baval->base_name, basv_ca->lv4pn_hm);
        dele_blist(&basv_ca->base_list, blist);
    }

    inline void base_cache_insert(basv_lsmp *basv_ca, basv_list *blist) {
        OSEVPF("[FUNC]: -------- base_cache_insert\n");
        base_valu *baval = &blist->basval;
        cache_insert(&baval->base_obid, (void *) baval, basv_ca->lv4po_hm);
        cache_insert(baval->base_name, (void *) baval, basv_ca->lv4pn_hm);
        APPEND_BASE_LIST(&basv_ca->base_list, blist)
#ifdef _DEBUG
                char obid_stri[OBJE_IDENTI_ZLEN];
        OSEVPF("baval->base_obid:|%s| baval->base_name:|%s|\n", oidstr(obid_stri, &baval->base_obid), baval->base_name);
#endif   
    }

    inline void base_cache_initi(basv_lsmp *basv_ca) {
        basv_ca->lv4pn_hm = creat_cache(BASE_BACKET_SIZE);
        basv_ca->lv4po_hm = creat_obid_cache(BASE_BACKET_SIZE);
        basv_ca->base_list = NULL;
    }

    inline void final_base_cache(basv_lsmp *basv_ca) {
        cache_destroy(basv_ca->lv4po_hm);
        cache_destroy(basv_ca->lv4pn_hm);
        dele_base_list(basv_ca->base_list);
    }

    //

#define FIND_BASEDA_NAME(BASEN) ((base_valu *) cache_value(BASEN, _base_cache_.lv4pn_hm))
    //
#define FIND_BASEDA_OBID(BASE_OBID) ((base_valu *) cache_value(BASE_OBID, _base_cache_.lv4po_hm))

#ifdef __cplusplus
}
#endif

#endif /* BASE_CACHE_H */


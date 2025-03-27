
/* 
 * File:   lv2p_meta.h
 * Author: James Xu
 *
 * Created on 2022.11.25, PM 2:36
 */

#ifndef LVTP_META_H
#define LVTP_META_H

//
#include "lv2p_expand.h"
#include "lv2p_attri.h"

//

#ifdef __cplusplus
extern "C" {
#endif

    struct _lv2pme_ {
        // meta
        osv_oid_t lv2p_obid; // lv2p object id
        char lv2pn[LVTN_LENGTH];
        char lv2p_fmtsd_tm[FMTST_COUNT_ZTAI]; // lv2p data format string
        unsigned char fixed_float_tm; // 0x00:fixed 0x01:float
        uint64 data_size;
        lv2p_expa_t *lv2expt;
        // attrib
    };

    typedef struct _lv2pme_ lv2pme;

    //

    inline lv2pme *mallo_lv2pme(lv2p_expa_t *lv2expt) {
        lv2pme *lv2me = (lv2pme *) malloc(sizeof (lv2pme));
        if (!lv2me) return NULL;
        lv2me->lv2expt = lv2expt;
        return lv2me;
    }

    //

    void dele_lv2pme(void *lv2me);

    // lv2p name map

    struct _lv2pm_hmap_ {
        // lv2p meta
        cachemap *lv2pmn_hm; // lv2p name map
        cachemap *lv2pmo_hm; // lv2p obid map
        // lv2p attrib
        cachemap *lv2pan_hm; // lv2p key:decl value:lv2pme:attrib map
        cachemap *lv2pao_hm; // lv2p key:obid value:lv2pme:attrib map
    };
    typedef struct _lv2pm_hmap_ lv2pm_hmap;

    // lev2p
#define LVTPM_CACHE_INITI(LVTPM, BACKET_SIZE) { \
    LVTPM.lv2pmn_hm = creat_cache(BACKET_SIZE); \
    LVTPM.lv2pmo_hm = creat_obid_cache(BACKET_SIZE); \
    LVTPM.lv2pan_hm = creat_cache(BACKET_SIZE); \
    LVTPM.lv2pao_hm = creat_obid_cache(BACKET_SIZE); \
}

    // 

#define FINAL_LVTPM_CACHE(LVTPM) { \
    cache_each_data(LVTPM.lv2pao_hm, dele_lv2pai); \
    cache_destroy(LVTPM.lv2pao_hm); \
    cache_destroy(LVTPM.lv2pan_hm); \
    cache_each_data(LVTPM.lv2pmo_hm, dele_lv2pme); \
    cache_destroy(LVTPM.lv2pmo_hm); \
    cache_destroy(LVTPM.lv2pmn_hm); \
}

    //

#ifdef __cplusplus
}
#endif

#endif /* LVTP_META_H */


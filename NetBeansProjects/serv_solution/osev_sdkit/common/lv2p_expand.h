
/* 
 * File:   lv2p_expand.h
 * Author: James Xu
 *
 * Created on 20211029, PM 4:23
 */

#ifndef LVTP_EXPAND_H
#define LVTP_EXPAND_H

#include <assert.h>

#include "osev_macro.h"
#include "lv2p_decla.h"

#ifdef __cplusplus
extern "C" {
#endif

    struct _lv2p_expa_i_ {
        int lv2o_coun;
        lv2p_prop lv2nod[LVTNOD_COUNT];
        int lv1d_coun;
        lev1_decl_i lv1dat[LEVO_COUNT];
    }; // parse class decla

    typedef struct _lv2p_expa_i_ lv2p_expa_i;

    // trans-serve

    struct _lv2p_expa_t_ {
        int lv2o_coun;
        lv2p_prop *lv2nod;
        int lv1d_coun;
        lev1_decl_t *lv1dat;
    }; // parse class decla

    typedef struct _lv2p_expa_t_ lv2p_expa_t;

    // maybe error, debug it
#define REDUCE_LEVET_EXPANT(LVTEXPT) { \
    LVTEXPT->lv2nod = (lv2p_prop *) REALLOC_NTAI(LVTEXPT->lv2nod, sizeof (lv2p_prop), LVTEXPT->lv2o_coun); \
    assert(LVTEXPT->lv2nod); \
    LVTEXPT->lv1dat = (lev1_decl_t *) REALLOC_NTAI(LVTEXPT->lv1dat, sizeof (lev1_decl_t), LVTEXPT->lv1d_coun); \
    assert(LVTEXPT->lv1dat); \
}

    //
    lv2p_expa_t *mallo_lv2exp(int lv2o_coun, int lv1d_coun);
    lv2p_expa_t *creat_lv2exp(lv2p_expa_i *lv2expi);
    // trans-serve

    inline void free_lv2exp(lv2p_expa_t *lv2expt) {
        if (lv2expt) {
            if (lv2expt->lv2nod) free(lv2expt->lv2nod);
            if (lv2expt->lv1dat) free(lv2expt->lv1dat);
            free(lv2expt);
        }
    }


#ifdef __cplusplus
}
#endif

#endif /* LVTP_EXPAND_H */


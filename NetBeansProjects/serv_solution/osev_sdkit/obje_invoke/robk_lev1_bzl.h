
/* 
 * File:   robk_lev1_bzl.h
 * Author: James Xu
 *
 * Created on 2021.11.14, PM3:55
 */

#ifndef ROBK_LEVO_BZL_H
#define ROBK_LEVO_BZL_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int robk_cream_bzl(lv2pm_hmap *lv2pm_stm, char *basen, lev1_meta *lev1m);

    //

    struct _replm_envir_ {
        char handn[HANDN_LENGTH];
        char lv2pn[LVTN_LENGTH];
        char lev1n[LVON_LENGTH];
        //
        CALLER_TYPE oivk_retyp_re;
        char oivk_fmtsp_re[FMTST_COUNT_ZTAI];
        int oivk_size_re;
        //
        int bakup_libra;
        char lev1_librn[LVON_LENGTH];
    };

    typedef struct _replm_envir_ replm_envir;
    typedef struct _replm_envir_ relom_envir;

    //

    int prote_replm_bzl(replm_envir *envrpm, hand_hmap *hando_stm, char *basen, lev1_meta *lev1m);
    void cancel_replm_bzl(hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *basen, replm_envir *envrpm);
    int robk_replm_bzl(hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *basen, replm_envir *envrpm);
    void destr_replm_bzl(replm_envir *envrpm, char *basen);

    //

    int prote_relom_bzl(relom_envir *envrlm, hand_hmap *hando_stm, char *basen, lev1_meta *lev1m);
    void cancel_relom_bzl(hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *basen, relom_envir *envrlm);
    int robk_relom_bzl(hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *basen, relom_envir *envrlm);
    void destr_relom_bzl(relom_envir *envrlm, char *basen);
    
#ifdef __cplusplus
}
#endif

#endif /* ROBK_LEVO_BZL_H */


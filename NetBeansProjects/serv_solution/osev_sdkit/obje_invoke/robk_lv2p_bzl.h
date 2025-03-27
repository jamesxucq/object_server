
/* 
 * File:   robk_lv2p_bzl.h
 * Author: James Xu
 *
 * Created on 2024.4.9, AM 10:08
 */

#ifndef ROBK_LVTP_BZL_H
#define ROBK_LVTP_BZL_H

#include "commo_header.h"
// #include "repla/repla_iteli.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int robk_creac_bzl(lv2pm_hmap *lv2pm_stm, char *basen, char *lv2pn);
    int robk_inhem_bzl(lv2pm_hmap *lv2pm_stm, hand_hmap *hando_stm, char *basen, lev1_decl_t *lv1d, char *robk_clas);

    // lv2pm_stm: lv2p_attri, lv2pme, updat_conte_lv2p
    // lv2_dec, lv2dt->lv2pn, &lv2dt->lv2p_obid, lv2expt: lv2d_path, lv2t_path, lv2e_path
    // replc_list: inher_replc_ite, integ_replc_ite

    struct _replc_envir_ {
        osv_oid_t lv2p_obid;
        // lv2d_path, lv2t_path, lv2e_path
        char lv2pn[LVTN_LENGTH];
        // lv2p_attri
        unsigned long long versio;
        bool_osv iexter;
        // lv2pme, conte_lv2p
        char lv2p_fmtsd_re[FMTST_COUNT_ZTAI]; // lv2p data format string
        unsigned char fixed_float_re; // 0x00:fixed 0x01:float
        uint64 data_size;
        lv2p_expa_t *lv2expt;
        // replc_list
        replc_list *replst;
    };

    typedef struct _replc_envir_ replc_envir;

    //

    int prote_replc_bzl(replc_envir *envrpc, lv2pm_hmap *lv2pm_stm, char *basen, lv2p_decl_t *lv2dt, replc_list *replst);
    void cancel_replc_bzl(replc_envir *envrpc, char *basen, lv2p_expa_t *lv2expt);
    int robk_replc_bzl(lv2pm_hmap *lv2pm_stm, char *basen, lv2p_expa_t *lv2expt, replc_envir *envrpm);
    void destr_replc_bzl(replc_envir *envrpm, char *basen);


#ifdef __cplusplus
}
#endif

#endif /* ROBK_LVTP_BZL_H */


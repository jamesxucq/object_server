
/* 
 * File:   conte_bzl.h
 * Author: James Xu
 *
 * Created on 2016.12.31, AM 8:37
 */

#ifndef CONTE_BZL_H
#define CONTE_BZL_H

#include "commo_header.h"
#include "nstri_utili.h"

#include "lev1_dlsym.h"
#include "lv2p_conte.h"
#include "lev1_conte.h"
// #include "robk_lv2p_bzl.h"
#include "robk_lev1_bzl.h"

#ifdef __cplusplus
extern "C" {
#endif

    //    int handbzl_create(char *data_directory);
    //    int handbzl_destroy();

    //
    int hcrea_imeth_bzl(respo_ctrl *resctl, char *libr_path, char *clang_cont, char *basen, lev1id *lev1i);
    int creat_ilv1me_bzl(hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *libr_path, char *basen, lev1id *lev1i);

    //
    int hcrea_metho_bzl(respo_ctrl *resctl, char *libr_path, char *clang_cont, char *basen, lev1_meta *lev1m);
    int creat_lv1me_bzl(hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *libr_path, char *basen, lev1_meta *lev1m);

    //
    int hrepl_metho_bzl(respo_ctrl *resctl, char *libr_path, char *clang_cont, char *basen, lev1_meta *lev1m);
    int repla_lv1me_bzl(hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *libr_path, char *basen, lev1_meta *lev1m);

    //
    int hcrea_class_bzl(respo_ctrl *resctl, char *libr_path, char *clang_cont, char *basen, char *lv2pn);
    int creat_lv2me_bzl(lv2pm_hmap *lv2pm_stm, char *basen, lv2p_decl_t *lv2dt, lv2p_expa_t *lv2expt);
    lv2pme *lv2in_lv2me_bzl(inst_hmap *insda_stm, lv2pm_hmap *lv2pm_stm, char *lv2_dec, lv2p_expa_t *lv2expt, osv_oid_t *lv2p_obid);
    int repla_lv2me_bzl(lv2pm_hmap *lv2pm_stm, char *basen, lv2p_decl_t *lv2dt, lv2p_expa_t *lv2expt);

    //
    int hdrop_class_bzl(lv2pm_hmap *lv2pm_stm, char *lv2pn);
    int hdrop_metho_bzl(hand_hmap *hando_stm, char *basen, lev1_meta *lev1m);

    //
    int relom_handl_bzl(respo_ctrl *resctl, hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *basen, char *lev1_librn, lev1_meta *lev1m);
    int relom_objec_bzl(respo_ctrl *resctl, char *basen, lev1_meta *lev1m, char *clang_cont);
    int relom_libra_bzl(respo_ctrl *resctl, char *basen, char *lev1_librn, lev1_list *l1lst);

    // int hrelo_class_bzl(respo_ctrl *resctl, lv2pm_hmap *lv2pm_stm, char *clang_cont, char *basen, char *lv2pn);
    int reloc_handl_bzl(respo_ctrl *resctl, lv2pm_hmap *lv2pm_stm, char *basen, lv2p_decl_t *lv2dt);
    int reloc_objec_bzl(respo_ctrl *resctl, char *basen, lv2p_decl_t *lv2dt, char *clang_cont);
    int reloc_libra_bzl(respo_ctrl *resctl, char *basen, char *lev1_librn, lv2p_list *l2lst);

    //
    int hload_lv2dat_bzl(basv_list *blist);
    int open_lv2dat_bzl(base_valu *baval, char *basen);
    int close_lv2dat_bzl(base_valu *baval, char *basen);

    //
#define CREAT_HATTR_BZL(BASEN) { \
    creat_lev1_conte(BASEN); \
    creat_lv2p_conte(BASEN); \
}

    //
    int robk_lv2p_bzl(lv2pm_hmap *lv2pm_stm, char *lv2pn);
    int robk_ilev1_bzl(hand_hmap *hando_stm, char *basen, lev1id *lev1i);

    // 0x00:hand refer zero. >0x00:refer number <0x00:error
    int close_l1hand_bzl(char *lev1_librn, hand_hmap *hando_stm, char *handn, char *basen, lev1_meta *lev1m);
    lev1me *open_l1hand_bzl(hand_hmap *hando_stm, replm_envir *envrpm, char *basen);


#ifdef __cplusplus
}
#endif

#endif /* CONTE_BZL_H */


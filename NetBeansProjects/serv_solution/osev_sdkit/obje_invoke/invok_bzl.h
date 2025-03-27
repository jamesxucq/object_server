
/* 
 * File:   invok_bzl.h
 * Author: James Xu
 *
 * Created on 2016.12.17, PM 2:16
 */

#ifndef INVOK_BZL_H
#define INVOK_BZL_H

#include "commo_header.h"
#include "lv2p_meta/lv2me_ite.h"
#include "invok_obje.h"
#include "trans/trans_ite.h"
#include "inheri/inheri_ite.h"
#include "integ/integ_ite.h"
#include "lv2p_list.h"
#include "recod_bzl.h"
#include "civalid/cvalid_ite.h"
#include "civalid/ivalid_ite.h"
#include "robk_lev1_bzl.h"
#include "repla/repla_ite.h"
#include "filli_clang.h"
#include "lev1_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    // int compbzl_create(char *data_directory);
    // int compbzl_destroy();

    // post
    // instru
#define CPOST_INSTRU_CLEAINST   0x00
#define CPOST_INSTRU_EXPLAIN    0x01
#define CPOST_INSTRU_REPLACE    0x02
    // #define CPOST_INSTRU_CLEAINST   0x01
    int cole_post_instru_bzl(respo_ctrl *resctl, base_valu *baval, uint32 postyp, char *attach);
#define IPOST_INSTRU_REPLACE    0x00
    int invk_post_instru_bzl(respo_ctrl *resctl, base_valu *baval, lv2p_attri *lv2ai, uint32 postyp, char *attach);

    // attrib
#define CPOST_ATTRIB_EXTERN   0x00
    // #define CPOST_ATTRIB_EXTERN   0x00
    // #define CPOST_ATTRIB_EXTERN   0x01
    int cole_post_attrib_bzl(respo_ctrl *resctl, base_valu *baval, char *lv2pn, uint32 postyp, uint32 value);
#define IPOST_ATTRIB_EXTERN   0x00
    int invk_post_attrib_bzl(respo_ctrl *resctl, base_valu *baval, lv2p_attri *lv2ai, uint32 postyp, uint32 value);

    // list
    int invk_stalst_bzl(respo_ctrl *resctl, char *basen, lev1_meta *lev1m);
    int invk_stasti_bzl(respo_ctrl *resctl, char *basen, char *lv2pn);
    int cole_stalst_lv2pn_bzl(respo_ctrl *resctl, lv2pm_hmap *lv2pm_stm, char *basen, char *lv2pn, uint32 list_layou);
    int cole_stalst_whole_bzl(respo_ctrl *resctl, char *basen);
    int cole_stasti_lv2po_bzl(respo_ctrl *resctl, base_valu *baval, osv_oid_t *lv2p_obid);
    int cole_stasti_lv2pn_bzl(respo_ctrl *resctl, char *basen, char *lv2pn);
    int cole_stasti_whole_bzl(respo_ctrl *resctl, char *basen);

    //
    int conv_meth_bzl(char *clang_cont, char *basen, lev1_meta *lev1m, char *lev1_cont);
    int conv_imet_bzl(char *clang_cont, char *basen, lev1id *lev1i, char *lev1_cont);
    int conv_ilv1_bzl(char *clang_cont, char *basen, lev1id *lev1i, char *lev1_cont);

    //
    int cole_creat_bzl(lv2p_expa_t *lv2expt, char *basen, lv2p_decl_t * lv2dt);
    int cole_repla_bzl(lv2p_expa_t *lv2expt, char *basen, lv2p_decl_t * lv2dt);
#define COLE_RELOA_BZL(CLANG_CONT, BASEN, LVTPD) class_clang_ite(CLANG_CONT, BASEN, LVTPD)

    //
    int invk_repla_bzl(char *clang_cont, char *basen, lev1_meta *lev1m, char *lev1_cont);
    int invk_reloa_bzl(char *clang_cont, char *basen, lev1_meta *lev1m);

    //
    int invk_drop_conte_bzl(char *basen, lev1_meta *lev1m);
    int cole_drop_conte_bzl(char *basen, char *lv2pn);

    //
    int split_cprop_bzl(char (*lv2p_prop)[PARAM_LENGTH], char *basen, char *lv2pn);

    //
#define BUILD_HANDN_BZL(HANDN, LEVOM) build_handl_name(HANDN, (LEVOM)->lv2pn, (LEVOM)->lev1n, (LEVOM)->oivk_fmtsp_om)
#define BUILD_IHANDN_BZL(HANDN, LEVOI) build_ihand_name(HANDN, (LEVOI)->crea_lv2pn, (LEVOI)->crea_lev1n, (LEVOI)->oivk_fmtsp_oi);

    //
#define LIST_LVTP_BZL(LVTP_ARRA, CLSA_LINE, DATA_PATH) list_clas(LVTP_ARRA, CLSA_LINE, DATA_PATH)

    //
#define FIND_LEVON_BZL(LOLSND, LEVON) find_l1cnod_name(LOLSND, LEVON)
#define FREE_LVOLST_BZL(LOLSND) { \
    l1clst_dele(LOLSND); \
    (LOLSND) = NULL; \
}

#ifdef __cplusplus
}
#endif

#endif /* INVOK_BZL_H */


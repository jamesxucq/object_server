
#include "commo_header.h"
#include "kcomm_header.h"
#include "lv2p_meta/lv2me_ite.h"
#include "lv2p_list.h"
#include "lv2p_decla.h"
#include "integ/integ_ite.h"
#include "conte_bzl.h"
#include "istri_utili.h"

#include "cfile_utili.h"
#include "invok_bzl.h"
#include "filli_clang.h"
#include "debug_funct_oi.h"
#include "kcomm_struct.h"

#include "robk_lev1_bzl.h"

//

int robk_cream_bzl(lv2pm_hmap *lv2pm_stm, char *basen, lev1_meta *lev1m) {
    OSEVPF("Start robk_cream_bzl .....\n");
    char lv2d_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2d_path, basen, lev1m->lv2pn);
    lv2p_decl_i lv2di;
    INIT_LVTP_DECL(lv2di)
    if (!parse_l2con_ite(&lv2di, lv2d_path)) RETU_DELM(lv2di, -1);
    //
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lev1m->lv2pn, lv2pm_stm->lv2pan_hm);
    if (!lv2ai) RETU_DELM(lv2di, -1);
    //
    lv1_cont *l1c_nod = dele_l1cnod_iden(&lv2di.l1con_list, lev1m->lev1n, lev1m->oivk_fmtsp_om);
    if (!l1c_nod) RETU_DELM(lv2di, -1);
    LVOCND_DELE(l1c_nod);
    // lv2ai.versio--;
    if (robk_integ_cream_ite(&lv2ai->integ_list, lev1m, INTE_NORM_METH)) RETU_DELM(lv2di, -1);
    char lv2t_path[MAX_PATH * 3];
    LVTP_ATTRI_FILE(lv2t_path, basen, lev1m->lv2pn)
    if (save_l2con_ite(lv2d_path, &lv2di, lv2t_path, lv2ai)) RETU_DELM(lv2di, -1);
    //
    CLAM_STRU_DELE(lv2di)
    OSEVPF("robk_cream_bzl end .....\n");
    return 0x00;
}

//

int prote_replm_bzl(replm_envir *envrpm, hand_hmap *hando_stm, char *basen, lev1_meta *lev1m) {
    OSEVPF("[FUNC]:prote_replm_bzl\n");
    // memset(envrpm, '\0', sizeof (replm_envir));
    BUILD_HANDN_BZL(envrpm->handn, lev1m);
    strcpy(envrpm->lv2pn, lev1m->lv2pn);
    strcpy(envrpm->lev1n, lev1m->lev1n);
    envrpm->oivk_retyp_re = lev1m->oivk_retyp_om;
    strcpy(envrpm->oivk_fmtsp_re, lev1m->oivk_fmtsp_om);
    envrpm->oivk_size_re = lev1m->oivk_size_om;
    //
    int delval = close_l1hand_bzl(envrpm->lev1_librn, hando_stm, envrpm->handn, basen, lev1m);
    if (0x00 > delval) return -1;
    else if (!delval) {
        envrpm->bakup_libra = 0x01;
        if (bakup_libra_file(basen, envrpm->lev1_librn))
            return -1;
    }
    //
    return 0x00;
}

void cancel_replm_bzl(hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *basen, replm_envir *envrpm) {
    if (envrpm->bakup_libra) {
        if (recov_libra_file(basen, envrpm->lev1_librn))
            return;
    }
    //
    lv2pme *lv2me = (lv2pme *) cache_value(envrpm->lv2pn, lv2pm_stm->lv2pmn_hm);
    if (!lv2me) return;
    lev1me *lv1me = open_l1hand_bzl(hando_stm, envrpm, basen);
    if (!lv1me) return;
    lv1me->lv2me = lv2me;
}

void destr_replm_bzl(replm_envir *envrpm, char *basen) {
    OSEVPF("[FUNC]:destr_replm_bzl\n");
    char libr_baku[MAX_PATH * 3];
    if (envrpm->bakup_libra) {
        LIBRARY_SUFFIX_FILE(libr_baku, basen, envrpm->lev1_librn, BAKUP_SUFFIX);
        unlink(libr_baku);
    }
}

int robk_replm_bzl(hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *basen, replm_envir *envrpm) {
    OSEVPF("Start robk_replm_bzl .....\n");
    if (envrpm->bakup_libra) {
        if (recov_libra_file(basen, envrpm->lev1_librn))
            return -1;
    }
    //
    lv2pme *lv2me = (lv2pme *) cache_value(envrpm->lv2pn, lv2pm_stm->lv2pmn_hm);
    if (!lv2me) return -1;
    lev1me *lv1me = open_l1hand_bzl(hando_stm, envrpm, basen);
    if (!lv1me) return -1;
    lv1me->lv2me = lv2me;
    //
    OSEVPF("End robk_replm_bzl .....\n");
    return 0x00;
}

//

int prote_relom_bzl(relom_envir *envrlm, hand_hmap *hando_stm, char *basen, lev1_meta *lev1m) {
    OSEVPF("[FUNC]:prote_relom_bzl\n");
    // memset(envrlm, '\0', sizeof (replm_envir));
    BUILD_HANDN_BZL(envrlm->handn, lev1m);
    strcpy(envrlm->lv2pn, lev1m->lv2pn);
    strcpy(envrlm->lev1n, lev1m->lev1n);
    envrlm->oivk_retyp_re = lev1m->oivk_retyp_om;
    strcpy(envrlm->oivk_fmtsp_re, lev1m->oivk_fmtsp_om);
    envrlm->oivk_size_re = lev1m->oivk_size_om;
    //
    int delval = close_l1hand_bzl(envrlm->lev1_librn, hando_stm, envrlm->handn, basen, lev1m);
    if (0x00 > delval) return -1;
    else if (!delval) {
        envrlm->bakup_libra = 0x01;
        if (bakup_libra_file(basen, envrlm->lev1_librn))
            return -1;
    }
    //
    return 0x00;
}

void cancel_relom_bzl(hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *basen, relom_envir *envrlm) {
    if (envrlm->bakup_libra) {
        if (recov_libra_file(basen, envrlm->lev1_librn))
            return;
    }
    //
    lv2pme *lv2me = (lv2pme *) cache_value(envrlm->lv2pn, lv2pm_stm->lv2pmn_hm);
    if (!lv2me) return;
    lev1me *lv1me = open_l1hand_bzl(hando_stm, envrlm, basen);
    if (!lv1me) return;
    lv1me->lv2me = lv2me;
}

void destr_relom_bzl(relom_envir *envrlm, char *basen) {
    OSEVPF("[FUNC]:destr_relom_bzl\n");
    char libr_baku[MAX_PATH * 3];
    if (envrlm->bakup_libra) {
        LIBRARY_SUFFIX_FILE(libr_baku, basen, envrlm->lev1_librn, BAKUP_SUFFIX);
        OSEVPF("libr_baku:|%s|\n", libr_baku);
        unlink(libr_baku);
    }
}

int robk_relom_bzl(hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *basen, relom_envir *envrlm) {
    OSEVPF("Start robk_relom_bzl .....\n");
    if (envrlm->bakup_libra) {
        if (recov_libra_file(basen, envrlm->lev1_librn))
            return -1;
    }
    //
    lv2pme *lv2me = (lv2pme *) cache_value(envrlm->lv2pn, lv2pm_stm->lv2pmn_hm);
    if (!lv2me) return -1;
    lev1me *lv1me = open_l1hand_bzl(hando_stm, envrlm, basen);
    if (!lv1me) return -1;
    lv1me->lv2me = lv2me;
    //
    OSEVPF("End robk_relom_bzl .....\n");
    return 0x00;
}

//

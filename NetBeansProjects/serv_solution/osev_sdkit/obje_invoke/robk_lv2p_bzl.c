
#include "commo_header.h"
#include "kcomm_header.h"

#include "repla/repla_ite.h"
#include "reqin_ite.h"

#include "lv2p_meta/lv2me_ite.h"
#include "lv2p_list.h"
#include "lv2p_decla.h"
#include "integ/integ_ite.h"
#include "conte_bzl.h"
#include "istri_utili.h"
#include "reqin_bzl.h"

#include "cfile_utili.h"
#include "invok_bzl.h"
#include "filli_clang.h"
#include "debug_funct_oi.h"
#include "kcomm_struct.h"


#include "robk_lv2p_bzl.h"

//

int robk_creac_bzl(lv2pm_hmap *lv2pm_stm, char *basen, char *lv2pn) {
    OSEVPF("Start robk_creac_bzl .....\n");
    robk_lv2p_bzl(lv2pm_stm, lv2pn);
    //
    delet_conte_lv2p(lv2pn, basen);
    delet_lv2me_ite(basen, lv2pn);
    //
    OSEVPF("End robk_creac_bzl .....\n");
    return 0x00;
}

//

int robk_inhem_bzl(lv2pm_hmap *lv2pm_stm, hand_hmap *hando_stm, char *basen, lev1_decl_t *lv1d, char *robk_clas) {
    OSEVPF("Start robk_inhem_bzl .....\n");
    lv1_cont *l1con_list = NULL, *l1lsnd;
    lev1id robk_lev1i;
    char lv2t_path[MAX_PATH * 3];
    lv2p_attri *lv2ai;
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        if (LVTP_NORM_METH == lv1d->levtyp) continue;
        // OSEVPF("levtyp:|%08X| robk_clas:|%s| lv2pn:|%s| inhe_lv2n:|%s| ident:|%s| fmtsp:|%s|\n", lv1d->levtyp, robk_clas, lv1d->lv2pn, lv1d->inhe_lv2n[0x00], lv1d->ident, lv1d->innep.inne_fmtsp);
        strcpy(robk_lev1i.crea_lv2pn, robk_clas);
        if (!build_l2meth_ite(&l1con_list, basen, robk_lev1i.supe_lv2pn)) {
            l1lsnd = FIND_LEVON_BZL(l1con_list, lv1d->ident);
            for (; l1lsnd; l1lsnd = FIND_LEVON_BZL(l1lsnd->next, lv1d->ident)) {
                build_clev1i_lev1d(&robk_lev1i, lv1d, lv1d->ident, l1lsnd);
                PRIN_lev1id(&robk_lev1i);
                robk_ilev1_bzl(hando_stm, basen, &robk_lev1i);
            }
            FREE_LVOLST_BZL(l1con_list);
        }
        //
        if (LVTP_INHE_LVTP == lv1d->levtyp) {
            // strcpy(lv2pn, lv1d->ident);
            lv2ai = (lv2p_attri *) cache_value(lv1d->ident, lv2pm_stm->lv2pan_hm);
            if (!lv2ai) continue;
        } else {
            // strcpy(lv2ai->lv2pn, last_lv2pn(lv1d->inhe_lv2n));
            lv2ai = (lv2p_attri *) cache_value(last_lv2pn(lv1d->inhe_lv2n), lv2pm_stm->lv2pan_hm);
            if (!lv2ai) continue;
        }
        // OSEVPF("lv2ai.lv2pn:|%s|\n", lv2ai.lv2pn);
        inherit *innod = NULL;
        switch (lv1d->levtyp) {
            case LVTP_INHE_METH:
                innod = dele_inhe_meth(&lv2ai->inher_list, robk_clas, lv1d->ident);
                break;
            case LVTP_INHE_LEVO:
                innod = dele_inhe_lev1(&lv2ai->inher_list, robk_clas, lv1d->ident);
                break;
            case LVTP_INHE_LVTP:
                innod = dele_inhe_lv2p(&lv2ai->inher_list, robk_clas);
                break;
            case LVTP_INHE_CLAS:
                innod = dele_inhe_clas(&lv2ai->inher_list, robk_clas);
                break;
        }
        if (!innod) continue;
        IMETH_DELET(innod);
        //
        LVTP_ATTRI_FILE(lv2t_path, basen, lv2ai->lv2pn)
        if (save_l2att_ite(lv2t_path, lv2ai))
            continue;
    }
    //
    OSEVPF("End robk_inhem_bzl .....\n");
    return 0x00;
}

//

int prote_replc_bzl(replc_envir *envrpc, lv2pm_hmap *lv2pm_stm, char *basen, lv2p_decl_t *lv2dt, replc_list *replst) {
    OSEVPF("[FUNC]:prote_replc_bzl\n");
    // memset(envrpc, '\0', sizeof (replc_envir));
    strcpy(envrpc->lv2pn, lv2dt->lv2pn);
    envrpc->replst = replst;
    //
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lv2dt->lv2pn, lv2pm_stm->lv2pan_hm);
    if (!lv2ai) return -1;
    lv2pme * lv2me = (lv2pme *) cache_value(lv2dt->lv2pn, lv2pm_stm->lv2pmn_hm);
    if (!lv2me) return -1;
    //
    OBID_BINARY_COPY(&envrpc->lv2p_obid, &lv2me->lv2p_obid);
    // lv2p_attri
    envrpc->versio = lv2ai->versio;
    envrpc->iexter = lv2ai->iexter;
    // lv2pme, conte_lv2p
    strcpy(envrpc->lv2p_fmtsd_re, lv2me->lv2p_fmtsd_tm);
    envrpc->fixed_float_re = lv2me->fixed_float_tm;
    envrpc->data_size = lv2me->data_size;
    envrpc->lv2expt = lv2me->lv2expt;
    // backup: lv2d_path, lv2t_path, lv2e_path
    if (creat_l2mbkp_ite(basen, lv2dt->lv2pn))
        return -1;
    //
    return 0x00;
}

void cancel_replc_bzl(replc_envir *envrpc, char *basen, lv2p_expa_t *lv2expt) {
    // delete: lv2d_path, lv2t_path, lv2e_path
    delet_l2mbkp_ite(basen, envrpc->lv2pn);
    //
    dele_replc_list(envrpc->replst);
    free_lv2exp(lv2expt);
}

void destr_replc_bzl(replc_envir *envrpc, char *basen) {
    // delete: lv2d_path, lv2t_path, lv2e_path
    delet_l2mbkp_ite(basen, envrpc->lv2pn);
    //
    dele_replc_list(envrpc->replst);
    free_lv2exp(envrpc->lv2expt);
}

int robk_replc_bzl(lv2pm_hmap *lv2pm_stm, char *basen, lv2p_expa_t *lv2expt, replc_envir *envrpc) {
    OSEVPF("Start robk_replc_bzl .....\n");
    //
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(&envrpc->lv2p_obid, lv2pm_stm->lv2pao_hm);
    if (!lv2ai) return -1;
    lv2pme * lv2me = (lv2pme *) cache_value(&envrpc->lv2p_obid, lv2pm_stm->lv2pmo_hm);
    if (!lv2me) return -1;
    // lv2p_attri
    lv2ai->versio = envrpc->versio;
    lv2ai->iexter = envrpc->iexter;
    // lv2pme, conte_lv2p
    strcpy(lv2me->lv2p_fmtsd_tm, envrpc->lv2p_fmtsd_re);
    lv2me->fixed_float_tm = envrpc->fixed_float_re;
    lv2me->data_size = envrpc->data_size;
    lv2me->lv2expt = envrpc->lv2expt;
    if (updat_conte_lv2p(&lv2me->lv2p_obid, lv2me->lv2p_fmtsd_tm, lv2me->data_size, basen))
        return -1;
    // recovery: lv2d_path, lv2t_path, lv2e_path
    if (recov_l2mbkp_ite(basen, envrpc->lv2pn))
        return -1;
    //
    ROBK_REPLC_INHINT_ITE(lv2pm_stm, basen, envrpc->replst);
    dele_replc_list(envrpc->replst);
    free_lv2exp(lv2expt);
    //
    OSEVPF("End robk_replm_bzl .....\n");
    return 0x00;
}

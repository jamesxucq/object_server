
#include "commo_header.h"
#include "kcomm_header.h"
#include "conte_bzl.h"
#include "invok_bzl.h"
#include "lv2p_list.h"
#include "invok_bzl.h"
#include "robk_lv2p_bzl.h"
#include "istri_utili.h"

#include "lev1_decla.h"
#include "debug_funct_ci.h"
#include "lv2p_expand.h"
#include "colle_utili.h"

//

int creat_class_conte(respo_ctrl *resctl, lv2pm_hmap *lv2pm_stm, char *basen, lv2p_decl_t *lv2dt, char *lv2p_cont) {
    OSEVPF("[FUNC]:creat_class_conte\n");
    OSEVPF("lv2p_cont:|%s|\n", lv2p_cont);
    lv2p_expa_t *lv2expt = mallo_lv2exp(LVTNOD_COUNT, LEVO_COUNT);
    if (!lv2expt) {
        OSEVPF("Conve class excep!\n");
        PDAT_EXCEPTIO_TAIL(resctl, MALLO_LVTEXP_EXPT)
        return -1;
    }
    if (cole_creat_bzl(lv2expt, basen, lv2dt)) {
        OSEVPF("Conve class excep!\n");
        free_lv2exp(lv2expt);
        PDAT_EXCEPTIO_TAIL(resctl, CREAT_COLLE_EXPT)
        return -1;
    }
    REDUCE_LEVET_EXPANT(lv2expt);
    //
    if (creat_lv2me_bzl(lv2pm_stm, basen, lv2dt, lv2expt)) {
        OSEVPF("Creat class meta excep!\n");
        free_lv2exp(lv2expt);
        PDAT_EXCEPTIO_TAIL(resctl, CREAT_LVTME_EXPT)
        return -1;
    }
    //
    if (recod_creac_bzl(basen, lv2dt, lv2p_cont, lv2expt)) {
        OSEVPF("Recod creat class excep!\n");
        PDAT_EXCEPTIO_TAIL(resctl, COMPI_COLLE_EXPT)
        return -1;
    }
    //
    return 0x00;
}

//

int creat_inher_integ(respo_ctrl *resctl, hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *basen, lv2p_decl_t *lv2dt) {
    OSEVPF("[FUNC]:***** creat_inher_integ. *****\n");
    lev1id crea_lev1i;
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lv2dt->lv2pn, lv2pm_stm->lv2pan_hm);
    if (!lv2ai) return -1;
    // integra *inte_list = NULL;
    lev1_decl_t *lv1d = lv2dt->meth;
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        OSEVPF("--- crea_lev1i.lv2pn:|%s|, lv2pn:|%s|, ident:|%s|\n", lv2dt->lv2pn, lv1d->inhe_lv2n[0x00], lv1d->ident);
        if (LVTP_INHE_METH & lv1d->levtyp) {
            strcpy(crea_lev1i.crea_lv2pn, lv2dt->lv2pn);
            if (inher_meth_ite(resctl, hando_stm, lv2pm_stm, basen, lv1d, &crea_lev1i)) {
                olist_dele(lv2ai->integ_list);
                return -1;
            }
        } else if (LVTP_INHE_LEVO & lv1d->levtyp) {
            strcpy(crea_lev1i.crea_lv2pn, lv2dt->lv2pn);
            if (inher_lev1_ite(resctl, hando_stm, lv2pm_stm, basen, lv1d, &crea_lev1i)) {
                olist_dele(lv2ai->integ_list);
                return -1;
            }
        } else if (LVTP_INHE_LVTP & lv1d->levtyp) {
            strcpy(crea_lev1i.crea_lv2pn, lv2dt->lv2pn);
            if (inher_lv2p_ite(resctl, hando_stm, lv2pm_stm, basen, lv1d, &crea_lev1i)) {
                olist_dele(lv2ai->integ_list);
                return -1;
            }
        } else if (LVTP_INHE_CLAS & lv1d->levtyp) {
            strcpy(crea_lev1i.crea_lv2pn, lv2dt->lv2pn);
            if (inher_clas_ite(resctl, hando_stm, lv2pm_stm, basen, lv1d, &crea_lev1i)) {
                olist_dele(lv2ai->integ_list);
                return -1;
            }
        } else if (LVTP_NORM_METH & lv1d->levtyp) {
            if (integ_creac_ite(&lv2ai->integ_list, lv1d, INTE_NORM_METH)) {
                OSEVPF("Integ list excep!\n");
                olist_dele(lv2ai->integ_list);
                PDAT_EXCEPTIO_TAIL(resctl, CREAT_COLLE_EXPT)
                return -1;
            }
        }
    }
    //
    if (integ_updat_ite(lv2dt->lv2pn, basen, lv2ai)) {
        OSEVPF("Update integ excep!\n");
        olist_dele(lv2ai->integ_list);
        PDAT_EXCEPTIO_TAIL(resctl, CREAT_COLLE_EXPT)
        return -1;
    }
    //
    return 0x00;
}

//

static int relo_clas_hand(respo_ctrl *resctl, lv2pm_hmap *lv2pm_stm, char *basen, lv2p_list *l2lst) {
    for (; l2lst; l2lst = l2lst->next) {
        if (reloc_handl_bzl(resctl, lv2pm_stm, basen, &l2lst->lv2dt)) {
            return -1;
        }
        if (integ_reloc_ite(lv2pm_stm, basen, &l2lst->lv2dt)) {
            PDAT_EXCEPTIO_TAIL(resctl, RELOA_LVTP_EXPT)
            return -1;
        }
    }
    //
    return 0x00;
}

//

int reloc_clasn(respo_ctrl *resctl, lv2pm_hmap *lv2pm_stm, char *basen, char *lv2pn) {
    OSEVPF("[FUNC]:reloc_clasn, lv2pn:|%s|\n", lv2pn);
    if (valid_reloc_ite(basen, lv2pn)) {
        PDAT_EXCEPTIO_TAIL(resctl, LVTP_NOT_FOUND);
        return -1;
    }
    //
    lv2p_list *l2lst = NULL;
    if (lv2p_list_clas(&l2lst, basen, lv2pn)) {
        PDAT_EXCEPTIO_TAIL(resctl, RELOA_COLLE_DECL)
        return -1;
    }
    // char lv2p_librn[MAX_PATH * 3];
    // librn_clasn_lv2p(lv2p_librn, lv2pn);
    // if (produ_reloc_libra(resctl, basen, lev2_librn, l2lst)) {
    // dele_lv2p_list(l2lst);
    // return -1;
    // }
    if (relo_clas_hand(resctl, lv2pm_stm, basen, l2lst)) {
        dele_lv2p_list(l2lst);
        return -1;
    }
    //
    dele_lv2p_list(l2lst);
    return 0x00;
}

int reloc_whole(respo_ctrl *resctl, lv2pm_hmap *lv2pm_stm, char *basen) {
    OSEVPF("[FUNC]:reloc_whole\n");
    lv2p_list *l2lst = NULL;
    if (lv2p_list_whol(&l2lst, basen)) {
        PDAT_EXCEPTIO_TAIL(resctl, RELOA_COLLE_DECL)
        return -1;
    }
    // char lv2p_librn[MAX_PATH * 3];
    // librn_whole_lv2p(lv2p_librn);
    // if (produ_reloc_libra(resctl, basen, lev2_librn, l2lst)) {
    // dele_lv2p_list(l2lst);
    // return -1;
    // }
    if (relo_clas_hand(resctl, lv2pm_stm, basen, l2lst)) {
        dele_lv2p_list(l2lst);
        return -1;
    }
    //
    dele_lv2p_list(l2lst);
    return 0x00;
}

// 

int replc_inher_integ(lv2pm_hmap *lv2pm_stm, char *basen, replc_list *replst) {
    OSEVPF("[FUNC]:replc_inher_integ\n");
    if (inher_replc_ite(lv2pm_stm, basen, replst))
        return -1;
    if (integ_replc_ite(lv2pm_stm, basen, replst))
        return -1;
    //
    return 0x00;
}

int robk_replc_inher_integ(lv2pm_hmap *lv2pm_stm, char *basen, replc_list *replst) {
    OSEVPF("[FUNC]:replc_inher_integ\n");
    if (robk_inher_replc_ite(lv2pm_stm, basen, replst))
        return -1;
    if (robk_integ_replc_ite(lv2pm_stm, basen, replst))
        return -1;
    //
    return 0x00;
}
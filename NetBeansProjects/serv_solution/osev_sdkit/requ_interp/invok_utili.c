
#include "commo_header.h"
#include "kcomm_header.h"

#include "conte_bzl.h"
#include "invok_bzl.h"
#include "robk_lev1_bzl.h"
#include "civalid/cvalid_ite.h"
#include "civalid/ivalid_ite.h"
#include "istri_utili.h"

#include "invok_utili.h"
#include "debug_funct_ci.h"

//

static int produ_relom_libra(respo_ctrl *resctl, char *basen, char *lev1_librn, lev1_list *l1lst) {
    OSEVPF("[FUNC]:produ_relom_libra\n");
    char clang_cont[CLANG_CONTE_SIZE];
    lev1_list *l1nod = l1lst;
    //
    for (; l1nod; l1nod = l1nod->next) {
        MK_ZERO(clang_cont);
        if (invk_reloa_bzl(clang_cont, basen, &l1nod->lev1m)) {
            ulink_relom_objec(basen, l1lst);
            PDAT_EXCEPTIO_TAIL(resctl, RELOA_INVOK_CLANG)
            return -1;
        }
        if (relom_objec_bzl(resctl, basen, &l1nod->lev1m, clang_cont)) {
            ulink_relom_objec(basen, l1lst);
            return -1;
        }
    }
    //
    if (relom_libra_bzl(resctl, basen, lev1_librn, l1lst)) {
        ulink_relom_objec(basen, l1lst);
        return -1;
    }
    //
    ulink_relom_objec(basen, l1lst);
    return 0x00;
}

//

static int relo_meth_hand(respo_ctrl *resctl, hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *basen, char *lev1_librn, lev1_list *l1lst) {
    OSEVPF("[FUNC]:relo_meth_hand\n");
    relom_envir envrlm;
    //
    for (; l1lst; l1lst = l1lst->next) {
        if (prote_relom_bzl(&envrlm, hando_stm, basen, &l1lst->lev1m)) {
            cancel_relom_bzl(hando_stm, lv2pm_stm, basen, &envrlm);
            PDAT_EXCEPTIO_TAIL(resctl, RELOA_INVOK_PROTE)
            return -1;
        }
        PRIN_relom_envir(&envrlm);
        if (relom_handl_bzl(resctl, hando_stm, lv2pm_stm, basen, lev1_librn, &l1lst->lev1m)) {
            robk_relom_bzl(hando_stm, lv2pm_stm, basen, &envrlm);
            return -1;
        }
        if (integ_relom_ite(lv2pm_stm, basen, &l1lst->lev1m)) {
            robk_relom_bzl(hando_stm, lv2pm_stm, basen, &envrlm);
            PDAT_EXCEPTIO_TAIL(resctl, RELOA_INVOK_INTEG)
            return -1;
        }
        destr_relom_bzl(&envrlm, basen);
    }
    //
    return 0x00;
}

int relom_decla(respo_ctrl *resctl, hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *basen, lev1_meta *lev1m) {
    OSEVPF("[FUNC]:relom_decla\n");
    if (valid_rlmde_ite(basen, lev1m)) {
        PDAT_EXCEPTIO_TAIL(resctl, INVOK_NOT_FOUND)
        return -1;
    }
    //
    lev1_list *l1lst = NULL;
    if (!appe_lev1_meta(&l1lst, lev1m)) {
        PDAT_EXCEPTIO_TAIL(resctl, RELOA_INVOK_DECL)
        return -1;
    }
    //
    char lev1_librn[MAX_PATH * 3];
    librn_decla_lev1(lev1_librn, lev1m);
    if (produ_relom_libra(resctl, basen, lev1_librn, l1lst)) {
        dele_lev1_list(l1lst);
        return -1;
    }
    if (relo_meth_hand(resctl, hando_stm, lv2pm_stm, basen, lev1_librn, l1lst)) {
        dele_lev1_list(l1lst);
        return -1;
    }
    //
    dele_lev1_list(l1lst);
    return 0x00;
}

//

int relom_metho(respo_ctrl *resctl, hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *basen, lev1_meta *lev1m) {
    OSEVPF("[FUNC]:relom_metho\n");
    if (valid_rlmme_ite(basen, lev1m)) {
        PDAT_EXCEPTIO_TAIL(resctl, INVOK_NOT_FOUND)
        return -1;
    }
    //
    lev1_list *l1lst = NULL;
    if (lev1_list_meth(&l1lst, basen, lev1m->lv2pn, lev1m->lev1n)) {
        PDAT_EXCEPTIO_TAIL(resctl, RELOA_INVOK_EXPT)
        return -1;
    }
    //
    char lev1_librn[MAX_PATH * 3];
    librn_metho_lev1(lev1_librn, lev1m);
    if (produ_relom_libra(resctl, basen, lev1_librn, l1lst)) {
        dele_lev1_list(l1lst);
        return -1;
    }
    if (relo_meth_hand(resctl, hando_stm, lv2pm_stm, basen, lev1_librn, l1lst)) {
        dele_lev1_list(l1lst);
        return -1;
    }
    //
    dele_lev1_list(l1lst);
    return 0x00;
}

int relom_clasn(respo_ctrl *resctl, hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *basen, lev1_meta *lev1m) {
    OSEVPF("[FUNC]:relom_clasn\n");
    if (valid_rlmcl_ite(basen, lev1m)) {
        PDAT_EXCEPTIO_TAIL(resctl, INVOK_NOT_FOUND)
        return -1;
    }
    //
    lev1_list *l1lst = NULL;
    if (lev1_list_clas(&l1lst, basen, lev1m->lv2pn)) {
        PDAT_EXCEPTIO_TAIL(resctl, RELOA_INVOK_EXPT)
        return -1;
    }
    //
    char lev1_librn[MAX_PATH * 3];
    librn_clasn_lev1(lev1_librn, lev1m->lv2pn);
    if (produ_relom_libra(resctl, basen, lev1_librn, l1lst)) {
        dele_lev1_list(l1lst);
        return -1;
    }
    if (relo_meth_hand(resctl, hando_stm, lv2pm_stm, basen, lev1_librn, l1lst)) {
        dele_lev1_list(l1lst);
        return -1;
    }
    //
    dele_lev1_list(l1lst);
    return 0x00;
}

int relom_whole(respo_ctrl *resctl, hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *basen) {
    OSEVPF("[FUNC]:relom_whole\n");
    lev1_list *l1lst = NULL;
    if (lev1_list_whol(&l1lst, basen)) {
        PDAT_EXCEPTIO_TAIL(resctl, RELOA_INVOK_EXPT)
        return -1;
    }
    //
    char lev1_librn[MAX_PATH * 3];
    librn_whole_lev1(lev1_librn);
    if (produ_relom_libra(resctl, basen, lev1_librn, l1lst)) {
        dele_lev1_list(l1lst);
        return -1;
    }
    if (relo_meth_hand(resctl, hando_stm, lv2pm_stm, basen, lev1_librn, l1lst)) {
        dele_lev1_list(l1lst);
        return -1;
    }
    //
    dele_lev1_list(l1lst);
    return 0x00;
}


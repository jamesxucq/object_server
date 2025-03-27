#include "commo_header.h"
#include "kcomm_header.h"

#include "basev_bzl.h"
#include "lv2p_meta/lv2me_ite.h"
#include "integ/integ_ite.h"
#include "repla/repla_ite.h"
#include "query_bzl.h"
#include "ivalid_utili.h"
#include "inheri/inheri_ite.h"
#include "trans/trans_ite.h"

#include "lev1_decla.h"
#include "invok_bzl.h"
#include "civalid/ivalid_ite.h"

// lev1 check create method

int valid_cream_ite(char *basen, char *lv2pn, lev1_meta *lev1m) {
    if (!(HAVE_CLASN & lev1m->layout)
            || !(HAVE_METHN & lev1m->layout)
            || !(HAVE_DECLA & lev1m->layout)
            || !(HAVE_BODY & lev1m->layout))
        return -1;
    if (strcmp(lv2pn, lev1m->lv2pn))
        return -1;
    OSEVPF("lev1m->lv2pn:|%s|\n", lev1m->lv2pn);
    char lv2d_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2d_path, basen, lev1m->lv2pn);
    lv1_cont *l1con_list = NULL;
    if (parse_l2meth_ite(&l1con_list, lv2d_path))
        return -1;
    //
    if (find_l1cnod_iden(l1con_list, lev1m->lev1n, lev1m->oivk_fmtsp_om)) {
        l1clst_dele(l1con_list);
        return -1;
    }
    l1clst_dele(l1con_list);
    //
    lev1_decl_t lev1d[LEVO_COUNT];
    if (parse_lev1d_clasp(lev1d, lv2d_path)) {
        OSEVPF("Parse lev1d clasp excep!\n");
        return -1;
    }
    if (chk_ibind_ite(lev1d, lev1m))
        return -1;
    OSEVPF("PASSED, valid_cream_ite\n");
    return 0x00;
}

int valid_replm_ite(char *basen, char *lv2pn, lev1_meta * lev1m, uint32 *forced) {
    if (!(HAVE_CLASN & lev1m->layout)
            || !(HAVE_METHN & lev1m->layout)
            || !(HAVE_DECLA & lev1m->layout)
            || !(HAVE_BODY & lev1m->layout))
        return -1;
    if (strcmp(lv2pn, lev1m->lv2pn))
        return -1;
    //
    char lv2d_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2d_path, basen, lev1m->lv2pn);
    lv1_cont *l1con_list = NULL;
    if (parse_l2meth_ite(&l1con_list, lv2d_path))
        return -1;
    if (!find_l1cnod_iden(l1con_list, lev1m->lev1n, lev1m->oivk_fmtsp_om)) {
        l1clst_dele(l1con_list);
        return -1;
    }
    l1clst_dele(l1con_list);
    //
    lev1_decl_t lev1d[LEVO_COUNT];
    if (parse_lev1d_clasp(lev1d, lv2d_path)) {
        OSEVPF("Parse lev1d clasp excep!\n");
        return -1;
    }
    if (chk_ibind_ite(lev1d, lev1m))
        return -1;
    // check external
    OSEVPF("check external\n");
    if (!(forced && forced[0x00])) {
        if (valid_iextem_ite(basen, lev1m->lv2pn, lev1m->lev1n))
            return -1;
    }
    OSEVPF("PASSED, valid_replm_ite\n");
    return 0x00;
}

//

int valid_dropm_ite(respo_ctrl *resctl, char *basen, char *lv2pn, lev1_meta * lev1m) {
    OSEVPF("valid_dropm_ite\n");
    if (!(HAVE_CLASN & lev1m->layout)
            || !(HAVE_METHN & lev1m->layout)
            || !(HAVE_DECLA & lev1m->layout)) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    if (strcmp(lv2pn, lev1m->lv2pn)) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        return -1;
    }
    //
    lv1_cont *l1con_list = NULL;
    if (build_l2meth_ite(&l1con_list, basen, lev1m->lv2pn))
        return -1;
    OSEVPF("2a\n");
    if (!find_l1cnod_iden(l1con_list, lev1m->lev1n, lev1m->oivk_fmtsp_om)) {
        l1clst_dele(l1con_list);
        return -1;
    }
    l1clst_dele(l1con_list);
    //
    inherit *inhe_list = NULL;
    if (build_inhlst_ite(&inhe_list, basen, lev1m->lv2pn)) {
        PDAT_EXCEPTIO_TAIL(resctl, LVTP_INHER_EXPT);
        return -1;
    }
    inherit * innod = find_inher_iden(inhe_list, lev1m->lv2pn, lev1m->lev1n);
    if (innod) {
        ilist_dele(inhe_list);
        PDAT_EXCEPTIO_TAIL(resctl, LVTP_INHER_EXPT);
        return -1;
    }
    ilist_dele(inhe_list);
    //
    OSEVPF("PASSED, valid_dropm_ite\n");
    return 0x00;
}

//

int valid_intem_ite(char *basen, char *lv2pn, lev1_meta * lev1m) {
    if (!(HAVE_CLASN & lev1m->layout)
            || (HAVE_DECLA & lev1m->layout))
        return -1;
    if (strcmp(lv2pn, lev1m->lv2pn))
        return -1;
    // HAVE_CLASN
    lev1_decl_t lev1d[LEVO_COUNT];
    if (parse_lev1d_clasn(lev1d, basen, lev1m->lv2pn)) {
        OSEVPF("parse lev1d clasp excep!\n");
        return -1;
    }
    // OSEVPF("1a\n");
    if (HAVE_METHN & lev1m->layout) {
        if (!find_lev1d_iden(lev1d, lev1m->lv2pn, lev1m->lev1n))
            return -1;
    }
    OSEVPF("PASSED, valid_intem_ite\n");
    return 0x00;
}

int valid_statm_list_ite(char *basen, char *lv2pn, lev1_meta * lev1m) {
    OSEVPF("valid_statm_list_ite\n");
    if (!(HAVE_CLASN & lev1m->layout))
        return -1;
    if (strcmp(lv2pn, lev1m->lv2pn))
        return -1;
    //
    lv1_cont *l1con_list = NULL;
    // HAVE_CLASN
    if (build_l2meth_ite(&l1con_list, basen, lev1m->lv2pn))
        return -1;
    //
    if (HAVE_DECLA & lev1m->layout) {
        if (!find_l1cnod_iden(l1con_list, lev1m->lev1n, lev1m->oivk_fmtsp_om)) {
            l1clst_dele(l1con_list);
            return -1;
        }
    } else if (HAVE_METHN & lev1m->layout) {
        if (!find_l1cnod_name(l1con_list, lev1m->lev1n)) {
            l1clst_dele(l1con_list);
            return -1;
        }
    }
    l1clst_dele(l1con_list);
    //
    OSEVPF("PASSED, valid_statm_list_ite\n");
    return 0x00;
}

//

int valid_statm_stati_ite(char *basen, char *lv2pn) {
    char lv2d_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2d_path, basen, lv2pn);
    if (CLASS_EXIST(lv2d_path)) return -1;
    OSEVPF("PASSED, valid_statm_list_ite\n");
    return 0x00;
}

//

int valid_rlmde_ite(char *basen, lev1_meta * lev1m) {
    lv1_cont *l1con_list = NULL;
    if (build_l2meth_ite(&l1con_list, basen, lev1m->lv2pn))
        return -1;
    if (!find_l1cnod_iden(l1con_list, lev1m->lev1n, lev1m->oivk_fmtsp_om)) {
        l1clst_dele(l1con_list);
        return -1;
    }
    l1clst_dele(l1con_list);
    OSEVPF("PASSED, valid_rlmde_ite\n");
    return 0x00;
}

int valid_rlmme_ite(char *basen, lev1_meta *lev1m) {
    lv1_cont *l1con_list = NULL;
    if (build_l2meth_ite(&l1con_list, basen, lev1m->lv2pn))
        return -1;
    if (!find_l1cnod_name(l1con_list, lev1m->lev1n)) {
        l1clst_dele(l1con_list);
        return -1;
    }
    l1clst_dele(l1con_list);
    OSEVPF("PASSED, valid_rlmme_ite\n");
    return 0x00;
}

int valid_rlmcl_ite(char *basen, lev1_meta *lev1m) {
    char lv2d_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2d_path, basen, lev1m->lv2pn);
    if (CLASS_EXIST(lv2d_path)) return -1;
    OSEVPF("PASSED, valid_rlmcl_ite\n");
    return 0x00;
}

//

int check_iextem_ite(char *iexte_lv2pn, char *basen, char *space) {
    OSEVPF("[FUNC]:check_iextem_ite\n");
    char lv2pn[LVTN_LENGTH], lev1n[LVON_LENGTH];
    if (!split_space(lv2pn, lev1n, space))
        return -1;
    OSEVPF("basen:|%s| lv2pn:|%s| lev1n:|%s|\n", basen, lv2pn, lev1n);
    //
    lv2ex_conte l2ie_cont;
    initi_lv2ex_conte(&l2ie_cont);
    //
    lv2iex *l2e_nod = appe_lv2ie_init(&l2ie_cont, lv2pn);
    if (!l2e_nod) {
        final_lv2ex_conte(&l2ie_cont);
        return -1;
    }
    if (build_extern_inhlst_ite(&l2e_nod->iexter, &l2e_nod->inher_list, basen, lv2pn)) {
        final_lv2ex_conte(&l2ie_cont);
        return -1;
    }
    OSEVPF("lv2pn:|%s| l2e_nod->iexter:|%d|\n", lv2pn, l2e_nod->iexter);
    //
    while (l2e_nod) {
        if (l2e_nod->iexter) {
            strcpy(iexte_lv2pn, l2e_nod->lv2pn);
            final_lv2ex_conte(&l2ie_cont);
            OSEVPF("OK! iexte_lv2pn:|%s|\n", iexte_lv2pn);
            return 0x00;
        }
        //
        inherit *ilist = l2e_nod->inher_list;
        for (; ilist; ilist = ilist->next) {
            if ((((INHE_TYPE_METH | INHE_TYPE_LEVO) & ilist->rang_type) && strcmp(lev1n, ilist->lev1n))
                    || (INHE_TYPE_LVTP & ilist->rang_type))
                continue;
            //
            lv2iex *l2ie = appe_lv2ie_new(&l2ie_cont, ilist->lv2pn);
            if (!l2ie) {
                final_lv2ex_conte(&l2ie_cont);
                return -1;
            }
            if (build_extern_inhlst_ite(&l2ie->iexter, &l2ie->inher_list, basen, ilist->lv2pn)) {
                final_lv2ex_conte(&l2ie_cont);
                return -1;
            }
            OSEVPF("lv2pn:|%s| l2e_nod->iexter:|%d|\n", lv2pn, l2e_nod->iexter);
        }
        //
        l2e_nod = get_l2ie_node(&l2ie_cont);
    }
    final_lv2ex_conte(&l2ie_cont);
    //
    OSEVPF("PASSED, check_iextem_ite\n");
    MK_ZERO(iexte_lv2pn);
    return 0x00;
}
#include "commo_header.h"
#include "kcomm_header.h"
#include "ostri_utili.h"

#include "lv2p_meta/lv2me_ite.h"
#include "repla/repla_utili.h"
#include "lv2p_list.h"
#include "lev1_utili.h"

#include "cvalid_utili.h"

//

int valid_replc_delem(char *basen, replc_list *rep_nod) {
    OSEVPF("[FUNC]:valid_replc_delem\n");
    integra *inte_list = NULL;
    if (LVTP_NORM_METH & rep_nod->levtyp) {
        if (build_intlst_ite(&inte_list, basen, rep_nod->lv2pn))
            return -1;
        if (!find_integ_iden(inte_list, rep_nod->lv2pn, rep_nod->ident)) {
            olist_dele(inte_list);
            return -1;
        }
        olist_dele(inte_list);
    }
    //
    return 0x00;
}

//

int valid_replc_addim(char *basen, replc_list *rep_nod) {
    OSEVPF("[FUNC]:valid_replc_addim\n");
    integra *inte_list = NULL;
    if (LVTP_INHE_METH & rep_nod->levtyp) {
        if (build_intlst_ite(&inte_list, basen, rep_nod->lv2pn))
            return -1;
        if (find_integ_iden(inte_list, rep_nod->lv2pn, rep_nod->ident)) {
            olist_dele(inte_list);
            return -1;
        }
        olist_dele(inte_list);
    } else if (LVTP_INHE_LEVO & rep_nod->levtyp) {
        if (build_intlst_ite(&inte_list, basen, rep_nod->lv2pn))
            return -1;
        if (find_integ_iden(inte_list, rep_nod->lv2pn, rep_nod->ident)) {
            olist_dele(inte_list);
            return -1;
        }
        olist_dele(inte_list);
    } else if (LVTP_INHE_LVTP & rep_nod->levtyp) {
        if (build_intlst_ite(&inte_list, basen, rep_nod->lv2pn))
            return -1;
        if (inte_list) {
            olist_dele(inte_list);
            return -1;
        }
        olist_dele(inte_list);
    } else if (LVTP_INHE_CLAS & rep_nod->levtyp) {
        if (build_intlst_ite(&inte_list, basen, rep_nod->lv2pn))
            return -1;
        if (inte_list) {
            olist_dele(inte_list);
            return -1;
        }
        olist_dele(inte_list);
    }
    //
    return 0x00;
}

//

int valid_replc_bindm(char *basen, replc_list *rep_nod) {
    OSEVPF("[FUNC]:valid_replc_bindm\n");
    integra *inte_list = NULL;
    if (LVTP_INHE_METH & rep_nod->levtyp) {
        if (build_intlst_ite(&inte_list, basen, rep_nod->lv2pn))
            return -1;
        if (find_integ_iden(inte_list, rep_nod->lv2pn, rep_nod->ident)) {
            olist_dele(inte_list);
            return -1;
        }
        olist_dele(inte_list);
    }
    return 0x00;
}

// 

int valid_dropc_integ(char *basen, char *lv2pn, integra *olist) {
    lev1_decl_t lev1d[LEVO_COUNT];
    if (parse_lev1d_clasn(lev1d, basen, lv2pn))
        return -1;
    //
    lev1_decl_t *lv1d = lev1d;
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        if (LVTP_NORM_METH & lv1d->levtyp) {
            if (!find_integ_iden(olist, lv1d->lv2pn, lv1d->ident))
                return -1;
        }
    }
    //
    return 0x00;
}

lev1_decl_t *chk_same_lev1n(lev1_decl_t *lev1d, lev1_decl_t *lv1d) {
    for (; LVTP_TYPE_NONE != lev1d->levtyp; ++lev1d) {
        // OSEVPF("----- lev1d->lev1n:|%s| levtyp:|%08X|\n", lev1d->lev1n, lev1d->levtyp);
        if (lv1d != lev1d) {
            if (!strcmp(lv1d->ident, lev1d->ident))
                return lev1d;
        }
    }
    return NULL;
}

//

int valid_iextec_ite(char *basen, char *lv2pn) {
    OSEVPF("[FUNC]:valid_iextec_ite\n");
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
    //
    while (l2e_nod) {
        if (l2e_nod->iexter) {
            final_lv2ex_conte(&l2ie_cont);
            OSEVPF("EXCEPTION, valid_iextec_ite\n");
            return 0x01;
        }
        //
        inherit *ilist = l2e_nod->inher_list;
        for (; ilist; ilist = ilist->next) {
            lv2iex *l2ie = appe_lv2ie_new(&l2ie_cont, ilist->lv2pn);
            if (!l2ie) {
                final_lv2ex_conte(&l2ie_cont);
                return -1;
            }
            if (build_extern_inhlst_ite(&l2ie->iexter, &l2ie->inher_list, basen, ilist->lv2pn)) {
                final_lv2ex_conte(&l2ie_cont);
                return -1;
            }
        }
        //
        l2e_nod = get_l2ie_node(&l2ie_cont);
    }
    final_lv2ex_conte(&l2ie_cont);
    //
    OSEVPF("PASSED, valid_iextec_ite\n");
    return 0x00;
}


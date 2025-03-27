#include "commo_header.h"

#include "kcomm_header.h"
#include "lv2p_list.h"
#include "lv2p_meta/lv2me_ite.h"
#include "repla/repla_utili.h"
#include "ostri_utili.h"

#include "lev1_decla.h"
#include "integ_utili.h"

//

int replc_addim_integ(lv2pm_hmap *lv2pm_stm, char *basen, replc_list *rep_nod) {
    char lv2t_path[MAX_PATH * 3];
    lv2p_attri *lv2ai;
    //
    if (LVTP_NORM_METH & rep_nod->levtyp) {
        lv2ai = (lv2p_attri *) cache_value(rep_nod->lv2pn, lv2pm_stm->lv2pan_hm);
        if (!lv2ai) return -1;
        //
        if (!appe_integ_list(&lv2ai->integ_list, rep_nod->levtyp, rep_nod->lv2pn, rep_nod->ident))
            return -1;
        //
        LVTP_ATTRI_FILE(lv2t_path, basen, rep_nod->lv2pn)
        if (save_l2att_ite(lv2t_path, lv2ai))
            return -1;
    }
    //
    return 0x00;
}

int robk_replc_addim_integ(lv2pm_hmap *lv2pm_stm, char *basen, replc_list *rep_nod) {
    char lv2t_path[MAX_PATH * 3];
    lv2p_attri *lv2ai;
    //
    if (LVTP_NORM_METH & rep_nod->levtyp) {
        lv2ai = (lv2p_attri *) cache_value(rep_nod->lv2pn, lv2pm_stm->lv2pan_hm);
        if (!lv2ai) return -1;
        //
        integra * onnod = dele_integ_iden(&lv2ai->integ_list, rep_nod->lv2pn, rep_nod->ident);
        if (onnod) LEVONE_DELET(onnod)
            //
            LVTP_ATTRI_FILE(lv2t_path, basen, rep_nod->lv2pn)
            if (save_l2att_ite(lv2t_path, lv2ai))
                return -1;
    }
    //
    return 0x00;
}

//

int replc_delem_integ(lv2pm_hmap *lv2pm_stm, char *basen, replc_list *rep_nod) {
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(rep_nod->lv2pn, lv2pm_stm->lv2pan_hm);
    if (!lv2ai) return -1;
    //
    integra * onnod = dele_integ_iden(&lv2ai->integ_list, rep_nod->lv2pn, rep_nod->ident);
    if (onnod) LEVONE_DELET(onnod)
        //
        char lv2t_path[MAX_PATH * 3];
    LVTP_ATTRI_FILE(lv2t_path, basen, rep_nod->lv2pn)
    if (save_l2att_ite(lv2t_path, lv2ai))
        return -1;
    //
    return 0x00;
}

int robk_replc_delem_integ(lv2pm_hmap *lv2pm_stm, char *basen, replc_list *rep_nod) {
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(rep_nod->lv2pn, lv2pm_stm->lv2pan_hm);
    if (!lv2ai) return -1;
    //
    if (!appe_integ_list(&lv2ai->integ_list, rep_nod->levtyp, rep_nod->lv2pn, rep_nod->ident))
        return -1;
    //
    char lv2t_path[MAX_PATH * 3];
    LVTP_ATTRI_FILE(lv2t_path, basen, rep_nod->lv2pn)
    if (save_l2att_ite(lv2t_path, lv2ai))
        return -1;
    //
    return 0x00;
}

//

int replc_bindm_integ(lv2pm_hmap *lv2pm_stm, char *basen, replc_list *rep_nod) {
    char lv2t_path[MAX_PATH * 3];
    lv2p_attri *lv2ai;
    //
    if ((LVTP_NORM_METH | LVTP_INHE_METH) & rep_nod->levtyp) {
        lv2ai = (lv2p_attri *) cache_value(rep_nod->lv2pn, lv2pm_stm->lv2pan_hm);
        if (!lv2ai) return -1;
        //
        if (!appe_integ_list(&lv2ai->integ_list, rep_nod->levtyp, rep_nod->lv2pn, rep_nod->ident))
            return -1;
        //
        LVTP_ATTRI_FILE(lv2t_path, basen, rep_nod->lv2pn)
        if (save_l2att_ite(lv2t_path, lv2ai))
            return -1;
        //
        inherit * ilist = lv2ai->inher_list;
        for (; ilist; ilist = ilist->next) {
            ilist = find_inher_iden(ilist, rep_nod->lv2pn, rep_nod->ident);
            if (!ilist) break;
            //
            if (recur_inser_integ(ilist, lv2pm_stm, basen, rep_nod->lv2pn))
                return -1;
        }
    }
    //
    return 0x00;
}

int robk_replc_bindm_integ(lv2pm_hmap *lv2pm_stm, char *basen, replc_list *rep_nod) {
    char lv2t_path[MAX_PATH * 3];
    lv2p_attri *lv2ai;
    //
    if ((LVTP_NORM_METH | LVTP_INHE_METH) & rep_nod->levtyp) {
        lv2ai = (lv2p_attri *) cache_value(rep_nod->lv2pn, lv2pm_stm->lv2pan_hm);
        if (!lv2ai) return -1;
        //
        integra * onnod = dele_integ_iden(&lv2ai->integ_list, rep_nod->lv2pn, rep_nod->ident);
        if (onnod) LEVONE_DELET(onnod)
            //
            LVTP_ATTRI_FILE(lv2t_path, basen, rep_nod->lv2pn)
            if (save_l2att_ite(lv2t_path, lv2ai))
                return -1;
        //
        inherit * ilist = lv2ai->inher_list;
        for (; ilist; ilist = ilist->next) {
            ilist = find_inher_iden(ilist, rep_nod->lv2pn, rep_nod->ident);
            if (!ilist) break;
            //
            if (recur_delet_integ(ilist, lv2pm_stm, basen, rep_nod->lv2pn))
                return -1;
        }
    }
    //
    return 0x00;
}

//

int valid_imeth_integ(char *basen, lev1_decl_t *lev1d) {
    OSEVPF("[FUNC]:valid_imeth_integ\n");
    integra *inte_list = NULL;
    char *supe_lv2n = last_lv2pn(lev1d->inhe_lv2n);
    if (build_intlst_ite(&inte_list, basen, supe_lv2n))
        return -1;
    //
    OSEVPF("supe_lv2n:|%s| lev1d->ident:|%s|\n", supe_lv2n, lev1d->ident);
    integra *onnod = inte_list;
    for (; onnod; onnod = onnod->next) {
        OSEVPF("onnod->lv2pn:|%s| onnod->lev1n:|%s|\n", onnod->lv2pn, onnod->lev1n);
        if (!strcmp(supe_lv2n, onnod->lv2pn) && !strcmp(lev1d->ident, onnod->lev1n)) {
            olist_dele(inte_list);
            return -1;
        }
    }
    //
    olist_dele(inte_list);
    return 0x00;
}

int valid_ilev1_integ(char *basen, lev1_decl_t *lev1d) {
    OSEVPF("[FUNC]:valid_ilev1_integ\n");
    integra *inte_list = NULL;
    char *supe_lv2n = last_lv2pn(lev1d->inhe_lv2n);
    if (build_intlst_ite(&inte_list, basen, supe_lv2n))
        return -1;
    //
    OSEVPF("supe_lv2n:|%s| lev1d->ident:|%s| \n", supe_lv2n, lev1d->ident);
    integra *onnod = inte_list;
    for (; onnod; onnod = onnod->next) {
        OSEVPF("onnod->lv2pn:|%s| onnod->lev1n:|%s|\n", onnod->lv2pn, onnod->lev1n);
        if (!strcmp(supe_lv2n, onnod->lv2pn) && !strcmp(lev1d->ident, onnod->lev1n)) {
            olist_dele(inte_list);
            return -1;
        }
    }
    //
    olist_dele(inte_list);
    return 0x00;
}

int valid_ilv2p_integ(char *basen, lev1_decl_t *lev1d) {
    OSEVPF("[FUNC]:valid_ilv2p_integ\n");
    integra *inte_list = NULL;
    if (build_intlst_ite(&inte_list, basen, lev1d->ident))
        return -1;
    //
    OSEVPF("lev1d->ident:|%s| \n", lev1d->ident);
    integra *onnod = inte_list;
    for (; onnod; onnod = onnod->next) {
        OSEVPF("onnod->lv2pn:|%s|\n", onnod->lv2pn);
        if (!strcmp(lev1d->ident, onnod->lv2pn)) {
            olist_dele(inte_list);
            return -1;
        }
    }
    //
    olist_dele(inte_list);
    return 0x00;
}

int valid_iclas_integ(char *basen, lev1_decl_t *lev1d) {
    OSEVPF("[FUNC]:valid_iclas_integ\n");
    integra *inte_list = NULL;
    OSEVPF("lev1d->inhe_lv2n:|%s|\n", lev1d->inhe_lv2n[0x00]);
    OSEVPF("lev1d->inhe_lv2n:|%s|\n", lev1d->inhe_lv2n[0x01]);
    OSEVPF("lev1d->inhe_lv2n:|%s|\n", lev1d->inhe_lv2n[0x02]);
    if (build_intlst_ite(&inte_list, basen, last_lv2pn(lev1d->inhe_lv2n)))
        return -1;
    if (inte_list) {
        olist_dele(inte_list);
        return -1;
    }
    olist_dele(inte_list);
    return 0x00;
}

//

static int inser_integ_node(lv2pm_hmap *lv2pm_stm, char *basen, char *clasn, char *lv2pn, char *lev1n, int range_type) {
    OSEVPF("[FUNC]:integ_updac_ite, clasn:|%s|\n", clasn);
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(clasn, lv2pm_stm->lv2pan_hm);
    if (!lv2ai) return -1;
    //
    if (appe_integ_list(&lv2ai->integ_list, range_type, lv2pn, lev1n))
        return -1;
    //
    char lv2t_path[MAX_PATH * 3];
    LVTP_ATTRI_FILE(lv2t_path, basen, clasn);
    if (save_l2att_ite(lv2t_path, lv2ai))
        return -1;
    //
    return 0x00;
}

int recur_inser_integ(inherit *innod, lv2pm_hmap *lv2pm_stm, char *basen, char *lv2pn) {
    OSEVPF("[FUNC]:recur_inser_integ\n");
    if (inser_integ_node(lv2pm_stm, basen, innod->lv2pn, lv2pn, innod->lev1n, innod->rang_type))
        return -1;
    inherit *inhe_list = NULL;
    if (build_inhlst_ite(&inhe_list, basen, lv2pn))
        return -1;
    //
    inherit *ilist = inhe_list;
    for (; ilist; ilist = ilist->next) {
        ilist = find_inher_iden(ilist, innod->lv2pn, innod->lev1n);
        if (!ilist)break;
        //
        if (recur_inser_integ(ilist, lv2pm_stm, basen, innod->lv2pn)) {
            ilist_dele(inhe_list);
            return -1;
        }
    }
    //
    ilist_dele(inhe_list);
    return 0x00;
}

//

static int delet_integ_node(lv2pm_hmap *lv2pm_stm, char *basen, char *clasn, char *lv2pn, char *lev1n) {
    OSEVPF("[FUNC]:delet_integ_node, clasn:|%s|\n", clasn);
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(clasn, lv2pm_stm->lv2pan_hm);
    if (!lv2ai) return -1;
    //
    integra * onnod = dele_integ_iden(&lv2ai->integ_list, lv2pn, lev1n);
    if (onnod) LEVONE_DELET(onnod)
        //
        char lv2t_path[MAX_PATH * 3];
    LVTP_ATTRI_FILE(lv2t_path, basen, clasn);
    if (save_l2att_ite(lv2t_path, lv2ai))
        return -1;
    //
    return 0x00;
}

int recur_delet_integ(inherit *innod, lv2pm_hmap *lv2pm_stm, char *basen, char *lv2pn) {
    OSEVPF("[FUNC]:recur_delet_integ\n");
    if (delet_integ_node(lv2pm_stm, basen, innod->lv2pn, lv2pn, innod->lev1n))
        return -1;
    inherit *inhe_list = NULL;
    if (build_inhlst_ite(&inhe_list, basen, lv2pn))
        return -1;
    //
    inherit *ilist = inhe_list;
    for (; ilist; ilist = ilist->next) {
        ilist = find_inher_iden(ilist, innod->lv2pn, innod->lev1n);
        if (!ilist)break;
        //
        if (recur_inser_integ(ilist, lv2pm_stm, basen, innod->lv2pn)) {
            ilist_dele(inhe_list);
            return -1;
        }
    }
    //
    ilist_dele(inhe_list);
    return 0x00;
}





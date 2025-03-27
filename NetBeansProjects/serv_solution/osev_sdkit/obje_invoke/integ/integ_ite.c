
#include "commo_header.h"
#include "kcomm_header.h"
#include "istri_utili.h"
#include "trans/trans_utili.h"
#include "lv2p_meta/lv2me_ite.h"
#include "lv2p_list.h"
#include "stat_respo.h"
#include "invok_obje.h"
#include "repla/repla_utili.h"

#include "integ_utili.h"
#include "integ_ite.h"

//

int integ_creac_ite(integra **olsth, lev1_decl_t *lev1d, int range_type) {
    OSEVPF("[FUNC]:integ_creac_ite, lv2pn:|%s| ident:|%s|\n", lev1d->lv2pn, lev1d->ident);
    integra *onnod = new_integ_list(olsth);
    if (!onnod) return -1;
    char cline[LINE_LENGTH];
    onnod->rang_type = range_type;
    echo_inher_clasn(cline, lev1d->lv2pn, lev1d->inhe_lv2n);
    strcpy(onnod->lv2pn, cline);
    strcpy(onnod->lev1n, lev1d->ident);
    //
    return 0x00;
}

int integ_updat_ite(char *lv2pn, char *basen, lv2p_attri *lv2ai) {
    OSEVPF("[FUNC]:integ_updac_ite, lv2pn:|%s|\n", lv2pn);
    if (!lv2ai->integ_list) return 0x00;
    char lv2t_path[MAX_PATH * 3];
    LVTP_ATTRI_FILE(lv2t_path, basen, lv2pn);
    if (save_l2att_ite(lv2t_path, lv2ai))
        return -1;
    //
    return 0x00;
}

//

int integ_cream_ite(lv2pm_hmap *lv2pm_stm, char *basen, lev1_meta *lev1m) {
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lev1m->lv2pn, lv2pm_stm->lv2pan_hm);
    if (!lv2ai) return -1;
    //
    inherit *ilist = lv2ai->inher_list;
    for (; ilist; ilist = ilist->next) {
        ilist = find_inher_iden(ilist, lev1m->lv2pn, lev1m->lev1n);
        if (!ilist) break;
        //
        if (recur_inser_integ(ilist, lv2pm_stm, basen, lev1m->lv2pn))
            return -1;
    }
    //
    integra *onnod = dele_integ_iden(&lv2ai->integ_list, lev1m->lv2pn, lev1m->lev1n);
    if (onnod) LEVONE_DELET(onnod)
        lv2ai->versio++;
    //
    char lv2t_path[MAX_PATH * 3];
    LVTP_ATTRI_FILE(lv2t_path, basen, lev1m->lv2pn)
    if (save_l2att_ite(lv2t_path, lv2ai))
        return -1;
    //
    return 0x00;
}

int robk_integ_cream_ite(integra **olsth, lev1_meta *lev1m, int range_type) {
    if (find_integ_iden(olsth[0x00], lev1m->lv2pn, lev1m->lev1n))
        return 0x00;
    //
    integra *onnod = new_integ_list(olsth);
    if (!onnod) return -1;
    onnod->rang_type = range_type;
    strcpy(onnod->lv2pn, lev1m->lv2pn);
    strcpy(onnod->lev1n, lev1m->lev1n);
    //
    return 0x00;
}

//

int integ_class_ite(respo_ctrl *resctl, char *basen, char *lv2pn) {
    OSEVPF("[FUNC]:integ_class_ite\n");
    char lv2p_path[MAX_PATH * 3];
    char *lv2p_arra[LVTP_COUNT];
    char _cline_[LARGE_CONTE_SIZE];
    //
    PDAT_PRODUCE_INITI(resctl)
    integra *inte_list = NULL;
    if (lv2pn) { // OSEVPF("have class name, lv2pn:|%s|\n", lv2pn);
        if (build_intlst_ite(&inte_list, basen, lv2pn)) {
            PDAT_EXCEPTIO_TAIL(resctl, LVTP_INFO_EXPT);
            return -1;
        }
        if (inte_list) list_lv2p_lolst(resctl, inte_list);
        olist_dele(inte_list);
    } else { // OSEVPF("not have class name.\n");
        CREAT_CLASS_DIRECTORY(lv2p_path, basen)
        if (list_clas(lv2p_arra, _cline_, lv2p_path)) {
            PDAT_EXCEPTIO_TAIL(resctl, LVTP_INFO_EXPT);
            return -1;
        }
        char **lv2pnp = lv2p_arra;
        LIST_LVTP_INTEG_HEAD(resctl);
        for (; lv2pnp[0x00]; ++lv2pnp) {
            // OSEVPF("lv2pn:|%s|\n", lv2pnp[0x00]);
            if (build_intlst_ite(&inte_list, basen, lv2pnp[0x00])) {
                PDAT_EXCEPTIO_TAIL(resctl, LVTP_INFO_EXPT);
                return -1;
            }
            if (inte_list) list_lv2p_integ(resctl, lv2pnp[0x00]);
            olist_dele(inte_list);
        }
        LIST_LVTP_INTEG_TAIL(resctl);
    }
    PDAT_PRODUCE_FINAL(resctl)
            //
    return 0x00;
}

//

int integ_metho_ident_ite(respo_ctrl *resctl, char *basen, lev1_meta *lev1m) {
    OSEVPF("[FUNC]:integ_metho_ident_ite, lv2pn:|%s| lev1n:|%s|\n", lev1m->lv2pn, lev1m->lev1n);
    integra *inte_list = NULL;
    if (build_intlst_ite(&inte_list, basen, lev1m->lv2pn)) {
        PDAT_EXCEPTIO_TAIL(resctl, INVOK_INFO_EXPT)
        return -1;
    }
    //
    PDAT_PRODUCE_INITI(resctl)
    integra *onnod = inte_list;
    LIST_LEVO_INTEG_HEAD(resctl);
    if (HAVE_METHN & lev1m->layout) {
        for (; (onnod = find_integ_iden(onnod, lev1m->lv2pn, lev1m->lev1n)); onnod = onnod->next) {
            // list_lev1_integ(resctl, onnod);
            LIST_LEVO_INTEG_BODY(resctl, onnod);
        }
    } else { // HAVE_CLASN
        for (; onnod; onnod = onnod->next) {
            // list_lev1_integ(resctl, onnod);
            LIST_LEVO_INTEG_BODY(resctl, onnod)
        }
    }
    LIST_LEVO_INTEG_TAIL(resctl);
    PDAT_PRODUCE_FINAL(resctl)
    //
    olist_dele(inte_list);
    return 0x00;
}

int integ_metho_empty_ite(respo_ctrl *resctl, char *basen, char *lv2pn) {
    OSEVPF("[FUNC]:integ_metho_empty_ite, lv2pn:|%s|\n", lv2pn);
    integra *inte_list = NULL;
    if (build_intlst_ite(&inte_list, basen, lv2pn)) {
        PDAT_EXCEPTIO_TAIL(resctl, INVOK_INFO_EXPT)
        return -1;
    }
    //
    PDAT_PRODUCE_INITI(resctl)
    integra *onnod = inte_list;
    LIST_LEVO_INTEG_HEAD(resctl);
    for (; onnod; onnod = onnod->next) {
        // list_lev1_integ(resctl, onnod);
        LIST_LEVO_INTEG_BODY(resctl, onnod)
    }
    LIST_LEVO_INTEG_TAIL(resctl);
    PDAT_PRODUCE_FINAL(resctl)
    //
    olist_dele(inte_list);
    return 0x00;
}

//

int integ_replm_ite(lv2pm_hmap *lv2pm_stm, char *basen, lev1_meta *lev1m) {
    inherit *inhe_list = NULL;
    if (build_inhlst_ite(&inhe_list, basen, lev1m->lv2pn))
        return -1;
    inherit *ilist = inhe_list;
    for (; ilist; ilist = ilist->next) {
        ilist = find_inher_iden(ilist, lev1m->lv2pn, lev1m->lev1n);
        if (!ilist) break;
        //
        if (recur_inser_integ(ilist, lv2pm_stm, basen, lev1m->lv2pn)) {
            ilist_dele(inhe_list);
            return -1;
        }
    }
    //
    ilist_dele(inhe_list);
    return 0x00;
}

//

int integ_relom_ite(lv2pm_hmap *lv2pm_stm, char *basen, lev1_meta *lev1m) {
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lev1m->lv2pn, lv2pm_stm->lv2pan_hm);
    if (!lv2ai) return -1;
    //
    integra * onnod = dele_integ_iden(&lv2ai->integ_list, lev1m->lv2pn, lev1m->lev1n);
    if (onnod) LEVONE_DELET(onnod)
        lv2ai->versio++;
    //
    char lv2t_path[MAX_PATH * 3];
    LVTP_ATTRI_FILE(lv2t_path, basen, lev1m->lv2pn)
    if (save_l2att_ite(lv2t_path, lv2ai))
        return -1;
    //
    return 0x00;
}

// binding changed

int integ_replc_ite(lv2pm_hmap *lv2pm_stm, char *basen, replc_list *replst) {
    OSEVPF("[FUNC]:integ_replc_ite\n");
    for (; replst; replst = replst->next) {
        switch (replst->replc_type) {
            case REPLC_MORE_DATA:
            case REPLC_LESS_DATA:
                break;
            case REPLC_ADDI_METH:
                if (replc_addim_integ(lv2pm_stm, basen, replst))
                    return -1;
                break;
            case REPLC_DELE_METH:
                if (replc_delem_integ(lv2pm_stm, basen, replst))
                    return -1;
                break;
            case REPLC_BIND_CHAN:
                if (replc_bindm_integ(lv2pm_stm, basen, replst))
                    return -1;
                break;
        }
    }
    //
    return 0x00;
}

//

int robk_integ_replc_ite(lv2pm_hmap *lv2pm_stm, char *basen, replc_list *replst) {
    OSEVPF("[FUNC]:integ_replc_ite\n");
    for (; replst; replst = replst->next) {
        switch (replst->replc_type) {
            case REPLC_MORE_DATA:
            case REPLC_LESS_DATA:
                break;
            case REPLC_ADDI_METH:
                if (robk_replc_addim_integ(lv2pm_stm, basen, replst))
                    return -1;
                break;
            case REPLC_DELE_METH:
                if (robk_replc_delem_integ(lv2pm_stm, basen, replst))
                    return -1;
                break;
            case REPLC_BIND_CHAN:
                if (robk_replc_bindm_integ(lv2pm_stm, basen, replst))
                    return -1;
                break;
        }
    }
    //
    return 0x00;
}

//

int integ_reloc_ite(lv2pm_hmap *lv2pm_stm, char *basen, lv2p_decl_t *lv2dt) {
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lv2dt->lv2pn, lv2pm_stm->lv2pan_hm);
    if (!lv2ai) return -1;
    //
    integra * onnod = dele_integ_lv2p(&lv2ai->integ_list, lv2dt->lv2pn);
    if (onnod) LEVONE_DELET(onnod)
        lv2ai->versio++;
    //
    char lv2t_path[MAX_PATH * 3];
    LVTP_ATTRI_FILE(lv2t_path, basen, lv2dt->lv2pn);
    if (save_l2att_ite(lv2t_path, lv2ai))
        return -1;
    //
    return 0x00;
}

// check class integra
// integra *integ_list, char *lv2pn, char *lev1n, char *fmtsp

int integ_legal_ite(char *basen, lev1_decl_t *lev1d) {
    OSEVPF("[FUNC]:integ_legal_ite\n");
    switch (lev1d->levtyp) {
        case LVTP_INHE_METH:
            if (valid_imeth_integ(basen, lev1d))
                return -1;
            break;
        case LVTP_INHE_LEVO:
            if (valid_ilev1_integ(basen, lev1d))
                return -1;
            break;
        case LVTP_INHE_LVTP:
            if (valid_ilv2p_integ(basen, lev1d))
                return -1;
            break;
        case LVTP_INHE_CLAS:
            if (valid_iclas_integ(basen, lev1d))
                return -1;
            break;
    }
    //
    return 0x00;
}

int integ_dropm_ite(lv2pm_hmap *lv2pm_stm, char *basen, lev1_meta *lev1m) {
    OSEVPF("[FUNC]:integ_dropm_ite.\n");
    lv1_cont *l1con_list = NULL;
    if (build_l2meth_ite(&l1con_list, basen, lev1m->lv2pn))
        return -1;
    if (find_l1cnod_name(l1con_list, lev1m->lev1n)) {
        l1clst_dele(l1con_list);
        return 0x00;
    }
    l1clst_dele(l1con_list);
    //
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lev1m->lv2pn, lv2pm_stm->lv2pan_hm);
    if (!lv2ai) return -1;
    //
    lv2ai->versio++;
    if (!appe_integ_list(&lv2ai->integ_list, INTE_NORM_METH, lev1m->lv2pn, lev1m->lev1n))
        return -1;
    //
    char lv2t_path[MAX_PATH * 3];
    LVTP_ATTRI_FILE(lv2t_path, basen, lev1m->lv2pn)
    if (save_l2att_ite(lv2t_path, lv2ai))
        return -1;
    //
    return 0x00;
}

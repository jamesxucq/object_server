
#include "commo_header.h"
#include "kcomm_header.h"
#include "lv2p_meta/lv2me_ite.h"
#include "trans/trans_utili.h"
#include "lv2p_list.h"

#include "ostri_utili.h"
#include "conte_bzl.h"
#include "istri_utili.h"
#include "inher_utili.h"
#include "inheri_ite.h"

#include "lv2p_expand.h"
#include "invok_bzl.h"
#include "filli_clang.h"
#include "lev1_decla.h"
#include "inheri_ite.h"
#include "debug_funct_oi.h"

//

int inher_meth_ite(respo_ctrl *resctl, hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *basen, lev1_decl_t *lev1d, lev1id *crea_lev1i) {
    OSEVPF("[FUNC]:inher_meth_ite\n");
    char clang_cont[CLANG_CONTE_SIZE];
    lv1_cont *l1con_list = NULL, *l1lsnd;
    if (regis_inher_meth(lv2pm_stm, basen, last_lv2pn(lev1d->inhe_lv2n), crea_lev1i->crea_lv2pn, lev1d->ident)) {
        OSEVPF("Regis inher excep!\n");
        PDAT_EXCEPTIO_TAIL(resctl, CREAT_REGIS_INHE)
        return -1;
    }
    if (find_super_lv2pn(crea_lev1i->supe_lv2pn, basen, lev1d)) {
        OSEVPF("Find super excep!\n");
        PDAT_EXCEPTIO_TAIL(resctl, FIND_SUPER_EXPT)
        return -1;
    }
    OSEVPF("crea_lev1i->supe_lv2pn:|%s|, lev1d->ident:|%s|\n", crea_lev1i->supe_lv2pn, lev1d->ident);
    if (build_l2meth_ite(&l1con_list, basen, crea_lev1i->supe_lv2pn)) {
        OSEVPF("Creat imeth excep!\n");
        PDAT_EXCEPTIO_TAIL(resctl, CREAT_INLVO_EXPT)
        return -1;
    }
    l1lsnd = FIND_LEVON_BZL(l1con_list, lev1d->ident);
    for (; l1lsnd; l1lsnd = FIND_LEVON_BZL(l1lsnd->next, lev1d->ident)) { // out_invoke
        build_clev1i_lev1d(crea_lev1i, lev1d, lev1d->ident, l1lsnd);
        PRIN_lev1id(crea_lev1i);
        if (conv_imet_bzl(clang_cont, basen, crea_lev1i, l1lsnd->conte)) {
            OSEVPF("Conve imeth excep!\n");
            FREE_LVOLST_BZL(l1con_list);
            PDAT_EXCEPTIO_TAIL(resctl, CONVE_INLVO_EXPT)
            return -1;
        }
        char libr_path[MAX_PATH * 3];
        if (hcrea_imeth_bzl(resctl, libr_path, clang_cont, basen, crea_lev1i)) {
            FREE_LVOLST_BZL(l1con_list);
            OSEVPF("Hand creat imeth excep!\n");
            return -1;
        }
        if (creat_ilv1me_bzl(hando_stm, lv2pm_stm, libr_path, basen, crea_lev1i)) {
            OSEVPF("Creat imeth meta excep!\n");
            FREE_LVOLST_BZL(l1con_list);
            PDAT_EXCEPTIO_TAIL(resctl, CREAT_LVOME_EXPT)
            return -1;
        }
    }
    FREE_LVOLST_BZL(l1con_list);
    //
    return 0x00;
}

//

int inher_lev1_ite(respo_ctrl *resctl, hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *basen, lev1_decl_t *lev1d, lev1id *crea_lev1i) {
    OSEVPF("[FUNC]:inher_lev1_ite\n");
    char clang_cont[CLANG_CONTE_SIZE];
    lv1_cont *l1con_list = NULL, *l1lsnd;
    if (regis_inher_lev1(lv2pm_stm, basen, last_lv2pn(lev1d->inhe_lv2n), crea_lev1i->crea_lv2pn, lev1d->ident)) {
        OSEVPF("Regis inher excep!\n");
        PDAT_EXCEPTIO_TAIL(resctl, CREAT_REGIS_INHE)
        return -1;
    }
    if (filli_ilev1_fmtsd(lev1d->innep.inne_fmtsp, basen, lev1d->inhe_lv2n[0x00], lev1d->ident)) {
        OSEVPF("Fill lev1 param type excep!\n");
        PDAT_EXCEPTIO_TAIL(resctl, CREAT_INHER_EXPT)
        return -1;
    }
    if (find_super_lv2pn(crea_lev1i->supe_lv2pn, basen, lev1d)) {
        OSEVPF("Find super excep!\n");
        PDAT_EXCEPTIO_TAIL(resctl, FIND_SUPER_EXPT)
        return -1;
    }
    OSEVPF("crea_lev1i->supe_lv2pn:|%s|, lev1d->ident:|%s|\n", crea_lev1i->supe_lv2pn, lev1d->ident);
    if (build_l2meth_ite(&l1con_list, basen, crea_lev1i->supe_lv2pn)) {
        OSEVPF("Creat imeth excep!\n");
        PDAT_EXCEPTIO_TAIL(resctl, CREAT_INLVO_EXPT)
        return -1;
    }
    l1lsnd = FIND_LEVON_BZL(l1con_list, lev1d->ident);
    for (; l1lsnd; l1lsnd = FIND_LEVON_BZL(l1lsnd->next, lev1d->ident)) { // out_invoke
        build_clev1i_lev1d(crea_lev1i, lev1d, lev1d->ident, l1lsnd);
        PRIN_lev1id(crea_lev1i);
        if (conv_ilv1_bzl(clang_cont, basen, crea_lev1i, l1lsnd->conte)) {
            OSEVPF("Conve ilev1 excep!\n");
            FREE_LVOLST_BZL(l1con_list);
            PDAT_EXCEPTIO_TAIL(resctl, CONVE_INLVO_EXPT)
            return -1;
        }
        char libr_path[MAX_PATH * 3];
        if (hcrea_imeth_bzl(resctl, libr_path, clang_cont, basen, crea_lev1i)) {
            OSEVPF("Hand creat imeth excep!\n");
            FREE_LVOLST_BZL(l1con_list);
            return -1;
        }
        if (creat_ilv1me_bzl(hando_stm, lv2pm_stm, libr_path, basen, crea_lev1i)) {
            OSEVPF("Creat imeth meta excep!\n");
            FREE_LVOLST_BZL(l1con_list);
            PDAT_EXCEPTIO_TAIL(resctl, CREAT_LVOME_EXPT)
            return -1;
        }
    }
    FREE_LVOLST_BZL(l1con_list);
    //
    return 0x00;
}

//

int inher_lv2p_ite(respo_ctrl *resctl, hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *basen, lev1_decl_t *lev1d, lev1id *crea_lev1i) {
    OSEVPF("[FUNC]:inher_lv2p_ite\n");
    char clang_cont[CLANG_CONTE_SIZE];
    lv1_cont *l1con_list = NULL, *l1lsnd;
    if (regis_inher_lv2p(lv2pm_stm, basen, lev1d->ident, crea_lev1i->crea_lv2pn)) {
        OSEVPF("Regis inher excep!\n");
        PDAT_EXCEPTIO_TAIL(resctl, CREAT_REGIS_INHE)
        return -1;
    }
    //
    lev1_decl_t ilev1d[LEVO_COUNT];
    if (parse_lev1d_clasn(ilev1d, basen, lev1d->ident)) {
        OSEVPF("Parse lev1d lv2pn excep!\n");
        PDAT_EXCEPTIO_TAIL(resctl, CREAT_INHER_EXPT)
        return -1;
    }
    lev1_decl_t *ilv1d = ilev1d;
    for (; LVTP_TYPE_NONE != ilv1d->levtyp; ++ilv1d) {
        if (build_l2meth_ite(&l1con_list, basen, ilv1d->lv2pn)) {
            OSEVPF("Creat imeth excep!\n");
            PDAT_EXCEPTIO_TAIL(resctl, CREAT_INLVO_EXPT)
            return -1;
        }
        l1lsnd = FIND_LEVON_BZL(l1con_list, lev1d->ident);
        for (; l1lsnd; l1lsnd = FIND_LEVON_BZL(l1lsnd->next, lev1d->ident)) { // out_invoke
            build_clev1i_ilv1d(crea_lev1i, ilv1d, lev1d->inhe_lv2n, l1lsnd);
            PRIN_lev1id(crea_lev1i);
            if (conv_ilv1_bzl(clang_cont, basen, crea_lev1i, l1lsnd->conte)) {
                OSEVPF("Conve imeth excep!\n");
                PDAT_EXCEPTIO_TAIL(resctl, CONVE_INLVO_EXPT)
                return -1;
            }
            char libr_path[MAX_PATH * 3];
            if (hcrea_imeth_bzl(resctl, libr_path, clang_cont, basen, crea_lev1i)) {
                OSEVPF("Hand creat imeth excep!\n");
                return -1;
            }
            if (creat_ilv1me_bzl(hando_stm, lv2pm_stm, libr_path, basen, crea_lev1i)) {
                OSEVPF("Creat imeth meta excep!\n");
                PDAT_EXCEPTIO_TAIL(resctl, CREAT_LVOME_EXPT)
                return -1;
            }
        }
        FREE_LVOLST_BZL(l1con_list);
    }
    //
    return 0x00;
}

int inher_clas_ite(respo_ctrl *resctl, hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *basen, lev1_decl_t *lev1d, lev1id *crea_lev1i) {
    OSEVPF("[FUNC]:inher_clas_ite\n");
    char clang_cont[CLANG_CONTE_SIZE];
    lv1_cont *l1con_list = NULL, *l1lsnd;
    if (regis_inher_clas(lv2pm_stm, basen, last_lv2pn(lev1d->inhe_lv2n), crea_lev1i->crea_lv2pn)) {
        OSEVPF("Regis inher excep!\n");
        PDAT_EXCEPTIO_TAIL(resctl, CREAT_REGIS_INHE)
        return -1;
    }
    //
    lev1_decl_t ilev1d[LEVO_COUNT];
    if (parse_lev1d_clasn(ilev1d, basen, lev1d->inhe_lv2n[0x00])) {
        OSEVPF("Parse lev1d lv2pn excep!\n");
        PDAT_EXCEPTIO_TAIL(resctl, CREAT_INHER_EXPT)
        return -1;
    }
    lev1_decl_t *ilv1d = ilev1d;
    for (; LVTP_TYPE_NONE != ilv1d->levtyp; ++ilv1d) {
        if (build_l2meth_ite(&l1con_list, basen, ilv1d->lv2pn)) {
            OSEVPF("Creat imeth excep!\n");
            PDAT_EXCEPTIO_TAIL(resctl, CREAT_INLVO_EXPT)
            return -1;
        }
        l1lsnd = FIND_LEVON_BZL(l1con_list, lev1d->ident);
        for (; l1lsnd; l1lsnd = FIND_LEVON_BZL(l1lsnd->next, lev1d->ident)) { // out_invoke
            build_clev1i_ilv1d(crea_lev1i, ilv1d, lev1d->inhe_lv2n, l1lsnd);
            PRIN_lev1id(crea_lev1i);
            if (conv_ilv1_bzl(clang_cont, basen, crea_lev1i, l1lsnd->conte)) {
                OSEVPF("Conve ilev1 excep!\n");
                FREE_LVOLST_BZL(l1con_list);
                PDAT_EXCEPTIO_TAIL(resctl, CONVE_INLVO_EXPT)
                return -1;
            }
            char libr_path[MAX_PATH * 3];
            if (hcrea_imeth_bzl(resctl, libr_path, clang_cont, basen, crea_lev1i)) {
                OSEVPF("Hand creat imeth excep!\n");
                FREE_LVOLST_BZL(l1con_list);
                return -1;
            }
            if (creat_ilv1me_bzl(hando_stm, lv2pm_stm, libr_path, basen, crea_lev1i)) {
                OSEVPF("Creat imeth meta excep!\n");
                FREE_LVOLST_BZL(l1con_list);
                PDAT_EXCEPTIO_TAIL(resctl, CREAT_LVOME_EXPT)
                return -1;
            }
        }
        FREE_LVOLST_BZL(l1con_list);
    }
    //
    return 0x00;
}

//

int inser_clapo_ite(lv2p_prop *l2_nod, char *basen, char *inhe_lv2n) {
    OSEVPF("[FUNC]:inser_clapo_ite\n");
    char lv2d_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2d_path, basen, inhe_lv2n);
    char lv2p_decl[LARGE_TEXT_SIZE];
    if (!split_l2dec_ite(lv2p_decl, lv2d_path))
        return -1;
    lv2p_prop clnod[LVTNOD_COUNT];
    if (parse_class_meta(clnod, lv2p_decl))
        return -1;
    // PRIN_lv2p_prop_array(clnod);
    if (merge_lv2p_prop(l2_nod, clnod))
        return -1;
    //
    OSEVPF("END inser_clapo_ite\n");
    return 0x00;
}

int inser_lv2po_ite(lv2p_prop *l2_nod, char *basen, char **inhe_l2np) {
    OSEVPF("[FUNC]:inser_lv2po_ite\n");
    char lv2d_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2d_path, basen, last_lv2pn(inhe_l2np));
    char lv2p_decl[LARGE_TEXT_SIZE];
    if (!split_l2dec_ite(lv2p_decl, lv2d_path))
        return -1;
    lv2p_prop clnod[LVTNOD_COUNT];
    if (parse_class_meta(clnod, lv2p_decl))
        return -1;
    if (merge_lv2p_prop(l2_nod, clnod))
        return -1;
    //
    OSEVPF("END inser_lv2po_ite\n");
    return 0x00;
}

//

int inser_lv1da_ite(lv2p_prop *l2_nod, char *basen, char **inhe_l2np, char *lev1n) {
    OSEVPF("[FUNC]:inser_lv1da_ite\n");
    // OSEVPF("inhe_l2np:|%s|:|%s| lev1n:|%s|\n", inhe_l2np[0x00], inhe_l2np[0x01], lev1n);
    char lv2p_decl[LARGE_TEXT_SIZE];
    char lv2d_path[MAX_PATH * 3];
    for (; inhe_l2np[0x00]; ++inhe_l2np) {
        LVTP_DECLA_FILE(lv2d_path, basen, inhe_l2np[0x00]);
        if (!split_l2dec_ite(lv2p_decl, lv2d_path))
            return -1;
        if (INHER_TYPE_BINDI == chk_inher_type(lv2p_decl, lev1n))
            break;
    }
    //
    lv2p_prop clnod[LVTNOD_COUNT];
    if (parse_lev1d_bindi(clnod, lv2p_decl, lev1n))
        return -1;
    if (merge_lv2p_prop(l2_nod, clnod))
        return -1;
    //
    OSEVPF("END inser_lv1da_ite\n");
    return 0x00;
}

//

lev1_decl_t *inser_claep_ite(lev1_decl_t *lev1d, char *basen, char *inhe_lv2n) {
    OSEVPF("[FUNC]:inser_claep_ite\n");
    char lv2d_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2d_path, basen, inhe_lv2n);
    char lv2p_decl[LARGE_TEXT_SIZE];
    if (!split_l2dec_ite(lv2p_decl, lv2d_path))
        return NULL;
    //
    // PRIN_lv2p_prop_array(clnod);
    OSEVPF("END inser_claep_ite\n");
    return parse_lev1_decla(lev1d, lv2p_decl);
}

lev1_decl_t *inser_lv2ep_ite(lev1_decl_t *lev1d, char *basen, char **inhe_l2np) {
    OSEVPF("[FUNC]:inser_lv2ep_ite\n");
    char lv2d_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2d_path, basen, last_lv2pn(inhe_l2np));
    char lv2p_decl[LARGE_TEXT_SIZE];
    if (!split_l2dec_ite(lv2p_decl, lv2d_path))
        return NULL;
    //
    OSEVPF("END inser_lv2ep_ite\n");
    return parse_lev1_decla(lev1d, lv2p_decl);
}

lev1_decl_t *inser_lv1ep_ite(lev1_decl_t *lev1d, char *basen, char **inhe_l2np, char *lev1n) {
    OSEVPF("[FUNC]:inser_lv1ep_ite\n");
    // OSEVPF("inhe_l2np:|%s|:|%s| lev1n:|%s|\n", inhe_l2np[0x00], inhe_l2np[0x01], lev1n);
    char lv2p_decl[LARGE_TEXT_SIZE];
    char lv2d_path[MAX_PATH * 3];
    for (; inhe_l2np[0x00]; ++inhe_l2np) {
        LVTP_DECLA_FILE(lv2d_path, basen, inhe_l2np[0x00]);
        if (!split_l2dec_ite(lv2p_decl, lv2d_path))
            return NULL;
        if (INHER_TYPE_BINDI == chk_inher_type(lv2p_decl, lev1n))
            break;
    }
    //
    OSEVPF("END inser_lv1ep_ite\n");
    return parse_lev1d_lev1n(lev1d, lv2p_decl, lev1n);
}

//

int inher_legal_ite(char *basen, lev1_decl_t *lev1d) {
    OSEVPF("inher_legal_ite\n");
    switch (lev1d->levtyp) {
        case LVTP_INHE_METH:
            if (valid_imeth_legal(basen, lev1d))
                return -1;
            break;
        case LVTP_INHE_LEVO:
            if (valid_ilev1_legal(basen, lev1d))
                return -1;
            break;
        case LVTP_INHE_LVTP:
            if (valid_ilv2p_legal(basen, lev1d))
                return -1;
            break;
        case LVTP_INHE_CLAS:
            if (valid_iclas_legal(basen, lev1d))
                return -1;
            break;
    }
    //
    return 0x00;
}

// todo: inher class name

static int replc_delem_inher(lv2pm_hmap *lv2pm_stm, char *basen, replc_list *rep_nod) {
    switch (rep_nod->levtyp) {
        case LVTP_INHE_METH:
            // rep_nod->lv2pn /*inher clas name*/
            if (clear_inher_meth(lv2pm_stm, basen, rep_nod->lv2pn, rep_nod->lv2pn, rep_nod->ident))
                return -1;
            break;
        case LVTP_INHE_LEVO:
            // rep_nod->lv2pn /*inher clas name*/
            if (clear_inher_lev1(lv2pm_stm, basen, rep_nod->lv2pn, rep_nod->lv2pn, rep_nod->ident))
                return -1;
            break;
        case LVTP_INHE_LVTP:
            // rep_nod->lv2pn /*inher clas name*/
            if (clear_inher_lv2p(lv2pm_stm, basen, rep_nod->lv2pn, rep_nod->lv2pn))
                return -1;
            break;
        case LVTP_INHE_CLAS:
            // rep_nod->lv2pn /*inher clas name*/
            if (clear_inher_clas(lv2pm_stm, basen, rep_nod->lv2pn, rep_nod->lv2pn))
                return -1;
            break;
    }
    //
    return 0x00;
}

// todo: inher class name

static int replc_addim_inher(lv2pm_hmap *lv2pm_stm, char *basen, replc_list *rep_nod) {
    switch (rep_nod->levtyp) {
        case LVTP_INHE_METH:
            // rep_nod->lv2pn /*inher clas name*/
            if (regis_inher_meth(lv2pm_stm, basen, rep_nod->lv2pn, rep_nod->lv2pn, rep_nod->ident))
                return -1;
            break;
        case LVTP_INHE_LEVO:
            // rep_nod->lv2pn /*inher clas name*/
            if (regis_inher_lev1(lv2pm_stm, basen, rep_nod->lv2pn, rep_nod->lv2pn, rep_nod->ident))
                return -1;
            break;
        case LVTP_INHE_LVTP:
            // rep_nod->lv2pn /*inher clas name*/
            if (regis_inher_lv2p(lv2pm_stm, basen, rep_nod->lv2pn, rep_nod->lv2pn))
                return -1;
            break;
        case LVTP_INHE_CLAS:
            // rep_nod->lv2pn /*inher clas name*/
            if (regis_inher_clas(lv2pm_stm, basen, rep_nod->lv2pn, rep_nod->lv2pn))
                return -1;
            break;
    }
    //
    return 0x00;
}

int inher_replc_ite(lv2pm_hmap *lv2pm_stm, char *basen, replc_list *replst) {
    OSEVPF("inher_replc_ite\n");
    for (; replst; replst = replst->next) {
        switch (replst->replc_type) {
            case REPLC_MORE_DATA:
            case REPLC_LESS_DATA:
                break;
            case REPLC_ADDI_METH:
                if (replc_addim_inher(lv2pm_stm, basen, replst))
                    return -1;
                break;
            case REPLC_DELE_METH:
                if (replc_delem_inher(lv2pm_stm, basen, replst))
                    return -1;
                break;
            case REPLC_BIND_CHAN:
                break;
        }
    }
    //
    return 0x00;
}

// robk replace class

int robk_inher_replc_ite(lv2pm_hmap *lv2pm_stm, char *basen, replc_list *replst) {
    OSEVPF("robk_inher_replc_ite\n");
    for (; replst; replst = replst->next) {
        switch (replst->replc_type) {
            case REPLC_MORE_DATA:
            case REPLC_LESS_DATA:
                break;
            case REPLC_ADDI_METH:
                if (replc_delem_inher(lv2pm_stm, basen, replst))
                    return -1;
                break;
            case REPLC_DELE_METH:
                if (replc_addim_inher(lv2pm_stm, basen, replst))
                    return -1;
                break;
            case REPLC_BIND_CHAN:
                break;
        }
    }
    //
    return 0x00;
}

//

int inher_dropc_ite(lv2pm_hmap *lv2pm_stm, char *basen, char *lv2pn) {
    OSEVPF("[FUNC]:inher_replc_ite\n");
    lev1_decl_t lev1d[LEVO_COUNT];
    if (build_lev1d_clasn(lev1d, basen, lv2pn))
        return -1;
    //
    OSEVPF("1\n");
    lev1_decl_t *lv1d = lev1d;
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        PRIN_lev1_decl(lv1d);
        switch (lv1d->levtyp) {
            case LVTP_INHE_METH:
                if (clear_inher_meth(lv2pm_stm, basen, last_lv2pn(lv1d->inhe_lv2n), lv1d->lv2pn, lv1d->ident))
                    return -1;
                break;
            case LVTP_INHE_LEVO:
                if (clear_inher_lev1(lv2pm_stm, basen, last_lv2pn(lv1d->inhe_lv2n), lv1d->lv2pn, lv1d->ident))
                    return -1;
                break;
            case LVTP_INHE_LVTP:
                if (clear_inher_lv2p(lv2pm_stm, basen, last_lv2pn(lv1d->inhe_lv2n), lv1d->lv2pn))
                    return -1;
                break;
            case LVTP_INHE_CLAS:
                if (clear_inher_clas(lv2pm_stm, basen, last_lv2pn(lv1d->inhe_lv2n), lv1d->lv2pn))
                    return -1;
                break;
        }
    }
    //
    OSEVPF("2\n");
    return 0x00;
}


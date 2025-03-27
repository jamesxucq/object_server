
#include "commo_header.h"
#include "kcomm_header.h"

#include "basev_bzl.h"
#include "lv2p_meta/lv2me_ite.h"
#include "integ/integ_ite.h"
#include "repla/repla_ite.h"
#include "query_bzl.h"
#include "cvalid_utili.h"
#include "inheri/inheri_ite.h"
#include "trans/trans_ite.h"

#include "lev1_decla.h"
#include "invok_bzl.h"
#include "civalid/cvalid_ite.h"

//

int valid_listc_ite(lv2pm_hmap *lv2pm_stm, char *lv2pn) {
    if (lv2pn) {
        if (!cache_value(lv2pn, lv2pm_stm->lv2pmn_hm))
            return -1;
    }
    OSEVPF("PASSED, valid_listc_ite\n");
    return 0x00;
}


// lv2p check method  inheri integ legal

int valid_creac_ite(char *basen, lv2p_decl_t *lv2dt) {
    OSEVPF("[FUNC]:valid_creac_ite\n");
    char lv2d_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2d_path, basen, lv2dt->lv2pn);
    OSEVPF("----- lv2d_path:|%s|\n", lv2d_path);
    if (!CLASS_EXIST(lv2d_path))
        return -1;
    //
    OSEVPF("check the same lev1n.\n");
    lev1_decl_t *lv1d = lv2dt->meth;
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        OSEVPF("----- lv1d->ident:|%s| levtyp:|%08X|\n", lv1d->ident, lv1d->levtyp);
        if (chk_same_lev1n(lv2dt->meth, lv1d))
            return -1;
    }
    OSEVPF("integ_legal_ite, inher_legal_ite\n");
    lv1d = lv2dt->meth;
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        OSEVPF("----- lv1d->ident:|%s| levtyp:|%08X|\n", lv1d->ident, lv1d->levtyp);
        if (integ_legal_ite(basen, lv1d))
            return -1;
        if (inher_legal_ite(basen, lv1d))
            return -1;
    }
    OSEVPF("PASSED, valid_creac_ite\n");
    return 0x00;
}

//

int valid_dropc_ite(respo_ctrl *resctl, char *basen, char *lv2pn, lv2pm_hmap *lv2pm_stm) {
    char lv2d_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2d_path, basen, lv2pn);
    if (CLASS_EXIST(lv2d_path)) return -1;
    // class have container
    lv2pme *lv2me = (lv2pme *) cache_value(lv2pn, lv2pm_stm->lv2pmn_hm);
    if (!lv2me) {
        PDAT_EXCEPTIO_TAIL(resctl, LVTP_NOT_FOUND);
        return -1;
    }
    if (0x00 >= check_catti_lv2p(basen, &lv2me->lv2p_obid)) {
        PDAT_EXCEPTIO_TAIL(resctl, LVTP_INTEG_EXPT)
        return -1;
    }
    // check inherit
    inherit *inhe_list = NULL;
    if (build_inhlst_ite(&inhe_list, basen, lv2pn)) {
        PDAT_EXCEPTIO_TAIL(resctl, LVTP_NOT_FOUND);
        return -1;
    }
    if (inhe_list) {
        PDAT_EXCEPTIO_TAIL(resctl, DROP_COLLE_INHE)
        ilist_dele(inhe_list);
        return -1;
    }
    // check level 1 define
    lv1_cont *l1con_list = NULL;
    if (build_l2meth_ite(&l1con_list, basen, lv2pn)) {
        PDAT_EXCEPTIO_TAIL(resctl, LVTP_NOT_FOUND);
        return -1;
    }
    if (l1con_list) {
        PDAT_EXCEPTIO_TAIL(resctl, DROP_COLLE_OEXI)
        l1clst_dele(l1con_list);
        return -1;
    }
    //
    OSEVPF("PASSED, valid_dropc_ite\n");
    return 0x00;
}

// data must more, can del or add method, binding changed

int valid_replc_ite(char *basen, replc_list *replst, lv2p_decl_t *nlv2pd, uint32 *forced) {
    OSEVPF("[FUNC]:valid_replc_ite\n");
    if (forced)OSEVPF("forced[0x00]:%u\n", forced[0x00]);
    else OSEVPF("forced:%p\n", forced);
    if (!replst) {
        _LOG_WARN("The lv2p not changed");
        return -1;
    }
    char lv2d_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2d_path, basen, nlv2pd->lv2pn);
    if (CLASS_EXIST(lv2d_path)) {
        _LOG_WARN("Can not find lv2p");
        return -1;
    }
    //
    for (; replst; replst = replst->next) {
        switch (replst->replc_type) {
            case REPLC_MORE_DATA:
            case REPLC_LESS_DATA:
                return -1;
                break;
            case REPLC_ADDI_METH:
                if (valid_replc_addim(basen, replst))
                    return -1;
                break;
            case REPLC_DELE_METH:
                if (valid_replc_delem(basen, replst))
                    return -1;
                break;
            case REPLC_BIND_CHAN:
                if (valid_replc_bindm(basen, replst))
                    return -1;
                break;
        }
    }
    //
    lev1_decl_t *lv1d = nlv2pd->meth;
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        if (integ_legal_ite(basen, lv1d))
            return -1;
        if (inher_legal_ite(basen, lv1d))
            return -1;
    }
    // check external
    OSEVPF("check external\n");
    if (!(forced && forced[0x00])) {
        if (valid_iextec_ite(basen, nlv2pd->lv2pn))
            return -1;
    }
    OSEVPF("PASSED, valid_replc_ite\n");
    return 0x00;
}

int valid_intec_ite(char *basen, char *lv2pn) {
    char lv2d_path[MAX_PATH * 3];
    if (lv2pn) {
        OSEVPF("have class name, lv2pn:|%s|\n", lv2pn);
        LVTP_DECLA_FILE(lv2d_path, basen, lv2pn);
        if (CLASS_EXIST(lv2d_path)) return -1;
    }
    OSEVPF("PASSED, valid_intec_ite\n");
    return 0x00;
}

int valid_reloc_ite(char *basen, char *lv2pn) {
    char lv2d_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2d_path, basen, lv2pn);
    OSEVPF("lv2d_path:|%s|\n", lv2d_path);
    if (CLASS_EXIST(lv2d_path)) return -1;
    OSEVPF("PASSED, valid_reloc_ite\n");
    return 0x00;
}

//

int check_iextec_ite(char *iexte_lv2pn, char *basen, char *lv2pn) {
    OSEVPF("[FUNC]:check_iextec_ite\n");
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
            strcpy(iexte_lv2pn, l2e_nod->lv2pn);
            final_lv2ex_conte(&l2ie_cont);
            OSEVPF("OK! iexte_lv2pn:|%s|\n", iexte_lv2pn);
            return 0x00;
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
    OSEVPF("PASSED, check_iextec_ite\n");
    MK_ZERO(iexte_lv2pn);
    return 0x00;
}

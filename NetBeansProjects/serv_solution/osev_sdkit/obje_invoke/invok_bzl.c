
#include "commo_header.h"
#include "kcomm_header.h"
#include "ostri_utili.h"
#include "lv2p_list.h"

#include "conte_bzl.h"
#include "trans/trans_utili.h"
#include "stat_respo.h"
#include "post_respo.h"
#include "seion_struct.h"
#include "civalid/cvalid_ite.h"
#include "civalid/ivalid_ite.h"
#include "integ/integ_ite.h"
#include "invok_obje.h"
#include "istri_utili.h"
#include "filli_clang.h"
#include "mesg_hand.h"

#include "instda_bzl.h"
#include "lev1_decla.h"
#include "invok_bzl.h"
#include "lv2p_expand.h"
//
/*
int compbzl_create(char *data_directory) {
    strcpy(_comp_data_directory_, data_directory);
    return ERR_SUCCESS; //succ
}
int compbzl_destroy() {
    return ERR_SUCCESS; //succ
}
 */

// #define CPOST_INSTRU_CLEAINST    0x00
// #define CPOST_INSTRU_EXPLAIN     0x01
// #define CPOST_INSTRU_REPLACE     0x02

int cole_post_instru_bzl(respo_ctrl *resctl, base_valu *baval, uint32 postyp, char *attach) {
    OSEVPF("[FUNC]:cole_post_instru_bzl\n");
    switch (postyp) {
        case CPOST_INSTRU_CLEAINST:
            OSEVPF("Clear lv2p instant\n");
            if (clear_insta(&baval->insda_stm)) {
                PDAT_EXCEPTIO_TAIL(resctl, LVTP_NOT_FOUND);
                return -1;
            }
            PDAT_PRODUCEN_TAIL(resctl)
            break;
        case CPOST_INSTRU_EXPLAIN:
            OSEVPF("Explain lv2p declare, attach:|%s|\n", attach);
            lv2p_expa_t *lv2expt = lv2expt_interp_bzl(baval, attach);
            if (!lv2expt) {
                PDAT_EXCEPTIO_TAIL(resctl, LVTP_NOT_FOUND);
                return -1;
            }
            post_lv2p_explain(resctl, lv2expt);
            free_lv2exp(lv2expt);
            break;
        case CPOST_INSTRU_REPLACE:
            OSEVPF("Replaceability lv2p, attach:|%s|\n", attach);
            char iexte_lv2pn[LVTN_LENGTH];
            if (check_iextec_ite(iexte_lv2pn, baval->base_name, attach)) {
                PDAT_EXCEPTIO_TAIL(resctl, LVTP_NOT_FOUND);
                return -1;
            }
            post_lv2p_iexter(resctl, iexte_lv2pn);
            break;
        default:
            _LOG_WARN("default: postyp");
            PDAT_EXCEPTIO_TAIL(resctl, LVTP_NOT_FOUND);
            return -1;
            break;
    }
    //
    return ERR_SUCCESS;
}

int invk_post_instru_bzl(respo_ctrl *resctl, base_valu *baval, lv2p_attri *lv2ai, uint32 postyp, char *attach) {
    OSEVPF("[FUNC]:invk_post_instru_bzl\n");
    switch (postyp) {
        case IPOST_INSTRU_REPLACE:
            if (valid_postm_insrep_lv2pn(lv2ai->lv2pn, attach)) {
                PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT);
                return -1;
            }
            OSEVPF("Replaceability lev1, attach:|%s|\n", attach);
            char iexte_lv2pn[LVTN_LENGTH];
            if (check_iextem_ite(iexte_lv2pn, baval->base_name, attach)) {
                PDAT_EXCEPTIO_TAIL(resctl, LEVO_NOT_FOUND);
                return -1;
            }
            post_lv2p_iexter(resctl, iexte_lv2pn);
            break;
        default:
            _LOG_WARN("default: postyp");
            PDAT_EXCEPTIO_TAIL(resctl, LEVO_NOT_FOUND);
            return -1;
            break;
    }
    //
    return ERR_SUCCESS;
}

// #define CPOST_ATTRIB_EXTERN   0x00

int cole_post_attrib_bzl(respo_ctrl *resctl, base_valu *baval, char *lv2pn, uint32 postyp, uint32 value) {
    OSEVPF("[FUNC]:cole_post_attrib_bzl\n");
    OSEVPF("lv2pn:%s, postyp:%u, value:%u\n", lv2pn, postyp, value);
    switch (postyp) {
        case CPOST_ATTRIB_EXTERN:
            OSEVPF("Set lv2p extern\n");
            if (updat_lv2p_extern(&baval->lv2pm_stm, baval->base_name, lv2pn, value)) {
                PDAT_EXCEPTIO_TAIL(resctl, LVTP_NOT_FOUND);
                return -1;
            }
            break;
        default:
            _LOG_WARN("default: postyp");
            PDAT_EXCEPTIO_TAIL(resctl, INVA_ATTRIB_EXPT);
            return -1;
            break;
    }
    //
    PDAT_PRODUCEN_TAIL(resctl)
    return ERR_SUCCESS;
}

int invk_post_attrib_bzl(respo_ctrl *resctl, base_valu *baval, lv2p_attri *lv2ai, uint32 postyp, uint32 value) {
    OSEVPF("[FUNC]:invk_post_attrib_bzl\n");
    OSEVPF("lv2pn:%s, postyp:%u, value:%u\n", lv2ai->lv2pn, postyp, value);
    switch (postyp) {
        case CPOST_ATTRIB_EXTERN:
            OSEVPF("Set lev1 extern\n");
            break;
        default:
            _LOG_WARN("default: postyp");
            PDAT_EXCEPTIO_TAIL(resctl, INVA_ATTRIB_EXPT);
            return -1;
            break;
    }
    //
    PDAT_PRODUCEN_TAIL(resctl)
    return ERR_SUCCESS;
}

//

int invk_stalst_bzl(respo_ctrl *resctl, char *basen, lev1_meta *lev1m) {
    OSEVPF("[FUNC]:invk_stalst_bzl\n");
    lv1_cont *l1con_list = NULL;
    if (build_l2meth_ite(&l1con_list, basen, lev1m->lv2pn)) {
        PDAT_EXCEPTIO_TAIL(resctl, LVTP_NOT_FOUND);
        return -1;
    }
    OSEVPF("1\n");
    if (HAVE_DECLA & lev1m->layout) {
        list_lev1_fmtsp(resctl, lev1m->lev1n, lev1m->oivk_fmtsp_om, l1con_list);
    } else if (HAVE_METHN & lev1m->layout) {
        list_lev1_iden(resctl, lev1m->lev1n, l1con_list);
    } else list_lev1_lv2p(resctl, l1con_list);
    l1clst_dele(l1con_list);
    OSEVPF("2\n");
    //
    return 0x00;
}

//

int invk_stasti_bzl(respo_ctrl *resctl, char *basen, char *lv2pn) {
    OSEVPF("[FUNC]:invk_stasti_bzl\n");
    OSEVPF("basen:|%s| lv2pn:|%s|\n", basen, lv2pn);
    lev1_list *l1lst = NULL;
    if (lev1_list_lv2pn(&l1lst, basen, lv2pn)) {
        PDAT_EXCEPTIO_TAIL(resctl, RELOA_INVOK_EXPT)
        return -1;
    }
    stat_lev1_stai(resctl, lv2pn, l1lst);
    dele_lev1_list(l1lst);
    //
    return 0x00;
}

// trans-serve
#define LIST_LVTP_OBJID     0x0001
#define LIST_LVTP_ATTRIB    0x0002
#define LIST_LVTP_INHERI    0x0004
#define LIST_LVTP_EXPAND    0x0010
#define LIST_LVTP_CONTEN    0x0020

int cole_stalst_lv2pn_bzl(respo_ctrl *resctl, lv2pm_hmap *lv2pm_stm, char *basen, char *lv2pn, uint32 list_layou) {
    OSEVPF("[FUNC]:cole_stalst_lv2pn_bzl\n");
    PDAT_PRODUCE_INITI(resctl)
    //
    OSEVPF("lv2pn:|%s| list_layou:|%08X|\n", lv2pn, list_layou);
    if ((LIST_LVTP_OBJID | LIST_LVTP_ATTRIB | LIST_LVTP_INHERI) & list_layou) {
        lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lv2pn, lv2pm_stm->lv2pan_hm);
        if (!lv2ai) {
            PDAT_EXCEPTIO_TAIL(resctl, LVTP_NOT_FOUND);
            return -1;
        }
        if (LIST_LVTP_OBJID & list_layou)
            list_lv2p_objid(resctl, lv2ai);
        //
        if (LIST_LVTP_ATTRIB & list_layou)
            list_lv2p_attri(resctl, lv2ai);
        //
        if (LIST_LVTP_INHERI & list_layou)
            list_lv2p_inheri(resctl, lv2ai);
    }
    if (LIST_LVTP_EXPAND & list_layou) {
        lv2p_expa_t *lv2expt = load_lv2expt_ite(basen, lv2pn);
        if (!lv2expt) {
            PDAT_EXCEPTIO_TAIL(resctl, LVTP_NOT_FOUND);
            return -1;
        }
        list_lv2p_expand(resctl, lv2expt);
        free_lv2exp(lv2expt);
    }
    if (LIST_LVTP_CONTEN & list_layou) {
        lv2p_decl_i lv2di;
        if (!build_l2con_ite(&lv2di, basen, lv2pn)) {
            PDAT_EXCEPTIO_TAIL(resctl, LVTP_NOT_FOUND);
            RETU_DELM(lv2di, -1);
        }
        list_lv2p_meta(resctl, &lv2di);
        CLAM_STRU_DELE(lv2di);
    }
    //
    PDAT_PRODUCE_FINAL(resctl)
    OSEVPF("execu_str:|%s|\n", resctl->resp_memo);
    return 0x00;
}

int cole_stalst_whole_bzl(respo_ctrl *resctl, char *basen) {
    OSEVPF("[FUNC]:cole_stalst_lv2pn_bzl\n");
    PDAT_PRODUCE_INITI(resctl)
            //
            char lv2pt_path[MAX_PATH * 3];
    char *lv2p_arra[LVTP_COUNT];
    char _cline_[LARGE_CONTE_SIZE];
    CREAT_CLASS_DIRECTORY(lv2pt_path, basen);
    if (list_clas(lv2p_arra, _cline_, lv2pt_path)) {
        PDAT_EXCEPTIO_TAIL(resctl, LVTP_INFO_EXPT);
        return -1;
    }
    //
    stai_l2noi_head(resctl);
    osv_oid_t lv2p_obid;
    char **lv2np = lv2p_arra;
    for (; lv2np[0x00]; ++lv2np) {
        // OSEVPF("lv2np:|%s|\n", lv2np[0x00]);
        LVTP_ATTRI_FILE(lv2pt_path, basen, lv2np[0x00])
                // OSEVPF("lv2pt_path:|%s|\n", lv2pt_path);
        if (!find_l2oid_ite(&lv2p_obid, lv2pt_path)) {
            PDAT_EXCEPTIO_TAIL(resctl, LVTP_NOT_FOUND);
            return -1;
        }
        // OSEVPF("lv2p_aico:|%s|\n", lv2p_aico);
        stai_lv2pn_objid(resctl, lv2np[0x00], &lv2p_obid);
    }
    stai_l2noi_end(resctl);
    //
    PDAT_PRODUCE_FINAL(resctl)
    OSEVPF("execu_str:|%s|\n", resctl->resp_memo);
    return 0x00;
}

// invk_stasti_bzl

int cole_stasti_lv2po_bzl(respo_ctrl *resctl, base_valu *baval, osv_oid_t *lv2p_obid) {
    OSEVPF("[FUNC]:cole_stasti_lv2po_bzl\n");
    OSEVPF("baval->base_name:|%s|\n", baval->base_name);
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lv2p_obid, baval->lv2pm_stm.lv2pao_hm);
    if (!lv2ai) {
        PDAT_EXCEPTIO_TAIL(resctl, RELOA_INVOK_EXPT)
        return -1;
    }
    //
    lev1_list *l1lst = NULL;
    if (lev1_list_lv2pn(&l1lst, baval->base_name, lv2ai->lv2pn)) {
        PDAT_EXCEPTIO_TAIL(resctl, RELOA_INVOK_EXPT)
        return -1;
    }
    stat_lev1_stai(resctl, lv2ai->lv2pn, l1lst);
    dele_lev1_list(l1lst);
    //
    return 0x00;
}

// invk_stasti_bzl

int cole_stasti_lv2pn_bzl(respo_ctrl *resctl, char *basen, char *lv2pn) {
    OSEVPF("[FUNC]:cole_stasti_lv2pn_bzl\n");
    OSEVPF("basen:|%s| lv2pn:|%s|\n", basen, lv2pn);
    lev1_list *l1lst = NULL;
    if (lev1_list_lv2pn(&l1lst, basen, lv2pn)) {
        PDAT_EXCEPTIO_TAIL(resctl, RELOA_INVOK_EXPT)
        return -1;
    }
    stat_lev1_stai(resctl, lv2pn, l1lst);
    dele_lev1_list(l1lst);
    //
    return 0x00;
}

int cole_stasti_whole_bzl(respo_ctrl *resctl, char *basen) {
    OSEVPF("[FUNC]:cole_stasti_whole_bzl\n");
    PDAT_PRODUCE_INITI(resctl)
            //
            char lv2pt_path[MAX_PATH * 3];
    char *lv2p_arra[LVTP_COUNT];
    char _cline_[LARGE_CONTE_SIZE];
    CREAT_CLASS_DIRECTORY(lv2pt_path, basen);
    // OSEVPF("lv2pt_path:|%s|\n", lv2pt_path);
    if (list_clas(lv2p_arra, _cline_, lv2pt_path)) {
        PDAT_EXCEPTIO_TAIL(resctl, LVTP_INFO_EXPT);
        return -1;
    }
    //
    stai_l2noi_head(resctl);
    osv_oid_t lv2p_obid;
    char **lv2np = lv2p_arra;
    for (; lv2np[0x00]; ++lv2np) {
        // OSEVPF("--- lv2np:|%s|\n", lv2np[0x00]);
        LVTP_ATTRI_FILE(lv2pt_path, basen, lv2np[0x00])
                // OSEVPF("lv2pt_path:|%s|\n", lv2pt_path);
        if (!find_l2oid_ite(&lv2p_obid, lv2pt_path)) {
            PDAT_EXCEPTIO_TAIL(resctl, LVTP_NOT_FOUND);
            return -1;
        }
        // OSEVPF("lv2p_aico:|%s|\n", lv2p_aico);
        stai_lv2pn_objid(resctl, lv2np[0x00], &lv2p_obid);
    }
    stai_l2noi_end(resctl);
    //
    PDAT_PRODUCE_FINAL(resctl)
    OSEVPF("execu_str:|%s|\n", resctl->resp_memo);
    return 0x00;
}


//

int invk_drop_conte_bzl(char *basen, lev1_meta *lev1m) {
    OSEVPF("[FUNC]:invk_drop_conte_bzl.\n");
    delet_conte_lev1m(basen, lev1m);
    OSEVPF("1.\n");
    char lv2d_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2d_path, basen, lev1m->lv2pn);
    lv2p_decl_i lv2di;
    INIT_LVTP_DECL(lv2di)
    if (!parse_l2con_ite(&lv2di, lv2d_path)) RETU_DELM(lv2di, -1);
    OSEVPF("2.\n");
    //
    lv1_cont *l1c_nod = dele_l1cnod_iden(&lv2di.l1con_list, lev1m->lev1n, lev1m->oivk_fmtsp_om);
    OSEVPF("3.\n");
    if (!l1c_nod) RETU_DELM(lv2di, -1);
    LVOCND_DELE(l1c_nod);
    if (save_l2dec_ite(lv2d_path, &lv2di)) RETU_DELM(lv2di, -1);
    //
    OSEVPF("4.\n");
    CLAM_STRU_DELE(lv2di);
    return 0x00;
}

int cole_drop_conte_bzl(char *basen, char *lv2pn) {
    OSEVPF("[FUNC]:cole_drop_conte_bzl\n");
    delet_conte_lv2p(lv2pn, basen);
    //    
    char lv2d_path[MAX_PATH * 3];
    char lv2t_path[MAX_PATH * 3];
    char lv2e_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2d_path, basen, lv2pn);
    LVTP_ATTRI_FILE(lv2t_path, basen, lv2pn);
    LVTP_EXPAN_FILE(lv2e_path, basen, lv2pn);
    if (delet_l2con_ite(lv2d_path, lv2t_path, lv2e_path))
        return -1;
    return 0x00;
}

//

int conv_meth_bzl(char *clang_cont, char *basen, lev1_meta *lev1m, char *lev1_cont) {
    OSEVPF("[FUNC]:conv_meth_bzl.\n");
    char lv2p_cont[LARGE_TEXT_SIZE];
    if (!filli_l2dec_ite(lv2p_cont, basen, lev1m->lv2pn))
        return -1;
    // -1:error 0x00:constructor 0x01:normal
    int norma_const = chk_norma_const(lv2p_cont, lev1m->lev1n);
    if (-1 == norma_const) return -1;
    OSEVPF("2. norma_const:%d\n", norma_const);
    if (metho_clang_ite(clang_cont, lev1_cont, lv2p_cont, norma_const))
        return -1;
    OSEVPF("3.\n");
    //
    return 0x00;
}

//

int conv_imet_bzl(char *clang_cont, char *basen, lev1id *lev1i, char *lev1_cont) {
    OSEVPF("[FUNC]:conv_imet_bzl\n");
    char lv2p_cont[LARGE_TEXT_SIZE];
    if (!filli_l2dec_ite(lv2p_cont, basen, lev1i->crea_lv2pn))
        return -1;
    if (imeth_clang_ite(clang_cont, lev1_cont, lv2p_cont, lev1i))
        return -1;
    //
    return 0x00;
}

int conv_ilv1_bzl(char *clang_cont, char *basen, lev1id *lev1i, char *lev1_cont) {
    OSEVPF("[FUNC]:conv_ilv1_bzl\n");
    char lv2p_decl[LARGE_TEXT_SIZE];
    char clas_decl[LARGE_TEXT_SIZE];
    if (!filli_l2dec_ite(lv2p_decl, basen, lev1i->crea_lv2pn))
        return -1;
    if (!filli_l2dec_ite(clas_decl, basen, lev1i->supe_lv2pn))
        return -1;
    if (ilev1_clang_ite(clang_cont, lv2p_decl, lev1_cont, clas_decl, lev1i))
        return -1;
    //
    return 0x00;
}

//

int invk_repla_bzl(char *clang_cont, char *basen, lev1_meta *lev1m, char *lev1_cont) {
    OSEVPF("[FUNC]:invk_repla_bzl\n");
    char lv2p_cont[LARGE_TEXT_SIZE];
    if (!filli_l2dec_ite(lv2p_cont, basen, lev1m->lv2pn))
        return -1;
    // -1:error 0x00:constructor 0x01:normal
    int norma_const = chk_norma_const(lv2p_cont, lev1m->lev1n);
    if (-1 == norma_const) return -1;
    if (metho_clang_ite(clang_cont, lev1_cont, lv2p_cont, norma_const))
        return -1;
    //
    OSEVPF("invk_repla_bzl, clang_cont:|%s|\n", clang_cont);
    return 0x00;
}

//

int invk_reloa_bzl(char *clang_cont, char *basen, lev1_meta *lev1m) {
    OSEVPF("[FUNC]:invk_reloa_bzl\n");
    char lv2d_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2d_path, basen, lev1m->lv2pn);
    lv2p_decl_i lv2di;
    INIT_LVTP_DECL(lv2di)
    if (!parse_l2con_ite(&lv2di, lv2d_path)) RETU_DELM(lv2di, -1);
    //
    lv1_cont *l1c_nod = find_l1cnod_iden(lv2di.l1con_list, lev1m->lev1n, lev1m->oivk_fmtsp_om);
    if (!l1c_nod) RETU_DELM(lv2di, -1);
    int norma_const = gener_const_type(lev1m->lv2pn, lev1m->lev1n);
    if (metho_clang_ite(clang_cont, l1c_nod->conte, lv2di.lv2p_decl, norma_const))
        RETU_DELM(lv2di, -1);
    //
    CLAM_STRU_DELE(lv2di);
    return 0x00;
}

//

int split_cprop_bzl(char (*lv2p_prop)[PARAM_LENGTH], char *basen, char *lv2pn) {
    // OSEVPF("[FUNC]:split_cprop_bzl\n");
    char lv2d_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2d_path, basen, lv2pn);
    // OSEVPF("lv2d_path:|%s| base:|%s| lv2pn:|%s|\n", lv2d_path, basen, lv2pn);
    char lv2p_decl[LARGE_TEXT_SIZE];
    if (!split_l2dec_ite(lv2p_decl, lv2d_path))
        return -1;
    // OSEVPF("lv2p_decl:|%s|\n", lv2p_decl);
    if (split_class_prope(lv2p_prop, lv2p_decl))
        return -1;
    // OSEVPF("lv2pn:|%s|\n", lv2pn);
    return 0x00;
}

//

int cole_creat_bzl(lv2p_expa_t *lv2expt, char *basen, lv2p_decl_t * lv2dt) {
    OSEVPF("cole_creat_bzl\n");
    if (lv2p_clang_ite(lv2expt->lv2nod, basen, lv2dt))
        return -1;
    lv2expt->lv2o_coun = LVTP_EXCOUN_ITE(lv2expt->lv2nod);
    if (meth_expand_ite(lv2expt->lv1dat, basen, lv2dt))
        return -1;
    lv2expt->lv1d_coun = LEVO_EXCOUN_ITE(lv2expt->lv1dat);
    //
    return 0x00;
}

int cole_repla_bzl(lv2p_expa_t *lv2expt, char *basen, lv2p_decl_t * lv2dt) {
    OSEVPF("cole_repla_bzl\n");
    if (lv2p_clang_ite(lv2expt->lv2nod, basen, lv2dt))
        return -1;
    lv2expt->lv2o_coun = LVTP_EXCOUN_ITE(lv2expt->lv2nod);
    if (meth_expand_ite(lv2expt->lv1dat, basen, lv2dt))
        return -1;
    lv2expt->lv1d_coun = LEVO_EXCOUN_ITE(lv2expt->lv1dat);
    //
    return 0x00;
}

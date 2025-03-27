#include "commo_header.h"
#include "kcomm_header.h"

#include "invok_bzl.h"
#include "invok_utili.h"
#include "conte_bzl.h"
#include "debug_funct_ci.h"

#include "hand_invok.h"
#define IPAM_POST_TYPE    0x00
//
// [txxt]lev1> odb:post(INSTRU); // instru
// [txxt]lev1> odb:post(REPLACE, "txxt:tpp"); // replaceability
// instru
#define IPAM_POST_INTYP    0x00
#define IPAM_POST_ATTACH   0x01
// 
// [txxt]lev1> odb:post(ATTRIB, VALUE); // set lv2p value;
// set lv2p value;
// #define IPAM_POST_LVTPN    0x00
#define IPAM_POST_ATTYP    0x00
#define IPAM_POST_VALUE    0x01

int invok_post_hand(respo_ctrl *resctl, base_valu *baval, osv_oid_t *lv2p_obid, pams_valu *pamvu) {
    OSEVPF("[FUNC]:invok_post_hand\n");
    // pamvu = 1 = 2
    if (!pamvu->pamtyp[0x00] || (pamvu->pamtyp[0x01] && pamvu->pamtyp[0x02])) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    //
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lv2p_obid, baval->lv2pm_stm.lv2pao_hm);
    if (!lv2ai) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("lv2ai not found\n");
        return -1;
    }
    OSEVPF("lv2ai->lv2pn:|%s|\n", lv2ai->lv2pn);
    //
    switch (pamvu->pamtyp[IPAM_POST_TYPE]) {
        case DATY_INVAL:
            _LOG_WARN("case: DATY_INVAL");
            PDAT_EXCEPTIO_TAIL(resctl, IPAM_POST_TYPE)
            return -1;
            break;
        case DATY_UINT:
            if (invk_post_instru_bzl(resctl, baval, lv2ai, ((uint32 *) pamvu->pamcon[IPAM_POST_INTYP])[0x00], pamvu->pamcon[IPAM_POST_ATTACH]))
                return -1;
            break;
        case DATY_STRI:
            if (invk_post_attrib_bzl(resctl, baval, lv2ai, ((uint32 *) pamvu->pamcon[IPAM_POST_ATTYP])[0x00], ((uint32 *) pamvu->pamcon[IPAM_POST_VALUE])[0x00]))
                return -1;
            break;
        default:
            _LOG_WARN("default: CPAM_POST_TYPE");
            PDAT_EXCEPTIO_TAIL(resctl, IPAM_POST_TYPE)
            return -1;
            break;
    }
    //
    return 0x00;
}

// invoke
// [txxt]lev1> odb:list("txxt");
// [txxt]lev1> odb:list("txxt:txp");
// [txxt]lev1> odb:list("taat:tpp<(x int), (a int)int>");
// [txxt]lev1> odb:list("taat:tpp(a int, int)");

#define IPAM_LIST_LVOID   0x00

int invok_statu_list_hand(respo_ctrl *resctl, base_valu *baval, osv_oid_t *lv2p_obid, pams_valu *pamvu) {
    OSEVPF("[FUNC]:invok_statu_list_hand\n");
    // pamvu = 1
    if (!pamvu->pamcon[0x00] || pamvu->pamcon[0x01]) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    //
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lv2p_obid, baval->lv2pm_stm.lv2pao_hm);
    if (!lv2ai) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("lv2ai not found\n");
        return -1;
    }
    OSEVPF("lv2ai->lv2pn:|%s|\n", lv2ai->lv2pn);
    //
    lev1_meta lev1m;
    if (build_metho_ident(&lev1m, pamvu->pamcon[IPAM_LIST_LVOID])) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    PRIN_lev1_meta(&lev1m);
    if (valid_statm_list_ite(baval->base_name, lv2ai->lv2pn, &lev1m)) {
        PDAT_EXCEPTIO_TAIL(resctl, INVOK_NOT_FOUND)
        return -1;
    }
    if (invk_stalst_bzl(resctl, baval->base_name, &lev1m))
        return -1;
    //
    return 0x00;
}

// #define IPAM_STATI_LVTPN   0x00

int invok_statu_stati_hand(respo_ctrl *resctl, base_valu *baval, osv_oid_t *lv2p_obid, pams_valu *pamvu) {
    OSEVPF("[FUNC]:invok_statu_stati_hand\n");
    // pamvu = 0
    if (pamvu->pamcon[0x00]) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    //
#ifdef _DEBUG
    char obid_stri[OBJE_IDENTI_ZLEN];
    OSEVPF("lv2p_obid:|%s|\n", oidstr(obid_stri, lv2p_obid));
#endif
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lv2p_obid, baval->lv2pm_stm.lv2pao_hm);
    if (!lv2ai) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("lv2ai not found\n");
        return -1;
    }
    OSEVPF("lv2ai->lv2pn:|%s|\n", lv2ai->lv2pn);
    //
    if (valid_statm_stati_ite(baval->base_name, lv2ai->lv2pn)) {
        PDAT_EXCEPTIO_TAIL(resctl, INVOK_NOT_FOUND)
        return -1;
    }
    if (invk_stasti_bzl(resctl, baval->base_name, lv2ai->lv2pn))
        return -1;
    //
    return 0x00;
}

// [txxt]lev1> txxt:txp<(hx int), (aa int, bb int)int> {hx = aa; return hx;}
// [txxt]lev1> taat:tpp<(hx int), (aa int, bb int)int> {hx = aa; return hx;}
#define IPAM_CREAT_CONTE   0x00

int invok_creat_hand(respo_ctrl *resctl, base_valu *baval, osv_oid_t *lv2p_obid, pams_valu *pamvu) {
    OSEVPF("[FUNC]:invok_creat_hand\n");
    // pamvu = 1
    if (!pamvu->pamcon[0x00] || pamvu->pamcon[0x01]) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    //
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lv2p_obid, baval->lv2pm_stm.lv2pao_hm);
    if (!lv2ai) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("lv2ai not found\n");
        return -1;
    }
    OSEVPF("lv2ai->lv2pn:|%s|\n", lv2ai->lv2pn);
    //
    lev1_meta lev1m;
    if (build_metho_conte(&lev1m, pamvu->pamcon[IPAM_CREAT_CONTE])) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    PRIN_lev1_meta(&lev1m);
    if (valid_cream_ite(baval->base_name, lv2ai->lv2pn, &lev1m)) {
        robk_cream_bzl(&baval->lv2pm_stm, baval->base_name, &lev1m);
        PDAT_EXCEPTIO_TAIL(resctl, INVOK_NOT_FOUND)
        return -1;
    }
    //
    char clang_cont[CLANG_CONTE_SIZE];
    MK_ZERO(clang_cont);
    if (conv_meth_bzl(clang_cont, baval->base_name, &lev1m, pamvu->pamcon[IPAM_CREAT_CONTE])) {
        robk_cream_bzl(&baval->lv2pm_stm, baval->base_name, &lev1m);
        PDAT_EXCEPTIO_TAIL(resctl, CREAT_INVOK_EXPT)
        return -1;
    }
    //
    PRIN_lev1_clang(clang_cont);
    char libr_path[MAX_PATH * 3];
    if (hcrea_metho_bzl(resctl, libr_path, clang_cont, baval->base_name, &lev1m)) {
        robk_cream_bzl(&baval->lv2pm_stm, baval->base_name, &lev1m);
        return -1;
    }
    if (creat_lv1me_bzl(&baval->hando_stm, &baval->lv2pm_stm, libr_path, baval->base_name, &lev1m)) {
        robk_cream_bzl(&baval->lv2pm_stm, baval->base_name, &lev1m);
        PDAT_EXCEPTIO_TAIL(resctl, CREAT_LVOME_EXPT)
        return -1;
    }
    if (recod_cream_bzl(baval->base_name, &lev1m, pamvu->pamcon[IPAM_CREAT_CONTE])) {
        robk_cream_bzl(&baval->lv2pm_stm, baval->base_name, &lev1m);
        PDAT_EXCEPTIO_TAIL(resctl, CREAT_INVOK_EXPT)
        return -1;
    }
    if (integ_cream_ite(&baval->lv2pm_stm, baval->base_name, &lev1m)) {
        robk_cream_bzl(&baval->lv2pm_stm, baval->base_name, &lev1m);
        PDAT_EXCEPTIO_TAIL(resctl, CREAT_INVOK_EXPT)
        return -1;
    }
    //
    PDAT_PRODUCEN_TAIL(resctl)
    return 0x00;
}

//
#define IPAM_RELOSD_IDENT   0x00

int invok_reload_hand(respo_ctrl *resctl, base_valu *baval, osv_oid_t *lv2p_obid, pams_valu *pamvu) {
    OSEVPF("[FUNC]:invok_reload_hand\n");
    // pamvu = 0 = 1
    if (pamvu->pamcon[0x00] && pamvu->pamcon[0x01]) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    //
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lv2p_obid, baval->lv2pm_stm.lv2pao_hm);
    if (!lv2ai) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("lv2ai not found\n");
        return -1;
    }
    OSEVPF("lv2ai->lv2pn:|%s|\n", lv2ai->lv2pn);
    //
    lev1_meta lev1m;
    if (pamvu->pamcon[IPAM_RELOSD_IDENT]) {
        if (build_metho_ident(&lev1m, pamvu->pamcon[IPAM_RELOSD_IDENT])) {
            PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
            OSEVPF("PAMVU EXCEPITON!\n");
            return -1;
        }
        if (valid_relom_ite(lv2ai->lv2pn, &lev1m)) {
            PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
            return -1;
        }
        PRIN_lev1_meta(&lev1m);
        if ((HAVE_DECLA & lev1m.layout) && (HAVE_METHN & lev1m.layout) && (HAVE_CLASN & lev1m.layout)) {
            if (relom_decla(resctl, &baval->hando_stm, &baval->lv2pm_stm, baval->base_name, &lev1m))
                return -1;
        } else if ((HAVE_METHN & lev1m.layout) && (HAVE_CLASN & lev1m.layout)) {
            if (relom_metho(resctl, &baval->hando_stm, &baval->lv2pm_stm, baval->base_name, &lev1m))
                return -1;
        } else if ((HAVE_CLASN & lev1m.layout)) {
            if (relom_clasn(resctl, &baval->hando_stm, &baval->lv2pm_stm, baval->base_name, &lev1m))
                return -1;
        }
    } else {
        if (relom_whole(resctl, &baval->hando_stm, &baval->lv2pm_stm, baval->base_name))
            return -1;
    }
    //
    PDAT_PRODUCEN_TAIL(resctl)
    return 0x00;
}

//
#define IPAM_DROP_IDENT   0x00
// [txxt]lev1> odb:drop("txxt:tpp<(x int), (a int)int>");
// [txxt]lev1> odb:drop("txxt:txp(aa int, bb int)"); // out invoke

int invok_drop_hand(respo_ctrl *resctl, base_valu *baval, osv_oid_t *lv2p_obid, pams_valu *pamvu) {
    OSEVPF("[FUNC]:invok_drop_hand\n");
    // pamvu = 1
    if (!pamvu->pamcon[0x00] || pamvu->pamcon[0x01]) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    //
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lv2p_obid, baval->lv2pm_stm.lv2pao_hm);
    if (!lv2ai) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("lv2ai not found\n");
        return -1;
    }
    OSEVPF("lv2ai->lv2pn:|%s|\n", lv2ai->lv2pn);
    //
    lev1_meta lev1m;
    if (build_metho_ident(&lev1m, pamvu->pamcon[IPAM_DROP_IDENT])) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        return -1;
    }
    PRIN_lev1_meta(&lev1m);
    if (valid_dropm_ite(resctl, baval->base_name, lv2ai->lv2pn, &lev1m))
        return -1;
    if (hdrop_metho_bzl(&baval->hando_stm, baval->base_name, &lev1m)) {
        PDAT_EXCEPTIO_TAIL(resctl, DROP_INVOK_HAND)
        return -1;
    }
    if (invk_drop_conte_bzl(baval->base_name, &lev1m)) {
        PDAT_EXCEPTIO_TAIL(resctl, DROP_INVOK_CONTE)
        return -1;
    }
    if (integ_dropm_ite(&baval->lv2pm_stm, baval->base_name, &lev1m)) {
        PDAT_EXCEPTIO_TAIL(resctl, DROP_INVOK_INTE)
        return -1;
    }
    //
    PDAT_PRODUCEN_TAIL(resctl)
    return 0x00;
}

//
#define IPAM_REPLACE_CONTE   0x00
#define IPAM_FORCED_REPLA    0x01

int invok_repla_hand(respo_ctrl *resctl, base_valu *baval, osv_oid_t *lv2p_obid, pams_valu *pamvu) {
    OSEVPF("[FUNC]:invok_repla_hand\n");
    // pamvu = 1 = 2
    if (!pamvu->pamcon[0x00] || (pamvu->pamcon[0x01] && pamvu->pamcon[0x02])) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    //
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lv2p_obid, baval->lv2pm_stm.lv2pao_hm);
    if (!lv2ai) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("lv2ai not found\n");
        return -1;
    }
    OSEVPF("lv2ai->lv2pn:|%s|\n", lv2ai->lv2pn);
    //   
    lev1_meta nlev1m;
    if (build_metho_conte(&nlev1m, pamvu->pamcon[IPAM_REPLACE_CONTE])) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        return -1;
    }
    PRIN_lev1_meta(&nlev1m);
    if (valid_replm_ite(baval->base_name, lv2ai->lv2pn, &nlev1m, (uint32 *) pamvu->pamcon[IPAM_FORCED_REPLA])) {
        PDAT_EXCEPTIO_TAIL(resctl, REQUE_VALID_EXPT)
        return -1;
    }
    //
    char clang_cont[CLANG_CONTE_SIZE];
    MK_ZERO(clang_cont);
    if (invk_repla_bzl(clang_cont, baval->base_name, &nlev1m, pamvu->pamcon[IPAM_REPLACE_CONTE])) {
        PDAT_EXCEPTIO_TAIL(resctl, CREAT_INVOK_EXPT)
        return -1;
    }
    //
    replm_envir envrpm;
    if (prote_replm_bzl(&envrpm, &baval->hando_stm, baval->base_name, &nlev1m)) {
        cancel_replm_bzl(&baval->hando_stm, &baval->lv2pm_stm, baval->base_name, &envrpm);
        PDAT_EXCEPTIO_TAIL(resctl, REPLA_INVOK_EXPT)
        return -1;
    }
    PRIN_replm_envir(&envrpm);
    char libr_path[MAX_PATH * 3];
    if (hrepl_metho_bzl(resctl, libr_path, clang_cont, baval->base_name, &nlev1m)) {
        robk_replm_bzl(&baval->hando_stm, &baval->lv2pm_stm, baval->base_name, &envrpm);
        return -1;
    }
    if (repla_lv1me_bzl(&baval->hando_stm, &baval->lv2pm_stm, libr_path, baval->base_name, &nlev1m)) {
        robk_replm_bzl(&baval->hando_stm, &baval->lv2pm_stm, baval->base_name, &envrpm);
        PDAT_EXCEPTIO_TAIL(resctl, CREAT_LVOME_EXPT)
        return -1;
    }
    if (recod_replm_bzl(&baval->lv2pm_stm, baval->base_name, &nlev1m, pamvu->pamcon[IPAM_REPLACE_CONTE])) {
        robk_replm_bzl(&baval->hando_stm, &baval->lv2pm_stm, baval->base_name, &envrpm);
        PDAT_EXCEPTIO_TAIL(resctl, REPLA_INVOK_EXPT)
        return -1;
    }
    if (integ_replm_ite(&baval->lv2pm_stm, baval->base_name, &nlev1m)) {
        robk_replm_bzl(&baval->hando_stm, &baval->lv2pm_stm, baval->base_name, &envrpm);
        PDAT_EXCEPTIO_TAIL(resctl, REPLA_INVOK_EXPT)
        return -1;
    }
    destr_replm_bzl(&envrpm, baval->base_name);
    //
    PDAT_PRODUCEN_TAIL(resctl)
    return 0x00;
}

//
#define IPAM_INTEGRA_INENT    0x00

int invok_integra_hand(respo_ctrl *resctl, base_valu *baval, osv_oid_t *lv2p_obid, pams_valu *pamvu) {
    OSEVPF("[FUNC]:invok_integra_hand\n");
    // pamvu = 0 = 1
    if (pamvu->pamcon[0x00] && pamvu->pamcon[0x01]) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    //
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lv2p_obid, baval->lv2pm_stm.lv2pao_hm);
    if (!lv2ai) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("lv2ai not found\n");
        return -1;
    }
    OSEVPF("lv2ai->lv2pn:|%s|\n", lv2ai->lv2pn);
    //
    if (pamvu->pamcon[IPAM_INTEGRA_INENT]) {
        lev1_meta lev1m;
        if (build_metho_ident(&lev1m, pamvu->pamcon[IPAM_INTEGRA_INENT])) {
            PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
            return -1;
        }
        PRIN_lev1_meta(&lev1m);
        if (valid_intem_ite(baval->base_name, lv2ai->lv2pn, &lev1m)) {
            PDAT_EXCEPTIO_TAIL(resctl, INVOK_NOT_FOUND)
            return -1;
        }
        if (integ_metho_ident_ite(resctl, baval->base_name, &lev1m))
            return -1;
    } else { // empty
        if (integ_metho_empty_ite(resctl, baval->base_name, lv2ai->lv2pn))
            return -1;
    }
    //
    return 0x00;
}

//
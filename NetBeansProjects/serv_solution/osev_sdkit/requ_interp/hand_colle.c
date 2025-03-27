#include "commo_header.h"
#include "kcomm_header.h"

#include "invok_bzl.h"
#include "conte_bzl.h"
#include "robk_lv2p_bzl.h"
#include "colle_utili.h"
#include "seion_struct.h"
#include "debug_funct_ci.h"
#include "lv2p_expand.h"

#include "hand_colle.h"

//
#define CPAM_POST_TYPE    0x00
// odb-lv2p> kits:expand("<[xx int32, ax int32, cx int32], tpp(cx, ax, xx)>") | kits:format(XML);
#define CPAM_POST_INTYP    0x00
// odb-lv2p> odb:post(INSTRU); // instru
// odb-lv2p> odb:post(CLEAR_INSTANT);
// odb-lv2p> :post(EXPLAIN, "<[xx int32, ax int32, cx int32]>");
// odb-lv2p> :post(REPLACE, "txxt"); // replaceability
// instru
#define CPAM_POST_INTYP    0x00
#define CPAM_POST_ATTACH   0x01
// 
// odb-lv2p> :post(lv2pn, ATTRIB, VALUE); // set lv2p value;
// odb-lv2p> :post("txxt", EXTERN, TRUE);
// odb-lv2p> :post("txxt", EXTERN, FALSE);
// set lv2p value;
#define CPAM_POST_LVTPN    0x00
#define CPAM_POST_ATTYP    0x01
#define CPAM_POST_VALUE    0x02

int colle_post_hand(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:colle_post_hand\n");
    // pamvu = 1 = 2 = 3
    if (!pamvu->pamtyp[0x00] || (pamvu->pamtyp[0x01] && pamvu->pamtyp[0x02] && pamvu->pamtyp[0x03])) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    //
    switch (pamvu->pamtyp[CPAM_POST_TYPE]) {
        case DATY_INVAL:
            _LOG_WARN("case: DATY_INVAL");
            PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
            return -1;
            break;
        case DATY_UINT:
            if (cole_post_instru_bzl(resctl, baval, ((uint32 *) pamvu->pamcon[CPAM_POST_INTYP])[0x00], pamvu->pamcon[CPAM_POST_ATTACH]))
                return -1;
            break;
        case DATY_STRI:
            if (cole_post_attrib_bzl(resctl, baval, pamvu->pamcon[CPAM_POST_LVTPN], ((uint32 *) pamvu->pamcon[CPAM_POST_ATTYP])[0x00], ((uint32 *) pamvu->pamcon[CPAM_POST_VALUE])[0x00]))
                return -1;
            break;
        default:
            _LOG_WARN("default: CPAM_POST_TYPE");
            PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
            return -1;
            break;
    }
    //
    return 0x00;
}

// colle
// odb-lv2p> :invok_statu_list_hand();
// odb-lv2p> :status:list() | kits:format(XML);
// odb-lv2p> :status:list(lv2pn) => odb:list(lv2pn, "OBJID|ATTRIB|INHERIT|CONTENT");
// odb-lv2p> :status:list(lv2pn, "OBJID|ATTRIB|INHERIT|CONTENT");
// odb-lv2p> :status:list(lv2pn, ATTRIB);
// odb-lv2p> :status:list(lv2pn, ATTRIB|INHERIT);
// odb-lv2p> :status:list(lv2pn, ATTRIB|EXPAND);
// odb-lv2p> :list:statis() | kits:format(XML);

#define CPAM_LIST_LVTPN   0x00
#define CPAM_LIST_LAYOU   0x01

int colle_statu_list_hand(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:colle_statu_list_hand\n");
    // pamvu = 0 = 2
    if ((pamvu->pamtyp[0x00] && !pamvu->pamtyp[0x01]) || (pamvu->pamtyp[0x00] && pamvu->pamtyp[0x02])) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    //
    if (valid_listc_ite(&baval->lv2pm_stm, pamvu->pamcon[CPAM_LIST_LVTPN])) {
        PDAT_EXCEPTIO_TAIL(resctl, LVTP_NOT_FOUND);
        return -1;
    }
    if (pamvu->pamtyp[CPAM_LIST_LVTPN]) {
        if (cole_stalst_lv2pn_bzl(resctl, &baval->lv2pm_stm, baval->base_name, pamvu->pamcon[CPAM_LIST_LVTPN], ((uint32 *) pamvu->pamcon[CPAM_LIST_LAYOU])[0x00]))
            return -1;
    } else {
        if (cole_stalst_whole_bzl(resctl, baval->base_name))
            return -1;
    }
    //
    return 0x00;
}

#define CPAM_STAI_TYPE    0x00
#define CPAM_STATI_LVTPN   0x00
#define CPAM_STATI_LVTPO   0x00

int colle_statu_stati_hand(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:colle_statu_stati_hand\n");
    // pamvu = 0 = 1
    if (pamvu->pamtyp[0x00] && pamvu->pamtyp[0x01]) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    //
    switch (pamvu->pamtyp[CPAM_STAI_TYPE]) {
        case DATY_INVAL:
            if (cole_stasti_whole_bzl(resctl, baval->base_name))
                return -1;
            break;
        case DATY_OBID:
            if (cole_stasti_lv2po_bzl(resctl, baval, (osv_oid_t *) pamvu->pamcon[CPAM_STATI_LVTPO]))
                return -1;
            break;
        case DATY_STRI:
            if (cole_stasti_lv2pn_bzl(resctl, baval->base_name, pamvu->pamcon[CPAM_STATI_LVTPN]))
                return -1;
            break;
        default:
            _LOG_WARN("default: CPAM_POST_TYPE");
            PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
            return -1;
            break;
    }
    //
    return 0x00;
}

// odb-lv2p> txxt<[xx int32, ax int32, cx int32], tpp(cx, ax, xx)>;
// odb-lv2p> teet<[ex=8 int, ix int], [fx int] auto, txst(fx, ex), txp(ix)>;
// odb-lv2p> tbbt<[ex=8 int, ix int], [fx int] auto, txst(fx, ex), txp(ix)>;
// odb-lv2p> taat<[xx=8 int, ax int], [cx int] auto, tst(cx, xx), tpp(ax)>;
// odb-lv2p> tiit<teet:txst>;
// odb-lv2p> tttt<[tx int32, tx int32, tx int32], ttt(tx, tx, tx), txxt>; // fixme: 20241018

// odb-lv2p> user <[user_name char(32), password char(32), salt char(16), role_obid char(96)]>; // admin
// odb-lv2p> role <[role_type uint8, role_name char(32), priv_array char(1024)]>; // admin

#define CPAM_CREAT_CONTE   0x00

int colle_creat_hand(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:colle_creat_hand\n");
    OSEVPF("pamvu->pamcon[0x00]:|%s|\n", pamvu->pamcon[0x00]);
    OSEVPF("pamvu->pamcon[0x01]:|%s|\n", pamvu->pamcon[0x01]);
    OSEVPF("pamvu->pamcon[0x02]:|%s|\n", pamvu->pamcon[0x02]);
    // pamvu = 1
    if (!pamvu->pamcon[0x00] || pamvu->pamcon[0x01]) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    //
    lv2p_decl_t lv2dt;
    creat_class_obid(&lv2dt.lv2p_obid);
    if (build_lv2pd_conte(&lv2dt, pamvu->pamcon[CPAM_CREAT_CONTE], baval->base_name)) {
        PDAT_EXCEPTIO_TAIL(resctl, PARMS_PARM_EXPT)
        return -1;
    }
    if (valid_creac_ite(baval->base_name, &lv2dt)) {
        PDAT_EXCEPTIO_TAIL(resctl, REQUE_VALID_EXPT)
        return -1;
    }
    //
    if (creat_class_conte(resctl, &baval->lv2pm_stm, baval->base_name, &lv2dt, pamvu->pamcon[CPAM_CREAT_CONTE])) {
        OSEVPF("Creat class excep!\n");
        robk_creac_bzl(&baval->lv2pm_stm, baval->base_name, lv2dt.lv2pn);
        return -1;
    }
    if (creat_inher_integ(resctl, &baval->hando_stm, &baval->lv2pm_stm, baval->base_name, &lv2dt)) {
        OSEVPF("Creat inher excep!\n");
        robk_inhem_bzl(&baval->lv2pm_stm, &baval->hando_stm, baval->base_name, lv2dt.meth, lv2dt.lv2pn);
        robk_creac_bzl(&baval->lv2pm_stm, baval->base_name, lv2dt.lv2pn);
        return -1;
    }
    //
    PDAT_PRODUCEN_TAIL(resctl)
    return 0x00;
}

// replace the class data and method
// data must more, can del or add method, binding changed
// odb-lv2p> :replace("txxt<[xx int32, ax int32, cx int32], tpp(cx, ax, xx)>");
// odb-lv2p> :replace("txxt<[xx int32, ax int32, cx int32], tpp(cx, ax, xx)>", FORCED);

#define CPAM_REPLACE_CONTE   0x00
#define CPAM_FORECD_REPLA    0x01

int colle_repla_hand(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:colle_repla_hand\n");
    // pamvu = 1 = 2
    OSEVPF("pamvu->pamcon[0x00]:%p\n", pamvu->pamcon[0x00]);
    OSEVPF("pamvu->pamcon[0x01]:%p\n", pamvu->pamcon[0x01]);
    OSEVPF("pamvu->pamcon[0x02]:%p\n", pamvu->pamcon[0x02]);
    OSEVPF("pamvu->pamcon[0x03]:%p\n", pamvu->pamcon[0x03]);
    OSEVPF("pamvu->pamcon[0x04]:%p\n", pamvu->pamcon[0x04]);
    if (!pamvu->pamcon[0x00] || (pamvu->pamcon[0x01] && pamvu->pamcon[0x02])) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    //
    lv2p_decl_t nlv2dt;
    if (build_lv2pd_conte(&nlv2dt, pamvu->pamcon[CPAM_REPLACE_CONTE], baval->base_name)) {
        PDAT_EXCEPTIO_TAIL(resctl, PARMS_PARM_EXPT)
        return -1;
    }
    lv2p_decl_t elv2dt;
    if (build_lv2pd_clasn(&elv2dt, baval->base_name, nlv2dt.lv2pn)) {
        PDAT_EXCEPTIO_TAIL(resctl, INNER_DATA_EXPT)
        return -1;
    }
    replc_list *replst = NULL;
    if (build_replc_list_ite(&replst, &elv2dt, &nlv2dt)) {
        PDAT_EXCEPTIO_TAIL(resctl, INNER_DATA_EXPT)
        return -1;
    }
    if (valid_replc_ite(baval->base_name, replst, &nlv2dt, (uint32 *) pamvu->pamcon[CPAM_FORECD_REPLA])) {
        dele_replc_list(replst);
        PDAT_EXCEPTIO_TAIL(resctl, REQUE_VALID_EXPT)
        return -1;
    }
    //
    lv2p_expa_t *lv2expt = mallo_lv2exp(LVTNOD_COUNT, LEVO_COUNT);
    if (!lv2expt) {
        OSEVPF("Conve class excep!\n");
        PDAT_EXCEPTIO_TAIL(resctl, MALLO_LVTEXP_EXPT)
        return -1;
    }
    // char clang_cont[CLANG_CONTE_SIZE];
    // MK_ZERO(clang_cont);
    if (cole_repla_bzl(lv2expt, baval->base_name, &nlv2dt)) {
        dele_replc_list(replst);
        free_lv2exp(lv2expt);
        PDAT_EXCEPTIO_TAIL(resctl, REPLA_COLLE_EXPT)
        return -1;
    }
    REDUCE_LEVET_EXPANT(lv2expt);
    //
    replc_envir envrpc;
    if (prote_replc_bzl(&envrpc, &baval->lv2pm_stm, baval->base_name, &nlv2dt, replst)) {
        cancel_replc_bzl(&envrpc, baval->base_name, lv2expt);
        PDAT_EXCEPTIO_TAIL(resctl, REPLA_COLLE_EXPT)
        return -1;
    }
    if (repla_lv2me_bzl(&baval->lv2pm_stm, baval->base_name, &nlv2dt, lv2expt)) {
        robk_replc_bzl(&baval->lv2pm_stm, baval->base_name, lv2expt, &envrpc);
        PDAT_EXCEPTIO_TAIL(resctl, CREAT_LVTME_EXPT)
        return -1;
    }
    if (recod_replc_bzl(baval->base_name, &baval->lv2pm_stm, nlv2dt.lv2pn, pamvu->pamcon[CPAM_REPLACE_CONTE], lv2expt)) {
        robk_replc_bzl(&baval->lv2pm_stm, baval->base_name, lv2expt, &envrpc);
        PDAT_EXCEPTIO_TAIL(resctl, REPLA_COLLE_EXPT)
        return -1;
    }
    if (replc_inher_integ(&baval->lv2pm_stm, baval->base_name, replst)) {
        robk_replc_bzl(&baval->lv2pm_stm, baval->base_name, lv2expt, &envrpc);
        PDAT_EXCEPTIO_TAIL(resctl, REPLA_COLLE_EXPT)
        return -1;
    }
    destr_replc_bzl(&envrpc, baval->base_name);
    //
    PDAT_PRODUCEN_TAIL(resctl)
    return 0x00;
}

// odb-lv2p> odb:drop("lv2pn");
// odb-lv2p> odb:drop(teet);

#define CPAM_DROP_LVTPN   0x00

int colle_drop_hand(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:colle_drop_hand\n");
    // pamvu = 1
    if (!pamvu->pamcon[0x00] || pamvu->pamcon[0x01]) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    if (valid_dropc_ite(resctl, baval->base_name, pamvu->pamcon[CPAM_DROP_LVTPN], &baval->lv2pm_stm))
        return -1;
    if (hdrop_class_bzl(&baval->lv2pm_stm, pamvu->pamcon[CPAM_DROP_LVTPN])) {
        PDAT_EXCEPTIO_TAIL(resctl, DROP_COLLE_HAND)
        return -1;
    }
    if (inher_dropc_ite(&baval->lv2pm_stm, baval->base_name, pamvu->pamcon[CPAM_DROP_LVTPN])) {
        PDAT_EXCEPTIO_TAIL(resctl, DROP_COLLE_INHE)
        return -1;
    }
    if (cole_drop_conte_bzl(baval->base_name, pamvu->pamcon[CPAM_DROP_LVTPN])) {
        PDAT_EXCEPTIO_TAIL(resctl, DROP_COLLE_EXPT)
        return -1;
    }
    //
    PDAT_PRODUCEN_TAIL(resctl)

    return 0x00;
}

//
#define CPAM_RELOAD_LVTPN   0x00

int colle_reload_hand(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:colle_reload_hand\n");
    // pamvu < 2
    if (pamvu->pamcon[0x00] && pamvu->pamcon[0x01]) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    //
    if (pamvu->pamcon[CPAM_RELOAD_LVTPN]) {
        if (reloc_clasn(resctl, &baval->lv2pm_stm, baval->base_name, pamvu->pamcon[CPAM_RELOAD_LVTPN]))
            return -1;
    } else {
        if (reloc_whole(resctl, &baval->lv2pm_stm, baval->base_name))
            return -1;
    }
    //
    PDAT_PRODUCEN_TAIL(resctl)

    return 0x00;
}

// odb-lv2p> odb:integra(); odb:integra(lv2pn);

#define CPAM_INTEGRA_LVTPN   0x00

int colle_integra_hand(respo_ctrl *resctl, char *basen, pams_valu *pamvu) {
    OSEVPF("[FUNC]:colle_integra_hand\n");
    // pamvu < 2
    if (pamvu->pamcon[0x00] && pamvu->pamcon[0x01]) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    if (valid_intec_ite(basen, pamvu->pamcon[CPAM_INTEGRA_LVTPN])) {
        PDAT_EXCEPTIO_TAIL(resctl, LVTP_NOT_FOUND);
        return -1;
    }
    if (integ_class_ite(resctl, basen, pamvu->pamcon[CPAM_INTEGRA_LVTPN]))
        return -1;
    //
    return 0x00;
}


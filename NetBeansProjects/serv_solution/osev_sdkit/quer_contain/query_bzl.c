#include "commo_header.h"
#include "astri_utili.h"
#include "kcomm_header.h"

#include "rstatu_bzl.h"
#include "basev_bzl.h"
#include "query_obje.h"
#include "creaq.h"
#include "creaq_reen.h"
#include "dropq.h"
#include "dropq_reen.h"
#include "facto.h"
#include "searq.h"
#include "searq_reen.h"
#include "invokq.h"
#include "invokq_reen.h"
#include "updatq.h"
#include "updatq_reen.h"
#include "inserq.h"
#include "inserq_reen.h"
#include "rive_bzl.h"
#include "query_utili.h"
#include "qstri_utili.h"
#include "statq_respo.h"
#include "chk_privi_bzl.h"
#include "privile_bzl.h"
#include "instda_bzl.h"

#include "query_bzl.h"

//

/*
int querbzl_create(char *data_directory) {
    strcpy(_quer_data_directory_, data_directory);
    return ERR_SUCCESS; //succ
}
int querbzl_destroy() {
    return ERR_SUCCESS; //succ
}
 */

//

int quer_statu_whole_bzl(respo_ctrl *resctl, base_valu *baval, user_privi *uepriv) {
    OSEVPF("[FUNC]:quer_statu_whole_bzl\n");
    // all contain name, must check permissions
#ifndef NOAUTH
    if (lechq_privile_bzl(uepriv, &baval->base_obid, BLVF_READ)) {
        if (!fill_nechq_perm(resctl, uepriv, baval->conda_stm.clist) && baval->conda_stm.clist) {
            _LOG_WARN("NO PERMISSIONS!");
            return -1;
        }
    } else fill_nechq_mult(resctl, baval->conda_stm.clist);
#else
    fill_nechq_mult(resctl, baval->conda_stm.clist);
#endif // NOAUTH
    //
    return 0x00;
}

int quer_statu_objid_bzl(respo_ctrl *resctl, base_valu *baval, char *contn) {
    OSEVPF("[FUNC]:quer_statu_objid_bzl\n");
    contain *contp = (contain *) cache_value(contn, baval->conda_stm.lev3n_hm);
    // OSEVPF("not found:|%s|\n", pamvp[0x00]);
    if (!contp) return -1;
    fill_oechq_ensi(resctl, contp);
    //
    return 0x00;
}

int quer_statu_name_bzl(respo_ctrl *resctl, base_valu *baval, osv_oid_t *cont_obid) {
    OSEVPF("[FUNC]:quer_statu_name_bzl\n");
    contain *contp = (contain *) cache_value(cont_obid, baval->conda_stm.lev3o_hm);
    // OSEVPF("not found:|%s|\n", pamvp[0x00]);
    if (!contp) return -1;
    fill_nechq_ensi(resctl, contp);
    //
    return 0x00;
}

//

#define QPAM_ATTI_TYPE   0x00
#define QPAM_ATTI_NAME   0x00
#define QPAM_ATTI_OBID   0x00

int quer_statu_attri_bzl(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:quer_statu_attri_bzl\n");
    lv2pme *lv2me;
    contain *contp;
    //
    switch (pamvu->pamtyp[QPAM_ATTI_TYPE]) {
        case DATY_INVAL:
            _LOG_WARN("case: DATY_INVAL");
            return -1;
            break;
        case DATY_OBID:
            contp = (contain *) cache_value((osv_oid_t *) pamvu->pamcon[QPAM_ATTI_OBID], baval->conda_stm.lev3o_hm);
            if (!contp) return -1;
            lv2me = (lv2pme *) cache_value(&contp->lv2p_type, baval->lv2pm_stm.lv2pmo_hm);
            if (!lv2me) return -1;
            break;
        case DATY_STRI:
            contp = (contain *) cache_value(pamvu->pamcon[QPAM_ATTI_NAME], baval->conda_stm.lev3n_hm);
            if (!contp) return -1;
            lv2me = (lv2pme *) cache_value(&contp->lv2p_type, baval->lv2pm_stm.lv2pmo_hm);
            if (!lv2me) return -1;
            break;
        default:
            _LOG_WARN("default: QPAM_ATTI_TYPE");
            return -1;
            break;
    }
    fill_statq_atti(resctl, contp, lv2me, &baval->conda_stm);
    //
    return 0x00;
}

//

int quer_statu_ustai_bzl(respo_ctrl *resctl, base_valu *baval, uint32 ustai_type) {
    OSEVPF("[FUNC]:quer_statu_ustai_bzl\n");
    switch (ustai_type) {
        case QUARY_STATI_BASE: // base running status / running level / clear status base_obid, authen status
            if (quer_stasti_base_bzl(resctl, &((base_valu *) baval)->base_obid)) {
                PDAT_EXCEPTIO_TAIL(resctl, STATI_BASE_EXPT)
                return -1;
            }
            break;
        case QUARY_STATI_CONTAIN: // contain statis
            fill_cstiq_mult(resctl, baval->conda_stm.clist);
            break;
        default:
            _LOG_WARN("default: QPAM_USTAI_TYPE");
            break;
    }
    //
    return 0x00;
}

int quer_statu_ostai_bzl(respo_ctrl *resctl, base_valu *baval, osv_oid_t *cont_obid) {
    OSEVPF("[FUNC]:quer_statu_ostai_bzl\n");
    contain *contp = (contain *) cache_value(cont_obid, ((base_valu *) baval)->conda_stm.lev3o_hm);
    if (!contp) return -1;
#ifdef _DEBUG

    OSEVPF("Contain:|%s|\n", contp->cont_name);
#endif
    lv2pme *lv2me = (lv2pme *) cache_value(&contp->lv2p_type, baval->lv2pm_stm.lv2pmo_hm);
    if (!lv2me) return -1;
    fill_statq_stai(resctl, contp, lv2me, &baval->conda_stm);
    //
    return 0x00;
}

int quer_statu_nstai_bzl(respo_ctrl *resctl, base_valu *baval, char *contn) {
    OSEVPF("[FUNC]:quer_statu_nstai_bzl\n");
    contain *contp = (contain *) cache_value(contn, ((base_valu *) baval)->conda_stm.lev3n_hm);
    if (!contp) return -1;
#ifdef _DEBUG
    char obid_stri[OBJE_IDENTI_ZLEN];
    OSEVPF("Contain:|%s|\n", oidstr(obid_stri, &contp->cont_obid));
#endif
    lv2pme *lv2me = (lv2pme *) cache_value(&contp->lv2p_type, baval->lv2pm_stm.lv2pmo_hm);
    if (!lv2me) return -1;
    fill_statq_stai(resctl, contp, lv2me, &baval->conda_stm);
    //
    return 0x00;
}
//
// #define ENTIT_CONTA_NORMAL    0x00
// odb:create("mycon", "rive", "test");
// #define REFER_CONTA_STATIC   0x01
// odb:create("mycon", "rive", "test", 0x02);
// #define REFER_CONTA_DYNAMI   0x02
// odb:create("mycon", "rive", "test", "scon1, scon2", "xxx=0x00");

//
#define QPAM_CREA_CONTN     0x00
#define QPAM_CREA_ENGIN     0x01
#define QPAM_CREA_LVTYP     0x02
#define QPAM_CREA_CONTYP    0x03
#define QPAM_CREA_RCOUN     0x03
#define QPAM_CREA_RCONT     0x03
#define QPAM_CREA_CONDIT    0x04

int quer_creat_bzl(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:quer_creat_bzl\n");
    int quer_valu = -1;
    //
    switch (pamvu->pamtyp[QPAM_CREA_CONTYP]) {
        case DATY_INVAL: // ENTIT_CONTA_NORMAL
            quer_valu = creat_qcont_normal(baval, pamvu->pamcon);
            break;
        case DATY_UINT: // REFER_CONTA_STATIC
            quer_valu = creat_qcont_static_reen(baval, pamvu->pamcon);
            break;
        case DATY_STRI: // REFER_CONTA_DYNAMI
            quer_valu = creat_qcont_dynamic_reen(baval, pamvu->pamcon, pamvu->pamtyp[QPAM_CREA_CONDIT]);
            break;
        default:
            _LOG_WARN("default: QPAM_CREA_CONTYP");
            return -1;
            break;
    }
    //
    if (!quer_valu) {
        contain *contp = creat_qcont_meta(baval, pamvu->pamcon[QPAM_CREA_CONTN]);
        if (!contp) return -1;
        OSEVPF("Create contain OK! %s\n", pamvu->pamcon[QPAM_CREA_CONTN]);
        OBID_BINARY_COPY((osv_oid_t *) resctl->resp_memo, &contp->cont_obid);
        PDAT_PRODUCEM_TAIL(resctl, OBJE_IDENTI_BLEN)
    }
    //
    return quer_valu;
}

//char *contn
#define QPAM_DROP_CONTA     0x00

int quer_drop_bzl(base_valu *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:quer_drop_bzl\n");
    int quer_valu = -1;
    contain *contp;
    switch (pamvu->pamtyp[QPAM_DROP_CONTA]) {
        case DATY_INVAL:
            _LOG_WARN("case: DATY_INVAL");
            return -1;
            break;
        case DATY_OBID:
            if (!(contp = (contain *) cache_value(pamvu->pamcon[QPAM_DROP_CONTA], baval->conda_stm.lev3o_hm)))
                return -1;
            break;
        case DATY_STRI:
            if (!(contp = (contain *) cache_value(pamvu->pamcon[QPAM_DROP_CONTA], baval->conda_stm.lev3n_hm)))
                return -1;
            break;
        default:
            _LOG_WARN("default: QPAM_DROP_CONTA");
            return -1;
            break;
    }
    // drop contain
    stor_seio *sto_seio = ACTIV_SESSION_BZL(baval->rivcon, contp->stora_ha);
    if (!sto_seio) return -1;
    OSEVPF("drop contn:|%s|\n", contp->cont_name);
    quer_valu = drop_qcont_conta(sto_seio->seion, contp->stora_ha, baval->base_name, &contp->cont_obid, contp->cont_name);
    QUIET_SESSION_BZL(baval->rivcon, contp->stora_ha, sto_seio);
    // drop contain privile
    crevk_privi_bzl(&contp->cont_obid);
    conta_cache_remove(&baval->conda_stm, contp);
    //
    return quer_valu;
}

//
#define QPAM_SEARQ_DESTIN     0x00
#define QPAM_SEARQ_SOURCE     0x01
#define QPAM_SEARQ_CONDIT     0x02

int quer_searq_bzl(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:quer_searq_bzl, pamvu->pamcon[QPAM_SEARQ_DESTIN]:|%s|\n", pamvu->pamcon[QPAM_SEARQ_DESTIN]);
    int quer_valu = -1;
    contain *dcont;
    switch (pamvu->pamtyp[QPAM_SEARQ_DESTIN]) {
        case DATY_INVAL:
            _LOG_WARN("case: DATY_INVAL");
            return -1;
            break;
        case DATY_OBID:
            dcont = (contain *) cache_value(pamvu->pamcon[QPAM_SEARQ_DESTIN], baval->conda_stm.lev3o_hm);
            break;
        case DATY_STRI:
            dcont = (contain *) cache_value(pamvu->pamcon[QPAM_SEARQ_DESTIN], baval->conda_stm.lev3n_hm);
            break;
        default:
            _LOG_WARN("default: QPAM_SEARQ_DESTIN");
            return -1;
            break;
    }
    //
    OSEVPF("pamvu->pamcon[QPAM_SEARQ_SOURCE]:|%s|\n", pamvu->pamcon[QPAM_SEARQ_SOURCE]);
    contain * scont[SCONT_CONUT_ZTAI];
    unsigned int cont_type, scoun;
    switch (pamvu->pamtyp[QPAM_SEARQ_SOURCE]) {
        case DATY_INVAL:
            _LOG_WARN("case: DATY_INVAL");
            return -1;
            break;
        case DATY_OBID:
            scoun = parse_source_conto(scont, &cont_type, &baval->conda_stm, (osv_oid_t *) pamvu->pamcon[QPAM_SEARQ_SOURCE], pamvu->req_len[QPAM_SEARQ_SOURCE]);
            break;
        default:
        case DATY_STRI:
            scoun = parse_source_contn(scont, &cont_type, &baval->conda_stm, pamvu->pamcon[QPAM_SEARQ_SOURCE]);
            break;
            _LOG_WARN("default: QPAM_SEARQ_SOURCE");
            return -1;
            break;
    }
    OSEVPF("scoun:%u, cont_type:%u\n", scoun, cont_type);
    if (!scoun || (ENTIT_REFER_TYPE == cont_type))
        return -1;
    //
    if (dcont) {
        OSEVPF("find contain, contp->refe_coun:%d\n", dcont->refe_coun);
        if ((REFER_CONTA_STATIC == dcont->contype) && (ENTIT_CONTA_TYPE == cont_type)) {
            if (scoun != dcont->refe_coun)
                return -1;
            quer_valu = searq_qcont_conta(resctl, baval, pamvu, dcont, scoun, scont);
        }
        // if (!quer_valu) REFRESH_CONTAIN_VERSION(dcont);
    } else {
        if ((DATY_STRI != pamvu->pamtyp[QPAM_SEARQ_DESTIN]) || chk_lv2p_decl(pamvu->pamcon[QPAM_SEARQ_DESTIN])) {
            OSEVPF("find exists class\n");
            if (ENTIT_CONTA_TYPE == cont_type) {
                if (check_refer_obid(pamvu->pamtyp[QPAM_SEARQ_CONDIT], pamvu->pamcon[QPAM_SEARQ_CONDIT])) {
                    quer_valu = searq_qcont_lv2pn(resctl, baval, pamvu, scoun, scont);
                } else {
                    quer_valu = searq_qcont_lv2pn_ore(resctl, baval, pamvu, scoun, scont);
                }
            } else if (REFER_CONTA_TYPE == cont_type) {
                if (0x01 != scoun) return -1;
                quer_valu = searq_qcont_lv2pn_reen(resctl, baval, pamvu, scont[0x00]);
            }
        } else {
            OSEVPF("find new class\n");
            lv2pme *lv2dme = lv2me_interp_bzl(baval, pamvu->pamcon[QPAM_SEARQ_DESTIN]);
            if (!lv2dme) {
                OSEVPF("lv2me_interp_bzl error!\n");
                return -1;
            }
            if (ENTIT_CONTA_TYPE == cont_type)
                quer_valu = searq_qcont_decla(resctl, baval, pamvu, lv2dme, scoun, scont);
            else {
                if (0x01 != scoun) return -1;
                quer_valu = searq_qcont_decla_reen(resctl, baval, pamvu, lv2dme, scont[0x00]);
            }
        }
    }
    //
    return quer_valu;
}

//
#define QPAM_FACTO_DESTIN     0x00
#define QPAM_FACTO_SOURCE     0x01
#define QPAM_FACTO_CONDIT     0x02

int quer_facto_bzl(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:quer_facto_bzl, pamvu->pamcon[QPAM_FACTO_DESTIN]:|%s|\n", pamvu->pamcon[QPAM_FACTO_DESTIN]);
    int quer_valu = -1;
    contain *dcont;
    switch (pamvu->pamtyp[QPAM_FACTO_DESTIN]) {
        case DATY_INVAL:
            _LOG_WARN("case: DATY_INVAL");
            return -1;
            break;
        case DATY_OBID:
            dcont = (contain *) cache_value(pamvu->pamcon[QPAM_FACTO_DESTIN], baval->conda_stm.lev3o_hm);
            break;
        case DATY_STRI:
            dcont = (contain *) cache_value(pamvu->pamcon[QPAM_FACTO_DESTIN], baval->conda_stm.lev3n_hm);
            break;
        default:
            _LOG_WARN("default: QPAM_FACTO_DESTIN");
            return -1;
            break;
    }
    //
    contain * scont[SCONT_CONUT_ZTAI];
    unsigned int cont_type, scoun;
    switch (pamvu->pamtyp[QPAM_FACTO_SOURCE]) {
        case DATY_INVAL:
            _LOG_WARN("case: DATY_INVAL");
            return -1;
            break;
        case DATY_OBID:
            scoun = parse_source_conto(scont, &cont_type, &baval->conda_stm, (osv_oid_t *) pamvu->pamcon[QPAM_FACTO_SOURCE], pamvu->req_len[QPAM_FACTO_SOURCE]);
            break;
        case DATY_STRI:
            scoun = parse_source_contn(scont, &cont_type, &baval->conda_stm, pamvu->pamcon[QPAM_FACTO_SOURCE]);
            break;
        default:
            _LOG_WARN("default: QPAM_FACTO_SOURCE");
            return -1;
            break;
    }
    OSEVPF("scoun:%u, cont_type:%u\n", scoun, cont_type);
    if (!scoun || (ENTIT_CONTA_TYPE != cont_type))
        return -1;
    //
    if (dcont) {
        OSEVPF("find contain, contp->refe_coun:%d\n", dcont->refe_coun);
        if (ENTIT_CONTA_NORMAL == dcont->contype) // fixme: check user level 3 privile
            quer_valu = facto_qcont_conta(resctl, baval, pamvu, dcont, scoun, scont);
        if (!quer_valu) REFRESH_CONTAIN_VERSION(dcont);
    } else {
        if ((DATY_STRI != pamvu->pamtyp[QPAM_FACTO_DESTIN]) || chk_lv2p_decl(pamvu->pamcon[QPAM_FACTO_DESTIN])) {
            OSEVPF("find exists class\n");
            quer_valu = facto_qcont_lv2pn(resctl, baval, pamvu, scoun, scont);
        } else {
            OSEVPF("find new class\n");
            lv2pme *lv2dme = lv2me_interp_bzl(baval, pamvu->pamcon[QPAM_FACTO_DESTIN]);
            if (!lv2dme) {
                OSEVPF("lv2me_interp_bzl error!\n");

                return -1;
            }
            quer_valu = facto_qcont_decla(resctl, baval, pamvu, lv2dme, scoun, scont);
        }
    }
    //
    return quer_valu;
}

//
#define QPAM_INVK_METHOD     0x00
#define QPAM_INVK_SOURCE     0x01
#define QPAM_INVK_CONDIT     0x02

int quer_invok_bzl(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:quer_invok_bzl\n");
    // OSEVPF("pamtyp[QPAM_INVK_METHOD]:%d pamtyp[QPAM_INVK_SOURCE]:%d pamtyp[QPAM_INVK_CONDIT]:%d\n", pamvu->pamtyp[QPAM_INVK_METHOD], pamvu->pamtyp[QPAM_INVK_SOURCE], pamvu->pamtyp[QPAM_INVK_CONDIT]);
    // OSEVPF("pamcon[QPAM_INVK_METHOD]:%p pamcon[QPAM_INVK_SOURCE]:%p pamcon[QPAM_INVK_CONDIT]:%p\n", pamvu->pamcon[QPAM_INVK_METHOD], pamvu->pamcon[QPAM_INVK_SOURCE], pamvu->pamcon[QPAM_INVK_CONDIT]);
    contain *contp;
    switch (pamvu->pamtyp[QPAM_INVK_METHOD]) {
        case DATY_INVAL:
            _LOG_WARN("case: DATY_INVAL");
            return -1;
            break;
        case DATY_OBID:
            contp = (contain *) cache_value(pamvu->pamcon[QPAM_INVK_METHOD], baval->conda_stm.lev3o_hm);
            break;
        case DATY_STRI:
            contp = (contain *) cache_value(pamvu->pamcon[QPAM_INVK_METHOD], baval->conda_stm.lev3n_hm);
            break;
        default:
            _LOG_WARN("default: QPAM_INVK_METHOD");
            return -1;
            break;
    }
    if (!contp) return -1;
    lv2pme * lv2me = (lv2pme *) cache_value(&contp->lv2p_type, baval->lv2pm_stm.lv2pmo_hm);
    if (!lv2me) return -1;
    // invoke contp object
    int quer_valu = -1;
    switch (pamvu->pamtyp[QPAM_INVK_CONDIT]) {
        case DATY_INVAL:
            quer_valu = invok_qcont_trave(resctl, contp, lv2me, &baval->hando_stm, baval->rivcon, pamvu->pamcon);
            break;
        case DATY_OBID:
            quer_valu = invok_qcont_objid(resctl, contp, lv2me, &baval->hando_stm, baval->rivcon, pamvu->pamcon);
            break;
        case DATY_STRI:
            quer_valu = invok_qcont_predi(resctl, contp, lv2me, &baval->hando_stm, baval->rivcon, pamvu->pamcon);
            break;
        default:
            _LOG_WARN("default: QPAM_INVK_CONDIT");
            quer_valu = -1;
            break;
    }
    //
    if (!quer_valu) REFRESH_CONTAIN_VERSION(contp);
    return quer_valu;
}

// todo:20230912
#define QPAM_UPDAT_CONTA     0x00
#define QPAM_UPDAT_VALUE     0x01

int quer_updat_bzl(base_valu *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:quer_updat_bzl, pamvu->pamcon[QPAM_UPDAT_CONTA]:|%s|\n", pamvu->pamcon[QPAM_UPDAT_CONTA]);
    int quer_valu = -1;
    contain *dcont;
    switch (pamvu->pamtyp[QPAM_UPDAT_CONTA]) {
        case DATY_INVAL:
            _LOG_WARN("case: DATY_INVAL");
            return -1;
            break;
        case DATY_OBID:
            dcont = (contain *) cache_value(pamvu->pamcon[QPAM_UPDAT_CONTA], baval->conda_stm.lev3o_hm);
            break;
        case DATY_STRI:
            dcont = (contain *) cache_value(pamvu->pamcon[QPAM_UPDAT_CONTA], baval->conda_stm.lev3n_hm);
            break;
        default:
            _LOG_WARN("default: QPAM_UPDAT_CONTA");
            return -1;
            break;
    }
    if (!dcont) return -1;
    //
    OSEVPF("find contain, contp->refe_coun:%d\n", dcont->refe_coun);
    if (dcont->contype) {
        if (DATY_BINARY != pamvu->pamtyp[QPAM_UPDAT_VALUE])
            return -1;
        quer_valu = UPDAT_QCONT_CONTA_REEN(baval, dcont, pamvu);
    } else {
        if (DATY_BINARY != pamvu->pamtyp[QPAM_UPDAT_VALUE])
            return -1;
        quer_valu = updat_qcont_conta(baval, dcont, pamvu);
    }
    //
    if (!quer_valu) REFRESH_CONTAIN_VERSION(dcont);
    return quer_valu;
}

// todo:20230912
#define QPAM_INSER_CONTA     0x00
#define QPAM_INSER_VALUE     0x01

int quer_inser_bzl(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:quer_inser_bzl, pamvu->pamcon[QPAM_INSER_CONTA]:|%s|\n", pamvu->pamcon[QPAM_INSER_CONTA]);
    int quer_valu = -1;
    contain *dcont;
    switch (pamvu->pamtyp[QPAM_INSER_CONTA]) {
        case DATY_INVAL:
            _LOG_WARN("case: DATY_INVAL");
            return -1;
            break;
        case DATY_OBID:
            dcont = (contain *) cache_value(pamvu->pamcon[QPAM_INSER_CONTA], baval->conda_stm.lev3o_hm);
            break;
        case DATY_STRI:
            dcont = (contain *) cache_value(pamvu->pamcon[QPAM_INSER_CONTA], baval->conda_stm.lev3n_hm);
            break;
        default:
            _LOG_WARN("default: QPAM_INSER_CONTA");
            return -1;
            break;
    }
    if (!dcont) return -1;
    //
    OSEVPF("find contain, contp->refe_coun:%d\n", dcont->refe_coun);
    if (dcont->contype) {
        if (DATY_BINARY != pamvu->pamtyp[QPAM_INSER_VALUE])
            return -1;
        quer_valu = INSER_QCONT_CONTA_REEN(resctl, baval, dcont, pamvu);
    } else {
        if (DATY_BINARY != pamvu->pamtyp[QPAM_INSER_VALUE])
            return -1;
        quer_valu = inser_qcont_conta(resctl, baval, dcont, pamvu);
    }
    //
    if (!quer_valu) REFRESH_CONTAIN_VERSION(dcont);
    return quer_valu;
}



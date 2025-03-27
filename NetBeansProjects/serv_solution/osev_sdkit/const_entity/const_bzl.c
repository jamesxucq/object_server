#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_header.h"
#include "basev_bzl.h"
#include "const_obje.h"
#include "creao.h"
#include "creao_reen.h"
#include "dropo.h"
#include "dropo_reen.h"
#include "invoko.h"
#include "invoko_reen.h"
#include "searo.h"
#include "searo_reen.h"
#include "insero.h"
#include "insero_reen.h"
#include "updato.h"
#include "updato_reen.h"
#include "stato_respo.h"

#include "rive_bzl.h"
#include "const_bzl.h"
#include "seion_struct.h"

/*
int invobzl_create(char *data_directory) {
    strcpy(_invo_data_directory_, data_directory);
    return ERR_SUCCESS; //succ
}
int invobzl_destroy() {
    return ERR_SUCCESS; //succ
}
 */

int enti_statu_echo_bzl(respo_ctrl *resctl, contain *contp) {
    OSEVPF("[FUNC]:enti_statu_echo_bzl\n");
    // if (contp->contype) return -1;
    fill_state_echo(resctl, contp);
    return 0x00;
}

int enti_statu_attri_bzl(respo_ctrl *resctl, contain *contp, base_valu *baval) {
    OSEVPF("[FUNC]:enti_statu_attri_bzl\n");
    // if (contp->contype) return -1;
    lv2pme *lv2me = (lv2pme *) cache_value(&contp->lv2p_type, baval->lv2pm_stm.lv2pmo_hm);
    if (!lv2me) return -1;
    //
    fill_state_atti(resctl, contp, lv2me, &baval->conda_stm);
    return 0x00;
}

int enti_statu_stati_bzl(respo_ctrl *resctl, contain *contp, base_valu *baval) {
    OSEVPF("[FUNC]:enti_statu_attri_bzl\n");
    // if (contp->contype) return -1;
    lv2pme *lv2me = (lv2pme *) cache_value(&contp->lv2p_type, baval->lv2pm_stm.lv2pmo_hm);
    if (!lv2me) return -1;
    //
    fill_state_stai(resctl, contp, lv2me, &baval->conda_stm);
    return 0x00;
}

int enti_creat_bzl(respo_ctrl *resctl, contain *contp, base_valu *baval, char **pamvp) {
    OSEVPF("[FUNC]:enti_creat_bzl\n");
    // create a user object
    lv2pme *lv2me = (lv2pme *) cache_value(&contp->lv2p_type, baval->lv2pm_stm.lv2pmo_hm);
    if (!lv2me) return -1;
    //
    rive_ha *stora_ha = contp->stora_ha;
    riv_curso_t *dcurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(baval->rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&dcurso, sto_seio->seion, contp->cont_name, "raw")) {
        QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    int creat_valu = -1;
    if (contp->contype) { // fixme: by james, 20221110
        OSEVPF("CREAT_CONST_ENTIT_RE contp->cont_name:|%s|\n", contp->cont_name);
        // wt_begin_transa_sess(sto_seio->seion);
        CREAT_CONST_ENTIT_REEN(creat_valu, resctl, dcurso, stora_ha, lv2me, &baval->hando_stm, contp->base_name, pamvp);
        // wt_commit_transa_sess(sto_seio->seion);
    } else {
        OSEVPF("CREAT_CONST_ENTIT contp->cont_name:|%s|\n", contp->cont_name);
        // wt_begin_transa_sess(sto_seio->seion);
        CREAT_CONST_ENTIT(creat_valu, resctl, dcurso, stora_ha, lv2me, &baval->hando_stm, contp->base_name, pamvp);
        // wt_commit_transa_sess(sto_seio->seion);
    }
    //
    stora_ha->close_curso(dcurso);
    QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
    return creat_valu;
}

//
#define EPAM_DROP_CONDIT     0x00

int enti_drop_bzl(contain *contp, base_valu *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:enti_drop_bzl\n");
    if (contp->contype) { // fixme: by james, 20221110
        switch (pamvu->pamtyp[EPAM_DROP_CONDIT]) {
            case DATY_INVAL:
                if (DROP_CONST_TRAVE_REEN(contp, baval))
                    return -1;
                break;
            case DATY_OBID:
                if (DROP_CONST_OBJID_REEN(baval->rivcon, contp, (osv_oid_i *) pamvu->pamcon[EPAM_DROP_CONDIT]))
                    return -1;
                break;
            case DATY_STRI:
                if (DROP_CONST_PREDI_REEN(contp, baval, pamvu->pamcon[EPAM_DROP_CONDIT]))
                    return -1;
                break;
            default:
                _LOG_WARN("default: EPAM_DROP_CONDIT");
                return -1;
                break;
        }
    } else { // drop user object
        switch (pamvu->pamtyp[EPAM_DROP_CONDIT]) {
            case DATY_INVAL:
                if (drop_const_trave(contp, baval))
                    return -1;
                break;
            case DATY_OBID:
                if (DROP_CONST_OBJID(baval->rivcon, contp, (osv_oid_i *) pamvu->pamcon[EPAM_DROP_CONDIT]))
                    return -1;
                break;
            case DATY_STRI:
                if (drop_const_predi(contp, baval, pamvu->pamcon[EPAM_DROP_CONDIT]))
                    return -1;
                break;
            default:
                _LOG_WARN("default: EPAM_DROP_CONDIT");
                return -1;
                break;
        }
    }
    //
    return 0x00;
}

int enti_updat_bzl(contain *contp, base_valu *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:enti_updat_bzl\n");
    // updat user object
    lv2pme *lv2me = (lv2pme *) cache_value(&contp->lv2p_type, baval->lv2pm_stm.lv2pmo_hm);
    if (!lv2me) return -1;
    //
    rive_ha *stora_ha = contp->stora_ha;
    riv_curso_t *dcurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(baval->rivcon, stora_ha);
    if (!sto_seio) return -1;
    OSEVPF("contp->cont_name:|%s|\n", contp->cont_name);
    if (stora_ha->open_curso_cont(&dcurso, sto_seio->seion, contp->cont_name, "raw")) {
        QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
        return -1;
    }
    int updat_valu = -1;
    if (contp->contype) { // fixme: by james, 20221110
        updat_valu = UPDAT_CONST_ENTIT_REEN(dcurso, stora_ha, lv2me, pamvu);
    } else {
        updat_valu = updat_const_entit(dcurso, stora_ha, lv2me, pamvu);
    }
    //
    stora_ha->close_curso(dcurso);
    QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
    return updat_valu;
}

int enti_inser_bzl(respo_ctrl *resctl, contain *contp, base_valu *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:enti_inser_bzl\n");
    // inser user object
    lv2pme *lv2me = (lv2pme *) cache_value(&contp->lv2p_type, baval->lv2pm_stm.lv2pmo_hm);
    if (!lv2me) return -1;
    //
    rive_ha *stora_ha = contp->stora_ha;
    riv_curso_t *dcurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(baval->rivcon, stora_ha);
    if (!sto_seio) return -1;
    OSEVPF("contp->cont_name:|%s|\n", contp->cont_name);
    if (stora_ha->open_curso_cont(&dcurso, sto_seio->seion, contp->cont_name, RIV_NOVWT_CONF)) {
        QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
        return -1;
    }
    int inser_valu = -1;
    if (contp->contype) { // fixme: by james, 20221110
        inser_valu = INSER_CONST_ENTIT_REEN(resctl, dcurso, stora_ha, lv2me, pamvu);
    } else {
        inser_valu = inser_const_entit(resctl, dcurso, stora_ha, lv2me, pamvu);
    }
    //
    stora_ha->close_curso(dcurso);
    QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
    return inser_valu;
}

//
#define EPAM_SEARO_CONDIT     0x00

int enti_searo_bzl(respo_ctrl *resctl, contain *contp, base_valu *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:enti_searo_bzl\n");
    lv2pme *lv2me = (lv2pme *) cache_value(&contp->lv2p_type, baval->lv2pm_stm.lv2pmo_hm);
    if (!lv2me) return -1;
    //
    int searo_valu = -1;
    if (contp->contype) {
        switch (pamvu->pamtyp[EPAM_SEARO_CONDIT]) {
            case DATY_INVAL:
                searo_valu = searo_const_trave_reen(resctl, contp, baval);
                break;
            case DATY_OBID:
                searo_valu = searo_const_objid_reen(resctl, contp, baval, (osv_oid_i *) pamvu->pamcon[EPAM_SEARO_CONDIT]);
                break;
            case DATY_STRI:
                searo_valu = searo_const_predi_reen(resctl, contp, baval, pamvu->pamcon[EPAM_SEARO_CONDIT]);
                break;
            default:
                _LOG_WARN("default: EPAM_SEARO_CONDIT");
                searo_valu = -1;
                break;
        }
    } else { // just single param
        switch (pamvu->pamtyp[EPAM_SEARO_CONDIT]) {
            case DATY_INVAL:
                searo_valu = searo_const_trave_ensi(resctl, contp, baval);
                break;
            case DATY_OBID:
                searo_valu = searo_const_objid_ensi(resctl, contp, baval, (osv_oid_i *) pamvu->pamcon[EPAM_SEARO_CONDIT]);
                break;
            case DATY_STRI:
                searo_valu = searo_const_predi_ensi(resctl, contp, baval, pamvu->pamcon[EPAM_SEARO_CONDIT]);
                break;
            default:
                _LOG_WARN("default: EPAM_SEARO_CONDIT");
                searo_valu = -1;
                break;
        }
    }
    //
    return searo_valu;
}

//
#define EPAM_INVK_METHOD     0x00
#define EPAM_INVK_CONDIT     0x01

int enti_invok_bzl(respo_ctrl *resctl, contain *contp, base_valu *baval, pams_valu *pamvu) {
    OSEVPF("[FUNC]:enti_invok_bzl\n");
    lv2pme *lv2me = (lv2pme *) cache_value(&contp->lv2p_type, baval->lv2pm_stm.lv2pmo_hm);
    if (!lv2me) return -1;
    OSEVPF("pamvu->pamtyp[EPAM_INVK_CONDIT]:%d\n", pamvu->pamtyp[EPAM_INVK_CONDIT]);
    int invok_valu = -1;
    if (contp->contype) { // fixme: by james, 20221110
        switch (pamvu->pamtyp[EPAM_INVK_CONDIT]) {
            case DATY_INVAL:
                invok_valu = INVOK_CONST_TRAVE_REEN(resctl, contp, baval, lv2me, pamvu->pamcon);
                break;
            case DATY_OBID:
                invok_valu = INVOK_CONST_OBJID_REEN(resctl, contp, baval, lv2me, pamvu->pamcon);
                break;
            case DATY_STRI:
                invok_valu = INVOK_CONST_PREDI_REEN(resctl, contp, baval, lv2me, pamvu->pamcon);
                break;
            default:
                _LOG_WARN("default: EPAM_INVK_CONDIT");
                invok_valu = -1;
                break;
        }
    } else { // invoke user object
        switch (pamvu->pamtyp[EPAM_INVK_CONDIT]) {
            case DATY_INVAL:
                invok_valu = invok_const_trave(resctl, contp, baval, lv2me, pamvu->pamcon);
                break;
            case DATY_OBID:
                invok_valu = invok_const_objid(resctl, contp, baval, lv2me, pamvu->pamcon);
                break;
            case DATY_STRI:
                invok_valu = invok_const_predi(resctl, contp, baval, lv2me, pamvu->pamcon);
                break;
            default:
                _LOG_WARN("default: EPAM_INVK_CONDIT");
                invok_valu = -1;
                break;
        }
    }
    //
    return invok_valu;
}
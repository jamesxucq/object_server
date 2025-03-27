
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_header.h"

#include "basev_bzl.h"
#include "cqutili.h"
#include "astri_utili.h"
#include "query_utili.h"
#include "searq_utili/searq_utili.h"

#include "searq.h"

// searc to object
#define QPAM_SEARQ_DESTIN     0x00
#define QPAM_SEARQ_SOURCE     0x01
#define QPAM_SEARQ_CONDIT     0x02

int searq_qcont_conta(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu, contain *dcont, int scoun, contain **sconp) {
    OSEVPF("[FUNC]:searq_qcont_conta\n");
    lv2pme *lv2me = (lv2pme *) cache_value(&dcont->lv2p_type, baval->lv2pm_stm.lv2pmo_hm);
    if (!lv2me) {
        OSEVPF("fdd lv2me:%p lv2pm:%p\n", lv2me, &baval->lv2pm_stm);
        return -1;
    }
    stati_scont scont[MAX_SCONT_COUNT];
    if (build_stati_scont(scont, sconp))
        return -1;
    if (fill_check_rcont(dcont, scont))
        return -1;
    //
    int searq_valu = -1;
    if (0x01 == scoun) {
        switch (pamvu->pamtyp[QPAM_SEARQ_CONDIT]) {
            case DATY_INVAL:
                TRAVE_QCONT_ENSI(searq_valu, resctl, baval->rivcon, dcont, scont, lv2me);
                break;
            case DATY_OBID:
                OBJID_QCONT_ENSI(searq_valu, resctl, baval->rivcon, dcont, scont, lv2me, (osv_oid_i *) pamvu->pamcon[QPAM_SEARQ_CONDIT]);
                break;
            case DATY_STRI:
            {
                switch (check_condi_type(pamvu->pamcon[QPAM_SEARQ_CONDIT])) {
                    case PREDI_TYPE_CONDI:
                        CONDI_QCONT_ENSI(searq_valu, resctl, dcont, scont, baval, lv2me, pamvu->pamcon[QPAM_SEARQ_CONDIT]);
                        break;
                    case PREDI_TYPE_TRAVE:
                        TRAVE_QCONT_ENSI(searq_valu, resctl, baval->rivcon, dcont, scont, lv2me);
                        break;
                    case PREDI_TYPE_EXCEP:
                    default:
                        break;
                }
            }
                break;
            default:
                searq_valu = -1;
                break;
        }
    } else if (0x02 == scoun) {
        switch (pamvu->pamtyp[QPAM_SEARQ_CONDIT]) {
            case DATY_INVAL:
                searq_valu = trave_qcont_enco(resctl, baval->rivcon, dcont, scont);
                break;
            case DATY_OBID:
                searq_valu = objid_qcont_enco(resctl, baval->rivcon, dcont, scont, (osv_oid_i *) pamvu->pamcon[QPAM_SEARQ_CONDIT]);
                break;
            case DATY_STRI:
            { // -1:error 0x00:objeid 0x01:predi
                switch (check_condi_type(pamvu->pamcon[QPAM_SEARQ_CONDIT])) {
                    case PREDI_TYPE_CONDI:
                        searq_valu = condi_qcont_enco(resctl, dcont, scont, baval, lv2me, pamvu->pamcon[QPAM_SEARQ_CONDIT]);
                        break;
                    case PREDI_TYPE_TRAVE:
                        searq_valu = trave_qcont_enco(resctl, baval->rivcon, dcont, scont);
                        break;
                    case PREDI_TYPE_EXCEP:
                    default:
                        break;
                }
            }
                break;
            default:
                searq_valu = -1;
                break;
        }
    }
    //
    if (searq_valu) robk_fichk_rcont(dcont, scont);
    return searq_valu;
}

// searc to class

int searq_qcont_lv2pn(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu, int scoun, contain **sconp) {
    OSEVPF("searq_qcont_lv2pn\n");
    OSEVPF("parms[QPAM_SEARQ_DESTIN]:|%s| parms[QPAM_SEARQ_SOURCE]:|%s| parms[QPAM_SEARQ_CONDIT]:|%s|\n", pamvu->pamcon[QPAM_SEARQ_DESTIN], pamvu->pamcon[QPAM_SEARQ_SOURCE], pamvu->pamcon[QPAM_SEARQ_CONDIT]);
    lv2pme *lv2me = NULL;
    if (DATY_STRI == pamvu->pamtyp[QPAM_SEARQ_DESTIN]) {
        lv2me = (lv2pme *) cache_value(pamvu->pamcon[QPAM_SEARQ_DESTIN], baval->lv2pm_stm.lv2pmn_hm);
    } else if (DATY_OBID == pamvu->pamtyp[QPAM_SEARQ_DESTIN]) {
        lv2me = (lv2pme *) cache_value(pamvu->pamcon[QPAM_SEARQ_DESTIN], baval->lv2pm_stm.lv2pmo_hm);
    }
    if (!lv2me) {
        OSEVPF("fdd lv2me:%p lv2pm:%p\n", lv2me, &baval->lv2pm_stm);
        return -1;
    }
    //
    int searq_valu = -1;
    if (0x01 == scoun) {
        switch (pamvu->pamtyp[QPAM_SEARQ_CONDIT]) {
            case DATY_INVAL:
                TRAVE_QLTPN_ENSI(searq_valu, resctl, baval->rivcon, sconp[0x00], lv2me);
                break;
            case DATY_OBID:
                OBJID_QLTPN_ENSI(searq_valu, resctl, baval->rivcon, sconp[0x00], lv2me, (osv_oid_i *) pamvu->pamcon[QPAM_SEARQ_CONDIT]);
                break;
            case DATY_STRI:
            {
                switch (check_condi_type(pamvu->pamcon[QPAM_SEARQ_CONDIT])) {
                    case PREDI_TYPE_CONDI:
                        CONDI_QLTPN_ENSI(searq_valu, resctl, sconp[0x00], baval, lv2me, pamvu->pamcon[QPAM_SEARQ_CONDIT]);
                        break;
                    case PREDI_TYPE_TRAVE:
                        TRAVE_QLTPN_ENSI(searq_valu, resctl, baval->rivcon, sconp[0x00], lv2me);
                        break;
                    case PREDI_TYPE_EXCEP:
                    default:
                        break;
                }
            }
                break;
            default:
                searq_valu = -1;
                break;
        }
    } else if (0x02 == scoun) {
        switch (pamvu->pamtyp[QPAM_SEARQ_CONDIT]) {
            case DATY_INVAL:
                searq_valu = trave_qlv2n_enco(resctl, baval->rivcon, sconp, lv2me);
                break;
            case DATY_OBID:
                searq_valu = objid_qlv2n_enco(resctl, baval->rivcon, sconp, lv2me, (osv_oid_i *) pamvu->pamcon[QPAM_SEARQ_CONDIT]);
                break;
            case DATY_STRI:
            {
                switch (check_condi_type(pamvu->pamcon[QPAM_SEARQ_CONDIT])) {
                    case PREDI_TYPE_CONDI:
                        searq_valu = condi_qlv2n_enco(resctl, sconp, baval, lv2me, pamvu->pamcon[QPAM_SEARQ_CONDIT]);
                        break;
                    case PREDI_TYPE_TRAVE:
                        searq_valu = trave_qlv2n_enco(resctl, baval->rivcon, sconp, lv2me);
                        break;
                    case PREDI_TYPE_EXCEP:
                    default:
                        break;
                }
            }
                break;
            default:
                searq_valu = -1;
                break;
        }
    }
    //
    return searq_valu;
}

int searq_qcont_decla(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu, lv2pme *lv2dme, int scoun, contain **sconp) {
    OSEVPF("searq_qcont_decla\n");
    OSEVPF("parms[QPAM_SEARQ_DESTIN]:|%s| parms[QPAM_SEARQ_SOURCE]:|%s| parms[QPAM_SEARQ_CONDIT]:|%s|\n", pamvu->pamcon[QPAM_SEARQ_DESTIN], pamvu->pamcon[QPAM_SEARQ_SOURCE], pamvu->pamcon[QPAM_SEARQ_CONDIT]);
    int searq_valu = -1;
    if (0x01 == scoun) {
        switch (pamvu->pamtyp[QPAM_SEARQ_CONDIT]) {
            case DATY_INVAL:
                searq_valu = trave_qdecl_ensi(resctl, baval->rivcon, sconp[0x00], lv2dme);
                break;
            case DATY_OBID:
                searq_valu = objid_qdecl_ensi(resctl, baval->rivcon, sconp[0x00], lv2dme, (osv_oid_i *) pamvu->pamcon[QPAM_SEARQ_CONDIT]);
                break;
            case DATY_STRI:
            {
                switch (check_condi_type(pamvu->pamcon[QPAM_SEARQ_CONDIT])) {
                    case PREDI_TYPE_CONDI:
                        searq_valu = condi_qdecl_ensi(resctl, sconp[0x00], baval, lv2dme, pamvu->pamcon[QPAM_SEARQ_CONDIT]);
                        break;
                    case PREDI_TYPE_TRAVE:
                        searq_valu = trave_qdecl_ensi(resctl, baval->rivcon, sconp[0x00], lv2dme);
                        break;
                    case PREDI_TYPE_EXCEP:
                    default:
                        break;
                }
            }
                break;
            default:
                searq_valu = -1;
                break;
        }
    } else if (0x02 == scoun) {
        switch (pamvu->pamtyp[QPAM_SEARQ_CONDIT]) {
            case DATY_INVAL:
                searq_valu = trave_qdecl_enco(resctl, baval->rivcon, sconp, lv2dme);
                break;
            case DATY_OBID:
                searq_valu = objid_qdecl_enco(resctl, baval->rivcon, sconp, lv2dme, (osv_oid_i *) pamvu->pamcon[QPAM_SEARQ_CONDIT]);
                break;
            case DATY_STRI:
            {
                switch (check_condi_type(pamvu->pamcon[QPAM_SEARQ_CONDIT])) {
                    case PREDI_TYPE_CONDI:
                        searq_valu = condi_qdecl_enco(resctl, sconp, baval, lv2dme, pamvu->pamcon[QPAM_SEARQ_CONDIT]);
                        break;
                    case PREDI_TYPE_TRAVE:
                        searq_valu = trave_qdecl_enco(resctl, baval->rivcon, sconp, lv2dme);
                        break;
                    case PREDI_TYPE_EXCEP:
                    default:
                        break;
                }
            }
                break;
            default:
                searq_valu = -1;
                break;
        }
    }
    //
    return searq_valu;
}

//

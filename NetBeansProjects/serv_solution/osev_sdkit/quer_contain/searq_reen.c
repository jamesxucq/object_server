
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_header.h"

#include "basev_bzl.h"
#include "astri_utili.h"
#include "query_utili.h"
#include "cqutili.h"
#include "searq_utili/searq_utili.h"

#include "searq_reen.h"

//
#define QPAM_SEARQ_DESTIN     0x00
#define QPAM_SEARQ_SOURCE     0x01
#define QPAM_SEARQ_CONDIT     0x02

int searq_qcont_lv2pn_ore(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu, int scoun, contain **rconp) {
    OSEVPF("parms[QPAM_SEARQ_DESTIN]:|%s| parms[QPAM_SEARQ_SOURCE]:|%s| parms[QPAM_SEARQ_CONDIT]:|%s|\n", pamvu->pamcon[QPAM_SEARQ_DESTIN], pamvu->pamcon[QPAM_SEARQ_SOURCE], pamvu->pamcon[QPAM_SEARQ_CONDIT]);
    lv2pme * lv2me[DCONT_SCONT_COUNT];
    if (DATY_STRI == pamvu->pamtyp[QPAM_SEARQ_DESTIN]) {
        if (find_lv2pn_meta(lv2me, &baval->lv2pm_stm, pamvu->pamcon[QPAM_SEARQ_DESTIN], rconp)) {
            OSEVPF("fdd lv2me:%p lv2pm:%p\n", lv2me, &baval->lv2pm_stm);
            return -1;
        }
    } else if (DATY_OBID == pamvu->pamtyp[QPAM_SEARQ_DESTIN]) {
        if (find_lv2po_meta(lv2me, &baval->lv2pm_stm, (osv_oid_t *) pamvu->pamcon[QPAM_SEARQ_DESTIN], rconp)) {
            OSEVPF("fdd lv2me:%p lv2pm:%p\n", lv2me, &baval->lv2pm_stm);
            return -1;
        }
    }
    //
    int searq_valu = -1;
    if (0x01 == scoun) {
        if (pamvu->pamcon[0x03]) { // -1:error 0x00:objeid 0x01:predi
            searq_valu = objid_qlv2n_oresi(resctl, baval->rivcon, rconp[0x00], lv2me, (osv_oid_i *) pamvu->pamcon[QPAM_SEARQ_CONDIT]);
        }
    } else if (0x02 == scoun) {
        if (pamvu->pamcon[0x03] && pamvu->pamcon[0x04]) { // -1:error 0x00:objeid 0x01:predi
            searq_valu = objid_qlv2n_oreco(resctl, baval->rivcon, rconp, lv2me, (osv_oid_i *) pamvu->pamcon[QPAM_SEARQ_CONDIT]);
        }
    }
    //
    return searq_valu;
}

// searc to class

int searq_qcont_lv2pn_reen(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu, contain *scont) {
    OSEVPF("parms[QPAM_SEARQ_DESTIN]:|%s| parms[QPAM_SEARQ_SOURCE]:|%s| parms[QPAM_SEARQ_CONDIT]:|%s|\n", pamvu->pamcon[QPAM_SEARQ_DESTIN], pamvu->pamcon[QPAM_SEARQ_SOURCE], pamvu->pamcon[QPAM_SEARQ_CONDIT]);
    contain * rcont[SCONT_CONUT_ZTAI];
    if (parse_refere_conta(rcont, &baval->conda_stm, scont->refe_cove, scont->refe_coun)) {
        OSEVPF("Parse refere conta ERROR!\n");
        return -1;
    }
    lv2pme * lv2me[DCONT_SCONT_COUNT];
    if (DATY_STRI == pamvu->pamtyp[QPAM_SEARQ_DESTIN]) {
        if (find_lv2pn_meta(lv2me, &baval->lv2pm_stm, pamvu->pamcon[QPAM_SEARQ_DESTIN], rcont)) {
            OSEVPF("fdd lv2me:%p lv2pm:%p\n", lv2me, &baval->lv2pm_stm);
            return -1;
        }
    } else if (DATY_OBID == pamvu->pamtyp[QPAM_SEARQ_DESTIN]) {
        if (find_lv2po_meta(lv2me, &baval->lv2pm_stm, (osv_oid_t *) pamvu->pamcon[QPAM_SEARQ_DESTIN], rcont)) {
            OSEVPF("fdd lv2me:%p lv2pm:%p\n", lv2me, &baval->lv2pm_stm);
            return -1;
        }
    }
    //
    int searq_valu = -1;
    if (0x01 == scont->refe_coun) {
        switch (pamvu->pamtyp[QPAM_SEARQ_CONDIT]) {
            case DATY_INVAL:
                searq_valu = trave_qlv2n_resi(resctl, baval->rivcon, scont, rcont[0x00], lv2me);
                break;
            case DATY_OBID:
                searq_valu = objid_qlv2n_resi(resctl, baval->rivcon, scont, rcont[0x00], lv2me, (osv_oid_i *) pamvu->pamcon[QPAM_SEARQ_CONDIT]);
                break;
            case DATY_STRI:
            {
                switch (check_condi_type(pamvu->pamcon[QPAM_SEARQ_CONDIT])) {
                    case PREDI_TYPE_CONDI:
                        searq_valu = condi_qlv2n_resi(resctl, scont, rcont[0x00], baval, lv2me, pamvu->pamcon[QPAM_SEARQ_CONDIT]);
                        break;
                    case PREDI_TYPE_TRAVE:
                        searq_valu = trave_qlv2n_resi(resctl, baval->rivcon, scont, rcont[0x00], lv2me);
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
    } else if (0x02 == scont->refe_coun) {
        switch (pamvu->pamtyp[QPAM_SEARQ_CONDIT]) {
            case DATY_INVAL:
                searq_valu = trave_qlv2n_reco(resctl, baval->rivcon, scont, rcont, lv2me);
                break;
            case DATY_OBID:
                searq_valu = objid_qlv2n_reco(resctl, baval->rivcon, scont, rcont, lv2me, (osv_oid_i *) pamvu->pamcon[QPAM_SEARQ_CONDIT]);
                break;
            case DATY_STRI:
            {
                switch (check_condi_type(pamvu->pamcon[QPAM_SEARQ_CONDIT])) {
                    case PREDI_TYPE_CONDI:
                        searq_valu = condi_qlv2n_reco(resctl, scont, rcont, baval, lv2me, pamvu->pamcon[QPAM_SEARQ_CONDIT]);
                        break;
                    case PREDI_TYPE_TRAVE:
                        searq_valu = trave_qlv2n_reco(resctl, baval->rivcon, scont, rcont, lv2me);
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

int searq_qcont_decla_reen(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu, lv2pme *lv2dme, contain *scont) {
    OSEVPF("searq_qcont_decla_re clasn:|%s|\n", pamvu->pamcon[QPAM_SEARQ_DESTIN]);
    int searq_valu = -1;
    //
    return searq_valu;
}

//


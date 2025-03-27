
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_header.h"

#include "basev_bzl.h"
#include "cqutili.h"
#include "astri_utili.h"
#include "query_utili.h"

#include "facto.h"
#include "facto_utili/facto_utili.h"


// odb:factory("clasn", "conobje", "obje:numb() > 0x00");
// :factory("clasn", conobje", "obje:numb() > 0x00");
// :factory("clasn", conobje1, conobje2", "conobje1:obje:numb() > 0x00 AND conobje2::numb() > 0x00");
// :factory("clasn", conobje1, conobje2", "conobje1::numb() > 0x00 AND conobje2::numb() > 0x00");
// odb:factory("clasn", "conobje");
#define QPAM_FACTO_DESTIN     0x00
#define QPAM_FACTO_SOURCE     0x01
#define QPAM_FACTO_CONDIT     0x02

int facto_qcont_conta(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu, contain *dcont, int scoun, contain **sconp) {
    OSEVPF("[FUNC]:facto_qcont_conta\n");
    lv2pme * lv2me[DCONT_SCONT_COUNT];
    if (DATY_STRI == pamvu->pamtyp[QPAM_FACTO_DESTIN]) {
        if (find_lv2pn_meta(lv2me, &baval->lv2pm_stm, pamvu->pamcon[QPAM_FACTO_DESTIN], sconp)) {
            OSEVPF("fdd lv2pm:%p\n", &baval->lv2pm_stm);
            return -1;
        }
    } else if (DATY_OBID == pamvu->pamtyp[QPAM_FACTO_DESTIN]) {
        if (find_lv2po_meta(lv2me, &baval->lv2pm_stm, (osv_oid_t *) pamvu->pamcon[QPAM_FACTO_DESTIN], sconp)) {
            OSEVPF("fdd lv2pm:%p\n", &baval->lv2pm_stm);
            return -1;
        }
    }
    //
    int facto_valu = -1;
    if (0x01 == scoun) {
        switch (pamvu->pamtyp[QPAM_FACTO_CONDIT]) {
            case DATY_INVAL:
                TRAVE_FCONT_ENSI(facto_valu, resctl, baval->rivcon, dcont, sconp[0x00], lv2me);
                break;
            case DATY_OBID:
                OBJID_FCONT_ENSI(facto_valu, resctl, baval->rivcon, dcont, sconp[0x00], lv2me, (osv_oid_i *) pamvu->pamcon[QPAM_FACTO_CONDIT]);
                break;
            case DATY_STRI:
            { // -1:error 0x00:objeid 0x01:predi
                switch (check_condi_type(pamvu->pamcon[QPAM_FACTO_CONDIT])) {
                    case PREDI_TYPE_CONDI:
                        CONDI_FCONT_ENSI(facto_valu, resctl, dcont, sconp[0x00], baval, lv2me, pamvu->pamcon[QPAM_FACTO_CONDIT]);
                        break;
                    case PREDI_TYPE_TRAVE:
                        TRAVE_FCONT_ENSI(facto_valu, resctl, baval->rivcon, dcont, sconp[0x00], lv2me);
                        break;
                    case PREDI_TYPE_EXCEP:
                    default:
                        break;
                }
            }
                break;
            default:
                facto_valu = -1;
                break;
        }
    } else if (0x02 == scoun) {
        switch (pamvu->pamtyp[QPAM_FACTO_CONDIT]) {
            case DATY_INVAL:
                facto_valu = trave_fcont_enco(resctl, baval->rivcon, dcont, sconp, lv2me);
                break;
            case DATY_OBID:
                facto_valu = objid_fcont_enco(resctl, baval->rivcon, dcont, sconp, lv2me, (osv_oid_i *) pamvu->pamcon[QPAM_FACTO_CONDIT]);
                break;
            case DATY_STRI:
            {
                switch (check_condi_type(pamvu->pamcon[QPAM_FACTO_CONDIT])) {
                    case PREDI_TYPE_CONDI:
                        facto_valu = condi_fcont_enco(resctl, dcont, sconp, baval, lv2me, pamvu->pamcon[QPAM_FACTO_CONDIT]);
                        break;
                    case PREDI_TYPE_TRAVE:
                        facto_valu = trave_fcont_enco(resctl, baval->rivcon, dcont, sconp, lv2me);
                        break;
                    case PREDI_TYPE_EXCEP:
                    default:
                        break;
                }
            }
                break;
            default:
                facto_valu = -1;
                break;
        }
    }
    //
    return facto_valu;
}

//

int facto_qcont_lv2pn(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu, int scoun, contain **sconp) {
    OSEVPF("pamvu->pamcon[QPAM_FACTO_DESTIN]:|%s| pamvu->pamcon[QPAM_FACTO_SOURCE]:|%s| pamvu->pamcon[QPAM_FACTO_CONDIT]:|%s|\n", pamvu->pamcon[QPAM_FACTO_DESTIN], pamvu->pamcon[QPAM_FACTO_SOURCE], pamvu->pamcon[QPAM_FACTO_CONDIT]);
    lv2pme * lv2me[DCONT_SCONT_COUNT];
    if (DATY_STRI == pamvu->pamtyp[QPAM_FACTO_DESTIN]) {
        if (find_lv2pn_meta(lv2me, &baval->lv2pm_stm, pamvu->pamcon[QPAM_FACTO_DESTIN], sconp)) {
            OSEVPF("fdd lv2pm:%p\n", &baval->lv2pm_stm);
            return -1;
        }
    } else if (DATY_OBID == pamvu->pamtyp[QPAM_FACTO_DESTIN]) {
        if (find_lv2po_meta(lv2me, &baval->lv2pm_stm, (osv_oid_t *) pamvu->pamcon[QPAM_FACTO_DESTIN], sconp)) {
            OSEVPF("fdd lv2pm:%p\n", &baval->lv2pm_stm);
            return -1;
        }
    }
    //
    int facto_valu = -1;
    if (0x01 == scoun) {
        switch (pamvu->pamtyp[QPAM_FACTO_CONDIT]) {
            case DATY_INVAL:
                TRAVE_FLTPN_ENSI(facto_valu, resctl, baval->rivcon, sconp[0x00], lv2me);
                break;
            case DATY_OBID:
                OBJID_FLTPN_ENSI(facto_valu, resctl, baval->rivcon, sconp[0x00], lv2me, (osv_oid_i *) pamvu->pamcon[QPAM_FACTO_CONDIT]);
                break;
            case DATY_STRI:
            {
                switch (check_condi_type(pamvu->pamcon[QPAM_FACTO_CONDIT])) {
                    case PREDI_TYPE_CONDI:
                        CONDI_FLTPN_ENSI(facto_valu, resctl, sconp[0x00], baval, lv2me, pamvu->pamcon[QPAM_FACTO_CONDIT]);
                        break;
                    case PREDI_TYPE_TRAVE:
                        TRAVE_FLTPN_ENSI(facto_valu, resctl, baval->rivcon, sconp[0x00], lv2me);
                        break;
                    case PREDI_TYPE_EXCEP:
                    default:
                        break;
                }
            }
                break;
            default:
                facto_valu = -1;
                break;
        }
    } else if (0x02 == scoun) {
        switch (pamvu->pamtyp[QPAM_FACTO_CONDIT]) {
            case DATY_INVAL:
                facto_valu = trave_flv2n_enco(resctl, baval->rivcon, sconp, lv2me);
                break;
            case DATY_OBID:
                facto_valu = objid_flv2n_enco(resctl, baval->rivcon, sconp, lv2me, (osv_oid_i *) pamvu->pamcon[QPAM_FACTO_CONDIT]);
                break;
            case DATY_STRI:
            {
                switch (check_condi_type(pamvu->pamcon[QPAM_FACTO_CONDIT])) {
                    case PREDI_TYPE_CONDI:
                        facto_valu = condi_flv2n_enco(resctl, sconp, baval, lv2me, pamvu->pamcon[QPAM_FACTO_CONDIT]);
                        break;
                    case PREDI_TYPE_TRAVE:
                        facto_valu = trave_flv2n_enco(resctl, baval->rivcon, sconp, lv2me);
                        break;
                    case PREDI_TYPE_EXCEP:
                    default:
                        break;
                }
            }
                break;
            default:
                facto_valu = -1;
                break;
        }
    }
    //
    return facto_valu;
}

//

int facto_qcont_decla(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu, lv2pme *lv2dme, int scoun, contain **sconp) {
    OSEVPF("[FUNC]:facto_qcont_decla decla:|%s|\n", pamvu->pamcon[QPAM_FACTO_DESTIN]);
    lv2pme * lv2me[DCONT_SCONT_COUNT];
    if (find_lv2pm_meta(lv2me, &baval->lv2pm_stm, lv2dme, sconp)) {
        OSEVPF("fdd lv2pm:%p\n", &baval->lv2pm_stm);
        return -1;
    }
    //
    int facto_valu = -1;
    if (0x01 == scoun) {
        switch (pamvu->pamtyp[QPAM_FACTO_CONDIT]) {
            case DATY_INVAL:
                facto_valu = trave_fdecl_ensi(resctl, baval->rivcon, sconp[0x00], lv2me[0x00]);
                break;
            case DATY_OBID:
                facto_valu = objid_fdecl_ensi(resctl, baval->rivcon, sconp[0x00], lv2me[0x00], (osv_oid_i *) pamvu->pamcon[QPAM_FACTO_CONDIT]);
                break;
            case DATY_STRI:
            {
                switch (check_condi_type(pamvu->pamcon[QPAM_FACTO_CONDIT])) {
                    case PREDI_TYPE_CONDI:
                        facto_valu = condi_fdecl_ensi(resctl, sconp[0x00], baval, lv2me[0x00], pamvu->pamcon[QPAM_FACTO_CONDIT]);
                        break;
                    case PREDI_TYPE_TRAVE:
                        facto_valu = trave_fdecl_ensi(resctl, baval->rivcon, sconp[0x00], lv2me[0x00]);
                        break;
                    case PREDI_TYPE_EXCEP:
                    default:
                        break;
                }
            }
                break;
            default:
                facto_valu = -1;
                break;
        }
    } else if (0x02 == scoun) {
        switch (pamvu->pamtyp[QPAM_FACTO_CONDIT]) {
            case DATY_INVAL:
                facto_valu = trave_fdecl_enco(resctl, baval->rivcon, sconp, lv2me[0x00]);
                break;
            case DATY_OBID:
                facto_valu = objid_fdecl_enco(resctl, baval->rivcon, sconp, lv2me[0x00], (osv_oid_i *) pamvu->pamcon[QPAM_FACTO_CONDIT]);
                break;
            case DATY_STRI:
            {
                switch (check_condi_type(pamvu->pamcon[QPAM_FACTO_CONDIT])) {
                    case PREDI_TYPE_CONDI:
                        facto_valu = condi_fdecl_enco(resctl, sconp, baval, lv2me[0x00], pamvu->pamcon[QPAM_FACTO_CONDIT]);
                        break;
                    case PREDI_TYPE_TRAVE:
                        facto_valu = trave_fdecl_enco(resctl, baval->rivcon, sconp, lv2me[0x00]);
                        break;
                    case PREDI_TYPE_EXCEP:
                    default:
                        break;
                }
            }
                break;
            default:
                facto_valu = -1;
                break;
        }
    }
    //
    return facto_valu;
}

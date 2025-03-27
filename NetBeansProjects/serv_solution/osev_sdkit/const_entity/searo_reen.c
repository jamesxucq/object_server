
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "third_party.h"
#include "kcomm_header.h"

#include "basev_bzl.h"
#include "cqutili.h"
#include "estri_utili.h"
#include "searo_utili/searo_utili.h"

#include "searo_reen.h"
#include "debug_funct_ce.h"

//

int searo_const_predi_reen(respo_ctrl *resctl, contain *contp, base_valu *baval, char *pamvu) {
    OSEVPF("[FUNC]:searo_const_predi_reen\n");
    lv2pme *lv2me = (lv2pme *) cache_value(&contp->lv2p_type, baval->lv2pm_stm.lv2pmo_hm);
    if (!lv2me) {
        OSEVPF("fdd lv2me:%p baval:%p\n", lv2me, baval);
        return -1;
    }
    //
    int searo_valu = -1;
    switch (contp->contype) {
        case REFER_CONTA_STATIC:
        {
            switch (contp->refe_coun) {
                case 0x01:
                {
                    if (pamvu) { // -1:error 0x00:objeid 0x01:predi 0x02:"*"
                        switch (check_condi_type(pamvu)) {
                            case PREDI_TYPE_CONDI:
                                searo_valu = condi_const_searo_rssi(resctl, contp, baval, lv2me, pamvu);
                                break;
                            case PREDI_TYPE_TRAVE:
                                searo_valu = trave_const_searo_rssi(resctl, contp, baval, lv2me);
                                break;
                            case PREDI_TYPE_EXCEP:
                            default:
                                break;
                        }
                    } else searo_valu = trave_const_searo_rssi(resctl, contp, baval, lv2me);
                }
                    break;
                case 0x02:
                {
                    if (pamvu) { // -1:error 0x00:objeid 0x01:predi 0x02:"*"
                        switch (check_condi_type(pamvu)) {
                            case PREDI_TYPE_CONDI:
                                searo_valu = condi_const_searo_rsco(resctl, contp, baval, lv2me, pamvu);
                                break;
                            case PREDI_TYPE_TRAVE:
                                searo_valu = trave_const_searo_rsco(resctl, contp, baval, lv2me);
                                break;
                            case PREDI_TYPE_EXCEP:
                            default:
                                break;
                        }
                    } else searo_valu = trave_const_searo_rsco(resctl, contp, baval, lv2me);
                }
                    break;
                default:
                    break;
            }
        }
            break;
        case REFER_CONTA_DYNAMI:
        {
            switch (contp->refe_coun) {
                case 0x01:
                {
                    if (pamvu) { // -1:error 0x00:objeid 0x01:predi 0x02:"*"
                        switch (check_condi_type(pamvu)) {
                            case PREDI_TYPE_CONDI:
                                searo_valu = condi_const_searo_rdsi(resctl, contp, baval, lv2me, pamvu);
                                break;
                            case PREDI_TYPE_TRAVE:
                                searo_valu = trave_const_searo_rdsi(resctl, contp, baval, lv2me);
                                break;
                            case PREDI_TYPE_EXCEP:
                            default:
                                break;
                        }
                    } else searo_valu = trave_const_searo_rdsi(resctl, contp, baval, lv2me);
                }
                    break;
                case 0x02:
                {
                    if (pamvu) { // -1:error 0x00:objeid 0x01:predi 0x02:"*"
                        switch (check_condi_type(pamvu)) {
                            case PREDI_TYPE_CONDI:
                                searo_valu = condi_const_searo_rdco(resctl, contp, baval, lv2me, pamvu);
                                break;
                            case PREDI_TYPE_TRAVE:
                                searo_valu = trave_const_searo_rdco(resctl, contp, baval, lv2me);
                                break;
                            case PREDI_TYPE_EXCEP:
                            default:
                                break;
                        }
                    } else searo_valu = trave_const_searo_rdco(resctl, contp, baval, lv2me);
                }
                    break;
                default:
                    break;
            }
        }
            break;
        case ENTIT_CONTA_NORMAL:
        default:
            break;
    }
    // OSEVPF("lv2me:%08X, lv2me->bound:%08X\n", lv2me, lv2me->bound);
    return searo_valu;
}

//

int searo_const_objid_reen(respo_ctrl *resctl, contain *contp, base_valu *baval, osv_oid_i *searo_obid) {
    OSEVPF("[FUNC]:searo_const_objid_reen\n");
    lv2pme *lv2me = (lv2pme *) cache_value(&contp->lv2p_type, baval->lv2pm_stm.lv2pmo_hm);
    if (!lv2me) {
        OSEVPF("fdd lv2me:%p baval:%p\n", lv2me, baval);
        return -1;
    }
    //
    int searo_valu = -1;
    switch (contp->contype) {
        case REFER_CONTA_STATIC:
        {
            switch (contp->refe_coun) {
                case 0x01:
                    if (INSTAN_UNIQUE != searo_obid->osev_unique)
                        return -1;
                    searo_valu = objid_const_searo_rssi(resctl, contp, baval, lv2me, searo_obid);
                    break;
                case 0x02:
                    searo_valu = objid_const_searo_rsco(resctl, contp, baval, lv2me, searo_obid);
                    break;
                default:
                    break;
            }
        }
            break;
        case REFER_CONTA_DYNAMI:
        {
            switch (contp->refe_coun) {
                case 0x01:
                    if (INSTAN_UNIQUE != searo_obid->osev_unique)
                        return -1;
                    searo_valu = objid_const_searo_rdsi(resctl, contp, baval, lv2me, searo_obid);
                    break;
                case 0x02:
                    searo_valu = objid_const_searo_rdco(resctl, contp, baval, lv2me, searo_obid);
                    break;
                default:
                    break;
            }
        }
            break;
        case ENTIT_CONTA_NORMAL:
        default:
            break;
    }
    //
    return searo_valu;
}

//

int searo_const_trave_reen(respo_ctrl *resctl, contain *contp, base_valu *baval) {
    OSEVPF("[FUNC]:searo_const_trave_reen\n");
    // OSEVPF("lv2me:%08X, lv2me->bound:%08X\n", lv2me, lv2me->bound);
    lv2pme *lv2me = (lv2pme *) cache_value(&contp->lv2p_type, baval->lv2pm_stm.lv2pmo_hm);
    if (!lv2me) {
        OSEVPF("fdd lv2me:%p baval:%p\n", lv2me, baval);
        return -1;
    }
    //
    int searo_valu = -1;
    switch (contp->contype) {
        case REFER_CONTA_STATIC:
        {
            switch (contp->refe_coun) {
                case 0x01:
                    searo_valu = trave_const_searo_rssi(resctl, contp, baval, lv2me);
                    break;
                case 0x02:
                    searo_valu = trave_const_searo_rsco(resctl, contp, baval, lv2me);
                    break;
                default:
                    break;
            }
        }
            break;
        case REFER_CONTA_DYNAMI:
        {
            switch (contp->refe_coun) {
                case 0x01:
                    searo_valu = trave_const_searo_rdsi(resctl, contp, baval, lv2me);
                    break;
                case 0x02:
                    searo_valu = trave_const_searo_rdco(resctl, contp, baval, lv2me);
                    break;
                default:
                    break;
            }
        }
            break;
        case ENTIT_CONTA_NORMAL:
        default:
            break;
    }
    //
    return searo_valu;
}


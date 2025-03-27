#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "third_party.h"
#include "commo_header.h"
#include "kcomm_header.h"
#include "basev_bzl.h"
#include "cqutili.h"
#include "estri_utili.h"
#include "lv2p_meta.h"
#include "searo_utili/searo_utili.h"

#include "searo.h"
#include "debug_funct_ce.h"

//

int searo_const_predi_ensi(respo_ctrl *resctl, contain *contp, base_valu *baval, char *pamvu) {
    OSEVPF("searo_const_predi_ensi\n");
    lv2pme *lv2me = (lv2pme *) cache_value(&contp->lv2p_type, baval->lv2pm_stm.lv2pmo_hm);
    if (!lv2me) {
        OSEVPF("fdd lv2me:%p lv2pm_stm:%p\n", lv2me, &baval->lv2pm_stm);
        return -1;
    }
    OSEVPF("lv2pn:|%s| lv2pm_stm:%p\n", lv2me->lv2pn, &baval->lv2pm_stm);
    // OSEVPF("lv2me:%08X, lv2me->bound:%08X\n", lv2me, lv2me->bound);
    int searo_valu = -1;
    if (pamvu) { // -1:error 0x00:objeid 0x01:predi 0x02:"*"
        switch (check_condi_type(pamvu)) {
            case PREDI_TYPE_CONDI:
                searo_valu = condi_const_searo_ensi(resctl, contp, baval, lv2me, pamvu);
                break;
            case PREDI_TYPE_TRAVE:
                searo_valu = trave_const_searo_ensi(resctl, baval->rivcon, contp, lv2me);
                break;
            case PREDI_TYPE_EXCEP:
            default:
                break;
        }
    } else searo_valu = trave_const_searo_ensi(resctl, baval->rivcon, contp, lv2me);
    //
    return searo_valu;
}

//

int searo_const_objid_ensi(respo_ctrl *resctl, contain *contp, base_valu *baval, osv_oid_i *searo_obid) {
    OSEVPF("searo_const_predi_ensi\n");
    lv2pme *lv2me = (lv2pme *) cache_value(&contp->lv2p_type, baval->lv2pm_stm.lv2pmo_hm);
    if (!lv2me) return -1;
    OSEVPF("lv2pn:|%s| lv2pm_stm:%p\n", lv2me->lv2pn, &baval->lv2pm_stm);
    // contp->refe_coun
    // OSEVPF("lv2me:%08X, lv2me->bound:%08X\n", lv2me, lv2me->bound);
    //
    if (INSTAN_UNIQUE != searo_obid->osev_unique)
        return -1;
    int searo_valu = objid_const_searo_ensi(resctl, baval->rivcon, contp, lv2me, searo_obid);
    return searo_valu;
}

int searo_const_trave_ensi(respo_ctrl *resctl, contain *contp, base_valu *baval) {
    OSEVPF("searo_const_trave_ensi\n");
    lv2pme *lv2me = (lv2pme *) cache_value(&contp->lv2p_type, baval->lv2pm_stm.lv2pmo_hm);
    if (!lv2me) {
        OSEVPF("fdd lv2me:%p lv2pm_stm:%p\n", lv2me, &baval->lv2pm_stm);
        return -1;
    }
    // OSEVPF("lv2me:%08X, lv2me->bound:%08X\n", lv2me, lv2me->bound);
    int searo_valu = trave_const_searo_ensi(resctl, baval->rivcon, contp, lv2me);
    return searo_valu;
}










/* 
 * File:   searo_entit_rsco.h
 * Author: james
 *
 * Created on 2024.6.3, PM 2:57
 */

#ifndef SEARO_ENTIT_RSCO_H
#define SEARO_ENTIT_RSCO_H

#include "rive_bzl.h"
#include "contain.h"

#ifdef __cplusplus
extern "C" {
#endif

//
    int condi_const_searo_rsco(respo_ctrl *resctl, contain *contp, base_valu *baval, lv2pme *lv2me, char *condi);
    int objid_const_searo_rsco(respo_ctrl *resctl, contain *contp, base_valu *baval, lv2pme *lv2me, osv_oid_i *searo_obid);
    int trave_const_searo_rsco(respo_ctrl *resctl, contain *contp, base_valu *baval, lv2pme *lv2me);

#ifdef __cplusplus
}
#endif

#endif /* SEARO_ENTIT_RSCO_H */


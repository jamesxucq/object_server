
/* 
 * File:   searo_entit_rdco.h
 * Author: James Xu
 *
 * Created on 2024.6.3, PM 2:56
 */

#ifndef SEARO_ENTIT_RDCO_H
#define SEARO_ENTIT_RDCO_H

#include "rive_bzl.h"
#include "contain.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int condi_const_searo_rdco(respo_ctrl *resctl, contain *contp, base_valu *baval, lv2pme *lv2me, char *condi);
    int objid_const_searo_rdco(respo_ctrl *resctl, contain *contp, base_valu *baval, lv2pme *lv2me, osv_oid_i *searo_obid);
    int trave_const_searo_rdco(respo_ctrl *resctl, contain *contp, base_valu *baval, lv2pme *lv2me);

#ifdef __cplusplus
}
#endif

#endif /* SEARO_ENTIT_RDCO_H */


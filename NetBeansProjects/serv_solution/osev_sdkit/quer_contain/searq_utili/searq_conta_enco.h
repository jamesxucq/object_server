
/* 
 * File:   searq_conta_enco.h
 * Author: James Xu
 *
 * Created on 2022.10.31, PM 3:20
 */

#ifndef SEARQ_CONTA_ENCO_H
#define SEARQ_CONTA_ENCO_H

#include "commo_header.h"
#include "rive_bzl.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int condi_qcont_enco(respo_ctrl *resctl, contain *dcont, stati_scont *scont, base_valu *baval, lv2pme *lv2me, char *condi);
    int objid_qcont_enco(respo_ctrl *resctl, rive_conne *rivcon, contain *dcont, stati_scont *scont, osv_oid_i *searq_obid);
    int trave_qcont_enco(respo_ctrl *resctl, rive_conne *rivcon, contain *dcont, stati_scont *scont);

#ifdef __cplusplus
}
#endif

#endif /* SEARQ_CONTA_ENCO_H */


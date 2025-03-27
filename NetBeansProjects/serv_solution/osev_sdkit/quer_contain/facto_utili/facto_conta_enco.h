
/* 
 * File:   facto_conta_enco.h
 * Author: James Xu
 *
 * Created on 2022.10.31, PM 3:18
 */

#ifndef FACTO_CONTA_ENCO_H
#define FACTO_CONTA_ENCO_H

#include "commo_header.h"
#include "rive_bzl.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int condi_fcont_enco(respo_ctrl *resctl, contain *dcont, contain **sconp, base_valu *baval, lv2pme **lv2mep, char *condi);
    int objid_fcont_enco(respo_ctrl *resctl, rive_conne *rivcon, contain *dcont, contain **sconp, lv2pme **lv2mep, osv_oid_i *facto_obid);
    int trave_fcont_enco(respo_ctrl *resctl, rive_conne *rivcon, contain *dcont, contain **sconp, lv2pme **lv2mep);


#ifdef __cplusplus
}
#endif

#endif /* FACTO_CONTA_ENCO_H */


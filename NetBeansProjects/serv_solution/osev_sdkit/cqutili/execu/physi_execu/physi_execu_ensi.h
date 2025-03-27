
/* 
 * File:   physi_execu_ensi.h
 * Author: James
 *
 * Created on 2019.3.26, 8:57
 */

#ifndef PHYSI_EXECU_ENSI_H
#define PHYSI_EXECU_ENSI_H

#include "commo_header.h"
// #include "plan/quer_plan_ensi.h"

#ifdef __cplusplus
extern "C" {
#endif


    //
    int execu_physi_searo_ensi(plan_node_ensi *firspn, rive_ha *stora_ha, base_valu *baval, lv2pme *lv2me);

    //
    int ephys_searq_conta_ensi(plan_node_ensi *firspn, rive_ha *stora_ha, base_valu *baval, lv2pme *lv2me);
    int ephys_searq_conta_enob(plan_node_ensi *firspn, rive_ha *stora_ha, base_valu *baval, lv2pme *lv2me);
    int ephys_searq_lv2pn_ensi(plan_node_ensi *firspn, rive_ha *stora_ha, base_valu *baval, lv2pme *lv2me);
    int ephys_searq_lv2pn_enob(plan_node_ensi *firspn, rive_ha *stora_ha, base_valu *baval, lv2pme *lv2me);

    //
    int ephys_facto_conta_ensi(plan_node_ensi *firspn, rive_ha *stora_ha, base_valu *baval, lv2pme **lv2mep);
    int ephys_facto_conta_enob(plan_node_ensi *firspn, rive_ha *stora_ha, base_valu *baval, lv2pme **lv2mep);
    int ephys_facto_lv2pn_ensi(plan_node_ensi *firspn, rive_ha *stora_ha, base_valu *baval, lv2pme **lv2mep);
    int ephys_facto_lv2pn_enob(plan_node_ensi *firspn, rive_ha *stora_ha, base_valu *baval, lv2pme **lv2mep);

    //
    int execu_physi_dropo(plan_node_ensi *firspn, rive_ha *stora_ha, base_valu *baval, lv2pme *lv2me);
    int execu_physi_invoko(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk);

    //
    int ephys_refeo_rcont_ensi(plan_node_ensi *firspn, rive_ha *stora_ha, base_valu *baval, lv2pme *lv2me);


#ifdef __cplusplus
}
#endif

#endif /* PHYSI_EXECU_ENSI_H */


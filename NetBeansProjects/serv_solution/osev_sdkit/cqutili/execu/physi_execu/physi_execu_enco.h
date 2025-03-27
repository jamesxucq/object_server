
/* 
 * File:   physi_execu_enco.h
 * Author: James Xu
 *
 * Created on 2022.11.1, AM 9:35
 */

#ifndef PHYSI_EXECU_ENCO_H
#define PHYSI_EXECU_ENCO_H

#include "commo_header.h"
// #include "plan/quer_plan_enco.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int ephys_searq_conta_enco(plan_node_enco *firspn, rive_ha *stora_ha, base_valu *baval, lv2pme *lv2me);
    int ephys_searq_lv2pn_enco(plan_node_enco *firspn, rive_ha *stora_ha, base_valu *baval, lv2pme *lv2me);
    int ephys_facto_conta_enco(plan_node_enco *firspn, rive_ha *stora_ha, base_valu *baval, lv2pme **lv2mep);
    int ephys_facto_lv2pn_enco(plan_node_enco *firspn, rive_ha *stora_ha, base_valu *baval, lv2pme **lv2mep);

     //
    int ephys_refeo_rcont_enco(plan_node_enco *firspn, rive_ha *stora_ha, base_valu *baval, lv2pme *lv2me);

#ifdef __cplusplus
}
#endif

#endif /* PHYSI_EXECU_ENCO_H */


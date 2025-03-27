
/* 
 * File:   physi_execu_reco.h
 * Author: James Xu
 *
 * Created on 2024.6.20, AM 9:46
 */

#ifndef PHYSI_EXECU_RECO_H
#define PHYSI_EXECU_RECO_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    int execu_physi_searo_rsco(plan_node_enco *firspn, contain *contp, base_valu *baval, lv2pme *lv2me);
    int execu_physi_searo_rdco(plan_node_enco *firspn, contain *contp, base_valu *baval, lv2pme *lv2me);

    //
    int ephys_searq_lv2pn_reco(plan_node_enco *firspn, rive_ha *stora_ha, base_valu *baval, lv2pme **lv2mep);

#ifdef __cplusplus
}
#endif

#endif /* PHYSI_EXECU_RECO_H */


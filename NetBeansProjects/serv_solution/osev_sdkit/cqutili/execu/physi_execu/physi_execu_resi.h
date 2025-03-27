
/* 
 * File:   physi_execu_resi.h
 * Author: James Xu
 *
 * Created on 2022.10.27, AM 10:54
 */

#ifndef PHYSI_EXECU_REEN_H
#define PHYSI_EXECU_REEN_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int execu_physi_searo_rssi(plan_node_ensi *firspn, contain *contp, base_valu *baval, lv2pme *lv2me);
    int execu_physi_searo_rsob(plan_node_ensi *firspn, contain *contp, base_valu *baval, lv2pme *lv2me);
    
    //
    int execu_physi_searo_rdsi(plan_node_ensi *firspn, contain *contp, base_valu *baval, lv2pme *lv2me);
    int execu_physi_searo_rdob(plan_node_ensi *firspn, contain *contp, base_valu *baval, lv2pme *lv2me);

    //
    int ephys_searq_lv2pn_resi(plan_node_ensi *firspn, rive_ha *stora_ha, base_valu *baval, lv2pme **lv2mep);

#ifdef __cplusplus
}
#endif

#endif /* PHYSI_EXECU_REEN_H */



/* 
 * File:   debug_funct_qc.h
 * Author: James Xu
 *
 * Created on 2022.11.15, PM 5:04
 */

#ifndef DEBUG_FUNCT_QC_H
#define DEBUG_FUNCT_QC_H

#include "plan/plan_node_ensi.h"
#include "plan/plan_node_enco.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    void p_plan_node_ensi(plan_node_ensi *quer_tok);
    void p_plan_node_enco(plan_node_enco *quer_tok);
    void p_plan_node_resi(plan_node_ensi *quer_tok);
    void p_plan_node_reco(plan_node_enco *quer_tok);
    void p_lv2p_expa_t(lv2p_expa_t *lv2expt);
    void p_contain(contain *contp);

#ifdef _DEBUG
#define PRIN_plan_node_ensi p_plan_node_ensi
#define PRIN_plan_node_enco p_plan_node_enco    
#define PRIN_plan_node_resi p_plan_node_resi    
#define PRIN_plan_node_reco p_plan_node_reco    
#define PRIN_lv2p_expa_t p_lv2p_expa_t    
#define PRIN_contain p_contain
#else
#define PRIN_plan_node_ensi(...)
#define PRIN_plan_node_enco(...)
#define PRIN_plan_node_resi(...)
#define PRIN_plan_node_reco(...)
#define PRIN_lv2p_expa_t(...)
#define PRIN_contain(...)
#endif
    
    
#ifdef __cplusplus
}
#endif

#endif /* DEBUG_FUNCT_QC_H */


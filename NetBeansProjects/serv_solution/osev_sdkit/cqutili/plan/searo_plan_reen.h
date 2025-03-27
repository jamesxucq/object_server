
/* 
 * File:   searo_plan_reen.h
 * Author: James Xu
 *
 * Created on 2024.6.24, AM 2:09
 */

#ifndef SEARO_PLAN_REEN_H
#define SEARO_PLAN_REEN_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    int creat_searo_plan_resi(plan_node_ensi *firspn, respo_ctrl *resctl, contain *scont, oper_node *synt_head);
    int creat_searo_plan_reco(plan_node_enco *firspn, respo_ctrl *resctl, contain **scont, oper_node *synt_head);

    //
    int creat_refro_plan_rdsi(plan_node_ensi *firspn, contain *dcont, contain *scont, oper_node *synt_head);
    
    //
    int creat_refro_plan_rdco(plan_node_enco *firspn, contain *dcont, contain **sconp, oper_node *synt_head);
    
#ifdef __cplusplus
}
#endif

#endif /* SEARO_PLAN_REEN_H */


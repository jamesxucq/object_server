
/* 
 * File:   searq_plan_enco.h
 * Author: James Xu
 *
 * Created on 2022.11.1, AM 9:57
 */

#ifndef SEARQ_PLAN_ENCO_H
#define SEARQ_PLAN_ENCO_H

// #include "plan/quer_plan_enco.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int creat_sconq_plan_enco(plan_node_enco *firspn, respo_ctrl *resctl, contain *dcont, stati_scont *scont, oper_node *synt_head);
    int creat_slv2q_plan_enco(plan_node_enco *firspn, respo_ctrl *resctl, contain **sconp, oper_node *synt_head);

    //

#ifdef __cplusplus
}
#endif

#endif /* SEARQ_PLAN_ENCO_H */


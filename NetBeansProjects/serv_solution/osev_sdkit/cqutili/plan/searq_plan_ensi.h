
/* 
 * File:   searq_plan_ensi.h
 * Author: James Xu
 *
 * Created on 2021.6.1, AM9:11
 */

#ifndef SEARQ_PLAN_ENSI_H
#define SEARQ_PLAN_ENSI_H

// #include "plan/quer_plan_ensi.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int creat_sconq_plan_ensi(plan_node_ensi *firspn, respo_ctrl *resctl, contain *dcont, stati_scont *scont, oper_node *synt_head);
    int creat_slv2q_plan_ensi(plan_node_ensi *firspn, respo_ctrl *resctl, contain *scont, oper_node *synt_head);


#ifdef __cplusplus
}
#endif

#endif /* SEARQ_PLAN_ENSI_H */


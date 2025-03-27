
/* 
 * File:   facto_plan_ensi.h
 * Author: James Xu
 *
 * Created on 2022.10.10, PM 3:18
 */

#ifndef FACTO_PLAN_ENSI_H
#define FACTO_PLAN_ENSI_H

// #include "plan/quer_plan_ensi.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int creat_fconq_plan_ensi(plan_node_ensi *firspn, respo_ctrl *resctl, contain *dcont, contain *scont, oper_node *synt_head);
    int creat_flv2q_plan_ensi(plan_node_ensi *firspn, respo_ctrl *resctl, contain *scont, oper_node *synt_head);

#ifdef __cplusplus
}
#endif

#endif /* FACTO_PLAN_ENSI_H */


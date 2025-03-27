
/* 
 * File:   facto_plan_enco.h
 * Author: James Xu
 *
 * Created on 2022.11.1, AM 9:57
 */

#ifndef FACTO_PLAN_ENCO_H
#define FACTO_PLAN_ENCO_H

// #include "plan/quer_plan_enco.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int creat_fconq_plan_enco(plan_node_enco *firspn, respo_ctrl *resctl, contain *dcont, contain **sconp, lv2pme **lv2mep, oper_node *synt_head);
    int creat_flv2q_plan_enco(plan_node_enco *firspn, respo_ctrl *resctl, contain **sconp, lv2pme **lv2mep, oper_node *synt_head);

#ifdef __cplusplus
}
#endif

#endif /* FACTO_PLAN_ENCO_H */



/* 
 * File:   searq_plan_reen.h
 * Author: James Xu
 *
 * Created on 2022.10.27, AM 10:41
 */

#ifndef SEARQ_PLAN_REEN_H
#define SEARQ_PLAN_REEN_H

// #include "plan/quer_plan_ensi.h"
// #include "plan/quer_plan_enco.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int creat_slv2q_plan_resi(plan_node_ensi *firspn, respo_ctrl *resctl, contain *scont, contain *rcont, oper_node *synt_head);

    //
    int creat_slv2q_plan_reco(plan_node_enco *firspn, respo_ctrl *resctl, contain *scont, contain **rconp, lv2pme **lv2mep, oper_node *synt_head);

#ifdef __cplusplus
}
#endif

#endif /* SEARQ_PLAN_REEN_H */


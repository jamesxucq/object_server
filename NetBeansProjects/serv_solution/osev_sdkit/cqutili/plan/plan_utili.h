
#ifndef PLAN_UTILI_H
#define PLAN_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif
    //
#include <stdlib.h>

    // #include "plan/quer_plan_ensi.h"
    // #include "plan/quer_plan_enco.h"

    //
    plan_node_ensi *appe_noeq_node_ensi(plan_node_ensi *querpn, oper_node *leno, oper_node *rino, char *qcont);
    plan_node_ensi *appe_equa_node_ensi(plan_node_ensi *querpn, oper_node *leno, oper_node *rino, char *qcont);
    plan_node_ensi *appe_grth_node_ensi(plan_node_ensi *querpn, oper_node *leno, oper_node *rino, char *qcont);
    plan_node_ensi *appe_leeq_node_ensi(plan_node_ensi *querpn, oper_node *leno, oper_node *rino, char *qcont);
    plan_node_ensi *appe_leth_node_ensi(plan_node_ensi *querpn, oper_node *leno, oper_node *rino, char *qcont);
    plan_node_ensi *appe_greq_node_ensi(plan_node_ensi *querpn, oper_node *leno, oper_node *rino, char *qcont);
    plan_node_ensi *appe_plus_node_ensi(plan_node_ensi *querpn, oper_node *leno, oper_node *rino, char *qcont);
    plan_node_ensi *appe_minu_node_ensi(plan_node_ensi *querpn, oper_node *leno, oper_node *rino, char *qcont);

    //
    plan_node_ensi *appe_or_node_ensi(plan_node_ensi *querpn, plan_node_ensi *left_chil, plan_node_ensi *rich_chil);
    plan_node_ensi *appe_and_node_ensi(plan_node_ensi *querpn, plan_node_ensi *left_chil, plan_node_ensi *rich_chil);
    plan_node_ensi *appe_not_node_ensi(plan_node_ensi *querpn, plan_node_ensi *left_chil);

    /////////////////////////////////
    plan_node_enco *appe_noeq_node_enco(plan_node_enco *querpn, oper_node *leno, oper_node *rino, char *qcont);
    plan_node_enco *appe_equa_node_enco(plan_node_enco *querpn, oper_node *leno, oper_node *rino, char *qcont);
    plan_node_enco *appe_grth_node_enco(plan_node_enco *querpn, oper_node *leno, oper_node *rino, char *qcont);
    plan_node_enco *appe_leeq_node_enco(plan_node_enco *querpn, oper_node *leno, oper_node *rino, char *qcont);
    plan_node_enco *appe_leth_node_enco(plan_node_enco *querpn, oper_node *leno, oper_node *rino, char *qcont);
    plan_node_enco *appe_greq_node_enco(plan_node_enco *querpn, oper_node *leno, oper_node *rino, char *qcont);
    plan_node_enco *appe_plus_node_enco(plan_node_enco *querpn, oper_node *leno, oper_node *rino, char *qcont);
    plan_node_enco *appe_minu_node_enco(plan_node_enco *querpn, oper_node *leno, oper_node *rino, char *qcont);

    //
    plan_node_enco *appe_or_node_enco(plan_node_enco *querpn, plan_node_enco *left_chil, plan_node_enco *rich_chil);
    plan_node_enco *appe_and_node_enco(plan_node_enco *querpn, plan_node_enco *left_chil, plan_node_enco *rich_chil);
    plan_node_enco *appe_not_node_enco(plan_node_enco *querpn, plan_node_enco *left_chil);


    //
    char *find_conta_enco(contain **qcontp, char *lev1n_lv2pn);
    char *find_conta_cost(stati_scont *qscont, char *lev1n_lv2pn);

#ifdef __cplusplus
}
#endif

#endif /* PLAN_UTILI_H */

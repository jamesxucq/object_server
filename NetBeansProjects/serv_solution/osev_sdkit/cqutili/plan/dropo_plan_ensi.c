
#include "commo_header.h"
#include "kcomm_header.h"
#include "lexic/valtok.h"
#include "gramm/synta_tree.h"
#include "plan/plan_node_ensi.h"

#include "dropo_plan_ensi.h"

//

static plan_node_ensi *initi_dropo_plan(plan_node_ensi *querpn) {
    OSEVPF("[FUNC]:initi_dropo_plan\n");
    querpn->acti_oper = INIT_QUERY_ACCO;
    querpn->resctl = NULL;
    return ++querpn;
}

//

static plan_node_ensi *final_dropo_plan(plan_node_ensi *querpn, contain *qcontp) {
    OSEVPF("[FUNC]:final_dropo_plan\n");
    querpn->acti_oper = FINAL_QUDRY_ACCO;
    strcpy(querpn->cont_name, qcontp->cont_name);
    //
    return ++querpn;
}

//

int creat_plan_dropo(plan_node_ensi *firspn, contain *qcontp, oper_node *synt_head) {
    plan_node_ensi *quer_tok;
    OSEVPF("[FUNC]:initi_dropo_plan\n");
    if (!(quer_tok = initi_dropo_plan(firspn)))
        return -1;
    OSEVPF("open_curso_ensi\n");
    if (!(quer_tok = open_curso_ensi(quer_tok, qcontp)))
        return -1;
    OSEVPF("synt_plan_ensi\n");
    if (!(quer_tok = synt_plan_ensi(quer_tok, synt_head, qcontp)))
        return -1;
    OSEVPF("set_initi_valu_ensi\n");
    set_initi_valu_ensi(firspn, quer_tok - 0x01);
    OSEVPF("close_curso_ensi\n");
    if (!(quer_tok = close_curso_ensi(quer_tok, qcontp)))
        return -1;
    OSEVPF("final_dropo_plan\n");
    if (!(quer_tok = final_dropo_plan(quer_tok, qcontp)))
        return -1;
    (quer_tok)->acti_oper = INVA_ACCO;
    //
    OSEVPF("creat_plan_quer_single end.....\n");
    return 0x00;
}

#include "commo_header.h"
#include "kcomm_header.h"
#include "lexic/valtok.h"
#include "gramm/synta_tree.h"
#include "plan_node_ensi.h"

#include "searo_plan_ensi.h"

//

static plan_node_ensi *initi_searo_plan(plan_node_ensi *querpn, respo_ctrl *resctl) {
    // OSEVPF("[FUNC]:initi_searo_plan\n");
    // OSEVPF("resctl:|%p|, resctl->resp_stram:|%p|\n", resctl, resctl->resp_stram);
    querpn->acti_oper = INIT_QUERY_ACCO;
    querpn->resctl = resctl;
    return ++querpn;
}

static plan_node_ensi *final_searo_plan(plan_node_ensi *querpn, contain *scont) {
    // OSEVPF("[FUNC]:final_searo_plan\n");
    querpn->acti_oper = FINAL_QUDRY_ACCO;
    strcpy(querpn->cont_name, scont->cont_name);
    //
    return ++querpn;
}

//

int creat_searo_plan_ensi(plan_node_ensi *firspn, respo_ctrl *resctl, contain *scont, oper_node *synt_head) {
    plan_node_ensi *quer_tok;
    OSEVPF("[FUNC]:initi_searo_plan start.....\n");
    if (!(quer_tok = initi_searo_plan(firspn, resctl)))
        return -1;
    OSEVPF("open_curso_ensi\n");
    if (!(quer_tok = open_curso_ensi(quer_tok, scont)))
        return -1;
    OSEVPF("synt_plan_ensi\n");
    if (!(quer_tok = synt_plan_ensi(quer_tok, synt_head, scont)))
        return -1;
    OSEVPF("set_initi_valu_ensi\n");
    set_initi_valu_ensi(firspn, quer_tok - 0x01);
    OSEVPF("close_curso_ensi\n");
    if (!(quer_tok = close_curso_ensi(quer_tok, scont)))
        return -1;
    OSEVPF("final_searo_plan\n");
    if (!(quer_tok = final_searo_plan(quer_tok, scont)))
        return -1;
    (quer_tok)->acti_oper = INVA_ACCO;
    //
    OSEVPF("creat_searo_plan_ensi end.....\n");
    return 0x00;
}



#include "commo_header.h"
#include "kcomm_header.h"
#include "lexic/valtok.h"
#include "gramm/synta_tree.h"
#include "plan/plan_node_ensi.h"

#include "facto_plan_ensi.h"

//

static plan_node_ensi *initi_fconq_plan_ensi(plan_node_ensi *querpn, respo_ctrl *resctl, contain *dcont) {
    querpn->acti_oper = INIT_QUERY_ACCO;
    strcpy(querpn->cont_name, dcont->cont_name);
    querpn->resctl = resctl;
    return ++querpn;
}

static plan_node_ensi *final_fconq_plan_ensi(plan_node_ensi *querpn, contain *scont) {
    querpn->acti_oper = FINAL_QUDRY_ACCO;
    strcpy(querpn->cont_name, scont->cont_name);
    strcpy(querpn->source_str, "xx, ax ,cx");
    //
    return ++querpn;
}

//

int creat_fconq_plan_ensi(plan_node_ensi *firspn, respo_ctrl *resctl, contain *dcont, contain *scont, oper_node *synt_head) {
    plan_node_ensi *quer_tok;
    OSEVPF("[FUNC]:initi_fconq_plan_ensi\n");
    if (!(quer_tok = initi_fconq_plan_ensi(firspn, resctl, dcont)))
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
    OSEVPF("final_fconq_plan_ensi\n");
    if (!(quer_tok = final_fconq_plan_ensi(quer_tok, scont)))
        return -1;
    (quer_tok)->acti_oper = INVA_ACCO;
    //
    OSEVPF("creat_facto_plan_siingle end.....\n");
    return 0x00;
}

//

static plan_node_ensi *initi_flv2q_plan_ensi(plan_node_ensi *querpn, respo_ctrl *resctl) {
    querpn->acti_oper = INIT_QUERY_ACCO;
    querpn->resctl = resctl;
    return ++querpn;
}

static plan_node_ensi *final_flv2q_plan_ensi(plan_node_ensi *querpn, contain *scont) {
    querpn->acti_oper = FINAL_QUDRY_ACCO;
    strcpy(querpn->cont_name, scont->cont_name);
    strcpy(querpn->source_str, "xx, ax ,cx");
    //
    return ++querpn;
}

//

int creat_flv2q_plan_ensi(plan_node_ensi *firspn, respo_ctrl *resctl, contain *scont, oper_node *synt_head) {
    plan_node_ensi *quer_tok;
    OSEVPF("[FUNC]:initi_flv2q_plan_ensi\n");
    if (!(quer_tok = initi_flv2q_plan_ensi(firspn, resctl)))
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
    OSEVPF("final_flv2q_plan_ensi\n");
    if (!(quer_tok = final_flv2q_plan_ensi(quer_tok, scont)))
        return -1;
    (quer_tok)->acti_oper = INVA_ACCO;
    //
    OSEVPF("creat_facto_plan_siingle end.....\n");
    return 0x00;
}


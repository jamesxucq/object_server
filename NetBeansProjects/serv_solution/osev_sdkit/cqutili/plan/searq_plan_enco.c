
#include "commo_header.h"
#include "kcomm_header.h"
#include "lexic/valtok.h"
#include "gramm/synta_tree.h"
#include "plan_node_enco.h"

#include "searq_plan_enco.h"
#include "stati_scont.h"

//

static plan_node_enco *initi_sconq_plan_enco(plan_node_enco *querpn, respo_ctrl *resctl, contain * dcont) {
    querpn->acti_oper = INIT_QUERY_ACCO;
    strcpy(querpn->cont_name, dcont->cont_name);
    querpn->resctl = resctl;
    querpn->fieres = NULL;
    return ++querpn;
}

static plan_node_enco *final_sconq_plan_enco(plan_node_enco *querpn, stati_scont *scont) {
    querpn->acti_oper = FINAL_QUDRY_ACCO;
    strcpy(querpn->cont_name, scont->cont_name);
    //
    ++scont;
    ++querpn;
    querpn->acti_oper = FINAL_QUDRY_ACCO;
    strcpy(querpn->cont_name, scont->cont_name);
    //
    return ++querpn;
}

//

int creat_sconq_plan_enco(plan_node_enco *firspn, respo_ctrl *resctl, contain *dcont, stati_scont *scont, oper_node *synt_head) {
    plan_node_enco *quer_tok;
    OSEVPF("[FUNC]:initi_sconq_plan_enco\n");
    if (!(quer_tok = initi_sconq_plan_enco(firspn, resctl, dcont)))
        return -1;
    OSEVPF("open_curso_enco\n");
    if (!(quer_tok = open_curso_rsco(quer_tok, scont)))
        return -1;
    if (!(quer_tok = synt_plan_rsco(quer_tok, synt_head, scont)))
        return -1;
    OSEVPF("set_initi_valu_ensi\n");
    set_initi_valu_enco(firspn, quer_tok - 0x01);
    OSEVPF("close_curso_enco\n");
    if (!(quer_tok = close_curso_rsco(quer_tok, scont)))
        return -1;
    OSEVPF("final_sconq_plan_enco\n");
    if (!(quer_tok = final_sconq_plan_enco(quer_tok, scont)))
        return -1;
    quer_tok->acti_oper = INVA_ACCO;
    //
    return 0x00;
}

//

static plan_node_enco *initi_slv2q_plan_enco(plan_node_enco *querpn, respo_ctrl *resctl) {
    querpn->acti_oper = INIT_QUERY_ACCO;
    querpn->resctl = resctl;
    querpn->fieres = NULL;
    return ++querpn;
}

static plan_node_enco *final_slv2q_plan_enco(plan_node_enco *querpn, contain **sconp) {
    querpn->acti_oper = FINAL_QUDRY_ACCO;
    strcpy(querpn->cont_name, sconp[0x00]->cont_name);
    // querpn->source_str
    // querpn->fieres = NULL;
    //
    ++sconp;
    ++querpn;
    querpn->acti_oper = FINAL_QUDRY_ACCO;
    strcpy(querpn->cont_name, sconp[0x00]->cont_name);
    // querpn->source_str
    // querpn->fieres = NULL;
    //
    return ++querpn;
}

//

int creat_slv2q_plan_enco(plan_node_enco *firspn, respo_ctrl *resctl, contain **sconp, oper_node *synt_head) {
    plan_node_enco *quer_tok;
    OSEVPF("[FUNC]:initi_slv2q_plan_enco\n");
    if (!(quer_tok = initi_slv2q_plan_enco(firspn, resctl)))
        return -1;
    OSEVPF("open_curso_enco\n");
    if (!(quer_tok = open_curso_enco(quer_tok, sconp)))
        return -1;
    if (!(quer_tok = synt_plan_enco(quer_tok, synt_head, sconp)))
        return -1;
    OSEVPF("set_initi_valu_ensi\n");
    set_initi_valu_enco(firspn, quer_tok - 0x01);
    OSEVPF("close_curso_enco\n");
    if (!(quer_tok = close_curso_enco(quer_tok, sconp)))
        return -1;
    OSEVPF("final_slv2q_plan_enco\n");
    if (!(quer_tok = final_slv2q_plan_enco(quer_tok, sconp)))
        return -1;
    quer_tok->acti_oper = INVA_ACCO;
    //
    return 0x00;
}


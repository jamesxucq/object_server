
#include "commo_header.h"
#include "kcomm_header.h"
#include "lexic/valtok.h"
#include "gramm/synta_tree.h"
#include "plan_node_ensi.h"
#include "plan_node_enco.h"

#include "searo_plan_ensi.h"

//

static plan_node_ensi *initi_searo_plan_resi(plan_node_ensi *querpn, respo_ctrl *resctl) {
    querpn->acti_oper = INIT_QUERY_ACCO;
    querpn->resctl = resctl;
    return ++querpn;
}

static plan_node_ensi *final_searo_plan_resi(plan_node_ensi *querpn, contain *scont) {
    querpn->acti_oper = FINAL_QUDRY_ACCO;
    strcpy(querpn->cont_name, scont->cont_name);
    //
    return ++querpn;
}

//

int creat_searo_plan_resi(plan_node_ensi *firspn, respo_ctrl *resctl, contain *scont, oper_node *synt_head) {
    plan_node_ensi *quer_tok;
    OSEVPF("[FUNC]:initi_searo_plan_resi\n");
    if (!(quer_tok = initi_searo_plan_resi(firspn, resctl)))
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
    if (!(quer_tok = final_searo_plan_resi(quer_tok, scont)))
        return -1;
    (quer_tok)->acti_oper = INVA_ACCO;
    //
    OSEVPF("creat_searo_plan_resi end.....\n");
    return 0x00;
}

//

static plan_node_enco *initi_searo_plan_reco(plan_node_enco *querpn, respo_ctrl *resctl) {
    querpn->acti_oper = INIT_QUERY_ACCO;
    querpn->resctl = resctl;
    querpn->fieres = NULL;
    return ++querpn;
}

static plan_node_enco *final_searo_plan_reco(plan_node_enco *querpn, contain **sconp) {
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

int creat_searo_plan_reco(plan_node_enco *firspn, respo_ctrl *resctl, contain **scont, oper_node *synt_head) {
    plan_node_enco *quer_tok;
    OSEVPF("[FUNC]:initi_searo_plan_reco\n");
    if (!(quer_tok = initi_searo_plan_reco(firspn, resctl)))
        return -1;
    OSEVPF("open_curso_enco\n");
    if (!(quer_tok = open_curso_enco(quer_tok, scont)))
        return -1;
    OSEVPF("synt_plan_enco\n");
    if (!(quer_tok = synt_plan_enco(quer_tok, synt_head, scont)))
        return -1;
    OSEVPF("set_initi_valu_enco\n");
    set_initi_valu_enco(firspn, quer_tok - 0x01);
    OSEVPF("close_curso_enco\n");
    if (!(quer_tok = close_curso_enco(quer_tok, scont)))
        return -1;
    OSEVPF("final_searo_plan\n");
    if (!(quer_tok = final_searo_plan_reco(quer_tok, scont)))
        return -1;
    (quer_tok)->acti_oper = INVA_ACCO;
    //
    OSEVPF("creat_searo_plan_reco end.....\n");
    return 0x00;
}

//

static plan_node_ensi *initi_refro_plan_rdsi(plan_node_ensi *querpn, contain * dcont) {
    querpn->acti_oper = INIT_QUERY_ACCO;
    strcpy(querpn->cont_name, dcont->cont_name);
    querpn->resctl = NULL;
    return ++querpn;
}

static plan_node_ensi *final_refro_plan_rdsi(plan_node_ensi *querpn, contain *qscont) {
    querpn->acti_oper = FINAL_QUDRY_ACCO;
    strcpy(querpn->cont_name, qscont->cont_name);
    strcpy(querpn->source_str, "xx, ax ,cx");
    //
    return ++querpn;
}

//

int creat_refro_plan_rdsi(plan_node_ensi *firspn, contain *dcont, contain *scont, oper_node *synt_head) {
    plan_node_ensi *quer_tok;
    OSEVPF("[FUNC]:initi_refro_plan_rdsi\n");
    if (!(quer_tok = initi_refro_plan_rdsi(firspn, dcont)))
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
    OSEVPF("final_refro_plan_rdsi\n");
    if (!(quer_tok = final_refro_plan_rdsi(quer_tok, scont)))
        return -1;
    (quer_tok)->acti_oper = INVA_ACCO;
    //
    OSEVPF("creat_searq_plan_ensi end.....\n");
    return 0x00;
}

//

static plan_node_enco *initi_refro_plan_rdco(plan_node_enco *querpn, contain * dcont) {
    querpn->acti_oper = INIT_QUERY_ACCO;
    strcpy(querpn->cont_name, dcont->cont_name);
    querpn->resctl = NULL;
    return ++querpn;
}

static plan_node_enco *final_refro_plan_rdco(plan_node_enco *querpn, contain **qcontp) {
    querpn->acti_oper = FINAL_QUDRY_ACCO;
    strcpy(querpn->cont_name, qcontp[0x00]->cont_name);
    strcpy(querpn->source_str, "xx, ax ,cx");
    //
    return ++querpn;
}

//

int creat_refro_plan_rdco(plan_node_enco *firspn, contain *dcont, contain **sconp, oper_node *synt_head) {
    plan_node_enco *quer_tok;
    OSEVPF("[FUNC]:initi_refro_plan_rdco\n");
    if (!(quer_tok = initi_refro_plan_rdco(firspn, dcont)))
        return -1;
    OSEVPF("open_curso_ensi\n");
    if (!(quer_tok = open_curso_enco(quer_tok, sconp)))
        return -1;
    OSEVPF("synt_plan_ensi\n");
    if (!(quer_tok = synt_plan_enco(quer_tok, synt_head, sconp)))
        return -1;
    OSEVPF("set_initi_valu_ensi\n");
    set_initi_valu_enco(firspn, quer_tok - 0x01);
    OSEVPF("close_curso_ensi\n");
    if (!(quer_tok = close_curso_enco(quer_tok, sconp)))
        return -1;
    OSEVPF("final_refro_plan_rdco\n");
    if (!(quer_tok = final_refro_plan_rdco(quer_tok, sconp)))
        return -1;
    (quer_tok)->acti_oper = INVA_ACCO;
    //
    OSEVPF("creat_searq_plan_ensi end.....\n");
    return 0x00;
}


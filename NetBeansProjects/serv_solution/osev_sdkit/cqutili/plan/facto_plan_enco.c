
#include "commo_header.h"
#include "kcomm_header.h"
#include "lexic/valtok.h"
#include "gramm/synta_tree.h"
#include "plan_node_enco.h"
#include "field_utili.h"

#include "facto_plan_enco.h"

//

static plan_node_enco *initi_fconq_plan_enco(plan_node_enco *querpn, respo_ctrl *resctl, contain *dcont, lv2pme **lv2mep) {
    querpn->acti_oper = INIT_QUERY_ACCO;
    strcpy(querpn->cont_name, dcont->cont_name);
    querpn->resctl = resctl;
    querpn->fieres = CREAT_FIELD_RESUL_ENCO();
    if (!querpn->fieres) return NULL;
    if (fires_lv2pn_item_enco(querpn->fieres, lv2mep)) {
        DELET_FIELD_RESUL_ENCO(querpn->fieres);
        return NULL;
    }
    //
    return ++querpn;
}

static plan_node_enco *final_fconq_plan_enco(plan_node_enco *querpn, contain **sconp) {
    querpn->acti_oper = FINAL_QUDRY_ACCO;
    strcpy(querpn->cont_name, sconp[0x00]->cont_name);
    //
    ++sconp;
    ++querpn;
    querpn->acti_oper = FINAL_QUDRY_ACCO;
    strcpy(querpn->cont_name, sconp[0x00]->cont_name);
    //
    return ++querpn;
}

//

int creat_fconq_plan_enco(plan_node_enco *firspn, respo_ctrl *resctl, contain *dcont, contain **sconp, lv2pme **lv2mep, oper_node *synt_head) {
    plan_node_enco *quer_tok;
    OSEVPF("[FUNC]:initi_fconq_plan_enco\n");
    if (!(quer_tok = initi_fconq_plan_enco(firspn, resctl, dcont, lv2mep)))
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
    OSEVPF("final_fconq_plan_enco\n");
    if (!(quer_tok = final_fconq_plan_enco(quer_tok, sconp)))
        return -1;
    quer_tok->acti_oper = INVA_ACCO;
    //
    return 0x00;
}

//

static plan_node_enco *initi_flv2q_plan_enco(plan_node_enco *querpn, respo_ctrl *resctl, lv2pme **lv2mep) {
    querpn->acti_oper = INIT_QUERY_ACCO;
    querpn->resctl = resctl;
    querpn->fieres = CREAT_FIELD_RESUL_ENCO();
    if (!querpn->fieres) return NULL;
    if (fires_lv2pn_type_enco(querpn->fieres, lv2mep)) {
        DELET_FIELD_RESUL_ENCO(querpn->fieres);
        return NULL;
    }
    //
    return ++querpn;
}

static plan_node_enco *final_flv2q_plan_enco(plan_node_enco *querpn, contain **sconp) {
    querpn->acti_oper = FINAL_QUDRY_ACCO;
    strcpy(querpn->cont_name, sconp[0x00]->cont_name);
    //
    ++sconp;
    ++querpn;
    querpn->acti_oper = FINAL_QUDRY_ACCO;
    strcpy(querpn->cont_name, sconp[0x00]->cont_name);
    //
    return ++querpn;
}

//

int creat_flv2q_plan_enco(plan_node_enco *firspn, respo_ctrl *resctl, contain **sconp, lv2pme **lv2mep, oper_node *synt_head) {
    plan_node_enco *quer_tok;
    OSEVPF("[FUNC]:initi_flv2q_plan_enco\n");
    if (!(quer_tok = initi_flv2q_plan_enco(firspn, resctl, lv2mep)))
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
    OSEVPF("final_flv2q_plan_enco\n");
    if (!(quer_tok = final_flv2q_plan_enco(quer_tok, sconp)))
        return -1;
    quer_tok->acti_oper = INVA_ACCO;
    //
    return 0x00;
}


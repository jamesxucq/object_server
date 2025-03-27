
#include "commo_header.h"
#include "kcomm_header.h"
#include "lexic/valtok.h"
#include "gramm/synta_tree.h"
#include "plan_node_ensi.h"
#include "plan_node_enco.h"
#include "field_utili.h"

#include "searq_plan_reen.h"

//

static plan_node_ensi *initi_slv2q_plan_resi(plan_node_ensi *querpn, respo_ctrl *resctl) {
    querpn->acti_oper = INIT_QUERY_ACCO;
    // strcpy(querpn->cont_name, qcontp->cont_name);
    querpn->resctl = resctl;
    return ++querpn;
}

static plan_node_ensi *final_slv2q_plan_resi(plan_node_ensi *querpn, contain *rcont, contain *scont) {
    querpn->acti_oper = FINAL_QUDRY_ACCO;
    strcpy(querpn->cont_name, rcont->cont_name);
    strcpy(querpn->source_str, "xx, ax ,cx");
    //
    ++querpn;
    querpn->acti_oper = FINAL_QUDRY_ACCO;
    strcpy(querpn->cont_name, scont->cont_name);
    //
    return ++querpn;
}

//

int creat_slv2q_plan_resi(plan_node_ensi *firspn, respo_ctrl *resctl, contain *scont, contain *rcont, oper_node *synt_head) {
    plan_node_ensi *quer_tok;
    OSEVPF("[FUNC]:initi_slv2q_plan_ensi\n");
    if (!(quer_tok = initi_slv2q_plan_resi(firspn, resctl)))
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
    OSEVPF("final_slv2q_plan_ensi\n");
    if (!(quer_tok = final_slv2q_plan_resi(quer_tok, rcont, scont)))
        return -1;
    (quer_tok)->acti_oper = INVA_ACCO;
    //
    OSEVPF("creat_searq_plan_ensi end.....\n");
    return 0x00;
}

//

static plan_node_enco *initi_slv2q_plan_reco(plan_node_enco *querpn, respo_ctrl *resctl, lv2pme **lv2mep) {
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

static plan_node_enco *final_slv2q_plan_reco(plan_node_enco *querpn, contain *scont, contain **rconp) {
    querpn->acti_oper = FINAL_QUDRY_ACCO;
    strcpy(querpn->cont_name, rconp[0x00]->cont_name);
    //
    ++rconp;
    ++querpn;
    querpn->acti_oper = FINAL_QUDRY_ACCO;
    strcpy(querpn->cont_name, rconp[0x00]->cont_name);
    //
    ++querpn;
    querpn->acti_oper = FINAL_QUDRY_ACCO;
    strcpy(querpn->cont_name, scont->cont_name);
    //
    return ++querpn;
}

//

int creat_slv2q_plan_reco(plan_node_enco *firspn, respo_ctrl *resctl, contain *scont, contain **rconp, lv2pme **lv2mep, oper_node *synt_head) {
    plan_node_enco *quer_tok;
    OSEVPF("[FUNC]:initi_slv2q_plan_enco\n");
    if (!(quer_tok = initi_slv2q_plan_reco(firspn, resctl, lv2mep)))
        return -1;
    OSEVPF("open_curso_enco\n");
    if (!(quer_tok = open_curso_enco(quer_tok, rconp)))
        return -1;
    if (!(quer_tok = synt_plan_enco(quer_tok, synt_head, rconp)))
        return -1;
    OSEVPF("set_initi_valu_ensi\n");
    set_initi_valu_enco(firspn, quer_tok - 0x01);
    OSEVPF("close_curso_enco\n");
    if (!(quer_tok = close_curso_enco(quer_tok, rconp)))
        return -1;
    OSEVPF("final_slv2q_plan_enco\n");
    if (!(quer_tok = final_slv2q_plan_reco(quer_tok, scont, rconp)))
        return -1;
    quer_tok->acti_oper = INVA_ACCO;
    //
    return 0x00;
}


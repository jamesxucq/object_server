
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_header.h"
#include "lexic/valtok.h"
#include "gramm/synta_tree.h"
#include "plan_node_ensi.h"
#include "plan_node_enco.h"

#include "gramm/expre_analy.h"
#include "gramm/exptoke.h"

#include "plan_utili.h"

#include "plan_node_ensi.h"
#include "stati_scont.h"

//

plan_node_ensi *CREAT_PLAN_NODE_ENSI(int count) {
    plan_node_ensi *querpn = (plan_node_ensi *) malloc(sizeof (plan_node_ensi) * count);
    if (!querpn) return NULL;
    memset(querpn, '\0', sizeof (plan_node_ensi) * count);
    return querpn;
}

void DESTR_PLAN_NODE_ENSI(plan_node_ensi *querpn) {
    plan_node_ensi *quer_tok = querpn;
    for (; INVA_ACCO != quer_tok->acti_oper; ++quer_tok) {
        if (METHO_SET_ACCO == ACTI_CODE(quer_tok->acti_oper)) {
            if (quer_tok->parm_list) leaf_list_dele(quer_tok->parm_list);
        } else if (OPEN_CONTE_ACCO == ACTI_CODE(quer_tok->acti_oper)) {
            //
        } else if (FINAL_QUDRY_ACCO == ACTI_CODE(quer_tok->acti_oper)) {
            // if (quer_tok->lv2nod) DELE_LVTP_DASI(quer_tok->lv2nod);
        }
    }
    free(querpn);
}

//

plan_node_ensi *open_curso_ensi(plan_node_ensi *querpn, contain *qcontp) {
    querpn->acti_oper = OPEN_CONTE_ACCO;
    strcpy(querpn->cont_name, qcontp->cont_name);
    return ++querpn;
}

plan_node_ensi *close_curso_ensi(plan_node_ensi *querpn, contain *qcontp) {
    querpn->acti_oper = CLOSE_CONTE_ACCO;
    strcpy(querpn->cont_name, qcontp->cont_name);
    return ++querpn;
}

plan_node_ensi *open_curso_rssi(plan_node_ensi *querpn, stati_scont *qscont) {
    querpn->acti_oper = OPEN_CONTE_ACCO;
    strcpy(querpn->cont_name, qscont->cont_name);
    return ++querpn;
}

plan_node_ensi *close_curso_rssi(plan_node_ensi *querpn, stati_scont *qscont) {
    querpn->acti_oper = CLOSE_CONTE_ACCO;
    strcpy(querpn->cont_name, qscont->cont_name);
    return ++querpn;
}

//

static plan_node_ensi *inse_plan_node_ensi(oper_node *synt_node, plan_node_ensi *left_chil, plan_node_ensi *querpn, contain *qcontp) {
    // OSEVPF("--- node, node_type:%u, stri_valu:|%s|\n", synt_node->node_type, synt_node->leno->stri_valu);
    plan_node_ensi *quer_tok = NULL;

    //
    switch (OPER_TYPE(synt_node->node_type)) {
        case OR_TOKE:
            quer_tok = appe_or_node_ensi(querpn, left_chil - 0x01, querpn - 0x01);
            break;
        case AND_TOKE:
            quer_tok = appe_and_node_ensi(querpn, left_chil - 0x01, querpn - 0x01);
            break;
        case NOT_TOKE:
            quer_tok = appe_not_node_ensi(left_chil, left_chil - 0x01);
            break;
        case IS_TOKE:
            break;
        case MATCH_TOKE:
            break;
        case LIKE_KW_TOKE:
            break;
        case BETWEEN_TOKE:
            break;
        case IN_TOKE:
            break;
        case NOT_EQUAL_TOKE:
            quer_tok = appe_noeq_node_ensi(querpn, synt_node->left_chil, synt_node->righ_chil, qcontp->cont_name);
            break;
        case EQUAL_TOKE:
            quer_tok = appe_equa_node_ensi(querpn, synt_node->left_chil, synt_node->righ_chil, qcontp->cont_name);
            break;
        case GREAT_THAN_TOKE:
            quer_tok = appe_grth_node_ensi(querpn, synt_node->left_chil, synt_node->righ_chil, qcontp->cont_name);
            break;
        case LESS_EQUAL_TOKE:
            quer_tok = appe_leeq_node_ensi(querpn, synt_node->left_chil, synt_node->righ_chil, qcontp->cont_name);
            break;
        case LESS_THAN_TOKE:
            quer_tok = appe_leth_node_ensi(querpn, synt_node->left_chil, synt_node->righ_chil, qcontp->cont_name);
            break;
        case GREAT_EQUAL_TOKE:
            quer_tok = appe_greq_node_ensi(querpn, synt_node->left_chil, synt_node->righ_chil, qcontp->cont_name);
            break;
        case ESCAPE_TOKE:
            break;
        case PLUS_TOKE:
            quer_tok = appe_plus_node_ensi(querpn, synt_node->left_chil, synt_node->righ_chil, qcontp->cont_name);
            break;
        case MINUS_TOKE:
            quer_tok = appe_minu_node_ensi(querpn, synt_node->left_chil, synt_node->righ_chil, qcontp->cont_name);
            break;
        default:
            _LOG_WARN("default: node_type");
            return NULL;
    }
    //
    return quer_tok;
}

/*
             |>|
             / \
           |ax||0| 
 *  */

// recurs synta plan single

plan_node_ensi *synt_plan_ensi(plan_node_ensi *querpn, oper_node *synt_node, contain *qcontp) {
    plan_node_ensi *left_chil, *quer_tok;
    // OSEVPF("--- recur_synta, node_type:%u, stri_valu:|%s|\n", synt_node->node_type, synt_node->leno->stri_valu);
    if (!synt_node || ((TERM_TOKE | METH_TOKE) & synt_node->node_type))
        return querpn;
    //
    left_chil = synt_plan_ensi(querpn, synt_node->left_chil, qcontp);
    if (!left_chil) return NULL;
    quer_tok = synt_plan_ensi(left_chil, synt_node->righ_chil, qcontp);
    if (!quer_tok) return NULL;
    //
    return inse_plan_node_ensi(synt_node, left_chil, quer_tok, qcontp);
}

//

static plan_node_ensi *inse_plan_node_ensist(oper_node *synt_node, plan_node_ensi *left_chil, plan_node_ensi *querpn, stati_scont *qscont) {
    // OSEVPF("--- node, node_type:%u, stri_valu:|%s|\n", synt_node->node_type, synt_node->leno->stri_valu);
    plan_node_ensi *quer_tok = NULL;

    //
    switch (OPER_TYPE(synt_node->node_type)) {
        case OR_TOKE:
            quer_tok = appe_or_node_ensi(querpn, left_chil - 0x01, querpn - 0x01);
            break;
        case AND_TOKE:
            quer_tok = appe_and_node_ensi(querpn, left_chil - 0x01, querpn - 0x01);
            break;
        case NOT_TOKE:
            quer_tok = appe_not_node_ensi(left_chil, left_chil - 0x01);
            break;
        case IS_TOKE:
            break;
        case MATCH_TOKE:
            break;
        case LIKE_KW_TOKE:
            break;
        case BETWEEN_TOKE:
            break;
        case IN_TOKE:
            break;
        case NOT_EQUAL_TOKE:
            quer_tok = appe_noeq_node_ensi(querpn, synt_node->left_chil, synt_node->righ_chil, qscont->cont_name);
            break;
        case EQUAL_TOKE:
            quer_tok = appe_equa_node_ensi(querpn, synt_node->left_chil, synt_node->righ_chil, qscont->cont_name);
            break;
        case GREAT_THAN_TOKE:
            quer_tok = appe_grth_node_ensi(querpn, synt_node->left_chil, synt_node->righ_chil, qscont->cont_name);
            break;
        case LESS_EQUAL_TOKE:
            quer_tok = appe_leeq_node_ensi(querpn, synt_node->left_chil, synt_node->righ_chil, qscont->cont_name);
            break;
        case LESS_THAN_TOKE:
            quer_tok = appe_leth_node_ensi(querpn, synt_node->left_chil, synt_node->righ_chil, qscont->cont_name);
            break;
        case GREAT_EQUAL_TOKE:
            quer_tok = appe_greq_node_ensi(querpn, synt_node->left_chil, synt_node->righ_chil, qscont->cont_name);
            break;
        case ESCAPE_TOKE:
            break;
        case PLUS_TOKE:
            quer_tok = appe_plus_node_ensi(querpn, synt_node->left_chil, synt_node->righ_chil, qscont->cont_name);
            break;
        case MINUS_TOKE:
            quer_tok = appe_minu_node_ensi(querpn, synt_node->left_chil, synt_node->righ_chil, qscont->cont_name);
            break;
        default:
            _LOG_WARN("default: node_type");
            return NULL;
    }
    //
    return quer_tok;
}

//

plan_node_ensi *synt_plan_rssi(plan_node_ensi *querpn, oper_node *synt_node, stati_scont *qscont) {
    plan_node_ensi *left_chil, *quer_tok;
    // OSEVPF("--- recur_synta, node_type:%u, stri_valu:|%s|\n", synt_node->node_type, synt_node->leno->stri_valu);
    if (!synt_node || ((TERM_TOKE | METH_TOKE) & synt_node->node_type))
        return querpn;
    //
    left_chil = synt_plan_rssi(querpn, synt_node->left_chil, qscont);
    if (!left_chil) return NULL;
    quer_tok = synt_plan_rssi(left_chil, synt_node->righ_chil, qscont);
    if (!quer_tok) return NULL;
    //
    return inse_plan_node_ensist(synt_node, left_chil, quer_tok, qscont);
}

//

void set_initi_valu_ensi(plan_node_ensi *querpn, plan_node_ensi *plan_head) {
    querpn->resul_node = plan_head;
    plan_head->acti_oper |= PLAN_HEAD_ACCO;
}
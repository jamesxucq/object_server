
#include "commo_header.h"
#include "lexic/valtok.h"
#include "gramm/synta_tree.h"

#include "gramm/expre_analy.h"
#include "gramm/exptoke.h"

#include "adju_synta.h"
#include "prep_sequen.h"
#include "debug_funct_cq.h"

//

static int adju_synt_node(oper_node *synt_node) {
    // OSEVPF("--- node, node_type:%u, stri_valu:|%s|\n", synt_node->node_type, synt_node->leno->stri_valu);
    int int_valu = -1;
    //
    switch (OPER_TYPE(synt_node->node_type)) {
        case OR_TOKE:
        case AND_TOKE:
        case NOT_TOKE:
            break;
        case IS_TOKE:
        case MATCH_TOKE:
        case LIKE_KW_TOKE:
        case BETWEEN_TOKE:
        case IN_TOKE:
            break;
        case NOT_EQUAL_TOKE:
            int_valu = adju_noeq_node(synt_node, synt_node->left_chil, synt_node->righ_chil);
            break;
        case EQUAL_TOKE:
            int_valu = adju_equa_node(synt_node, synt_node->left_chil, synt_node->righ_chil);
            break;
        case GREAT_THAN_TOKE:
            int_valu = adju_grth_node(synt_node, synt_node->left_chil, synt_node->righ_chil);
            break;
        case LESS_EQUAL_TOKE:
            int_valu = adju_leeq_node(synt_node, synt_node->left_chil, synt_node->righ_chil);
            break;
        case LESS_THAN_TOKE:
            int_valu = adju_leth_node(synt_node, synt_node->left_chil, synt_node->righ_chil);
            break;
        case GREAT_EQUAL_TOKE:
            int_valu = adju_greq_node(synt_node, synt_node->left_chil, synt_node->righ_chil);
            break;
        case ESCAPE_TOKE:
            break;
        case PLUS_TOKE:
            int_valu = adju_plus_node(synt_node, synt_node->left_chil, synt_node->righ_chil);
            break;
        case MINUS_TOKE:
            int_valu = adju_minu_node(synt_node, synt_node->left_chil, synt_node->righ_chil);
            break;
        default:
            _LOG_WARN("default: node_type");
            return -1;
    }
    //
    return int_valu;
}

//

static int recu_synta_sequ(oper_node *synt_node) {
    // if (synt_node)PRIN_synt_node(synt_node);
    if (!synt_node || ((TERM_TOKE | METH_TOKE) & synt_node->node_type))
        return 0x00;
    //
    if (recu_synta_sequ(synt_node->left_chil))
        return -1;
    if (recu_synta_sequ(synt_node->righ_chil))
        return -1;
    OSEVPF("adju_synt_node.\n");
    return adju_synt_node(synt_node);
}

//

int adjust_syntax_sequen(oper_node *synt_head) {
    // OSEVPF("[FUNC]:reduce_uplus_uminus.\n");
    if (recu_synta_sequ(synt_head))
        return -1;
    return 0x00;
}
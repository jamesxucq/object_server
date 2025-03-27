#include "stdio.h"

#include "commo_header.h"
#include "lexic/valtok.h"
#include "gramm/synta_tree.h"

#include "gramm/expre_analy.h"
#include "gramm/exptoke.h"

#include "prep_signed.h"
#include "debug_funct_cq.h"

//

static int erase_uplus_c(oper_node *synt_node) {
    // OSEVPF("[FUNC]:erase_uplus.\n");
    oper_node *last_node = synt_node->left_chil;
    //
    synt_node->node_type = TERM_TOKE;
    synt_node->leno = last_node->leno;
    free(last_node);
    //
    return 0x00;
}

static int erase_uminus_c(oper_node *synt_node) {
    // OSEVPF("[FUNC]:erase_uminus.\n");
    oper_node *last_node = synt_node->left_chil;
    //
    synt_node->node_type = TERM_TOKE;
    synt_node->leno = last_node->leno;
    free(last_node);
    //
    leaf_node *leno = synt_node->leno;
    switch (leno->vtok_kind) {
        case TEXT_TOKE:
            return -1;
            break;
        case LOLO_NUMB_TOKE:
            leno->lolo_valu = (-1) * leno->lolo_valu;
            break;
        case ULLO_NUMB_TOKE:
            return -1;
            break;
        case DOUB_NUMB_TOKE:
            leno->doub_valu = (-1) * leno->doub_valu;
            break;
        case ID_TOKE:
            return -1;
            break;
        default:
            _LOG_WARN("default: vtok_kind");
            return -1;
    }
    //
    return 0x00;
}

//

static int dele_cond_sign(oper_node *synt_node) {
    switch (OPER_TYPE(synt_node->node_type)) {
        case UPLUS_TOKE:
            erase_uplus_c(synt_node);
            break;
        case UMINUS_TOKE:
            erase_uminus_c(synt_node);
            break;
        default:
            _LOG_WARN("default: node_type");
            return 0x00;
    }
    //
    return 0x00;
}

//

static int recu_synta_sign(oper_node *synt_node) {
    if (synt_node) PRIN_synt_node(synt_node);
    if (!synt_node || ((TERM_TOKE | METH_TOKE) & synt_node->node_type))
        return 0x00;
    //
    if (recu_synta_sign(synt_node->left_chil))
        return -1;
    if (recu_synta_sign(synt_node->righ_chil))
        return -1;
    OSEVPF("dele_cond_sign.\n");
    return dele_cond_sign(synt_node);
}

int reduce_uplus_uminus(oper_node *synt_head) {
    // OSEVPF("[FUNC]:reduce_uplus_uminus.\n");
    if (recu_synta_sign(synt_head))
        return -1;
    return 0x00;
}
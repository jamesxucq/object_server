#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "synta_tree.h"
#include "gramm_analy.h"
#include "lexic/valtok.h"
#include "expre_analy.h"
#include "exptoke.h"
#include "debug_funct_cq.h"

//

static int erase_uplus_p(leaf_node *leno) {
    // OSEVPF("--- erase_uplus_p.\n");
    return 0x00;
}

static int erase_uminus_p(leaf_node *leno) {
    // OSEVPF("--- erase_uminus_p. leno->vtok_kind:%u, leno->stri_valu:|%s|\n", leno->vtok_kind, leno->stri_valu);
    switch (leno->vtok_kind) {
        case TEXT_TOKE:
            return -1;
            break;
        case LOLO_NUMB_TOKE:
            // OSEVPF("1 --- leno->lolo_valu:|%lld|\n", leno->lolo_valu);
            leno->lolo_valu = (-1) * leno->lolo_valu;
            // OSEVPF("2 --- leno->lolo_valu:|%lld|\n", leno->lolo_valu);
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

static int dele_pamvu_sign(leaf_node *leno, uint sinum) {
    // OSEVPF("--- dele_pamvu_sign\n");
    switch (sinum) {
        case UPLUS_TOKE:
            erase_uplus_p(leno);
            break;
        case UMINUS_TOKE:
            erase_uminus_p(leno);
            break;
        default:
            _LOG_WARN("default: sinum");
            return 0x00;
    }
    //
    return 0x00;
}

//

leaf_node *new_leaf_vato(valu_toke *valtok) {
    // PRIN_leaf_vato(valtok);
    leaf_node *leno = (leaf_node *) malloc(sizeof (leaf_node));
    if (!leno) return NULL;
    memcpy(leno, valtok, sizeof (leaf_node));
    //
    return leno;
}

//

leaf_list *new_leaf_list(valu_toke *valtok) {
    // OSEVPF("--- new_leaf_list\n");
    leaf_list *leli = (leaf_list *) malloc(sizeof (leaf_list));
    if (!leli) return NULL;
    leli->next = NULL;
    //
    leli->leno = (leaf_node *) malloc(sizeof (leaf_node));
    if (!leli->leno) {
        free(leli);
        return NULL;
    }
    memcpy(leli->leno, valtok, sizeof (leaf_node));
    //
    return leli;
}

leaf_list *new_leaf_sign(uint sinum, valu_toke *valtok) {
    // OSEVPF("--- new_leaf_sign\n");
    leaf_list *leli = (leaf_list *) malloc(sizeof (leaf_list));
    if (!leli) return NULL;
    leli->next = NULL;
    //
    leli->leno = (leaf_node *) malloc(sizeof (leaf_node));
    if (!leli->leno) {
        free(leli);
        return NULL;
    }
    memcpy(leli->leno, valtok, sizeof (leaf_node));
    dele_pamvu_sign(leli->leno, sinum);
    //
    return leli;
}

//

leaf_list *appe_leaf_vato(leaf_list *leli, valu_toke *valtok) {
    // OSEVPF("--- appe_leaf_vato\n");
    leaf_list *lels = leli;
    for (; lels->next; lels = lels->next);
    //
    lels->next = (leaf_list *) malloc(sizeof (leaf_list));
    if (!lels->next) return NULL;
    lels = lels->next;
    lels->next = NULL;
    //
    lels->leno = (leaf_node *) malloc(sizeof (leaf_node));
    if (!lels->leno) {
        free(lels);
        return NULL;
    }
    memcpy(lels->leno, valtok, sizeof (leaf_node));
    //
    return leli;
}

leaf_list *appe_leaf_vats(leaf_list *leli, uint sinum, valu_toke *valtok) {
    // OSEVPF("--- appe_leaf_vats\n");
    leaf_list *lels = leli;
    for (; lels->next; lels = lels->next);
    //
    lels->next = (leaf_list *) malloc(sizeof (leaf_list));
    if (!lels->next) return NULL;
    lels = lels->next;
    lels->next = NULL;
    //
    lels->leno = (leaf_node *) malloc(sizeof (leaf_node));
    if (!lels->leno) {
        free(lels);
        return NULL;
    }
    memcpy(lels->leno, valtok, sizeof (leaf_node));
    dele_pamvu_sign(lels->leno, sinum);
    //
    return leli;
}

leaf_list *appe_leaf_type(leaf_list *leli, valu_toke *valtok) {
    // OSEVPF("--- appe_leaf_type\n");
    leaf_list *lels = leli;
    for (; lels->next; lels = lels->next);
    //
    strcat(lels->leno->stri_valu, valtok->stri_valu);
    free(valtok);
    //
    return leli;
}

//

oper_node *new_oper_leaf(uint opnum, leaf_node *leno) {
    // OSEVPF("--- new_oper_leaf\n");
    oper_node *opno = (oper_node *) malloc(sizeof (oper_node));
    if (!opno) return NULL;
    memset(opno, '\0', sizeof (oper_node));
    opno->node_type = opnum;
    opno->leno = leno;
    //
    return opno;
}

//

oper_node *new_oper_node(pastat *state, uint opnum, oper_node *leno, oper_node *riod) {
    // OSEVPF("--- new_oper_node, opnum:%u, leno->node_type:%08x, riod->node_type:%08x\n", opnum, leno->node_type, riod->node_type);
    oper_node *opno = (oper_node *) malloc(sizeof (oper_node));
    if (!opno) return NULL;
    memset(opno, '\0', sizeof (oper_node));
    opno->node_type = opnum;
    opno->left_chil = leno;
    opno->righ_chil = riod;
    //
    state->synt_head = opno;
    // OSEVPF("--- node_type:%u\n", state->synt_head->node_type);
    // OSEVPF("--- opno:%016X leno:%016X riod:%016X\n", opno, leno, riod);
    return opno;
}

oper_list *new_oper_list(oper_list *olist, oper_node *opno) {
    // OSEVPF("--- new_oper_list\n");
    oper_list *list_temp = (oper_list *) malloc(sizeof (oper_list));
    if (!list_temp) return NULL;
    memset(list_temp, '\0', sizeof (oper_list));
    if (olist) list_temp->next = olist;
    //
    list_temp->opno = opno;
    return list_temp;
}

//

static inline void dele_meta(oper_node *ople_node) {
    // OSEVPF("--- dele_meta\n");
    if (TERM_TOKE & ople_node->node_type) {
        free(ople_node->leno);
    } else if (METH_TOKE & ople_node->node_type) {
        free(ople_node->leno);
        if (ople_node->lealst) leaf_list_dele(ople_node->lealst);
    }
}

void recu_dele(oper_node *ople_node) {
    // OSEVPF("--- recu_dele\n");
    if (!((METH_TOKE | TERM_TOKE) & ople_node->node_type)) {
        if (ople_node->left_chil) recu_dele(ople_node->left_chil);
        if (ople_node->righ_chil) recu_dele(ople_node->righ_chil);
    }
    // OSEVPF("--- ople_node->node_type:%08X\n", ople_node->node_type);
    dele_meta(ople_node);
    free(ople_node);
}

//

oper_node *expr_add_collate(pastat *state, uint opnum, leaf_node *leno, oper_node *riod) {
    // OSEVPF("--- expr_add_collate\n");
    oper_node *opno = (oper_node *) malloc(sizeof (oper_node));
    if (!opno) return NULL;
    //
    return opno;
}

//

oper_node *expr_function(valu_toke *valtok, leaf_list *leli) {
    // OSEVPF("--- expr_function, valtok->stri_valu:|%s|\n", valtok->stri_valu);
    leaf_node *leno = (leaf_node *) malloc(sizeof (leaf_node));
    if (!leno) return NULL;
    memcpy(leno, valtok, sizeof (leaf_node));
    //
    oper_node *opno = (oper_node *) malloc(sizeof (oper_node));
    if (!opno) {
        free(leno);
        return NULL;
    }
    opno->node_type = METH_TOKE;
    opno->leno = leno;
    opno->lealst = leli;
    //
    return opno;
}

oper_node *binary_unary_null(pastat *state, oper_node *leno, oper_node *riod, uint opnum) {
    // OSEVPF("--- binary_unary_null\n");
    oper_node *opno = (oper_node *) malloc(sizeof (oper_node));
    if (!opno) return NULL;
    //
    return opno;
}
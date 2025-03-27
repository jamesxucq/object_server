
#include "commo_header.h"
#include "lexic/valtok.h"
#include "gramm/synta_tree.h"

#include "gramm/expre_analy.h"
#include "gramm/exptoke.h"

#include "adju_synta.h"

//

int adju_noeq_node(oper_node *syno, oper_node *leno, oper_node *rino) {
    if ((ID_TOKE == leno->leno->vtok_kind) || (METH_TOKE & leno->node_type))
        return 0x00;
    if ((ID_TOKE == rino->leno->vtok_kind) || (METH_TOKE & rino->node_type)) {
        syno->left_chil = syno->righ_chil;
        syno->righ_chil = leno;
    }
    return 0x00;
}

int adju_equa_node(oper_node *syno, oper_node *leno, oper_node *rino) {
    if ((ID_TOKE == leno->leno->vtok_kind) || (METH_TOKE & leno->node_type))
        return 0x00;
    if ((ID_TOKE == rino->leno->vtok_kind) || (METH_TOKE & rino->node_type)) {
        syno->left_chil = syno->righ_chil;
        syno->righ_chil = leno;
    }
    return 0x00;
}

int adju_grth_node(oper_node *syno, oper_node *leno, oper_node *rino) {
    if ((ID_TOKE == leno->leno->vtok_kind) || (METH_TOKE & leno->node_type))
        return 0x00;
    if ((ID_TOKE == rino->leno->vtok_kind) || (METH_TOKE & rino->node_type)) {
        syno->node_type = LESS_THAN_TOKE;
        syno->left_chil = syno->righ_chil;
        syno->righ_chil = leno;
    }
    return 0x00;
}

int adju_leeq_node(oper_node *syno, oper_node *leno, oper_node *rino) {
    if ((ID_TOKE == leno->leno->vtok_kind) || (METH_TOKE & leno->node_type))
        return 0x00;
    if ((ID_TOKE == rino->leno->vtok_kind) || (METH_TOKE & rino->node_type)) {
        syno->node_type = GREAT_EQUAL_TOKE;
        syno->left_chil = syno->righ_chil;
        syno->righ_chil = leno;
    }
    return 0x00;
}

int adju_leth_node(oper_node *syno, oper_node *leno, oper_node *rino) {
    if ((ID_TOKE == leno->leno->vtok_kind) || (METH_TOKE & leno->node_type))
        return 0x00;
    if ((ID_TOKE == rino->leno->vtok_kind) || (METH_TOKE & rino->node_type)) {
        syno->node_type = GREAT_THAN_TOKE;
        syno->left_chil = syno->righ_chil;
        syno->righ_chil = leno;
    }
    return 0x00;
}

int adju_greq_node(oper_node *syno, oper_node *leno, oper_node *rino) {
    if ((ID_TOKE == leno->leno->vtok_kind) || (METH_TOKE & leno->node_type))
        return 0x00;
    if ((ID_TOKE == rino->leno->vtok_kind) || (METH_TOKE & rino->node_type)) {
        syno->node_type = LESS_EQUAL_TOKE;
        syno->left_chil = syno->righ_chil;
        syno->righ_chil = leno;
    }
    return 0x00;
}

int adju_plus_node(oper_node *syno, oper_node *leno, oper_node *rino) {
    if ((ID_TOKE == leno->leno->vtok_kind) || (METH_TOKE & leno->node_type))
        return 0x00;
    if ((ID_TOKE == rino->leno->vtok_kind) || (METH_TOKE & rino->node_type)) {
        syno->left_chil = syno->righ_chil;
        syno->righ_chil = leno;
    }
    return 0x00;
}

int adju_minu_node(oper_node *syno, oper_node *leno, oper_node *rino) {
    return 0x00;
}

#include "commo_header.h"
#include "kcomm_header.h"
#include "lexic/valtok.h"
#include "gramm/synta_tree.h"
#include "plan_node_ensi.h"
#include "plan_node_enco.h"

#include "gramm/expre_analy.h"
#include "gramm/exptoke.h"

#include "plan_utili.h"

//

plan_node_ensi *appe_noeq_node_ensi(plan_node_ensi *querpn, oper_node *leno, oper_node *rino, char *qcont) {
    if (METH_TOKE & leno->node_type) {
        querpn->acti_oper = METHO_SET_ACCO | NOT_EQUAL_OPCO;
        GET_LEAF_LIST(querpn->parm_list, leno->lealst);
    } else querpn->acti_oper = RESUL_SET_ACCO | NOT_EQUAL_OPCO;
    //
    strcpy(querpn->source_str, leno->leno->stri_valu);
    plan_node_ensi *quer_tok = querpn;
    switch (rino->leno->vtok_kind) {
        case TEXT_TOKE:
            strcpy(quer_tok->stri_valu, rino->leno->stri_valu);
            quer_tok->acti_oper |= TEXT_VALU;
            break;
        case LOLO_NUMB_TOKE:
            quer_tok->lolo_valu = rino->leno->lolo_valu;
            quer_tok->acti_oper |= LOLO_NUMB_VALU;
            break;
        case ULLO_NUMB_TOKE:
            quer_tok->ullo_valu = rino->leno->ullo_valu;
            quer_tok->acti_oper |= ULLO_NUMB_VALU;
            break;
        case DOUB_NUMB_TOKE:
            quer_tok->doub_valu = rino->leno->doub_valu;
            quer_tok->acti_oper |= DOUB_NUMB_VALU;
            break;
        case ID_TOKE:
            strcpy(quer_tok->stri_valu, rino->leno->stri_valu);
            quer_tok->acti_oper |= ID_VALU;
            break;
        default:
            _LOG_WARN("default: vtok_kind");
            return NULL;
    }
    //
    strcpy(querpn->cont_name, qcont);
    querpn->resul_set = NULL;
    return ++quer_tok;
}

plan_node_ensi *appe_equa_node_ensi(plan_node_ensi *querpn, oper_node *leno, oper_node *rino, char *qcont) {
    if (METH_TOKE & leno->node_type) {
        querpn->acti_oper = METHO_SET_ACCO | EQUAL_OPCO;
        GET_LEAF_LIST(querpn->parm_list, leno->lealst);
    } else querpn->acti_oper = RESUL_SET_ACCO | EQUAL_OPCO;
    //
    strcpy(querpn->source_str, leno->leno->stri_valu);
    plan_node_ensi *quer_tok = querpn;
    switch (rino->leno->vtok_kind) {
        case TEXT_TOKE:
            strcpy(quer_tok->stri_valu, rino->leno->stri_valu);
            quer_tok->acti_oper |= TEXT_VALU;
            break;
        case LOLO_NUMB_TOKE:
            quer_tok->lolo_valu = rino->leno->lolo_valu;
            quer_tok->acti_oper |= LOLO_NUMB_VALU;
            break;
        case ULLO_NUMB_TOKE:
            quer_tok->ullo_valu = rino->leno->ullo_valu;
            quer_tok->acti_oper |= ULLO_NUMB_VALU;
            break;
        case DOUB_NUMB_TOKE:
            quer_tok->doub_valu = rino->leno->doub_valu;
            quer_tok->acti_oper |= DOUB_NUMB_VALU;
            break;
        case ID_TOKE:
            strcpy(quer_tok->stri_valu, rino->leno->stri_valu);
            quer_tok->acti_oper |= ID_VALU;
            break;
        default:
            _LOG_WARN("default: vtok_kind");
            return NULL;
    }
    //
    strcpy(querpn->cont_name, qcont);
    querpn->resul_set = NULL;
    return ++quer_tok;
}

plan_node_ensi *appe_grth_node_ensi(plan_node_ensi *querpn, oper_node *leno, oper_node *rino, char *qcont) {
    if (METH_TOKE & leno->node_type) {
        querpn->acti_oper = METHO_SET_ACCO | GREAT_THAN_OPCO;
        GET_LEAF_LIST(querpn->parm_list, leno->lealst);
    } else querpn->acti_oper = RESUL_SET_ACCO | GREAT_THAN_OPCO;
    //
    strcpy(querpn->source_str, leno->leno->stri_valu);
    plan_node_ensi *quer_tok = querpn;
    switch (rino->leno->vtok_kind) {
        case TEXT_TOKE:
            strcpy(quer_tok->stri_valu, rino->leno->stri_valu);
            quer_tok->acti_oper |= TEXT_VALU;
            break;
        case LOLO_NUMB_TOKE:
            quer_tok->lolo_valu = rino->leno->lolo_valu;
            quer_tok->acti_oper |= LOLO_NUMB_VALU;
            break;
        case ULLO_NUMB_TOKE:
            quer_tok->ullo_valu = rino->leno->ullo_valu;
            quer_tok->acti_oper |= ULLO_NUMB_VALU;
            break;
        case DOUB_NUMB_TOKE:
            quer_tok->doub_valu = rino->leno->doub_valu;
            quer_tok->acti_oper |= DOUB_NUMB_VALU;
            break;
        case ID_TOKE:
            strcpy(quer_tok->stri_valu, rino->leno->stri_valu);
            quer_tok->acti_oper |= ID_VALU;
            break;
        default:
            _LOG_WARN("default: vtok_kind");
            return NULL;
    }
    //
    strcpy(querpn->cont_name, qcont);
    querpn->resul_set = NULL;
    return ++quer_tok;
}

plan_node_ensi *appe_leeq_node_ensi(plan_node_ensi *querpn, oper_node *leno, oper_node *rino, char *qcont) {
    if (METH_TOKE & leno->node_type) {
        querpn->acti_oper = METHO_SET_ACCO | LESS_EQUAL_OPCO;
        GET_LEAF_LIST(querpn->parm_list, leno->lealst);
    } else querpn->acti_oper = RESUL_SET_ACCO | LESS_EQUAL_OPCO;
    //
    strcpy(querpn->source_str, leno->leno->stri_valu);
    plan_node_ensi *quer_tok = querpn;
    switch (rino->leno->vtok_kind) {
        case TEXT_TOKE:
            strcpy(quer_tok->stri_valu, rino->leno->stri_valu);
            quer_tok->acti_oper |= TEXT_VALU;
            break;
        case LOLO_NUMB_TOKE:
            quer_tok->lolo_valu = rino->leno->lolo_valu;
            quer_tok->acti_oper |= LOLO_NUMB_VALU;
            break;
        case ULLO_NUMB_TOKE:
            quer_tok->ullo_valu = rino->leno->ullo_valu;
            quer_tok->acti_oper |= ULLO_NUMB_VALU;
            break;
        case DOUB_NUMB_TOKE:
            quer_tok->doub_valu = rino->leno->doub_valu;
            quer_tok->acti_oper |= DOUB_NUMB_VALU;
            break;
        case ID_TOKE:
            strcpy(quer_tok->stri_valu, rino->leno->stri_valu);
            quer_tok->acti_oper |= ID_VALU;
            break;
        default:
            _LOG_WARN("default: vtok_kind");
            return NULL;
    }
    //
    strcpy(querpn->cont_name, qcont);
    querpn->resul_set = NULL;
    return ++quer_tok;
}

plan_node_ensi *appe_leth_node_ensi(plan_node_ensi *querpn, oper_node *leno, oper_node *rino, char *qcont) {
    if (METH_TOKE & leno->node_type) {
        querpn->acti_oper = METHO_SET_ACCO | LESS_THAN_OPCO;
        GET_LEAF_LIST(querpn->parm_list, leno->lealst);
    } else querpn->acti_oper = RESUL_SET_ACCO | LESS_THAN_OPCO;
    //
    strcpy(querpn->source_str, leno->leno->stri_valu);
    plan_node_ensi *quer_tok = querpn;
    switch (rino->leno->vtok_kind) {
        case TEXT_TOKE:
            strcpy(quer_tok->stri_valu, rino->leno->stri_valu);
            quer_tok->acti_oper |= TEXT_VALU;
            break;
        case LOLO_NUMB_TOKE:
            quer_tok->lolo_valu = rino->leno->lolo_valu;
            quer_tok->acti_oper |= LOLO_NUMB_VALU;
            break;
        case ULLO_NUMB_TOKE:
            quer_tok->ullo_valu = rino->leno->ullo_valu;
            quer_tok->acti_oper |= ULLO_NUMB_VALU;
            break;
        case DOUB_NUMB_TOKE:
            quer_tok->doub_valu = rino->leno->doub_valu;
            quer_tok->acti_oper |= DOUB_NUMB_VALU;
            break;
        case ID_TOKE:
            strcpy(quer_tok->stri_valu, rino->leno->stri_valu);
            quer_tok->acti_oper |= ID_VALU;
            break;
        default:
            _LOG_WARN("default: vtok_kind");
            return NULL;
    }
    //
    strcpy(querpn->cont_name, qcont);
    querpn->resul_set = NULL;
    return ++quer_tok;
}

plan_node_ensi *appe_greq_node_ensi(plan_node_ensi *querpn, oper_node *leno, oper_node *rino, char *qcont) {
    if (METH_TOKE & leno->node_type) {
        querpn->acti_oper = METHO_SET_ACCO | GREAT_EQUAL_OPCO;
        GET_LEAF_LIST(querpn->parm_list, leno->lealst);
    } else querpn->acti_oper = RESUL_SET_ACCO | GREAT_EQUAL_OPCO;
    //
    strcpy(querpn->source_str, leno->leno->stri_valu);
    plan_node_ensi *quer_tok = querpn;
    switch (rino->leno->vtok_kind) {
        case TEXT_TOKE:
            strcpy(quer_tok->stri_valu, rino->leno->stri_valu);
            quer_tok->acti_oper |= TEXT_VALU;
            break;
        case LOLO_NUMB_TOKE:
            quer_tok->lolo_valu = rino->leno->lolo_valu;
            quer_tok->acti_oper |= LOLO_NUMB_VALU;
            break;
        case ULLO_NUMB_TOKE:
            quer_tok->ullo_valu = rino->leno->ullo_valu;
            quer_tok->acti_oper |= ULLO_NUMB_VALU;
            break;
        case DOUB_NUMB_TOKE:
            quer_tok->doub_valu = rino->leno->doub_valu;
            quer_tok->acti_oper |= DOUB_NUMB_VALU;
            break;
        case ID_TOKE:
            strcpy(quer_tok->stri_valu, rino->leno->stri_valu);
            quer_tok->acti_oper |= ID_VALU;
            break;
        default:
            _LOG_WARN("default: vtok_kind");
            return NULL;
    }
    //
    strcpy(querpn->cont_name, qcont);
    querpn->resul_set = NULL;
    return ++quer_tok;
}

plan_node_ensi *appe_plus_node_ensi(plan_node_ensi *querpn, oper_node *leno, oper_node *rino, char *qcont) {
    if (METH_TOKE & leno->node_type) {
        querpn->acti_oper = METHO_SET_ACCO | PLUS_OPCO;
        GET_LEAF_LIST(querpn->parm_list, leno->lealst);
    } else querpn->acti_oper = RESUL_SET_ACCO | PLUS_OPCO;
    //
    strcpy(querpn->source_str, leno->leno->stri_valu);
    plan_node_ensi *quer_tok = querpn;
    switch (rino->leno->vtok_kind) {
        case LOLO_NUMB_TOKE:
            quer_tok->lolo_valu = rino->leno->lolo_valu;
            quer_tok->acti_oper |= LOLO_NUMB_VALU;
            break;
        case ULLO_NUMB_TOKE:
            quer_tok->ullo_valu = rino->leno->ullo_valu;
            quer_tok->acti_oper |= ULLO_NUMB_VALU;
            break;
        case DOUB_NUMB_TOKE:
            quer_tok->doub_valu = rino->leno->doub_valu;
            quer_tok->acti_oper |= DOUB_NUMB_VALU;
            break;
        case ID_TOKE:
            strcpy(quer_tok->stri_valu, rino->leno->stri_valu);
            quer_tok->acti_oper |= ID_VALU;
            break;
        case TEXT_TOKE:
        default:
            _LOG_WARN("default: vtok_kind");
            return NULL;
    }
    //
    strcpy(querpn->cont_name, qcont);
    querpn->resul_set = NULL;
    return ++quer_tok;
}

plan_node_ensi *appe_minu_node_ensi(plan_node_ensi *querpn, oper_node *leno, oper_node *rino, char *qcont) {
    if (METH_TOKE & leno->node_type) {
        querpn->acti_oper = METHO_SET_ACCO | MINUS_OPCO;
        GET_LEAF_LIST(querpn->parm_list, leno->lealst);
    } else querpn->acti_oper = RESUL_SET_ACCO | MINUS_OPCO;
    //
    strcpy(querpn->source_str, leno->leno->stri_valu);
    plan_node_ensi *quer_tok = querpn;
    switch (rino->leno->vtok_kind) {
        case LOLO_NUMB_TOKE:
            quer_tok->lolo_valu = rino->leno->lolo_valu;
            quer_tok->acti_oper |= LOLO_NUMB_VALU;
            break;
        case ULLO_NUMB_TOKE:
            quer_tok->ullo_valu = rino->leno->ullo_valu;
            quer_tok->acti_oper |= ULLO_NUMB_VALU;
            break;
        case DOUB_NUMB_TOKE:
            quer_tok->doub_valu = rino->leno->doub_valu;
            quer_tok->acti_oper |= DOUB_NUMB_VALU;
            break;
        case ID_TOKE:
            strcpy(quer_tok->stri_valu, rino->leno->stri_valu);
            quer_tok->acti_oper |= ID_VALU;
            break;
        case TEXT_TOKE:
        default:
            _LOG_WARN("default: vtok_kind");
            return NULL;
    }
    //
    strcpy(querpn->cont_name, qcont);
    querpn->resul_set = NULL;
    return ++quer_tok;
}

//

plan_node_ensi *appe_or_node_ensi(plan_node_ensi *querpn, plan_node_ensi *left_chil, plan_node_ensi *rich_chil) {
    OSEVPF("[FUNC]:appe_or_node_ensi\n");
    querpn->acti_oper = OPERA_SET_ACCO | OR_OPCO;
    querpn->left_chil = left_chil;
    querpn->righ_chil = rich_chil;
    querpn->resul_set = NULL;
    return ++querpn;
}

plan_node_ensi *appe_and_node_ensi(plan_node_ensi *querpn, plan_node_ensi *left_chil, plan_node_ensi *rich_chil) {
    OSEVPF("[FUNC]:appe_and_node_ensi\n");
    querpn->acti_oper = OPERA_SET_ACCO | AND_OPCO;
    querpn->left_chil = left_chil;
    querpn->righ_chil = rich_chil;
    querpn->resul_set = NULL;
    return ++querpn;
}

plan_node_ensi *appe_not_node_ensi(plan_node_ensi *querpn, plan_node_ensi *left_chil) {
    OSEVPF("[FUNC]:appe_not_node_ensi\n");
    querpn->acti_oper = OPERA_SET_ACCO | NOT_OPCO;
    querpn->left_chil = left_chil;
    querpn->resul_set = NULL;
    return ++querpn;
}

/////////////////////

plan_node_enco *appe_noeq_node_enco(plan_node_enco *querpn, oper_node *leno, oper_node *rino, char *qcont) {
    if (METH_TOKE & leno->node_type) {
        querpn->acti_oper = METHO_SET_ACCO | NOT_EQUAL_OPCO;
        GET_LEAF_LIST(querpn->parm_list, leno->lealst);
    } else querpn->acti_oper = RESUL_SET_ACCO | NOT_EQUAL_OPCO;
    //
    strcpy(querpn->source_str, leno->leno->stri_valu);
    plan_node_enco *quer_tok = querpn;
    switch (rino->leno->vtok_kind) {
        case TEXT_TOKE:
            strcpy(quer_tok->stri_valu, rino->leno->stri_valu);
            quer_tok->acti_oper |= TEXT_VALU;
            break;
        case LOLO_NUMB_TOKE:
            quer_tok->lolo_valu = rino->leno->lolo_valu;
            quer_tok->acti_oper |= LOLO_NUMB_VALU;
            break;
        case ULLO_NUMB_TOKE:
            quer_tok->ullo_valu = rino->leno->ullo_valu;
            quer_tok->acti_oper |= ULLO_NUMB_VALU;
            break;
        case DOUB_NUMB_TOKE:
            quer_tok->doub_valu = rino->leno->doub_valu;
            quer_tok->acti_oper |= DOUB_NUMB_VALU;
            break;
        case ID_TOKE:
            strcpy(quer_tok->stri_valu, rino->leno->stri_valu);
            quer_tok->acti_oper |= ID_VALU;
            break;
        default:
            _LOG_WARN("default: vtok_kind");
            return NULL;
    }
    //
    strcpy(querpn->cont_name, qcont);
    querpn->resul_set = NULL;
    return ++quer_tok;
}

plan_node_enco *appe_equa_node_enco(plan_node_enco *querpn, oper_node *leno, oper_node *rino, char *qcont) {
    if (METH_TOKE & leno->node_type) {
        querpn->acti_oper = METHO_SET_ACCO | EQUAL_OPCO;
        GET_LEAF_LIST(querpn->parm_list, leno->lealst);
    } else querpn->acti_oper = RESUL_SET_ACCO | EQUAL_OPCO;
    //
    strcpy(querpn->source_str, leno->leno->stri_valu);
    plan_node_enco *quer_tok = querpn;
    switch (rino->leno->vtok_kind) {
        case TEXT_TOKE:
            strcpy(quer_tok->stri_valu, rino->leno->stri_valu);
            quer_tok->acti_oper |= TEXT_VALU;
            break;
        case LOLO_NUMB_TOKE:
            quer_tok->lolo_valu = rino->leno->lolo_valu;
            quer_tok->acti_oper |= LOLO_NUMB_VALU;
            break;
        case ULLO_NUMB_TOKE:
            quer_tok->ullo_valu = rino->leno->ullo_valu;
            quer_tok->acti_oper |= ULLO_NUMB_VALU;
            break;
        case DOUB_NUMB_TOKE:
            quer_tok->doub_valu = rino->leno->doub_valu;
            quer_tok->acti_oper |= DOUB_NUMB_VALU;
            break;
        case ID_TOKE:
            strcpy(quer_tok->stri_valu, rino->leno->stri_valu);
            quer_tok->acti_oper |= ID_VALU;
            break;
        default:
            _LOG_WARN("default: vtok_kind");
            return NULL;
    }
    //
    strcpy(querpn->cont_name, qcont);
    querpn->resul_set = NULL;
    return ++quer_tok;
}

plan_node_enco *appe_grth_node_enco(plan_node_enco *querpn, oper_node *leno, oper_node *rino, char *qcont) {
    if (METH_TOKE & leno->node_type) {
        querpn->acti_oper = METHO_SET_ACCO | GREAT_THAN_OPCO;
        GET_LEAF_LIST(querpn->parm_list, leno->lealst);
    } else querpn->acti_oper = RESUL_SET_ACCO | GREAT_THAN_OPCO;
    //
    strcpy(querpn->source_str, leno->leno->stri_valu);
    plan_node_enco *quer_tok = querpn;
    switch (rino->leno->vtok_kind) {
        case TEXT_TOKE:
            strcpy(quer_tok->stri_valu, rino->leno->stri_valu);
            quer_tok->acti_oper |= TEXT_VALU;
            break;
        case LOLO_NUMB_TOKE:
            quer_tok->lolo_valu = rino->leno->lolo_valu;
            quer_tok->acti_oper |= LOLO_NUMB_VALU;
            break;
        case ULLO_NUMB_TOKE:
            quer_tok->ullo_valu = rino->leno->ullo_valu;
            quer_tok->acti_oper |= ULLO_NUMB_VALU;
            break;
        case DOUB_NUMB_TOKE:
            quer_tok->doub_valu = rino->leno->doub_valu;
            quer_tok->acti_oper |= DOUB_NUMB_VALU;
            break;
        case ID_TOKE:
            strcpy(quer_tok->stri_valu, rino->leno->stri_valu);
            quer_tok->acti_oper |= ID_VALU;
            break;
        default:
            _LOG_WARN("default: vtok_kind");
            return NULL;
    }
    //
    strcpy(querpn->cont_name, qcont);
    querpn->resul_set = NULL;
    return ++quer_tok;
}

plan_node_enco *appe_leeq_node_enco(plan_node_enco *querpn, oper_node *leno, oper_node *rino, char *qcont) {
    if (METH_TOKE & leno->node_type) {
        querpn->acti_oper = METHO_SET_ACCO | LESS_EQUAL_OPCO;
        GET_LEAF_LIST(querpn->parm_list, leno->lealst);
    } else querpn->acti_oper = RESUL_SET_ACCO | LESS_EQUAL_OPCO;
    //
    strcpy(querpn->source_str, leno->leno->stri_valu);
    plan_node_enco *quer_tok = querpn;
    switch (rino->leno->vtok_kind) {
        case TEXT_TOKE:
            strcpy(quer_tok->stri_valu, rino->leno->stri_valu);
            quer_tok->acti_oper |= TEXT_VALU;
            break;
        case LOLO_NUMB_TOKE:
            quer_tok->lolo_valu = rino->leno->lolo_valu;
            quer_tok->acti_oper |= LOLO_NUMB_VALU;
            break;
        case ULLO_NUMB_TOKE:
            quer_tok->ullo_valu = rino->leno->ullo_valu;
            quer_tok->acti_oper |= ULLO_NUMB_VALU;
            break;
        case DOUB_NUMB_TOKE:
            quer_tok->doub_valu = rino->leno->doub_valu;
            quer_tok->acti_oper |= DOUB_NUMB_VALU;
            break;
        case ID_TOKE:
            strcpy(quer_tok->stri_valu, rino->leno->stri_valu);
            quer_tok->acti_oper |= ID_VALU;
            break;
        default:
            _LOG_WARN("default: vtok_kind");
            return NULL;
    }
    //
    strcpy(querpn->cont_name, qcont);
    querpn->resul_set = NULL;
    return ++quer_tok;
}

plan_node_enco *appe_leth_node_enco(plan_node_enco *querpn, oper_node *leno, oper_node *rino, char *qcont) {
    if (METH_TOKE & leno->node_type) {
        querpn->acti_oper = METHO_SET_ACCO | LESS_THAN_OPCO;
        GET_LEAF_LIST(querpn->parm_list, leno->lealst);
    } else querpn->acti_oper = RESUL_SET_ACCO | LESS_THAN_OPCO;
    //
    strcpy(querpn->source_str, leno->leno->stri_valu);
    plan_node_enco *quer_tok = querpn;
    switch (rino->leno->vtok_kind) {
        case TEXT_TOKE:
            strcpy(quer_tok->stri_valu, rino->leno->stri_valu);
            quer_tok->acti_oper |= TEXT_VALU;
            break;
        case LOLO_NUMB_TOKE:
            quer_tok->lolo_valu = rino->leno->lolo_valu;
            quer_tok->acti_oper |= LOLO_NUMB_VALU;
            break;
        case ULLO_NUMB_TOKE:
            quer_tok->ullo_valu = rino->leno->ullo_valu;
            quer_tok->acti_oper |= ULLO_NUMB_VALU;
            break;
        case DOUB_NUMB_TOKE:
            quer_tok->doub_valu = rino->leno->doub_valu;
            quer_tok->acti_oper |= DOUB_NUMB_VALU;
            break;
        case ID_TOKE:
            strcpy(quer_tok->stri_valu, rino->leno->stri_valu);
            quer_tok->acti_oper |= ID_VALU;
            break;
        default:
            _LOG_WARN("default: vtok_kind");
            return NULL;
    }
    //
    strcpy(querpn->cont_name, qcont);
    querpn->resul_set = NULL;
    return ++quer_tok;
}

plan_node_enco *appe_greq_node_enco(plan_node_enco *querpn, oper_node *leno, oper_node *rino, char *qcont) {
    if (METH_TOKE & leno->node_type) {
        querpn->acti_oper = METHO_SET_ACCO | GREAT_EQUAL_OPCO;
        GET_LEAF_LIST(querpn->parm_list, leno->lealst);
    } else querpn->acti_oper = RESUL_SET_ACCO | GREAT_EQUAL_OPCO;
    //
    strcpy(querpn->source_str, leno->leno->stri_valu);
    plan_node_enco *quer_tok = querpn;
    switch (rino->leno->vtok_kind) {
        case TEXT_TOKE:
            strcpy(quer_tok->stri_valu, rino->leno->stri_valu);
            quer_tok->acti_oper |= TEXT_VALU;
            break;
        case LOLO_NUMB_TOKE:
            quer_tok->lolo_valu = rino->leno->lolo_valu;
            quer_tok->acti_oper |= LOLO_NUMB_VALU;
            break;
        case ULLO_NUMB_TOKE:
            quer_tok->ullo_valu = rino->leno->ullo_valu;
            quer_tok->acti_oper |= ULLO_NUMB_VALU;
            break;
        case DOUB_NUMB_TOKE:
            quer_tok->doub_valu = rino->leno->doub_valu;
            quer_tok->acti_oper |= DOUB_NUMB_VALU;
            break;
        case ID_TOKE:
            strcpy(quer_tok->stri_valu, rino->leno->stri_valu);
            quer_tok->acti_oper |= ID_VALU;
            break;
        default:
            _LOG_WARN("default: vtok_kind");
            return NULL;
    }
    //
    strcpy(querpn->cont_name, qcont);
    querpn->resul_set = NULL;
    return ++quer_tok;
}

plan_node_enco *appe_plus_node_enco(plan_node_enco *querpn, oper_node *leno, oper_node *rino, char *qcont) {
    if (METH_TOKE & leno->node_type) {
        querpn->acti_oper = METHO_SET_ACCO | PLUS_OPCO;
        GET_LEAF_LIST(querpn->parm_list, leno->lealst);
    } else querpn->acti_oper = RESUL_SET_ACCO | PLUS_OPCO;
    //
    strcpy(querpn->source_str, leno->leno->stri_valu);
    plan_node_enco *quer_tok = querpn;
    switch (rino->leno->vtok_kind) {
        case LOLO_NUMB_TOKE:
            quer_tok->lolo_valu = rino->leno->lolo_valu;
            quer_tok->acti_oper |= LOLO_NUMB_VALU;
            break;
        case ULLO_NUMB_TOKE:
            quer_tok->ullo_valu = rino->leno->ullo_valu;
            quer_tok->acti_oper |= ULLO_NUMB_VALU;
            break;
        case DOUB_NUMB_TOKE:
            quer_tok->doub_valu = rino->leno->doub_valu;
            quer_tok->acti_oper |= DOUB_NUMB_VALU;
            break;
        case ID_TOKE:
            strcpy(quer_tok->stri_valu, rino->leno->stri_valu);
            quer_tok->acti_oper |= ID_VALU;
            break;
        case TEXT_TOKE:
        default:
            _LOG_WARN("default: vtok_kind");
            return NULL;
    }
    //
    strcpy(querpn->cont_name, qcont);
    querpn->resul_set = NULL;
    return ++quer_tok;
}

plan_node_enco *appe_minu_node_enco(plan_node_enco *querpn, oper_node *leno, oper_node *rino, char *qcont) {
    if (METH_TOKE & leno->node_type) {
        querpn->acti_oper = METHO_SET_ACCO | MINUS_OPCO;
        GET_LEAF_LIST(querpn->parm_list, leno->lealst);
    } else querpn->acti_oper = RESUL_SET_ACCO | MINUS_OPCO;
    //
    strcpy(querpn->source_str, leno->leno->stri_valu);
    plan_node_enco *quer_tok = querpn;
    switch (rino->leno->vtok_kind) {
        case LOLO_NUMB_TOKE:
            quer_tok->lolo_valu = rino->leno->lolo_valu;
            quer_tok->acti_oper |= LOLO_NUMB_VALU;
            break;
        case ULLO_NUMB_TOKE:
            quer_tok->ullo_valu = rino->leno->ullo_valu;
            quer_tok->acti_oper |= ULLO_NUMB_VALU;
            break;
        case DOUB_NUMB_TOKE:
            quer_tok->doub_valu = rino->leno->doub_valu;
            quer_tok->acti_oper |= DOUB_NUMB_VALU;
            break;
        case ID_TOKE:
            strcpy(quer_tok->stri_valu, rino->leno->stri_valu);
            quer_tok->acti_oper |= ID_VALU;
            break;
        case TEXT_TOKE:
        default:
            _LOG_WARN("default: vtok_kind");
            return NULL;
    }
    //
    strcpy(querpn->cont_name, qcont);
    querpn->resul_set = NULL;
    return ++quer_tok;
}

//

plan_node_enco *appe_or_node_enco(plan_node_enco *querpn, plan_node_enco *left_chil, plan_node_enco *rich_chil) {
    OSEVPF("[FUNC]:appe_or_node_enco\n");
    querpn->acti_oper = OPERA_SET_ACCO | OR_OPCO;
    querpn->left_chil = left_chil;
    querpn->righ_chil = rich_chil;
    querpn->resul_set = NULL;
    return ++querpn;
}

plan_node_enco *appe_and_node_enco(plan_node_enco *querpn, plan_node_enco *left_chil, plan_node_enco *rich_chil) {
    OSEVPF("[FUNC]:appe_and_node_enco\n");
    querpn->acti_oper = OPERA_SET_ACCO | AND_OPCO;
    querpn->left_chil = left_chil;
    querpn->righ_chil = rich_chil;
    querpn->resul_set = NULL;
    return ++querpn;
}

plan_node_enco *appe_not_node_enco(plan_node_enco *querpn, plan_node_enco *left_chil) {
    OSEVPF("[FUNC]:appe_not_node_enco\n");
    querpn->acti_oper = OPERA_SET_ACCO | NOT_OPCO;
    querpn->left_chil = left_chil;
    querpn->resul_set = NULL;
    return ++querpn;
}

//

char *find_conta_enco(contain **qcontp, char *lev1n_lv2pn) {
    //
    return lev1n_lv2pn;
}

//

char *find_conta_cost(stati_scont *qscont, char *lev1n_lv2pn) {
    //
    return lev1n_lv2pn;
}
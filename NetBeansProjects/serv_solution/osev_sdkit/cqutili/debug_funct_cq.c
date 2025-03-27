
#include "commo_header.h"
#include "kcomm_header.h"
#include "cqutili.h"
#include "debug_funct_cq.h"

//

void p_state(pastat *state) {
    printf("--- 3 synt_node:%p node_type:%u\n", state->synt_head, state->synt_head->node_type);
    printf("left_chil:%p righ_chil:%p\n", state->synt_head->left_chil, state->synt_head->righ_chil);
    printf("--- left_chil->node_type:%u, righ_chil->node_type:%u\n", state->synt_head->left_chil->node_type, state->synt_head->righ_chil->node_type);
}

//

void p_leaf_vato(valu_toke *valtok) {
    printf("--- new_leaf_vato ");
    switch (valtok->vtok_kind) {
        case TEXT_TOKE:
            printf("valtok->stri_valu:|%s|\n", valtok->stri_valu);
            break;
        case LOLO_NUMB_TOKE:
            printf("valtok->lolo_valu:|%lld|\n", valtok->lolo_valu);
            break;
        case DOUB_NUMB_TOKE:
            printf("valtok->doub_valu:|%f|\n", valtok->doub_valu);
            break;
        default:
            _LOG_WARN("default: vtok_kind");
            printf("valtok->vtok_kind:%08X\n", valtok->vtok_kind);
    }
}

//

void p_invo_vato(valu_toke *valtok) {
    switch (valtok->vtok_kind) {
        case TEXT_TOKE:
            printf("valtok->stri_valu:|%s|\n", valtok->stri_valu);
            break;
        case LOLO_NUMB_TOKE:
            printf("valtok->lolo_valu:|%lld| stri_valu:|%s|\n", valtok->lolo_valu, valtok->stri_valu);
            break;
        case ULLO_NUMB_TOKE:
            printf("valtok->ullo_valu:|%llu| stri_valu:|%s|\n", valtok->ullo_valu, valtok->stri_valu);
            break;
        case DOUB_NUMB_TOKE:
            printf("valtok->doub_valu:|%f| stri_valu:|%s|\n", valtok->doub_valu, valtok->stri_valu);
            break;
        default:
            _LOG_WARN("default: vtok_kind");
            printf("valtok->vtok_kind:%08X stri_valu:|%s|\n", valtok->vtok_kind, valtok->stri_valu);
    }
}

void p_invok(leaf_list *lealst) {
    for (; lealst; lealst = lealst->next) {
        printf("------ invo ");
        p_invo_vato(lealst->leno);
    }
}

void p_synt_node(oper_node *synt_node) {
    printf("--- synt_node:%p node_type:%u\n", synt_node, synt_node->node_type);
    if (synt_node->leno) {
        printf("    leno:%p righ_chil:%p", synt_node->leno, synt_node->righ_chil);
        printf(" stri_valu:|%s|", synt_node->leno->stri_valu);
    }
    printf("\n");
    if (METH_TOKE & synt_node->node_type) p_invok(synt_node->lealst);
}

//
void p_field_resul_enco(field_resul_co *fieres) {
    printf("field_str1:|%s|\n", fieres->field_str1);
    printf("rfmtst1:|%s|\n", fieres->rfmtst1);
    printf("field_str2:|%s|\n", fieres->field_str2);
    printf("rfmtst2:|%s|\n", fieres->rfmtst2);
    unsigned char *rescod = fieres->rescod;
    for (; rescod[0x00]; ++rescod)
        printf("rescod:|%08x|\n", rescod[0x00]);
}


#include "commo_header.h"

#include "kcomm_header.h"
#include "cqutili.h"
#include "debug_funct_ce.h"

//

void p_plan_node(plan_node_ensi *quer_tok) {
    for (; quer_tok->acti_oper; ++quer_tok) {
        printf("acti_oper:%08X ", quer_tok->acti_oper);
        printf("cont_name:|%s| \n", quer_tok->cont_name);
        // printf("source_str:|%s| \n", quer_tok->source_str);    
    }
}

//

void p_lev1me(lev1me *lv1me) {
    printf("--- printf lev1me *lv1me\n");
    printf("handn:|%s|\n", lv1me->handn);
    printf("lev1n:|%s|\n", lv1me->lev1n);
    printf("oivk_fmtsp_oe:|%s|\n", lv1me->oivk_fmtsp_oe);
    printf("oivk_size_oe:%d\n", lv1me->oivk_size_oe);
    printf("oivk_retyp_oe:%d\n", lv1me->oivk_retyp_oe);
}
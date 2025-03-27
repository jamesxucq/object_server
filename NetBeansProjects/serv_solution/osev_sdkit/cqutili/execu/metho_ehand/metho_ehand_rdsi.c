
#include "commo_header.h"
#include "kcomm_header.h"
#include "cqutili.h"
#include "../meth_compa/meth_compa_rdsi.h"
#include "../conte_resou.h"
#include "../ustri_utili.h"

#include "metho_ehand_rdsi.h"

// riv_curso_t *lidcur;
#define CREAT_HANDL_RESOU(LID_CURSO, QUER_PLAN, STORA_HA, PHYS_CONT) \
    QUER_PLAN->resul_set = tmpfile64(); \
    if (!QUER_PLAN->resul_set) return -1; \
    LID_CURSO = creat_curso(STORA_HA, PHYS_CONT, QUER_PLAN->cont_name); \
    if (!LID_CURSO) return -1;

// char *parm_oivk;
#define CREAT_PARAM_RESOU(PARM_OIVK, QUER_PLAN, LVOME, STORA_HA, LID_CURSO) \
    pams_invk parm_invo; \
    if (creat_binary_parms(&parm_invo, QUER_PLAN->parm_list)) { \
        CLOSE_CURSO(STORA_HA, LID_CURSO); \
        return -1; \
    } \
    PARM_OIVK = (char *) malloc(LVOME->oivk_size_oe); \
    if (!PARM_OIVK) { \
        CLOSE_CURSO(STORA_HA, LID_CURSO); \
        return -1; \
    } \
    if (build_oinvk_parms(PARM_OIVK, parm_invo.pamvp)) \
        return -1;

//
#define CLOSE_PARAM(PARM_OIVK)  free(PARM_OIVK)

//
// rdsi
//

static int hand_not_rdsi() {
    OSEVPF("[FUNC]:hand_not\n");
    //
    return 0x00;
}

static int hand_is_rdsi() {
    OSEVPF("[FUNC]:hand_is\n");
    //
    return 0x00;
}

static int hand_match_rdsi() {
    OSEVPF("[FUNC]:hand_match\n");
    //
    return 0x00;
}

static int hand_like_kw_rdsi() {
    OSEVPF("[FUNC]:hand_like_kw\n");
    //
    return 0x00;
}

static int hand_between_rdsi() {
    OSEVPF("[FUNC]:hand_between\n");
    //
    return 0x00;
}

static int hand_in_rdsi() {
    OSEVPF("[FUNC]:hand_in\n");
    //
    return 0x00;
}

static int hand_not_equal_rdsi(plan_node_ensi *querpn, physi_conte *phys_cont, rive_ha *stora_ha, lev1me *lv1me) {
    int hand_valu = 0x00;
    OSEVPF("[FUNC]:hand_not_equal\n");
    OSEVPF("--- create tmpfile64.\n");
    riv_curso_t *lidcur;
    CREAT_HANDL_RESOU(lidcur, querpn, stora_ha, phys_cont);
    char *parm_oivk;
    CREAT_PARAM_RESOU(parm_oivk, querpn, lv1me, stora_ha, lidcur);
    //
    switch (VALU_CODE(querpn->acti_oper)) {
        case TEXT_VALU:
            hand_valu = meth_text_noteq_rdsi(querpn->resul_set, lidcur, stora_ha, lv1me, parm_oivk, querpn->stri_valu);
            break;
        case LOLO_NUMB_VALU:
            hand_valu = meth_lolo_noteq_rdsi(querpn->resul_set, lidcur, stora_ha, lv1me, parm_oivk, querpn->lolo_valu);
            break;
        case ULLO_NUMB_VALU:
            hand_valu = meth_ullo_noteq_rdsi(querpn->resul_set, lidcur, stora_ha, lv1me, parm_oivk, querpn->ullo_valu);
            break;
        case DOUB_NUMB_VALU:
            hand_valu = meth_doub_noteq_rdsi(querpn->resul_set, lidcur, stora_ha, lv1me, parm_oivk, querpn->doub_valu);
            break;
        case ID_VALU:
            hand_valu = -1;
            break;
    }
    CLOSE_PARAM(parm_oivk);
    CLOSE_CURSO(stora_ha, lidcur);
    //
    return hand_valu;
}

static int hand_equal_rdsi(plan_node_ensi *querpn, physi_conte *phys_cont, rive_ha *stora_ha, lev1me *lv1me) {
    int hand_valu = 0x00;
    OSEVPF("[FUNC]:hand_equal\n");
    OSEVPF("--- create tmpfile64.\n");
    riv_curso_t *lidcur;
    CREAT_HANDL_RESOU(lidcur, querpn, stora_ha, phys_cont);
    char *parm_oivk;
    CREAT_PARAM_RESOU(parm_oivk, querpn, lv1me, stora_ha, lidcur);
    //
    switch (VALU_CODE(querpn->acti_oper)) {
        case TEXT_VALU:
            hand_valu = meth_text_equal_rdsi(querpn->resul_set, lidcur, stora_ha, lv1me, parm_oivk, querpn->stri_valu);
            break;
        case LOLO_NUMB_VALU:
            hand_valu = meth_lolo_equal_rdsi(querpn->resul_set, lidcur, stora_ha, lv1me, parm_oivk, querpn->lolo_valu);
            break;
        case ULLO_NUMB_VALU:
            hand_valu = meth_ullo_equal_rdsi(querpn->resul_set, lidcur, stora_ha, lv1me, parm_oivk, querpn->ullo_valu);
            break;
        case DOUB_NUMB_VALU:
            hand_valu = meth_doub_equal_rdsi(querpn->resul_set, lidcur, stora_ha, lv1me, parm_oivk, querpn->doub_valu);
            break;
        case ID_VALU:
            hand_valu = meth_rid_equal_rdsi(querpn->resul_set, lidcur, stora_ha, lv1me, parm_oivk, querpn->source_str);
            break;
    }
    CLOSE_PARAM(parm_oivk);
    CLOSE_CURSO(stora_ha, lidcur);
    //
    return hand_valu;
}

static int hand_great_than_rdsi(plan_node_ensi *querpn, physi_conte *phys_cont, rive_ha *stora_ha, lev1me *lv1me) {
    int hand_valu = 0x00;
    OSEVPF("[FUNC]:hand_great_than\n");
    OSEVPF("--- create tmpfile64.\n");
    riv_curso_t *lidcur;
    CREAT_HANDL_RESOU(lidcur, querpn, stora_ha, phys_cont);
    char *parm_oivk;
    CREAT_PARAM_RESOU(parm_oivk, querpn, lv1me, stora_ha, lidcur);
    //
    switch (VALU_CODE(querpn->acti_oper)) {
        case TEXT_VALU:
            hand_valu = meth_text_great_rdsi(querpn->resul_set, lidcur, stora_ha, lv1me, parm_oivk, querpn->stri_valu);
            break;
        case LOLO_NUMB_VALU:
            hand_valu = meth_lolo_great_rdsi(querpn->resul_set, lidcur, stora_ha, lv1me, parm_oivk, querpn->lolo_valu);
            break;
        case ULLO_NUMB_VALU:
            hand_valu = meth_ullo_great_rdsi(querpn->resul_set, lidcur, stora_ha, lv1me, parm_oivk, querpn->ullo_valu);
            break;
        case DOUB_NUMB_VALU:
            hand_valu = meth_doub_great_rdsi(querpn->resul_set, lidcur, stora_ha, lv1me, parm_oivk, querpn->doub_valu);
            break;
        case ID_VALU:
            hand_valu = -1;
            break;
    }
    CLOSE_PARAM(parm_oivk);
    CLOSE_CURSO(stora_ha, lidcur);
    //
    OSEVPF("hand_great_than end.....\n");
    return hand_valu;
}

static int hand_less_equal_rdsi(plan_node_ensi *querpn, physi_conte *phys_cont, rive_ha *stora_ha, lev1me *lv1me) {
    int hand_valu = 0x00;
    OSEVPF("[FUNC]:hand_less_equal\n");
    OSEVPF("--- create tmpfile64.\n");
    riv_curso_t *lidcur;
    CREAT_HANDL_RESOU(lidcur, querpn, stora_ha, phys_cont);
    char *parm_oivk;
    CREAT_PARAM_RESOU(parm_oivk, querpn, lv1me, stora_ha, lidcur);
    //
    switch (VALU_CODE(querpn->acti_oper)) {
        case TEXT_VALU:
            hand_valu = meth_text_leseq_rdsi(querpn->resul_set, lidcur, stora_ha, lv1me, parm_oivk, querpn->stri_valu);
            break;
        case LOLO_NUMB_VALU:
            hand_valu = meth_lolo_leseq_rdsi(querpn->resul_set, lidcur, stora_ha, lv1me, parm_oivk, querpn->lolo_valu);
            break;
        case ULLO_NUMB_VALU:
            hand_valu = meth_ullo_leseq_rdsi(querpn->resul_set, lidcur, stora_ha, lv1me, parm_oivk, querpn->ullo_valu);
            break;
        case DOUB_NUMB_VALU:
            hand_valu = meth_doub_leseq_rdsi(querpn->resul_set, lidcur, stora_ha, lv1me, parm_oivk, querpn->doub_valu);
            break;
        case ID_VALU:
            hand_valu = -1;
            break;
    }
    CLOSE_PARAM(parm_oivk);
    CLOSE_CURSO(stora_ha, lidcur);
    //
    return hand_valu;
}

static int hand_less_than_rdsi(plan_node_ensi *querpn, physi_conte *phys_cont, rive_ha *stora_ha, lev1me *lv1me) {
    int hand_valu = 0x00;
    OSEVPF("[FUNC]:hand_less_than\n");
    OSEVPF("--- create tmpfile64.\n");
    riv_curso_t *lidcur;
    CREAT_HANDL_RESOU(lidcur, querpn, stora_ha, phys_cont);
    char *parm_oivk;
    CREAT_PARAM_RESOU(parm_oivk, querpn, lv1me, stora_ha, lidcur);
    //
    switch (VALU_CODE(querpn->acti_oper)) {
        case TEXT_VALU:
            hand_valu = meth_text_less_rdsi(querpn->resul_set, lidcur, stora_ha, lv1me, parm_oivk, querpn->stri_valu);
            break;
        case LOLO_NUMB_VALU:
            hand_valu = meth_lolo_less_rdsi(querpn->resul_set, lidcur, stora_ha, lv1me, parm_oivk, querpn->lolo_valu);
            break;
        case ULLO_NUMB_VALU:
            hand_valu = meth_ullo_less_rdsi(querpn->resul_set, lidcur, stora_ha, lv1me, parm_oivk, querpn->ullo_valu);
            break;
        case DOUB_NUMB_VALU:
            hand_valu = meth_doub_less_rdsi(querpn->resul_set, lidcur, stora_ha, lv1me, parm_oivk, querpn->doub_valu);
            break;
        case ID_VALU:
            hand_valu = -1;
            break;
    }
    CLOSE_PARAM(parm_oivk);
    CLOSE_CURSO(stora_ha, lidcur);
    //
    return hand_valu;
}

static int hand_great_equal_rdsi(plan_node_ensi *querpn, physi_conte *phys_cont, rive_ha *stora_ha, lev1me *lv1me) {
    int hand_valu = 0x00;
    OSEVPF("[FUNC]:hand_great_equal\n");
    OSEVPF("--- create tmpfile64.\n");
    riv_curso_t *lidcur;
    CREAT_HANDL_RESOU(lidcur, querpn, stora_ha, phys_cont);
    char *parm_oivk;
    CREAT_PARAM_RESOU(parm_oivk, querpn, lv1me, stora_ha, lidcur);
    //
    switch (VALU_CODE(querpn->acti_oper)) {
        case TEXT_VALU:
            hand_valu = meth_text_greeq_rdsi(querpn->resul_set, lidcur, stora_ha, lv1me, parm_oivk, querpn->stri_valu);
            break;
        case LOLO_NUMB_VALU:
            hand_valu = meth_lolo_greeq_rdsi(querpn->resul_set, lidcur, stora_ha, lv1me, parm_oivk, querpn->lolo_valu);
            break;
        case ULLO_NUMB_VALU:
            hand_valu = meth_ullo_greeq_rdsi(querpn->resul_set, lidcur, stora_ha, lv1me, parm_oivk, querpn->ullo_valu);
            break;
        case DOUB_NUMB_VALU:
            hand_valu = meth_doub_greeq_rdsi(querpn->resul_set, lidcur, stora_ha, lv1me, parm_oivk, querpn->doub_valu);
            break;
        case ID_VALU:
            hand_valu = -1;
            break;
    }
    CLOSE_PARAM(parm_oivk);
    CLOSE_CURSO(stora_ha, lidcur);
    //
    return hand_valu;
}

static int hand_escape_rdsi() {
    OSEVPF("[FUNC]:hand_escape\n");
    //
    return 0x00;
}

static int hand_plus_rdsi() {
    OSEVPF("[FUNC]:hand_plus\n");
    //
    return 0x00;
}

static int hand_minus_rdsi() {
    OSEVPF("[FUNC]:hand_minus\n");
    //
    return 0x00;
}

//

int hand_metho_set_rdsi(plan_node_ensi *querpn, physi_conte *phys_cont, rive_ha *stora_ha, lev1me *lv1me) {
    int hand_valu = 0x00;
    // NOT IS MATCH LIKE_KW BETWEEN IN NOT_EQUAL EQUAL 
    // GREAT_THAN LESS_EQUAL LESS_THAN GREAT_EQUAL ESCAPE PLUS MINUS
    switch (OPER_CODE(querpn->acti_oper)) {
        case NOT_OPCO:
            hand_valu = hand_not_rdsi(); //
            break;
        case IS_OPCO:
            hand_valu = hand_is_rdsi(); //
            break;
        case MATCH_OPCO:
            hand_valu = hand_match_rdsi(); //
            break;
        case LIKE_KW_OPCO:
            hand_valu = hand_like_kw_rdsi(); //
            break;
        case BETWEEN_OPCO:
            hand_valu = hand_between_rdsi(); //
            break;
        case IN_OPCO:
            hand_valu = hand_in_rdsi(); //
            break;
        case NOT_EQUAL_OPCO:
            hand_valu = hand_not_equal_rdsi(querpn, phys_cont, stora_ha, lv1me);
            break;
        case EQUAL_OPCO:
            hand_valu = hand_equal_rdsi(querpn, phys_cont, stora_ha, lv1me);
            break;
        case GREAT_THAN_OPCO:
            hand_valu = hand_great_than_rdsi(querpn, phys_cont, stora_ha, lv1me);
            break;
        case LESS_EQUAL_OPCO:
            hand_valu = hand_less_equal_rdsi(querpn, phys_cont, stora_ha, lv1me);
            break;
        case LESS_THAN_OPCO:
            hand_valu = hand_less_than_rdsi(querpn, phys_cont, stora_ha, lv1me);
            break;
        case GREAT_EQUAL_OPCO:
            hand_valu = hand_great_equal_rdsi(querpn, phys_cont, stora_ha, lv1me);
            break;
        case ESCAPE_OPCO:
            hand_valu = hand_escape_rdsi(); //
            break;
        case PLUS_OPCO:
            hand_valu = hand_plus_rdsi(); //
            break;
        case MINUS_OPCO:
            hand_valu = hand_minus_rdsi(); //
            break;
    }
    //
    OSEVPF("hand_metho_set_rdsi end.....\n");
    return hand_valu;
}

//







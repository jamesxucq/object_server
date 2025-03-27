
#include "commo_header.h"
#include "kcomm_header.h"
#include "lexic/valtok.h"
#include "gramm/synta_tree.h"
#include "plan/plan_node_ensi.h"
#include "plan/plan_node_enco.h"

#include "../data_compa/data_compa.h"
#include "../conte_resou.h"
#include "resul_ehand_enco.h"

//
#define PROJE_HANDL_RESOU(QUER_PLAN, LID_CURSO, STORA_HA, PHYS_CONT) \
    QUER_PLAN->resul_set = tmpfile64(); \
    if (!QUER_PLAN->resul_set) return -1; \
    LID_CURSO = proje_curso(STORA_HA, PHYS_CONT, QUER_PLAN->cont_name, QUER_PLAN->source_str); \
    if (!LID_CURSO) return -1;

// NOT IS MATCH LIKE_KW BETWEEN IN NOT_EQUAL EQUAL 
// GREAT_THAN LESS_EQUAL LESS_THAN GREAT_EQUAL ESCAPE PLUS MINUS

static int hand_not() {
    OSEVPF("[FUNC]:hand_not\n");
    //
    return 0x00;
}

static int hand_is() {
    OSEVPF("[FUNC]:hand_is\n");
    //
    return 0x00;
}

static int hand_match() {
    OSEVPF("[FUNC]:hand_match\n");
    //
    return 0x00;
}

static int hand_like_kw() {
    OSEVPF("[FUNC]:hand_like_kw\n");
    //
    return 0x00;
}

static int hand_between() {
    OSEVPF("[FUNC]:hand_between\n");
    //
    return 0x00;
}

static int hand_in() {
    OSEVPF("[FUNC]:hand_in\n");
    //
    return 0x00;
}

static int hand_not_equal(plan_node_enco *querpn, physi_conte *phys_cont, rive_ha *stora_ha) {
    int hand_valu = 0x00;
    OSEVPF("[FUNC]:hand_not_equal\n");
    OSEVPF("--- create tmpfile64.\n");
    riv_curso_t *lidcur;
    PROJE_HANDL_RESOU(querpn, lidcur, stora_ha, phys_cont);
    //
    switch (VALU_CODE(querpn->acti_oper)) {
        case TEXT_VALU:
            hand_valu = data_text_noteq(querpn->resul_set, lidcur, stora_ha, querpn->stri_valu);
            break;
        case LOLO_NUMB_VALU:
            hand_valu = data_lolo_noteq(querpn->resul_set, lidcur, stora_ha, querpn->lolo_valu);
            break;
        case ULLO_NUMB_VALU:
            hand_valu = data_ullo_noteq(querpn->resul_set, lidcur, stora_ha, querpn->ullo_valu);
            break;
        case DOUB_NUMB_VALU:
            hand_valu = data_doub_noteq(querpn->resul_set, lidcur, stora_ha, querpn->doub_valu);
            break;
        case ID_VALU:
            hand_valu = -1;
            break;
    }
    CLOSE_CURSO(stora_ha, lidcur);
    //
    return hand_valu;
}

static int hand_equal(plan_node_enco *querpn, physi_conte *phys_cont, rive_ha *stora_ha) {
    int hand_valu = 0x00;
    OSEVPF("[FUNC]:hand_equal\n");
    OSEVPF("--- create tmpfile64.\n");
    riv_curso_t *lidcur;
    PROJE_HANDL_RESOU(querpn, lidcur, stora_ha, phys_cont);
    //
    switch (VALU_CODE(querpn->acti_oper)) {
        case TEXT_VALU:
            hand_valu = data_text_equal(querpn->resul_set, lidcur, stora_ha, querpn->stri_valu);
            break;
        case LOLO_NUMB_VALU:
            hand_valu = data_lolo_equal(querpn->resul_set, lidcur, stora_ha, querpn->lolo_valu);
            break;
        case ULLO_NUMB_VALU:
            hand_valu = data_ullo_equal(querpn->resul_set, lidcur, stora_ha, querpn->ullo_valu);
            break;
        case DOUB_NUMB_VALU:
            hand_valu = data_doub_equal(querpn->resul_set, lidcur, stora_ha, querpn->doub_valu);
            break;
        case ID_VALU:
            // hand_valu = data_rid_equal(querpn->resul_set, lidcur, stora_ha, querpn->source_str);
            break;
    }
    CLOSE_CURSO(stora_ha, lidcur);
    //
    return hand_valu;
}

static int hand_great_than(plan_node_enco *querpn, physi_conte *phys_cont, rive_ha *stora_ha) {
    int hand_valu = 0x00;
    OSEVPF("[FUNC]:hand_great_than\n");
    OSEVPF("--- create tmpfile64.\n");
    riv_curso_t *lidcur;
    PROJE_HANDL_RESOU(querpn, lidcur, stora_ha, phys_cont);
    //
    switch (VALU_CODE(querpn->acti_oper)) {
        case TEXT_VALU:
            hand_valu = data_text_great(querpn->resul_set, lidcur, stora_ha, querpn->stri_valu);
            break;
        case LOLO_NUMB_VALU:
            hand_valu = data_lolo_great(querpn->resul_set, lidcur, stora_ha, querpn->lolo_valu);
            break;
        case ULLO_NUMB_VALU:
            hand_valu = data_ullo_great(querpn->resul_set, lidcur, stora_ha, querpn->ullo_valu);
            break;
        case DOUB_NUMB_VALU:
            hand_valu = data_doub_great(querpn->resul_set, lidcur, stora_ha, querpn->doub_valu);
            break;
        case ID_VALU:
            hand_valu = -1;
            break;
    }
    CLOSE_CURSO(stora_ha, lidcur);
    //
    OSEVPF("hand_great_than end.....\n");
    return hand_valu;
}

static int hand_less_equal(plan_node_enco *querpn, physi_conte *phys_cont, rive_ha *stora_ha) {
    int hand_valu = 0x00;
    OSEVPF("[FUNC]:hand_less_equal\n");
    OSEVPF("--- create tmpfile64.\n");
    riv_curso_t *lidcur;
    PROJE_HANDL_RESOU(querpn, lidcur, stora_ha, phys_cont);
    //
    switch (VALU_CODE(querpn->acti_oper)) {
        case TEXT_VALU:
            hand_valu = data_text_leseq(querpn->resul_set, lidcur, stora_ha, querpn->stri_valu);
            break;
        case LOLO_NUMB_VALU:
            hand_valu = data_lolo_leseq(querpn->resul_set, lidcur, stora_ha, querpn->lolo_valu);
            break;
        case ULLO_NUMB_VALU:
            hand_valu = data_ullo_leseq(querpn->resul_set, lidcur, stora_ha, querpn->ullo_valu);
            break;
        case DOUB_NUMB_VALU:
            hand_valu = data_doub_leseq(querpn->resul_set, lidcur, stora_ha, querpn->doub_valu);
            break;
        case ID_VALU:
            hand_valu = -1;
            break;
    }
    CLOSE_CURSO(stora_ha, lidcur);
    //
    return hand_valu;
}

static int hand_less_than(plan_node_enco *querpn, physi_conte *phys_cont, rive_ha *stora_ha) {
    int hand_valu = 0x00;
    OSEVPF("[FUNC]:hand_less_than\n");
    OSEVPF("--- create tmpfile64.\n");
    riv_curso_t *lidcur;
    PROJE_HANDL_RESOU(querpn, lidcur, stora_ha, phys_cont);
    //
    switch (VALU_CODE(querpn->acti_oper)) {
        case TEXT_VALU:
            hand_valu = data_text_less(querpn->resul_set, lidcur, stora_ha, querpn->stri_valu);
            break;
        case LOLO_NUMB_VALU:
            hand_valu = data_lolo_less(querpn->resul_set, lidcur, stora_ha, querpn->lolo_valu);
            break;
        case ULLO_NUMB_VALU:
            hand_valu = data_ullo_less(querpn->resul_set, lidcur, stora_ha, querpn->ullo_valu);
            break;
        case DOUB_NUMB_VALU:
            hand_valu = data_doub_less(querpn->resul_set, lidcur, stora_ha, querpn->doub_valu);
            break;
        case ID_VALU:
            hand_valu = -1;
            break;
    }
    CLOSE_CURSO(stora_ha, lidcur);
    //
    return hand_valu;
}

static int hand_great_equal(plan_node_enco *querpn, physi_conte *phys_cont, rive_ha *stora_ha) {
    int hand_valu = 0x00;
    OSEVPF("[FUNC]:hand_great_equal\n");
    OSEVPF("--- create tmpfile64.\n");
    riv_curso_t *lidcur;
    PROJE_HANDL_RESOU(querpn, lidcur, stora_ha, phys_cont);
    //
    switch (VALU_CODE(querpn->acti_oper)) {
        case TEXT_VALU:
            hand_valu = data_text_greeq(querpn->resul_set, lidcur, stora_ha, querpn->stri_valu);
            break;
        case LOLO_NUMB_VALU:
            hand_valu = data_lolo_greeq(querpn->resul_set, lidcur, stora_ha, querpn->lolo_valu);
            break;
        case ULLO_NUMB_VALU:
            hand_valu = data_ullo_greeq(querpn->resul_set, lidcur, stora_ha, querpn->ullo_valu);
            break;
        case DOUB_NUMB_VALU:
            hand_valu = data_doub_greeq(querpn->resul_set, lidcur, stora_ha, querpn->doub_valu);
            break;
        case ID_VALU:
            hand_valu = -1;
            break;
    }
    CLOSE_CURSO(stora_ha, lidcur);
    //
    return hand_valu;
}

static int hand_escape() {
    OSEVPF("[FUNC]:hand_escape\n");
    //
    return 0x00;
}

static int hand_plus() {
    OSEVPF("[FUNC]:hand_plus\n");
    //
    return 0x00;
}

static int hand_minus() {
    OSEVPF("[FUNC]:hand_minus\n");
    //
    return 0x00;
}

//

int hand_resul_set_enco(plan_node_enco *querpn, physi_conte *phys_cont, rive_ha *stora_ha) {
    int hand_valu = 0x00;
    // NOT IS MATCH LIKE_KW BETWEEN IN NOT_EQUAL EQUAL 
    // GREAT_THAN LESS_EQUAL LESS_THAN GREAT_EQUAL ESCAPE PLUS MINUS
    switch (OPER_CODE(querpn->acti_oper)) {
        case NOT_OPCO:
            hand_valu = hand_not(); //
            break;
        case IS_OPCO:
            hand_valu = hand_is(); //
            break;
        case MATCH_OPCO:
            hand_valu = hand_match(); //
            break;
        case LIKE_KW_OPCO:
            hand_valu = hand_like_kw(); //
            break;
        case BETWEEN_OPCO:
            hand_valu = hand_between(); //
            break;
        case IN_OPCO:
            hand_valu = hand_in(); //
            break;
        case NOT_EQUAL_OPCO:
            hand_valu = hand_not_equal(querpn, phys_cont, stora_ha);
            break;
        case EQUAL_OPCO:
            hand_valu = hand_equal(querpn, phys_cont, stora_ha);
            break;
        case GREAT_THAN_OPCO:
            hand_valu = hand_great_than(querpn, phys_cont, stora_ha);
            break;
        case LESS_EQUAL_OPCO:
            hand_valu = hand_less_equal(querpn, phys_cont, stora_ha);
            break;
        case LESS_THAN_OPCO:
            hand_valu = hand_less_than(querpn, phys_cont, stora_ha);
            break;
        case GREAT_EQUAL_OPCO:
            hand_valu = hand_great_equal(querpn, phys_cont, stora_ha);
            break;
        case ESCAPE_OPCO:
            hand_valu = hand_escape(); //
            break;
        case PLUS_OPCO:
            hand_valu = hand_plus(); //
            break;
        case MINUS_OPCO:
            hand_valu = hand_minus(); //
            break;
    }
    //
    OSEVPF("hand_resul_set_ensi end.....\n");
    return hand_valu;
}




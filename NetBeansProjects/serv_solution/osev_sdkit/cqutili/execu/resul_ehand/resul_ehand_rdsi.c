
#include "commo_header.h"
#include "kcomm_header.h"
#include "lexic/valtok.h"
#include "gramm/synta_tree.h"
#include "plan/plan_node_ensi.h"
#include "plan/plan_node_enco.h"

#include "../data_compa/data_compa_rdsi.h"
#include "../conte_resou.h"
#include "resul_ehand_rdsi.h"

//
#define PROJE_HANDL_RESOU(QUER_PLAN, LID_CURSO, STORA_HA, PHYS_CONT) \
    QUER_PLAN->resul_set = tmpfile64(); \
    if (!QUER_PLAN->resul_set) return -1; \
    LID_CURSO = proje_curso(STORA_HA, PHYS_CONT, QUER_PLAN->cont_name, QUER_PLAN->source_str); \
    if (!LID_CURSO) return -1;

// rssi

// NOT IS MATCH LIKE_KW BETWEEN IN NOT_EQUAL EQUAL 
// GREAT_THAN LESS_EQUAL LESS_THAN GREAT_EQUAL ESCAPE PLUS MINUS

//
// rdsi

// NOT IS MATCH LIKE_KW BETWEEN IN NOT_EQUAL EQUAL 
// GREAT_THAN LESS_EQUAL LESS_THAN GREAT_EQUAL ESCAPE PLUS MINUS

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

static int hand_not_equal_rdsi(plan_node_ensi *querpn, physi_conte *phys_cont, rive_ha *stora_ha) {
    int hand_valu = 0x00;
    OSEVPF("[FUNC]:hand_not_equal\n");
    OSEVPF("--- create tmpfile64.\n");
    riv_curso_t *lidcur;
    PROJE_HANDL_RESOU(querpn, lidcur, stora_ha, phys_cont);
    //
    switch (VALU_CODE(querpn->acti_oper)) {
        case TEXT_VALU:
            hand_valu = data_text_noteq_rdsi(querpn->resul_set, lidcur, stora_ha, querpn->stri_valu);
            break;
        case LOLO_NUMB_VALU:
            hand_valu = data_lolo_noteq_rdsi(querpn->resul_set, lidcur, stora_ha, querpn->lolo_valu);
            break;
        case ULLO_NUMB_VALU:
            hand_valu = data_ullo_noteq_rdsi(querpn->resul_set, lidcur, stora_ha, querpn->ullo_valu);
            break;
        case DOUB_NUMB_VALU:
            hand_valu = data_doub_noteq_rdsi(querpn->resul_set, lidcur, stora_ha, querpn->doub_valu);
            break;
        case ID_VALU:
            hand_valu = -1;
            break;
    }
    CLOSE_CURSO(stora_ha, lidcur);
    //
    return hand_valu;
}

static int hand_equal_rdsi(plan_node_ensi *querpn, physi_conte *phys_cont, rive_ha *stora_ha) {
    int hand_valu = 0x00;
    OSEVPF("[FUNC]:hand_equal\n");
    OSEVPF("--- create tmpfile64.\n");
    riv_curso_t *lidcur;
    PROJE_HANDL_RESOU(querpn, lidcur, stora_ha, phys_cont);
    //
    switch (VALU_CODE(querpn->acti_oper)) {
        case TEXT_VALU:
            hand_valu = data_text_equal_rdsi(querpn->resul_set, lidcur, stora_ha, querpn->stri_valu);
            break;
        case LOLO_NUMB_VALU:
            hand_valu = data_lolo_equal_rdsi(querpn->resul_set, lidcur, stora_ha, querpn->lolo_valu);
            break;
        case ULLO_NUMB_VALU:
            hand_valu = data_ullo_equal_rdsi(querpn->resul_set, lidcur, stora_ha, querpn->ullo_valu);
            break;
        case DOUB_NUMB_VALU:
            hand_valu = data_doub_equal_rdsi(querpn->resul_set, lidcur, stora_ha, querpn->doub_valu);
            break;
        case ID_VALU:
            hand_valu = data_rid_equal_rdsi(querpn->resul_set, lidcur, stora_ha, querpn->source_str);
            break;
    }
    CLOSE_CURSO(stora_ha, lidcur);
    //
    return hand_valu;
}

static int hand_great_than_rdsi(plan_node_ensi *querpn, physi_conte *phys_cont, rive_ha *stora_ha) {
    int hand_valu = 0x00;
    OSEVPF("[FUNC]:hand_great_than\n");
    OSEVPF("--- create tmpfile64.\n");
    riv_curso_t *lidcur;
    PROJE_HANDL_RESOU(querpn, lidcur, stora_ha, phys_cont);
    //
    switch (VALU_CODE(querpn->acti_oper)) {
        case TEXT_VALU:
            hand_valu = data_text_great_rdsi(querpn->resul_set, lidcur, stora_ha, querpn->stri_valu);
            break;
        case LOLO_NUMB_VALU:
            hand_valu = data_lolo_great_rdsi(querpn->resul_set, lidcur, stora_ha, querpn->lolo_valu);
            break;
        case ULLO_NUMB_VALU:
            hand_valu = data_ullo_great_rdsi(querpn->resul_set, lidcur, stora_ha, querpn->ullo_valu);
            break;
        case DOUB_NUMB_VALU:
            hand_valu = data_doub_great_rdsi(querpn->resul_set, lidcur, stora_ha, querpn->doub_valu);
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

static int hand_less_equal_rdsi(plan_node_ensi *querpn, physi_conte *phys_cont, rive_ha *stora_ha) {
    int hand_valu = 0x00;
    OSEVPF("[FUNC]:hand_less_equal\n");
    OSEVPF("--- create tmpfile64.\n");
    riv_curso_t *lidcur;
    PROJE_HANDL_RESOU(querpn, lidcur, stora_ha, phys_cont);
    //
    switch (VALU_CODE(querpn->acti_oper)) {
        case TEXT_VALU:
            hand_valu = data_text_leseq_rdsi(querpn->resul_set, lidcur, stora_ha, querpn->stri_valu);
            break;
        case LOLO_NUMB_VALU:
            hand_valu = data_lolo_leseq_rdsi(querpn->resul_set, lidcur, stora_ha, querpn->lolo_valu);
            break;
        case ULLO_NUMB_VALU:
            hand_valu = data_ullo_leseq_rdsi(querpn->resul_set, lidcur, stora_ha, querpn->ullo_valu);
            break;
        case DOUB_NUMB_VALU:
            hand_valu = data_doub_leseq_rdsi(querpn->resul_set, lidcur, stora_ha, querpn->doub_valu);
            break;
        case ID_VALU:
            hand_valu = -1;
            break;
    }
    CLOSE_CURSO(stora_ha, lidcur);
    //
    return hand_valu;
}

static int hand_less_than_rdsi(plan_node_ensi *querpn, physi_conte *phys_cont, rive_ha *stora_ha) {
    int hand_valu = 0x00;
    OSEVPF("[FUNC]:hand_less_than\n");
    OSEVPF("--- create tmpfile64.\n");
    riv_curso_t *lidcur;
    PROJE_HANDL_RESOU(querpn, lidcur, stora_ha, phys_cont);
    //
    switch (VALU_CODE(querpn->acti_oper)) {
        case TEXT_VALU:
            hand_valu = data_text_less_rdsi(querpn->resul_set, lidcur, stora_ha, querpn->stri_valu);
            break;
        case LOLO_NUMB_VALU:
            hand_valu = data_lolo_less_rdsi(querpn->resul_set, lidcur, stora_ha, querpn->lolo_valu);
            break;
        case ULLO_NUMB_VALU:
            hand_valu = data_ullo_less_rdsi(querpn->resul_set, lidcur, stora_ha, querpn->ullo_valu);
            break;
        case DOUB_NUMB_VALU:
            hand_valu = data_doub_less_rdsi(querpn->resul_set, lidcur, stora_ha, querpn->doub_valu);
            break;
        case ID_VALU:
            hand_valu = -1;
            break;
    }
    CLOSE_CURSO(stora_ha, lidcur);
    //
    return hand_valu;
}

static int hand_great_equal_rdsi(plan_node_ensi *querpn, physi_conte *phys_cont, rive_ha *stora_ha) {
    int hand_valu = 0x00;
    OSEVPF("[FUNC]:hand_great_equal\n");
    OSEVPF("--- create tmpfile64.\n");
    riv_curso_t *lidcur;
    PROJE_HANDL_RESOU(querpn, lidcur, stora_ha, phys_cont);
    //
    switch (VALU_CODE(querpn->acti_oper)) {
        case TEXT_VALU:
            hand_valu = data_text_greeq_rdsi(querpn->resul_set, lidcur, stora_ha, querpn->stri_valu);
            break;
        case LOLO_NUMB_VALU:
            hand_valu = data_lolo_greeq_rdsi(querpn->resul_set, lidcur, stora_ha, querpn->lolo_valu);
            break;
        case ULLO_NUMB_VALU:
            hand_valu = data_ullo_greeq_rdsi(querpn->resul_set, lidcur, stora_ha, querpn->ullo_valu);
            break;
        case DOUB_NUMB_VALU:
            hand_valu = data_doub_greeq_rdsi(querpn->resul_set, lidcur, stora_ha, querpn->doub_valu);
            break;
        case ID_VALU:
            hand_valu = -1;
            break;
    }
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

int hand_resul_set_rdsi(plan_node_ensi *querpn, physi_conte *phys_cont, rive_ha *stora_ha) {
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
            hand_valu = hand_not_equal_rdsi(querpn, phys_cont, stora_ha);
            break;
        case EQUAL_OPCO:
            hand_valu = hand_equal_rdsi(querpn, phys_cont, stora_ha);
            break;
        case GREAT_THAN_OPCO:
            hand_valu = hand_great_than_rdsi(querpn, phys_cont, stora_ha);
            break;
        case LESS_EQUAL_OPCO:
            hand_valu = hand_less_equal_rdsi(querpn, phys_cont, stora_ha);
            break;
        case LESS_THAN_OPCO:
            hand_valu = hand_less_than_rdsi(querpn, phys_cont, stora_ha);
            break;
        case GREAT_EQUAL_OPCO:
            hand_valu = hand_great_equal_rdsi(querpn, phys_cont, stora_ha);
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
    OSEVPF("hand_resul_set_rssi end.....\n");
    return hand_valu;
}

//



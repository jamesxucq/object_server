#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "third_party.h"
#include "kcomm_header.h"

#include "cqutili.h"
#include "estri_utili.h"

#include "close_rcont_utili.h"
#include "refre_utili.h"
#include "refresh_rcontai.h"

// -1: error 0x00: pass check 0x01: must refresh

int chk_rcont_versi(int rcoun, cont_versi *rcove, cont_lsmp *conda_stm) {
    OSEVPF("[FUNC]:chk_rcont_versi\n");
    contain *rdcop;
    unsigned int inde = 0x00;
    for (; rcoun > inde; ++inde, ++rcove) {
        rdcop = (contain *) cache_value(&rcove->lv4p_obid, conda_stm->lev3o_hm);
        if (!rdcop) return -1;
        if (rcove->versio != rdcop->versio)
            return 0x01;
    }
    //
    return 0x00;
}

int updat_rcont_versi(int rcoun, cont_versi *rcove, cont_lsmp *conda_stm) {
    OSEVPF("[FUNC]:updat_rcont_versi\n");
    contain *rdcop;
    unsigned int inde = 0x00;
    for (; rcoun > inde; ++inde, ++rcove) {
        rdcop = (contain *) cache_value(&rcove->lv4p_obid, conda_stm->lev3o_hm);
        if (!rdcop) return -1;
        if (rcove->versio != rdcop->versio)
            rcove->versio = rdcop->versio;
    }
    //
    return 0x00;
}

// rdsi

int rcontai_predica_refresh_rdsi(contain *contp, base_valu *baval, lv2pme *lv2me) {
    OSEVPF("[FUNC]:rcontai_predica_refresh_rdsi\n");
    OSEVPF("condition:|%s|\n", contp->condition);
    contain *scont;
    scont = (contain *) cache_value(&contp->refe_cove->lv4p_obid, baval->conda_stm.lev3o_hm);
    if (!scont) return -1;
    //
    oper_node *synt_head;
    char erro_msg[LINE_LENGTH];
    if (build_query_synta(&synt_head, erro_msg, contp->condition)) {
        OSEVPF("rcontai_predica_refresh_rdsi: %s\n", erro_msg);
        return -1;
    }
    //
    OSEVPF("creat_searq_plan_coulti\n");
    plan_node_ensi *querpn = CREAT_PLAN_NODE_ENSI(PLAN_ITEM_SZIE);
    if (!querpn) {
        DESTROY_STREE(synt_head);
        return -1;
    }
    if (creat_refro_plan_rdsi(querpn, contp, scont, synt_head)) {
        DESTR_PLAN_NODE_ENSI(querpn);
        DESTROY_STREE(synt_head);
        return -1;
    }
    DESTROY_STREE(synt_head);
    // PRIN_plan_node_ensi(querpn);
    int refro_valu = ephys_refeo_rcont_ensi(querpn, contp->stora_ha, baval, lv2me);
    DESTR_PLAN_NODE_ENSI(querpn);
    return refro_valu;
}

//

int rcontai_objid_refresh_rdsi(contain *contp, base_valu *baval) {
    OSEVPF("[FUNC]:rcontai_objid_refresh_rdsi\n");
    rive_ha *stora_ha = contp->stora_ha;
    riv_curso_t *rcurso;
    riv_curso_t *scurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(baval->rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&rcurso, sto_seio->seion, contp->cont_name, "raw")) {
        QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (open_refre_contai_rdsi(&scurso, contp->refe_cove, stora_ha, sto_seio, &baval->conda_stm)) {
        stora_ha->close_curso(rcurso);
        QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
        return -1;
    }
    // clear old referen entity
    while (0x00 == stora_ha->next_curso(rcurso)) {
        if (stora_ha->remove_curso(rcurso))
            break;
    }
    // stora_ha->reset_curso(rcurso);
    PK_ITEM skey;
    osv_sid_t deske_stoid;
    stora_ha->set_sid_key(scurso, &((osv_oid_i*) contp->condition)->stoid);
    if (0x00 != stora_ha->search_curso(scurso)) {
        stora_ha->close_curso(rcurso);
        close_refre_contai_rdsi(scurso, stora_ha);
        QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
        return -1;
    }
    stora_ha->get_key(scurso, &skey);
    //
    creat_objec_stoid(&deske_stoid);
    stora_ha->set_sid_key(rcurso, (uint64 *) & deske_stoid);
    stora_ha->set_value(rcurso, &skey);
    if (stora_ha->inser_curso(rcurso)) {
        stora_ha->close_curso(rcurso);
        close_refre_contai_rdsi(scurso, stora_ha);
        QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
        return -1;
    }
    // log_binary_file(robj_data, lv2me->data_size, "./binary_code.bin_f");
    //
    stora_ha->close_curso(rcurso);
    close_refre_contai_rdsi(scurso, stora_ha);
    QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
    return 0x00;
}

//

int rcontai_traver_refresh_rdsi(contain *contp, base_valu *baval) {
    OSEVPF("[FUNC]:rcontai_traver_refresh_rdsi\n");
    rive_ha *stora_ha = contp->stora_ha;
    riv_curso_t *rcurso;
    riv_curso_t *scurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(baval->rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&rcurso, sto_seio->seion, contp->cont_name, "raw")) {
        QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (open_refre_contai_rdsi(&scurso, contp->refe_cove, stora_ha, sto_seio, &baval->conda_stm)) {
        stora_ha->close_curso(rcurso);
        QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
        return -1;
    }
    // clear old referen entity
    while (0x00 == stora_ha->next_curso(rcurso)) {
        if (stora_ha->remove_curso(rcurso))
            break;
    }
    // stora_ha->reset_curso(rcurso);
    PK_ITEM skey;
    osv_sid_t deske_stoid;
    while (0x00 == stora_ha->next_curso(scurso)) {
        // OSEVPF("wt_next_curs\n");
        stora_ha->get_key(scurso, &skey);
        //
        creat_objec_stoid(&deske_stoid);
        stora_ha->set_sid_key(rcurso, (uint64 *) & deske_stoid);
        stora_ha->set_value(rcurso, &skey);
        if (stora_ha->inser_curso(rcurso)) {
            stora_ha->close_curso(rcurso);
            close_refre_contai_rdsi(scurso, stora_ha);
            QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
            return -1;
        }
        // log_binary_file(robj_data, lv2me->data_size, "./binary_code.bin_f");
    }
    //
    stora_ha->close_curso(rcurso);
    close_refre_contai_rdsi(scurso, stora_ha);
    QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
    return 0x00;
}

// rdco

int rcontai_predica_refresh_rdco(contain *contp, base_valu *baval, lv2pme *lv2me) {
    OSEVPF("[FUNC]:rcontai_predica_refresh_rdco\n");
    OSEVPF("condition:|%s|\n", contp->condition);
    contain * scont[SCONT_CONUT_ZTAI];
    if (build_source_contp(scont, &baval->conda_stm, contp->refe_cove)) {
        OSEVPF("build_source_contp\n");
        return -1;
    }
    //
    oper_node *synt_head;
    char erro_msg[LINE_LENGTH];
    if (build_query_synta(&synt_head, erro_msg, contp->condition)) {
        OSEVPF("rcontai_predica_refresh_rdco: %s\n", erro_msg);
        return -1;
    }
    //
    OSEVPF("creat_searq_plan_coulti\n");
    plan_node_enco *querpn = CREAT_PLAN_NODE_ENCO(PLAN_ITEM_SZIE);
    if (!querpn) {
        DESTROY_STREE(synt_head);
        return -1;
    }
    if (creat_refro_plan_rdco(querpn, contp, scont, synt_head)) {
        DESTR_PLAN_NODE_ENCO(querpn);
        DESTROY_STREE(synt_head);
        return -1;
    }
    DESTROY_STREE(synt_head);
    // PRIN_plan_node_enco(querpn);
    int refro_valu = ephys_refeo_rcont_enco(querpn, contp->stora_ha, baval, lv2me);
    DESTR_PLAN_NODE_ENCO(querpn);
    return refro_valu;
}

//

int rcontai_objid_refresh_rdco(contain *contp, base_valu *baval) {
    OSEVPF("[FUNC]:rcontai_objid_refresh_rdco\n");
    rive_ha *stora_ha = contp->stora_ha;
    riv_curso_t *rcurso;
    riv_curso_t *scurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(baval->rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&rcurso, sto_seio->seion, contp->cont_name, "raw")) {
        QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (open_refre_contai_rdco(&scurso, contp->refe_cove, stora_ha, sto_seio, &baval->conda_stm)) {
        stora_ha->close_curso(rcurso);
        QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
        return -1;
    }
    // clear old referen entity
    while (0x00 == stora_ha->next_curso(rcurso)) {
        if (stora_ha->remove_curso(rcurso))
            break;
    }
    // stora_ha->reset_curso(rcurso);
    PK_ITEM skey;
    osv_sid_t deske_stoid;
    stora_ha->set_sid_key(scurso, &((osv_oid_i*) contp->condition)->stoid);
    if (0x00 != stora_ha->search_curso(scurso)) {
        stora_ha->close_curso(rcurso);
        close_refre_contai_rdco(scurso, stora_ha);
        QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
        return -1;
    }
    stora_ha->get_key(scurso, &skey);
    //
    creat_objec_stoid(&deske_stoid);
    stora_ha->set_sid_key(rcurso, (uint64 *) & deske_stoid);
    stora_ha->set_value(rcurso, &skey);
    if (stora_ha->inser_curso(rcurso)) {
        stora_ha->close_curso(rcurso);
        close_refre_contai_rdco(scurso, stora_ha);
        QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
        return -1;
    }
    // log_binary_file(robj_data, lv2me->data_size, "./binary_code.bin_f");
    //
    stora_ha->close_curso(rcurso);
    close_refre_contai_rdco(scurso, stora_ha);
    QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
    return 0x00;
}

//

int rcontai_traver_refresh_rdco(contain *contp, base_valu *baval) {
    OSEVPF("[FUNC]:rcontai_traver_refresh_rdco\n");
    rive_ha *stora_ha = contp->stora_ha;
    riv_curso_t *rcurso;
    riv_curso_t *scurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(baval->rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&rcurso, sto_seio->seion, contp->cont_name, "raw")) {
        QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (open_refre_contai_rdco(&scurso, contp->refe_cove, stora_ha, sto_seio, &baval->conda_stm)) {
        stora_ha->close_curso(rcurso);
        QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
        return -1;
    }
    // clear old referen entity
    while (0x00 == stora_ha->next_curso(rcurso)) {
        if (stora_ha->remove_curso(rcurso))
            break;
    }
    // stora_ha->reset_curso(rcurso);
    PK_ITEM skey;
    osv_sid_t deske_stoid;
    while (0x00 == stora_ha->next_curso(scurso)) {
        // OSEVPF("wt_next_curs\n");
        stora_ha->get_key(scurso, &skey);
        //
        creat_objec_stoid(&deske_stoid);
        stora_ha->set_sid_key(rcurso, (uint64 *) & deske_stoid);
        stora_ha->set_value(rcurso, &skey);
        if (stora_ha->inser_curso(rcurso)) {
            stora_ha->close_curso(rcurso);
            close_refre_contai_rdco(scurso, stora_ha);
            QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
            return -1;
        }
        // log_binary_file(robj_data, lv2me->data_size, "./binary_code.bin_f");
    }
    //
    stora_ha->close_curso(rcurso);
    close_refre_contai_rdco(scurso, stora_ha);
    QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
    return 0x00;
}


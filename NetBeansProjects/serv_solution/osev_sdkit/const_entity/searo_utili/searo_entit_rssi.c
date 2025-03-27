#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "third_party.h"
#include "kcomm_header.h"

#include "cqutili.h"
#include "estri_utili.h"

#include "refresh_rcontai/close_rcont_utili.h"
#include "searo_entit_rssi.h"
#include "debug_funct_ce.h"
// #include "refere/refer_struct.h"


// teet_con:search(xx>0)|kits:pretty("oiii");
// teet_con:search(xx>0 AND ax>0)|kits:pretty("oiii");
// teet_con:search("tpp(33, 55, 77)>0")|kits:pretty("oiii");

// predicate search / condition

// rssi

int condi_const_searo_rssi(respo_ctrl *resctl, contain *contp, base_valu *baval, lv2pme *lv2me, char *condi) {
    OSEVPF("[FUNC]:condi_const_searo_rssi\n");
    OSEVPF("condition:|%s|\n", condi);
    //
    oper_node *synt_head;
    char erro_msg[LINE_LENGTH];
    if (build_query_synta(&synt_head, erro_msg, condi)) {
        OSEVPF("build_query_synta: %s\n", erro_msg);
        return -1;
    }
    //
    OSEVPF("creat_searo_plan_ensi\n");
    plan_node_ensi *querpn = CREAT_PLAN_NODE_ENSI(PLAN_ITEM_SZIE);
    if (!querpn) return -1;
    if (creat_searo_plan_resi(querpn, resctl, contp, synt_head)) {
        DESTR_PLAN_NODE_ENSI(querpn);
        // OSEVPF("--- X synt_node:%016X node_type:%u\n", synt_head, synt_head->node_type);
        DESTROY_STREE(synt_head);
        return -1;
    }
    DESTROY_STREE(synt_head);
    PRIN_plan_node(querpn);
    // physical execute
    int searo_valu = execu_physi_searo_rssi(querpn, contp, baval, lv2me);
    DESTR_PLAN_NODE_ENSI(querpn);
    return searo_valu;
}

//

int objid_const_searo_rssi(respo_ctrl *resctl, contain *contp, base_valu *baval, lv2pme *lv2me, osv_oid_i *searo_obid) {
    OSEVPF("[FUNC]:objid_const_searo_rssi\n");
    rive_ha *stora_ha = contp->stora_ha;
    riv_curso_t *rcurso;
    riv_curso_t * scurso[RCONT_CONUT_ZTAI];
    stor_seio *sto_seio = ACTIV_SESSION_BZL(baval->rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&rcurso, sto_seio->seion, contp->cont_name, "raw")) {
        QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (open_stati_contai_rssi(scurso, contp->refe_cove, stora_ha, sto_seio, lv2me, &baval->conda_stm)) {
        stora_ha->close_curso(rcurso);
        QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    osv_oid_i refe_obid;
    FILL_UNIQUE_OBID((osv_oid_i *) & refe_obid);
    uint64 data_size;
    PK_ITEM rkey, rvalu;
    stora_ha->set_sid_key(rcurso, &searo_obid->stoid);
    if (0x00 != stora_ha->search_curso(rcurso)) {
        stora_ha->close_curso(rcurso);
        close_stati_contai_rssi(scurso, stora_ha);
        QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    stora_ha->get_key(rcurso, &rkey);
    stora_ha->get_value(rcurso, &rvalu);
    STOID_BINARY_COPY(refe_obid.stoid, rkey.data)
    if (0x00 >= APPEND_DATAS(resctl->resp_stram, &refe_obid, sizeof (osv_oid_t))) {
        stora_ha->close_curso(rcurso);
        close_stati_contai_rssi(scurso, stora_ha);
        QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
        return -1;
    }
    data_size = build_object_strea_rssi(resctl->resp_stram, stora_ha, (rsent_sing *) rvalu.data, scurso[((rsent_sing *) rvalu.data)->sinde]);
    if (-1 == data_size) {
        stora_ha->close_curso(rcurso);
        close_stati_contai_rssi(scurso, stora_ha);
        QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
        return -1;
    }
    data_size += sizeof (osv_oid_t);
    FDAT_PRODUCE_TAIL(resctl, data_size)
    //
    stora_ha->close_curso(rcurso);
    close_stati_contai_rssi(scurso, stora_ha);
    QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
    return 0x00;
}

//

int trave_const_searo_rssi(respo_ctrl *resctl, contain *contp, base_valu *baval, lv2pme *lv2me) {
    OSEVPF("[FUNC]:trave_const_searo_rssi\n");
    rive_ha *stora_ha = contp->stora_ha;
    riv_curso_t *rcurso;
    riv_curso_t * scurso[RCONT_CONUT_ZTAI];
    stor_seio *sto_seio = ACTIV_SESSION_BZL(baval->rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&rcurso, sto_seio->seion, contp->cont_name, "raw")) {
        QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (open_stati_contai_rssi(scurso, contp->refe_cove, stora_ha, sto_seio, lv2me, &baval->conda_stm)) {
        stora_ha->close_curso(rcurso);
        QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    osv_oid_i refe_obid;
    FILL_UNIQUE_OBID((osv_oid_i *) & refe_obid);
    uint64 content_length = 0x00;
    int data_size;
    PK_ITEM rkey, rvalu;
    while (0x00 == stora_ha->next_curso(rcurso)) {
        // OSEVPF("wt_next_curs\n");
        stora_ha->get_key(rcurso, &rkey);
        stora_ha->get_value(rcurso, &rvalu);
        //
        STOID_BINARY_COPY(refe_obid.stoid, rkey.data)
        if (0x00 >= APPEND_DATAS(resctl->resp_stram, &refe_obid, sizeof (osv_oid_t))) {
            stora_ha->close_curso(rcurso);
            close_stati_contai_rssi(scurso, stora_ha);
            QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
            return -1;
        }
        data_size = build_object_strea_rssi(resctl->resp_stram, stora_ha, (rsent_sing *) rvalu.data, scurso[((rsent_sing *) rvalu.data)->sinde]);
        if (-1 == data_size) {
            stora_ha->close_curso(rcurso);
            close_stati_contai_rssi(scurso, stora_ha);
            QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
            return -1;
        }
        content_length += sizeof (osv_oid_t) + data_size;
        // log_binary_file(robj_data, lv2me->data_size, "./binary_code.bin_f");
    }
    FDAT_PRODUCE_TAIL(resctl, content_length)
    OSEVPF("resctl->content_length:%llu\n", resctl->content_length);
    //
    stora_ha->close_curso(rcurso);
    close_stati_contai_rssi(scurso, stora_ha);
    QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
    return 0x00;
}


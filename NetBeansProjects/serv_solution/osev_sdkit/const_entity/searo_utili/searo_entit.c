#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "third_party.h"
#include "kcomm_header.h"

#include "cqutili.h"
#include "estri_utili.h"

#include "searo_entit.h"
#include "debug_funct_ce.h"


// teet_con:search(xx>0)|kits:pretty("oiii");
// teet_con:search(xx>0 AND ax>0)|kits:pretty("oiii");
// teet_con:search("tpp(33, 55, 77)>0")|kits:pretty("oiii");

// predicate search / condition

int condi_const_searo_ensi(respo_ctrl *resctl, contain *contp, base_valu *baval, lv2pme *lv2me, char *condi) {
    OSEVPF("[FUNC]:condi_const_searo_ensi\n");
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
    if (creat_searo_plan_ensi(querpn, resctl, contp, synt_head)) {
        DESTR_PLAN_NODE_ENSI(querpn);
        // OSEVPF("--- X synt_node:%016X node_type:%u\n", synt_head, synt_head->node_type);
        DESTROY_STREE(synt_head);
        return -1;
    }
    DESTROY_STREE(synt_head);
    PRIN_plan_node(querpn);
    // physical execute
    int searo_valu = execu_physi_searo_ensi(querpn, contp->stora_ha, baval, lv2me);
    DESTR_PLAN_NODE_ENSI(querpn);
    return searo_valu;
}

//

int objid_const_searo_ensi(respo_ctrl *resctl, rive_conne *rivcon, contain *contp, lv2pme *lv2me, osv_oid_i *searo_obid) {
    OSEVPF("[FUNC]:objid_const_searo_ensi\n");
    osv_oid_t key_obid;
    FILL_UNIQUE_OBID((osv_oid_i *) & key_obid);
    //
    rive_ha *stora_ha = contp->stora_ha;
    riv_curso_t *scurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&scurso, sto_seio->seion, contp->cont_name, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    PK_ITEM key, valu;
    stora_ha->set_sid_key(scurso, &searo_obid->stoid);
    if (0x00 != stora_ha->search_curso(scurso)) {
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    stora_ha->get_key(scurso, &key);
    stora_ha->get_value(scurso, &valu);
    // dylid->solve(obje_memo, (uint64 *) key.data, &valu);
    // 0x00 >= APPEND_DATAS(resctl->resp_stram, obje_memo, dylid->data_size)
    PACKING_KEY_UNPACK(((osv_oid_i *) & key_obid)->stoid, (uint64 *) key.data);
    if (build_objec_strea_ensi(resctl->resp_stram, &key_obid, &valu)) {
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    FDAT_PRODUCE_TAIL(resctl, ftello64(resctl->resp_stram))
    //
    stora_ha->close_curso(scurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    return 0x00;
}

//

int trave_const_searo_ensi(respo_ctrl *resctl, rive_conne *rivcon, contain *contp, lv2pme *lv2me) {
    OSEVPF("[FUNC]:trave_const_searo_ensi\n");
    osv_oid_t key_obid;
    FILL_UNIQUE_OBID((osv_oid_i *) & key_obid);
    //
    rive_ha *stora_ha = contp->stora_ha;
    riv_curso_t *scurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&scurso, sto_seio->seion, contp->cont_name, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    PK_ITEM key, valu;
    while (0x00 == stora_ha->next_curso(scurso)) {
        // OSEVPF("wt_next_curs\n");
        stora_ha->get_key(scurso, &key);
        stora_ha->get_value(scurso, &valu);
        // dylid->solve(obje_memo, (uint64 *) key.data, &valu);
        // PRIN_test_object((struct test *) obje_memo);
        // 0x00 >= APPEND_DATAS(resctl->resp_stram, obje_memo, dylid->data_size)
        PACKING_KEY_UNPACK(((osv_oid_i *) & key_obid)->stoid, (uint64 *) key.data);
        if (build_objec_strea_ensi(resctl->resp_stram, &key_obid, &valu)) {
            stora_ha->close_curso(scurso);
            QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
            return -1;
        }
        // log_binary_file(obje_memo, dylid->data_size, "./binary_code.bin_f");
    }
    FDAT_PRODUCE_TAIL(resctl, ftello64(resctl->resp_stram))
    OSEVPF("resctl->content_length:%llu\n", resctl->content_length);
    //
    stora_ha->close_curso(scurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    return 0x00;
}



#include "commo_header.h"
#include "kcomm_header.h"
#include "cqutili.h"
#include "query_utili.h"
#include "rive_bzl.h"

#include "lv2p_meta.h"
#include "searq_decla_ensi.h"
#include "debug_funct/debug_funct_qc.h"

// odb:search("clasn", "conobje", "obje:numb() > 0x00");
// :search("cobje", "conobje", "obje:numb() > 0x00");
// :search("cobje", "conobje1, conobje2", "conobje1:obje:numb() > 0x00 AND conobje2:obje:numb() > 0x00");
// :search("cobje", "conobje1, conobje2", "conobje1::numb() > 0x00 AND conobje2::numb() > 0x00");
// odb:search("cobje", "conobje");
// predicate search / condition
// normal

int condi_qdecl_ensi(respo_ctrl *resctl, contain *scont, base_valu *baval, lv2pme *lv2me, char *condi) {
    OSEVPF("[FUNC]:condi_qdecl_nosi\n");
    oper_node *synt_head;
    char erro_msg[LINE_LENGTH];
    if (build_query_synta(&synt_head, erro_msg, condi)) {
        OSEVPF("condit_lv2pn_single: %s\n", erro_msg);
        return -1;
    }
    //
    OSEVPF("creat_searq_plan_coulti\n");
    plan_node_ensi *querpn = CREAT_PLAN_NODE_ENSI(PLAN_ITEM_SZIE);
    if (!querpn) {
        DESTROY_STREE(synt_head);
        return -1;
    }
    if (creat_slv2q_plan_ensi(querpn, resctl, scont, synt_head)) {
        DESTR_PLAN_NODE_ENSI(querpn);
        DESTROY_STREE(synt_head);
        return -1;
    }
    DESTROY_STREE(synt_head);
    PRIN_plan_node_ensi(querpn);
    // physical
    int searq_valu = ephys_searq_lv2pn_ensi(querpn, scont->stora_ha, baval, lv2me);
    DESTR_PLAN_NODE_ENSI(querpn);
    return searq_valu;
}

//
// parms[0x00] distance container 
// parms[0x01] source container 
// parms[0x02] object ident 

int objid_qdecl_ensi(respo_ctrl *resctl, rive_conne *rivcon, contain *scont, lv2pme *lv2me, osv_oid_i *searq_obid) {
    OSEVPF("[FUNC]:objid_qdecl_nosi\n");
    osv_oid_i key_memo[0x02];
    FILL_UNIQUE_OBID((osv_oid_t *) & key_memo[0x00]);
    //
    rive_ha *stora_ha = scont->stora_ha;
    riv_curso_t *scurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&scurso, sto_seio->seion, scont->cont_name, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // osv_oid_i key_memo;
    if (INSTAN_UNIQUE != key_memo[0x01].osev_unique) {
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    stora_ha->set_sid_key(scurso, (uint64 *) & key_memo[0x01].stoid);
    if (0x00 != stora_ha->search_curso(scurso)) {
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    creat_objec_stoid((osv_sid_t *)&(key_memo[0x00].stoid));
    if (0x00 >= APPEND_DATAS(resctl->resp_stram, key_memo, (0x02 * sizeof (osv_oid_i)))) {
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    FDAT_PRODUCE_TAIL(resctl, (0x02 * sizeof (osv_oid_i)))
    //
    stora_ha->close_curso(scurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    return 0x00;
}

//
// odb:search("taat", "tsta_con") | kits:pretty("oiii");
// odb:search("taat", "tsst_con") | kits:pretty("oiii");

int trave_qdecl_ensi(respo_ctrl *resctl, rive_conne *rivcon, contain *scont, lv2pme *lv2me) {
    OSEVPF("[FUNC]:trave_qdecl_nosi\n");
    osv_oid_i key_memo[0x02];
    FILL_UNIQUE_OBID((osv_oid_t *) & key_memo[0x00]);
    FILL_UNIQUE_OBID((osv_oid_t *) & key_memo[0x01]);
    //
    rive_ha *stora_ha = scont->stora_ha;
    riv_curso_t *scurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&scurso, sto_seio->seion, scont->cont_name, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    PK_ITEM skey;
    unsigned int inde = 0x00;
    for (; 0x00 == stora_ha->next_curso(scurso); ++inde) {
        // OSEVPF("wt_next_curs\n");
        stora_ha->get_key(scurso, &skey);
        memcpy(&(key_memo[0x01].stoid), skey.data, sizeof (osv_sid_t));
        creat_objec_stoid((osv_sid_t *)&(key_memo[0x00].stoid));
        if (0x00 >= APPEND_DATAS(resctl->resp_stram, key_memo, (0x02 * sizeof (osv_oid_i)))) {
            stora_ha->close_curso(scurso);
            QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
            return -1;
        }
        // log_binary_file(key_memo, dylid->data_size, "./binary_code.bin_f");
    }
    //
    FDAT_PRODUCE_TAIL(resctl, (0x02 * sizeof (osv_oid_i)) * inde)
    // OSEVPF("resctl->content_length:%d\n", resctl->content_length);
    stora_ha->close_curso(scurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);

    return 0x00;
}



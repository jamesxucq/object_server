
#include "commo_header.h"
#include "kcomm_header.h"
#include "cqutili.h"
#include "query_utili.h"
#include "qstri_utili.h"
#include "rive_bzl.h"

#include "searq_lv2pn_enco.h"
#include "debug_funct/debug_funct_qc.h"

//

int condi_qlv2n_enco(respo_ctrl *resctl, contain **sconp, base_valu *baval, lv2pme *lv2me, char *condi) {
    OSEVPF("[FUNC]:condi_qlv2n_enco\n");
    oper_node *synt_head;
    char erro_msg[LINE_LENGTH];
    if (build_query_synta(&synt_head, erro_msg, condi)) {
        OSEVPF("condit_lv2pn_single: %s\n", erro_msg);
        return -1;
    }
    //
    OSEVPF("creat_searq_plan_coulti\n");
    plan_node_enco *querpn = CREAT_PLAN_NODE_ENCO(PLAN_ITEM_SZIE);
    if (!querpn) {
        DESTROY_STREE(synt_head);
        return -1;
    }
    if (creat_slv2q_plan_enco(querpn, resctl, sconp, synt_head)) {
        DESTR_PLAN_NODE_ENCO(querpn);
        DESTROY_STREE(synt_head);
        return -1;
    }
    DESTROY_STREE(synt_head);
    PRIN_plan_node_enco(querpn);
    // physical
    int searq_valu = ephys_searq_lv2pn_enco(querpn, sconp[0x00]->stora_ha, baval, lv2me);
    DESTR_PLAN_NODE_ENCO(querpn);
    return searq_valu;
}

//

int objid_qlv2n_enco(respo_ctrl *resctl, rive_conne *rivcon, contain **sconp, lv2pme *lv2me, osv_oid_i *searq_obid) {
    OSEVPF("[FUNC]:objid_qlv2n_enco\n");
    osv_oid_i key_memo[0x03];
    FILL_UNIQUE_OBID((osv_oid_t *) & key_memo[0x00]);
    FILL_UNIQUE_OBID((osv_oid_t *) & key_memo[0x01]);
    FILL_UNIQUE_OBID((osv_oid_t *) & key_memo[0x02]);
    //
    rive_ha *stora_ha = sconp[0x00]->stora_ha;
    riv_curso_t *scurso1, *scurso2;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&scurso1, sto_seio->seion, sconp[0x00]->cont_name, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (stora_ha->open_curso_cont(&scurso2, sto_seio->seion, sconp[0x01]->cont_name, "raw")) {
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    if (INSTAN_UNIQUE != key_memo[0x01].osev_unique) {
        stora_ha->close_curso(scurso2);
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (INSTAN_UNIQUE != key_memo[0x02].osev_unique) {
        stora_ha->close_curso(scurso2);
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    stora_ha->set_sid_key(scurso1, (uint64 *) & key_memo[0x01].stoid);
    if (0x00 != stora_ha->search_curso(scurso1)) {
        stora_ha->close_curso(scurso2);
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    stora_ha->set_sid_key(scurso2, (uint64 *) & key_memo[0x02].stoid);
    if (0x00 != stora_ha->search_curso(scurso2)) {
        stora_ha->close_curso(scurso2);
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    creat_objec_stoid((osv_sid_t *)&(key_memo[0x00].stoid));
    if (0x00 >= APPEND_DATAS(resctl->resp_stram, key_memo, (0x03 * sizeof (osv_oid_i)))) {
        stora_ha->close_curso(scurso2);
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    FDAT_PRODUCE_TAIL(resctl, (0x03 * sizeof (osv_oid_i)))
    //
    stora_ha->close_curso(scurso2);
    stora_ha->close_curso(scurso1);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    return 0x00;
}

//

static int trave_secon_curso(respo_ctrl *resctl, riv_curso_t *scurso2, rive_ha *stora_ha, osv_oid_i *key_memo) {
    PK_ITEM skey2;
    unsigned int inde = 0x00;
    stora_ha->reset_curso(scurso2);
    for (; 0x00 == stora_ha->next_curso(scurso2); ++inde) {
        // OSEVPF("wt_next_curs\n");
        stora_ha->get_key(scurso2, &skey2);
        memcpy(&(key_memo[0x02].stoid), skey2.data, sizeof (osv_sid_t));
        creat_objec_stoid((osv_sid_t *)&(key_memo[0x00].stoid));
        if (0x00 >= APPEND_DATAS(resctl->resp_stram, key_memo, (0x03 * sizeof (osv_oid_i)))) {
            return -1;
        }
        // log_binary_file(key_memo, dylid->data_size, "./binary_code.bin_f");
    }
    //
    return inde;
}

// odb:search("taat", "tsst_con, taat_con") | kits:pretty("oiii");

int trave_qlv2n_enco(respo_ctrl *resctl, rive_conne *rivcon, contain **sconp, lv2pme *lv2me) {
    OSEVPF("[FUNC]:trave_qlv2n_enco\n");
    osv_oid_i key_memo[0x03];
    FILL_UNIQUE_OBID((osv_oid_t *) & key_memo[0x00]);
    FILL_UNIQUE_OBID((osv_oid_t *) & key_memo[0x01]);
    FILL_UNIQUE_OBID((osv_oid_t *) & key_memo[0x02]);
    //
    rive_ha *stora_ha = sconp[0x00]->stora_ha;
    riv_curso_t *scurso1, *scurso2;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&scurso1, sto_seio->seion, sconp[0x00]->cont_name, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (stora_ha->open_curso_cont(&scurso2, sto_seio->seion, sconp[0x01]->cont_name, "raw")) {
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    PK_ITEM skey1;
    int trav_inde;
    unsigned int inde = 0x00;
    while (0x00 == stora_ha->next_curso(scurso1)) {
        // OSEVPF("wt_next_curs\n");
        stora_ha->get_key(scurso1, &skey1);
        memcpy(&(key_memo[0x01].stoid), skey1.data, sizeof (osv_sid_t));
        if (0x00 > (trav_inde = trave_secon_curso(resctl, scurso2, stora_ha, key_memo))) {
            stora_ha->close_curso(scurso2);
            stora_ha->close_curso(scurso1);
            QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
            return -1;
        }
        inde += trav_inde;
        // log_binary_file(key_memo, dylid->data_size, "./binary_code.bin_f");
    }
    FDAT_PRODUCE_TAIL(resctl, (0x03 * sizeof (osv_oid_i)) * inde)
    // OSEVPF("resctl->content_length:%d\n", resctl->content_length);
    stora_ha->close_curso(scurso2);
    stora_ha->close_curso(scurso1);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    return 0x00;
}




#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "third_party.h"
#include "kcomm_header.h"

#include "cqutili.h"
#include "estri_utili.h"

#include "searo_entit_rsco.h"
#include "debug_funct_ce.h"


// teet_con:search(xx>0)|kits:pretty("oiii");
// teet_con:search(xx>0 AND ax>0)|kits:pretty("oiii");
// teet_con:search("tpp(33, 55, 77)>0")|kits:pretty("oiii");

// predicate search / condition

int condi_const_searo_rsco(respo_ctrl *resctl, contain *contp, base_valu *baval, lv2pme *lv2me, char *condi) {
    OSEVPF("[FUNC]:condi_const_searo_rsco\n");
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
    plan_node_enco *querpn = CREAT_PLAN_NODE_ENCO(PLAN_ITEM_SZIE);
    if (!querpn) return -1;
    if (creat_searo_plan_reco(querpn, resctl, &contp, synt_head)) {
        DESTR_PLAN_NODE_ENCO(querpn);
        // OSEVPF("--- X synt_node:%016X node_type:%u\n", synt_head, synt_head->node_type);
        DESTROY_STREE(synt_head);
        return -1;
    }
    DESTROY_STREE(synt_head);
    // PRIN_plan_node(querpn);
    // physical execute
    int searo_valu = execu_physi_searo_rsco(querpn, contp, baval, lv2me);
    DESTR_PLAN_NODE_ENCO(querpn);
    return searo_valu;
}

//

/*
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
 */
int objid_const_searo_rsco(respo_ctrl *resctl, contain *contp, base_valu *baval, lv2pme *lv2me, osv_oid_i *searo_obid) {
    OSEVPF("[FUNC]:objid_const_searo_rsco\n");
    osv_oid_i robj_data[SCONT_CONUT_ZTAI];
    init_static_robj((void *) robj_data, contp->refe_coun);
    //
    rive_ha *stora_ha = contp->stora_ha;
    riv_curso_t *rcurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(baval->rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&rcurso, sto_seio->seion, contp->cont_name, "raw")) {
        QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    uint64 data_size = contp->refe_coun * sizeof (osv_oid_t);
    PK_ITEM skey, svalu;
    stora_ha->set_sid_key(rcurso, &searo_obid->stoid);
    if (0x00 != stora_ha->search_curso(rcurso)) {
        stora_ha->close_curso(rcurso);
        QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    stora_ha->get_key(rcurso, &skey);
    stora_ha->get_value(rcurso, &svalu);
    static_unpack_tab[contp->refe_coun]((void *) robj_data, &skey, &svalu);
    if (0x00 >= APPEND_DATAS(resctl->resp_stram, robj_data, data_size)) {
        stora_ha->close_curso(rcurso);
        QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
        return -1;
    }
    FDAT_PRODUCE_TAIL(resctl, data_size)
    //
    stora_ha->close_curso(rcurso);
    QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
    return 0x00;
}

//

/*
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
 */
int trave_const_searo_rsco(respo_ctrl *resctl, contain *contp, base_valu *baval, lv2pme *lv2me) {
    OSEVPF("[FUNC]:trave_const_searo_rsco\n");
    osv_oid_i robj_data[SCONT_CONUT_ZTAI];
    init_static_robj((void *) robj_data, contp->refe_coun);
    int (*rsobje_unpack)(void *, PK_ITEM *, PK_ITEM *);
    rsobje_unpack = static_unpack_tab[contp->refe_coun];
    //
    rive_ha *stora_ha = contp->stora_ha;
    riv_curso_t *rcurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(baval->rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&rcurso, sto_seio->seion, contp->cont_name, "raw")) {
        QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    uint64 data_size = contp->refe_coun * sizeof (osv_oid_t);
    PK_ITEM skey, svalu;
    unsigned int inde = 0x00;
    for (; 0x00 == stora_ha->next_curso(rcurso); ++inde) {
        // OSEVPF("wt_next_curs\n");
        stora_ha->get_key(rcurso, &skey);
        stora_ha->get_value(rcurso, &svalu);
        rsobje_unpack((void *) robj_data, &skey, &svalu);
        if (0x00 >= APPEND_DATAS(resctl->resp_stram, robj_data, data_size)) {
            stora_ha->close_curso(rcurso);
            QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
            return -1;
        }
        // log_binary_file(robj_data, lv2me->data_size, "./binary_code.bin_f");
    }
    FDAT_PRODUCE_TAIL(resctl, data_size * inde)
    OSEVPF("resctl->content_length:%llu\n", resctl->content_length);
    //
    stora_ha->close_curso(rcurso);
    QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
    return 0x00;
}




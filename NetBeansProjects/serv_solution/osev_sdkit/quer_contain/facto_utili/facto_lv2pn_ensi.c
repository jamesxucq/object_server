
#include "commo_header.h"
#include "kcomm_header.h"

#include "cqutili.h"
#include "query_utili.h"
#include "rive_bzl.h"

#include "facto_lv2pn_ensi.h"
#include "debug_funct/debug_funct_qc.h"
#include "debug_funct_co.h"
#include "lv2p_meta.h"
#include "kcomm_struct.h"

// odb:factory("clasn", "conobje", "obje:numb() > 0x00");
// :factory("cobje", "conobje", "obje:numb() > 0x00");
// :factory("cobje", "conobje1, conobje2", "conobje1:obje:numb() > 0x00 AND conobje2:obje:numb() > 0x00");
// :factory("cobje", "conobje1, conobje2", "conobje1::numb() > 0x00 AND conobje2::numb() > 0x00");
// odb:factory("cobje", "conobje");
// predicate factory / condition

// ensi

int condi_flv2n_ensi(respo_ctrl *resctl, contain *scont, base_valu *baval, lv2pme **lv2mep, char *condi) {
    OSEVPF("[FUNC]:condi_flv2n_ensi\n");
    oper_node *synt_head;
    char erro_msg[LINE_LENGTH];
    if (build_query_synta(&synt_head, erro_msg, condi)) {
        OSEVPF("condit_lv2pn_single: %s\n", erro_msg);
        return -1;
    }
    //
    OSEVPF("creat_facto_plan_coulti\n");
    plan_node_ensi *querpn = CREAT_PLAN_NODE_ENSI(PLAN_ITEM_SZIE);
    if (!querpn) {
        DESTROY_STREE(synt_head);
        return -1;
    }
    if (creat_flv2q_plan_ensi(querpn, resctl, scont, synt_head)) {
        DESTR_PLAN_NODE_ENSI(querpn);
        DESTROY_STREE(synt_head);
        return -1;
    }
    DESTROY_STREE(synt_head);
    PRIN_plan_node_ensi(querpn);
    // physical
    int facto_valu = ephys_facto_lv2pn_ensi(querpn, scont->stora_ha, baval, lv2mep);
    DESTR_PLAN_NODE_ENSI(querpn);
    return facto_valu;
}

//
// parms[0x00] distance container 
// parms[0x01] source container 
// parms[0x02] object ident 

int objid_flv2n_ensi(respo_ctrl *resctl, rive_conne *rivcon, contain *scont, lv2pme **lv2mep, osv_oid_i *facto_obid) {
    OSEVPF("[FUNC]:objid_flv2n_ensi\n");
    char field_str[LVTNOD_LENGTH];
    if (field_lv2me_ensi(field_str, lv2mep))
        return -1;
    OSEVPF("field_str:|%s|\n", field_str);
    osv_oid_t key_obid;
    FILL_UNIQUE_OBID((osv_oid_i *) & key_obid);
    //
    rive_ha *stora_ha = scont->stora_ha;
    riv_curso_t *scurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_prop(&scurso, sto_seio->seion, scont->cont_name, field_str, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    if (INSTAN_UNIQUE != facto_obid[0x00].osev_unique) {
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    PK_ITEM svalu;
    stora_ha->set_sid_key(scurso, (uint64 *) & facto_obid[0x00].stoid);
    if (0x00 != stora_ha->search_curso(scurso)) {
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    stora_ha->get_value(scurso, &svalu);
    //
    osv_sid_t deske_stoid;
    creat_objec_stoid(&deske_stoid);
    // dylid->solve(obje_memo, (uint64 *) & deske_stoid, &svalu);
    // 0x00 >= APPEND_DATAS(resctl->resp_stram, obje_memo, dylid->data_size)
    PACKING_KEY_UNPACK(((osv_oid_i *) & key_obid)->stoid, (uint64 *) & deske_stoid);
    if (build_objec_strea_ensi(resctl->resp_stram, &key_obid, &svalu)) {
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
// odb:factory("taat", "tsta_con") | kits:pretty("iii");

int trave_flv2n_ensi(respo_ctrl *resctl, rive_conne *rivcon, contain *scont, lv2pme **lv2mep) {
    OSEVPF("[FUNC]:trave_flv2n_ensi\n");
    char field_str[LVTNOD_LENGTH];
    if (field_lv2me_ensi(field_str, lv2mep))
        return -1;
    // OSEVPF("field_str:|%s|\n", field_str);
    osv_oid_t key_obid;
    FILL_UNIQUE_OBID((osv_oid_i *) & key_obid);
    //
    rive_ha *stora_ha = scont->stora_ha;
    riv_curso_t *scurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_prop(&scurso, sto_seio->seion, scont->cont_name, field_str, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    osv_sid_t deske_stoid;
    PK_ITEM svalu;
    unsigned int inde = 0x00;
    for (; 0x00 == stora_ha->next_curso(scurso); ++inde) {
        // OSEVPF("wt_next_curs\n");
        stora_ha->get_value(scurso, &svalu);
        creat_objec_stoid(&deske_stoid);
        // dylid->solve(obje_memo, (uint64 *) & deske_stoid, &svalu);
        // 0x00 >= APPEND_DATAS(resctl->resp_stram, obje_memo, dylid->data_size)
        PACKING_KEY_UNPACK(((osv_oid_i *) & key_obid)->stoid, (uint64 *) & deske_stoid);
        if (build_objec_strea_ensi(resctl->resp_stram, &key_obid, &svalu)) {
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

// enob

int condi_flv2n_enob(respo_ctrl *resctl, contain *scont, base_valu *baval, lv2pme **lv2mep, char *condi) {
    OSEVPF("[FUNC]:condi_flv2n_enob  \n");
    oper_node *synt_head;
    char erro_msg[LINE_LENGTH];
    if (build_query_synta(&synt_head, erro_msg, condi)) {
        OSEVPF("condit_lv2pn_single: %s\n", erro_msg);
        return -1;
    }
    //
    OSEVPF("creat_facto_plan_coulti\n");
    plan_node_ensi *querpn = CREAT_PLAN_NODE_ENSI(PLAN_ITEM_SZIE);
    if (!querpn) {
        DESTROY_STREE(synt_head);
        return -1;
    }
    if (creat_flv2q_plan_ensi(querpn, resctl, scont, synt_head)) {
        DESTR_PLAN_NODE_ENSI(querpn);
        DESTROY_STREE(synt_head);
        return -1;
    }
    DESTROY_STREE(synt_head);
    PRIN_plan_node_ensi(querpn);
    // physical
    int facto_valu = ephys_facto_lv2pn_enob(querpn, scont->stora_ha, baval, lv2mep);
    DESTR_PLAN_NODE_ENSI(querpn);
    return facto_valu;
}

//
// parms[0x00] distance container 
// parms[0x01] source container 
// parms[0x02] object ident 

int objid_flv2n_enob(respo_ctrl *resctl, rive_conne *rivcon, contain *scont, lv2pme **lv2mep, osv_oid_i *facto_obid) {
    OSEVPF("[FUNC]:objid_flv2n_enob  \n");
    osv_oid_t key_obid;
    FILL_UNIQUE_OBID((osv_oid_i *) & key_obid);
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
    if (INSTAN_UNIQUE != facto_obid[0x00].osev_unique) {
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    PK_ITEM svalu;
    stora_ha->set_sid_key(scurso, (uint64 *) & facto_obid[0x00].stoid);
    if (0x00 != stora_ha->search_curso(scurso)) {
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    stora_ha->get_value(scurso, &svalu);
    //
    osv_sid_t deske_stoid;
    creat_objec_stoid(&deske_stoid);
    // dylid->solve(obje_memo, (uint64 *) & deske_stoid, &svalu);
    // 0x00 >= APPEND_DATAS(resctl->resp_stram, obje_memo, dylid->data_size)
    PACKING_KEY_UNPACK(((osv_oid_i *) & key_obid)->stoid, (uint64 *) & deske_stoid);
    if (build_objec_strea_enob(resctl->resp_stram, &key_obid, &svalu)) {
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
// odb:factory("taat", "tsta_con") | kits:pretty("iii");

int trave_flv2n_enob(respo_ctrl *resctl, rive_conne *rivcon, contain *scont, lv2pme **lv2mep) {
    OSEVPF("[FUNC]:trave_flv2n_enob  \n");
    osv_oid_t key_obid;
    FILL_UNIQUE_OBID((osv_oid_i *) & key_obid);
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
    osv_sid_t deske_stoid;
    PK_ITEM svalu;
    unsigned int inde = 0x00;
    for (; 0x00 == stora_ha->next_curso(scurso); ++inde) {
        // OSEVPF("wt_next_curs\n");
        stora_ha->get_value(scurso, &svalu);
        creat_objec_stoid(&deske_stoid);
        // dylid->solve(obje_memo, (uint64 *) & deske_stoid, &svalu);
        // 0x00 >= APPEND_DATAS(resctl->resp_stram, obje_memo, dylid->data_size)
        PACKING_KEY_UNPACK(((osv_oid_i *) & key_obid)->stoid, (uint64 *) & deske_stoid);
        if (build_objec_strea_enob(resctl->resp_stram, &key_obid, &svalu)) {
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


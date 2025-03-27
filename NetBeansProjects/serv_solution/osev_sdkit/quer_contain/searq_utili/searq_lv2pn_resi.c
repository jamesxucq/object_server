
#include "commo_header.h"
#include "kcomm_header.h"
#include "cqutili.h"
#include "query_utili.h"
#include "rive_bzl.h"

#include "searq_lv2pn_resi.h"
#include "debug_funct/debug_funct_qc.h"
#include "debug_funct_co.h"
#include "kcomm_struct.h"

// odb:search("clasn", "conobje", "obje:numb() > 0x00");
// :search("cobje", "conobje", "obje:numb() > 0x00");
// :search("cobje", "conobje1, conobje2", "conobje1:obje:numb() > 0x00 AND conobje2:obje:numb() > 0x00");
// :search("cobje", "conobje1, conobje2", "conobje1::numb() > 0x00 AND conobje2::numb() > 0x00");
// odb:search("cobje", "conobje");
// predicate search / condition

int condi_qlv2n_resi(respo_ctrl *resctl, contain *scont, contain *rcont, base_valu *baval, lv2pme **lv2mep, char *condi) {
    OSEVPF("[FUNC]:condi_qlv2n_resi\n");
    oper_node *synt_head;
    char erro_msg[LINE_LENGTH];
    if (build_query_synta(&synt_head, erro_msg, condi)) {
        OSEVPF("condi_qlv2n_resi: %s\n", erro_msg);
        return -1;
    }
    //
    OSEVPF("creat_searq_plan_coulti\n");
    plan_node_ensi *querpn = CREAT_PLAN_NODE_ENSI(PLAN_ITEM_SZIE);
    if (!querpn) {
        DESTROY_STREE(synt_head);
        return -1;
    }
    if (creat_slv2q_plan_resi(querpn, resctl, scont, rcont, synt_head)) {
        DESTR_PLAN_NODE_ENSI(querpn);
        DESTROY_STREE(synt_head);
        return -1;
    }
    DESTROY_STREE(synt_head);
    PRIN_plan_node_resi(querpn);
    // physical
    int searq_valu = ephys_searq_lv2pn_resi(querpn, scont->stora_ha, baval, lv2mep);
    DESTR_PLAN_NODE_ENSI(querpn);
    return searq_valu;
}

//
// parms[0x00] distance container 
// parms[0x01] source container 
// parms[0x02] object ident 

static int find_refer_obid_ensi(PK_ITEM *skey, riv_curso_t *scurso, rive_ha *stora_ha, osv_oid_i *refer_obid) {
    stora_ha->reset_curso(scurso);
    PK_ITEM svalu;
    while (0x00 == stora_ha->next_curso(scurso)) {
        // OSEVPF("wt_next_curs\n");
        stora_ha->get_value(scurso, &svalu);
        if (refer_obid->stoid == ((unsigned long long *) svalu.data)[0x00]) {
            stora_ha->get_key(scurso, skey);
            return 0x00;
        }
    }
    //
    return -1;
}

int objid_qlv2n_resi(respo_ctrl *resctl, rive_conne *rivcon, contain *scont, contain *rcont, lv2pme **lv2mep, osv_oid_i *searq_obid) {
    OSEVPF("[FUNC]:objid_qlv2n_resi\n");
    char field_str[LVTNOD_LENGTH];
    if (field_lv2me_ensi(field_str, lv2mep))
        return -1;
    OSEVPF("field_str:|%s|\n", field_str);
    osv_oid_t key_obid;
    FILL_UNIQUE_OBID((osv_oid_i *) & key_obid);
    //
    rive_ha *stora_ha = scont->stora_ha;
    riv_curso_t *rcurso, *scurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&scurso, sto_seio->seion, scont->cont_name, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (stora_ha->open_curso_prop(&rcurso, sto_seio->seion, rcont->cont_name, field_str, "raw")) {
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    if (INSTAN_UNIQUE != searq_obid[0x00].osev_unique) {
        stora_ha->close_curso(rcurso);
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    PK_ITEM skey;
    if (find_refer_obid_ensi(&skey, scurso, stora_ha, &searq_obid[0x00])) {
        stora_ha->close_curso(rcurso);
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    PK_ITEM rvalu;
    stora_ha->set_sid_key(rcurso, (uint64 *) & searq_obid[0x00].stoid);
    if (0x00 != stora_ha->search_curso(rcurso)) {
        stora_ha->close_curso(rcurso);
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    stora_ha->get_value(rcurso, &rvalu);
    // dylid->solve(obje_memo, (uint64 *) skey.data, &rvalu);
    // 0x00 >= APPEND_DATAS(resctl->resp_stram, obje_memo, dylid->data_size)
    PACKING_KEY_UNPACK(((osv_oid_i *) & key_obid)->stoid, (uint64 *) skey.data);
    if (build_objec_strea_ensi(resctl->resp_stram, &key_obid, &rvalu)) {
        stora_ha->close_curso(rcurso);
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    FDAT_PRODUCE_TAIL(resctl, ftello64(resctl->resp_stram))
    //
    stora_ha->close_curso(rcurso);
    stora_ha->close_curso(scurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    return 0x00;
}

//
// odb:search("taat", "tsta_con") | kits:pretty("oiii");
// odb:search("taat", "tsst_con") | kits:pretty("oiii");

int trave_qlv2n_resi(respo_ctrl *resctl, rive_conne *rivcon, contain *scont, contain *rcont, lv2pme **lv2mep) {
    OSEVPF("[FUNC]:trave_qlv2n_resi\n");
    char field_str[LVTNOD_LENGTH];
    if (field_lv2me_ensi(field_str, lv2mep))
        return -1;
    OSEVPF("field_str:|%s|\n", field_str);
    osv_oid_t key_obid;
    FILL_UNIQUE_OBID((osv_oid_i *) & key_obid);
    //
    rive_ha *stora_ha = scont->stora_ha;
    riv_curso_t *rcurso, *scurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&scurso, sto_seio->seion, scont->cont_name, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (stora_ha->open_curso_prop(&rcurso, sto_seio->seion, rcont->cont_name, field_str, "raw")) {
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    PK_ITEM skey, svalu, rvalu;
    while (0x00 == stora_ha->next_curso(scurso)) {
        // OSEVPF("wt_next_curs\n");
        stora_ha->get_key(scurso, &skey);
        stora_ha->get_value(scurso, &svalu);
        stora_ha->set_key(rcurso, &svalu);
        PRIN_stoid_stri(svalu.data, svalu.size);
        if (0x00 != stora_ha->search_curso(rcurso)) {
            stora_ha->close_curso(rcurso);
            stora_ha->close_curso(scurso);
            QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
            return -1;
        }
        stora_ha->get_value(rcurso, &rvalu);
        // dylid->solve(obje_memo, (uint64 *) skey.data, &rvalu);
        // PRIN_test_object((struct test *) obje_memo);
        // 0x00 >= APPEND_DATAS(resctl->resp_stram, obje_memo, dylid->data_size)
        PACKING_KEY_UNPACK(((osv_oid_i *) & key_obid)->stoid, (uint64 *) skey.data);
        if (build_objec_strea_ensi(resctl->resp_stram, &key_obid, &rvalu)) {
            stora_ha->close_curso(rcurso);
            stora_ha->close_curso(scurso);
            QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
            return -1;
        }
        // log_binary_file(obje_memo, dylid->data_size, "./binary_code.bin_f");
    }
    FDAT_PRODUCE_TAIL(resctl, ftello64(resctl->resp_stram))
    // OSEVPF("resctl->content_length:%d\n", resctl->content_length);
    stora_ha->close_curso(rcurso);
    stora_ha->close_curso(scurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    return 0x00;
}

//

int objid_qlv2n_oresi(respo_ctrl *resctl, rive_conne *rivcon, contain *rcont, lv2pme **lv2mep, osv_oid_i *searq_obid) {
    OSEVPF("[FUNC]:objid_qlv2n_oresi\n");
    char field_str[LVTNOD_LENGTH];
    if (field_lv2me_ensi(field_str, lv2mep))
        return -1;
    OSEVPF("field_str:|%s|\n", field_str);
    osv_oid_t key_obid;
    FILL_UNIQUE_OBID((osv_oid_i *) & key_obid);
    //
    rive_ha *stora_ha = rcont->stora_ha;
    riv_curso_t *rcurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_prop(&rcurso, sto_seio->seion, rcont->cont_name, field_str, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    if (INSTAN_UNIQUE != searq_obid[0x01].osev_unique) {
        stora_ha->close_curso(rcurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    PK_ITEM rvalu;
    stora_ha->set_sid_key(rcurso, (uint64 *) & searq_obid[0x01].stoid);
    if (0x00 != stora_ha->search_curso(rcurso)) {
        stora_ha->close_curso(rcurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    stora_ha->get_value(rcurso, &rvalu);
    // dylid->solve(obje_memo, &searq_obid[0x00].stoid, &rvalu);
    // 0x00 >= APPEND_DATAS(resctl->resp_stram, obje_memo, dylid->data_size)
    PACKING_KEY_UNPACK(((osv_oid_i *) & key_obid)->stoid, (uint64 *) & searq_obid[0x00].stoid);
    if (build_objec_strea_ensi(resctl->resp_stram, &key_obid, &rvalu)) {
        stora_ha->close_curso(rcurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    FDAT_PRODUCE_TAIL(resctl, ftello64(resctl->resp_stram))
    //
    stora_ha->close_curso(rcurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    return 0x00;
}


#include "commo_header.h"
#include "kcomm_header.h"
#include "cqutili.h"
#include "query_utili.h"
#include "qstri_utili.h"
#include "lv2p_meta.h"
#include "rive_bzl.h"

#include "searq_lv2pn_reco.h"
#include "debug_funct_co.h"
#include "debug_funct/debug_funct_qc.h"
#include "kcomm_struct.h"
//

int condi_qlv2n_reco(respo_ctrl *resctl, contain *scont, contain **rconp, base_valu *baval, lv2pme **lv2mep, char *condi) {
    OSEVPF("[FUNC]:condi_qlv2n_reco\n");
    oper_node *synt_head;
    char erro_msg[LINE_LENGTH];
    if (build_query_synta(&synt_head, erro_msg, condi)) {
        OSEVPF("condi_qlv2n_reco: %s\n", erro_msg);
        return -1;
    }
    //
    OSEVPF("creat_searq_plan_coulti\n");
    plan_node_enco *querpn = CREAT_PLAN_NODE_ENCO(PLAN_ITEM_SZIE);
    if (!querpn) {
        DESTROY_STREE(synt_head);
        return -1;
    }
    if (creat_slv2q_plan_reco(querpn, resctl, scont, rconp, lv2mep, synt_head)) {
        DESTR_PLAN_NODE_ENCO(querpn);
        DESTROY_STREE(synt_head);
        return -1;
    }
    DESTROY_STREE(synt_head);
    PRIN_plan_node_reco(querpn);
    // physical
    int searq_valu = ephys_searq_lv2pn_reco(querpn, rconp[0x00]->stora_ha, baval, lv2mep);
    DESTR_PLAN_NODE_ENCO(querpn);
    return searq_valu;
}

//

static int find_refer_obid_enco(PK_ITEM *skey, riv_curso_t *scurso, rive_ha *stora_ha, osv_oid_i *refer_obid1, osv_oid_i *refer_obid2) {
    stora_ha->reset_curso(scurso);
    PK_ITEM svalu;
    while (0x00 == stora_ha->next_curso(scurso)) {
        // OSEVPF("wt_next_curs\n");
        stora_ha->get_value(scurso, &svalu);
        if (refer_obid1->stoid == ((unsigned long long *) svalu.data)[0x00]
                && refer_obid2->stoid == ((unsigned long long *) (svalu.data + sizeof (unsigned long long)))[0x00]) {
            stora_ha->get_key(scurso, skey);
            return 0x00;
        }
    }
    //
    return -1;
}

//

int objid_qlv2n_reco(respo_ctrl *resctl, rive_conne *rivcon, contain *scont, contain **rconp, lv2pme **lv2mep, osv_oid_i *searq_obid) {
    OSEVPF("[FUNC]:objid_qlv2n_reco\n");
    field_resul_co fieres;
    if (fires_lv2pn_type_enco(&fieres, lv2mep))
        return -1;
    PRIN_field_resul_enco(&fieres);
    //
    PK_ITEM kient;
    if (!pkite_mallo(&kient, fieres.data_size))
        return -1;
    FILL_UNIQUE_OBID((osv_oid_i *) kient.data);
    //
    rive_ha *stora_ha = scont->stora_ha;
    riv_curso_t *scurso, *rcurso1, *rcurso2;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) {
        FREE_KITE(&kient);
        return -1;
    }
    if (stora_ha->open_curso_prop(&rcurso1, sto_seio->seion, rconp[0x00]->cont_name, fieres.field_str1, "raw")) {
        FREE_KITE(&kient);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (stora_ha->open_curso_prop(&rcurso2, sto_seio->seion, rconp[0x01]->cont_name, fieres.field_str2, "raw")) {
        FREE_KITE(&kient);
        stora_ha->close_curso(rcurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (stora_ha->open_curso_cont(&scurso, sto_seio->seion, rconp[0x01]->cont_name, "raw")) {
        FREE_KITE(&kient);
        stora_ha->close_curso(rcurso2);
        stora_ha->close_curso(rcurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    if (INSTAN_UNIQUE != searq_obid[0x00].osev_unique) {
        FREE_KITE(&kient);
        stora_ha->close_curso(scurso);
        stora_ha->close_curso(rcurso2);
        stora_ha->close_curso(rcurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (INSTAN_UNIQUE != searq_obid[0x01].osev_unique) {
        FREE_KITE(&kient);
        stora_ha->close_curso(scurso);
        stora_ha->close_curso(rcurso2);
        stora_ha->close_curso(rcurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    PK_ITEM skey;
    if (find_refer_obid_enco(&skey, scurso, stora_ha, &searq_obid[0x00], &searq_obid[0x01])) {
        FREE_KITE(&kient);
        stora_ha->close_curso(scurso);
        stora_ha->close_curso(rcurso2);
        stora_ha->close_curso(rcurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    PK_ITEM rvalu1, rvalu2;
    stora_ha->set_sid_key(rcurso1, (uint64 *) & searq_obid[0x00].stoid);
    if (0x00 != stora_ha->search_curso(rcurso1)) {
        FREE_KITE(&kient);
        stora_ha->close_curso(scurso);
        stora_ha->close_curso(rcurso2);
        stora_ha->close_curso(rcurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    stora_ha->get_value(rcurso1, &rvalu1);
    stora_ha->set_sid_key(rcurso2, (uint64 *) & searq_obid[0x01].stoid);
    if (0x00 != stora_ha->search_curso(rcurso2)) {
        FREE_KITE(&kient);
        stora_ha->close_curso(scurso);
        stora_ha->close_curso(rcurso2);
        stora_ha->close_curso(rcurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    stora_ha->get_value(rcurso2, &rvalu2);
    // PASS_OBIDEN_SECTI(kient.data)
    PACKING_KEY_UNPACK(((osv_oid_i *) kient.data)->stoid, skey.data);
    if (fieres.fixed_float_co) {
        if (reall_objec_pkite(&kient, &rvalu1, &rvalu2)) {
            FREE_KITE(&kient);
            stora_ha->close_curso(scurso);
            stora_ha->close_curso(rcurso2);
            stora_ha->close_curso(rcurso1);
            QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
            return -1;
        }
    }
    if (build_proje_strea_enco(resctl->resp_stram, &kient, &rvalu1, &rvalu2, &fieres)) {
        FREE_KITE(&kient);
        stora_ha->close_curso(scurso);
        stora_ha->close_curso(rcurso2);
        stora_ha->close_curso(rcurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    FDAT_PRODUCE_TAIL(resctl, ftello64(resctl->resp_stram))
    //
    FREE_KITE(&kient);
    stora_ha->close_curso(scurso);
    stora_ha->close_curso(rcurso2);
    stora_ha->close_curso(rcurso1);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    return 0x00;
}

//
#define BUILD_REFER_OBJEC(ERRO_LINE, RESCTL, RCURSOO, RCURSOT, FIRES, STORA_HA, LVTMEP, SKEY, SVALU, OBJE_NODE) { \
    PK_ITEM rvalu1, rvalu2; \
    STORA_HA->set_sid_key(RCURSOO, (unsigned long long *) (unsigned long long *) ((SVALU)->data)); \
    if (0x00 != STORA_HA->search_curso(RCURSOO)) \
        goto ERRO_LINE; \
    STORA_HA->get_value(RCURSOO, &rvalu1); \
    STORA_HA->set_sid_key(RCURSOT, (unsigned long long *) ((SVALU)->data + sizeof (osv_sid_t))); \
    if (0x00 != STORA_HA->search_curso(RCURSOT)) \
        goto ERRO_LINE; \
    STORA_HA->get_value(RCURSOT, &rvalu2); \
    PACKING_KEY_UNPACK(((osv_oid_i *) (OBJE_NODE)->data)->stoid, (uint64 *) (SKEY)->data); \
    if ((FIRES)->fixed_float_co) { \
        if (reall_objec_pkite(OBJE_NODE, &rvalu1, &rvalu2)) \
            goto ERRO_LINE; \
    } \
    if (build_proje_strea_enco(RESCTL->resp_stram, OBJE_NODE, &rvalu1, &rvalu2, FIRES)) { \
        goto ERRO_LINE; \
    } \
}

//

int trave_qlv2n_reco(respo_ctrl *resctl, rive_conne *rivcon, contain *scont, contain **rconp, lv2pme **lv2mep) {
    OSEVPF("[FUNC]:trave_qlv2n_reco\n");
    field_resul_co fieres;
    if (fires_lv2pn_type_enco(&fieres, lv2mep))
        return -1;
    PRIN_field_resul_enco(&fieres);
    //
    PK_ITEM kient;
    if (!pkite_mallo(&kient, fieres.data_size))
        return -1;
    FILL_UNIQUE_OBID((osv_oid_i *) kient.data);
    //
    rive_ha *stora_ha = scont->stora_ha;
    riv_curso_t *scurso, *rcurso1, *rcurso2;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) {
        FREE_KITE(&kient);
        return -1;
    }
    if (stora_ha->open_curso_prop(&rcurso1, sto_seio->seion, rconp[0x00]->cont_name, fieres.field_str1, "raw")) {
        FREE_KITE(&kient);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (stora_ha->open_curso_prop(&rcurso2, sto_seio->seion, rconp[0x01]->cont_name, fieres.field_str2, "raw")) {
        FREE_KITE(&kient);
        stora_ha->close_curso(rcurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (stora_ha->open_curso_cont(&scurso, sto_seio->seion, rconp[0x01]->cont_name, "raw")) {
        FREE_KITE(&kient);
        stora_ha->close_curso(rcurso2);
        stora_ha->close_curso(rcurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    PK_ITEM skey, svalu;
    while (0x00 == stora_ha->next_curso(scurso)) {
        // OSEVPF("wt_next_curs\n");
        stora_ha->get_key(scurso, &skey);
        stora_ha->get_value(scurso, &svalu);
        BUILD_REFER_OBJEC(erro_line, resctl, &rcurso1, &rcurso2, &fieres, stora_ha, lv2mep, &skey, &svalu, &kient);
        // log_binary_file(kient, dylid->data_size, "./binary_code.bin_f");
    }
    FDAT_PRODUCE_TAIL(resctl, ftello64(resctl->resp_stram))
    // OSEVPF("resctl->content_length:%d\n", resctl->content_length);
    FREE_KITE(&kient);
    stora_ha->close_curso(scurso);
    stora_ha->close_curso(rcurso2);
    stora_ha->close_curso(rcurso1);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    return 0x00;
erro_line:
    FREE_KITE(&kient);
    stora_ha->close_curso(scurso);
    stora_ha->close_curso(rcurso2);
    stora_ha->close_curso(rcurso1);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    return -1;
}

//

int objid_qlv2n_oreco(respo_ctrl *resctl, rive_conne *rivcon, contain **rconp, lv2pme **lv2mep, osv_oid_i *searq_obid) {
    OSEVPF("[FUNC]:objid_qlv2n_oreco\n");
    field_resul_co fieres;
    if (fires_lv2pn_type_enco(&fieres, lv2mep))
        return -1;
    PRIN_field_resul_enco(&fieres);
    //
    PK_ITEM kient;
    if (!pkite_mallo(&kient, fieres.data_size))
        return -1;
    FILL_UNIQUE_OBID((osv_oid_i *) kient.data);
    //
    rive_ha *stora_ha = rconp[0x00]->stora_ha;
    riv_curso_t *rcurso1, *rcurso2;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) {
        FREE_KITE(&kient);
        return -1;
    }
    if (stora_ha->open_curso_prop(&rcurso1, sto_seio->seion, rconp[0x00]->cont_name, fieres.field_str1, "raw")) {
        FREE_KITE(&kient);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (stora_ha->open_curso_prop(&rcurso2, sto_seio->seion, rconp[0x01]->cont_name, fieres.field_str2, "raw")) {
        FREE_KITE(&kient);
        stora_ha->close_curso(rcurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    if (INSTAN_UNIQUE != searq_obid[0x01].osev_unique) {
        FREE_KITE(&kient);
        stora_ha->close_curso(rcurso2);
        stora_ha->close_curso(rcurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (INSTAN_UNIQUE != searq_obid[0x02].osev_unique) {
        FREE_KITE(&kient);
        stora_ha->close_curso(rcurso2);
        stora_ha->close_curso(rcurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    PK_ITEM rvalu1, rvalu2;
    stora_ha->set_sid_key(rcurso1, (uint64 *) & searq_obid[0x01].stoid);
    if (0x00 != stora_ha->search_curso(rcurso1)) {
        FREE_KITE(&kient);
        stora_ha->close_curso(rcurso2);
        stora_ha->close_curso(rcurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    stora_ha->get_value(rcurso1, &rvalu1);
    stora_ha->set_sid_key(rcurso2, (uint64 *) & searq_obid[0x02].stoid);
    if (0x00 != stora_ha->search_curso(rcurso2)) {
        FREE_KITE(&kient);
        stora_ha->close_curso(rcurso2);
        stora_ha->close_curso(rcurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    stora_ha->get_value(rcurso2, &rvalu2);
    // PASS_OBIDEN_SECTI(kient.data)
    PACKING_KEY_UNPACK(((osv_oid_i *) kient.data)->stoid, &searq_obid[0x00].stoid);
    if (fieres.fixed_float_co) {
        if (reall_objec_pkite(&kient, &rvalu1, &rvalu2)) {
            FREE_KITE(&kient);
            stora_ha->close_curso(rcurso2);
            stora_ha->close_curso(rcurso1);
            QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
            return -1;
        }
    }
    if (build_proje_strea_enco(resctl->resp_stram, &kient, &rvalu1, &rvalu2, &fieres)) {
        FREE_KITE(&kient);
        stora_ha->close_curso(rcurso2);
        stora_ha->close_curso(rcurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    FDAT_PRODUCE_TAIL(resctl, ftello64(resctl->resp_stram))
    //
    FREE_KITE(&kient);
    stora_ha->close_curso(rcurso2);
    stora_ha->close_curso(rcurso1);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    return 0x00;
}


#include "commo_header.h"
#include "kcomm_header.h"

#include "cqutili.h"
#include "query_utili.h"
#include "qstri_utili.h"
#include "lv2p_meta.h"
#include "rive_bzl.h"

#include "facto_lv2pn_enco.h"
#include "debug_funct/debug_funct_qc.h"
#include "debug_funct_co.h"
#include "kcomm_struct.h"
//

int condi_flv2n_enco(respo_ctrl *resctl, contain **sconp, base_valu *baval, lv2pme **lv2mep, char *condi) {
    OSEVPF("[FUNC]:condi_flv2n_enco\n");
    oper_node *synt_head;
    char erro_msg[LINE_LENGTH];
    if (build_query_synta(&synt_head, erro_msg, condi)) {
        OSEVPF("condit_lv2pn_single: %s\n", erro_msg);
        return -1;
    }
    //
    OSEVPF("creat_facto_plan_coulti\n");
    plan_node_enco *querpn = CREAT_PLAN_NODE_ENCO(PLAN_ITEM_SZIE);
    if (!querpn) return -1;
    if (creat_flv2q_plan_enco(querpn, resctl, sconp, lv2mep, synt_head)) {
        DESTR_PLAN_NODE_ENCO(querpn);
        DESTROY_STREE(synt_head);
        return -1;
    }
    DESTROY_STREE(synt_head);
    PRIN_plan_node_enco(querpn);
    // physical
    int facto_valu = ephys_facto_lv2pn_enco(querpn, sconp[0x00]->stora_ha, baval, lv2mep);
    DESTR_PLAN_NODE_ENCO(querpn);
    return facto_valu;
}

//

int objid_flv2n_enco(respo_ctrl *resctl, rive_conne *rivcon, contain **sconp, lv2pme **lv2mep, osv_oid_i *facto_obid) {
    OSEVPF("[FUNC]:objid_flv2n_enco\n");
    field_resul_co fieres;
    if (fires_lv2pn_type_enco(&fieres, lv2mep))
        return -1;
    PRIN_field_resul_enco(&fieres);
    //
    PK_ITEM kient;
    if (!pkite_mallo(&kient, fieres.data_size))
        return -1;
    FILL_UNIQUE_OBID((osv_oid_t *) kient.data);
    //
    rive_ha *stora_ha = sconp[0x00]->stora_ha;
    riv_curso_t *scurso1, *scurso2;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) {
        FREE_KITE(&kient);
        return -1;
    }
    if (stora_ha->open_curso_prop(&scurso1, sto_seio->seion, sconp[0x00]->cont_name, fieres.field_str1, "raw")) {
        FREE_KITE(&kient);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (stora_ha->open_curso_prop(&scurso2, sto_seio->seion, sconp[0x01]->cont_name, fieres.field_str2, "raw")) {
        FREE_KITE(&kient);
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    if (INSTAN_UNIQUE != facto_obid[0x00].osev_unique) {
        FREE_KITE(&kient);
        stora_ha->close_curso(scurso2);
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (INSTAN_UNIQUE != facto_obid[0x01].osev_unique) {
        FREE_KITE(&kient);
        stora_ha->close_curso(scurso2);
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    PK_ITEM svalu1, svalu2;
    stora_ha->set_sid_key(scurso1, (uint64 *) & facto_obid[0x00].stoid);
    if (0x00 != stora_ha->search_curso(scurso1)) {
        FREE_KITE(&kient);
        stora_ha->close_curso(scurso2);
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    stora_ha->get_value(scurso1, &svalu1);
    stora_ha->set_sid_key(scurso2, (uint64 *) & facto_obid[0x01].stoid);
    if (0x00 != stora_ha->search_curso(scurso2)) {
        FREE_KITE(&kient);
        stora_ha->close_curso(scurso2);
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    stora_ha->get_value(scurso2, &svalu2);
    // PASS_OBIDEN_SECTI(kient.data)
    creat_objec_stoid((osv_sid_t *)&((osv_oid_i *) kient.data)->stoid);
    if (fieres.fixed_float_co) {
        if (reall_objec_pkite(&kient, &svalu1, &svalu2)) {
            FREE_KITE(&kient);
            stora_ha->close_curso(scurso2);
            stora_ha->close_curso(scurso1);
            QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
            return -1;
        }
    }
    if (build_proje_strea_enco(resctl->resp_stram, &kient, &svalu1, &svalu2, &fieres)) {
        FREE_KITE(&kient);
        stora_ha->close_curso(scurso2);
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    FDAT_PRODUCE_TAIL(resctl, ftello64(resctl->resp_stram))
    //
    FREE_KITE(&kient);
    stora_ha->close_curso(scurso2);
    stora_ha->close_curso(scurso1);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    return 0x00;
}

//

static inline int trave_secon_curso(respo_ctrl *resctl, PK_ITEM *svalu1, riv_curso_t *scurso2, field_resul_co *fieres, rive_ha *stora_ha, PK_ITEM *kient) {
    PK_ITEM svalu2;
    // osv_sid_t deske_stoid;
    stora_ha->reset_curso(scurso2);
    while (0x00 == stora_ha->next_curso(scurso2)) {
        // OSEVPF("wt_next_curs\n");
        stora_ha->get_value(scurso2, &svalu2);
        // PASS_OBIDEN_SECTI(kient->data)
        creat_objec_stoid((osv_sid_t *)&((osv_oid_i *) kient->data)->stoid);
        if (fieres->fixed_float_co) {
            if (reall_objec_pkite(kient, svalu1, &svalu2))
                return -1;
        }
        if (build_proje_strea_enco(resctl->resp_stram, kient, svalu1, &svalu2, fieres)) {
            return -1;
        }
        // log_binary_file(key_memo, dylid->data_size, "./binary_code.bin_f");
    }
    //
    return 0x00;
}

//

int trave_flv2n_enco(respo_ctrl *resctl, rive_conne *rivcon, contain **sconp, lv2pme **lv2mep) {
    OSEVPF("[FUNC]:trave_flv2n_enco\n");
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
    rive_ha *stora_ha = sconp[0x00]->stora_ha;
    riv_curso_t *scurso1, *scurso2;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) {
        FREE_KITE(&kient);
        return -1;
    }
    if (stora_ha->open_curso_prop(&scurso1, sto_seio->seion, sconp[0x00]->cont_name, fieres.field_str1, "raw")) {
        FREE_KITE(&kient);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (stora_ha->open_curso_prop(&scurso2, sto_seio->seion, sconp[0x01]->cont_name, fieres.field_str2, "raw")) {
        FREE_KITE(&kient);
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    PK_ITEM svalu1;
    while (0x00 == stora_ha->next_curso(scurso1)) {
        // OSEVPF("wt_next_curs\n");
        stora_ha->get_value(scurso1, &svalu1);
        if (trave_secon_curso(resctl, &svalu1, scurso2, &fieres, stora_ha, &kient)) {
            FREE_KITE(&kient);
            stora_ha->close_curso(scurso2);
            stora_ha->close_curso(scurso1);
            QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
            return -1;
        }
        // log_binary_file(kient, dylid->data_size, "./binary_code.bin_f");
    }
    FDAT_PRODUCE_TAIL(resctl, ftello64(resctl->resp_stram))
    OSEVPF("resctl->content_length:%llu\n", resctl->content_length);
    FREE_KITE(&kient);
    stora_ha->close_curso(scurso2);
    stora_ha->close_curso(scurso1);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    return 0x00;
}

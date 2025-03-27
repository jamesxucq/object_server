
#include "commo_header.h"
#include "kcomm_header.h"
#include "cqutili.h"
#include "query_utili.h"

#include "facto_conta_ensi.h"
#include "debug_funct/debug_funct_qc.h"
#include "debug_funct_co.h"

// ensi

// odb:factory("clasn", "conobje", "obje:numb() > 0x00");
// :factory("cobje", "conobje", "obje:numb() > 0x00");
// :factory("cobje", "conobje1, conobje2", "conobje1:obje:numb() > 0x00 AND conobje2:obje:numb() > 0x00");
// :factory("cobje", "conobje1, conobje2", "conobje1::numb() > 0x00 AND conobje2::numb() > 0x00");
// odb:factory("cobje", "conobje");
// predicate factory / condition

int condi_fcont_ensi(respo_ctrl *resctl, contain *dcont, contain *scont, base_valu *baval, lv2pme **lv2mep, char *condi) {
    OSEVPF("[FUNC]:condi_fcont_ensi\n");
    oper_node *synt_head;
    char erro_msg[LINE_LENGTH];
    if (build_query_synta(&synt_head, erro_msg, condi)) {
        OSEVPF("condi_fcont_ensi: %s\n", erro_msg);
        return -1;
    }
    //
    OSEVPF("creat_facto_plan_coulti\n");
    plan_node_ensi *querpn = CREAT_PLAN_NODE_ENSI(PLAN_ITEM_SZIE);
    if (!querpn) return -1;
    if (creat_fconq_plan_ensi(querpn, resctl, dcont, scont, synt_head)) {
        DESTR_PLAN_NODE_ENSI(querpn);
        DESTROY_STREE(synt_head);
        return -1;
    }
    DESTROY_STREE(synt_head);
    PRIN_plan_node_ensi(querpn);
    // physical
    int facto_valu = ephys_facto_conta_ensi(querpn, dcont->stora_ha, baval, lv2mep);
    DESTR_PLAN_NODE_ENSI(querpn);
    return facto_valu;
}

// odb:search("taat", "txxt_con") | kits:pretty("oiii");
// odb:factory("txxt_con", "tsta_con", "bf7f65dee501622d2e700000");
// parms[0x00] distance container 
// parms[0x01] source container 
// parms[0x02] object ident 

int objid_fcont_ensi(respo_ctrl *resctl, rive_conne *rivcon, contain *dcont, contain *scont, lv2pme **lv2mep, osv_oid_i *facto_obid) {
    OSEVPF("[FUNC]:objid_fcont_ensi\n");
    char field_str[LVTNOD_LENGTH];
    if (field_lv2me_ensi(field_str, lv2mep))
        return -1;
    OSEVPF("field_str:|%s|\n", field_str);
    //
    rive_ha *stora_ha = dcont->stora_ha;
    riv_curso_t *dcurso, *scurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_prop(&scurso, sto_seio->seion, scont->cont_name, field_str, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (stora_ha->open_curso_cont(&dcurso, sto_seio->seion, dcont->cont_name, "raw")) {
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    if (INSTAN_UNIQUE != facto_obid[0x00].osev_unique) {
        stora_ha->close_curso(dcurso);
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    PK_ITEM svalu;
    stora_ha->set_sid_key(scurso, (uint64 *) & facto_obid[0x00].stoid);
    if (0x00 != stora_ha->search_curso(scurso)) {
        stora_ha->close_curso(dcurso);
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    stora_ha->get_value(scurso, &svalu);
    //
    osv_sid_t deske_stoid;
    creat_objec_stoid(&deske_stoid);
    stora_ha->set_sid_key(dcurso, (uint64 *) & deske_stoid);
    stora_ha->set_value(dcurso, &svalu);
    if (stora_ha->inser_curso(dcurso)) {
        stora_ha->close_curso(dcurso);
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    FDAT_PRODUCE_TAIL(resctl, 0x00)
    //
    stora_ha->close_curso(dcurso);
    stora_ha->close_curso(scurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    return 0x00;
}

//

// odb:factory("taat", "txxt_con") | kits:pretty("iii");
// odb:factory("txxt_con", "tsta_con");

int trave_fcont_ensi(respo_ctrl *resctl, rive_conne *rivcon, contain *dcont, contain *scont, lv2pme **lv2mep) {
    OSEVPF("[FUNC]:trave_fcont_ensi\n");
    char field_str[LVTNOD_LENGTH];
    if (field_lv2me_ensi(field_str, lv2mep))
        return -1;
    OSEVPF("field_str:|%s|\n", field_str);
    //
    rive_ha *stora_ha = dcont->stora_ha;
    riv_curso_t *dcurso, *scurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_prop(&scurso, sto_seio->seion, scont->cont_name, field_str, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (stora_ha->open_curso_cont(&dcurso, sto_seio->seion, dcont->cont_name, "raw")) {
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    osv_sid_t deske_stoid;
    PK_ITEM svalu;
    while (0x00 == stora_ha->next_curso(scurso)) {
        // OSEVPF("wt_next_curs\n");
        stora_ha->get_value(scurso, &svalu);
        // p_stoid_stri((osv_sid_t *) skey.data, skey.size);
        creat_objec_stoid(&deske_stoid);
        stora_ha->set_sid_key(dcurso, (uint64 *) & deske_stoid);
        stora_ha->set_value(dcurso, &svalu);
        if (stora_ha->inser_curso(dcurso)) {
            stora_ha->close_curso(dcurso);
            stora_ha->close_curso(scurso);
            QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
            return -1;
        }
        // log_binary_file(obje_data, dylid->data_size, "./binary_code.bin_f");
    }
    FDAT_PRODUCE_TAIL(resctl, 0x00)
    //
    stora_ha->close_curso(dcurso);
    stora_ha->close_curso(scurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    return 0x00;
}

// enob

int condi_fcont_enob(respo_ctrl *resctl, contain *dcont, contain *scont, base_valu *baval, lv2pme **lv2mep, char *condi) {
    OSEVPF("[FUNC]:condi_fcont_enob\n");
    oper_node *synt_head;
    char erro_msg[LINE_LENGTH];
    if (build_query_synta(&synt_head, erro_msg, condi)) {
        OSEVPF("condi_fcont_enob: %s\n", erro_msg);
        return -1;
    }
    //
    OSEVPF("creat_facto_plan_coulti\n");
    plan_node_ensi *querpn = CREAT_PLAN_NODE_ENSI(PLAN_ITEM_SZIE);
    if (!querpn) return -1;
    if (creat_fconq_plan_ensi(querpn, resctl, dcont, scont, synt_head)) {
        DESTR_PLAN_NODE_ENSI(querpn);
        DESTROY_STREE(synt_head);
        return -1;
    }
    DESTROY_STREE(synt_head);
    PRIN_plan_node_ensi(querpn);
    // physical
    int facto_valu = ephys_facto_conta_enob(querpn, dcont->stora_ha, baval, lv2mep);
    DESTR_PLAN_NODE_ENSI(querpn);
    return facto_valu;
}

// odb:search("taat", "txxt_con") | kits:pretty("oiii");
// odb:factory("txxt_con", "tsta_con", "bf7f65dee501622d2e700000");
// parms[0x00] distance container 
// parms[0x01] source container 
// parms[0x02] object ident 

int objid_fcont_enob(respo_ctrl *resctl, rive_conne *rivcon, contain *dcont, contain *scont, lv2pme **lv2mep, osv_oid_i *facto_obid) {
    OSEVPF("[FUNC]:objid_fcont_enob\n");
    rive_ha *stora_ha = dcont->stora_ha;
    riv_curso_t *dcurso, *scurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&scurso, sto_seio->seion, scont->cont_name, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (stora_ha->open_curso_cont(&dcurso, sto_seio->seion, dcont->cont_name, "raw")) {
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    if (INSTAN_UNIQUE != facto_obid[0x00].osev_unique) {
        stora_ha->close_curso(dcurso);
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    PK_ITEM svalu;
    stora_ha->set_sid_key(scurso, (uint64 *) & facto_obid[0x00].stoid);
    if (0x00 != stora_ha->search_curso(scurso)) {
        stora_ha->close_curso(dcurso);
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    stora_ha->get_value(scurso, &svalu);
    //
    osv_sid_t deske_stoid;
    creat_objec_stoid(&deske_stoid);
    stora_ha->set_sid_key(dcurso, (uint64 *) & deske_stoid);
    stora_ha->set_value(dcurso, &svalu);
    if (stora_ha->inser_curso(dcurso)) {
        stora_ha->close_curso(dcurso);
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    FDAT_PRODUCE_TAIL(resctl, 0x00)
    //
    stora_ha->close_curso(dcurso);
    stora_ha->close_curso(scurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    return 0x00;
}

//

// odb:factory("taat", "txxt_con") | kits:pretty("iii");
// odb:factory("txxt_con", "tsta_con");

int trave_fcont_enob(respo_ctrl *resctl, rive_conne *rivcon, contain *dcont, contain *scont, lv2pme **lv2mep) {
    OSEVPF("[FUNC]:trave_fcont_enob\n");
    rive_ha *stora_ha = dcont->stora_ha;
    riv_curso_t *dcurso, *scurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&scurso, sto_seio->seion, scont->cont_name, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (stora_ha->open_curso_cont(&dcurso, sto_seio->seion, dcont->cont_name, "raw")) {
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    osv_sid_t deske_stoid;
    PK_ITEM svalu;
    while (0x00 == stora_ha->next_curso(scurso)) {
        // OSEVPF("wt_next_curs\n");
        stora_ha->get_value(scurso, &svalu);
        // p_stoid_stri((osv_sid_t *) skey.data, skey.size);
        creat_objec_stoid(&deske_stoid);
        stora_ha->set_sid_key(dcurso, (uint64 *) & deske_stoid);
        stora_ha->set_value(dcurso, &svalu);
        if (stora_ha->inser_curso(dcurso)) {
            stora_ha->close_curso(dcurso);
            stora_ha->close_curso(scurso);
            QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
            return -1;
        }
        // log_binary_file(obje_data, dylid->data_size, "./binary_code.bin_f");
    }
    FDAT_PRODUCE_TAIL(resctl, 0x00)
    //
    stora_ha->close_curso(dcurso);
    stora_ha->close_curso(scurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    return 0x00;
}









#include "commo_header.h"
#include "kcomm_header.h"
#include "cqutili.h"
#include "query_utili.h"
#include "qstri_utili.h"
#include "lv2p_meta.h"

#include "debug_funct_co.h"
#include "facto_conta_enco.h"
#include "debug_funct/debug_funct_qc.h"
#include "kcomm_struct.h"
#include "paki_memo.h"

//

int condi_fcont_enco(respo_ctrl *resctl, contain *dcont, contain **sconp, base_valu *baval, lv2pme **lv2mep, char *condi) {
    OSEVPF("[FUNC]:condi_fcont_enco\n");
    oper_node *synt_head;
    char erro_msg[LINE_LENGTH];
    if (build_query_synta(&synt_head, erro_msg, condi)) {
        OSEVPF("condi_fcont_ensi: %s\n", erro_msg);
        return -1;
    }
    //
    OSEVPF("creat_facto_plan_coulti\n");
    plan_node_enco *querpn = CREAT_PLAN_NODE_ENCO(PLAN_ITEM_SZIE);
    if (!querpn) return -1;
    if (creat_fconq_plan_enco(querpn, resctl, dcont, sconp, lv2mep, synt_head)) {
        DESTR_PLAN_NODE_ENCO(querpn);
        DESTROY_STREE(synt_head);
        return -1;
    }
    DESTROY_STREE(synt_head);
    PRIN_plan_node_enco(querpn);
    // physical
    int facto_valu = ephys_facto_conta_enco(querpn, dcont->stora_ha, baval, lv2mep);
    DESTR_PLAN_NODE_ENCO(querpn);
    return facto_valu;
}

//

int objid_fcont_enco(respo_ctrl *resctl, rive_conne *rivcon, contain *dcont, contain **sconp, lv2pme **lv2mep, osv_oid_i *facto_obid) {
    OSEVPF("[FUNC]:objid_fcont_enco\n");
    field_resul_co fieres;
    if (fires_lv2pn_item_enco(&fieres, lv2mep))
        return -1;
    PRIN_field_resul_enco(&fieres);
    //
    rive_ha *stora_ha = sconp[0x00]->stora_ha;
    riv_curso_t *dcurso, *scurso1, *scurso2;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_prop(&scurso1, sto_seio->seion, sconp[0x00]->cont_name, fieres.field_str1, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (stora_ha->open_curso_prop(&scurso2, sto_seio->seion, sconp[0x01]->cont_name, fieres.field_str2, "raw")) {
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (stora_ha->open_curso_cont(&dcurso, sto_seio->seion, dcont->cont_name, "raw")) {
        stora_ha->close_curso(scurso2);
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    if (INSTAN_UNIQUE != facto_obid[0x00].osev_unique) {
        stora_ha->close_curso(dcurso);
        stora_ha->close_curso(scurso2);
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (INSTAN_UNIQUE != facto_obid[0x01].osev_unique) {
        stora_ha->close_curso(dcurso);
        stora_ha->close_curso(scurso2);
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    PK_ITEM svalu1, svalu2;
    stora_ha->set_sid_key(scurso1, (uint64 *) & facto_obid[0x00].stoid);
    if (0x00 != stora_ha->search_curso(scurso1)) {
        stora_ha->close_curso(dcurso);
        stora_ha->close_curso(scurso2);
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    stora_ha->get_value(scurso1, &svalu1);
    stora_ha->set_sid_key(scurso2, (uint64 *) & facto_obid[0x01].stoid);
    if (0x00 != stora_ha->search_curso(scurso2)) {
        stora_ha->close_curso(dcurso);
        stora_ha->close_curso(scurso2);
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    stora_ha->get_value(scurso2, &svalu2);
    //
    osv_sid_t deske_stoid;
    creat_objec_stoid((osv_sid_t *) & deske_stoid);
    stora_ha->set_sid_key(dcurso, (uint64 *) & deske_stoid);
    paki_memo_t objnod;
    if (!pkmem_mallo(&objnod, svalu1.size + svalu2.size)) {
        stora_ha->close_curso(dcurso);
        stora_ha->close_curso(scurso2);
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    build_proje_objec_enco(&objnod, &svalu1, &svalu2, &fieres);
    stora_ha->set_value(dcurso, &objnod.item);
    if (stora_ha->inser_curso(dcurso)) {
        FREE_PAKI(&objnod);
        stora_ha->close_curso(dcurso);
        stora_ha->close_curso(scurso2);
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    FDAT_PRODUCE_TAIL(resctl, 0x00)
    //
    FREE_PAKI(&objnod);
    stora_ha->close_curso(dcurso);
    stora_ha->close_curso(scurso2);
    stora_ha->close_curso(scurso1);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    return 0x00;
}

//

static int trave_secon_curso(riv_curso_t *dcurso, paki_memo_t *objnod, PK_ITEM *svalu1, riv_curso_t *scurso2, field_resul_co *fieres, rive_ha *stora_ha) {
    PK_ITEM svalu2;
    osv_sid_t deske_stoid;
    stora_ha->reset_curso(scurso2);
    while (0x00 == stora_ha->next_curso(scurso2)) {
        // OSEVPF("wt_next_curs\n");
        stora_ha->get_value(scurso2, &svalu2);
        creat_objec_stoid((osv_sid_t *) & deske_stoid);
        stora_ha->set_sid_key(dcurso, (uint64 *) & deske_stoid);
        if (fieres->fixed_float_co) {
            if (reall_objec_pkmem(objnod, svalu1, &svalu2))
                return -1;
        }
        build_proje_objec_enco(objnod, svalu1, &svalu2, fieres);
        stora_ha->set_value(dcurso, &objnod->item);
        if (stora_ha->inser_curso(dcurso))
            return -1;
        // log_binary_file(key_memo, dylid->data_size, "./binary_code.bin_f");
    }
    //
    return 0x00;
}

//

int trave_fcont_enco(respo_ctrl *resctl, rive_conne *rivcon, contain *dcont, contain **sconp, lv2pme **lv2mep) {
    OSEVPF("[FUNC]:trave_fcont_enco\n");
    field_resul_co fieres;
    if (fires_lv2pn_item_enco(&fieres, lv2mep))
        return -1;
    PRIN_field_resul_enco(&fieres);
    //
    rive_ha *stora_ha = sconp[0x00]->stora_ha;
    riv_curso_t *dcurso, *scurso1, *scurso2;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_prop(&scurso1, sto_seio->seion, sconp[0x00]->cont_name, fieres.field_str1, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (stora_ha->open_curso_prop(&scurso2, sto_seio->seion, sconp[0x01]->cont_name, fieres.field_str2, "raw")) {
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (stora_ha->open_curso_cont(&dcurso, sto_seio->seion, dcont->cont_name, "raw")) {
        stora_ha->close_curso(scurso2);
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    PK_ITEM svalu1;
    paki_memo_t objnod;
    if (!pkmem_mallo(&objnod, fieres.data_size)) {
        stora_ha->close_curso(dcurso);
        stora_ha->close_curso(scurso2);
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    while (0x00 == stora_ha->next_curso(scurso1)) {
        // OSEVPF("wt_next_curs\n");
        stora_ha->get_value(scurso1, &svalu1);
        if (trave_secon_curso(dcurso, &objnod, &svalu1, scurso2, &fieres, stora_ha)) {
            FREE_PAKI(&objnod);
            stora_ha->close_curso(dcurso);
            stora_ha->close_curso(scurso2);
            stora_ha->close_curso(scurso1);
            QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
            return -1;
        }
        // log_binary_file(obje_data, dylid->data_size, "./binary_code.bin_f");
    }
    FDAT_PRODUCE_TAIL(resctl, 0x00)
    OSEVPF("resctl->content_length:%llu\n", resctl->content_length);
    FREE_PAKI(&objnod);
    stora_ha->close_curso(dcurso);
    stora_ha->close_curso(scurso2);
    stora_ha->close_curso(scurso1);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    return 0x00;
}




#include "commo_header.h"
#include "kcomm_header.h"
#include "cqutili.h"
#include "query_utili.h"
#include "qstri_utili.h"
#include "conattr.h"

#include "searq_conta_ensi.h"
#include "searq_conta_enco.h"
#include "debug_funct/debug_funct_qc.h"
#include "stati_scont.h"
// #include "refere/refer_struct.h"

//

int condi_qcont_enco(respo_ctrl *resctl, contain *dcont, stati_scont *scont, base_valu *baval, lv2pme *lv2me, char *condi) {
    OSEVPF("[FUNC]:condi_qcont_enco\n");
    oper_node *synt_head;
    char erro_msg[LINE_LENGTH];
    if (build_query_synta(&synt_head, erro_msg, condi)) {
        OSEVPF("condi_qcont_enco: %s\n", erro_msg);
        return -1;
    }
    //
    OSEVPF("creat_searq_plan_coulti\n");
    plan_node_enco *querpn = CREAT_PLAN_NODE_ENCO(PLAN_ITEM_SZIE);
    if (!querpn) {
        DESTROY_STREE(synt_head);
        return -1;
    }
    if (creat_sconq_plan_enco(querpn, resctl, dcont, scont, synt_head)) {
        DESTR_PLAN_NODE_ENCO(querpn);
        DESTROY_STREE(synt_head);
        return -1;
    }
    DESTROY_STREE(synt_head);
    PRIN_plan_node_enco(querpn);
    // physical
    int searq_valu = ephys_searq_conta_enco(querpn, dcont->stora_ha, baval, lv2me);
    DESTR_PLAN_NODE_ENCO(querpn);
    return searq_valu;
}

//

int objid_qcont_enco(respo_ctrl *resctl, rive_conne *rivcon, contain *dcont, stati_scont *scont, osv_oid_i *searq_obid) {
    OSEVPF("[FUNC]:objid_qcont_enco\n");
    rive_ha *stora_ha = dcont->stora_ha;
    riv_curso_t *dcurso, *scurso1, *scurso2;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&scurso1, sto_seio->seion, (scont)->cont_name, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (stora_ha->open_curso_cont(&scurso2, sto_seio->seion, (++scont)->cont_name, "raw")) {
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (stora_ha->open_curso_cont(&dcurso, sto_seio->seion, dcont->cont_name, "raw")) {
        stora_ha->close_curso(scurso1);
        stora_ha->close_curso(scurso2);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    if (INSTAN_UNIQUE != searq_obid[0x00].osev_unique) {
        stora_ha->close_curso(dcurso);
        stora_ha->close_curso(scurso2);
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (INSTAN_UNIQUE != searq_obid[0x01].osev_unique) {
        stora_ha->close_curso(dcurso);
        stora_ha->close_curso(scurso2);
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    stora_ha->set_sid_key(scurso1, (uint64 *) & searq_obid[0x00].stoid);
    if (0x00 != stora_ha->search_curso(scurso1)) {
        stora_ha->close_curso(dcurso);
        stora_ha->close_curso(scurso2);
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    stora_ha->set_sid_key(scurso2, (uint64 *) & searq_obid[0x01].stoid);
    if (0x00 != stora_ha->search_curso(scurso2)) {
        stora_ha->close_curso(dcurso);
        stora_ha->close_curso(scurso2);
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    osv_sid_t deske_stoid;
    creat_objec_stoid(&deske_stoid);
    stora_ha->set_sid_key(dcurso, (uint64 *) & deske_stoid);
    osv_sid_t desv_memo[0x02];
    PK_ITEM kient;
    kient.data = (void *) desv_memo;
    kient.size = (0x02 * sizeof (osv_sid_t));
    memcpy((void *) kient.data, &searq_obid[0x00].stoid, sizeof (osv_sid_t));
    memcpy(sizeof (osv_sid_t) + (void *) kient.data, &searq_obid[0x01].stoid, sizeof (osv_sid_t));
    stora_ha->set_value(dcurso, &kient);
    if (stora_ha->inser_curso(dcurso)) {
        stora_ha->close_curso(dcurso);
        stora_ha->close_curso(scurso2);
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    FDAT_PRODUCE_TAIL(resctl, 0x00)
    //
    stora_ha->close_curso(dcurso);
    stora_ha->close_curso(scurso2);
    stora_ha->close_curso(scurso1);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    return 0x00;
}

//

static int trave_secon_curso(riv_curso_t *dcurso, rsent_coup *desv_memo, riv_curso_t *scurso2, rive_ha *stora_ha) {
    osv_sid_t deske_stoid;
    PK_ITEM kient;
    kient.data = (void *) desv_memo;
    kient.size = sizeof (rsent_coup);
    //
    PK_ITEM rkey2;
    stora_ha->reset_curso(scurso2);
    while (0x00 == stora_ha->next_curso(scurso2)) {
        // OSEVPF("wt_next_curs\n");
        stora_ha->get_key(scurso2, &rkey2);
        // paki_struct_pack((void *) kient.data, (0x02 * sizeof (osv_sid_t)), "RR", ((int64_t *) skey1->data)[0x00], ((int64_t *) skey1->data)[0x01]);
        desv_memo->senti2 = ((osv_sid_i *) rkey2.data)[0x00];
        //
        creat_objec_stoid(&deske_stoid);
        stora_ha->set_sid_key(dcurso, (uint64 *) & deske_stoid);
        stora_ha->set_value(dcurso, &kient);
        if (stora_ha->inser_curso(dcurso)) {
            return -1;
        }
        // log_binary_file(obje_data, dylid->data_size, "./binary_code.bin_f");
    }
    //
    return 0x00;
}

//

int trave_qcont_enco(respo_ctrl *resctl, rive_conne *rivcon, contain *dcont, stati_scont *scont) {
    OSEVPF("[FUNC]:trave_qcont_enco\n");
    rsent_coup desv_memo;
    //
    rive_ha *stora_ha = dcont->stora_ha;
    riv_curso_t *dcurso, *scurso1, *scurso2;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    desv_memo.sinde1 = (scont)->sinde;
    if (stora_ha->open_curso_cont(&scurso1, sto_seio->seion, (scont)->cont_name, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    desv_memo.sinde2 = (++scont)->sinde;
    if (stora_ha->open_curso_cont(&scurso2, sto_seio->seion, (++scont)->cont_name, "raw")) {
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (stora_ha->open_curso_cont(&dcurso, sto_seio->seion, dcont->cont_name, "raw")) {
        stora_ha->close_curso(scurso1);
        stora_ha->close_curso(scurso2);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    PK_ITEM rkey1;
    while (0x00 == stora_ha->next_curso(scurso1)) {
        // OSEVPF("wt_next_curs\n");
        stora_ha->get_key(scurso1, &rkey1);
        desv_memo.senti1 = ((osv_sid_i *) rkey1.data)[0x00];
        //
        if (trave_secon_curso(dcurso, &desv_memo, scurso2, stora_ha)) {
            stora_ha->close_curso(dcurso);
            stora_ha->close_curso(scurso2);
            stora_ha->close_curso(scurso1);
            QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
            return -1;
        }
        // log_binary_file(obje_data, dylid->data_size, "./binary_code.bin_f");
    }
    FDAT_PRODUCE_TAIL(resctl, 0x00)
    //
    stora_ha->close_curso(dcurso);
    stora_ha->close_curso(scurso2);
    stora_ha->close_curso(scurso1);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    return 0x00;
}




#include "commo_header.h"
#include "kcomm_header.h"
#include "cqutili.h"
#include "query_utili.h"
#include "conattr.h"

#include "searq_conta_ensi.h"
#include "debug_funct/debug_funct_qc.h"

// odb:search("clasn", "conobje", "obje:numb() > 0x00");
// :search("cobje", "conobje", "obje:numb() > 0x00");
// :search("cobje", "conobje1, conobje2", "conobje1:obje:numb() > 0x00 AND conobje2:obje:numb() > 0x00");
// :search("cobje", "conobje1, conobje2", "conobje1::numb() > 0x00 AND conobje2::numb() > 0x00");
// odb:search("cobje", "conobje");
// predicate search / condition

// ensi

int condi_qcont_ensi(respo_ctrl *resctl, contain *dcont, stati_scont *scont, base_valu *baval, lv2pme *lv2me, char *condi) {
    OSEVPF("[FUNC]:condi_qcont_ensi\n");
    oper_node *synt_head;
    char erro_msg[LINE_LENGTH];
    if (build_query_synta(&synt_head, erro_msg, condi)) {
        OSEVPF("condi_qcont_ensi: %s\n", erro_msg);
        return -1;
    }
    //
    OSEVPF("creat_searq_plan_coulti\n");
    plan_node_ensi *querpn = CREAT_PLAN_NODE_ENSI(PLAN_ITEM_SZIE);
    if (!querpn) {
        DESTROY_STREE(synt_head);
        return -1;
    }
    if (creat_sconq_plan_ensi(querpn, resctl, dcont, scont, synt_head)) {
        DESTR_PLAN_NODE_ENSI(querpn);
        DESTROY_STREE(synt_head);
        return -1;
    }
    DESTROY_STREE(synt_head);
    PRIN_plan_node_ensi(querpn);
    // physical
    int searq_valu = ephys_searq_conta_ensi(querpn, dcont->stora_ha, baval, lv2me);
    DESTR_PLAN_NODE_ENSI(querpn);
    return searq_valu;
}

// odb:search("taat", "txxt_con") | kits:pretty("iii");
// odb:search("txxt_con", "tsta_con", "bf7f65dee501622d2e700000");
// parms[0x00] distance container 
// parms[0x01] source container 
// parms[0x02] object ident 

int objid_qcont_ensi(respo_ctrl *resctl, rive_conne *rivcon, contain *dcont, stati_scont *scont, lv2pme *lv2me, osv_oid_i *searq_obid) {
    OSEVPF("[FUNC]:objid_qcont_ensi\n");
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
    if (INSTAN_UNIQUE != searq_obid[0x00].osev_unique) {
        stora_ha->close_curso(dcurso);
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    PK_ITEM kient;
    stora_ha->set_sid_key(scurso, (uint64 *) & searq_obid[0x00].stoid);
    if (0x00 != stora_ha->search_curso(scurso)) {
        stora_ha->close_curso(dcurso);
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    stora_ha->get_key(scurso, &kient);
    //
    creat_objec_stoid((osv_sid_t *) & searq_obid[0x00].stoid);
    stora_ha->set_sid_key(dcurso, (uint64 *) & searq_obid[0x00].stoid);
    stora_ha->set_value(dcurso, &kient);
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

// odb:search("taat", "txxt_con") | kits:pretty("iii");
// odb:search("txxt_con", "tsta_con");

int trave_qcont_ensi(respo_ctrl *resctl, rive_conne *rivcon, contain *dcont, stati_scont *scont, lv2pme *lv2me) {
    OSEVPF("[FUNC]:trave_qcont_ensi\n");
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
    PK_ITEM rkey;
    rsent_sing desv_memo;
    desv_memo.sinde = scont->sinde;
    PK_ITEM kient;
    kient.data = &desv_memo;
    kient.size = sizeof (rsent_sing);
    //
    osv_sid_t deske_stoid;
    while (0x00 == stora_ha->next_curso(scurso)) {
        // OSEVPF("wt_next_curs\n");
        stora_ha->get_key(scurso, &rkey);
        desv_memo.senti = ((osv_sid_i *) rkey.data)[0x00];
        //
        creat_objec_stoid(&deske_stoid);
        stora_ha->set_sid_key(dcurso, (uint64 *) & deske_stoid);
        stora_ha->set_value(dcurso, &kient);
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

int condi_qcont_enob(respo_ctrl *resctl, contain *dcont, stati_scont *scont, base_valu *baval, lv2pme *lv2me, char *condi) {
    OSEVPF("[FUNC]:condi_qcont_obsi\n");
    oper_node *synt_head;
    char erro_msg[LINE_LENGTH];
    if (build_query_synta(&synt_head, erro_msg, condi)) {
        OSEVPF("condi_qcont_ensi: %s\n", erro_msg);
        return -1;
    }
    //
    OSEVPF("creat_searq_plan_coulti\n");
    plan_node_ensi *querpn = CREAT_PLAN_NODE_ENSI(PLAN_ITEM_SZIE);
    if (!querpn) {
        DESTROY_STREE(synt_head);
        return -1;
    }
    if (creat_sconq_plan_ensi(querpn, resctl, dcont, scont, synt_head)) {
        DESTR_PLAN_NODE_ENSI(querpn);
        DESTROY_STREE(synt_head);
        return -1;
    }
    DESTROY_STREE(synt_head);
    PRIN_plan_node_ensi(querpn);
    // physical
    int searq_valu = ephys_searq_conta_enob(querpn, dcont->stora_ha, baval, lv2me);
    DESTR_PLAN_NODE_ENSI(querpn);
    return searq_valu;
}


// odb:search("taat", "txxt_con") | kits:pretty("iii");
// odb:search("txxt_con", "tsta_con", "bf7f65dee501622d2e700000");
// parms[0x00] distance container 
// parms[0x01] source container 
// parms[0x02] object ident 

int objid_qcont_enob(respo_ctrl *resctl, rive_conne *rivcon, contain *dcont, stati_scont *scont, osv_oid_i *searq_obid) {
    OSEVPF("[FUNC]:objid_qcont_obsi\n");
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
    if (INSTAN_UNIQUE != searq_obid[0x00].osev_unique) {
        stora_ha->close_curso(dcurso);
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    PK_ITEM kient;
    stora_ha->set_sid_key(scurso, (uint64 *) & searq_obid[0x00].stoid);
    if (0x00 != stora_ha->search_curso(scurso)) {
        stora_ha->close_curso(dcurso);
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    stora_ha->get_key(scurso, &kient);
    //
    creat_objec_stoid((osv_sid_t *) & searq_obid[0x00].stoid);
    stora_ha->set_sid_key(dcurso, (uint64 *) & searq_obid[0x00].stoid);
    stora_ha->set_value(dcurso, &kient);
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

// odb:search("taat", "txxt_con") | kits:pretty("iii");
// odb:search("txxt_con", "tsta_con");

int trave_qcont_enob(respo_ctrl *resctl, rive_conne *rivcon, contain *dcont, stati_scont *scont) {
    OSEVPF("[FUNC]:trave_qcont_obsi\n");
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
    PK_ITEM rkey;
    rsent_sing desv_memo;
    desv_memo.sinde = scont->sinde;
    PK_ITEM kient;
    kient.data = &desv_memo;
    kient.size = sizeof (rsent_sing);
    //
    osv_sid_t deske_stoid;
    while (0x00 == stora_ha->next_curso(scurso)) {
        // OSEVPF("wt_next_curs\n");
        stora_ha->get_key(scurso, &rkey);
        desv_memo.senti = ((osv_sid_i *) rkey.data)[0x00];
        //
        creat_objec_stoid(&deske_stoid);
        stora_ha->set_sid_key(dcurso, (uint64 *) & deske_stoid);
        stora_ha->set_value(dcurso, &kient);
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

//

static inline unsigned int find_refer_cont(cont_versi *rcove, contain *contp) {
    OSEVPF("[FUNC]:find_refer_cont\n");
    unsigned int inde = 0x00;
    for (; (MAX_RSCON_COUNT > inde) && CHK_ZERO_COVE(rcove); ++inde, ++rcove) {
        if (OBID_EQUALI(&contp->cont_obid, &rcove->lv4p_obid))
            return inde;
    }
    return INVA_INDE_VALU;
}

int fill_check_rcont(contain *contp, stati_scont *sscon) {
    OSEVPF("[FUNC]:fill_check_rcont\n");
    int rscont_modified = 0x00;
    //
    cont_versi *rcove = contp->refe_cove;
    stati_scont *sscop = sscon;
    int ssind = 0x00;
    for (; (MAX_SCONT_COUNT > ssind) && CHK_ZERO_SSCON(sscop); ++ssind, ++sscop) {
        sscop->sinde = find_refer_cont(rcove, sscop->contp);
    }
    // INVA_INDE_VALU
    int sinde = 0x00;
    for (; (MAX_RSCON_COUNT > sinde) && CHK_ZERO_COVE(rcove); ++sinde, ++rcove);
    sscop = sscon;
    ssind = 0x00;
    for (; (MAX_SCONT_COUNT > ssind) && CHK_ZERO_SSCON(sscop); ++ssind, ++sscop) {
        if (INVA_INDE_VALU == sscop->sinde) {
            OSEVPF("add sscop->contp->cont_name:|%s|\n", sscop->contp->cont_name);
            OBID_BINARY_COPY(&rcove->lv4p_obid, &sscop->contp->cont_obid);
            OSEVPF("sinde:|%d| ssind:|%d|\n", sinde, ssind);
            ++rscont_modified;
            sscop->append++;
            sscop->sinde = sinde++;
            ++rcove;
        } else sscop->append = 0x00;
    }
    OSEVPF("rscont_modified:%d\n", rscont_modified);
    if (rscont_modified) {
        MAKE_ZERO_COVE(rcove);
        if (updat_rscont_atti(contp, contp->base_name))
            return -1;
    }
    //
    return 0x00;
}

int robk_fichk_rcont(contain *contp, stati_scont *sscon) {
    OSEVPF("[FUNC]:robk_fichk_rcont\n");
    int rscont_modified = 0x00;
    // memset(&contp->refe_cove, '\0', RCONT_CONUT_ZTAI * sizeof (cont_versi));
    cont_versi *rcove;
    osv_oid_t *cont_obid;
    int sinde;
    int ssind = 0x00;
    for (; (MAX_SCONT_COUNT > ssind) && CHK_ZERO_SSCON(sscon); ++ssind, ++sscon) {
        if (sscon->append) {
            cont_obid = &(sscon->contp->cont_obid);
            rcove = contp->refe_cove;
            for (sinde = 0x00; (MAX_RSCON_COUNT > sinde) && CHK_ZERO_COVE(rcove); ++sinde, ++rcove) {
                if (OBID_EQUALI(cont_obid, &rcove->lv4p_obid)) {
                    MAKE_ZERO_COVE(rcove);
                    ++rscont_modified;
                    break;
                }
            }
        }
    }
    //
    if (rscont_modified) {
        if (updat_rscont_atti(contp, contp->base_name))
            return -1;
    }
    return 0x00;
}

//

int build_stati_scont(stati_scont *sscon, contain **sconp) {
    OSEVPF("[FUNC]:build_stati_scont\n");
    unsigned int inde = 0x00;
    for (; (MAX_SCONT_COUNT > inde) && sconp[0x00]; ++inde, ++sconp, ++sscon) {
        sscon->contp = sconp[0x00];
        sscon->cont_name = sconp[0x00]->cont_name;
        sscon->lv2p_type = &sconp[0x00]->lv2p_type;
        OSEVPF("conve sscon->cont_name:|%s|\n", sscon->cont_name);
    }
    MAKE_SSCON_ZERO(sscon)
            //
    return 0x00;
}





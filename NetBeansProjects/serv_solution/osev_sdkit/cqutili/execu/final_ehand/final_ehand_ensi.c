#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_header.h"

#include "kcomm_struct.h"
#include "basev_bzl.h"
#include "cqutili.h"
#include "invoko.h"
// #include "../opera_utili.h"
#include "../data_compa/data_compa.h"
#include "seion_struct.h"
#include "lv2p_meta.h"

#include "final_ehand_ensi.h"
#include "debug_funct_co.h"

//

static int load_searo_entit_ensi(respo_ctrl *resctl, FILE *soure, riv_curso_t *proj_curso, rive_ha *stora_ha, lv2pme *lv2me) {
    OSEVPF("[FUNC]:load_searo_entit_ensi\n");
    rewind(resctl->resp_stram);
    rewind(soure);
    osv_oid_t key_obid;
    FILL_UNIQUE_OBID((osv_oid_i *) & key_obid);
    //
    PK_ITEM key, valu;
    osv_oid_i reso_obid;
    unsigned int inde = 0x00;
    for (; 0x00 < fread(&reso_obid, sizeof (osv_oid_i), 0x01, soure); ++inde) {
        stora_ha->set_sid_key(proj_curso, (uint64 *) & reso_obid.stoid);
        // PRIN_osv_oid_t_stri((osv_oid_t *) & reso_obid);
        if (0x00 != stora_ha->search_curso(proj_curso))
            return -1;
        stora_ha->get_key(proj_curso, &key);
        stora_ha->get_value(proj_curso, &valu);
        // dylid->solve(obje_memo, (uint64 *) key.data, &valu);
        // 0x00 >= APPEND_DATAS(resctl->resp_stram, obje_memo, dylid->data_size)
        PACKING_KEY_UNPACK(((osv_oid_i *) & key_obid)->stoid, (uint64 *) key.data);
        if (build_objec_strea_ensi(resctl->resp_stram, &key_obid, &valu))
            return -1;
    }
    FDAT_PRODUCE_TAIL(resctl, ftello64(resctl->resp_stram))
    OSEVPF("resctl->content_length:%llu\n", resctl->content_length);
    //
    return 0x00;
}

int hand_final_searo_ensi(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha, lv2pme *lv2me, char *contn) {
    OSEVPF("[FUNC]:hand_final_searo_ensi\n");
    plan_node_ensi *resupn = firspn->resul_node;
    //
    riv_curso_t *scurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&scurso, sto_seio->seion, contn, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (load_searo_entit_ensi(firspn->resctl, resupn->resul_set, scurso, stora_ha, lv2me)) {
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    stora_ha->close_curso(scurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    //
    if (resupn->resul_set) {
        fclose(resupn->resul_set);
        resupn->resul_set = NULL;
    }
    return 0x00;
}

//

static int load_slv2q_entit_ensi(respo_ctrl *resctl, FILE *soure) {
    // OSEVPF("[FUNC]:load_slv2q_refe_nosi\n");
    rewind(resctl->resp_stram);
    rewind(soure);
    osv_oid_i reso_obid[0x02];
    FILL_UNIQUE_OBID((osv_oid_t *) & reso_obid[0x00]);
    unsigned int inde = 0x00;
    for (; 0x00 < fread(&reso_obid[0x01], sizeof (osv_oid_i), 0x01, soure); ++inde) {
        creat_objec_stoid((osv_sid_t *)&(reso_obid[0x00].stoid));
        if (0x00 >= APPEND_DATAS(resctl->resp_stram, reso_obid, (0x02 * sizeof (osv_oid_i))))
            return -1;
    }
    //
    FDAT_PRODUCE_TAIL(resctl, (0x02 * sizeof (osv_oid_i)) * inde)
    OSEVPF("resctl->content_length:%llu\n", resctl->content_length);
    return 0x00;
}

int hfina_searq_lv2pn_ensi(plan_node_ensi *firspn) {
    OSEVPF("[FUNC]:hfina_searq_lv2pn_nosi\n");
    plan_node_ensi *resupn = firspn->resul_node;
    // OSEVPF("--- 2\n");
    if (load_slv2q_entit_ensi(firspn->resctl, resupn->resul_set)) {
        return -1;
    }
    // OSEVPF("--- 3\n");
    if (resupn->resul_set) {
        fclose(resupn->resul_set);
        resupn->resul_set = NULL;
    }
    return 0x00;
}

//

static int load_slv2q_proje_enob(respo_ctrl *resctl, FILE *soure, riv_curso_t *proj_curso, rive_ha *stora_ha, lv2pme *lv2me) {
    // OSEVPF("[FUNC]:load_slv2q_proje_enob\n");
    rewind(resctl->resp_stram);
    rewind(soure);
    osv_oid_t key_obid;
    FILL_UNIQUE_OBID((osv_oid_i *) & key_obid);
    //
    PK_ITEM svalu;
    osv_oid_i reso_obid;
    unsigned int inde = 0x00;
    for (; 0x00 < fread(&reso_obid, sizeof (osv_oid_i), 0x01, soure); ++inde) {
        stora_ha->set_sid_key(proj_curso, (uint64 *) & reso_obid.stoid);
        // PRIN_osv_oid_t_stri((osv_oid_t *) & reso_obid);
        if (0x00 != stora_ha->search_curso(proj_curso))
            return -1;
        stora_ha->get_value(proj_curso, &svalu);
        // dylid->solve(obje_memo, &reso_obid.stoid, &svalu);
        // 0x00 >= APPEND_DATAS(resctl->resp_stram, obje_memo, dylid->data_size)
        PACKING_KEY_UNPACK(((osv_oid_i *) & key_obid)->stoid, (uint64 *) & reso_obid.stoid);
        if (build_objec_strea_ensi(resctl->resp_stram, &key_obid, &svalu))
            return -1;
    }
    FDAT_PRODUCE_TAIL(resctl, ftello64(resctl->resp_stram))
    OSEVPF("resctl->content_length:%llu\n", resctl->content_length);
    //
    return 0x00;
}

int hfina_searq_lv2pn_enob(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha, lv2pme *lv2me, plan_node_ensi *finapn) {
    OSEVPF("[FUNC]:hfina_searq_lv2pn_obsi\n");
    plan_node_ensi *resupn = firspn->resul_node;
    //
    riv_curso_t *scurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&scurso, sto_seio->seion, finapn->cont_name, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 2\n");
    if (load_slv2q_proje_enob(firspn->resctl, resupn->resul_set, scurso, stora_ha, lv2me)) {
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 3\n");
    stora_ha->close_curso(scurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    //
    if (resupn->resul_set) {
        fclose(resupn->resul_set);
        resupn->resul_set = NULL;
    }
    return 0x00;
}

//

static int load_sconq_refer_ensi(respo_ctrl *resctl, FILE *soure, riv_curso_t *rcurso, rive_ha *stora_ha) {
    // OSEVPF("[FUNC]:load_sconq_refer_ensi\n");
    rewind(resctl->resp_stram);
    rewind(soure);
    //
    osv_sid_t deske_stoid;
    osv_oid_i reso_obid;
    PK_ITEM kient;
    kient.data = &(reso_obid.stoid);
    kient.size = sizeof (osv_sid_t);
    while (0x00 < fread(&reso_obid, sizeof (osv_oid_i), 0x01, soure)) {
        // PRIN_osv_oid_t_stri((osv_oid_t *) & reso_obid);
        creat_objec_stoid(&deske_stoid);
        stora_ha->set_sid_key(rcurso, (uint64 *) & deske_stoid);
        stora_ha->set_value(rcurso, &kient);
        if (stora_ha->inser_curso(rcurso))
            return -1;
    }
    //
    FDAT_PRODUCE_TAIL(resctl, 0x00)
    OSEVPF("resctl->content_length:%llu\n", resctl->content_length);
    return 0x00;
}

int hfina_searq_conta_ensi(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha) {
    OSEVPF("[FUNC]:hfina_searq_conta_ensi\n");
    plan_node_ensi *resupn = firspn->resul_node;
    riv_curso_t *rcurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&rcurso, sto_seio->seion, firspn->cont_name, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 2\n");
    if (load_sconq_refer_ensi(firspn->resctl, resupn->resul_set, rcurso, stora_ha)) {
        stora_ha->close_curso(rcurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 3\n");
    stora_ha->close_curso(rcurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    //
    if (resupn->resul_set) {
        fclose(resupn->resul_set);
        resupn->resul_set = NULL;
    }
    return 0x00;
}

//

static int load_sconq_refer_enob(respo_ctrl *resctl, FILE *soure, riv_curso_t *rcurso, rive_ha *stora_ha) {
    // OSEVPF("[FUNC]:load_sconq_refer_ensi\n");
    rewind(resctl->resp_stram);
    rewind(soure);
    //
    osv_sid_t deske_stoid;
    osv_oid_i reso_obid;
    PK_ITEM kient;
    kient.data = &(reso_obid.stoid);
    kient.size = sizeof (osv_sid_t);
    while (0x00 < fread(&reso_obid, sizeof (osv_oid_i), 0x01, soure)) {
        // PRIN_osv_oid_t_stri((osv_oid_t *) & reso_obid);
        creat_objec_stoid(&deske_stoid);
        stora_ha->set_sid_key(rcurso, (uint64 *) & deske_stoid);
        stora_ha->set_value(rcurso, &kient);
        if (stora_ha->inser_curso(rcurso))
            return -1;
    }
    //
    FDAT_PRODUCE_TAIL(resctl, 0x00)
    OSEVPF("resctl->content_length:%llu\n", resctl->content_length);
    return 0x00;
}

int hfina_searq_conta_enob(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha) {
    OSEVPF("[FUNC]:hfina_searq_conta_enob\n");
    plan_node_ensi *resupn = firspn->resul_node;
    riv_curso_t *rcurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&rcurso, sto_seio->seion, firspn->cont_name, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 2\n");
    if (load_sconq_refer_enob(firspn->resctl, resupn->resul_set, rcurso, stora_ha)) {
        stora_ha->close_curso(rcurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 3\n");
    stora_ha->close_curso(rcurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    //
    if (resupn->resul_set) {
        fclose(resupn->resul_set);
        resupn->resul_set = NULL;
    }
    return 0x00;
}

//

static int remo_dropo_entit(FILE *soure, riv_curso_t *drop_curso, rive_ha *stora_ha) {
    // OSEVPF("[FUNC]:remo_dropo_entit\n");
    rewind(soure);
    osv_oid_i reso_obid;
    while (0x00 < fread(&reso_obid, sizeof (osv_oid_i), 0x01, soure)) {
        stora_ha->set_sid_key(drop_curso, (uint64 *) & reso_obid.stoid);
        if (0x00 == stora_ha->search_curso(drop_curso)) {
            if ((stora_ha->remove_curso(drop_curso)))
                return -1;
        }
    }
    //
    return 0x00;
}

int hand_final_dropo(plan_node_ensi *resupn, rive_conne *rivcon, rive_ha *stora_ha, char *contn) {
    OSEVPF("[FUNC]:hand_final_dropo\n");
    riv_curso_t *dcurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&dcurso, sto_seio->seion, contn, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    if (remo_dropo_entit(resupn->resul_set, dcurso, stora_ha)) {
        stora_ha->close_curso(dcurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    stora_ha->close_curso(dcurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    //
    if (resupn->resul_set) {
        fclose(resupn->resul_set);
        resupn->resul_set = NULL;
    }
    return 0x00;
}

//

static int each_invoko_entit(respo_ctrl *resctl, FILE *soure, riv_curso_t *invo_curso, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk) {
    // OSEVPF("[FUNC]:each_invoko_entit\n");
    rewind(soure);
    rewind(resctl->resp_stram);
    //
    loop_memo_t obje_memo;
    if (!loop_malloc(&obje_memo, lv1me->lv2me))
        return -1;
    //
    oreval rvalu;
    FILL_UNIQUE_OBID((osv_oid_t *) & rvalu.obje_obid);
    int rval_len = type_rvlen_tab[lv1me->oivk_retyp_oe];
    //
    PK_ITEM key, valu;
    osv_oid_i reso_obid;
    while (0x00 < fread(&reso_obid, sizeof (osv_oid_i), 0x01, soure)) {
        stora_ha->set_sid_key(invo_curso, (uint64 *) & reso_obid.stoid);
        if (0x00 != stora_ha->search_curso(invo_curso)) {
            free_loop(&obje_memo);
            return -1;
        }
        stora_ha->get_key(invo_curso, &key);
        stora_ha->get_value(invo_curso, &valu);
        if (bound_objec_loop(&obje_memo, (uint64 *) key.data, &valu, lv1me->lv2me)) {
            free_loop(&obje_memo);
            return -1;
        }
        rvalu.obje_obid.stoid = ((osv_oid_i *) obje_memo.data)->stoid;
        lv1me->method.invoke(&rvalu, obje_memo.data, parm_oivk);
        //
        PK_ITEM key, valu;
        if (solve_objec_loop(&key, &valu, &obje_memo, lv1me->lv2me)) {
            free_loop(&obje_memo);
            return -1;
        }
        stora_ha->set_key(invo_curso, &key);
        stora_ha->set_value(invo_curso, &valu);
        if (!stora_ha->update_curso(invo_curso)) {
            if (0x00 >= APPEND_DATAS(resctl->resp_stram, (char *) &rvalu, rval_len)) {
                free_loop(&obje_memo);
                return -1;
            }
        }
    }
    FDAT_PRODUCE_TAIL(resctl, ftello64(resctl->resp_stram))
    OSEVPF("resctl->content_length:%llu\n", resctl->content_length);
    //
    free_loop(&obje_memo);
    return 0x00;
}

int hand_final_invoko(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, char *contn) {
    OSEVPF("[FUNC]:hand_final_invoko\n");
    plan_node_ensi *resupn = firspn->resul_node;
    //
    riv_curso_t *dcurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&dcurso, sto_seio->seion, contn, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    if (each_invoko_entit(firspn->resctl, resupn->resul_set, dcurso, stora_ha, lv1me, parm_oivk)) {
        stora_ha->close_curso(dcurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    stora_ha->close_curso(dcurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    //
    if (resupn->resul_set) {
        fclose(resupn->resul_set);
        resupn->resul_set = NULL;
    }
    return 0x00;
}

//

static int load_flv2q_proje_ensi(respo_ctrl *resctl, FILE *soure, riv_curso_t *proj_curso, rive_ha *stora_ha, lv2pme **lv2mep) {
    // OSEVPF("[FUNC]:load_flv2q_proje_ensi\n");
    rewind(resctl->resp_stram);
    rewind(soure);
    osv_oid_t key_obid;
    FILL_UNIQUE_OBID((osv_oid_i *) & key_obid);
    //
    osv_sid_t deske_stoid;
    PK_ITEM svalu;
    osv_oid_i reso_obid;
    while (0x00 < fread(&reso_obid, sizeof (osv_oid_i), 0x01, soure)) {
        // PRIN_osv_oid_t_stri((osv_oid_t *) & reso_obid);
        stora_ha->set_sid_key(proj_curso, (uint64 *) & reso_obid.stoid);
        if (0x00 != stora_ha->search_curso(proj_curso))
            return -1;
        stora_ha->get_value(proj_curso, &svalu);
        creat_objec_stoid(&deske_stoid);
        // dylid->solve(obje_memo, (uint64 *) & deske_stoid, &svalu);
        // 0x00 >= APPEND_DATAS(resctl->resp_stram, obje_memo, dylid->data_size)
        PACKING_KEY_UNPACK(((osv_oid_i *) & key_obid)->stoid, (uint64 *) & deske_stoid);
        if (build_objec_strea_ensi(resctl->resp_stram, &key_obid, &svalu))
            return -1;
    }
    FDAT_PRODUCE_TAIL(resctl, ftello64(resctl->resp_stram))
    //
    OSEVPF("resctl->content_length:%llu\n", resctl->content_length);
    return 0x00;
}

int hfina_facto_lv2pn_ensi(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha, lv2pme **lv2mep, plan_node_ensi *finapn) {
    OSEVPF("[FUNC]:hfina_facto_lv2pn_ensi\n");
    plan_node_ensi *resupn = firspn->resul_node;
    //
    riv_curso_t *scurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_prop(&scurso, sto_seio->seion, finapn->cont_name, finapn->source_str, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 2\n");
    if (load_flv2q_proje_ensi(firspn->resctl, resupn->resul_set, scurso, stora_ha, lv2mep)) {
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 3\n");
    stora_ha->close_curso(scurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    // OSEVPF("--- 4\n");
    if (resupn->resul_set) {
        fclose(resupn->resul_set);
        resupn->resul_set = NULL;
    }
    return 0x00;
}

//

static int load_flv2q_proje_enob(respo_ctrl *resctl, FILE *soure, riv_curso_t *proj_curso, rive_ha *stora_ha, lv2pme **lv2mep) {
    // OSEVPF("[FUNC]:load_flv2q_proje_ensi\n");
    rewind(resctl->resp_stram);
    rewind(soure);
    osv_oid_t key_obid;
    FILL_UNIQUE_OBID((osv_oid_i *) & key_obid);
    //
    osv_sid_t deske_stoid;
    PK_ITEM svalu;
    osv_oid_i reso_obid;
    while (0x00 < fread(&reso_obid, sizeof (osv_oid_i), 0x01, soure)) {
        // PRIN_osv_oid_t_stri((osv_oid_t *) & reso_obid);
        stora_ha->set_sid_key(proj_curso, (uint64 *) & reso_obid.stoid);
        if (0x00 != stora_ha->search_curso(proj_curso))
            return -1;
        stora_ha->get_value(proj_curso, &svalu);
        creat_objec_stoid(&deske_stoid);
        // dylid->solve(obje_memo, (uint64 *) & deske_stoid, &svalu);
        // 0x00 >= APPEND_DATAS(resctl->resp_stram, obje_memo, dylid->data_size)
        PACKING_KEY_UNPACK(((osv_oid_i *) & key_obid)->stoid, (uint64 *) & deske_stoid);
        if (build_objec_strea_ensi(resctl->resp_stram, &key_obid, &svalu))
            return -1;
    }
    FDAT_PRODUCE_TAIL(resctl, ftello64(resctl->resp_stram))
    //
    OSEVPF("resctl->content_length:%llu\n", resctl->content_length);
    return 0x00;
}

int hfina_facto_lv2pn_enob(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha, lv2pme **lv2mep, plan_node_ensi *finapn) {
    OSEVPF("[FUNC]:hfina_facto_lv2pn_enob\n");
    plan_node_ensi *resupn = firspn->resul_node;
    //
    riv_curso_t *scurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_prop(&scurso, sto_seio->seion, finapn->cont_name, finapn->source_str, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 2\n");
    if (load_flv2q_proje_enob(firspn->resctl, resupn->resul_set, scurso, stora_ha, lv2mep)) {
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 3\n");
    stora_ha->close_curso(scurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    // OSEVPF("--- 4\n");
    if (resupn->resul_set) {
        fclose(resupn->resul_set);
        resupn->resul_set = NULL;
    }
    return 0x00;
}

//

static int load_fconq_proje_ensi(respo_ctrl *resctl, FILE *soure, riv_curso_t *dcurso, riv_curso_t *scurso, rive_ha *stora_ha) {
    // OSEVPF("[FUNC]:load_fconq_proje_ensi\n");
    rewind(resctl->resp_stram);
    rewind(soure);
    //
    osv_sid_t deske_stoid;
    PK_ITEM svalu;
    osv_oid_i reso_obid;
    while (0x00 < fread(&reso_obid, sizeof (osv_oid_i), 0x01, soure)) {
        stora_ha->set_sid_key(scurso, (uint64 *) & reso_obid.stoid);
        // PRIN_osv_oid_t_stri((osv_oid_t *) & reso_obid);
        if (0x00 != stora_ha->search_curso(scurso)) {
            return -1;
        }
        stora_ha->get_value(scurso, &svalu);
        creat_objec_stoid(&deske_stoid);
        stora_ha->set_sid_key(dcurso, (uint64 *) & deske_stoid);
        stora_ha->set_value(dcurso, &svalu);
        if (stora_ha->inser_curso(dcurso)) {
            return -1;
        }
    }
    FDAT_PRODUCE_TAIL(resctl, 0x00)
    OSEVPF("resctl->content_length:%llu\n", resctl->content_length);
    //
    return 0x00;
}

int hfina_facto_conta_ensi(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha, plan_node_ensi *finapn) {
    OSEVPF("[FUNC]:hfina_facto_conta_ensi\n");
    OSEVPF("[FUNC]:firspn->cont_name:|%s|\n", firspn->cont_name);
    plan_node_ensi *resupn = firspn->resul_node;
    riv_curso_t *dcurso, *scurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_prop(&scurso, sto_seio->seion, finapn->cont_name, finapn->source_str, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (stora_ha->open_curso_cont(&dcurso, sto_seio->seion, firspn->cont_name, "raw")) {
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 2\n");
    if (load_fconq_proje_ensi(firspn->resctl, resupn->resul_set, dcurso, scurso, stora_ha)) {
        stora_ha->close_curso(dcurso);
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 3\n");
    stora_ha->close_curso(dcurso);
    stora_ha->close_curso(scurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    if (resupn->resul_set) {
        fclose(resupn->resul_set);
        resupn->resul_set = NULL;
    }
    return 0x00;
}

//

//

static int load_fconq_proje_enob(respo_ctrl *resctl, FILE *soure, riv_curso_t *dcurso, riv_curso_t *scurso, rive_ha *stora_ha) {
    // OSEVPF("[FUNC]:load_fconq_proje_ensi\n");
    rewind(resctl->resp_stram);
    rewind(soure);
    //
    osv_sid_t deske_stoid;
    PK_ITEM svalu;
    osv_oid_i reso_obid;
    while (0x00 < fread(&reso_obid, sizeof (osv_oid_i), 0x01, soure)) {
        stora_ha->set_sid_key(scurso, (uint64 *) & reso_obid.stoid);
        // PRIN_osv_oid_t_stri((osv_oid_t *) & reso_obid);
        if (0x00 != stora_ha->search_curso(scurso)) {
            return -1;
        }
        stora_ha->get_value(scurso, &svalu);
        creat_objec_stoid(&deske_stoid);
        stora_ha->set_sid_key(dcurso, (uint64 *) & deske_stoid);
        stora_ha->set_value(dcurso, &svalu);
        if (stora_ha->inser_curso(dcurso)) {
            return -1;
        }
    }
    FDAT_PRODUCE_TAIL(resctl, 0x00)
    OSEVPF("resctl->content_length:%llu\n", resctl->content_length);
    //
    return 0x00;
}

int hfina_facto_conta_enob(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha, plan_node_ensi *finapn) {
    OSEVPF("[FUNC]:hfina_facto_conta_enob\n");
    OSEVPF("[FUNC]:firspn->cont_name:|%s|\n", firspn->cont_name);
    plan_node_ensi *resupn = firspn->resul_node;
    riv_curso_t *dcurso, *scurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_prop(&scurso, sto_seio->seion, finapn->cont_name, finapn->source_str, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (stora_ha->open_curso_cont(&dcurso, sto_seio->seion, firspn->cont_name, "raw")) {
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 2\n");
    if (load_fconq_proje_enob(firspn->resctl, resupn->resul_set, dcurso, scurso, stora_ha)) {
        stora_ha->close_curso(dcurso);
        stora_ha->close_curso(scurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 3\n");
    stora_ha->close_curso(dcurso);
    stora_ha->close_curso(scurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    if (resupn->resul_set) {
        fclose(resupn->resul_set);
        resupn->resul_set = NULL;
    }
    return 0x00;
}

//

static int load_refro_entit_ensi(FILE *soure, riv_curso_t *rcurso, rive_ha *stora_ha) {
    // OSEVPF("[FUNC]:load_refro_entit_ensi\n");
    rewind(soure);
    //
    osv_sid_t deske_stoid;
    osv_oid_i reso_obid;
    PK_ITEM kient;
    kient.data = &(reso_obid.stoid);
    kient.size = sizeof (osv_sid_t);
    while (0x00 < fread(&reso_obid, sizeof (osv_oid_i), 0x01, soure)) {
        // PRIN_osv_oid_t_stri((osv_oid_t *) & reso_obid);
        creat_objec_stoid(&deske_stoid);
        stora_ha->set_sid_key(rcurso, (uint64 *) & deske_stoid);
        stora_ha->set_value(rcurso, &kient);
        if (stora_ha->inser_curso(rcurso))
            return -1;
    }
    //
    return 0x00;
}

int hfina_refro_rcont_ensi(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha) {
    OSEVPF("[FUNC]:hfina_refro_rcont_ensi\n");
    plan_node_ensi *resupn = firspn->resul_node;
    riv_curso_t *rcurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&rcurso, sto_seio->seion, firspn->cont_name, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 2\n");
    if (load_refro_entit_ensi(resupn->resul_set, rcurso, stora_ha)) {
        stora_ha->close_curso(rcurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 3\n");
    stora_ha->close_curso(rcurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    //
    if (resupn->resul_set) {
        fclose(resupn->resul_set);
        resupn->resul_set = NULL;
    }
    return 0x00;
}



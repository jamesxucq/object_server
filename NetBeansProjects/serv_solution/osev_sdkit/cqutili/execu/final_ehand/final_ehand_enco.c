#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_header.h"

#include "basev_bzl.h"
#include "cqutili.h"
#include "invoko.h"
#include "../data_compa/data_compa.h"
#include "seion_struct.h"
#include "debug_funct_co.h"
#include "lv2p_meta.h"
#include "kcomm_struct.h"
#include "paki_memo.h"

#include "final_ehand_enco.h"
//

static int load_slv2q_proje_enco(respo_ctrl *resctl, FILE *soure) {
    // OSEVPF("[FUNC]:load_slv2q_proje_enco\n");
    rewind(resctl->resp_stram);
    rewind(soure);
    //
    osv_oid_i reso_obid[0x03];
    FILL_UNIQUE_OBID((osv_oid_t *) & reso_obid[0x00]);
    unsigned int inde = 0x00;
    for (; 0x00 < fread(&reso_obid[0x01], sizeof (osv_oid_i), 0x02, soure); ++inde) {
        creat_objec_stoid((osv_sid_t *)&(reso_obid[0x00].stoid));
        if (0x00 >= APPEND_DATAS(resctl->resp_stram, reso_obid, (0x03 * sizeof (osv_oid_i))))
            return -1;
    }
    //
    FDAT_PRODUCE_TAIL(resctl, (0x03 * sizeof (osv_oid_i)) * inde)
    OSEVPF("resctl->content_length:%llu\n", resctl->content_length);
    return 0x00;
}

int hfina_searq_lv2pn_enco(plan_node_enco *firspn) {
    OSEVPF("[FUNC]:hfina_searq_lv2pn_enco\n");
    plan_node_enco *resupn = firspn->resul_node;
    // OSEVPF("--- 1\n");
    if (load_slv2q_proje_enco(firspn->resctl, resupn->resul_set)) {
        return -1;
    }
    // OSEVPF("--- 4\n");
    if (resupn->resul_set) {
        fclose(resupn->resul_set);
        resupn->resul_set = NULL;
    }
    return 0x00;
}

//

static int load_sconq_refer_enco(respo_ctrl *resctl, FILE *soure, riv_curso_t *rcurso, rive_ha *stora_ha) {
    // OSEVPF("[FUNC]:load_sconq_refer_enco\n");
    rewind(resctl->resp_stram);
    rewind(soure);
    //
    osv_sid_t deske_stoid, desv_memo[0x02];
    PK_ITEM kient;
    kient.data = (void *) desv_memo;
    kient.size = (0x02 * sizeof (osv_sid_t));
    osv_oid_i reso_obid[0x02];
    while (0x00 < fread(reso_obid, sizeof (osv_oid_i), 0x02, soure)) {
        // PRIN_osv_oid_t_stri((osv_oid_t *) & reso_obid);
        creat_objec_stoid(&deske_stoid);
        stora_ha->set_sid_key(rcurso, (uint64 *) & deske_stoid);
        memcpy((void *) kient.data, &reso_obid[0x00].stoid, sizeof (osv_sid_t));
        memcpy(sizeof (osv_sid_t) + (void *) kient.data, &reso_obid[0x01].stoid, sizeof (osv_sid_t));
        stora_ha->set_value(rcurso, &kient);
        if (stora_ha->inser_curso(rcurso))
            return -1;
    }
    //
    FDAT_PRODUCE_TAIL(resctl, 0x00)
    OSEVPF("resctl->content_length:%llu\n", resctl->content_length);
    return 0x00;
}

int hfina_searq_conta_enco(plan_node_enco *firspn, rive_conne *rivcon, rive_ha *stora_ha) {
    OSEVPF("[FUNC]:hfina_searq_conta_enco\n");
    plan_node_enco *resupn = firspn->resul_node;
    //
    riv_curso_t *rcurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&rcurso, sto_seio->seion, firspn->cont_name, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 1\n");
    if (load_sconq_refer_enco(firspn->resctl, resupn->resul_set, rcurso, stora_ha)) {
        stora_ha->close_curso(rcurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 3\n");

    stora_ha->close_curso(rcurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    // OSEVPF("--- 4\n");
    if (resupn->resul_set) {
        fclose(resupn->resul_set);
        resupn->resul_set = NULL;
    }
    return 0x00;
}

//

static int load_flv2q_proje_enco(plan_node_enco *firspn, FILE *soure, riv_curso_t *scurso1, riv_curso_t *scurso2, rive_ha *stora_ha) {
    // OSEVPF("[FUNC]:load_flv2q_proje_enco\n");
    respo_ctrl *resctl = firspn->resctl;
    field_resul_co *fieres = firspn->fieres;
    rewind(resctl->resp_stram);
    rewind(soure);
    PK_ITEM kient;
    if (!pkite_mallo(&kient, fieres->data_size))
        return -1;
    FILL_UNIQUE_OBID((osv_oid_t *) kient.data);
    //
    PK_ITEM svalu1, svalu2;
    osv_oid_i reso_obid[0x02];
    while (0x00 < fread(reso_obid, sizeof (osv_oid_i), 0x02, soure)) {
        stora_ha->set_sid_key(scurso1, (uint64 *) & reso_obid[0x00].stoid);
        if (0x00 != stora_ha->search_curso(scurso1)) {
            FREE_KITE(&kient);
            return -1;
        }
        stora_ha->get_value(scurso1, &svalu1);
        //
        stora_ha->set_sid_key(scurso2, (uint64 *) & reso_obid[0x01].stoid);
        if (0x00 != stora_ha->search_curso(scurso2)) {
            FREE_KITE(&kient);
            return -1;
        }
        stora_ha->get_value(scurso2, &svalu2);
        // PASS_OBIDEN_SECTI(kient.data)
        creat_objec_stoid((osv_sid_t *)&((osv_oid_i *) kient.data)->stoid);
        if (fieres->fixed_float_co) {
            if (reall_objec_pkite(&kient, &svalu1, &svalu2)) {
                FREE_KITE(&kient);
                return -1;
            }
        }
        if (build_proje_strea_enco(resctl->resp_stram, &kient, &svalu1, &svalu2, fieres)) {
            FREE_KITE(&kient);
            return -1;
        }
    }
    FDAT_PRODUCE_TAIL(resctl, ftello64(resctl->resp_stram))
    OSEVPF("resctl->content_length:%llu\n", resctl->content_length);
    //
    FREE_KITE(&kient);
    return 0x00;
}

int hfina_facto_lv2pn_enco(plan_node_enco *firspn, rive_conne *rivcon, rive_ha *stora_ha, lv2pme **lv2mep, plan_node_enco *finapn) {
    OSEVPF("[FUNC]:hfina_facto_lv2pn_enco\n");
    plan_node_enco *resupn = firspn->resul_node;
    field_resul_co *fieres = firspn->fieres;
    //
    riv_curso_t *scurso1, *scurso2;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_prop(&scurso1, sto_seio->seion, finapn->cont_name, fieres->field_str1, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    ++finapn;
    if (FINAL_QUDRY_ACCO != finapn->acti_oper) {
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (stora_ha->open_curso_prop(&scurso2, sto_seio->seion, finapn->cont_name, fieres->field_str2, "raw")) {
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 2\n");
    if (load_flv2q_proje_enco(firspn, resupn->resul_set, scurso1, scurso2, stora_ha)) {
        stora_ha->close_curso(scurso2);
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 3\n");
    stora_ha->close_curso(scurso2);
    stora_ha->close_curso(scurso1);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    // OSEVPF("--- 4\n");
    if (resupn->resul_set) {
        fclose(resupn->resul_set);
        resupn->resul_set = NULL;
    }
    return 0x00;
}

//

static int load_fconq_proje_enco(respo_ctrl *resctl, FILE *soure, riv_curso_t *dcurso, riv_curso_t *scurso1, riv_curso_t *scurso2, field_resul_co *fieres, rive_ha *stora_ha) {
    // OSEVPF("[FUNC]:load_fconq_proje_enco\n");
    rewind(resctl->resp_stram);
    rewind(soure);
    //
    PK_ITEM svalu1, svalu2;
    osv_sid_t deske_stoid;
    paki_memo_t objnod;
    if (!pkmem_mallo(&objnod, fieres->data_size))
        return -1;
    osv_oid_i reso_obid[0x02];
    while (0x00 < fread(reso_obid, sizeof (osv_oid_i), 0x02, soure)) {
        stora_ha->set_sid_key(scurso1, (uint64 *) & reso_obid[0x00].stoid);
        if (0x00 != stora_ha->search_curso(scurso1)) {
            FREE_PAKI(&objnod);
            return -1;
        }
        stora_ha->get_value(scurso1, &svalu1);
        //
        stora_ha->set_sid_key(scurso2, (uint64 *) & reso_obid[0x01].stoid);
        if (0x00 != stora_ha->search_curso(scurso2)) {
            FREE_PAKI(&objnod);
            return -1;
        }
        stora_ha->get_value(scurso2, &svalu2);
        //        
        creat_objec_stoid(&deske_stoid);
        stora_ha->set_sid_key(dcurso, (uint64 *) & deske_stoid);
        if (fieres->fixed_float_co) {
            if (reall_objec_pkmem(&objnod, &svalu1, &svalu2)) {
                FREE_PAKI(&objnod);
                return -1;
            }
        }
        build_proje_objec_enco(&objnod, &svalu1, &svalu2, fieres);
        stora_ha->set_value(dcurso, &objnod.item);
        if (stora_ha->inser_curso(dcurso)) {
            FREE_PAKI(&objnod);
            return -1;
        }
    }
    FDAT_PRODUCE_TAIL(resctl, 0x00)
    OSEVPF("resctl->content_length:%llu\n", resctl->content_length);
    //
    FREE_PAKI(&objnod);
    return 0x00;
}

int hfina_facto_conta_enco(plan_node_enco *firspn, rive_conne *rivcon, rive_ha *stora_ha, lv2pme **lv2mep, plan_node_enco *finapn) {
    OSEVPF("[FUNC]:hfina_facto_conta_enco\n");
    plan_node_enco *resupn = firspn->resul_node;
    field_resul_co *fieres = firspn->fieres;
    //
    riv_curso_t *dcurso, *scurso1, *scurso2;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_prop(&scurso1, sto_seio->seion, finapn->cont_name, fieres->field_str1, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    ++finapn;
    if (FINAL_QUDRY_ACCO != finapn->acti_oper) {
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (stora_ha->open_curso_prop(&scurso2, sto_seio->seion, finapn->cont_name, fieres->field_str2, "raw")) {
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (stora_ha->open_curso_cont(&dcurso, sto_seio->seion, firspn->cont_name, "raw")) {
        stora_ha->close_curso(scurso1);
        stora_ha->close_curso(scurso2);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 2\n");
    if (load_fconq_proje_enco(firspn->resctl, resupn->resul_set, dcurso, scurso1, scurso2, fieres, stora_ha)) {
        stora_ha->close_curso(dcurso);
        stora_ha->close_curso(scurso2);
        stora_ha->close_curso(scurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 3\n");
    stora_ha->close_curso(dcurso);
    stora_ha->close_curso(scurso2);
    stora_ha->close_curso(scurso1);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    // OSEVPF("--- 4\n");
    if (resupn->resul_set) {
        fclose(resupn->resul_set);
        resupn->resul_set = NULL;
    }
    return 0x00;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_header.h"

#include "basev_bzl.h"
#include "invoko.h"
#include "../data_compa/data_compa.h"
#include "cqutili.h"
#include "seion_struct.h"
#include "lv2p_meta.h"
#include "kcomm_struct.h"

#include "final_ehand_reco.h"
#include "debug_funct_co.h"

//

static int load_searo_proje_rsco(respo_ctrl *resctl, FILE *soure, riv_curso_t *proj_curso, rive_ha *stora_ha) {
    // OSEVPF("[FUNC]:load_searo_proje_rsco\n");
    rewind(resctl->resp_stram);
    rewind(soure);
    osv_oid_i objnod[SCONT_CONUT_ZTAI];
    init_dynami_robj((void *) objnod, 0x02);
    int (*rdobje_unpack)(void *, PK_ITEM *, PK_ITEM *);
    rdobje_unpack = dynami_unpack_tab[0x02];
    //
    uint64 data_size = 0x02 * sizeof (osv_oid_t);
    PK_ITEM skey, svalu;
    osv_oid_i reso_obid;
    unsigned int inde = 0x00;
    for (; 0x00 < fread(&reso_obid, sizeof (osv_oid_i), 0x01, soure); ++inde) {
        stora_ha->set_sid_key(proj_curso, (uint64 *) & reso_obid.stoid);
        // PRIN_osv_oid_t_stri((osv_oid_t *) & reso_obid);
        if (0x00 != stora_ha->search_curso(proj_curso))
            return -1;
        stora_ha->get_key(proj_curso, &skey);
        stora_ha->get_value(proj_curso, &svalu);
        rdobje_unpack((void *) objnod, &skey, &svalu);
        if (0x00 >= APPEND_DATAS(resctl->resp_stram, objnod, data_size))
            return -1;
    }
    FDAT_PRODUCE_TAIL(resctl, data_size * inde)
    OSEVPF("resctl->content_length:%llu\n", resctl->content_length);
    //
    return 0x00;
}

int hand_final_searo_rsco(plan_node_enco *firspn, rive_conne *rivcon, rive_ha *stora_ha, char *contn) {
    OSEVPF("[FUNC]:hand_final_searo_rsco\n");
    plan_node_enco *resupn = firspn->resul_node;
    //
    riv_curso_t *scurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&scurso, sto_seio->seion, contn, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 1\n");
    if (load_searo_proje_rsco(resupn->resctl, resupn->resul_set, scurso, stora_ha)) {
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

static int load_searo_proje_rdco(respo_ctrl *resctl, FILE *soure, riv_curso_t *proj_curso, rive_ha *stora_ha) {
    // OSEVPF("[FUNC]:load_searo_proje_rdco\n");
    rewind(resctl->resp_stram);
    rewind(soure);
    osv_oid_i objnod[SCONT_CONUT_ZTAI];
    init_dynami_robj((void *) objnod, 0x02);
    int (*rdobje_unpack)(void *, PK_ITEM *, PK_ITEM *);
    rdobje_unpack = dynami_unpack_tab[0x02];
    //
    uint64 data_size = 0x02 * sizeof (osv_oid_t);
    PK_ITEM skey, svalu;
    osv_oid_i reso_obid;
    unsigned int inde = 0x00;
    for (; 0x00 < fread(&reso_obid, sizeof (osv_oid_i), 0x01, soure); ++inde) {
        stora_ha->set_sid_key(proj_curso, (uint64 *) & reso_obid.stoid);
        // PRIN_osv_oid_t_stri((osv_oid_t *) & reso_obid);
        if (0x00 != stora_ha->search_curso(proj_curso))
            return -1;
        stora_ha->get_key(proj_curso, &skey);
        stora_ha->get_value(proj_curso, &svalu);
        rdobje_unpack((void *) objnod, &skey, &svalu);
        if (0x00 >= APPEND_DATAS(resctl->resp_stram, objnod, data_size))
            return -1;
    }
    FDAT_PRODUCE_TAIL(resctl, data_size * inde)
    OSEVPF("resctl->content_length:%llu\n", resctl->content_length);
    //
    return 0x00;
}

int hand_final_searo_rdco(plan_node_enco *firspn, rive_conne *rivcon, rive_ha *stora_ha, char *contn) {
    OSEVPF("[FUNC]:hand_final_searo_rdco\n");
    plan_node_enco *resupn = firspn->resul_node;
    //
    riv_curso_t *scurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&scurso, sto_seio->seion, contn, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 1\n");
    if (load_searo_proje_rdco(resupn->resctl, resupn->resul_set, scurso, stora_ha)) {
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

static int load_slv2q_proje_reco(respo_ctrl *resctl, FILE *soure, riv_curso_t *rcurso1, riv_curso_t *rcurso2, riv_curso_t *scurso, field_resul_co *fieres, rive_ha *stora_ha) {
    // OSEVPF("[FUNC]:load_slv2q_proje_reco\n");
    rewind(resctl->resp_stram);
    rewind(soure);
    PK_ITEM kient;
    if (!pkite_mallo(&kient, fieres->data_size))
        return -1;
    FILL_UNIQUE_OBID((osv_oid_t *) kient.data);
    //
    PK_ITEM skey, rvalu1, rvalu2;
    osv_oid_i reso_obid[0x02];
    while (0x00 < fread(&reso_obid, sizeof (osv_oid_i), 0x02, soure)) {
        if (find_refer_obid_enco(&skey, scurso, stora_ha, &reso_obid[0x00], &reso_obid[0x01]))
            continue;
        // PRIN_osv_oid_t_stri((osv_oid_t *) & reso_obid);
        stora_ha->set_sid_key(rcurso1, (uint64 *) & reso_obid[0x00].stoid);
        if (0x00 != stora_ha->search_curso(rcurso1)) {
            FREE_KITE(&kient);
            return -1;
        }
        stora_ha->get_value(rcurso1, &rvalu1);
        stora_ha->set_sid_key(rcurso2, (uint64 *) & reso_obid[0x01].stoid);
        if (0x00 != stora_ha->search_curso(rcurso2)) {
            FREE_KITE(&kient);
            return -1;
        }
        stora_ha->get_value(rcurso2, &rvalu2);
        // PASS_OBIDEN_SECTI(kient.data)
        PACKING_KEY_UNPACK(((osv_oid_i *) kient.data)->stoid, (uint64 *) skey.data);
        if (fieres->fixed_float_co) {
            if (reall_objec_pkite(&kient, &rvalu1, &rvalu2)) {
                FREE_KITE(&kient);
                return -1;
            }
        }
        if (build_proje_strea_enco(resctl->resp_stram, &kient, &rvalu1, &rvalu2, fieres)) {
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

int hfina_searq_lv2pn_reco(plan_node_enco *firspn, rive_conne *rivcon, rive_ha *stora_ha, lv2pme **lv2mep, plan_node_enco *finapn) {
    OSEVPF("[FUNC]:hfina_searq_lv2pn_enco\n");
    plan_node_enco *resupn = firspn->resul_node;
    field_resul_co *fieres = firspn->fieres;
    //
    riv_curso_t *scurso, *rcurso1, *rcurso2;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_prop(&rcurso1, sto_seio->seion, finapn->cont_name, fieres->field_str1, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    ++finapn;
    if (FINAL_QUDRY_ACCO != finapn->acti_oper) {
        stora_ha->close_curso(rcurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (stora_ha->open_curso_prop(&rcurso2, sto_seio->seion, finapn->cont_name, fieres->field_str2, "raw")) {
        stora_ha->close_curso(rcurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    ++finapn;
    if (FINAL_QUDRY_ACCO != finapn->acti_oper) {
        stora_ha->close_curso(rcurso2);
        stora_ha->close_curso(rcurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (stora_ha->open_curso_cont(&scurso, sto_seio->seion, finapn->cont_name, "raw")) {
        stora_ha->close_curso(scurso);
        stora_ha->close_curso(rcurso2);
        stora_ha->close_curso(rcurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 2\n");
    if (load_slv2q_proje_reco(firspn->resctl, resupn->resul_set, rcurso1, rcurso2, scurso, fieres, stora_ha)) {
        stora_ha->close_curso(scurso);
        stora_ha->close_curso(rcurso2);
        stora_ha->close_curso(rcurso1);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 3\n");
    stora_ha->close_curso(scurso);
    stora_ha->close_curso(rcurso2);
    stora_ha->close_curso(rcurso1);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    //
    if (resupn->resul_set) {
        fclose(resupn->resul_set);
        resupn->resul_set = NULL;
    }
    return 0x00;
}


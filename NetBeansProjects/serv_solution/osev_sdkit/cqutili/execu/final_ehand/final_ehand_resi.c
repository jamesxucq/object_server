#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_header.h"

#include "basev_bzl.h"
#include "invoko.h"
// #include "../opera_utili.h"
#include "../data_compa/data_compa.h"
#include "cqutili.h"
#include "seion_struct.h"
#include "lv2p_meta.h"
#include "kcomm_struct.h"

#include "final_ehand_resi.h"
#include "debug_funct_co.h"

//

static int load_searo_proje_rssi(respo_ctrl *resctl, FILE *soure, riv_curso_t *proj_curso, rive_ha *stora_ha) {
    // OSEVPF("[FUNC]:load_searo_proje_rssi\n");
    rewind(resctl->resp_stram);
    rewind(soure);
    osv_oid_i objnod[SCONT_CONUT_ZTAI];
    init_dynami_robj((void *) objnod, 0x01);
    int (*rdobje_unpack)(void *, PK_ITEM *, PK_ITEM *);
    rdobje_unpack = dynami_unpack_tab[0x01];
    //
    uint64 data_size = 0x01 * sizeof (osv_oid_t);
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

int hand_final_searo_rssi(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha, char *contn) {
    OSEVPF("[FUNC]:hand_final_searo_rssi\n");
    plan_node_ensi *resupn = firspn->resul_node;
    //
    riv_curso_t *scurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&scurso, sto_seio->seion, contn, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 1\n");
    if (load_searo_proje_rssi(resupn->resctl, resupn->resul_set, scurso, stora_ha)) {
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

static int load_searo_entit_rsob(respo_ctrl *resctl, FILE *soure, riv_curso_t *proj_curso, rive_ha *stora_ha) {
    // OSEVPF("[FUNC]:load_searo_entit_rsob\n");
    rewind(resctl->resp_stram);
    rewind(soure);
    osv_oid_i objnod[SCONT_CONUT_ZTAI];
    init_dynami_robj((void *) objnod, 0x01);
    int (*rdobje_unpack)(void *, PK_ITEM *, PK_ITEM *);
    rdobje_unpack = dynami_unpack_tab[0x01];
    //
    uint64 data_size = 0x01 * sizeof (osv_oid_t);
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

//

int hand_final_searo_rsob(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha, char *contn) {
    OSEVPF("[FUNC]:hand_final_searo_rsob\n");
    plan_node_ensi *resupn = firspn->resul_node;
    //
    riv_curso_t *scurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&scurso, sto_seio->seion, contn, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 1\n");
    if (load_searo_entit_rsob(resupn->resctl, resupn->resul_set, scurso, stora_ha)) {
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

static int load_searo_proje_rdsi(respo_ctrl *resctl, FILE *soure, riv_curso_t *proj_curso, rive_ha *stora_ha) {
    // OSEVPF("[FUNC]:load_searo_proje_rdsi\n");
    rewind(resctl->resp_stram);
    rewind(soure);
    osv_oid_i objnod[SCONT_CONUT_ZTAI];
    init_dynami_robj((void *) objnod, 0x01);
    int (*rdobje_unpack)(void *, PK_ITEM *, PK_ITEM *);
    rdobje_unpack = dynami_unpack_tab[0x01];
    //
    uint64 data_size = 0x01 * sizeof (osv_oid_t);
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

//

int hand_final_searo_rdsi(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha, char *contn) {
    OSEVPF("[FUNC]:hand_final_searo_rdsi\n");
    plan_node_ensi *resupn = firspn->resul_node;
    //
    riv_curso_t *scurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&scurso, sto_seio->seion, contn, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 1\n");
    if (load_searo_proje_rdsi(resupn->resctl, resupn->resul_set, scurso, stora_ha)) {
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

static int load_searo_entit_rdob(respo_ctrl *resctl, FILE *soure, riv_curso_t *proj_curso, rive_ha *stora_ha) {
    // OSEVPF("[FUNC]:load_searo_entit_rdob\n");
    rewind(resctl->resp_stram);
    rewind(soure);
    osv_oid_i objnod[SCONT_CONUT_ZTAI];
    init_dynami_robj((void *) objnod, 0x01);
    int (*rdobje_unpack)(void *, PK_ITEM *, PK_ITEM *);
    rdobje_unpack = dynami_unpack_tab[0x01];
    //
    uint64 data_size = 0x01 * sizeof (osv_oid_t);
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

//

int hand_final_searo_rdob(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha, char *contn) {
    OSEVPF("[FUNC]:hand_final_searo_rdob\n");
    plan_node_ensi *resupn = firspn->resul_node;
    //
    riv_curso_t *scurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&scurso, sto_seio->seion, contn, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 1\n");
    if (load_searo_entit_rdob(resupn->resctl, resupn->resul_set, scurso, stora_ha)) {
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

static int find_refer_obid_ensi(riv_curso_t *scurso, rive_ha *stora_ha, osv_oid_i *refer_obid) {
    stora_ha->reset_curso(scurso);
    PK_ITEM svalu;
    while (0x00 == stora_ha->next_curso(scurso)) {
        // OSEVPF("wt_next_curs\n");
        stora_ha->get_value(scurso, &svalu);
        if (refer_obid->stoid == ((unsigned long long *) svalu.data)[0x00]) {
            return 0x00;
        }
    }
    //
    return -1;
}

static int load_slv2q_proje_resi(respo_ctrl *resctl, FILE *soure, riv_curso_t *rcurso, riv_curso_t *scurso, rive_ha *stora_ha, lv2pme **lv2mep) {
    // OSEVPF("[FUNC]:load_slv2q_proje_resi\n");
    rewind(resctl->resp_stram);
    rewind(soure);
    osv_oid_t key_obid;
    FILL_UNIQUE_OBID((osv_oid_i *) & key_obid);
    //
    PK_ITEM svalu;
    osv_oid_i reso_obid;
    while (0x00 < fread(&reso_obid, sizeof (osv_oid_i), 0x01, soure)) {
        if (find_refer_obid_ensi(scurso, stora_ha, &reso_obid))
            continue;
        // PRIN_osv_oid_t_stri((osv_oid_t *) & reso_obid);
        stora_ha->set_sid_key(rcurso, (uint64 *) & reso_obid.stoid);
        if (0x00 != stora_ha->search_curso(rcurso))
            return -1;
        stora_ha->get_value(rcurso, &svalu);
        // dylid->solve(objnod, &reso_obid.stoid, &svalu);
        // 0x00 >= APPEND_DATAS(resctl->resp_stram, objnod, dylid->data_size)
        PACKING_KEY_UNPACK(((osv_oid_i *) & key_obid)->stoid, (uint64 *) & reso_obid.stoid);
        if (build_objec_strea_ensi(resctl->resp_stram, &key_obid, &svalu))
            return -1;
    }
    FDAT_PRODUCE_TAIL(resctl, ftello64(resctl->resp_stram))
    OSEVPF("resctl->content_length:%llu\n", resctl->content_length);
    //
    return 0x00;
}

//

int hfina_searq_lv2pn_resi(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha, lv2pme **lv2mep, plan_node_ensi *finapn) {
    OSEVPF("[FUNC]:hfina_searq_lv2pn_resi\n");
    plan_node_ensi *resupn = firspn->resul_node;
    //
    riv_curso_t *scurso, *rcurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_prop(&rcurso, sto_seio->seion, finapn->cont_name, finapn->source_str, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    ++finapn;
    if (FINAL_QUDRY_ACCO != finapn->acti_oper) {
        stora_ha->close_curso(rcurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    if (stora_ha->open_curso_cont(&scurso, sto_seio->seion, finapn->cont_name, "raw")) {
        stora_ha->close_curso(rcurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 2\n");
    if (load_slv2q_proje_resi(firspn->resctl, resupn->resul_set, rcurso, scurso, stora_ha, lv2mep)) {
        stora_ha->close_curso(scurso);
        stora_ha->close_curso(rcurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // OSEVPF("--- 3\n");
    stora_ha->close_curso(scurso);
    stora_ha->close_curso(rcurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    //
    if (resupn->resul_set) {
        fclose(resupn->resul_set);
        resupn->resul_set = NULL;
    }
    return 0x00;
}


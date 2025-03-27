
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "third_party.h"
#include "kcomm_header.h"

#include "cqutili.h"
#include "estri_utili.h"
#include "refresh_rcontai/refresh_rcontai.h"

#include "searo_entit_rdco.h"
#include "debug_funct_ce.h"



// teet_con:search(xx>0)|kits:pretty("oiii");
// teet_con:search(xx>0 AND ax>0)|kits:pretty("oiii");
// teet_con:search("tpp(33, 55, 77)>0")|kits:pretty("oiii");

// predicate search / condition

static int condi_searo_rdco(respo_ctrl *resctl, contain *contp, base_valu *baval, lv2pme *lv2me, char *condi) {
    OSEVPF("[FUNC]:condi_searo_rdco\n");
    OSEVPF("condition:|%s|\n", condi);
    //
    oper_node *synt_head;
    char erro_msg[LINE_LENGTH];
    if (build_query_synta(&synt_head, erro_msg, condi)) {
        OSEVPF("build_query_synta: %s\n", erro_msg);
        return -1;
    }
    //
    OSEVPF("creat_searo_plan_ensi\n");
    plan_node_enco *querpn = CREAT_PLAN_NODE_ENCO(PLAN_ITEM_SZIE);
    if (!querpn) return -1;
    if (creat_searo_plan_reco(querpn, resctl, &contp, synt_head)) {
        DESTR_PLAN_NODE_ENCO(querpn);
        // OSEVPF("--- X synt_node:%016X node_type:%u\n", synt_head, synt_head->node_type);
        DESTROY_STREE(synt_head);
        return -1;
    }
    DESTROY_STREE(synt_head);
    // PRIN_plan_node(querpn);
    // physical execute
    int searo_valu = execu_physi_searo_rdco(querpn, contp, baval, lv2me);
    DESTR_PLAN_NODE_ENCO(querpn);
    return searo_valu;
}

//

int condi_const_searo_rdco(respo_ctrl *resctl, contain *contp, base_valu *baval, lv2pme *lv2me, char *condi) {
    OSEVPF("[FUNC]:trave_const_searo_rdco\n");
    int updat_cove = chk_rcont_versi(contp->refe_coun, contp->refe_cove, &baval->conda_stm);
    switch (updat_cove) {
        case -1:
            return -1;
            break;
        case 0x01:
        {
            switch (contp->conditype) {
                case CONDI_TYPE_TRAVE:
                    if (rcontai_traver_refresh_rdco(contp, baval))
                        return -1;
                    break;
                case CONDI_TYPE_OBJID:
                    if (rcontai_objid_refresh_rdco(contp, baval))
                        return -1;
                    break;
                case CONDI_TYPE_PREDI:
                    if (rcontai_predica_refresh_rdco(contp, baval, lv2me))
                        return -1;
                    break;
                default:
                    break;
            }
        }
            break;
        case 0x00:
        default:
            break;
    }
    //
    if (condi_searo_rdco(resctl, contp, baval, lv2me, condi))
        return -1;
    if (updat_cove && updat_rcont_versi(contp->refe_coun, contp->refe_cove, &baval->conda_stm))
        return -1;
    //
    return 0x00;
}

//

static int objid_searo_rdco(respo_ctrl *resctl, rive_conne *rivcon, contain *contp, cont_lsmp *conda_stm, osv_oid_i *searo_obid) {
    OSEVPF("[FUNC]:objid_searo_rdco\n");
    osv_oid_i robj_data[SCONT_CONUT_ZTAI];
    init_dynami_robj((void *) robj_data, contp->refe_coun);
    //
    rive_ha *stora_ha = contp->stora_ha;
    riv_curso_t *rcurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&rcurso, sto_seio->seion, contp->cont_name, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    uint64 data_size = contp->refe_coun * sizeof (osv_oid_t);
    PK_ITEM skey, svalu;
    stora_ha->set_sid_key(rcurso, &searo_obid->stoid);
    if (0x00 != stora_ha->search_curso(rcurso)) {
        stora_ha->close_curso(rcurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    stora_ha->get_key(rcurso, &skey);
    stora_ha->get_value(rcurso, &svalu);
    dynami_unpack_tab[contp->refe_coun]((void *) robj_data, &skey, &svalu);
    if (0x00 >= APPEND_DATAS(resctl->resp_stram, robj_data, data_size)) {
        stora_ha->close_curso(rcurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    FDAT_PRODUCE_TAIL(resctl, data_size)
    //
    stora_ha->close_curso(rcurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    return 0x00;
}

//

int objid_const_searo_rdco(respo_ctrl *resctl, contain *contp, base_valu *baval, lv2pme *lv2me, osv_oid_i *searo_obid) {
    OSEVPF("[FUNC]:trave_const_searo_rdco\n");
    int updat_cove = chk_rcont_versi(contp->refe_coun, contp->refe_cove, &baval->conda_stm);
    switch (updat_cove) {
        case -1:
            return -1;
            break;
        case 0x01:
        {
            switch (contp->conditype) {
                case CONDI_TYPE_TRAVE:
                    if (rcontai_traver_refresh_rdco(contp, baval))
                        return -1;
                    break;
                case CONDI_TYPE_OBJID:
                    if (rcontai_objid_refresh_rdco(contp, baval))
                        return -1;
                    break;
                case CONDI_TYPE_PREDI:
                    if (rcontai_predica_refresh_rdco(contp, baval, lv2me))
                        return -1;
                    break;
                default:
                    break;
            }
        }
            break;
        case 0x00:
        default:
            break;
    }
    //
    if (objid_searo_rdco(resctl, baval->rivcon, contp, &baval->conda_stm, searo_obid))
        return -1;
    if (updat_cove && updat_rcont_versi(contp->refe_coun, contp->refe_cove, &baval->conda_stm))
        return -1;
    //
    return 0x00;
}

//

static int trave_searo_rdco(respo_ctrl *resctl, rive_conne *rivcon, contain *contp, cont_lsmp *conda_stm) {
    OSEVPF("[FUNC]:trave_searo_rdco\n");
    osv_oid_i robj_data[SCONT_CONUT_ZTAI];
    init_dynami_robj((void *) robj_data, contp->refe_coun);
    int (*rdobje_unpack)(void *, PK_ITEM *, PK_ITEM *);
    rdobje_unpack = dynami_unpack_tab[contp->refe_coun];
    //
    rive_ha *stora_ha = contp->stora_ha;
    riv_curso_t *rcurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    if (stora_ha->open_curso_cont(&rcurso, sto_seio->seion, contp->cont_name, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    uint64 data_size = contp->refe_coun * sizeof (osv_oid_t);
    PK_ITEM skey, svalu;
    unsigned int inde = 0x00;
    for (; 0x00 == stora_ha->next_curso(rcurso); ++inde) {
        // OSEVPF("wt_next_curs\n");
        stora_ha->get_key(rcurso, &skey);
        stora_ha->get_value(rcurso, &svalu);
        rdobje_unpack((void *) robj_data, &skey, &svalu);
        if (0x00 >= APPEND_DATAS(resctl->resp_stram, robj_data, data_size)) {
            stora_ha->close_curso(rcurso);
            QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
            return -1;
        }
        // log_binary_file(robj_data, lv2me->data_size, "./binary_code.bin_f");
    }
    FDAT_PRODUCE_TAIL(resctl, data_size * inde)
    OSEVPF("resctl->content_length:%llu\n", resctl->content_length);
    //
    stora_ha->close_curso(rcurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    return 0x00;
}

//

int trave_const_searo_rdco(respo_ctrl *resctl, contain *contp, base_valu *baval, lv2pme *lv2me) {
    OSEVPF("[FUNC]:trave_const_searo_rdco\n");
    int updat_cove = chk_rcont_versi(contp->refe_coun, contp->refe_cove, &baval->conda_stm);
    switch (updat_cove) {
        case -1:
            return -1;
            break;
        case 0x01:
        {
            switch (contp->conditype) {
                case CONDI_TYPE_TRAVE:
                    if (rcontai_traver_refresh_rdco(contp, baval))
                        return -1;
                    break;
                case CONDI_TYPE_OBJID:
                    if (rcontai_objid_refresh_rdco(contp, baval))
                        return -1;
                    break;
                case CONDI_TYPE_PREDI:
                    if (rcontai_predica_refresh_rdco(contp, baval, lv2me))
                        return -1;
                    break;
                default:
                    break;
            }
        }
            break;
        case 0x00:
        default:
            break;
    }
    //
    if (trave_searo_rdco(resctl, baval->rivcon, contp, &baval->conda_stm))
        return -1;
    if (updat_cove && updat_rcont_versi(contp->refe_coun, contp->refe_cove, &baval->conda_stm))
        return -1;
    //
    return 0x00;
}

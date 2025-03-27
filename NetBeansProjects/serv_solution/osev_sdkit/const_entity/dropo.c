#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_header.h"
#include "cqutili.h"
#include "estri_utili.h"
#include "lv2p_meta.h"

#include "dropo.h"
#include "debug_funct_ce.h"

// predicate drop / condition

static int condi_const_drop(contain *contp, base_valu *baval, lv2pme *lv2me, char *pamcon) {
    OSEVPF("pamcon:|%s|\n", pamcon);
    oper_node *synt_head;
    char erro_msg[LINE_LENGTH];
    if (build_query_synta(&synt_head, erro_msg, pamcon)) {
        OSEVPF("build_query_synta: %s\n", erro_msg);
        return -1;
    }
    //
    OSEVPF("creat_plan_dropo\n");
    plan_node_ensi *querpn = CREAT_PLAN_NODE_ENSI(PLAN_ITEM_SZIE);
    if (!querpn) return -1;
    if (creat_plan_dropo(querpn, contp, synt_head)) {
        DESTR_PLAN_NODE_ENSI(querpn);
        DESTROY_STREE(synt_head);
        return -1;
    }
    DESTROY_STREE(synt_head);
    PRIN_plan_node(querpn);
    // physical execute
    int drop_valu = execu_physi_dropo(querpn, contp->stora_ha, baval, lv2me);
    DESTR_PLAN_NODE_ENSI(querpn);
    return drop_valu;
}

//

int _objid_const_drop_(rive_conne *rivcon, contain *contp, osv_oid_i *drop_obid) {
    OSEVPF("[FUNC]:objeid_const_drop\n");
    rive_ha *stora_ha = contp->stora_ha;
    int drop_valu = 0x00;
    //
    riv_curso_t *dcurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    OSEVPF("contp->cont_name:|%s|\n", contp->cont_name);
    if (stora_ha->open_curso_cont(&dcurso, sto_seio->seion, contp->cont_name, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    stora_ha->set_sid_key(dcurso, &drop_obid->stoid);
    if (0x00 == stora_ha->search_curso(dcurso))
        drop_valu = stora_ha->remove_curso(dcurso);
    //
    stora_ha->close_curso(dcurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    return drop_valu;
}

//

static int trave_const_drop(rive_conne *rivcon, contain *contp) {
    OSEVPF("[FUNC]:trave_const_drop\n");
    rive_ha *stora_ha = contp->stora_ha;
    int drop_valu = 0x00;
    //
    riv_curso_t *dcurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    OSEVPF("contp->cont_name:|%s|\n", contp->cont_name);
    if (stora_ha->open_curso_cont(&dcurso, sto_seio->seion, contp->cont_name, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    while (0x00 == stora_ha->next_curso(dcurso)) {
        drop_valu = stora_ha->remove_curso(dcurso);
        if (drop_valu) break;
    }
    //
    stora_ha->close_curso(dcurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    return drop_valu;
}

//
// -1:error 0x00:ok 0x01:exception

int drop_const_predi(contain *contp, base_valu *baval, char *pamvu) {
    int drop_valu = -1;
    //
    lv2pme *lv2me = (lv2pme *) cache_value(&contp->lv2p_type, baval->lv2pm_stm.lv2pmo_hm);
    if (!lv2me) {
        OSEVPF("fdd lv2me:%p\n", lv2me);
        return -1;
    }
    // -1:error 0x00:objeid 0x01:predicate / condition 0x02:"*"
    if (pamvu) { // -1:error 0x00:objeid 0x01:predi 0x02:"*"
        switch (check_condi_type(pamvu)) {
            case PREDI_TYPE_CONDI:
                drop_valu = condi_const_drop(contp, baval, lv2me, pamvu);
                break;
            case PREDI_TYPE_TRAVE:
                drop_valu = trave_const_drop(baval->rivcon, contp);
                break;
            case PREDI_TYPE_EXCEP:
            default:
                break;
        }
    } else drop_valu = trave_const_drop(baval->rivcon, contp);
    //
    return drop_valu;
}

int drop_const_trave(contain *contp, base_valu *baval) {
    int drop_valu = -1;
    //
    lv2pme *lv2me = (lv2pme *) cache_value(&contp->lv2p_type, baval->lv2pm_stm.lv2pmo_hm);
    if (!lv2me) {
        OSEVPF("fdd lv2me:%p\n", lv2me);
        return -1;
    }
    //
    drop_valu = trave_const_drop(baval->rivcon, contp);
    return drop_valu;
}


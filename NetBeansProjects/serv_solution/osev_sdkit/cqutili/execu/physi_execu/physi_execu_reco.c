
#include "commo_header.h"
#include "kcomm_header.h"
#include "../conte_resou.h"

#include "lexic/valtok.h"
#include "gramm/synta_tree.h"
#include "plan/plan_node_ensi.h"
#include "plan/plan_node_enco.h"

#include "execu/final_ehand/final_ehand_enco.h"
#include "execu/final_ehand/final_ehand_reco.h"
#include "execu/metho_ehand/metho_ehand_enco.h"
#include "execu/metho_ehand/metho_ehand_rsco.h"
#include "execu/metho_ehand/metho_ehand_rdco.h"
#include "execu/opera_ehand/opera_ehand_enco.h"
#include "execu/opera_ehand/opera_ehand_reco.h"
#include "../execu_excep.h"
#include "../execu_utili.h"
#include "execu/resul_ehand/resul_ehand_enco.h"
#include "execu/resul_ehand/resul_ehand_rsco.h"
#include "execu/resul_ehand/resul_ehand_rdco.h"

#include "physi_execu_reco.h"

//

int execu_physi_searo_rsco(plan_node_enco *firspn, contain *contp, base_valu *baval, lv2pme *lv2me) {
    int exce_code = 0x00;
    plan_node_enco *quer_tok = firspn;
    physi_conte phys_cont;
    INITI_PHYSI_CONTE(phys_cont)
    //
    rive_ha *stora_ha = contp->stora_ha;
    OSEVPF("[FUNC]:execu_physi_searo_reco start.....\n");
    for (; quer_tok->acti_oper; ++quer_tok) {
        OSEVPF("acti_oper:%08X ", quer_tok->acti_oper);
        switch (ACTI_CODE(quer_tok->acti_oper)) {
            case INIT_QUERY_ACCO:
                OSEVPF("INIT_QUERY_ACCO\n");
                break;
            case FINAL_QUDRY_ACCO:
                OSEVPF("FINAL_QUDRY_ACCO\n");
                exce_code |= hand_final_searo_rsco(firspn, baval->rivcon, stora_ha, quer_tok->cont_name);
                break;
            case OPEN_CONTE_ACCO:
                OSEVPF("OPEN_CONTE_ACCO, open cont_name:|%s|\n", quer_tok->cont_name);
                exce_code |= hand_open_conte_enco(&phys_cont, baval->rivcon, stora_ha);
                break;
            case CLOSE_CONTE_ACCO:
                OSEVPF("CLOSE_CONTE_ACCO, close cont_name:|%s|\n", quer_tok->cont_name);
                exce_code |= hand_close_conte_enco(&phys_cont, baval->rivcon, stora_ha);
                break;
            case RESUL_SET_ACCO:
                OSEVPF("RESUL_SET_ACCO\n");
                exce_code |= hand_resul_set_rsco(quer_tok, &phys_cont, stora_ha);
                break;
            case METHO_SET_ACCO:
                OSEVPF("METHO_SET_ACCO\n");
                lev1me *lv1me = find_lev1_meta(&baval->hando_stm, quer_tok->source_str, quer_tok->parm_list, lv2me->lv2pn);
                if (lv1me) exce_code |= hand_metho_set_rsco(quer_tok, &phys_cont, stora_ha, lv1me);
                else exce_code |= -1;
                break;
            case OPERA_SET_ACCO:
                OSEVPF("OPERA_SET_ACCO\n");
                exce_code |= hand_opera_set_rsco(quer_tok);
                break;
        }
        if (exce_code) {
            OSEVPF("HAND_EXCEPTION\n");
            hand_searo_excep_enco(quer_tok, firspn->resul_node, &phys_cont, baval->rivcon, stora_ha);
            return -1;
        }
    }
    //
    OSEVPF("execu_physi_searo_reco end.....\n");
    return 0x00;
}

//

int execu_physi_searo_rdco(plan_node_enco *firspn, contain *contp, base_valu *baval, lv2pme *lv2me) {
    int exce_code = 0x00;
    plan_node_enco *quer_tok = firspn;
    physi_conte phys_cont;
    INITI_PHYSI_CONTE(phys_cont)
    //
    rive_ha *stora_ha = contp->stora_ha;
    OSEVPF("[FUNC]:execu_physi_searo_reco start.....\n");
    for (; quer_tok->acti_oper; ++quer_tok) {
        OSEVPF("acti_oper:%08X ", quer_tok->acti_oper);
        switch (ACTI_CODE(quer_tok->acti_oper)) {
            case INIT_QUERY_ACCO:
                OSEVPF("INIT_QUERY_ACCO\n");
                break;
            case FINAL_QUDRY_ACCO:
                OSEVPF("FINAL_QUDRY_ACCO\n");
                exce_code |= hand_final_searo_rdco(firspn, baval->rivcon, stora_ha, quer_tok->cont_name);
                break;
            case OPEN_CONTE_ACCO:
                OSEVPF("OPEN_CONTE_ACCO, open cont_name:|%s|\n", quer_tok->cont_name);
                exce_code |= hand_open_conte_enco(&phys_cont, baval->rivcon, stora_ha);
                break;
            case CLOSE_CONTE_ACCO:
                OSEVPF("CLOSE_CONTE_ACCO, close cont_name:|%s|\n", quer_tok->cont_name);
                exce_code |= hand_close_conte_enco(&phys_cont, baval->rivcon, stora_ha);
                break;
            case RESUL_SET_ACCO:
                OSEVPF("RESUL_SET_ACCO\n");
                exce_code |= hand_resul_set_rdco(quer_tok, &phys_cont, stora_ha);
                break;
            case METHO_SET_ACCO:
                OSEVPF("METHO_SET_ACCO\n");
                lev1me *lv1me = find_lev1_meta(&baval->hando_stm, quer_tok->source_str, quer_tok->parm_list, lv2me->lv2pn);
                if (lv1me) exce_code |= hand_metho_set_rdco(quer_tok, &phys_cont, stora_ha, lv1me);
                else exce_code |= -1;
                break;
            case OPERA_SET_ACCO:
                OSEVPF("OPERA_SET_ACCO\n");
                exce_code |= hand_opera_set_rdco(quer_tok);
                break;
        }
        if (exce_code) {
            OSEVPF("HAND_EXCEPTION\n");
            hand_searo_excep_enco(quer_tok, firspn->resul_node, &phys_cont, baval->rivcon, stora_ha);
            return -1;
        }
    }
    //
    OSEVPF("execu_physi_searo_reco end.....\n");
    return 0x00;
}

//

int ephys_searq_lv2pn_reco(plan_node_enco *firspn, rive_ha *stora_ha, base_valu *baval, lv2pme **lv2mep) {
    int exce_code = 0x00;
    plan_node_enco *quer_tok = firspn;
    physi_conte phys_cont;
    INITI_PHYSI_CONTE(phys_cont)
    //
    OSEVPF("[FUNC]:ephys_searq_lv2pn_reco start.....\n");
    for (; quer_tok->acti_oper; ++quer_tok) {
        OSEVPF("acti_oper:%08X ", quer_tok->acti_oper);
        switch (ACTI_CODE(quer_tok->acti_oper)) {
            case INIT_QUERY_ACCO:
                OSEVPF("INIT_QUERY_ACCO\n");
                break;
            case FINAL_QUDRY_ACCO:
                OSEVPF("FINAL_QUDRY_ACCO\n");
                exce_code |= hfina_searq_lv2pn_reco(firspn, baval->rivcon, stora_ha, lv2mep, quer_tok);
                break;
            case OPEN_CONTE_ACCO:
                OSEVPF("OPEN_CONTE_ACCO, open cont_name:|%s|\n", quer_tok->cont_name);
                exce_code |= hand_open_conte_enco(&phys_cont, baval->rivcon, stora_ha);
                break;
            case CLOSE_CONTE_ACCO:
                OSEVPF("CLOSE_CONTE_ACCO, close cont_name:|%s|\n", quer_tok->cont_name);
                exce_code |= hand_close_conte_enco(&phys_cont, baval->rivcon, stora_ha);
                break;
            case RESUL_SET_ACCO:
                OSEVPF("RESUL_SET_ACCO\n");
                exce_code |= hand_resul_set_enco(quer_tok, &phys_cont, stora_ha);
                break;
            case METHO_SET_ACCO:
                OSEVPF("METHO_SET_ACCO\n");
                // lev1me *lv1me = find_lev1_meta(hando_stm, quer_tok->source_str, quer_tok->parm_list, lv2mep[0x00]->lv2pn);
                // if (lv1me) exce_code |= hand_metho_set_enco(quer_tok, &phys_cont, stora_ha, lv1me);
                // else exce_code |= -1;
                break;
            case OPERA_SET_ACCO:
                OSEVPF("OPERA_SET_ACCO\n");
                exce_code |= hand_opera_set_enco(quer_tok);
                break;
        }
        if (exce_code) {
            OSEVPF("HAND_EXCEPTION\n");
            hand_searq_excep_enco(quer_tok, firspn->resul_node, &phys_cont, baval->rivcon, stora_ha);
            return -1;
        }
    }
    //
    OSEVPF("ephys_searq_lv2pn_reco end.....\n");
    return 0x00;
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_header.h"

#include "basev_bzl.h"
#include "cqutili.h"
#include "estri_utili.h"

#include "invoko.h"
#include "debug_funct_ce.h"
#include "kcomm_struct.h"

// todo: 20240312
//　teet_con:invoke("tpp(33)")|kits:pretty("oi");
// predicate search / condition

static int condi_const_invok(respo_ctrl *resctl, rive_conne *rivcon, contain *contp, lev1me *lv1me, char *parm_oivk, char *pamcon) {
    OSEVPF("[FUNC]:condi_const_invok\n");
    OSEVPF("pamcon:|%s|\n", pamcon);
    //
    oper_node *synt_head;
    char erro_msg[LINE_LENGTH];
    if (build_query_synta(&synt_head, erro_msg, pamcon)) {
        OSEVPF("build_query_synta: %s\n", erro_msg);
        return -1;
    }
    //
    OSEVPF("[FUNC]:creat_plan_dropo\n");
    plan_node_ensi *querpn = CREAT_PLAN_NODE_ENSI(PLAN_ITEM_SZIE);
    if (!querpn) return -1;
    if (creat_plan_invoko(querpn, resctl, contp, synt_head)) {
        DESTR_PLAN_NODE_ENSI(querpn);
        DESTROY_STREE(synt_head);
        return -1;
    }
    DESTROY_STREE(synt_head);
    PRIN_plan_node(querpn);
    // physical execute
    int invo_valu = execu_physi_invoko(querpn, rivcon, contp->stora_ha, lv1me, parm_oivk);
    DESTR_PLAN_NODE_ENSI(querpn);
    return invo_valu;
}

//

static int objid_const_invok(respo_ctrl *resctl, rive_conne *rivcon, contain *contp, lev1me *lv1me, char *parm_oivk, osv_oid_i *invk_obid) {
    rive_ha *stora_ha = contp->stora_ha;
    OSEVPF("[FUNC]:objid_const_invok, lv1me->oivk_retyp_oe:%d\n", lv1me->oivk_retyp_oe);
    //
    riv_curso_t *dcurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) return -1;
    OSEVPF("contp->contp:|%s|\n", contp->cont_name);
    if (stora_ha->open_curso_cont(&dcurso, sto_seio->seion, contp->cont_name, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    loop_memo_t obje_memo;
    if (!loop_malloc(&obje_memo, lv1me->lv2me)) {
        stora_ha->close_curso(dcurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    PK_ITEM key, valu;
    stora_ha->set_sid_key(dcurso, &invk_obid->stoid);
    if (0x00 != stora_ha->search_curso(dcurso)) {
        free_loop(&obje_memo);
        stora_ha->close_curso(dcurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    stora_ha->get_key(dcurso, &key);
    stora_ha->get_value(dcurso, &valu);
    //
    oreval rvalu;
    FILL_UNIQUE_OBID((osv_oid_t *) & rvalu.obje_obid);
    int rval_len = type_rvlen_tab[lv1me->oivk_retyp_oe];
    if (bound_objec_loop(&obje_memo, (uint64 *) key.data, &valu, lv1me->lv2me)) {
        free_loop(&obje_memo);
        stora_ha->close_curso(dcurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    rvalu.obje_obid.stoid = ((osv_oid_i *) obje_memo.data)->stoid;
    lv1me->method.invoke(&rvalu, obje_memo.data, parm_oivk);
    //
    if (solve_value_loop(&valu, &obje_memo, lv1me->lv2me)) {
        free_loop(&obje_memo);
        stora_ha->close_curso(dcurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    // stora_ha->set_key(dcurso, &key);
    stora_ha->set_value(dcurso, &valu);
    if (!stora_ha->update_curso(dcurso)) {
        if (0x00 >= APPEND_DATAS(resctl->resp_stram, (char *) &rvalu, rval_len)) {
            free_loop(&obje_memo);
            stora_ha->close_curso(dcurso);
            QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
            return -1;
        }
    }
    FDAT_PRODUCE_TAIL(resctl, ftello64(resctl->resp_stram))
    //
    free_loop(&obje_memo);
    stora_ha->close_curso(dcurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    return 0x00;
}

//

static int trave_const_invok(respo_ctrl *resctl, rive_conne *rivcon, contain *contp, lev1me *lv1me, char *parm_oivk) {
    rive_ha *stora_ha = contp->stora_ha;
    OSEVPF("[FUNC]:trave_const_invok, lv1me->oivk_retyp_oe:%d\n", lv1me->oivk_retyp_oe);
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
    loop_memo_t obje_memo;
    if (!loop_malloc(&obje_memo, lv1me->lv2me)) {
        stora_ha->close_curso(dcurso);
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    PK_ITEM key, valu;
    oreval rvalu;
    FILL_UNIQUE_OBID((osv_oid_t *) & rvalu.obje_obid);
    int rval_len = type_rvlen_tab[lv1me->oivk_retyp_oe];
    while (0x00 == stora_ha->next_curso(dcurso)) {
        stora_ha->get_key(dcurso, &key);
        stora_ha->get_value(dcurso, &valu);
        if (bound_objec_loop(&obje_memo, (uint64 *) key.data, &valu, lv1me->lv2me)) {
            free_loop(&obje_memo);
            stora_ha->close_curso(dcurso);
            QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
            return -1;
        }
        rvalu.obje_obid.stoid = ((osv_oid_i *) obje_memo.data)->stoid;
        lv1me->method.invoke(&rvalu, obje_memo.data, parm_oivk);
        // PK_ITEM key, valu;
        if (solve_value_loop(&valu, &obje_memo, lv1me->lv2me)) {
            free_loop(&obje_memo);
            stora_ha->close_curso(dcurso);
            QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
            return -1;
        }
        //
        stora_ha->set_value(dcurso, &valu);
        if (!stora_ha->update_curso(dcurso)) {
            if (0x00 >= APPEND_DATAS(resctl->resp_stram, (char *) &rvalu, rval_len)) {
                free_loop(&obje_memo);
                stora_ha->close_curso(dcurso);
                QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
                return -1;
            }
        }
    }
    FDAT_PRODUCE_TAIL(resctl, ftello64(resctl->resp_stram))
    OSEVPF("resctl->content_length:%llu\n", resctl->content_length);
    //
    free_loop(&obje_memo);
    stora_ha->close_curso(dcurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    return 0x00;
}

//
#define EPAM_INVK_METHOD     0x00
#define EPAM_INVK_CONDIT     0x01

int invok_const_predi(respo_ctrl *resctl, contain *contp, base_valu *baval, lv2pme *lv2me, char **pamvp) {
    OSEVPF("[FUNC]: invok_const_predi\n");
    OSEVPF("lv2pn:|%s| pamvp[EPAM_INVK_METHOD]:|%s| pamvp[EPAM_INVK_CONDIT]:|%s|\n", lv2me->lv2pn, pamvp[EPAM_INVK_METHOD], pamvp[EPAM_INVK_CONDIT]);
    //
    char invo_lv2n[LVTN_LENGTH];
    char invo_lv1n[LVON_LENGTH];
    pams_invk parm_invo;
    if (decode_invok_parms(invo_lv2n, invo_lv1n, &parm_invo, pamvp[EPAM_INVK_METHOD]))
        return -1;
    if (strcmp(lv2me->lv2pn, invo_lv2n)) {
        if (NOT_ZERO(invo_lv2n))
            return -1;
        strcpy(invo_lv2n, lv2me->lv2pn);
    }
    char handn[HANDN_LENGTH];
    if (!filli_binary_handn(handn, invo_lv2n, invo_lv1n, parm_invo.pamvp))
        return -1;
    OSEVPF("cuo handn:|%s| lv2pn:|%s|\n", handn, lv2me->lv2pn);
    //
    lev1me *lv1me = (lev1me *) action_value(handn, baval->hando_stm.lev1n_hm);
    if (!lv1me) {
        OSEVPF("doh lv1me:%p lev1n_hm:%p\n", lv1me, baval->hando_stm.lev1n_hm);
        return -1;
    }
    // lv1me->parser(parm_invo.pamvp);
    char *parm_oivk = (char *) malloc(lv1me->oivk_size_oe);
    if (!parm_oivk) return -1;
    if (build_oinvk_parms(parm_oivk, parm_invo.pamvp))
        return -1;
    //    
    int invo_valu = -1;
    if (pamvp[EPAM_INVK_CONDIT]) { // -1:error 0x00:objeid 0x01:predi 0x02:"*"
        switch (check_condi_type(pamvp[EPAM_INVK_CONDIT])) {
            case PREDI_TYPE_CONDI:
                invo_valu = condi_const_invok(resctl, baval->rivcon, contp, lv1me, parm_oivk, pamvp[EPAM_INVK_CONDIT]);
                break;
            case PREDI_TYPE_TRAVE:
                invo_valu = trave_const_invok(resctl, baval->rivcon, contp, lv1me, parm_oivk);
                break;
            case PREDI_TYPE_EXCEP:
            default:
                break;
        }
    } else invo_valu = trave_const_invok(resctl, baval->rivcon, contp, lv1me, parm_oivk);
    //
    free(parm_oivk);
    return invo_valu;
}

int invok_const_objid(respo_ctrl *resctl, contain *contp, base_valu *baval, lv2pme *lv2me, char **pamvp) {
    OSEVPF("[FUNC]:invok_const_objid\n");
    // OSEVPF("lv2pn:|%s| pamvp[EPAM_INVK_METHOD]:|%s|\n", lv2me->lv2pn, pamvp[EPAM_INVK_METHOD]);
    // OSEVPF("pamvp[EPAM_INVK_CONDIT]:|%s|\n", pamvp[EPAM_INVK_CONDIT]);
    char invo_lv2n[LVTN_LENGTH];
    char invo_lv1n[LVON_LENGTH];
    pams_invk parm_invo;
    if (decode_invok_parms(invo_lv2n, invo_lv1n, &parm_invo, pamvp[EPAM_INVK_METHOD]))
        return -1;
    if (strcmp(lv2me->lv2pn, invo_lv2n)) {
        if (NOT_ZERO(invo_lv2n))
            return -1;
        strcpy(invo_lv2n, lv2me->lv2pn);
    }
    char handn[HANDN_LENGTH];
    if (!filli_binary_handn(handn, invo_lv2n, invo_lv1n, parm_invo.pamvp))
        return -1;
    OSEVPF("cuo handn:|%s| lv2pn:|%s|\n", handn, lv2me->lv2pn);
    //
    lev1me *lv1me = (lev1me *) action_value(handn, baval->hando_stm.lev1n_hm);
    if (!lv1me) {
        OSEVPF("doh lv1me:%p lev1n_hm:%p\n", lv1me, baval->hando_stm.lev1n_hm);
        return -1;
    }
    // lv1me->parser(parm_invo.pamvp);
    PRIN_lev1me(lv1me);
    char *parm_oivk = (char *) malloc(lv1me->oivk_size_oe);
    if (!parm_oivk) return -1;
    if (build_oinvk_parms(parm_oivk, parm_invo.pamvp))
        return -1;
    // obid_entit
    if (INSTAN_UNIQUE != ((osv_oid_i *) pamvp[EPAM_INVK_CONDIT])->osev_unique) {
        free(parm_oivk);
        return -1;
    }
    int invo_valu = objid_const_invok(resctl, baval->rivcon, contp, lv1me, parm_oivk, (osv_oid_i *) pamvp[EPAM_INVK_CONDIT]);
    //
    free(parm_oivk);
    return invo_valu;
}

int invok_const_trave(respo_ctrl *resctl, contain *contp, base_valu *baval, lv2pme *lv2me, char **pamvp) {
    OSEVPF("[FUNC]:invok_const_trave\n");
    OSEVPF("lv2pn:|%s| pamvp[EPAM_INVK_METHOD]:|%s| pamvp[EPAM_INVK_CONDIT]:|%s|\n", lv2me->lv2pn, pamvp[EPAM_INVK_METHOD], pamvp[EPAM_INVK_CONDIT]);
    //
    char invo_lv2n[LVTN_LENGTH];
    char invo_lv1n[LVON_LENGTH];
    pams_invk parm_invo;
    if (decode_invok_parms(invo_lv2n, invo_lv1n, &parm_invo, pamvp[EPAM_INVK_METHOD]))
        return -1;
    if (strcmp(lv2me->lv2pn, invo_lv2n)) {
        if (NOT_ZERO(invo_lv2n))
            return -1;
        strcpy(invo_lv2n, lv2me->lv2pn);
    }
    char handn[HANDN_LENGTH];
    if (!filli_binary_handn(handn, invo_lv2n, invo_lv1n, parm_invo.pamvp))
        return -1;
    OSEVPF("cuo handn:|%s| lv2pn:|%s|\n", handn, lv2me->lv2pn);
    //
    lev1me * lv1me = (lev1me *) action_value(handn, baval->hando_stm.lev1n_hm);
    if (!lv1me) {
        OSEVPF("doh lv1me:%p lev1n_hm:%p\n", lv1me, baval->hando_stm.lev1n_hm);
        return -1;
    }
    // lv1me->parser(parm_invo.pamvp);
    char *parm_oivk = (char *) malloc(lv1me->oivk_size_oe);
    if (!parm_oivk) return -1;
    if (build_oinvk_parms(parm_oivk, parm_invo.pamvp))
        return -1;
    //    
    int invo_valu = trave_const_invok(resctl, baval->rivcon, contp, lv1me, parm_oivk);
    free(parm_oivk);
    return invo_valu;
}
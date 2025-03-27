#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_header.h"
#include "basev_bzl.h"
#include "cqutili.h"
#include "astri_utili.h"

#include "invokq.h"

// todo: 20240312
// predicate invo / condition

static int condi_qcont_invok(respo_ctrl *resctl, riv_curso_t *dcurso, rive_ha *stora_ha, lev1me *lv1me, char *lv2pn, char *pamcon) {
    OSEVPF("[FUNC]:predica contao, lv1me->oivk_retyp_oe:%d\n", lv1me->oivk_retyp_oe);
    //
    return 0x00;
}

//

static int objid_qcont_invok(respo_ctrl *resctl, riv_curso_t *dcurso, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, osv_oid_i *obje_obid) {
    OSEVPF("[FUNC]:objid_qcont_invok, lv1me->oivk_retyp_oe:%d\n", lv1me->oivk_retyp_oe);
    loop_memo_t obje_memo;
    if (!loop_malloc(&obje_memo, lv1me->lv2me))
        return -1;
    //
    PK_ITEM key, valu;
    stora_ha->set_sid_key(dcurso, &obje_obid->stoid);
    if (0x00 != stora_ha->search_curso(dcurso)) {
        free_loop(&obje_memo);
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
        return -1;
    }
    rvalu.obje_obid.stoid = ((osv_oid_i *) obje_memo.data)->stoid;
    lv1me->method.invoke(&rvalu, obje_memo.data, parm_oivk);
    //
    if (solve_value_loop(&valu, &obje_memo, lv1me->lv2me)) {
        free_loop(&obje_memo);
        return -1;
    }
    // stora_ha->set_key(dcurso, &key);
    stora_ha->set_value(dcurso, &valu);
    if (!stora_ha->update_curso(dcurso)) {
        if (0x00 >= APPEND_DATAS(resctl->resp_stram, (char *) &rvalu, rval_len)) {
            free_loop(&obje_memo);
            return -1;
        }
    }
    FDAT_PRODUCE_TAIL(resctl, ftello64(resctl->resp_stram))
    //
    free_loop(&obje_memo);
    return 0x00;
}

//

static int trave_qcont_invok(respo_ctrl *resctl, riv_curso_t *dcurso, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk) {
    OSEVPF("[FUNC]:invoke traver contao, lv1me->oivk_retyp_oe:%d\n", lv1me->oivk_retyp_oe);
    loop_memo_t obje_memo;
    if (!loop_malloc(&obje_memo, lv1me->lv2me))
        return -1;
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
            return -1;
        }
        rvalu.obje_obid.stoid = ((osv_oid_i *) obje_memo.data)->stoid;
        lv1me->method.invoke(&rvalu, obje_memo.data, parm_oivk);
        ///
        if (solve_value_loop(&valu, &obje_memo, lv1me->lv2me)) {
            free_loop(&obje_memo);
            return -1;
        }
        // stora_ha->set_key(dcurso, &key);
        stora_ha->set_value(dcurso, &valu);
        if (!stora_ha->update_curso(dcurso)) {
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

//
#define QPAM_INVK_METHOD     0x00
#define QPAM_INVK_SOURCE     0x01
#define QPAM_INVK_CONDIT     0x02

int invok_qcont_predi(respo_ctrl *resctl, contain *contp, lv2pme *lv2me, hand_hmap *hando_stm, rive_conne *rivcon, char **pamvp) {
    OSEVPF("[FUNC]:invok_qcont_predi\n");
    OSEVPF("pamvp[QPAM_INVK_METHOD]:|%s|\n", pamvp[QPAM_INVK_METHOD]);
    //
    char invo_lv2n[LVTN_LENGTH];
    char invo_lv1n[LVON_LENGTH];
    pams_invk parm_invo;
    if (decode_invok_parms(invo_lv2n, invo_lv1n, &parm_invo, pamvp[QPAM_INVK_SOURCE]))
        return -1;
    if (strcmp(lv2me->lv2pn, invo_lv2n)) {
        // if (IS_ZERO(invo_lv2n) || !strcmp(invo_lv2n, pamvp[QPAM_INVK_METHOD]))
        if (NOT_ZERO(invo_lv2n))
            return -1;
        strcpy(invo_lv2n, lv2me->lv2pn);
    }
    char handn[HANDN_LENGTH];
    if (!filli_binary_handn(handn, invo_lv2n, invo_lv1n, parm_invo.pamvp))
        return -1;
    OSEVPF("cuo handn:|%s| lv2pn:|%s|\n", handn, lv2me->lv2pn);
    //
    lev1me *lv1me = (lev1me *) action_value(handn, hando_stm->lev1n_hm);
    if (!lv1me) {
        OSEVPF("doh lv1me:%p lev1n_hm:%p\n", lv1me, hando_stm->lev1n_hm);
        return -1;
    }
    // lv1me->parser(parm_invo.pamvp);
    char *parm_oivk = (char *) malloc(lv1me->oivk_size_oe);
    if (!parm_oivk) return -1;
    if (build_oinvk_parms(parm_oivk, parm_invo.pamvp))
        return -1;
    //
    rive_ha *stora_ha = contp->stora_ha;
    riv_curso_t *dcurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) {
        free(parm_oivk);
        return -1;
    }
    OSEVPF("contp->cont_name:|%s|\n", contp->cont_name);
    if (stora_ha->open_curso_cont(&dcurso, sto_seio->seion, contp->cont_name, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        free(parm_oivk);
        return -1;
    }
    //    
    int invo_valu = -1;
    if (pamvp[QPAM_INVK_CONDIT]) { // -1:error 0x00:objeid 0x01:predi QPAM_INVK_CONDIT:"*"
        switch (check_condi_type(pamvp[QPAM_INVK_CONDIT])) {
            case PREDI_TYPE_CONDI:
                invo_valu = condi_qcont_invok(resctl, dcurso, stora_ha, lv1me, lv2me->lv2pn, pamvp[QPAM_INVK_CONDIT]);
                break;
            case PREDI_TYPE_TRAVE:
                invo_valu = trave_qcont_invok(resctl, dcurso, stora_ha, lv1me, parm_oivk);
                break;
            case PREDI_TYPE_EXCEP:
            default:
                break;
        }
    } else invo_valu = trave_qcont_invok(resctl, dcurso, stora_ha, lv1me, parm_oivk);
    //
    stora_ha->close_curso(dcurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    free(parm_oivk);
    return invo_valu;
}

//

int invok_qcont_objid(respo_ctrl *resctl, contain *contp, lv2pme *lv2me, hand_hmap *hando_stm, rive_conne *rivcon, char **pamvp) {
    OSEVPF("[FUNC]:invok_qcont_objid\n");
    // OSEVPF("pamvp[QPAM_INVK_METHOD]:|%s|\n", pamvp[QPAM_INVK_METHOD]);
    //
    char invo_lv2n[LVTN_LENGTH];
    char invo_lv1n[LVON_LENGTH];
    pams_invk parm_invo;
    if (decode_invok_parms(invo_lv2n, invo_lv1n, &parm_invo, pamvp[QPAM_INVK_SOURCE]))
        return -1;
    if (strcmp(lv2me->lv2pn, invo_lv2n)) {
        // if (IS_ZERO(invo_lv2n) || !strcmp(invo_lv2n, pamvp[QPAM_INVK_METHOD]))
        if (NOT_ZERO(invo_lv2n))
            return -1;
        strcpy(invo_lv2n, lv2me->lv2pn);
    }
    char handn[HANDN_LENGTH];
    if (!filli_binary_handn(handn, invo_lv2n, invo_lv1n, parm_invo.pamvp))
        return -1;
    OSEVPF("cuo handn:|%s| lv2pn:|%s|\n", handn, lv2me->lv2pn);
    //
    lev1me * lv1me = (lev1me *) action_value(handn, hando_stm->lev1n_hm);
    if (!lv1me) {
        OSEVPF("doh lv1me:%p lev1n_hm:%p\n", lv1me, hando_stm->lev1n_hm);
        return -1;
    }
    // lv1me->parser(parm_invo.pamvp);
    char *parm_oivk = (char *) malloc(lv1me->oivk_size_oe);
    if (!parm_oivk) return -1;
    if (build_oinvk_parms(parm_oivk, parm_invo.pamvp))
        return -1;
    //
    rive_ha *stora_ha = contp->stora_ha;
    riv_curso_t *dcurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) {
        free(parm_oivk);
        return -1;
    }
    OSEVPF("contp->cont_name:|%s|\n", contp->cont_name);
    if (stora_ha->open_curso_cont(&dcurso, sto_seio->seion, contp->cont_name, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        free(parm_oivk);
        return -1;
    }
    if (INSTAN_UNIQUE != ((osv_oid_i *) pamvp[QPAM_INVK_CONDIT])->osev_unique) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        free(parm_oivk);
        return -1;
    }
    int invo_valu = objid_qcont_invok(resctl, dcurso, stora_ha, lv1me, parm_oivk, (osv_oid_i *) pamvp[QPAM_INVK_CONDIT]);
    //
    stora_ha->close_curso(dcurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    free(parm_oivk);
    return invo_valu;
}

int invok_qcont_trave(respo_ctrl *resctl, contain *contp, lv2pme *lv2me, hand_hmap *hando_stm, rive_conne *rivcon, char **pamvp) {
    OSEVPF("[FUNC]:invok_qcont_trave\n");
    OSEVPF("pamvp[QPAM_INVK_METHOD]:|%s|\n", pamvp[QPAM_INVK_METHOD]);
    //
    char invo_lv2n[LVTN_LENGTH];
    char invo_lv1n[LVON_LENGTH];
    pams_invk parm_invo;
    if (decode_invok_parms(invo_lv2n, invo_lv1n, &parm_invo, pamvp[QPAM_INVK_SOURCE]))
        return -1;
    if (strcmp(lv2me->lv2pn, invo_lv2n)) {
        // if (IS_ZERO(invo_lv2n) || !strcmp(invo_lv2n, pamvp[QPAM_INVK_METHOD]))
        if (NOT_ZERO(invo_lv2n))
            return -1;
        strcpy(invo_lv2n, lv2me->lv2pn);
    }
    char handn[HANDN_LENGTH];
    if (!filli_binary_handn(handn, invo_lv2n, invo_lv1n, parm_invo.pamvp))
        return -1;
    OSEVPF("cuo handn:|%s| lv2pn:|%s|\n", handn, lv2me->lv2pn);
    //
    lev1me * lv1me = (lev1me *) action_value(handn, hando_stm->lev1n_hm);
    if (!lv1me) {
        OSEVPF("doh lv1me:%p lev1n_hm:%p\n", lv1me, hando_stm->lev1n_hm);
        return -1;
    }
    // lv1me->parser(parm_invo.pamvp);
    char *parm_oivk = (char *) malloc(lv1me->oivk_size_oe);
    if (!parm_oivk) return -1;
    if (build_oinvk_parms(parm_oivk, parm_invo.pamvp))
        return -1;
    //
    rive_ha *stora_ha = contp->stora_ha;
    riv_curso_t *dcurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
    if (!sto_seio) {
        free(parm_oivk);
        return -1;
    }
    OSEVPF("contp->cont_name:|%s|\n", contp->cont_name);
    if (stora_ha->open_curso_cont(&dcurso, sto_seio->seion, contp->cont_name, "raw")) {
        QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
        free(parm_oivk);
        return -1;
    }
    int invo_valu = trave_qcont_invok(resctl, dcurso, stora_ha, lv1me, parm_oivk);
    //
    stora_ha->close_curso(dcurso);
    QUIET_SESSION_BZL(rivcon, stora_ha, sto_seio);
    free(parm_oivk);
    return invo_valu;
}

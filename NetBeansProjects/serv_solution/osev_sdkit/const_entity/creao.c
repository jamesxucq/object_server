
#include <ctype.h>

#include "commo_header.h"
#include "kcomm_header.h"
#include "estri_utili.h"
#include "creao.h"
#include "lv2p_meta.h"
#include "loop_memo.h"

// #include "plan/quer_plan_ensi.h"
// #include "debug_funct_ce.h"

//
// cursor->set_key(cursor, ); /* Insert a record. */
// cursor->set_value(cursor, "value1"); // fixme: 20170210
// -1:error 0x00:ok 0x01:exception

int _blank_defau_entit_(respo_ctrl *resctl, riv_curso_t *dcurso, rive_ha *stora_ha, lv2pme *lv2me) {
    OSEVPF("[FUNC]:_blank_defau_entit_\n");
    loop_memo_t obje_memo;
    if (!loop_malloc(&obje_memo, lv2me))
        return -1;
    memset(obje_memo.data, '\0', lv2me->data_size);
    creat_objec_obid((osv_oid_t *) obje_memo.data);
    // OSEVPF("pamvp, [0]:|%d| [1]:|%d|\n", *((int *) (pamvp[0x00] + 0x01)), ((int *) (pamvp[0x01] + 0x01))[0x00]);
    PRIN_test_object((struct test *) obje_memo.data);
    PK_ITEM key, valu;
    if (solve_objec_loop(&key, &valu, &obje_memo, lv2me)) {
        free_loop(&obje_memo);
        return -1;
    }
    stora_ha->set_key(dcurso, &key);
    stora_ha->set_value(dcurso, &valu);
    int creat_valu = stora_ha->inser_curso(dcurso);
    if (!creat_valu) {
        OBID_BINARY_COPY((osv_oid_t *) resctl->resp_memo, (osv_oid_t *) obje_memo.data);
        PDAT_PRODUCEM_TAIL(resctl, OBJE_IDENTI_BLEN)
    }
    //
    free_loop(&obje_memo);
    return creat_valu;
}

//
// taat:taat(33,44,5555);
// -1:error 0x00:ok 0x01:exception

int _full_defau_entit_(respo_ctrl *resctl, riv_curso_t *dcurso, rive_ha *stora_ha, lv2pme *lv2me, char *basen, char **pamvp) {
    OSEVPF("[FUNC]:_full_defau_entit_\n");
    OSEVPF("lv2me->data_size:%llu\n", lv2me->data_size);
    lv2p_prop lv2nod[LVTNOD_COUNT];
    if (parse_lev2p_prope(lv2nod, basen, lv2me->lv2pn))
        return -1;
    // PRIN_lv2p_prop_array(lv2nod);
    if (chk_lev1_type(lv2nod, pamvp))
        return 0x01;
    //
    valu_memo_t obje_memo = INIT_ZERO_VMEM;
    uint64 pack_size = count_pack_size(pamvp, lv2me);
    if (!pack_size) return 0x01;
    if (!valu_reallo(&obje_memo, pack_size))
        return -1;
    creat_objec_obid((osv_oid_t *) obje_memo.data);
    // OSEVPF("pamvp, [0]:|%d| [1]:|%d|\n", *((int *) (pamvp[0x00] + 0x01)), ((int *) (pamvp[0x01] + 0x01))[0x00]);
    // PRIN_test_object((struct test *) obje_memo.data);
    PK_ITEM key, valu;
    if (solve_lv2p_prop(&key, &valu, &obje_memo, pamvp, lv2me)) {
        free_valu(&obje_memo);
        return -1;
    }
    // _bind_taat_(obje_memo, &key, &valu);
    stora_ha->set_key(dcurso, &key);
    stora_ha->set_value(dcurso, &valu);
    int creat_valu = stora_ha->inser_curso(dcurso);
    if (!creat_valu) {
        OBID_BINARY_COPY((osv_oid_t *) resctl->resp_memo, (osv_oid_t *) obje_memo.data);
        PDAT_PRODUCEM_TAIL(resctl, OBJE_IDENTI_BLEN)
    }
    //
    free_valu(&obje_memo);
    return creat_valu;
}

// taat:taat(33,44,5555);

int _user_creat_entit_(respo_ctrl *resctl, riv_curso_t *dcurso, rive_ha *stora_ha, lev1me *lv1me, char **pamvp) {
    OSEVPF("[FUNC]:_user_creat_entit_\n");
    loop_memo_t obje_memo;
    if (!loop_malloc(&obje_memo, lv1me->lv2me))
        return -1;
    creat_objec_obid((osv_oid_t *) obje_memo.data);
    // OSEVPF("pamvp, [0]:|%d| [1]:|%d|\n", *((int *) (pamvp[0x00] + 0x01)), ((int *) (pamvp[0x01] + 0x01))[0x00]);
    char *parm_oivk = (char *) malloc(lv1me->oivk_size_oe);
    if (!parm_oivk) {
        free_loop(&obje_memo);
        return -1;
    }
    if (build_oinvk_parms(parm_oivk, pamvp))
        return -1;
    lv1me->method.constr(obje_memo.data, parm_oivk);
    //
    PRIN_test_object((struct test *) obje_memo.data);
    PK_ITEM key, valu;
    if (solve_objec_loop(&key, &valu, &obje_memo, lv1me->lv2me)) {
        free(parm_oivk);
        free_loop(&obje_memo);
        return -1;
    }
    stora_ha->set_key(dcurso, &key);
    stora_ha->set_value(dcurso, &valu);
    int creat_valu = stora_ha->inser_curso(dcurso);
    if (!creat_valu) {
        OBID_BINARY_COPY((osv_oid_t *) resctl->resp_memo, (osv_oid_t *) obje_memo.data);
        PDAT_PRODUCEM_TAIL(resctl, OBJE_IDENTI_BLEN)
    }
    //
    free(parm_oivk);
    free_loop(&obje_memo);
    return creat_valu;
}

//

int creat_eobje_echo(hand_hmap *hando_stm, char *lv2pn, char **pamvp) {
    OSEVPF("[FUNC]:creat_eobje_echo\n");
    char handn[HANDN_LENGTH];
    if (!filli_const_handn(handn, lv2pn, pamvp))
        return -1;
    OSEVPF("handn:|%s|\n", handn);
    //
    lev1me *lv1me = (lev1me *) action_value(handn, hando_stm->lev1n_hm);
    if (!lv1me) return -1;
    //
    return 0x00;
}




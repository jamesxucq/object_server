
/* 
 * File:   conte_utili.h
 * Author: James Xu
 *
 * Created on 2023.5.16, AM 9:39
 */

#ifndef CONTE_UTILI_H
#define CONTE_UTILI_H

#include "lv2p_conte.h"
#include "lev1_conte.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int hand_load_oatti(OUT hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, lev1_cont_t *ocont, char *basen);
    int hand_load_datti(OUT lv2pm_hmap *lv2pm_stm, lv2p_cont_t *dcont, char *basen);

    //

    inline int hand_dele_oatti(hand_hmap *hando_stm, lev1_cont_t *ocont) {
        char handn[HANDN_LENGTH];
        FILLI_HANDLE_NAME(handn, ocont->l1i_nod.lv2pn, ocont->l1i_nod.lev1n, ocont->l1i_nod.oivk_fmtsp);
        lev1me *lv1me = (lev1me *) action_value(handn, hando_stm->lev1n_hm);
        if (!lv1me) return -1;
        close_meth_hand(NULL, hando_stm, lv1me);
        action_remove(lv1me->handn, hando_stm->lev1n_hm);
        return 0x00;
    }

    inline int hand_dele_datti(lv2pm_hmap *lv2pm_stm, lv2p_cont_t *dcont) {
        osv_oid_t lv2p_obid;
        OBID_STOID_BUILD(&lv2p_obid, &dcont->l2nod.lv2p_stoid)
        if (close_lv2p_meta(lv2pm_stm, &lv2p_obid))
            return -1;
        return 0x00;
    }

    //
    int build_inher_versi(instda *lv2in, cachemap *lv2pan_hm, lv2p_expa_t *lv2expt);


#ifdef __cplusplus
}
#endif

#endif /* CONTE_UTILI_H */


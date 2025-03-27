
#include "commo_header.h"
#include "kcomm_header.h"

#include "lev1_dlsym.h"
#include "nstri_utili.h"
#include "lv2p_meta/lv2me_ite.h"
#include "invok_bzl.h"

#include "conte_utili.h"
#include "instda.h"

//

int hand_load_oatti(OUT hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, lev1_cont_t *ocont, char *basen) {
    // OSEVPF("[FUNC]:hand_load_oattr\n");
    lev1_cont_i *l1i_nod = &ocont->l1i_nod;
    char libr_path[MAX_PATH * 3];
    LIBRARY_SUFFIX_FILE(libr_path, basen, l1i_nod->lev1_librn, LIBRA_SUFFIX);
    // OSEVPF("libr_path:|%s| basen:|%s| l1i_nod->lev1_librn:|%s| LIBRA_SUFFIX:|%s|\n", libr_path, basen, l1i_nod->lev1_librn, LIBRA_SUFFIX);
    lev1me * lv1me = mallo_lev1me(); // checked
    if (!lv1me) return -1;
    FILLI_HANDLE_NAME(lv1me->handn, l1i_nod->lv2pn, l1i_nod->lev1n, l1i_nod->oivk_fmtsp);
    // OSEVPF("lv1me->handn:|%s| l1i_nod->lv2pn:|%s| l1i_nod->lev1n:|%s| l1i_nod->oivk_fmtsp:|%s|\n", lv1me->handn, l1i_nod->lv2pn, l1i_nod->lev1n, l1i_nod->oivk_fmtsp);
    lv1me->norma_const = gener_const_type(l1i_nod->lv2pn, l1i_nod->lev1n);
    if (open_meth_hand(lv1me, hando_stm, libr_path)) { // checked
        free(lv1me);
        return -1;
    }
    lv1me->lv2me = (lv2pme *) cache_value(l1i_nod->lv2pn, lv2pm_stm->lv2pmn_hm);
    if (!lv1me->lv2me) {
        char lev1_librn[LVON_LENGTH];
        if (!close_meth_hand(lev1_librn, hando_stm, lv1me))
            delet_libra_file(basen, lev1_librn);
        free(lv1me);
        return -1;
    }
    action_insert(lv1me->handn, lv1me, hando_stm->lev1n_hm);
    strcpy(lv1me->lev1n, l1i_nod->lev1n);
    lv1me->oivk_retyp_oe = l1i_nod->oivk_retyp;
    strcpy(lv1me->oivk_fmtsp_oe, l1i_nod->oivk_fmtsp);
    // SET_FIXED_FLOAT(lv1me->fixed_float_oe, lv1me->oivk_fmtsp_oe)
    lv1me->oivk_size_oe = l1i_nod->oivk_size;
    // OSEVPF("[FUNC]:hand_load_oattr, OK!\n");
    return 0x00;
}

// 

int hand_load_datti(OUT lv2pm_hmap *lv2pm_stm, lv2p_cont_t *dcont, char *basen) {
    // OSEVPF("[FUNC]:hand_load_datti\n");
    lv2p_cont_i *lv2_nod = &dcont->l2nod;
    osv_oid_t lv2p_obid;
    OBID_STOID_BUILD(&lv2p_obid, &lv2_nod->lv2p_stoid)
    //
    lv2p_attri *lv2ai = creat_lv2p_atti(lv2pm_stm, &lv2p_obid, lv2_nod->lv2pn);
    if (!lv2ai) return -1;
    if (!build_l2att_ite(lv2ai, basen)) {
        destr_lv2p_atti(lv2pm_stm, &lv2ai->lv2p_obid);
        return -1;
    }
    // OSEVPF("lv2pn:|%s|\n", lv2_nod->lv2pn);
    lv2p_expa_t *lv2expt = load_lv2expt_ite(basen, lv2_nod->lv2pn);
    if (!lv2expt) {
        destr_lv2p_atti(lv2pm_stm, &lv2ai->lv2p_obid);
        return -1;
    }
    //
    lv2pme *lv2me = open_lv2p_meta(lv2pm_stm, &lv2p_obid, lv2_nod->lv2pn, lv2expt);
    if (!lv2me) {
        destr_lv2p_atti(lv2pm_stm, &lv2ai->lv2p_obid);
        free_lv2exp(lv2expt);
        return -1;
    }
    strcpy(lv2me->lv2p_fmtsd_tm, lv2_nod->lv2p_fmtsd);
    SET_FIXED_FLOAT(lv2me->fixed_float_tm, lv2me->lv2p_fmtsd_tm)
    lv2me->data_size = lv2_nod->data_size;
    // OSEVPF("[FUNC]:hand_load_datti, OK!\n");
    return 0x00;
}

//

int build_inher_versi(instda *lv2in, cachemap *lv2pan_hm, lv2p_expa_t *lv2expt) {
    lev1_decl_t *lv1d = lv2expt->lv1dat;
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        if (LVTP_NORM_METH == lv1d->levtyp)
            continue;
        lv2p_attri *lv2ai = (lv2p_attri *) cache_value(last_lv2pn(lv1d->inhe_lv2n), lv2pan_hm);
        if (!lv2ai) return -1;
        //
        inher_versi *invep = lv2in->inhver;
        unsigned int inde = 0x00;
        for (; NOT_INVER_ZERO(invep); ++inde, ++invep) {
            if (OBID_EQUALI(&lv2ai->lv2p_obid, &invep->lv2p_obid))
                break;
        }
        if (IS_INVER_ZERO(invep)) {
            if (CINHE_COUNT_ZTAI == inde)
                return -1;
            OBID_BINARY_COPY(&invep->lv2p_obid, &lv2ai->lv2p_obid)
                    ++invep;
            SET_INVER_ZERO(invep)
        }
    }
    //
    return 0x00;
}

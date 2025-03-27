
#include "commo_header.h"
#include "kcomm_header.h"
#include "nstri_utili.h"
#include "cfile_utili.h"
#include "rstatu_bzl.h"
#include "invok_bzl.h"
#include "instda_bzl.h"
#include "conte_obje.h"
#include "istri_utili.h"
#include "lv2p_meta.h"
#include "lev1_dlsym.h"
#include "conte_utili.h"

#include "conte_bzl.h"
#include "kcomm_struct.h"
#include "instda.h"
/*
int handbzl_create(char *data_directory) {
    strcpy(_hand_data_directory_, data_directory);
    return ERR_SUCCESS; //succ
}
int handbzl_destroy() {
    return ERR_SUCCESS; //succ
}
 */

//

int robk_ilev1_bzl(hand_hmap *hando_stm, char *basen, lev1id *lev1i) {
    OSEVPF("[FUNC]:robk_ilev1_bzl.\n");
    char handn[HANDN_LENGTH];
    BUILD_IHANDN_BZL(handn, lev1i);
    lev1me *lv1me = (lev1me *) action_value(handn, hando_stm->lev1n_hm);
    if (!lv1me) return -1;
    //
    char lev1_librn[LVON_LENGTH];
    if (!close_meth_hand(lev1_librn, hando_stm, lv1me))
        delet_libra_file(basen, lev1_librn);
    //
    action_remove(lv1me->handn, hando_stm->lev1n_hm);
    delet_conte_lv1id(basen, lev1i);
    return 0x00;
}

//

int hcrea_imeth_bzl(respo_ctrl *resctl, char *libr_path, char *clang_cont, char *basen, lev1id *lev1i) {
    OSEVPF("[FUNC]:hcrea_imeth_bzl\n");
    char handn[HANDN_LENGTH];
    BUILD_IHANDN_BZL(handn, lev1i);
    OSEVPF("handn:|%s|\n", handn);
    char clan_file[MAX_PATH * 3];
    TEMPORA_SUFFIX_FILE(clan_file, basen, handn, CLANG_SUFFIX);
    LIBRARY_SUFFIX_FILE(libr_path, basen, handn, LIBRA_SUFFIX);
    //
    if (save_clang_file(clan_file, clang_cont)) {
        unlink(clan_file);
        PDAT_EXCEPTIO_TAIL(resctl, SAVE_CLANG_EXPT);
        return -1;
    }
    PDAT_EATTACH_HEAD(resctl, OSEV_ATTACH_OKAY);
    if (compi_clang_libra(libr_path, clan_file, resctl->posi_resp)) {
        unlink(clan_file);
        PDAT_EATTACH_END(resctl, strlen((char *) resctl->posi_resp))
        return -1;
    }
    OSEVPF("unlink clan_file:|%s|\n", clan_file);
    unlink(clan_file);
    //
    return 0x00;
}

int creat_ilv1me_bzl(hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *libr_path, char *basen, lev1id *lev1i) {
    OSEVPF("[FUNC]:creat_ilv1me_bzl.\n");
    OSEVPF("++++++++++++++++++++++++++++++++++++++++++++\n");
    char lev1_librn[LVON_LENGTH];
    lev1me * lv1me = mallo_lev1me();
    if (!lv1me) return -1;
    BUILD_IHANDN_BZL(lv1me->handn, lev1i);
    //
    lv1me->norma_const = gener_const_type(lev1i->crea_lv2pn, lev1i->crea_lev1n);
    if (open_meth_hand(lv1me, hando_stm, libr_path)) {
        free(lv1me);
        return -1;
    }
    lv1me->lv2me = (lv2pme *) cache_value(lev1i->crea_lv2pn, lv2pm_stm->lv2pmn_hm);
    if (!lv1me->lv2me) {
        if (!close_meth_hand(lev1_librn, hando_stm, lv1me))
            delet_libra_file(basen, lev1_librn);
        free(lv1me);
        return -1;
    }
    action_insert(lv1me->handn, lv1me, hando_stm->lev1n_hm);
    strcpy(lv1me->lev1n, lev1i->crea_lev1n);
    lv1me->oivk_retyp_oe = lev1i->oivk_retyp_oi;
    strcpy(lv1me->oivk_fmtsp_oe, lev1i->oivk_fmtsp_oi);
    // SET_FIXED_FLOAT(lv1me->fixed_float_oe, lv1me->oivk_fmtsp_oe)
    lv1me->oivk_size_oe = lev1i->oivk_size_oi;
    //
    if (appen_conte_lv1me(basen, lev1i->crea_lv2pn, lv1me, lv1me->handn)) {
        if (!close_meth_hand(lev1_librn, hando_stm, lv1me))
            delet_libra_file(basen, lev1_librn);
        action_remove(lv1me->handn, hando_stm->lev1n_hm);
        return -1;
    }
    //
    return 0x00;
}

// method class

int hcrea_metho_bzl(respo_ctrl *resctl, char *libr_path, char *clang_cont, char *basen, lev1_meta *lev1m) {
    OSEVPF("[FUNC]:hcrea_metho_bzl\n");
    char handn[HANDN_LENGTH];
    BUILD_HANDN_BZL(handn, lev1m);
    char clan_file[MAX_PATH * 3];
    TEMPORA_SUFFIX_FILE(clan_file, basen, handn, CLANG_SUFFIX);
    LIBRARY_SUFFIX_FILE(libr_path, basen, handn, LIBRA_SUFFIX);
    //
    if (save_clang_file(clan_file, clang_cont)) {
        unlink(clan_file);
        PDAT_EXCEPTIO_TAIL(resctl, SAVE_CLANG_EXPT);
        return -1;
    }
    PDAT_EATTACH_HEAD(resctl, OSEV_ATTACH_OKAY);
    if (compi_clang_libra(libr_path, clan_file, resctl->posi_resp)) {
        unlink(clan_file);
        PDAT_EATTACH_END(resctl, strlen((char *) resctl->posi_resp))
        return -1;
    }
    OSEVPF("unlink clan_file:|%s|\n", clan_file);
    unlink(clan_file);
    //
    return 0x00;
}

//

int creat_lv1me_bzl(hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *libr_path, char *basen, lev1_meta *lev1m) {
    OSEVPF("[FUNC]:creat_lv1me_bzl.\n");
    char lev1_librn[LVON_LENGTH];
    lev1me * lv1me = mallo_lev1me();
    if (!lv1me) return -1;
    BUILD_HANDN_BZL(lv1me->handn, lev1m);
    //
    lv1me->norma_const = gener_const_type(lev1m->lv2pn, lev1m->lev1n);
    if (open_meth_hand(lv1me, hando_stm, libr_path)) {
        free(lv1me);
        return -1;
    }
    lv1me->lv2me = (lv2pme *) cache_value(lev1m->lv2pn, lv2pm_stm->lv2pmn_hm);
    if (!lv1me->lv2me) {
        if (!close_meth_hand(lev1_librn, hando_stm, lv1me))
            delet_libra_file(basen, lev1_librn);
        free(lv1me);
        return -1;
    }
    action_insert(lv1me->handn, lv1me, hando_stm->lev1n_hm);
    strcpy(lv1me->lev1n, lev1m->lev1n);
    lv1me->oivk_retyp_oe = lev1m->oivk_retyp_om;
    strcpy(lv1me->oivk_fmtsp_oe, lev1m->oivk_fmtsp_om);
    // SET_FIXED_FLOAT(lv1me->fixed_float_oe, lv1me->oivk_fmtsp_oe)
    lv1me->oivk_size_oe = lev1m->oivk_size_om;
    //
    if (appen_conte_lv1me(basen, lev1m->lv2pn, lv1me, lv1me->handn)) {
        if (!close_meth_hand(lev1_librn, hando_stm, lv1me))
            delet_libra_file(basen, lev1_librn);
        action_remove(lv1me->handn, hando_stm->lev1n_hm);
        return -1;
    }
    //
    return 0x00;
}

//

int hrepl_metho_bzl(respo_ctrl *resctl, char *libr_path, char *clang_cont, char *basen, lev1_meta *lev1m) {
    OSEVPF("[FUNC]:hrepl_metho_bzl\n");
    char handn[HANDN_LENGTH];
    BUILD_HANDN_BZL(handn, lev1m);
    LIBRARY_SUFFIX_FILE(libr_path, basen, handn, LIBRA_SUFFIX);
    //
    char clan_file[MAX_PATH * 3];
    TEMPORA_SUFFIX_FILE(clan_file, basen, handn, CLANG_SUFFIX);
    if (save_clang_file(clan_file, clang_cont)) {
        unlink(clan_file);
        PDAT_EXCEPTIO_TAIL(resctl, SAVE_CLANG_EXPT);
        return -1;
    }
    PDAT_EATTACH_HEAD(resctl, OSEV_ATTACH_OKAY);
    if (compi_clang_libra(libr_path, clan_file, resctl->posi_resp)) {
        unlink(clan_file);
        PDAT_EATTACH_END(resctl, strlen((char *) resctl->posi_resp))
        return -1;
    }
    OSEVPF("unlink clan_file:|%s|\n", clan_file);
    unlink(clan_file);
    //
    return 0x00;
}

int repla_lv1me_bzl(hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *libr_path, char *basen, lev1_meta *lev1m) {
    OSEVPF("[FUNC]:repla_lv1me_bzl.\n");
    char lev1_librn[LVON_LENGTH];
    lev1me * lv1me = mallo_lev1me();
    if (!lv1me) return -1;
    BUILD_HANDN_BZL(lv1me->handn, lev1m);
    //
    lv1me->norma_const = gener_const_type(lev1m->lv2pn, lev1m->lev1n);
    if (open_meth_hand(lv1me, hando_stm, libr_path)) {
        free(lv1me);
        return -1;
    }
    lv1me->lv2me = (lv2pme *) cache_value(lev1m->lv2pn, lv2pm_stm->lv2pmn_hm);
    if (!lv1me->lv2me) {
        if (!close_meth_hand(lev1_librn, hando_stm, lv1me))
            delet_libra_file(basen, lev1_librn);
        free(lv1me);
        return -1;
    }
    action_insert(lv1me->handn, lv1me, hando_stm->lev1n_hm);
    strcpy(lv1me->lev1n, lev1m->lev1n);
    lv1me->oivk_retyp_oe = lev1m->oivk_retyp_om;
    strcpy(lv1me->oivk_fmtsp_oe, lev1m->oivk_fmtsp_om);
    // SET_FIXED_FLOAT(lv1me->fixed_float_oe, lv1me->oivk_fmtsp_oe)
    lv1me->oivk_size_oe = lev1m->oivk_size_om;
    //
    if (updat_conte_lv1me(basen, lev1m->lv2pn, lv1me, lv1me->handn)) {
        if (!close_meth_hand(lev1_librn, hando_stm, lv1me))
            delet_libra_file(basen, lev1_librn);
        action_remove(lv1me->handn, hando_stm->lev1n_hm);
        return -1;
    }
    //
    return 0x00;
}

//

int robk_lv2p_bzl(lv2pm_hmap *lv2pm_stm, char *lv2pn) {
    OSEVPF("[FUNC]:robk_lv2p_bzl.\n");
    delet_lv2p_meta(lv2pm_stm, lv2pn);
    delet_lv2p_atti(lv2pm_stm, lv2pn);
    //
    return 0x00;
}

int hcrea_class_bzl(respo_ctrl *resctl, char *libr_path, char *clang_cont, char *basen, char *lv2pn) {
    OSEVPF("[FUNC]:hcrea_class_bzl. lv2pn:|%s|\n", lv2pn);
    char clan_file[MAX_PATH * 3];
    TEMPORA_SUFFIX_FILE(clan_file, basen, lv2pn, CLANG_SUFFIX);
    if (save_clang_file(clan_file, clang_cont)) {
        unlink(clan_file);
        PDAT_EXCEPTIO_TAIL(resctl, SAVE_CLANG_EXPT);
        return -1;
    }
    LIBRARY_SUFFIX_FILE(libr_path, basen, lv2pn, LIBRA_SUFFIX);
    PDAT_EATTACH_HEAD(resctl, OSEV_ATTACH_OKAY);
    if (compi_clang_libra(libr_path, clan_file, resctl->posi_resp)) {
        unlink(clan_file);
        PDAT_EATTACH_END(resctl, strlen((char *) resctl->posi_resp))
        return -1;
    }
    OSEVPF("unlink clan_file:|%s|\n", clan_file);
    unlink(clan_file);
    //
    return 0x00;
}

int creat_lv2me_bzl(lv2pm_hmap *lv2pm_stm, char *basen, lv2p_decl_t *lv2dt, lv2p_expa_t *lv2expt) {
    OSEVPF("[FUNC]:creat_lv2me_bzl.\n");
    lv2p_attri *lv2ai = creat_lv2p_atti(lv2pm_stm, &lv2dt->lv2p_obid, lv2dt->lv2pn);
    if (!lv2ai) return -1;
    //
    lv2pme *lv2me = open_lv2p_meta(lv2pm_stm, &lv2dt->lv2p_obid, lv2dt->lv2pn, lv2expt);
    if (!lv2me) {
        destr_lv2p_atti(lv2pm_stm, &lv2dt->lv2p_obid);
        return -1;
    }
    build_lv2p_fmtsd(lv2me->lv2p_fmtsd_tm, lv2expt->lv2nod);
    SET_FIXED_FLOAT(lv2me->fixed_float_tm, lv2me->lv2p_fmtsd_tm)
    lv2me->data_size = count_lv2pd_size(lv2me->lv2p_fmtsd_tm);
    //     
    if (appen_conte_lv2p(lv2dt->lv2pn, &lv2dt->lv2p_obid, lv2me->lv2p_fmtsd_tm, lv2me->data_size, basen))
        return -1;
    //
    return 0x00;
}

//

lv2pme *lv2in_lv2me_bzl(inst_hmap *insda_stm, lv2pm_hmap *lv2pm_stm, char *lv2_dec, lv2p_expa_t *lv2expt, osv_oid_t *lv2p_obid) {
    OSEVPF("[FUNC]:lv2in_lv2me_bzl.\n");
    instda *lv2in = creat_insta_data(insda_stm, lv2_dec);
    if (!lv2in) return NULL;
    OSEVPF("[FUNC]:build_inher_versi\n");
    if (build_inher_versi(lv2in, lv2pm_stm->lv2pan_hm, lv2expt))
        return NULL;
    //
    OSEVPF("[FUNC]:creat_lv2p_meta\n");
    lv2pme *lv2me = creat_lv2p_meta(insda_stm, lv2in, lv2expt, lv2p_obid);
    if (!lv2me) {
        destr_insta_data(insda_stm, lv2_dec);
        return NULL;
    }
    build_lv2p_fmtsd(lv2me->lv2p_fmtsd_tm, lv2expt->lv2nod);
    SET_FIXED_FLOAT(lv2me->fixed_float_tm, lv2me->lv2p_fmtsd_tm)
    lv2me->data_size = count_lv2pd_size(lv2me->lv2p_fmtsd_tm);
    //
    return lv2me;
}

//

int repla_lv2me_bzl(lv2pm_hmap *lv2pm_stm, char *basen, lv2p_decl_t *lv2dt, lv2p_expa_t *lv2expt) {
    OSEVPF("[FUNC]:repla_lv2me_bzl.\n");
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lv2dt->lv2pn, lv2pm_stm->lv2pan_hm);
    if (!lv2ai) return -1;
    lv2ai->versio++;
    //
    lv2pme *lv2me = (lv2pme *) cache_value(&lv2ai->lv2p_obid, lv2pm_stm->lv2pmo_hm);
    if (!lv2me) return -1;
    build_lv2p_fmtsd(lv2me->lv2p_fmtsd_tm, lv2expt->lv2nod);
    SET_FIXED_FLOAT(lv2me->fixed_float_tm, lv2me->lv2p_fmtsd_tm)
    lv2me->data_size = count_lv2pd_size(lv2me->lv2p_fmtsd_tm);
    lv2me->lv2expt = lv2expt;
    //
    if (updat_conte_lv2p(&lv2me->lv2p_obid, lv2me->lv2p_fmtsd_tm, lv2me->data_size, basen))
        return -1;
    //
    return 0x00;
}

//

int hdrop_metho_bzl(hand_hmap *hando_stm, char *basen, lev1_meta *lev1m) {
    OSEVPF("[FUNC]:hdrop_metho_bzl.\n");
    char handn[HANDN_LENGTH];
    BUILD_HANDN_BZL(handn, lev1m);
    lev1me *lv1me = (lev1me *) action_value(handn, hando_stm->lev1n_hm);
    if (!lv1me) return -1;
    //
    char lev1_librn[LVON_LENGTH];
    if (!close_meth_hand(lev1_librn, hando_stm, lv1me))
        delet_libra_file(basen, lev1_librn);
    //
    action_remove(lv1me->handn, hando_stm->lev1n_hm);
    return 0x00;
}

//

int hdrop_class_bzl(lv2pm_hmap *lv2pm_stm, char *lv2pn) {
    OSEVPF("[FUNC]:hdrop_class_bzl.\n");
    delet_lv2p_meta(lv2pm_stm, lv2pn);
    delet_lv2p_atti(lv2pm_stm, lv2pn);
    //
    return 0x00;
}

//

int relom_handl_bzl(respo_ctrl *resctl, hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *basen, char *lev1_librn, lev1_meta *lev1m) {
    OSEVPF("[FUNC]:relom_handl_bzl\n");
    lev1me * lv1me = mallo_lev1me();
    if (!lv1me) {
        PDAT_EXCEPTIO_TAIL(resctl, OPEN_IHAND_EXPT)
        return -1;
    }
    BUILD_HANDN_BZL(lv1me->handn, lev1m);
    //
    lv1me->norma_const = gener_const_type(lev1m->lv2pn, lev1m->lev1n);
    char libr_path[MAX_PATH * 3];
    LIBRARY_SUFFIX_FILE(libr_path, basen, lev1_librn, LIBRA_SUFFIX);
    if (open_meth_hand_librn(lv1me, hando_stm, libr_path, lev1_librn)) {
        free(lv1me);
        PDAT_EXCEPTIO_TAIL(resctl, OPEN_IHAND_EXPT)
        return -1;
    }
    lv1me->lv2me = (lv2pme *) cache_value(lev1m->lv2pn, lv2pm_stm->lv2pmn_hm);
    if (!lv1me->lv2me) {
        if (!close_meth_hand(lev1_librn, hando_stm, lv1me))
            delet_libra_file(basen, lev1_librn);
        free(lv1me);
        PDAT_EXCEPTIO_TAIL(resctl, OPEN_IHAND_EXPT)
        return -1;
    }
    action_insert(lv1me->handn, lv1me, hando_stm->lev1n_hm);
    strcpy(lv1me->lev1n, lev1m->lev1n);
    lv1me->oivk_retyp_oe = lev1m->oivk_retyp_om;
    strcpy(lv1me->oivk_fmtsp_oe, lev1m->oivk_fmtsp_om);
    // SET_FIXED_FLOAT(lv1me->fixed_float_oe, lv1me->oivk_fmtsp_oe)
    lv1me->oivk_size_oe = lev1m->oivk_size_om;
    //
    if (updat_conte_lv1me(basen, lev1m->lv2pn, lv1me, lev1_librn)) {
        if (!close_meth_hand(lev1_librn, hando_stm, lv1me))
            delet_libra_file(basen, lev1_librn);
        action_remove(lv1me->handn, hando_stm->lev1n_hm);
        PDAT_EXCEPTIO_TAIL(resctl, OPEN_OATTR_EXPT)
        return -1;
    }
    //
    return 0x00;
}

int relom_objec_bzl(respo_ctrl *resctl, char *basen, lev1_meta *lev1m, char *clang_cont) {
    OSEVPF("[FUNC]:relom_objec_bzl\n");
    char handn[HANDN_LENGTH];
    BUILD_HANDN_BZL(handn, lev1m);
    //
    char clan_file[MAX_PATH * 3];
    char lev1_obje[MAX_PATH * 3];
    TEMPORA_SUFFIX_FILE(clan_file, basen, handn, CLANG_SUFFIX);
    TEMPORA_SUFFIX_FILE(lev1_obje, basen, handn, OBJEC_SUFFIX);
    if (save_clang_file(clan_file, clang_cont)) {
        unlink(clan_file);
        PDAT_EXCEPTIO_TAIL(resctl, SAVE_CLANG_EXPT);
        return -1;
    }
    PDAT_EATTACH_HEAD(resctl, OSEV_ATTACH_OKAY);
    if (compi_clang_objec(lev1_obje, clan_file, resctl->posi_resp)) {
        unlink(clan_file);
        PDAT_EATTACH_END(resctl, strlen((char *) resctl->posi_resp))
        return -1;
    }
    OSEVPF("unlink clan_file:|%s|\n", clan_file);
    unlink(clan_file);
    //
    return 0x00;
}

int relom_libra_bzl(respo_ctrl *resctl, char *basen, char *lev1_librn, lev1_list *l1lst) {
    OSEVPF("[FUNC]:relom_libra_bzl lev1_librn:|%s|\n", lev1_librn);
    char *obje_path[MAX_PARAM_CNT];
    char _ofile_[BUFF_32K_SIZE];
    if (!filli_relom_objen(obje_path, _ofile_, basen, l1lst)) {
        PDAT_EXCEPTIO_TAIL(resctl, OBJEC_FILE_EXPT)
        return -1;
    }
    char libr_path[MAX_PATH * 3];
    LIBRARY_SUFFIX_FILE(libr_path, basen, lev1_librn, LIBRA_SUFFIX);
    PDAT_EATTACH_HEAD(resctl, OSEV_ATTACH_OKAY);
    if (compi_objec_libra(libr_path, obje_path, resctl->posi_resp)) {
        PDAT_EATTACH_END(resctl, strlen((char *) resctl->posi_resp))
        return -1;
    }
    //
    return 0x00;
}

//

int reloc_handl_bzl(respo_ctrl *resctl, lv2pm_hmap *lv2pm_stm, char *basen, lv2p_decl_t *lv2dt) {
    OSEVPF("[FUNC]:reloc_handl_bzl\n");
    lv2p_attri *lv2ai = creat_lv2p_atti(lv2pm_stm, &lv2dt->lv2p_obid, lv2dt->lv2pn);
    if (!lv2ai) {
        PDAT_EXCEPTIO_TAIL(resctl, OPEN_IHAND_EXPT)
        return -1;
    }
    if (!build_l2att_ite(lv2ai, basen)) {
        destr_lv2p_atti(lv2pm_stm, &lv2ai->lv2p_obid);
        PDAT_EXCEPTIO_TAIL(resctl, OPEN_IHAND_EXPT)
        return -1;
    }
    //
    lv2p_expa_t *lv2expt = load_lv2expt_ite(basen, lv2dt->lv2pn);
    if (!lv2expt) {
        destr_lv2p_atti(lv2pm_stm, &lv2ai->lv2p_obid);
        PDAT_EXCEPTIO_TAIL(resctl, MALLO_LVTEXP_EXPT)
        return -1;
    }
    //
    lv2pme *lv2me = open_lv2p_meta(lv2pm_stm, &lv2dt->lv2p_obid, lv2dt->lv2pn, lv2expt);
    if (!lv2me) {
        destr_lv2p_atti(lv2pm_stm, &lv2ai->lv2p_obid);
        free_lv2exp(lv2expt);
        PDAT_EXCEPTIO_TAIL(resctl, OPEN_IHAND_EXPT)
        return -1;
    }
    build_lv2p_fmtsd(lv2me->lv2p_fmtsd_tm, lv2expt->lv2nod);
    SET_FIXED_FLOAT(lv2me->fixed_float_tm, lv2me->lv2p_fmtsd_tm)
    lv2me->data_size = count_lv2pd_size(lv2me->lv2p_fmtsd_tm);
    //
    if (updat_conte_lv2p(&lv2dt->lv2p_obid, lv2me->lv2p_fmtsd_tm, lv2me->data_size, basen)) {
        destr_lv2p_atti(lv2pm_stm, &lv2ai->lv2p_obid);
        free_lv2exp(lv2expt);
        close_lv2p_meta(lv2pm_stm, &lv2me->lv2p_obid);
        PDAT_EXCEPTIO_TAIL(resctl, OPEN_OATTR_EXPT)
        return -1;
    }
    //
    return 0x00;
}

int reloc_objec_bzl(respo_ctrl *resctl, char *basen, lv2p_decl_t *lv2dt, char *clang_cont) {
    OSEVPF("[FUNC]:reloc_objec_bzl\n");
    char clan_file[MAX_PATH * 3];
    char lv2p_obje[MAX_PATH * 3];
    TEMPORA_SUFFIX_FILE(clan_file, basen, lv2dt->lv2pn, CLANG_SUFFIX);
    TEMPORA_SUFFIX_FILE(lv2p_obje, basen, lv2dt->lv2pn, OBJEC_SUFFIX);
    if (save_clang_file(clan_file, clang_cont)) {
        unlink(clan_file);
        PDAT_EXCEPTIO_TAIL(resctl, SAVE_CLANG_EXPT);
        return -1;
    }
    PDAT_EATTACH_HEAD(resctl, OSEV_ATTACH_OKAY);
    if (compi_clang_objec(lv2p_obje, clan_file, resctl->posi_resp)) {
        unlink(clan_file);
        PDAT_EATTACH_END(resctl, strlen((char *) resctl->posi_resp))
        return -1;
    }
    OSEVPF("unlink clan_file:|%s|\n", clan_file);
    unlink(clan_file);
    //
    return 0x00;
}

int reloc_libra_bzl(respo_ctrl *resctl, char *basen, char *lev1_librn, lv2p_list *l2lst) {
    OSEVPF("[FUNC]:reloc_libra_bzl lev1_librn:|%s|\n", lev1_librn);
    char *obje_path[MAX_PARAM_CNT];
    char _ofile_[BUFF_32K_SIZE];
    if (!filli_reloc_objen(obje_path, _ofile_, basen, l2lst)) {
        PDAT_EXCEPTIO_TAIL(resctl, OBJEC_FILE_EXPT)
        return -1;
    }
    char libr_path[MAX_PATH * 3];
    LIBRARY_SUFFIX_FILE(libr_path, basen, lev1_librn, LIBRA_SUFFIX);
    PDAT_EATTACH_HEAD(resctl, OSEV_ATTACH_OKAY);
    if (compi_objec_libra(libr_path, obje_path, resctl->posi_resp)) {
        PDAT_EATTACH_END(resctl, strlen((char *) resctl->posi_resp))
        return -1;
    }
    //
    return 0x00;
}

// base

int hload_lv2dat_bzl(basv_list *blist) {
    lv2p_cont_t dcont;
    lev1_cont_t ocont;
    unsigned int cinde;
    //
    basv_list *blsnd = blist;
    for (; blsnd; blsnd = blsnd->next) {
        OSEVPF("[FUNC]:hload_lv2dat_bzl:|%s|", blsnd->_base_);
        cinde = open_conte_lv2p(&dcont, blsnd->_base_);
        while (INVA_INDE_VALU != cinde) {
            cinde = read_conte_lv2p(&dcont, cinde);
            if (hand_load_datti(&blsnd->basval.lv2pm_stm, &dcont, blsnd->_base_)) {
                close_conte_lv2p(&dcont);
                return -1;
            }
        }
        close_conte_lv2p(&dcont);
        //
        cinde = open_conte_lev1(&ocont, blsnd->_base_);
        while (INVA_INDE_VALU != cinde) {
            cinde = read_conte_lev1(&ocont, cinde);
            if (hand_load_oatti(&blsnd->basval.hando_stm, &blsnd->basval.lv2pm_stm, &ocont, blsnd->_base_)) {
                close_conte_lev1(&ocont);
                return -1;
            }
        }
        close_conte_lev1(&ocont);
    }
    //
    return 0x00;
}

int open_lv2dat_bzl(base_valu *baval, char *basen) {
    OSEVPF("[FUNC]:open_lv2dat_bzl:|%s|", basen);
    lv2p_cont_t dcont;
    unsigned int cinde = open_conte_lv2p(&dcont, basen);
    while (INVA_INDE_VALU != cinde) {
        cinde = read_conte_lv2p(&dcont, cinde);
        if (hand_load_datti(&baval->lv2pm_stm, &dcont, basen)) {
            close_conte_lv2p(&dcont);
            return -1;
        }
    }
    close_conte_lv2p(&dcont);
    //
    lev1_cont_t ocont;
    cinde = open_conte_lev1(&ocont, basen);
    while (INVA_INDE_VALU != cinde) {
        cinde = read_conte_lev1(&ocont, cinde);
        if (hand_load_oatti(&baval->hando_stm, &baval->lv2pm_stm, &ocont, basen)) {
            close_conte_lev1(&ocont);
            return -1;
        }
    }
    close_conte_lev1(&ocont);
    //
    return 0x00;
}

//

int close_lv2dat_bzl(base_valu *baval, char *basen) {
    OSEVPF("[FUNC]:close_lv2dat_bzl:|%s|", basen);
    lev1_cont_t ocont;
    unsigned int cinde = open_conte_lev1(&ocont, basen);
    while (INVA_INDE_VALU != cinde) {
        cinde = read_conte_lev1(&ocont, cinde);
        if (hand_dele_oatti(&baval->hando_stm, &ocont)) {
            close_conte_lev1(&ocont);
            return -1;
        }
    }
    close_conte_lev1(&ocont);
    //
    lv2p_cont_t dcont;
    cinde = open_conte_lv2p(&dcont, basen);
    while (INVA_INDE_VALU != cinde) {
        cinde = read_conte_lv2p(&dcont, cinde);
        if (hand_dele_datti(&baval->lv2pm_stm, &dcont)) {
            close_conte_lv2p(&dcont);
            return -1;
        }
    }
    close_conte_lv2p(&dcont);
    //
    return 0x00;
}

// 0x00:hand refer zero. >0x00:refer number <0x00:error

int close_l1hand_bzl(char *lev1_librn, hand_hmap *hando_stm, char *handn, char *basen, lev1_meta *lev1m) {
    lev1me *lv1me = (lev1me *) action_value(handn, hando_stm->lev1n_hm);
    if (!lv1me) return -1;
    int refer = close_meth_hand(lev1_librn, hando_stm, lv1me);
    action_remove(lv1me->handn, hando_stm->lev1n_hm);
    delet_conte_lev1m(basen, lev1m);
    //
    return refer;
}

//

lev1me *open_l1hand_bzl(hand_hmap *hando_stm, replm_envir *envrpm, char *basen) {
    lev1me *lv1me = mallo_lev1me();
    if (!lv1me) return NULL;
    strcpy(lv1me->handn, envrpm->handn);
    lv1me->norma_const = gener_const_type(envrpm->lv2pn, envrpm->lev1n);
    //
    char libr_path[MAX_PATH * 3];
    LIBRARY_SUFFIX_FILE(libr_path, basen, envrpm->lev1_librn, LIBRA_SUFFIX);
    if (open_meth_hand_librn(lv1me, hando_stm, libr_path, envrpm->lev1_librn)) {
        free(lv1me);
        return NULL;
    }
    action_insert(lv1me->handn, lv1me, hando_stm->lev1n_hm);
    strcpy(lv1me->lev1n, envrpm->lev1n);
    lv1me->oivk_retyp_oe = envrpm->oivk_retyp_re;
    strcpy(lv1me->oivk_fmtsp_oe, envrpm->oivk_fmtsp_re);
    // SET_FIXED_FLOAT(lv1me->fixed_float_oe, lv1me->oivk_fmtsp_oe)
    lv1me->oivk_size_oe = envrpm->oivk_size_re;
    //
    if (appen_conte_lv1me(basen, envrpm->lv2pn, lv1me, envrpm->lev1_librn)) {
        char lev1_librn[LVON_LENGTH];
        if (!close_meth_hand(lev1_librn, hando_stm, lv1me))
            delet_libra_file(basen, lev1_librn);
        action_remove(lv1me->handn, hando_stm->lev1n_hm);
        return NULL;
    }
    //
    return lv1me;
}

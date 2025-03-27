#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "commo_header.h"
#include "kcomm_header.h"
#include "lv2p_list.h"
#include "lv2p_save.h"
#include "lv2p_load.h"
#include "ostri_utili.h"
#include "trans/trans_utili.h"

#include "lv2p_expan.h"
#include "lev1_decla.h"
#include "inheri/inheri_ite.h"

#include "filli_clang.h"
#include "lv2me_ite.h"
#include "../debug_funct_oi.h"

// save

int save_l2con_ite(char *lv2d_path, lv2p_decl_i *lv2di, char *lv2t_path, lv2p_attri *lv2ai) {
    OSEVPF("[FUNC]:save_l2con_ite\n");
    if (save_lv2p_decla(lv2d_path, lv2di->lv2p_decl))
        return -1;
    if (save_lv2p_metho(lv2d_path, lv2di->l1con_list))
        return -1;
    if (save_lv2p_attrib(lv2t_path, lv2ai))
        return -1;
    if (save_lv2p_inher(lv2t_path, lv2ai->inher_list))
        return -1;
    return 0x00;
}

int save_l2att_ite(char *lv2t_path, lv2p_attri *lv2ai) {
    OSEVPF("[FUNC]:save_l2att_ite, lv2ai->lv2pn:|%s|\n", lv2ai->lv2pn);
    if (save_lv2p_attrib(lv2t_path, lv2ai))
        return -1;
    if (save_lv2p_inher(lv2t_path, lv2ai->inher_list))
        return -1;
    return 0x00;
}

int save_l2dec_ite(char *lv2d_path, lv2p_decl_i *lv2di) {
    OSEVPF("[FUNC]:save_l2met_ite\n");
    if (save_lv2p_decla(lv2d_path, lv2di->lv2p_decl))
        return -1;
    if (save_lv2p_metho(lv2d_path, lv2di->l1con_list))
        return -1;
    return 0x00;
}

//

int delet_l2con_ite(char *lv2d_path, char *lv2t_path, char *lv2e_path) {
    // OSEVPF("lv2d_path:|%s|\n", lv2d_path);
    if (unlink(lv2d_path)) return -1;
    // OSEVPF("lv2t_path:|%s|\n", lv2t_path);
    if (unlink(lv2t_path)) return -1;
    // OSEVPF("lv2d_path:|%s|\n", lv2d_path);
    if (unlink(lv2e_path)) return -1;
    // OSEVPF("end delet_l2con_ite\n");
    return 0x00;
}

//

int delet_lv2me_ite(char *basen, char *lv2pn) {
    char lv2p_path[MAX_PATH * 3];
    LVTP_ATTRI_FILE(lv2p_path, basen, lv2pn)
    OSEVPF("unlink lv2p_path:|%s|\n", lv2p_path);
    unlink(lv2p_path);

    LVTP_DECLA_FILE(lv2p_path, basen, lv2pn)
    OSEVPF("unlink lv2p_path:|%s|\n", lv2p_path);
    unlink(lv2p_path);

    LVTP_EXPAN_FILE(lv2p_path, basen, lv2pn)
    OSEVPF("unlink lv2p_path:|%s|\n", lv2p_path);
    unlink(lv2p_path);
    //
    return 0x00;
}

//

int creat_l2mbkp_ite(char *basen, char *lv2pn) {
    OSEVPF("[FUNC]:creat_l2mbkp_ite\n");
    char lv2p_path[MAX_PATH * 3];
    char lv2p_baku[MAX_PATH * 3];
    //
    CREAT_LVTP_FILE(lv2p_path, basen, lv2pn, DECLA_SUFFIX)
    TEMPORA_BAKUP_FILE(lv2p_baku, basen, lv2pn, DECLA_SUFFIX)
    OSEVPF("lv2p_path:|%s|\n", lv2p_path);
    OSEVPF("lv2p_baku:|%s|\n", lv2p_baku);
    if (file_copy_create(lv2p_path, lv2p_baku))
        return -1;
    //
    CREAT_LVTP_FILE(lv2p_path, basen, lv2pn, ATTRI_SUFFIX)
    TEMPORA_BAKUP_FILE(lv2p_baku, basen, lv2pn, ATTRI_SUFFIX)
    OSEVPF("lv2p_path:|%s|\n", lv2p_path);
    OSEVPF("lv2p_baku:|%s|\n", lv2p_baku);
    if (file_copy_create(lv2p_path, lv2p_baku))
        return -1;
    //
    CREAT_LVTP_FILE(lv2p_path, basen, lv2pn, EXPAN_SUFFIX)
    TEMPORA_BAKUP_FILE(lv2p_baku, basen, lv2pn, EXPAN_SUFFIX)
    OSEVPF("lv2p_path:|%s|\n", lv2p_path);
    OSEVPF("lv2p_baku:|%s|\n", lv2p_baku);
    if (file_copy_create(lv2p_path, lv2p_baku))
        return -1;
    //
    return 0x00;
}

//

int recov_l2mbkp_ite(char *basen, char *lv2pn) {
    OSEVPF("[FUNC]:recov_l2mbkp_ite\n");
    char lv2p_path[MAX_PATH * 3];
    char lv2p_baku[MAX_PATH * 3];
    //
    CREAT_LVTP_FILE(lv2p_path, basen, lv2pn, DECLA_SUFFIX)
    TEMPORA_BAKUP_FILE(lv2p_baku, basen, lv2pn, DECLA_SUFFIX)
    OSEVPF("lv2p_path:|%s|\n", lv2p_path);
    OSEVPF("lv2p_baku:|%s|\n", lv2p_baku);
    if (file_copy_trunca(lv2p_baku, lv2p_path))
        return -1;
    //
    CREAT_LVTP_FILE(lv2p_path, basen, lv2pn, ATTRI_SUFFIX)
    TEMPORA_BAKUP_FILE(lv2p_baku, basen, lv2pn, ATTRI_SUFFIX)
    OSEVPF("lv2p_path:|%s|\n", lv2p_path);
    OSEVPF("lv2p_baku:|%s|\n", lv2p_baku);
    if (file_copy_trunca(lv2p_baku, lv2p_path))
        return -1;
    //
    CREAT_LVTP_FILE(lv2p_path, basen, lv2pn, EXPAN_SUFFIX)
    TEMPORA_BAKUP_FILE(lv2p_baku, basen, lv2pn, EXPAN_SUFFIX)
    OSEVPF("lv2p_path:|%s|\n", lv2p_path);
    OSEVPF("lv2p_baku:|%s|\n", lv2p_baku);
    if (file_copy_trunca(lv2p_baku, lv2p_path))
        return -1;
    //
    return 0x00;
}

int delet_l2mbkp_ite(char *basen, char *lv2pn) {
    OSEVPF("[FUNC]:delet_l2mbkp_ite\n");
    char lv2p_baku[MAX_PATH * 3];
    //
    TEMPORA_BAKUP_FILE(lv2p_baku, basen, lv2pn, DECLA_SUFFIX)
    OSEVPF("lv2p_baku:|%s|\n", lv2p_baku);
    if (unlink(lv2p_baku)) return -1;
    //
    TEMPORA_BAKUP_FILE(lv2p_baku, basen, lv2pn, ATTRI_SUFFIX)
    OSEVPF("lv2p_baku:|%s|\n", lv2p_baku);
    if (unlink(lv2p_baku)) return -1;
    //
    TEMPORA_BAKUP_FILE(lv2p_baku, basen, lv2pn, EXPAN_SUFFIX)
    OSEVPF("lv2p_baku:|%s|\n", lv2p_baku);
    if (unlink(lv2p_baku)) return -1;
    //
    return 0x00;
}

// load

lv2p_attri *parse_l2att_ite(lv2p_attri *lv2ai, char *basen, char *lv2pn) {
    char lv2t_path[MAX_PATH * 3];
    LVTP_ATTRI_FILE(lv2t_path, basen, lv2pn);
    //
    char clat_data[OSLAN_CONTE_SIZE];
    if (!load_data(clat_data, OSLAN_CONTE_SIZE, lv2t_path))
        return NULL;
    // OSEVPF("attri load_data:|%s|\n", clat_data);
    char acont[LARGE_TEXT_SIZE];
    char *last_str = split_lv2p_atti(acont, clat_data);
    if (!last_str) return NULL;
    // OSEVPF("acont:|%s|\n", acont);
    if (!parse_attrib_lv2p(lv2ai, acont))
        return NULL;
    if (parse_inherit(&lv2ai->inher_list, last_str)) {
        ilist_dele(lv2ai->inher_list);
        return NULL;
    }
    OSEVPF("version:%llu integrality:%p\n", lv2ai->versio, lv2ai->integ_list);
    //
    return lv2ai;
}

lv2p_attri *build_l2att_ite(lv2p_attri *lv2ai, char *basen) {
    char lv2t_path[MAX_PATH * 3];
    LVTP_ATTRI_FILE(lv2t_path, basen, lv2ai->lv2pn);
    //
    char clat_data[OSLAN_CONTE_SIZE];
    if (!load_data(clat_data, OSLAN_CONTE_SIZE, lv2t_path))
        return NULL;
    // OSEVPF("attri load_data:|%s|\n", clat_data);
    char acont[LARGE_TEXT_SIZE];
    char *last_str = split_lv2p_atti(acont, clat_data);
    if (!last_str) return NULL;
    // OSEVPF("acont:|%s|\n", acont);
    if (!parse_attrib_lv2p(lv2ai, acont))
        return NULL;
    if (parse_inherit(&lv2ai->inher_list, last_str)) {
        ilist_dele(lv2ai->inher_list);
        return NULL;
    }
    OSEVPF("version:%llu integrality:%p\n", lv2ai->versio, lv2ai->integ_list);
    //
    return lv2ai;
}

//

int parse_intlst_ite(integra **inte_lsth, char *lv2t_path) {
    char clat_data[OSLAN_CONTE_SIZE];
    if (!load_data(clat_data, OSLAN_CONTE_SIZE, lv2t_path))
        return -1;
    // OSEVPF("attri load_data:|%s|\n", clat_data);
    char acont[LARGE_TEXT_SIZE];
    char *last_str = split_lv2p_integ(acont, clat_data);
    if (!last_str) return -1;
    // OSEVPF("acont:|%s|\n", acont);
    if (!parse_integra(inte_lsth, acont)) {
        olist_dele(inte_lsth[0x00]);
        return -1;
    }
    //
    return 0x00;
}

int build_intlst_ite(integra **inte_lsth, char *basen, char *lv2pn) {
    OSEVPF("[FUNC]:build_intlst_ite\n");
    OSEVPF("lv2pn:|%s|\n", lv2pn);
    char lv2t_path[MAX_PATH * 3];
    LVTP_ATTRI_FILE(lv2t_path, basen, lv2pn);
    //
    char clat_data[OSLAN_CONTE_SIZE];
    if (!load_data(clat_data, OSLAN_CONTE_SIZE, lv2t_path))
        return -1;
    // OSEVPF("attri load_data:|%s|\n", clat_data);
    char acont[LARGE_TEXT_SIZE];
    char *last_str = split_lv2p_integ(acont, clat_data);
    if (!last_str) return -1;
    // OSEVPF("acont:|%s|\n", acont);
    if (!parse_integra(inte_lsth, acont)) {
        olist_dele(inte_lsth[0x00]);
        return -1;
    }
    //
    return 0x00;
}

int parse_inhlst_ite(inherit **inhe_lsth, char *lv2t_path) {
    char clat_data[OSLAN_CONTE_SIZE];
    if (!load_data(clat_data, OSLAN_CONTE_SIZE, lv2t_path))
        return -1;
    // OSEVPF("attri load_data:|%s|\n", clat_data);
    char *last_str = pass_lv2p_atti(clat_data);
    if (!last_str) return -1;
    // OSEVPF("acont:|%s|\n", acont);
    if (parse_inherit(inhe_lsth, last_str)) {
        ilist_dele(inhe_lsth[0x00]);
        return -1;
    }
    //
    return 0x00;
}

int build_inhlst_ite(inherit **inhe_lsth, char *basen, char *lv2pn) {
    OSEVPF("[FUNC]:build_inhlst_ite\n");
    char lv2t_path[MAX_PATH * 3];
    LVTP_ATTRI_FILE(lv2t_path, basen, lv2pn);
    //
    char clat_data[OSLAN_CONTE_SIZE];
    if (!load_data(clat_data, OSLAN_CONTE_SIZE, lv2t_path))
        return -1;
    // OSEVPF("attri load_data:|%s|\n", clat_data);
    char *last_str = pass_lv2p_atti(clat_data);
    if (!last_str) return -1;
    OSEVPF("last_str:|%s|\n", last_str);
    if (parse_inherit(inhe_lsth, last_str)) {
        ilist_dele(inhe_lsth[0x00]);
        return -1;
    }
    //
    return 0x00;
}

int build_extern_inhlst_ite(bool_osv *iexter, inherit **inhe_lsth, char *basen, char *lv2pn) {
    OSEVPF("[FUNC]:build_extern_inhlst_ite\n");
    char lv2t_path[MAX_PATH * 3];
    LVTP_ATTRI_FILE(lv2t_path, basen, lv2pn);
    //
    char clat_data[OSLAN_CONTE_SIZE];
    if (!load_data(clat_data, OSLAN_CONTE_SIZE, lv2t_path))
        return -1;
    // OSEVPF("attri load_data:|%s|\n", clat_data);
    char acont[LARGE_TEXT_SIZE];
    char *last_str = split_lv2p_atti(acont, clat_data);
    if (!last_str) return -1;
    // OSEVPF("acont:|%s|\n", acont);
    if (parse_extern_lv2p(iexter, acont))
        return -1;
    if (parse_inherit(inhe_lsth, last_str)) {
        ilist_dele(inhe_lsth[0x00]);
        return -1;
    }
    //
    return 0x00;
}

//

lv2p_decl_i *parse_l2con_ite(lv2p_decl_i *lv2di, char *lv2d_path) {
    char lv2p_cont[OSLAN_CONTE_SIZE];
    if (!load_data(lv2p_cont, OSLAN_CONTE_SIZE, lv2d_path))
        return NULL;
    OSEVPF("conte load_data:|%s|\n", lv2p_cont);
    //
    char *last_str = split_class_conte(lv2di->lv2p_decl, lv2p_cont);
    OSEVPF("conte lv2p_decl_t:|%s|\n", lv2di->lv2p_decl);
    if (parse_lev1_meta(&lv2di->l1con_list, last_str)) {
        l1clst_dele(lv2di->l1con_list);
        return NULL;
    }
    //
    return lv2di;
}

lv2p_decl_i *build_l2con_ite(lv2p_decl_i *lv2di, char *basen, char *lv2pn) {
    char lv2d_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2d_path, basen, lv2pn);
    memset(lv2di, '\0', sizeof (lv2p_decl_i));
    //
    char lv2p_cont[OSLAN_CONTE_SIZE];
    if (!load_data(lv2p_cont, OSLAN_CONTE_SIZE, lv2d_path))
        return NULL;
    OSEVPF("conte load_data:|%s|\n", lv2p_cont);
    //
    char *last_str = split_class_conte(lv2di->lv2p_decl, lv2p_cont);
    OSEVPF("conte lv2p_decl_t:|%s|\n", lv2di->lv2p_decl);
    if (parse_lev1_meta(&lv2di->l1con_list, last_str)) {
        l1clst_dele(lv2di->l1con_list);
        return NULL;
    }
    //
    return lv2di;
}

//

char *split_l2dec_ite(char *lv2_dec, char *lv2d_path) {
    // OSEVPF("[FUNC]:split_l2dec_ite\n");
    char lv2p_cont[OSLAN_CONTE_SIZE];
    if (!load_data(lv2p_cont, OSLAN_CONTE_SIZE, lv2d_path))
        return NULL;
    // OSEVPF("decla load_data:|%s|\n", lv2p_cont);
    split_class_conte(lv2_dec, lv2p_cont);
    // OSEVPF("decla lv2_dec:|%s|\n", lv2_dec);
    return lv2_dec;
}

//

char *filli_l2dec_ite(char *lv2_dec, char *basen, char *lv2pn) {
    // OSEVPF("[FUNC]:filli_l2dec_ite\n");
    char lv2d_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2d_path, basen, lv2pn);
    //
    char lv2p_cont[OSLAN_CONTE_SIZE];
    if (!load_data(lv2p_cont, OSLAN_CONTE_SIZE, lv2d_path))
        return NULL;
    // OSEVPF("decla load_data:|%s|\n", lv2p_cont);
    split_class_conte(lv2_dec, lv2p_cont);
    // OSEVPF("decla lv2_dec:|%s|\n", lv2_dec);
    return lv2_dec;
}

//

int parse_l2meth_ite(lv1_cont **l1clsth, char *lv2d_path) {
    char lv2p_cont[OSLAN_CONTE_SIZE];
    if (!load_data(lv2p_cont, OSLAN_CONTE_SIZE, lv2d_path))
        return -1;
    OSEVPF("conte load_data:|%s|\n", lv2p_cont);
    //
    char *last_str = split_metho_decla(lv2p_cont);
    OSEVPF("conte class_metho:|%s|\n", last_str);
    if (parse_lev1_meta(l1clsth, last_str)) {
        l1clst_dele(l1clsth[0x00]);
        return -1;
    }
    //
    return 0x00;
}

//

int build_l2meth_ite(lv1_cont **l1clsth, char *basen, char *lv2pn) {
    char lv2d_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2d_path, basen, lv2pn);
    //
    char lv2p_cont[OSLAN_CONTE_SIZE];
    if (!load_data(lv2p_cont, OSLAN_CONTE_SIZE, lv2d_path))
        return -1;
    // OSEVPF("conte load_data:|%s|\n", lv2p_cont);
    char *last_str = split_metho_decla(lv2p_cont);
    OSEVPF("conte class_metho:|%s|\n", last_str);
    if (parse_lev1_meta(l1clsth, last_str)) {
        l1clst_dele(l1clsth[0x00]);
        return -1;
    }
    //
    return 0x00;
}

//

osv_oid_t *find_l2oid_ite(osv_oid_t *lv2p_obid, char *lv2t_path) {
    char clat_data[OSLAN_CONTE_SIZE];
    if (!load_data(clat_data, OSLAN_CONTE_SIZE, lv2t_path))
        return NULL;
    // OSEVPF("load_data:|%s|\n", clat_data);
    char sid_data[STOR_IDENTI_ZLEN];
    char *last_str = split_lv2p_stoid(sid_data, clat_data);
    if (!last_str) return NULL;
    strsid_obid(lv2p_obid, sid_data);
    //
    return lv2p_obid;
}

char *find_l2att_ite(char *lv2p_attri, char *lv2t_path) {
    char clat_data[OSLAN_CONTE_SIZE];
    if (!load_data(clat_data, OSLAN_CONTE_SIZE, lv2t_path))
        return NULL;
    // OSEVPF("load_data:|%s|\n", clat_data);
    if (!split_lv2p_atti(lv2p_attri, clat_data))
        return NULL;
    //
    return lv2p_attri;
}

char *find_l2inh_ite(char *lv2p_inhe, char *lv2t_path) {
    char clat_data[OSLAN_CONTE_SIZE];
    if (!load_data(clat_data, OSLAN_CONTE_SIZE, lv2t_path))
        return NULL;
    // OSEVPF("load_data:|%s|\n", clat_data);
    char *last_str = split_lv2p_atti(NULL, clat_data);
    if (!last_str) return NULL;
    strcpy(lv2p_inhe, last_str);
    //
    return lv2p_inhe;
}

//

int meth_expand_ite(lev1_decl_t *lev1d, char *basen, lv2p_decl_t * lv2dt) {
    OSEVPF("[FUNC]:meth_expand_ite\n");
    lev1_decl_t *lv1d = lv2dt->meth;
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        switch (lv1d->levtyp) {
            case LVTP_NORM_METH:
            case LVTP_INHE_METH:
                lev1d = appe_lev1_decl(lev1d, lv1d);
                break;
            case LVTP_INHE_LEVO:
                if (!(lev1d = inser_lv1ep_ite(lev1d, basen, lv1d->inhe_lv2n, lv1d->ident)))
                    return -1;
                break;
            case LVTP_INHE_LVTP:
                if (!(lev1d = inser_lv2ep_ite(lev1d, basen, lv1d->inhe_lv2n)))
                    return -1;
                break;
            case LVTP_INHE_CLAS:
                if (!(lev1d = inser_claep_ite(lev1d, basen, lv1d->inhe_lv2n[0x00])))
                    return -1;
                break;
        }
    }
    //
    return 0x00;
}

//

lv2p_expa_t *load_lv2expt_ite(char *basen, char *lv2pn) {
    lv2p_expa_i *lv2expi = (lv2p_expa_i *) malloc(sizeof (lv2p_expa_i));
    if (!lv2expi) return NULL;
    //
    if (load_lv2p_expand(lv2expi, basen, lv2pn)) {
        free(lv2expi);
        return NULL;
    }
    lv2p_expa_t *lv2expt = creat_lv2exp(lv2expi);
    if (!lv2expt) {
        free(lv2expi);
        return NULL;
    }
    PRIN_io_lv2p_expa_t(lv2expt);
    //
    free(lv2expi);
    return lv2expt;
}

//


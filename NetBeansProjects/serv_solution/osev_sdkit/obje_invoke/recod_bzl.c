
#include "commo_header.h"
#include "kcomm_header.h"
#include "lv2p_meta/lv2me_ite.h"
#include "integ/integ_ite.h"
#include "trans/trans_utili.h"

#include "recod_bzl.h"
#include "lv2p_decla.h"

//

int recod_creac_bzl(char *basen, lv2p_decl_t *lv2dt, char *lv2_dec, lv2p_expa_t *lv2expt) {
    OSEVPF("[FUNC]:recod_creac_bzl\n");
    char lv2d_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2d_path, basen, lv2dt->lv2pn);
    char lv2t_path[MAX_PATH * 3];
    LVTP_ATTRI_FILE(lv2t_path, basen, lv2dt->lv2pn);
    char lv2e_path[MAX_PATH * 3];
    LVTP_EXPAN_FILE(lv2e_path, basen, lv2dt->lv2pn);
    OSEVPF("lv2d_path:|%s|\n", lv2d_path);
    if (!CLASS_EXIST(lv2d_path) || !CLASS_EXIST(lv2t_path) || !CLASS_EXIST(lv2e_path)) {
        _LOG_INFO("class %s exists!", lv2dt->lv2pn);
        return -1;
    }
    CREAT_LVTCON_ITE(lv2d_path, lv2t_path, lv2e_path, lv2_dec, lv2dt->lv2pn, &lv2dt->lv2p_obid, lv2expt);
    //
    return 0x00;
}

//

int recod_replc_bzl(char *basen, lv2pm_hmap *lv2pm_stm, char *lv2pn, char *lv2_dec, lv2p_expa_t *lv2expt) {
    OSEVPF("[FUNC]:recod_replc_bzl\n");
    char lv2d_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2d_path, basen, lv2pn);
    char lv2t_path[MAX_PATH * 3];
    LVTP_ATTRI_FILE(lv2t_path, basen, lv2pn);
    char lv2e_path[MAX_PATH * 3];
    LVTP_EXPAN_FILE(lv2e_path, basen, lv2pn);
    OSEVPF("lv2d_path:|%s|\n", lv2d_path);
    if (CLASS_EXIST(lv2d_path) || CLASS_EXIST(lv2t_path) || CLASS_EXIST(lv2e_path))
        return -1;
    //
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lv2pn, lv2pm_stm->lv2pan_hm);
    if (!lv2ai) return -1;
    lv2p_decl_i lv2di;
    INIT_LVTP_DECL(lv2di)
    if (!parse_l2con_ite(&lv2di, lv2d_path)) RETU_DELM(lv2di, -1);
    strcpy(lv2di.lv2p_decl, lv2_dec);
    //
    SAVE_LVTCON_ITE(lv2d_path, &lv2di, lv2t_path, lv2ai, lv2e_path, lv2expt);
    CLAM_STRU_DELE(lv2di);
    return 0x00;
}

//

int recod_cream_bzl(char *basen, lev1_meta *lev1m, char *lev1_cont) {
    char lv2dt_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2dt_path, basen, lev1m->lv2pn);
    lv2p_decl_i lv2di;
    INIT_LVTP_DECL(lv2di)
    if (!parse_l2con_ite(&lv2di, lv2dt_path)) RETU_DELM(lv2di, -1);
    //
    lv1_cont *l1lsnd = find_l1cnod_iden(lv2di.l1con_list, lev1m->lev1n, lev1m->oivk_fmtsp_om);
    if (l1lsnd) RETU_DELM(lv2di, -1);
    OSEVPF("appe_l1clst_conte\n");
    l1lsnd = appe_l1clst_conte(&lv2di.l1con_list, lev1_cont);
    if (!l1lsnd) RETU_DELM(lv2di, -1);
    if (save_l2dec_ite(lv2dt_path, &lv2di)) RETU_DELM(lv2di, -1);
    //
    CLAM_STRU_DELE(lv2di);
    return 0x00;
}

//

int recod_replm_bzl(lv2pm_hmap *lv2pm_stm, char *basen, lev1_meta *lev1m, char *lev1_cont) {
    char lv2dt_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2dt_path, basen, lev1m->lv2pn);
    lv2p_decl_i lv2di;
    INIT_LVTP_DECL(lv2di)
    if (!parse_l2con_ite(&lv2di, lv2dt_path)) RETU_DELM(lv2di, -1);
    //
    if (!modi_l1cnod_conte(lv2di.l1con_list, lev1m->lev1n, lev1m->oivk_fmtsp_om, lev1_cont))
        RETU_DELM(lv2di, -1);
    if (save_l2dec_ite(lv2dt_path, &lv2di)) RETU_DELM(lv2di, -1);
    CLAM_STRU_DELE(lv2di);
    //
    LVTP_ATTRI_FILE(lv2dt_path, basen, lev1m->lv2pn)
    lv2p_attri *lv2ai = (lv2p_attri *) cache_value(lev1m->lv2pn, lv2pm_stm->lv2pan_hm);
    if (!lv2ai) return -1;
    lv2ai->versio++;
    if (save_l2att_ite(lv2dt_path, lv2ai))
        return -1;
    //
    return 0x00;
}


//



/* 
 * File:   lv2me_ite.h
 * Author: James Xu
 *
 * Created on 2022.11.21, PM 4:39
 */

#ifndef LVTME_ITE_H
#define LVTME_ITE_H

#include "lv2p_expan.h"
#include "lv2p_list.h"
#include "lv2p_save.h"
#include "lv2p_load.h"
#include "lv2me_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    // save lv2p content
    int save_l2con_ite(char *lv2d_path, lv2p_decl_i *lv2di, char *lv2t_path, lv2p_attri *lv2ai);

#define SAVE_LVTCON_ITE(LVTD_PATH, LVTDI, LVTT_PATH, LVTAI, LVTE_PATH, LVTEXP) { \
    if (save_lv2p_decla(LVTD_PATH, (LVTDI)->lv2p_decl)) RETU_DELMP(LVTDI, -1); \
    if (save_lv2p_metho(LVTD_PATH, (LVTDI)->l1con_list)) RETU_DELMP(LVTDI, -1); \
    if (save_lv2p_attrib(LVTT_PATH, LVTAI)) RETU_DELMP(LVTDI, -1); \
    if (save_lv2p_inher(LVTT_PATH, (LVTAI)->inher_list)) RETU_DELMP(LVTDI, -1); \
    if (save_lv2p_expand(LVTE_PATH, LVTEXP)) RETU_DELMP(LVTDI, -1); \
}

    int save_l2att_ite(char *lv2t_path, lv2p_attri *lv2ai);
    int save_l2dec_ite(char *lv2d_path, lv2p_decl_i *lv2di);

    // create lv2p content
#define CREAT_LVTCON_ITE(LVTD_PATH, LVTT_PATH, LVTE_PATH, LVTDEC, LVTPN, LVTP_OBID, LVTEXP) { \
    if (save_lv2p_decla(LVTD_PATH, LVTDEC)) \
        return -1; \
    if (crea_lv2p_attrib(LVTT_PATH, LVTPN, LVTP_OBID)) \
        return -1; \
    if (save_lv2p_expand(LVTE_PATH, LVTEXP)) \
        return -1; \
}

    int delet_l2con_ite(char *lv2d_path, char *lv2t_path, char *lv2e_path);
    int delet_lv2me_ite(char *basen, char *lv2pn);

    //
    int creat_l2mbkp_ite(char *basen, char *lv2pn);
    int recov_l2mbkp_ite(char *basen, char *lv2pn);
    int delet_l2mbkp_ite(char *basen, char *lv2pn);

    // load
    lv2p_attri *parse_l2att_ite(lv2p_attri *lv2ai, char *basen, char *lv2pn);
    lv2p_attri *build_l2att_ite(lv2p_attri *lv2ai, char *basen);

    //
    int parse_intlst_ite(integra **inte_lsth, char *lv2t_path);
    int build_intlst_ite(integra **inte_lsth, char *basen, char *lv2pn);

    //
    int parse_inhlst_ite(inherit **inhe_lsth, char *lv2t_path);
    int build_inhlst_ite(inherit **inhe_lsth, char *basen, char *lv2pn);
    int build_extern_inhlst_ite(bool_osv *iexter, inherit **inhe_lsth, char *basen, char *lv2pn);

    //
    lv2p_decl_i *parse_l2con_ite(lv2p_decl_i *lv2di, char *lv2d_path);
    lv2p_decl_i *build_l2con_ite(lv2p_decl_i *lv2di, char *basen, char *lv2pn);

    //
    char *split_l2dec_ite(char *lv2_dec, char *lv2d_path);
    char *filli_l2dec_ite(char *lv2_dec, char *basen, char *lv2pn);

    //
    int parse_l2meth_ite(lv1_cont **l1clsth, char *lv2d_path);
    int build_l2meth_ite(lv1_cont **l1clsth, char *basen, char *lv2pn);

    //
    osv_oid_t *find_l2oid_ite(osv_oid_t *lv2p_obid, char *lv2t_path);
    char *find_l2att_ite(char *lv2p_attri, char *lv2t_path);
    char *find_l2inh_ite(char *lv2p_inhe, char *lv2t_path);

    //
#define LVTP_EXCOUN_ITE(LVTNOD) lv2d_expan_count(LVTNOD)
#define LEVO_EXCOUN_ITE(LVTNOD) lv1d_expan_count(LVTNOD)
    int meth_expand_ite(lev1_decl_t *lev1d, char *basen, lv2p_decl_t * lv2dt);

    //
    lv2p_expa_t *load_lv2expt_ite(char *basen, char *lv2pn);

#ifdef __cplusplus
}
#endif

#endif /* LVTME_ITE_H */


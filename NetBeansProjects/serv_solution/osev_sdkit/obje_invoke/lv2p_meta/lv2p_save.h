
/* 
 * File:   lv2p_save.h
 * Author: James Xu
 *
 * Created on 2016.12.23, AM 9:35
 */

#ifndef LVTP_SAVE_H
#define LVTP_SAVE_H

#include "lv2p_list.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int crea_lv2p_attrib(char *lv2t_path, char *lv2pn, osv_oid_t *lv2p_obid);
    
    //
    int save_lv2p_attrib(char *lv2t_path, lv2p_attri *lv2ai);
    int save_lv2p_inher(char *lv2t_path, inherit *inhe_list); //  sub

    //
    int save_lv2p_decla(char *lv2d_path, char *lv2_dec);
    int save_lv2p_metho(char *lv2d_path, lv1_cont *l1lsnd); // sub

    //
    int save_lv2p_expand(char *lv2e_path, lv2p_expa_t *lv2expt);

#ifdef __cplusplus
}
#endif

#endif /* LVTP_SAVE_H */


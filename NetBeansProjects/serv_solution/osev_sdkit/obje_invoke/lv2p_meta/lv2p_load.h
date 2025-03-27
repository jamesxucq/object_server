/* 
 * File:   lv2p_load.h
 * Author: James Xu
 *
 * Created on 2016.12.17, PM 4:21
 */

#ifndef LVTP_LOAD_H
#define LVTP_LOAD_H

#include "commo_header.h"
#include "lv2p_list.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    char *split_lv2p_atti(char *acont, char *lv2p_cont);
    char *parse_attrib_lv2p(lv2p_attri *lv2ai, char *lv2p_cont);
    int parse_extern_lv2p(bool_osv *iexter, char *lv2p_cont);
    int parse_inherit(inherit **inhe_list, char *lv2p_inhe);
    char *split_lv2p_integ(char *inte_data, char *lv2p_cont);
    char *parse_integra(integra **olsth, char *inte_data);
    char *pass_lv2p_atti(char *lv2p_cont);
    int parse_lev1_meta(lv1_cont **l1clsth, char *meth_decl);
    char *split_lv2p_stoid(char *sid_data, char *lv2p_cont);

    //
    int load_lv2p_expand(lv2p_expa_i *lv2expi, char *basen, char *lv2pn);

#ifdef __cplusplus
}
#endif

#endif /* LVTP_LOAD_H */



/* 
 * File:   debug_funct_oi.h
 * Author: James Xu
 *
 * Created on 2022.11.1, AM 9:35
 */

#ifndef DEBUG_FUNCT_OI_H
#define DEBUG_FUNCT_OI_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    void p_parse_metho(conve_metho *metho);
    void p_lv2p_prop(lv2p_prop *lv2nod);
    void p_lv2p_prop_array(lv2p_prop *lv2nod);
    void p_colum(colum *colu_data);
    void p_inherit(inherit *ilsnd);
    void p_parm_node(pamv_node *pamnod);
    void p_lev1id(lev1id *lev1i);
    void p_lev1_decl(lev1_decl_t *lev1d);
    void p_lev1_conte(lv1_cont *l1con_list);
    void p_lv2p_expa_i(lv2p_expa_i *lv2expi);
    void p_io_lv2p_expa_t(lv2p_expa_t *lv2expt);

#ifdef _DEBUG
#define PRIN_parse_metho p_parse_metho
#define PRIN_lv2p_prop p_lv2p_prop
#define PRIN_lv2p_prop_array p_lv2p_prop_array
#define PRIN_colum p_colum
#define PRIN_inherit p_inherit
#define PRIN_parm_node p_parm_node
#define PRIN_lev1id p_lev1id
#define PRIN_lev1_decl p_lev1_decl
#define PRIN_lev1_conte p_lev1_conte
#define PRIN_lv2p_expa_i p_lv2p_expa_i
#define PRIN_io_lv2p_expa_t p_io_lv2p_expa_t
#else
#define PRIN_parse_metho(...)
#define PRIN_lv2p_prop(...)
#define PRIN_lv2p_prop_array(...)
#define PRIN_colum(...)
#define PRIN_inherit(...)
#define PRIN_parm_node(...)
#define PRIN_lev1id(...)
#define PRIN_lev1_decl(...)
#define PRIN_lev1_conte(...)
#define PRIN_lv2p_expa_i(...)
#define PRIN_io_lv2p_expa_t(...)
#endif


#ifdef __cplusplus
}
#endif

#endif /* DEBUG_FUNCT_OI_H */


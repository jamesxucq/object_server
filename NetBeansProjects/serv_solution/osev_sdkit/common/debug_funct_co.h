
/* 
 * File:   debug_funct_co.h
 * Author: James Xu
 *
 * Created on 2022.11.16, AM 9:50
 */

#ifndef DEBUG_FUNCT_CO_H
#define DEBUG_FUNCT_CO_H

#include "commo_header.h"
#include "lev1_decla.h"
#include "leve_list.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    void p_lev1d_debug(lev1_decl_t *lev1d);
    void p_lv2pd_debug(lv2p_decl_t *lv2dt);
    void p_lev1_list(lev1_list *l1lst);
    void p_parms_label(char *label, char **pamvp);
    void p_lv2p_expa_tx(lv2p_expa_t *lv2expt);

#ifdef _DEBUG
#define PRIN_lev1d_debug p_lev1d_debug
#define PRIN_lv2pd_debug p_lv2pd_debug
#define PRIN_lev1_list p_lev1_list
#define PRIN_parms_label p_parms_label
#define PRIN_lv2p_expa_tx p_lv2p_expa_tx   
#else
#define PRIN_lev1d_debug(...)
#define PRIN_lv2pd_debug(...)
#define PRIN_lev1_list(...)
#define PRIN_parms_label(...)
#define PRIN_lv2p_expa_tx(...)
#endif

#ifdef __cplusplus
}
#endif

#endif /* DEBUG_FUNCT_CO_H */


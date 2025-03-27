
/* 
 * File:   filli_clang.h
 * Author: James Xu
 *
 * Created on 2017.3.15, AM10:18
 */

#ifndef FILLI_CLANG_H
#define FILLI_CLANG_H

#include "commo_header.h"

#include "lv2p_list.h"
#include "trans/trans_utili.h"
#include "filli_inline.h"

#ifdef __cplusplus
extern "C" {
#endif

    // trans-serve

    struct _conve_metho_ {
        char lv2pn[LVTN_LENGTH];
        char lev1n[LVON_LENGTH];
        char line_oivk[LVON_LENGTH]; // out invoke params list. (ao int, bo int cx int)
        char oivk_fmtsp[FMTST_COUNT_ZTAI]; // out invoke params format string
        char oivk_retyp[PAMTYP_LENGTH];
        char ibind[LVON_LENGTH];
        char lev1_body[LARGE_TEXT_SIZE];
    };

    typedef struct _conve_metho_ conve_metho; // conve oslang to clang

    // trans-serve
    char *filli_lv2po_struct(char *clang_str, char *lv2pn, char (*lv2p_prop)[PARAM_LENGTH]);

    // trans-serve
    char *filli_metho_function(char *clang_str, conve_metho *metho);
    // trans-serve
    char *filli_const_function(char *clang_str, conve_metho *metho);

    // trans-serve
    char *filli_oinvk_struct(char *clang_str, conve_metho *metho, char (*oik_dat)[PARAM_LENGTH]);

    //
    char *filli_oinvk_istruc(char *clang_str, conve_metho *metho, char (*oik_dat)[PARAM_LENGTH], char *lv2pn);
    char *filli_metho_ifunctio(char *clang_str, conve_metho *metho, char *lv2pn);

    //
    char *filli_rllv2p_conte(char *clang_str, char *lv2pn, lv2p_prop *l2_nod, char *colu_types, colum *colu_data);

    //
    void filli_parms_oinvk(OUT char *oikdat, pamv_node *pamnod);
    
#ifdef __cplusplus
}
#endif

#endif /* FILLI_CLANG_H */


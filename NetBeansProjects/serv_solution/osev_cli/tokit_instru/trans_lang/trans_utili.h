
/* 
 * File:   trans_utili.h
 * Author: James Xu
 *
 * Created on 2023.10.7, PM 2:11
 */

#ifndef TRANS_UTILI_H
#define TRANS_UTILI_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    // trans-serve
    int conv_oinvk_ident(char *fmtst, char *ident);

    // trans-serve
    int valid_metho_legal(char *lev1_cont, char *lv2p_cont, int norma_const);
    
    // trans-serve
    int conv_oinvk_type(char *fmtst, char *line_oivk);

    // trans-serve
    // int conv_oinvk_data(char (*oivk_data)[PARAM_LENGTH], char (*oik_dat)[PARAM_LENGTH], char *line_oivk);
    int conv_oinvk_data(char (*oivk_data)[PARAM_LENGTH], char *line_oivk);
    int conv_clas_decl(char (*lv2p_prop)[PARAM_LENGTH]);
    int conv_lv2p_cons(char (*lv2p_prop)[PARAM_LENGTH]);
    // char *conv_decla(char *decla, char *node_str);

    // int conv_oinvk_type(char *param_type, char *lev1_cont);

    //
    char *conv_decla(char *decla, char *conte);
    
#ifdef __cplusplus
}
#endif

#endif /* TRANS_UTILI_H */



/* 
 * File:   trans_ite.h
 * Author: James Xu
 *
 * Created on 2016.12.21, PM 3:38
 */

#ifndef TRANS_ITE_H
#define TRANS_ITE_H

#include "commo_header.h"
#include "trans/trans_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int lv2p_clang_ite(lv2p_prop *l2_nod, char *basen, lv2p_decl_t *lv2dt);
    // reload class
    int class_clang_ite(char *clang_cont, char *basen, lv2p_decl_t *lv2dt);

    //
    int metho_clang_ite(char *clang_cont, char *lev1_cont, char *lv2_dec, int norma_const);
    int imeth_clang_ite(char *clang_cont, char *lev1_cont, char *lv2_dec, lev1id *lev1i);
    int ilev1_clang_ite(char *clang_cont, char *lv2_dec, char *lev1_cont, char *lv2p_decl, lev1id *lev1i);

    //
    int chk_ibind_ite(lev1_decl_t *lev1d, lev1_meta *lev1m);

#ifdef __cplusplus
}
#endif

#endif /* TRANS_ITE_H */


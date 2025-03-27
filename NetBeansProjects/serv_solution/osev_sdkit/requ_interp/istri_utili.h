
/* 
 * File:   istri_utili.h
 * Author: James Xu
 *
 * Created on 2016.12.31, AM 9:26
 */

#ifndef ISTRI_UTILI_H
#define ISTRI_UTILI_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    // (1a1, "bb", "22", "dd"); result 1 is object, other is string
    char *decode_const_invok(pams_valu *pamvu, char *_data_line_, char *req_dat);
    //
    char *decode_query_invok(pams_valu *pamvu, char *_data_line_, char *req_dat);
    // ("aa", 11, 22, 33); result 1 is string, other is uint
    char *decode_invok_statu(char **pamvp, char *_data_line_, char *req_dat, unsigned long long req_len);

    //
    char *decod_stri_uint(char **pamvp, char *_data_line_, char *req_dat, unsigned long long req_len);

    //
    char *filli_integ_handn(OUT char *handn, char *lv2pn, char *lev1n, char *ptype);
    lev1id *build_clev1i_lev1d(OUT lev1id *lev1i, lev1_decl_t *lev1d, char *lev1n, lv1_cont *l1lsnd);
    lev1id *build_clev1i_ilv1d(OUT lev1id *lev1i, lev1_decl_t *ilv1d, char **ilv2np, lv1_cont *l1lsnd);

    //
    void librn_whole_lev1(char *librn);
    void librn_clasn_lev1(char *librn, char *lv2pn);
    void librn_metho_lev1(char *librn, lev1_meta *lev1m);
    void librn_decla_lev1(char *librn, lev1_meta *lev1m);

    void librn_whole_lv2p(char *librn);
    void librn_clasn_lv2p(char *librn, char *lv2pn);


    //

#ifdef __cplusplus
}
#endif

#endif /* ISTRI_UTILI_H */


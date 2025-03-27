
/* 
 * File:   trans_utili.h
 * Author: James Xu
 *
 * Created on 2017.3.13. AM9:54
 */

#ifndef TRANS_UTILI_H
#define TRANS_UTILI_H

#include "ostri_utili.h"

#ifdef __cplusplus
extern "C" {
#endif


    // trans-serve
    int valid_metho_legal(char *lev1_cont, char *lv2p_cont, int norma_const);
    char *conv_decla(char *decla, char *conte);
    // int conv_inne_type(char *dtype, char *conte);
    int conv_bind_type(char *name, uint32 *potyp, uint32 *size, char *conte);
    int conv_clas_decl(char (*lv2p_prop)[PARAM_LENGTH]);
    int conv_lv2p_decl(lv2p_prop *l2_nod);
    void conv_lv2p_cons(char (*lv2p_prop)[PARAM_LENGTH]);

    //
#define COLU_END    0x00
#define COLU_NUMB   0x01
#define COLU_BYTE   0x02
#define COLU_CHAR   0x04
#define COLU_STRI   0x08

    struct _colum_ {
        int8_t type; // 0x00:num 0x01:char 0x02:string -1:end
        char name[PARAM_LENGTH];
        char size[PARAM_LENGTH];
    };

    typedef struct _colum_ colum;

    //

    int crea_lv2p_colu(colum *colu_data, lv2p_prop *l2_nod);

    // trans-serve
    // out invoke param type
    int const_oinvk_pmtyp(char *fmtsop, char *line_oivk);
    int conv_oinvk_decla(char *fmtsop, char *decla);
    // trans-serve
    int conv_oinvk_fmtsp(char *fmtsop, char *ident);
    int conv_oinvk_retyp(char *ident);
    // trans-serve
    int conv_oinvk_data(char (*oivk_data)[PARAM_LENGTH], char *line_oivk);

    //
    int conv_ibind_type(char *fmtsip, char *ibin_decl);
    // in invoke param type
    int conv_ibind_decla(char *fmtsip, char *decla);

    //
    int lv2pd_ibind_fmtsp(char *fmtsip, lv2p_prop *lv2nod, char **pamvp);
    int parse_class_meta(lv2p_prop *l2_nod, char *lv2p_cont);

#ifdef __cplusplus
}
#endif

#endif /* TRANS_UTILI_H */


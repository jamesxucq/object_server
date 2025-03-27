
/* 
 * File:   inher_utili.h
 * Author: James Xu
 *
 * Created on 20211104, PM3:39
 */

#ifndef INHER_UTILI_H
#define INHER_UTILI_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
#define INHER_TYPE_BINDI    0x00
#define INHER_TYPE_WHOLE    0x01
    int chk_inher_type(char *lv2_dec, char *lev1n);
    int parse_lev1d_bindi(lv2p_prop *clnod, char *lv2_dec, char *lev1n);
    lev1_decl_t *parse_lev1d_lev1n(lev1_decl_t *lev1d, char *lv2_dec, char *lev1n);
    //
    int merge_lv2p_prop(lv2p_prop *l2_nod, lv2p_prop *lv2nod);

    // rlv2pn<=>root_lv2pn
    int filli_ilev1_fmtsd(OUT char *fmtsd, char *basen, char *rlv2pn, char *lev1n);

    //
    int regis_inher_meth(lv2pm_hmap *lv2pm_stm, char *basen, char *lv2pn, char *regi_clas, char *lev1n);
    int regis_inher_lev1(lv2pm_hmap *lv2pm_stm, char *basen, char *lv2pn, char *regi_clas, char *lev1n);
    int regis_inher_lv2p(lv2pm_hmap *lv2pm_stm, char *basen, char *lv2pn, char *regi_clas);
    int regis_inher_clas(lv2pm_hmap *lv2pm_stm, char *basen, char *lv2pn, char *regi_clas);

    //
    lev1_meta *parse_metho_decla(lev1_meta *lev1m, char *basen, inherit * innod);

    //
    int valid_imeth_legal(char *basen, lev1_decl_t *lev1d);
    int valid_ilev1_legal(char *basen, lev1_decl_t *lev1d);
    int valid_ilv2p_legal(char *basen, lev1_decl_t *lev1d);
    int valid_iclas_legal(char *basen, lev1_decl_t *lev1d);

    //
    int clear_inher_meth(lv2pm_hmap *lv2pm_stm, char *basen, char *lv2pn, char *clea_lv2p, char *lev1n);
    int clear_inher_lev1(lv2pm_hmap *lv2pm_stm, char *basen, char *lv2pn, char *clea_lv2p, char *lev1n);
    int clear_inher_lv2p(lv2pm_hmap *lv2pm_stm, char *basen, char *lv2pn, char *clea_lv2p);
    int clear_inher_clas(lv2pm_hmap *lv2pm_stm, char *basen, char *lv2pn, char *clea_lv2p);

    //
    int find_super_lv2pn(OUT char *supe_lv2pn, char *basen, lev1_decl_t *lev1d);
    
#ifdef __cplusplus
}
#endif

#endif /* INHER_UTILI_H */


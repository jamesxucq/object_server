
/* 
 * File:   lev1_utili.h
 * Author: James Xu
 *
 * Created on 2022.11.23, PM 4:01
 */

#ifndef LEVO_UTILI_H
#define LEVO_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    lev1_decl_t *parse_lev1_decla(lev1_decl_t *lv1d, char *lv2p_decl);

    // LVTP_LVTP_LEVO
    int parse_lev1d_clasp(lev1_decl_t *lev1d, char *lv2d_path);
    int parse_lev1d_clasn(lev1_decl_t *lev1d, char *basen, char *lv2pn);
    // LVTP_INHE_LEVO LVTP_INHE_LVTP
    int build_lev1d_clasp(lev1_decl_t *lev1d, char *lv2p_path, char *basen);
    int build_lev1d_clasn(lev1_decl_t *lev1d, char *basen, char *lv2pn);

    // trans-serve
    int parse_metho_conte(lev1_meta *lev1m, char *lev1_cont);
    int build_metho_conte(lev1_meta *lev1m, char *lev1_cont);
    int build_metho_ident(lev1_meta *lev1m, char *lev1_iden);

#ifdef __cplusplus
}
#endif

#endif /* LEVO_UTILI_H */



/* 
 * File:   qstri_utili.h
 * Author: James Xu
 *
 * Created on 2022.9.22, PM3:24
 */

#ifndef QSTRI_UTILI_H
#define QSTRI_UTILI_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    // 0x00: is decla, 0x01: not decla
    int chk_lv2p_decl(char *lv2p_cont);

    //
    int conve_conta_types(char *forma_types, char (*lv2p_prop)[PARAM_LENGTH]);

    //
    char *stati_rcont_types(char *forma, uint32 refe_coun);
    char *dynam_rcont_types(char *forma, uint32 refe_coun);

    //
    char *match_field_lev1d(lev1_decl_t *lv1datd, lev1_decl_t *lv1dats, lv2p_prop *l2_nod);
    char *match_field_lv2po(lv2p_prop *lv2nod, lv2p_prop *l2_nod);

    //

    
#ifdef __cplusplus
}
#endif

#endif /* QSTRI_UTILI_H */



/* 
 * File:   integ_utili.h
 * Author: James Xu
 *
 * Created on 2021.12.1, PM 3:58
 */

#ifndef INTEG_UTILI_H
#define INTEG_UTILI_H

#include "repla/repla_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int valid_imeth_integ(char *basen, lev1_decl_t *lev1d);
    int valid_ilev1_integ(char *basen, lev1_decl_t *lev1d);
    int valid_ilv2p_integ(char *basen, lev1_decl_t *lev1d);
    int valid_iclas_integ(char *basen, lev1_decl_t *lev1d);

    //
    int replc_addim_integ(lv2pm_hmap *lv2pm_stm, char *basen, replc_list *rep_nod);
    int robk_replc_addim_integ(lv2pm_hmap *lv2pm_stm, char *basen, replc_list *rep_nod);
    //
    int replc_delem_integ(lv2pm_hmap *lv2pm_stm, char *basen, replc_list *rep_nod);
    int robk_replc_delem_integ(lv2pm_hmap *lv2pm_stm, char *basen, replc_list *rep_nod);
    //
    int replc_bindm_integ(lv2pm_hmap *lv2pm_stm, char *basen, replc_list *rep_nod);
    int robk_replc_bindm_integ(lv2pm_hmap *lv2pm_stm, char *basen, replc_list *rep_nod);

    //
    int recur_inser_integ(inherit *innod, lv2pm_hmap *lv2pm_stm, char *basen, char *lv2pn);
    int recur_delet_integ(inherit *innod, lv2pm_hmap *lv2pm_stm, char *basen, char *lv2pn);


#ifdef __cplusplus
}
#endif

#endif /* INTEG_UTILI_H */


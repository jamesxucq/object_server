
/* 
 * File:   inheri_ite.h
 * Author: James Xu
 *
 * Created on 2017.9.25
 */

#ifndef INHERI_ITE_H
#define INHERI_ITE_H

#include "commo_header.h"
#include "repla/repla_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int inher_meth_ite(respo_ctrl *resctl, hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *basen, lev1_decl_t *lev1d, lev1id *crea_lev1i);
    int inher_lev1_ite(respo_ctrl *resctl, hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *basen, lev1_decl_t *lev1d, lev1id *crea_lev1i);
    int inher_lv2p_ite(respo_ctrl *resctl, hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *basen, lev1_decl_t *lev1d, lev1id *crea_lev1i);
    int inher_clas_ite(respo_ctrl *resctl, hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *basen, lev1_decl_t *lev1d, lev1id *crea_lev1i);

    //
    int inser_clapo_ite(lv2p_prop *l2_nod, char *basen, char *inhe_lv2n);
    int inser_lv2po_ite(lv2p_prop *l2_nod, char *basen, char **inhe_l2np);
    int inser_lv1da_ite(lv2p_prop *l2_nod, char *basen, char **inhe_l2np, char *lev1n);

    //
    lev1_decl_t *inser_claep_ite(lev1_decl_t *lev1d, char *basen, char *inhe_lv2n);
    lev1_decl_t *inser_lv2ep_ite(lev1_decl_t *lev1d, char *basen, char **inhe_l2np);
    lev1_decl_t *inser_lv1ep_ite(lev1_decl_t *lev1d, char *basen, char **inhe_l2np, char *lev1n);

    // 
    int inher_legal_ite(char *basen, lev1_decl_t *lev1d);
    int inher_replc_ite(lv2pm_hmap *lv2pm_stm, char *basen, replc_list *replst);
    // robk replace class
    int robk_inher_replc_ite(lv2pm_hmap *lv2pm_stm, char *basen, replc_list *replst);

    //
    int inher_dropc_ite(lv2pm_hmap *lv2pm_stm, char *basen, char *lv2pn);


#ifdef __cplusplus
}
#endif

#endif /* INHERI_ITE_H */


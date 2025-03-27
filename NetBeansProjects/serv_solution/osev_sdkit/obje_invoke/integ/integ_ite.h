
/* 
 * File:   integ_ite.h
 * Author: James Xu
 *
 * Created on 20211015, PM3:13
 */

#ifndef INTEG_ITE_H
#define INTEG_ITE_H

#include "commo_header.h"
#include "repla/repla_utili.h"
#include "lv2p_list.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int integ_creac_ite(integra **olsth, lev1_decl_t *lev1d, int range_type);
    int integ_updat_ite(char *lv2pn, char *basen, lv2p_attri *lv2ai);

    //
    int integ_cream_ite(lv2pm_hmap *lv2pm_stm, char *basen, lev1_meta *lev1m);
#define FIND_INTEG_ITE(OLIST, LEVOM) find_integ_iden(OLIST, LEVOM->lv2pn, LEVOM->lev1n)
    int robk_integ_cream_ite(integra **olsth, lev1_meta *lev1m, int range_type);

    //
    int integ_class_ite(respo_ctrl *resctl, char *basen, char *lv2pn);
    int integ_metho_ident_ite(respo_ctrl *resctl, char *basen, lev1_meta *lev1m);
    int integ_metho_empty_ite(respo_ctrl *resctl, char *basen, char *lv2pn);

    //
    int integ_replm_ite(lv2pm_hmap *lv2pm_stm, char *basen, lev1_meta *lev1m);
    int integ_relom_ite(lv2pm_hmap *lv2pm_stm, char *basen, lev1_meta *lev1m);

    //
    int integ_replc_ite(lv2pm_hmap *lv2pm_stm, char *basen, replc_list *replst);
    int robk_integ_replc_ite(lv2pm_hmap *lv2pm_stm, char *basen, replc_list *replst);
    int integ_reloc_ite(lv2pm_hmap *lv2pm_stm, char *basen, lv2p_decl_t *lv2dt);

    //
    int integ_legal_ite(char *basen, lev1_decl_t *lev1d);

    //
    int integ_dropm_ite(lv2pm_hmap *lv2pm_stm, char *basen, lev1_meta *lev1m);


#ifdef __cplusplus
}
#endif

#endif /* INTEG_ITE_H */


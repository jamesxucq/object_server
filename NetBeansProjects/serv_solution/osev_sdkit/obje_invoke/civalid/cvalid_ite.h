
/* 
 * File:   cvalid_ite.h
 * Author: James Xu
 *
 * Created on 2021.11.15, AM9:18
 */

#ifndef CVALID_ITE_H
#define CVALID_ITE_H

#include "commo_header.h"
#include "repla/repla_utili.h"
#include "cvalid_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int valid_listc_ite(lv2pm_hmap *lv2pm_stm, char *lv2pn);
    int valid_creac_ite(char *basen, lv2p_decl_t *lv2dt);
    int valid_dropc_ite(respo_ctrl *resctl, char *basen, char *lv2pn, lv2pm_hmap *lv2pm_stm);
    int valid_replc_ite(char *basen, replc_list *replst, lv2p_decl_t *lv2dt, uint32 *forced);
    int valid_intec_ite(char *basen, char *lv2pn);
    int valid_reloc_ite(char *basen, char *lv2pn);

    //
    int check_iextec_ite(char *iexte_lv2pn, char *basen, char *lv2pn);

#ifdef __cplusplus
}
#endif

#endif /* CVALID_ITE_H */


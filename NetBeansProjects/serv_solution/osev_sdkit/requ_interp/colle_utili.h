
/* 
 * File:   colle_utili.h
 * Author: James Xu
 *
 * Created on 20211109, AM9:07
 */

#ifndef COLLE_UTILI_H
#define COLLE_UTILI_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int creat_class_conte(respo_ctrl *resctl, lv2pm_hmap *lv2pm_stm, char *basen, lv2p_decl_t *lv2dt, char *lv2p_cont);
    int creat_inher_integ(respo_ctrl *resctl, hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *basen, lv2p_decl_t *lv2dt);

    //
    int reloc_clasn(respo_ctrl *resctl, lv2pm_hmap *lv2pm_stm, char *basen, char *lv2pn);
    int reloc_whole(respo_ctrl *resctl, lv2pm_hmap *lv2pm_stm, char *basen);

    //
    int replc_inher_integ(lv2pm_hmap *lv2pm_stm, char *basen, replc_list *replst);
    int robk_replc_inher_integ(lv2pm_hmap *lv2pm_stm, char *basen, replc_list *replst);


#ifdef __cplusplus
}
#endif

#endif /* COLLE_UTILI_H */


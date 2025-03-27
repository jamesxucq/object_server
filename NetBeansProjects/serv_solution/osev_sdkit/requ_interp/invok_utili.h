
/* 
 * File:   invok_utili.h
 * Author: James Xu
 *
 * Created on 2021.11.25, PM4:51
 */

#ifndef INVOK_UTILI_H
#define INVOK_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    int relom_decla(respo_ctrl *resctl, hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *basen, lev1_meta *lev1m);
    int relom_metho(respo_ctrl *resctl, hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *basen, lev1_meta *lev1m);
    int relom_clasn(respo_ctrl *resctl, hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *basen, lev1_meta *lev1m);
    int relom_whole(respo_ctrl *resctl, hand_hmap *hando_stm, lv2pm_hmap *lv2pm_stm, char *basen);

    
    
#ifdef __cplusplus
}
#endif

#endif /* INVOK_UTILI_H */



/* 
 * File:   hand_invok.h
 * Author: James Xu
 *
 * Created on 2023.4.14, AM 9:37
 */

#ifndef HAND_INVOK_H
#define HAND_INVOK_H

#ifdef __cplusplus
extern "C";
#endif

//
int invok_post_hand(respo_ctrl *resctl, base_valu *baval, osv_oid_t *lv2p_obid, pams_valu *pamvu);

// invok_list_hand
int invok_statu_list_hand(respo_ctrl *resctl, base_valu *baval, osv_oid_t *lv2p_obid, pams_valu *pamvu);
int invok_statu_stati_hand(respo_ctrl *resctl, base_valu *baval, osv_oid_t *lv2p_obid, pams_valu *pamvu);


int invok_creat_hand(respo_ctrl *resctl, base_valu *baval, osv_oid_t *lv2p_obid, pams_valu *pamvu);
int invok_reload_hand(respo_ctrl *resctl, base_valu *baval, osv_oid_t *lv2p_obid, pams_valu *pamvu);
int invok_drop_hand(respo_ctrl *resctl, base_valu *baval, osv_oid_t *lv2p_obid, pams_valu *pamvu);
int invok_repla_hand(respo_ctrl *resctl, base_valu *baval, osv_oid_t *lv2p_obid, pams_valu *pamvu);
int invok_integra_hand(respo_ctrl *resctl, base_valu *baval, osv_oid_t *lv2p_obid, pams_valu *pamvu);


#ifdef __cplusplus
}
#endif

#endif /* HAND_INVOK_H */


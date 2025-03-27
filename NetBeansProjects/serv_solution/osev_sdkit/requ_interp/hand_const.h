
/* 
 * File:   hand_const.h
 * Author: James Xu
 *
 * Created on 2023.4.14, AM 9:37
 */

#ifndef HAND_CONST_H
#define HAND_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

    // 
    int const_post_hand(respo_ctrl *resctl, void *baval, osv_oid_t *cont_obid, pams_valu *pamvu);
    //
    int const_statu_echo_hand(respo_ctrl *resctl, void *baval, osv_oid_t *cont_obid, pams_valu *pamvu);
    int const_statu_attri_hand(respo_ctrl *resctl, void *baval, osv_oid_t *cont_obid, pams_valu *pamvu);
    int const_statu_stati_hand(respo_ctrl *resctl, void *baval, osv_oid_t *cont_obid, pams_valu *pamvu);
    //
    int const_creat_hand(respo_ctrl *resctl, void *baval, osv_oid_t *cont_obid, pams_valu *pamvu);
    int const_drop_hand(respo_ctrl *resctl, void *baval, osv_oid_t *cont_obid, pams_valu *pamvu);
    int const_updat_hand(respo_ctrl *resctl, void *baval, osv_oid_t *cont_obid, pams_valu *pamvu);
    int const_inser_hand(respo_ctrl *resctl, void *baval, osv_oid_t *cont_obid, pams_valu *pamvu);
    int const_searc_hand(respo_ctrl *resctl, void *baval, osv_oid_t *cont_obid, pams_valu *pamvu);
    int const_invok_hand(respo_ctrl *resctl, void *baval, osv_oid_t *cont_obid, pams_valu *pamvu);


#ifdef __cplusplus
}
#endif

#endif /* HAND_CONST_H */


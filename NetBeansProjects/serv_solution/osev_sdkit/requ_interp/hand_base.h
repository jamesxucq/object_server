
/* 
 * File:   hand_base.h
 * Author: James Xu
 *
 * Created on 2023.4.14, AM 9:38
 */

#ifndef HAND_BASE_H
#define HAND_BASE_H

#ifdef __cplusplus
extern "C";
#endif

// authen
int base_authen_hand(respo_ctrl *resctl, session *seion, pams_valu *pamvu);
int none_bauthe_hand(respo_ctrl *resctl, session *seion, inte_value *inval);

// post
int base_post_hand(respo_ctrl *resctl, pams_valu *pamvu);

// comand
int base_comd_open_hand(respo_ctrl *resctl, pams_valu *pamvu);
int base_comd_close_hand(respo_ctrl *resctl, pams_valu *pamvu);

// status
int base_statu_echo_hand(respo_ctrl *resctl, pams_valu *pamvu);
int base_statu_statu_hand(respo_ctrl *resctl, pams_valu *pamvu);
int base_statu_stati_hand(respo_ctrl *resctl, pams_valu *pamvu);

// privile
int base_priv_list_hand(respo_ctrl *resctl, pams_valu *pamvu);
int base_priv_role_hand(respo_ctrl *resctl, pams_valu *pamvu);
int base_priv_user_hand(respo_ctrl *resctl, pams_valu *pamvu);



#ifdef __cplusplus
}
#endif

#endif /* HAND_BASE_H */



/* 
 * File:   hand_osev.h
 * Author: James Xu
 *
 * Created on 2023.4.14, AM 9:39
 */

#ifndef HAND_OSEV_H
#define HAND_OSEV_H

#ifdef __cplusplus
extern "C";
#endif

// authen
int osev_authen_hand(respo_ctrl *resctl, session *seion, pams_valu *pamvu);
int none_oauthe_hand(respo_ctrl *resctl, session *seion, inte_value *inval);

// post
int osev_post_hand(respo_ctrl *resctl, pams_valu *pamvu);

// comand
int osev_comd_open_hand(respo_ctrl *resctl, pams_valu *pamvu);
int osev_comd_close_hand(respo_ctrl *resctl, pams_valu *pamvu);

// status
int osev_statu_echo_hand(respo_ctrl *resctl, pams_valu *pamvu);
int osev_statu_statu_hand(respo_ctrl *resctl, pams_valu *pamvu);
int osev_statu_stati_hand(respo_ctrl *resctl, pams_valu *pamvu);

// privile
int osev_priv_list_hand(respo_ctrl *resctl, pams_valu *pamvu);
int osev_priv_role_hand(respo_ctrl *resctl, pams_valu *pamvu);
int osev_priv_user_hand(respo_ctrl *resctl, pams_valu *pamvu);


#ifdef __cplusplus
}
#endif

#endif /* HAND_OSEV_H */


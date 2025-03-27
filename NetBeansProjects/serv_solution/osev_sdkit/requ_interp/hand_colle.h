
/* 
 * File:   hand_colle.h
 * Author: James Xu
 *
 * Created on 2023.4.14, AM 9:37
 */

#ifndef HAND_COLLE_H
#define HAND_COLLE_H

// #include "colle_utili.h"

#ifdef __cplusplus
extern "C";
#endif

//
int colle_post_hand(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu);

int colle_statu_list_hand(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu);
int colle_statu_stati_hand(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu);

int colle_creat_hand(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu);
int colle_repla_hand(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu);
int colle_drop_hand(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu);
int colle_reload_hand(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu);
int colle_integra_hand(respo_ctrl *resctl, char *basen, pams_valu *pamvu);


#ifdef __cplusplus
}
#endif

#endif /* HAND_COLLE_H */


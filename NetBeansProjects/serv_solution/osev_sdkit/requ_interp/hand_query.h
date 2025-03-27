
/* 
 * File:   hand_query.h
 * Author: James Xu
 *
 * Created on 2023.4.14, AM 9:38
 */

#ifndef HAND_QUERY_H
#define HAND_QUERY_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    int query_post_hand(respo_ctrl *resctl, void *baval, pams_valu *pamvu);
    //
    int query_statu_echo_hand(respo_ctrl *resctl, void *baval, pams_valu *pamvu);
    int query_statu_attri_hand(respo_ctrl *resctl, void *baval, pams_valu *pamvu);
    int query_statu_stati_hand(respo_ctrl *resctl, void *baval, pams_valu *pamvu);
    //
    int query_creat_hand(respo_ctrl *resctl, void *baval, pams_valu * pamvu);
    int query_drop_hand(respo_ctrl *resctl, void *baval, pams_valu * pamvu);
    int query_updat_hand(respo_ctrl *resctl, void *baval, pams_valu * pamvu);
    int query_inser_hand(respo_ctrl *resctl, void *baval, pams_valu * pamvu);
    int query_searc_hand(respo_ctrl *resctl, void *baval, pams_valu * pamvu);
    int query_invok_hand(respo_ctrl *resctl, void *baval, pams_valu * pamvu);
    int query_facto_hand(respo_ctrl *resctl, void *baval, pams_valu * pamvu);


#ifdef __cplusplus
}
#endif

#endif /* HAND_QUERY_H */


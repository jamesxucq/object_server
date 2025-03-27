
/* 
 * File:   reqin_ite.h
 * Author: James Xu
 *
 * Created on 2024.4.18, AM 9:15
 */

#ifndef REQIN_ITE_H
#define REQIN_ITE_H

#include "commo_header.h"

//
#include "inte_osev.h"
#include "inte_base.h"
#include "inte_invok.h"
#include "inte_colle.h"
#include "inte_const.h"
#include "inte_query.h"

//
#include "hand_osev.h"
#include "hand_base.h"
#include "hand_invok.h"
#include "hand_colle.h"
#include "hand_const.h"
#include "hand_query.h"

#ifdef __cplusplus
extern "C" {
#endif

    // parser
    // parse osev param
#define PARSE_OAUTHEN_ITE(PAMVP, _DATA_LINE_, REQU_MEMO) osev_authe_inpe(PAMVP, _DATA_LINE_, REQU_MEMO)
#define PARSE_OPOST_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) osev_post_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define     PARSE_OSTAT_ECHO_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) osev_stat_echo_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define     PARSE_OSTAT_STATI_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) osev_stat_stati_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define     PARSE_OCOMD_OPEN_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) osev_comd_open_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define     PARSE_OCOMD_CLOSE_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) osev_comd_close_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define     PARSE_OPRIV_LIST_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) osev_priv_list_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define     PARSE_OPRIV_ROLE_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) osev_priv_role_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define     PARSE_OPRIV_USER_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) osev_priv_user_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)

    // parse base param
#define PARSE_BAUTHEN_ITE(PAMVP, _DATA_LINE_, REQU_MEMO) base_authe_inpe(PAMVP, _DATA_LINE_, REQU_MEMO)
#define PARSE_BPOST_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) base_post_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define     PARSE_BSTAT_ECHO_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) base_stat_echo_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define     PARSE_BSTAT_STATI_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) base_stat_stati_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define     PARSE_BCOMD_OPEN_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) base_comd_open_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define     PARSE_BCOMD_CLOSE_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) base_comd_close_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define     PARSE_BPRIV_LIST_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) base_priv_list_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define     PARSE_BPRIV_ROLE_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) base_priv_role_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define     PARSE_BPRIV_USER_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) base_priv_user_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)

    // parse invoke param
#define PARSE_IPOST_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) invok_post_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define PARSE_ISTATU_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) invok_statu_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define PARSE_ICREAT_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) invok_creat_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define PARSE_IREPLA_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) invok_repla_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define PARSE_IDROP_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) invok_drop_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define PARSE_IINTEGRA_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) invok_integra_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define PARSE_IRELOAD_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) invok_reload_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)

    // parse colle param
#define PARSE_CPOST_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) colle_post_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define PARSE_CSTATU_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) colle_statu_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define PARSE_CCREAT_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) colle_creat_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define PARSE_CREPLA_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) colle_repla_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define PARSE_CDROP_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) colle_drop_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define PARSE_CINTEGRA_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) colle_integra_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define PARSE_CRELOAD_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) colle_reload_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)

    //  parse constr param
#define PARSE_EPOST_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) const_post_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define PARSE_ESTATU_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) const_statu_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define PARSE_ECREAT_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) const_creat_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define PARSE_EDROP_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) const_drop_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define PARSE_EUPDAT_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) const_updat_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define PARSE_EINSER_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) const_inser_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define PARSE_ESEARC_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) const_searc_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define PARSE_EINVOK_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) const_invok_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)

    // parse query param
#define PARSE_QPOST_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) query_post_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define PARSE_QSTATU_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) query_statu_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define PARSE_QCREAT_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) query_creat_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define PARSE_QDROP_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) query_drop_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define PARSE_QUPDAT_ITE(PAMVU, _DATA_LINE_, REQU_STRAM) query_updat_inpe(PAMVU, _DATA_LINE_, REQU_STRAM)
#define PARSE_QINSER_ITE(PAMVU, _DATA_LINE_, REQU_STRAM) query_inser_inpe(PAMVU, _DATA_LINE_, REQU_STRAM)
#define PARSE_QSEARC_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) query_searc_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define PARSE_QINVOK_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) query_invok_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)
#define PARSE_FACTO_ITE(PAMVU, _DATA_LINE_, REQU_MEMO) query_facto_inpe(PAMVU, _DATA_LINE_, REQU_MEMO)

    // handler
    // osev hand
#define HAND_OAUTHE_ITE(RESCTL, SEION, PAMVU) osev_authen_hand(RESCTL, SEION, PAMVU)
#define HAND_ONAUTH_ITE(RESCTL, SEION, INVAL) none_oauthe_hand(RESCTL, SEION, INVAL)
#define HAND_OPOST_ITE(RESCTL, PAMVU) osev_post_hand(RESCTL, PAMVU)
#define     HAND_OSTAT_ECHO_ITE(RESCTL, PAMVU) osev_statu_echo_hand(RESCTL, PAMVU)
#define     HAND_OSTAT_STATI_ITE(RESCTL, PAMVU) osev_statu_stati_hand(RESCTL, PAMVU)
#define     HAND_OCOMD_OPEN_ITE(RESCTL, PAMVU) osev_comd_open_hand(RESCTL, PAMVU)
#define     HAND_OCOMD_CLOSE_ITE(RESCTL, PAMVU) osev_comd_close_hand(RESCTL, PAMVU)
#define     HAND_OPRIV_LIST_ITE(RESCTL, PAMVU) osev_priv_list_hand(RESCTL, PAMVU)
#define     HAND_OPRIV_ROLE_ITE(RESCTL, PAMVU) osev_priv_role_hand(RESCTL, PAMVU)
#define     HAND_OPRIV_USER_ITE(RESCTL, PAMVU) osev_priv_user_hand(RESCTL, PAMVU)

    // base hand    
#define HAND_BAUTHE_ITE(RESCTL, SEION, PAMVU) base_authen_hand(RESCTL, SEION, PAMVU)
#define HAND_BNAUTH_ITE(RESCTL, SEION, INVAL) none_bauthe_hand(RESCTL, SEION, INVAL)
#define HAND_BPOST_ITE(RESCTL, PAMVU) base_post_hand(RESCTL, PAMVU)
#define     HAND_BSTAT_ECHO_ITE(RESCTL, PAMVU) base_statu_echo_hand(RESCTL, PAMVU)
#define     HAND_BSTAT_STATI_ITE(RESCTL, PAMVU) base_statu_stati_hand(RESCTL, PAMVU)
#define     HAND_BCOMD_OPEN_ITE(RESCTL, PAMVU) base_comd_open_hand(RESCTL, PAMVU)
#define     HAND_BCOMD_CLOSE_ITE(RESCTL, PAMVU) base_comd_close_hand(RESCTL, PAMVU)
#define     HAND_BPRIV_LIST_ITE(RESCTL, PAMVU) base_priv_list_hand(RESCTL, PAMVU)
#define     HAND_BPRIV_ROLE_ITE(RESCTL, PAMVU) base_priv_role_hand(RESCTL, PAMVU)
#define     HAND_BPRIV_USER_ITE(RESCTL, PAMVU) base_priv_user_hand(RESCTL, PAMVU)

    // HAND_INVOK_BZL
#define HAND_IPOST_ITE(RESCTL, BAVAL, LVTP_OBID, PAMVU) invok_post_hand(RESCTL, BAVAL, LVTP_OBID, PAMVU)
#define     HAND_ISTATU_LIST_ITE(RESCTL, BAVAL, LVTP_OBID, PAMVU) invok_statu_list_hand(RESCTL, BAVAL, LVTP_OBID, PAMVU)
#define     HAND_ISTATU_STATI_ITE(RESCTL, BAVAL, LVTP_OBID, PAMVU) invok_statu_stati_hand(RESCTL, BAVAL, LVTP_OBID, PAMVU)
#define HAND_ICREAT_ITE(RESCTL, BAVAL, LVTP_OBID, PAMVU) invok_creat_hand(RESCTL, BAVAL, LVTP_OBID, PAMVU)
#define HAND_IRELOAD_ITE(RESCTL, BAVAL, LVTP_OBID, PAMVU) invok_reload_hand(RESCTL, BAVAL, LVTP_OBID, PAMVU)
#define HAND_IDROP_ITE(RESCTL, BAVAL, LVTP_OBID, PAMVU) invok_drop_hand(RESCTL, BAVAL, LVTP_OBID, PAMVU)
#define HAND_IREPLA_ITE(RESCTL, BAVAL, LVTP_OBID, PAMVU) invok_repla_hand(RESCTL, BAVAL, LVTP_OBID, PAMVU)
#define HAND_IINTEGRA_ITE(RESCTL, BAVAL, LVTP_OBID, PAMVU) invok_integra_hand(RESCTL, BAVAL, LVTP_OBID, PAMVU)

    // HAND_COLLE_BZL
#define HAND_CPOST_ITE(RESCTL, BAVAL, PAMVU) colle_post_hand(RESCTL, BAVAL, PAMVU)
#define     HAND_CSTATU_LIST_ITE(RESCTL, BAVAL, PAMVU) colle_statu_list_hand(RESCTL, BAVAL, PAMVU)
#define     HAND_CSTATU_STATI_ITE(RESCTL, BAVAL, PAMVU) colle_statu_stati_hand(RESCTL, BAVAL, PAMVU)
#define HAND_CCREAT_ITE(RESCTL, BAVAL, PAMVU) colle_creat_hand(RESCTL, BAVAL, PAMVU)
#define HAND_CREPLA_ITE(RESCTL, BAVAL, PAMVU) colle_repla_hand(RESCTL, BAVAL, PAMVU)
#define HAND_CDROP_ITE(RESCTL, BAVAL, PAMVU) colle_drop_hand(RESCTL, BAVAL, PAMVU)
#define HAND_CRELOAD_ITE(RESCTL, BAVAL, PAMVU) colle_reload_hand(RESCTL, BAVAL, PAMVU)
#define HAND_CINTEGRA_ITE(RESCTL, BASEN, PAMVU) colle_integra_hand(RESCTL, BASEN, PAMVU)

    // HAND_CONST_BZL
#define HAND_EPOST_ITE(RESCTL, BAVAL, CONT_OBID, PAMVU) const_post_hand(RESCTL, BAVAL, CONT_OBID, PAMVU)
#define     HAND_ESTATU_ECHO_ITE(RESCTL, BAVAL, CONT_OBID, PAMVU) const_statu_echo_hand(RESCTL, BAVAL, CONT_OBID, PAMVU)
#define     HAND_ESTATU_ATTRI_ITE(RESCTL, BAVAL, CONT_OBID, PAMVU) const_statu_attri_hand(RESCTL, BAVAL, CONT_OBID, PAMVU)
#define     HAND_ESTATU_STATI_ITE(RESCTL, BAVAL, CONT_OBID, PAMVU) const_statu_stati_hand(RESCTL, BAVAL, CONT_OBID, PAMVU)
#define HAND_ECREAT_ITE(RESCTL, BAVAL, CONT_OBID, PAMVU) const_creat_hand(RESCTL, BAVAL, CONT_OBID, PAMVU)
#define HAND_EDROP_ITE(RESCTL, BAVAL, CONT_OBID, PAMVU) const_drop_hand(RESCTL, BAVAL, CONT_OBID, PAMVU)
#define HAND_EUPDAT_ITE(RESCTL, BAVAL, CONT_OBID, PAMVU) const_updat_hand(RESCTL, BAVAL, CONT_OBID, PAMVU)
#define HAND_EINSER_ITE(RESCTL, BAVAL, CONT_OBID, PAMVU) const_inser_hand(RESCTL, BAVAL, CONT_OBID, PAMVU)
#define HAND_ESEARC_ITE(RESCTL, BAVAL, CONT_OBID, PAMVU) const_searc_hand(RESCTL, BAVAL, CONT_OBID, PAMVU)
#define HAND_EINVOK_ITE(RESCTL, BAVAL, CONT_OBID, PAMVU) const_invok_hand(RESCTL, BAVAL, CONT_OBID, PAMVU)

    // HAND_QUERY_BZL
#define HAND_QPOST_ITE(RESCTL, BAVAL, PAMVU) query_post_hand(RESCTL, BAVAL, PAMVU)
#define     HAND_QSTATU_ECHO_ITE(RESCTL, BAVAL, PAMVU) query_statu_echo_hand(RESCTL, BAVAL, PAMVU)
#define     HAND_QSTATU_ATTRI_ITE(RESCTL, BAVAL, PAMVU) query_statu_attri_hand(RESCTL, BAVAL, PAMVU)
#define     HAND_QSTATU_STATI_ITE(RESCTL, BAVAL, PAMVU) query_statu_stati_hand(RESCTL, BAVAL, PAMVU)
#define HAND_QCREAT_ITE(RESCTL, BAVAL, PAMVU) query_creat_hand(RESCTL, BAVAL, PAMVU)
#define HAND_QDROP_ITE(RESCTL, BAVAL, PAMVU) query_drop_hand(RESCTL, BAVAL, PAMVU)
#define HAND_QUPDAT_ITE(RESCTL, BAVAL, PAMVU) query_updat_hand(RESCTL, BAVAL, PAMVU)
#define HAND_QINSER_ITE(RESCTL, BAVAL, PAMVU) query_inser_hand(RESCTL, BAVAL, PAMVU)
#define HAND_QSEARC_ITE(RESCTL, BAVAL, PAMVU) query_searc_hand(RESCTL, BAVAL, PAMVU)
#define HAND_QINVOK_ITE(RESCTL, BAVAL, PAMVU) query_invok_hand(RESCTL, BAVAL, PAMVU)
#define HAND_QFACTO_ITE(RESCTL, BAVAL, PAMVU) query_facto_hand(RESCTL, BAVAL, PAMVU)

#ifdef __cplusplus
}
#endif

#endif /* REQIN_ITE_H */


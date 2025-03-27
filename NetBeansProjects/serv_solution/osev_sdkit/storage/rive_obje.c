
#include "commo_header.h"

#include "plugin_sp.h"
#include "plugin_im.h"
#include "plugin_lp.h"
#include "plugin_wt.h"

#include "rive_obje.h"

//

static rive_ha sharp_ha = {
    SHARP_ENAME,
    ENGINE_SHARP,
    sp_open_conne,
    sp_close_conne,
    //
    sp_open_sess,
    sp_close_sess,
    sp_log_flush,
    sp_begin_transa_sess,
    sp_commit_transa_sess,
    sp_reset_sess,
    //
    sp_open_curso,
    sp_open_curso_cont,
    sp_open_curso_prop,
    sp_open_curso_grou,
    sp_open_curso_inde,
    sp_close_curso,
    sp_inser_curso,
    sp_reset_curso,
    sp_next_curso,
    sp_prev_curso,
    sp_search_curso,
    sp_searn_curso,
    sp_update_curso,
    sp_remove_curso,
    sp_reconf_curso,
    set_key_sp,
    set_sid_key_sp,
    set_value_sp,
    get_key_sp,
    get_value_sp,
    //
    sp_creat_contai,
    sp_dorp_contai
};

//

static rive_ha imemo_ha = {
    IMEMO_ENAME,
    ENGINE_IMEMO,
    im_open_conne,
    im_close_conne,
    //
    im_open_sess,
    im_close_sess,
    im_log_flush,
    im_begin_transa_sess,
    im_commit_transa_sess,
    im_reset_sess,
    //
    im_open_curso,
    im_open_curso_cont,
    im_open_curso_prop,
    im_open_curso_grou,
    im_open_curso_inde,
    im_close_curso,
    im_inser_curso,
    im_reset_curso,
    im_next_curso,
    im_prev_curso,
    im_search_curso,
    im_searn_curso,
    im_update_curso,
    im_remove_curso,
    im_reconf_curso,
    set_key_im,
    set_sid_key_im,
    set_value_im,
    get_key_im,
    get_value_im,
    //
    im_creat_contai,
    im_dorp_contai
};

//

static rive_ha leap_ha = {
    LEAP_ENAME,
    ENGINE_LEAP,
    lp_open_conne,
    lp_close_conne,
    //
    lp_open_sess,
    lp_close_sess,
    lp_log_flush,
    lp_begin_transa_sess,
    lp_commit_transa_sess,
    lp_reset_sess,
    //
    lp_open_curso,
    lp_open_curso_cont,
    lp_open_curso_prop,
    lp_open_curso_grou,
    lp_open_curso_inde,
    lp_close_curso,
    lp_inser_curso,
    lp_reset_curso,
    lp_next_curso,
    lp_prev_curso,
    lp_search_curso,
    lp_searn_curso,
    lp_update_curso,
    lp_remove_curso,
    lp_reconf_curso,
    set_key_lp,
    set_sid_key_lp,
    set_value_lp,
    get_key_lp,
    get_value_lp,
    //
    lp_creat_contai,
    lp_dorp_contai
};

//
static rive_ha wtiger_ha = {
    WTIGER_ENAME,
    ENGINE_WTIGER,
    wt_open_conne,
    wt_close_conne,
    //
    wt_open_sess,
    wt_close_sess,
    wt_log_flush,
    wt_begin_transa_sess,
    wt_commit_transa_sess,
    wt_reset_sess,
    //
    wt_open_curso,
    wt_open_curso_cont,
    wt_open_curso_prop,
    wt_open_curso_grou,
    wt_open_curso_inde,
    wt_close_curso,
    wt_inser_curso,
    wt_reset_curso,
    wt_next_curso,
    wt_prev_curso,
    wt_search_curso,
    wt_searn_curso,
    wt_update_curso,
    wt_remove_curso,
    wt_reconf_curso,
    set_key_wt,
    set_sid_key_wt,
    set_value_wt,
    get_key_wt,
    get_value_wt,
    //
    wt_creat_contai,
    wt_dorp_contai
};

//

//
rive_ha *_stora_hande_tab_[STORA_ENGINE_COUNT] = {&sharp_ha, &imemo_ha, &leap_ha, &wtiger_ha};
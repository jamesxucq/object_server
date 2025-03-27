
/* 
 * File:   plugin_wt.h
 * Author: James Xu
 *
 * Created on 2016.10.10, PM 2:43
 */

#ifndef PLUGIN_WT_H
#define PLUGIN_WT_H

#include "third_party.h"
#include "sess_list.h"

#ifdef __cplusplus
extern "C" {
#endif
    //
    // typedef WT_CONNECTION riv_conne_t;
    // typedef WT_SESSION riv_sessi_t;
    // typedef WT_CURSOR riv_curso_t;

    //
    int wt_open_conne(riv_conne_t **connp, char *basen, int durab);
    int wt_close_conne(riv_conne_t *conne);
    //
    int wt_open_sess(rive_conne *, riv_sessi_t **sessp);
    int wt_close_sess(riv_sessi_t *sessi);
    int wt_log_flush(riv_sessi_t *sessi);
    int wt_begin_transa_sess(riv_sessi_t *sessi);
    int wt_commit_transa_sess(riv_sessi_t *sessi);
    int wt_reset_sess(riv_sessi_t *sessi);
    //
    int wt_open_curso(riv_curso_t **cursp, riv_sessi_t *sessi, char *uri, char *config);
    int wt_open_curso_cont(riv_curso_t **cursp, riv_sessi_t *sessi, char *contai, char *config);
    int wt_open_curso_prop(riv_curso_t **cursp, riv_sessi_t *sessi, char *contai, char *field, char *config);
    int wt_open_curso_grou(riv_curso_t **cursp, riv_sessi_t *sessi, char *group, char *config);
    int wt_open_curso_inde(riv_curso_t **cursp, riv_sessi_t *sessi, char *index, char *config);
    int wt_close_curso(riv_curso_t *curso);
    int wt_inser_curso(riv_curso_t *curso);
    int wt_reset_curso(riv_curso_t *curso);
    int wt_next_curso(riv_curso_t *curso);
    int wt_prev_curso(riv_curso_t *curso);
    int wt_search_curso(riv_curso_t *curso);
    int wt_searn_curso(riv_curso_t *curso, int *exactp);
    int wt_update_curso(riv_curso_t *curso);
    int wt_remove_curso(riv_curso_t *curso);
    int wt_reconf_curso(riv_curso_t *curso, char *config);
    void set_key_wt(riv_curso_t *curso, PK_ITEM *key);
    void set_sid_key_wt(riv_curso_t *curso, unsigned long long *key);
    void set_value_wt(riv_curso_t *curso, PK_ITEM *value);
    int get_key_wt(riv_curso_t *curso, PK_ITEM *value);
    int get_value_wt(riv_curso_t *curso, PK_ITEM *value);
    //
    int wt_creat_contai(riv_sessi_t *sessi, char *contai, char *forma);
    int wt_dorp_contai(riv_sessi_t *sessi, char *contai);

#ifdef __cplusplus
}
#endif

#endif /* PLUGIN_WT_H */


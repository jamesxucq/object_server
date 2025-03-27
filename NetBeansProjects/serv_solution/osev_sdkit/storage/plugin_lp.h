
/* 
 * File:   plugin_lp.h
 * Author: James Xu
 *
 * Created on 2023.5.5, AM 10:45
 */

#ifndef PLUGIN_LP_H
#define PLUGIN_LP_H

#include "third_party.h"
#include "sess_list.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int lp_open_conne(riv_conne_t **connp, char *basen, int durab);
    int lp_close_conne(riv_conne_t *conne);
    //
    int lp_open_sess(rive_conne *, riv_sessi_t **sessp);
    int lp_close_sess(riv_sessi_t *sessi);
    int lp_log_flush(riv_sessi_t *sessi);
    int lp_begin_transa_sess(riv_sessi_t *sessi);
    int lp_commit_transa_sess(riv_sessi_t *sessi);
    int lp_reset_sess(riv_sessi_t *sessi);
    //
    int lp_open_curso(riv_curso_t **cursp, riv_sessi_t *sessi, char *uri, char *config);
    int lp_open_curso_cont(riv_curso_t **cursp, riv_sessi_t *sessi, char *contai, char *config);
    int lp_open_curso_prop(riv_curso_t **cursp, riv_sessi_t *sessi, char *contai, char *field, char *config);
    int lp_open_curso_grou(riv_curso_t **cursp, riv_sessi_t *sessi, char *group, char *config);
    int lp_open_curso_inde(riv_curso_t **cursp, riv_sessi_t *sessi, char *index, char *config);
    int lp_close_curso(riv_curso_t *curso);
    int lp_inser_curso(riv_curso_t *curso);
    int lp_reset_curso(riv_curso_t *curso);
    int lp_next_curso(riv_curso_t *curso);
    int lp_prev_curso(riv_curso_t *curso);
    int lp_search_curso(riv_curso_t *curso);
    int lp_searn_curso(riv_curso_t *curso, int *exactp);
    int lp_update_curso(riv_curso_t *curso);
    int lp_remove_curso(riv_curso_t *curso);
    int lp_reconf_curso(riv_curso_t *curso, char *config);
    void set_key_lp(riv_curso_t *curso, PK_ITEM *key);
    void set_sid_key_lp(riv_curso_t *curso, unsigned long long *key);
    void set_value_lp(riv_curso_t *curso, PK_ITEM *value);
    int get_key_lp(riv_curso_t *curso, PK_ITEM *value);
    int get_value_lp(riv_curso_t *curso, PK_ITEM *value);
    //
    int lp_creat_contai(riv_sessi_t *sessi, char *contai, char *forma);
    int lp_dorp_contai(riv_sessi_t *sessi, char *contai);


#ifdef __cplusplus
}
#endif

#endif /* PLUGIN_LP_H */


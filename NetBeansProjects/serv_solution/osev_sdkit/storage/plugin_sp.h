
/* 
 * File:   plugin_sp.h
 * Author: James Xu
 *
 * Created on 2023.5.5., AM 10:44
 */

#ifndef PLUGIN_SP_H
#define PLUGIN_SP_H

#include "third_party.h"
#include "sess_list.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int sp_open_conne(riv_conne_t **connp, char *basen, int durab);
    int sp_close_conne(riv_conne_t *conne);
    //
    int sp_open_sess(rive_conne *, riv_sessi_t **sessp);
    int sp_close_sess(riv_sessi_t *sessi);
    int sp_log_flush(riv_sessi_t *sessi);
    int sp_begin_transa_sess(riv_sessi_t *sessi);
    int sp_commit_transa_sess(riv_sessi_t *sessi);
    int sp_reset_sess(riv_sessi_t *sessi);
    //
    int sp_open_curso(riv_curso_t **cursp, riv_sessi_t *sessi, char *uri, char *config);
    int sp_open_curso_cont(riv_curso_t **cursp, riv_sessi_t *sessi, char *contai, char *config);
    int sp_open_curso_prop(riv_curso_t **cursp, riv_sessi_t *sessi, char *contai, char *field, char *config);
    int sp_open_curso_grou(riv_curso_t **cursp, riv_sessi_t *sessi, char *group, char *config);
    int sp_open_curso_inde(riv_curso_t **cursp, riv_sessi_t *sessi, char *index, char *config);
    int sp_close_curso(riv_curso_t *curso);
    int sp_inser_curso(riv_curso_t *curso);
    int sp_reset_curso(riv_curso_t *curso);
    int sp_next_curso(riv_curso_t *curso);
    int sp_prev_curso(riv_curso_t *curso);
    int sp_search_curso(riv_curso_t *curso);
    int sp_searn_curso(riv_curso_t *curso, int *exactp);
    int sp_update_curso(riv_curso_t *curso);
    int sp_remove_curso(riv_curso_t *curso);
    int sp_reconf_curso(riv_curso_t *curso, char *config);
    void set_key_sp(riv_curso_t *curso, PK_ITEM *key);
    void set_sid_key_sp(riv_curso_t *curso, unsigned long long *key);
    void set_value_sp(riv_curso_t *curso, PK_ITEM *value);
    int get_key_sp(riv_curso_t *curso, PK_ITEM *value);
    int get_value_sp(riv_curso_t *curso, PK_ITEM *value);
    //
    int sp_creat_contai(riv_sessi_t *sessi, char *contai, char *forma);
    int sp_dorp_contai(riv_sessi_t *sessi, char *contai);


#ifdef __cplusplus
}
#endif

#endif /* PLUGIN_SP_H */


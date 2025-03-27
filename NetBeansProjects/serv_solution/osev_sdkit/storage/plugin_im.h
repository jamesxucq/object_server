
/* 
 * File:   plugin_im.h
 * Author: James Xu
 *
 * Created on 2023.5.5, AM 10:45
 */

#ifndef PLUGIN_IM_H
#define PLUGIN_IM_H

#include "third_party.h"
#include "sess_list.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int im_open_conne(riv_conne_t **connp, char *basen, int durab);
    int im_close_conne(riv_conne_t *conne);
    //
    int im_open_sess(rive_conne *, riv_sessi_t **sessp);
    int im_close_sess(riv_sessi_t *sessi);
    int im_log_flush(riv_sessi_t *sessi);
    int im_begin_transa_sess(riv_sessi_t *sessi);
    int im_commit_transa_sess(riv_sessi_t *sessi);
    int im_reset_sess(riv_sessi_t *sessi);
    //
    int im_open_curso(riv_curso_t **cursp, riv_sessi_t *sessi, char *uri, char *config);
    int im_open_curso_cont(riv_curso_t **cursp, riv_sessi_t *sessi, char *contai, char *config);
    int im_open_curso_prop(riv_curso_t **cursp, riv_sessi_t *sessi, char *contai, char *field, char *config);
    int im_open_curso_grou(riv_curso_t **cursp, riv_sessi_t *sessi, char *group, char *config);
    int im_open_curso_inde(riv_curso_t **cursp, riv_sessi_t *sessi, char *index, char *config);
    int im_close_curso(riv_curso_t *curso);
    int im_inser_curso(riv_curso_t *curso);
    int im_reset_curso(riv_curso_t *curso);
    int im_next_curso(riv_curso_t *curso);
    int im_prev_curso(riv_curso_t *curso);
    int im_search_curso(riv_curso_t *curso);
    int im_searn_curso(riv_curso_t *curso, int *exactp);
    int im_update_curso(riv_curso_t *curso);
    int im_remove_curso(riv_curso_t *curso);
    int im_reconf_curso(riv_curso_t *curso, char *config);
    void set_key_im(riv_curso_t *curso, PK_ITEM *key);
    void set_sid_key_im(riv_curso_t *curso, unsigned long long *key);
    void set_value_im(riv_curso_t *curso, PK_ITEM *value);
    int get_key_im(riv_curso_t *curso, PK_ITEM *value);
    int get_value_im(riv_curso_t *curso, PK_ITEM *value);
    //
    int im_creat_contai(riv_sessi_t *sessi, char *contai, char *forma);
    int im_dorp_contai(riv_sessi_t *sessi, char *contai);


#ifdef __cplusplus
}
#endif

#endif /* PLUGIN_IM_H */


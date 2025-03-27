#include "commo_header.h"
#include "kcomm_header.h"

// #include "stora_engine.h"
#include "third_party.h"
#include "sess_list.h"
#include "rive_bzl.h"

#include "plugin_im.h"

//

int im_open_conne(riv_conne_t **connp, char *basen, int durab) {
    return 0x00;
}

int im_close_conne(riv_conne_t *conne) {
    return 0x00;
}

//

int im_open_sess(rive_conne *conne, riv_sessi_t **sessp) {
    return 0x00;
}

int im_close_sess(riv_sessi_t *sessi) {
    return 0x00;
}

int im_log_flush(riv_sessi_t *sessi) {
    return 0x00;
}

int im_begin_transa_sess(riv_sessi_t *sessi) {
    return 0x00;
}

int im_commit_transa_sess(riv_sessi_t *sessi) {
    return 0x00;
}

int im_reset_sess(riv_sessi_t *sessi) {
    return 0x00;
}


//

int im_open_curso(riv_curso_t **cursp, riv_sessi_t *sessi, char *uri, char *config) {
    return 0x00;
}

int im_open_curso_cont(riv_curso_t **cursp, riv_sessi_t *sessi, char *contai, char *config) {
    return 0x00;
}

int im_open_curso_prop(riv_curso_t **cursp, riv_sessi_t *sessi, char *contai, char *field, char *config) {
    return 0x00;
}

int im_open_curso_grou(riv_curso_t **cursp, riv_sessi_t *sessi, char *group, char *config) {
    return 0x00;
}

int im_open_curso_inde(riv_curso_t **cursp, riv_sessi_t *sessi, char *index, char *config) {
    return 0x00;
}

int im_close_curso(riv_curso_t *curso) {
    return 0x00;
}

int im_inser_curso(riv_curso_t *curso) {
    return 0x00;
}

int im_reset_curso(riv_curso_t *curso) {
    return 0x00;
}

int im_next_curso(riv_curso_t *curso) {
    return 0x00;
}

int im_prev_curso(riv_curso_t *curso) {
    return 0x00;
}

int im_search_curso(riv_curso_t *curso) {
    return 0x00;
}

int im_searn_curso(riv_curso_t *curso, int *exactp) {
    return 0x00;
}

int im_update_curso(riv_curso_t *curso) {
    return 0x00;
}

int im_remove_curso(riv_curso_t *curso) {
    return 0x00;
}

int im_reconf_curso(riv_curso_t *curso, char *config) {
    return 0x00;
}

void set_key_im(riv_curso_t *curso, PK_ITEM *key) {
    
}

void set_sid_key_im(riv_curso_t *curso, unsigned long long *key) {

}

void set_value_im(riv_curso_t *curso, PK_ITEM *value) {

}

int get_key_im(riv_curso_t *curso, PK_ITEM *value) {
    return 0x00;
}

int get_value_im(riv_curso_t *curso, PK_ITEM *value) {
    return 0x00;
}

//

int im_creat_contai(riv_sessi_t *sessi, char *contai, char *forma) {
    return 0x00;
}

//

int im_dorp_contai(riv_sessi_t *sessi, char *contai) {
    return 0x00;
}

//
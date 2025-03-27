
/* 
 * File:   rive_struct.h
 * Author: James Xu
 *
 * Created on 2018.3.12, PM 2:27
 */

#ifndef RIVE_STRUCT_H
#define RIVE_STRUCT_H

#ifdef __cplusplus
extern "C" {
#endif

    //
#include "stora_engine.h"

    //
    typedef void riv_conne_t;
    typedef void riv_sessi_t;
    typedef void riv_curso_t;
    // typedef WT_CURSOR riv_curso_t;
    typedef WT_ITEM riv_item;


    //

    struct _seio_list_ {
        riv_sessi_t *seion;
        //
        struct _seio_list_ *next;
    };

    typedef struct _seio_list_ seio_list;
    typedef struct _seio_list_ stor_seio;

    //
#define RIV_NOVWT_CONF    "raw, overwrite=false"
#define RIV_OVEWT_CONF    "raw, overwrite=true" // by default

    //

    struct _rive_conne_ {
        riv_conne_t *conne;
        seio_list *selist;
    };

    typedef struct _rive_conne_ rive_conne;

    //

    struct _rive_ha_ {
        char *storage_name;
        unsigned int storage_type;
        // connect
        int (*open_conne)(riv_conne_t **, char *, int);
        int (*close_conne)(riv_conne_t *);
        // session
        int (*open_sessi)(rive_conne *, riv_sessi_t **);
        int (*close_sessi)(riv_sessi_t *);
        int (*log_flush_sessi)(riv_sessi_t *);
        int (*begin_transa_sessi)(riv_sessi_t *);
        int (*commit_transa_sessi)(riv_sessi_t *);
        int (*reset_sessi)(riv_sessi_t *);
        // cursor
        int (*open_curso)(riv_curso_t **, riv_sessi_t *, char *, char *);
        int (*open_curso_cont)(riv_curso_t **, riv_sessi_t *, char *, char *);
        int (*open_curso_prop)(riv_curso_t **, riv_sessi_t *, char *, char *, char *);
        int (*open_curso_grou)(riv_curso_t **, riv_sessi_t *, char *, char *);
        int (*open_curso_inde)(riv_curso_t **, riv_sessi_t *, char *, char *);
        int (*close_curso)(riv_curso_t *);
        int (*inser_curso)(riv_curso_t *);
        int (*reset_curso)(riv_curso_t *);
        int (*next_curso)(riv_curso_t *);
        int (*prev_curso)(riv_curso_t *);
        int (*search_curso)(riv_curso_t *);
        int (*searn_curso)(riv_curso_t *, int *);
        int (*update_curso)(riv_curso_t *);
        int (*remove_curso)(riv_curso_t *);
        int (*reconf_curso)(riv_curso_t *, char *);
        void (*set_key)(riv_curso_t *, PK_ITEM *);
        void (*set_sid_key)(riv_curso_t *, unsigned long long *);
        void (*set_value)(riv_curso_t *, PK_ITEM *);
        int (*get_key)(riv_curso_t *, PK_ITEM *);
        int (*get_value)(riv_curso_t *, PK_ITEM *);
        // contain
        int (*creat_contai)(riv_sessi_t *, char *, char *);
        int (*dorp_contai)(riv_sessi_t *, char *);
    };

    typedef struct _rive_ha_ rive_ha;

    //

#ifdef __cplusplus
}
#endif

#endif /* RIVE_STRUCT_H */


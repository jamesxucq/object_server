
/* 
 * File:   rive_bzl.h
 * Author: James Xu
 *
 * Created on 2017.2.7, PM 2:29
 */

#ifndef RIVE_BZL_H
#define RIVE_BZL_H

#include "sess_list.h"
#include "rive_struct.h"
#include "rive_obje.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int rivebzl_create(char *data_directory);
    int rivebzl_destroy();
    int open_rive_bzl(rive_conne *rivcon, char *basen);
    int close_rive_bzl(rive_conne *rivcon);

    //
#define ACTIV_SESSION_BZL(RVCON, STORA_HA)     activ_seion(&(RVCON)[STORA_HA->storage_type].selist, STORA_HA, (RVCON)[STORA_HA->storage_type].conne)
#define QUIET_SESSION_BZL(RVCON, STORA_HA, SLIST) quiet_seion(&(RVCON)[STORA_HA->storage_type].selist, SLIST)
#define DESTROY_SESSION_BZL(SLIST, STORA_HA)   destroy_seion(SLIST, STORA_HA)

    //
#define GET_STORAHA_BZL(STORA_TYPE) _stora_hande_tab_[STORA_TYPE]

#ifdef __cplusplus
}
#endif

#endif /* RIVE_BZL_H */


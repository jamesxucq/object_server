/* 
 * File:   cache_utili.h
 * Author: David
 *
 * Created on: 2010-3-10
 */

#ifndef CACHE_UTILI_H
#define CACHE_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    // #include "sharp/sharp.h"

    //
#include "commo_header.h"
#include "hash_table_ex.h"
#include "osev_macro.h"
#include "stri_utili.h"

    //

    priv_auth* mallo_apval();
#define DELETE_APVAL(APVAL)     { if (APVAL) free(APVAL); APVAL = NULL; }
    void dele_apval(void* apval);

    //
    int creat_ouser_cache(cachemap *ouser_hm, liv_list *role_list, liv_list *ouse_list);
    int creat_buser_cache(cachemap *buser_hm, liv_list *role_list, liv_list *buse_list);

    //
#define ADDI_USER_CACHE(USER_HM, USER_DAT) cache_insert(USER_DAT->user_name, USER_DAT, USER_HM)
#define DELE_USER_CACHE(USER_HM, USER_DAT) cache_remove(USER_DAT->user_name, USER_HM)

    //
#define FIND_USER_CACHE(USER_HM, USER_NAME) cache_value(USER_NAME, USER_HM)

    //

#ifdef __cplusplus
}
#endif

#endif /* CACHE_UTILI_H */


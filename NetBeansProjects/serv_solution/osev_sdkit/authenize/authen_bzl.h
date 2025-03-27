#ifndef AUTHEN_BZL_H
#define AUTHEN_BZL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "commo_header.h"

    //
    int authbzl_create();
    int authbzl_destroy();

    //
    //    int creat_autho_bzl();

    // auth_db operator section
    priv_auth *osev_apval_bzl(char *user_name);
    priv_auth *base_apval_bzl(char *user_name, osv_oid_t *base_obid, char *basen);

    // no authen
    priv_auth *nosv_apval_bzl(char *user_name);
    priv_auth *nodb_apval_bzl(char *user_name, osv_oid_t *base_obid, char *basen);

    void authe_epoll_exceptio(char *action_key);
    int erase_auth_cache_end(char *action_key);

    //
    int chk_reque_bzl(unsigned char *req_valid, unsigned char *plai_valid, char *req_salt);

    //
#define AUTHEN_ON   0x00
#define AUTHEN_OFF  0x01

    int auth_status_bzl();


#ifdef __cplusplus
}
#endif

#endif /* AUTHEN_BZL_H */


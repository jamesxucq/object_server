
/* 
 * File:   privile_bzl.h
 * Author: James Xu
 *
 * Created on 2016.12.30, PM 2:18
 */

#ifndef PRIVILE_BZL_H
#define PRIVILE_BZL_H

#include "live_utili.h"
#include "authen_bzl.h"
#include "grant_revke.h"
#include "privile_obje.h"

#ifdef __cplusplus
extern "C" {
#endif

    // admin
    int privbzl_create(int max_connecting);
    int privbzl_destroy();

    //
#define LIST_ROLE   0x00
#define LIST_USER   0x01
    int olist_role_bzl(respo_ctrl *resctl, char *role_name);
    int olist_user_bzl(respo_ctrl *resctl, char *ouse_name);
    int blist_role_bzl(respo_ctrl *resctl, char *role_name);
    int blist_user_bzl(respo_ctrl *resctl, char *buse_name);

    //
#define ADDI_ROLE       0x00
#define DELE_ROLE       0x01
#define GRANT_PRIV      0x02
#define REVOKE_PRIV     0x03
    // osev role
    int oadd_role_bzl(respo_ctrl *resctl, char *role_name);
    int odel_role_bzl(respo_ctrl *resctl, char *role_name);
    int ogran_priv_bzl(respo_ctrl *resctl, char *role_name, uint32 priv_code);
    int orevk_priv_bzl(respo_ctrl *resctl, char *role_name, uint32 priv_code);
    // data role
    int badd_role_bzl(respo_ctrl *resctl, char *role_name);
    int bdel_role_bzl(respo_ctrl *resctl, char *role_name);
    int bgran_priv_bzl(respo_ctrl *resctl, char *role_name, char *dist_iden, uint32 priv_code);
    int brevk_priv_bzl(respo_ctrl *resctl, char *role_name, char *dist_iden, uint32 priv_code);
    
    // drop contain privile 
    int crevk_privi_bzl(osv_oid_t *cont_obid);
    // drop base privile
    int drevk_privi_bzl(osv_oid_t *base_obid);

    //
#define ADDI_USER       0x00
#define DELE_USER       0x01
#define GRANT_ROLE      0x02
#define REVOKE_ROLE     0x03
    // osev user
    int oadd_user_bzl(respo_ctrl *resctl, char *ouse_name, unsigned char *salt_paswd);
    int odel_user_bzl(respo_ctrl *resctl, char *ouse_name);
    int ogran_role_bzl(respo_ctrl *resctl, char *ouse_name, char *role_name);
    int orevk_role_bzl(respo_ctrl *resctl, char *ouse_name, char *role_name);
    // data user
    int badd_user_bzl(respo_ctrl *resctl, char *buse_name, unsigned char *salt_paswd);
    int bdel_user_bzl(respo_ctrl *resctl, char *buse_name);
    int bgran_role_bzl(respo_ctrl *resctl, char *buse_name, char *role_name);
    int brevk_role_bzl(respo_ctrl *resctl, char *buse_name, char *role_name);

    //
    int reset_baspriv_bzl(base_valu *baval, uint32 lvmsk_code);
    int load_baspriv_bzl(base_valu *baval, uint32 lvmsk_code);

#ifdef __cplusplus
}
#endif

#endif /* PRIVILE_BZL_H */


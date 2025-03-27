
/* 
 * File:   privile_obje.h
 * Author: James Xu
 *
 * Created on 2017.1.4, AM 9:33
 */

#ifndef PRIVILE_OBJE_H
#define PRIVILE_OBJE_H

#include "commo_header.h"
#include "kcomm_header.h"

#include "grant_revke.h"

#ifdef __cplusplus
extern "C" {
#endif

    // action_insert(apval->_action_key_, apval, _priv_auth_hm_);
    extern actionmap *_priv_auth_hm_;

    //
    extern usep_lsmp _user_priv_lm_;

    //
    int load_privi_list(usep_lsmp *usep_ca, base_valu *admbv);

    //
    role_privi *oadd_role_data(base_valu *admbv, liv_list **role_lsth, char *role_name);
    int odel_role_data(base_valu *admbv, liv_list **role_lsth, char *role_name);

    inline int ogran_priv_data(base_valu *admbv, role_privi *ropriv, dist_privi *priv_dist) {
        if (oins_priv_data(admbv, AUTH_ROLES_CONT, &ropriv->role_obid, priv_dist))
            return -1;
        if (oins_priv_cache(ropriv, priv_dist))
            return -1;
        return 0x00;
    }

    inline int orevk_priv_data(base_valu *admbv, role_privi *ropriv, dist_privi *priv_dist) {
        if (odel_priv_data(admbv, AUTH_ROLES_CONT, &ropriv->role_obid, priv_dist))
            return -1;
        if (odel_priv_cache(ropriv, priv_dist))
            return -1;
        return 0x00;
    }


    //
    role_privi *badd_role_data(base_valu *admbv, liv_list **role_lsth, char *role_name);
    int bdel_role_data(base_valu *admbv, liv_list **role_lsth, char *role_name);

    inline int bgran_priv_data(base_valu *admbv, role_privi *ropriv, dist_privi *priv_dist, uint32 lvmsk_code) {
        if (bins_priv_data(admbv, AUTH_ROLES_CONT, &ropriv->role_obid, priv_dist))
            return -1;
        if (bins_priv_cache(ropriv, priv_dist, lvmsk_code))
            return -1;
        return 0x00;
    }

    inline int brevk_priv_data(base_valu *admbv, role_privi *ropriv, dist_privi *priv_dist, uint32 lvmsk_code) {
        if (bdel_priv_data(admbv, AUTH_ROLES_CONT, &ropriv->role_obid, priv_dist))
            return -1;
        if (bdel_priv_cache(ropriv, priv_dist, lvmsk_code))
            return -1;
        return 0x00;
    }

    //

    inline int crevk_priv_data(base_valu *admbv, role_privi *ropriv, osv_oid_t *cont_obid) {
        if (cdel_priv_data(admbv, AUTH_ROLES_CONT, &ropriv->role_obid, cont_obid))
            return -1;
        if (cdel_priv_cache(ropriv, cont_obid))
            return -1;
        return 0x00;
    }

    inline int drevk_priv_data(base_valu *admbv, role_privi *ropriv, osv_oid_t *base_obid) {
        if (ddel_priv_data(admbv, AUTH_ROLES_CONT, &ropriv->role_obid, base_obid))
            return -1;
        if (ddel_priv_cache(ropriv, base_obid))
            return -1;
        return 0x00;
    }


    //
    user_privi *addi_ouser_data(base_valu *admbv, liv_list **ouse_lsth, char *ouse_name, unsigned char *salt_paswd);

    inline int dele_ouser_data(base_valu *admbv, liv_list **ouse_lsth, user_privi *uepriv) {
        OSEVPF("[FUNC]:dele_ouser_data\n");
        if (live_remove(admbv, AUTH_OUSER_CONT, &uepriv->user_obid))
            return -1;
        dele_livdat(ouse_lsth, (void *) uepriv);
        return 0x00;
    }

    inline int ogran_role_data(base_valu *admbv, user_privi *uepriv, role_privi *ropriv) {
        OSEVPF("[FUNC]:ogran_role_data\n");
        if (inse_role_data(admbv, AUTH_OUSER_CONT, &uepriv->user_obid, ropriv))
            return -1;
        if (inse_role_cache(uepriv, ropriv))
            return -1;
        return 0x00;
    }

    inline int orevk_role_data(base_valu *admbv, user_privi *uepriv, role_privi *ropriv) {
        if (dele_role_data(admbv, AUTH_OUSER_CONT, &uepriv->user_obid, ropriv))
            return -1;
        if (dele_role_cache(uepriv, ropriv))
            return -1;
        return 0x00;
    }

    //
    user_privi *addi_buser_data(base_valu *admbv, liv_list **buse_lsth, char *buse_name, unsigned char *salt_paswd);

    inline int dele_buser_data(base_valu *admbv, liv_list **buse_lsth, user_privi *uepriv) {
        if (live_remove(admbv, AUTH_BUSER_CONT, &uepriv->user_obid))
            return -1;
        dele_livdat(buse_lsth, (void *) uepriv);
        return 0x00;
    }

    inline int bgran_role_data(base_valu *admbv, user_privi *uepriv, role_privi *ropriv) {
        if (inse_role_data(admbv, AUTH_BUSER_CONT, &uepriv->user_obid, ropriv))
            return -1;
        if (inse_role_cache(uepriv, ropriv))
            return -1;
        return 0x00;
    }

    inline int brevk_role_data(base_valu *admbv, user_privi *uepriv, role_privi *ropriv) {
        if (dele_role_data(admbv, AUTH_BUSER_CONT, &uepriv->user_obid, ropriv))
            return -1;
        if (dele_role_cache(uepriv, ropriv))
            return -1;
        return 0x00;
    }

#ifdef __cplusplus
}
#endif

#endif /* PRIVILE_OBJE_H */


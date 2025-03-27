
/* 
 * File:   grant_revke.h
 * Author: James Xu
 *
 * Created on 2023.4.11, AM 11:07
 */

#ifndef GRANT_REVKE_H
#define GRANT_REVKE_H

#ifdef __cplusplus
extern "C" {
#endif


    int inse_role_cache(user_privi *uepriv, role_privi *ropriv);
    int inse_role_data(base_valu *admbv, char *contn, osv_oid_t *user_obid, role_privi *ropriv);
    int dele_role_cache(user_privi *uepriv, role_privi *ropriv);
    int dele_role_data(base_valu *admbv, char *contn, osv_oid_t *user_obid, role_privi *ropriv);

    //
    int bins_priv_cache(role_privi *ropriv, dist_privi *priv_dist, uint32 lvmsk_code);
    int oins_priv_cache(role_privi *ropriv, dist_privi *priv_dist);
    int bdel_priv_cache(role_privi *ropriv, dist_privi *priv_dist, uint32 lvmsk_code);
    int odel_priv_cache(role_privi *ropriv, dist_privi *priv_dist);

    //
    int cdel_priv_cache(role_privi *ropriv, osv_oid_t *cont_obid);
    int ddel_priv_cache(role_privi *ropriv, osv_oid_t *base_obid);

    //
    int bins_priv_data(base_valu *admbv, char *contn, osv_oid_t *role_obid, dist_privi *priv_dist);
    int oins_priv_data(base_valu *admbv, char *contn, osv_oid_t *role_obid, dist_privi *priv_dist);
    int bdel_priv_data(base_valu *admbv, char *contn, osv_oid_t *role_obid, dist_privi *priv_dist);
    int odel_priv_data(base_valu *admbv, char *contn, osv_oid_t *role_obid, dist_privi *priv_dist);

    //
    int cdel_priv_data(base_valu *admbv, char *contn, osv_oid_t *role_obid, osv_oid_t *cont_obid);
    int ddel_priv_data(base_valu *admbv, char *contn, osv_oid_t *role_obid, osv_oid_t *base_obid);

#ifdef __cplusplus
}
#endif

#endif /* GRANT_REVKE_H */


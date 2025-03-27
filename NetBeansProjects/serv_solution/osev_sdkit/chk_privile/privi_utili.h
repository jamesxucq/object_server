
/* 
 * File:   privi_utili.h
 * Author: James Xu
 *
 * Created on 2016.12.27, AM 9:59
 */

#ifndef PRIVI_UTILI_H
#define PRIVI_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    int load_privi_data(usep_lsmp *usep_ca, base_valu *admbv);

    inline int initi_privi_data(usep_lsmp *usep_ca, int hmap_size) {
        OSEVPF("[FUNC]:initi_privi_data\n");
        usep_ca->osev_user_hm = creat_cache(hmap_size);
        if (!usep_ca->osev_user_hm) return ERR_FAULT;
        usep_ca->base_user_hm = creat_cache(hmap_size);
        if (!usep_ca->base_user_hm) return ERR_FAULT;
        return ERR_SUCCESS;
    }

    inline int final_privi_data(usep_lsmp *usep_ca) {
        OSEVPF("[FUNC]:final_privi_data\n");
        if (usep_ca->base_user_hm) cache_clear(usep_ca->base_user_hm);
        if (usep_ca->osev_user_hm) cache_clear(usep_ca->osev_user_hm);
        DELE_LIVE_LIST(usep_ca->buse_list)
        DELE_LIVE_LIST(usep_ca->ouse_list)
        DELE_LIVE_LIST(usep_ca->role_list)
        return ERR_SUCCESS;
    }
    //
    role_privi *find_osev_role(liv_list *role_list, char *role_name);
    // 0x00;unused 0x01:used
    int osev_role_used(liv_list *ouse_list, char *role_name);
    role_privi *find_base_role(liv_list *role_list, char *role_name);
    // 0x00;unused 0x01:used
    int base_role_used(liv_list *buse_list, char *role_name);

    //
    user_privi *find_user_privi(liv_list *user_list, char *user_name);

    //
    int check_privi_obid(role_privi *ropriv, osv_oid_t *base_obid, cachemap *baval_ca);
    int reset_privile_code(role_privi *ropriv, role_privi *sto_ropri, osv_oid_t *base_obid, uint32 lev_valu, cachemap *baval_ca);

    //
    int opriv_dist_lvoid(osv_oid_t *dist_obid, uint32 priv_code);
    int bpriv_dist_lvoid(osv_oid_t *dist_obid, uint32 *lvmsk_code, char *dist_iden, uint32 priv_code);
    int bpriv_dist_obid(osv_oid_t *dist_obid, char *dist_iden, uint32 priv_code);

    // 0x00:exists -1:error / not found
    int osev_role_exis(user_privi *uepriv, role_privi *ropriv);
    // 0x00:exists -1:error / not found
    int base_role_exis(user_privi *uepriv, role_privi *ropriv);

    //
    int orole_privi_exist(char *contn, osv_oid_t *role_obid, dist_privi *priv_dist);
    int brole_privi_exist(char *contn, osv_oid_t *role_obid, dist_privi *priv_dist);

    //
    role_privi *find_role_data(role_privi *role_memo, osv_oid_t *role_obid);

    //
    int initi_privile_level(liv_list *role_list, base_valu *admbv);

#ifdef __cplusplus
}
#endif

#endif /* PRIVI_UTILI_H */


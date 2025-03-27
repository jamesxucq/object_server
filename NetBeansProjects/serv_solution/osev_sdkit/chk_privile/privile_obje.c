#include "commo_header.h"

#include "live_utili.h"
#include "seion_struct.h"
#include "grant_revke.h"

#include "privile_obje.h"
#include "debug_funct_cp.h"

//
actionmap *_priv_auth_hm_;

//
usep_lsmp _user_priv_lm_ = {NULL, NULL, NULL, NULL, NULL};

//

int load_privi_list(usep_lsmp *usep_ca, base_valu *admbv) {
    OSEVPF("[FUNC]:load_privi_list\n");
    // OSEVPF("size role_privi:%lu\n", sizeof (role_privi));
    OSEVPF("load usep_ca->role_list\n");
    if (live_recu_load(&usep_ca->role_list, admbv, AUTH_ROLES_CONT)) {
        OSEVPF("recurs roles exception.\n");
        return -1;
    }
    PRIN_role_privi_list(usep_ca->role_list);
    // OSEVPF("size user_privi:%lu\n", sizeof (user_privi));
    OSEVPF("load usep_ca->ouse_list\n");
    if (live_recu_load(&usep_ca->ouse_list, admbv, AUTH_OUSER_CONT)) {
        OSEVPF("recurs ouser exception.\n");
        return -1;
    }
    PRIN_user_privi_list(usep_ca->ouse_list);
    //
    OSEVPF("load usep_ca->buse_list\n");
    if (live_recu_load(&usep_ca->buse_list, admbv, AUTH_BUSER_CONT)) {
        OSEVPF("recurs buser exception.\n");
        return -1;
    }
    PRIN_user_privi_list(usep_ca->buse_list);
    //
    return 0x00;
}

//

user_privi *addi_ouser_data(base_valu *admbv, liv_list **ouse_lsth, char *ouse_name, unsigned char *salt_paswd) {
    OSEVPF("[FUNC]:addi_ouser_data\n");
    OSEVPF("ouse_name:|%s|\n", ouse_name);
    liv_list *ulist = addi_live_list(ouse_lsth, sizeof (user_privi));
    if (!ulist) return NULL;
    user_privi *uepriv = (user_privi *) ulist->liv_data;
    //
    strcpy(uepriv->user_name, ouse_name);
    creat_objec_obid(&uepriv->user_obid);
    decode_salt_paswd(uepriv->salt, uepriv->password, salt_paswd);
#ifdef _DEBUG
    char obid_stri[33];
    OSEVPF("uepriv->user_obid:|%s|\n", oidstr(obid_stri, &uepriv->user_obid));
#endif
    // OSEVPF("uepriv->password:|%s| uepriv->salt:|%s|\n", uepriv->password, uepriv->salt);
    memset(uepriv->role_obid, '\0', MAX_ROLE_SIZE * sizeof (osv_oid_t));
    //
    if (live_insert(admbv, AUTH_OUSER_CONT, uepriv)) {
        dele_livlst(ouse_lsth, ulist);
        return NULL;
    }
    return uepriv;
}

//

user_privi *addi_buser_data(base_valu *admbv, liv_list **buse_lsth, char *buse_name, unsigned char *salt_paswd) {
    // OSEVPF("[FUNC]:addi_buser_data\n");
    // OSEVPF("[FUNC]:buse_name:|%s| salt_paswd:|%s|\n", buse_name, salt_paswd);
    liv_list *ulist = addi_live_list(buse_lsth, sizeof (user_privi));
    if (!ulist) return NULL;
    user_privi *uepriv = (user_privi *) ulist->liv_data;
    //
    strcpy(uepriv->user_name, buse_name);
    creat_objec_obid(&uepriv->user_obid);
    decode_salt_paswd(uepriv->salt, uepriv->password, salt_paswd);
    memset(uepriv->role_obid, '\0', MAX_ROLE_SIZE * sizeof (osv_oid_t));
    //
    if (live_insert(admbv, AUTH_BUSER_CONT, uepriv)) {
        dele_livlst(buse_lsth, ulist);
        return NULL;
    }
    return uepriv;
}

//

role_privi *oadd_role_data(base_valu *admbv, liv_list **role_lsth, char *role_name) {
    liv_list *rlist = addi_live_list(role_lsth, sizeof (role_privi));
    if (!rlist) return NULL;
    role_privi *ropriv = (role_privi *) rlist->liv_data;
    //
    ropriv->role_type = ROLE_TYPE_OSEV;
    strcpy(ropriv->role_name, role_name);
    creat_objec_obid(&ropriv->role_obid);
    memset(ropriv->priv_array, '\0', MAX_PRIVI_SIZE * sizeof (dist_privi));
    //
    if (live_insert(admbv, AUTH_ROLES_CONT, ropriv)) {
        dele_livlst(role_lsth, rlist);
        return NULL;
    }
    // for debug
#ifdef _DEBUG
    char temp[512];
    PRIN_role_privi(temp, ropriv);
    OSEVPF("role_privi --------------------------------\n");
    OSEVPF("%s", temp);
#endif
    return ropriv;
}

int odel_role_data(base_valu *admbv, liv_list **role_lsth, char *role_name) {
    role_privi *ropriv;
    liv_list *rlist = role_lsth[0x00];
    for (; rlist; rlist = rlist->next) {
        ropriv = (role_privi *) rlist->liv_data;
        if (!strcmp(role_name, ropriv->role_name))
            break;
    }
    if (!rlist) return -1;
    //
    if (live_remove(admbv, AUTH_ROLES_CONT, &ropriv->role_obid))
        return -1;
    dele_livlst(role_lsth, rlist);
    //
    return 0x00;
}

//

role_privi *badd_role_data(base_valu *admbv, liv_list **role_lsth, char *role_name) {
    liv_list *rlist = addi_live_list(role_lsth, sizeof (role_privi));
    if (!rlist) return NULL;
    role_privi * ropriv = rlist->liv_data;
    //
    ropriv->role_type = ROLE_TYPE_BASE;
    strcpy(ropriv->role_name, role_name);
    creat_objec_obid(&ropriv->role_obid);
    memset(ropriv->priv_array, '\0', MAX_PRIVI_SIZE * sizeof (dist_privi));
    //
    if (live_insert(admbv, AUTH_ROLES_CONT, ropriv)) {
        dele_livlst(role_lsth, rlist);
        return NULL;
    }
    return ropriv;
}

int bdel_role_data(base_valu *admbv, liv_list **role_lsth, char *role_name) {
    role_privi *ropriv;
    liv_list *rlist = role_lsth[0x00];
    for (; rlist; rlist = rlist->next) {
        ropriv = (role_privi *) rlist->liv_data;
        if (!strcmp(role_name, ropriv->role_name))
            break;
    }
    if (!rlist) return -1;
    //     
    if (live_remove(admbv, AUTH_ROLES_CONT, &ropriv->role_obid))
        return -1;
    dele_livlst(role_lsth, rlist);
    //
    return 0x00;
}

//


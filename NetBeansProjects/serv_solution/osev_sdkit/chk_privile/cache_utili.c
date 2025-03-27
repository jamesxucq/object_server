#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_header.h"
#include "cache_utili.h"
#include "grant_revke.h"
#include "live_utili.h"
#include "privile_obje.h"

//

priv_auth* mallo_apval() {
    priv_auth *apval = (priv_auth *) malloc(sizeof (priv_auth));
    if (!apval) return NULL;
    memset(apval, '\0', sizeof (priv_auth));
    //
    return apval;
}

void dele_apval(void* apval) {
    if (apval) free(apval);
}

//

static int build_orole_cache(cachemap *role_hm, liv_list *rlist) {
    role_privi *ropriv;
    for (; rlist; rlist = rlist->next) {
        ropriv = (role_privi *) rlist->liv_data;
        if (ROLE_TYPE_OSEV == ropriv->role_type)
            cache_insert(&ropriv->role_obid, ropriv, role_hm);
    }
    return 0x00;
}

static int build_brole_cache(cachemap *role_hm, liv_list *rlist) {
    role_privi *ropriv;
    for (; rlist; rlist = rlist->next) {
        ropriv = (role_privi *) rlist->liv_data;
        if (ROLE_TYPE_BASE == ropriv->role_type)
            cache_insert(&ropriv->role_obid, ropriv, role_hm);
    }
    return 0x00;
}

//

static int build_user_cache(cachemap *user_hm, liv_list *ulist) {
    // OSEVPF("[FUNC]:build_user_cache\n");
    user_privi *uepriv;
    //
    for (; ulist; ulist = ulist->next) {
        uepriv = (user_privi *) ulist->liv_data;
        // role_privi **ropriv = uepriv->ropriv;
        // OSEVPF("uepriv->user_name:|%s| ropriv[0x00]:|%p|\n", uepriv->user_name, ropriv[0x00]);
        cache_insert(uepriv->user_name, uepriv, user_hm);
    }
    // OSEVPF("end build_user_cache\n");
    return 0x00;
}

static int conv_obid_poin(liv_list *ulist, cachemap *role_hm) {
    OSEVPF("[FUNC]:conv_obid_poin\n");
    osv_oid_t *role_obid;
    role_privi **ropriv;
    unsigned int inde;
    for (; ulist; ulist = ulist->next) {
        OSEVPF("((user_privi *) ulist->liv_data)->user_name:|%s|\n", ((user_privi *) ulist->liv_data)->user_name);
        role_obid = ((user_privi *) ulist->liv_data)->role_obid;
        ropriv = ((user_privi *) ulist->liv_data)->ropriv;
        inde = 0x00;
        for (; (MAX_ROLE_SIZE > inde) && CHK_ZERO_OBID(role_obid); ++inde, ++role_obid, ++ropriv) {
            FILL_UNIQUE_OBID(role_obid);
#ifdef _DEBUG
            char obid_stri[OBJE_IDENTI_ZLEN];
            OSEVPF("obid_stri:|%s|\n", oidstr(obid_stri, role_obid));
#endif 
            ropriv[0x00] = (role_privi *) cache_value((void *) &role_obid[0x00], role_hm);
            if (ropriv[0x00]) {
                OSEVPF("ropriv[0x00]->role_name:|%s|\n", ropriv[0x00]->role_name);
                OSEVPF("ropriv[0x00]:|%p|\n", ropriv[0x00]);
            } else OSEVPF("role_hm find ERROR!\n");
        }
        ropriv[0x00] = NULL;
    }
    OSEVPF("end conv_obid_poin\n");
    return 0x00;
}

int creat_ouser_cache(cachemap *ouser_hm, liv_list *role_list, liv_list *ouse_list) {
    OSEVPF("[FUNC]:creat_ouser_cache\n");
    cachemap *role_hm = creat_obid_cache(ROLE_BACKET_SIZE);
    if (!role_hm) return -1;
    if (build_orole_cache(role_hm, role_list)) {
        cache_destroy(role_hm);
        return -1;
    }
    //
    if (conv_obid_poin(ouse_list, role_hm)) {
        cache_destroy(role_hm);
        return -1;
    }
    cache_destroy(role_hm);
    if (build_user_cache(ouser_hm, ouse_list))
        return -1;
    //
    return 0x00;
}

int creat_buser_cache(cachemap *buser_hm, liv_list *role_list, liv_list *buse_list) {
    OSEVPF("[FUNC]:creat_buser_cache\n");
    cachemap *role_hm = creat_obid_cache(ROLE_BACKET_SIZE);
    if (!role_hm) return -1;
    if (build_brole_cache(role_hm, role_list)) {
        cache_destroy(role_hm);
        return -1;
    }
    //
    if (conv_obid_poin(buse_list, role_hm)) {
        cache_destroy(role_hm);
        return -1;
    }
    cache_destroy(role_hm);
    if (build_user_cache(buser_hm, buse_list))
        return -1;
    //
    return 0x00;
}

//
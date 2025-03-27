#include "commo_header.h"
#include "kcomm_header.h"

#include "basev_bzl.h"
#include "cache_utili.h"
#include "privi_utili.h"
#include "live_utili.h"
#include "privi_code.h"
#include "filli_privi.h"
#include "baseda_cache.h"
#include "rstatu_bzl.h"
#include "basev_bzl.h"
#include "liv_list.h"
#include "pstri_utili.h"

#include "privile_bzl.h"
//

int privbzl_create(int max_connecting) {
    fprintf(stdout, "[FUNC]:privbzl create start!\n");
    int hashmap_size = creat_pow2n_size(max_connecting) << 0x02;
    fprintf(stdout, "creat_pow2n_size(%d):%u\n", max_connecting, creat_pow2n_size(max_connecting));
    _priv_auth_hm_ = creat_actio(dele_apval, hashmap_size);
    if (!_priv_auth_hm_) return ERR_FAULT;
    if (initi_privi_data(&_user_priv_lm_, hashmap_size))
        return ERR_FAULT;
    //
#ifndef NOAUTH
    base_valu *admbv = FIND_BADATN_BZL(OSEV_ADMINIS_VALUE);
    if (!admbv) {
        fprintf(stderr, "AUTHEN ON! Check admin odb excep!\n");
        return ERR_EXCEP;
    }
    // check privileges data exists
    if (chk_privi_data(&admbv->conda_stm, &admbv->lv2pm_stm, _priv_data_)) {
        fprintf(stderr, "Check authen data excep!\n");
        return ERR_EXCEP;
    }
    if (load_privi_data(&_user_priv_lm_, admbv)) {
        fprintf(stderr, "Load privile excep!\n");
        return ERR_FAULT;
    }
    // reset level mask
    if (initi_privile_level(_user_priv_lm_.role_list, admbv)) {
        fprintf(stderr, "Reset privile excep!\n");
        return ERR_FAULT;
    }
#endif // NOAUTH
    // #ifdef _DEBUG
    // #ifdef NOAUTH
    // base_valu *admbv = FIND_BADATN_BZL(OSEV_ADMINIS_VALUE);
    // if (!admbv) {
    // fprintf(stderr, "AUTHEN ON! Check admin odb excep!\n");
    // return ERR_EXCEP;
    // }
    // #endif // NOAUTH
    // user_recu_prin(admbv, AUTH_OUSER_CONT);
    // user_recu_prin(admbv, AUTH_BUSER_CONT);
    // #endif // _DEBUG
    //
    fprintf(stdout, "[FUNC]:privbzl create end!\n");
    return ERR_SUCCESS; //succ
}

//

int privbzl_destroy() {
    fprintf(stdout, "[FUNC]:privbzl destroy start!\n");
    final_privi_data(&_user_priv_lm_);
    if (_priv_auth_hm_)
        action_destroy(_priv_auth_hm_);
    //
    fprintf(stdout, "[FUNC]:privbzl destroy end!\n");
    return ERR_SUCCESS; //succ
}

//

int olist_role_bzl(respo_ctrl *resctl, char *role_name) {
    OSEVPF("[FUNC]:olist_role_bzl\n");
    if (role_name) {
        OSEVPF("role_name:|%s|\n", role_name);
        role_privi *ropriv = find_osev_role(_user_priv_lm_.role_list, role_name);
        if (!ropriv) {
            PDAT_EXCEPTIO_TAIL(resctl, FIND_ROLE_EXPT)
            return ERR_FAULT;
        }
        //
#ifdef _DEBUG
        char obid_stri[OBJE_IDENTI_ZLEN];
        OSEVPF("|%s|\n", oidstr(obid_stri, &ropriv->role_obid));
#endif
        //
        oprin_role_name(resctl, ropriv);
    } else oprin_role_all(resctl, _user_priv_lm_.role_list);
    //
    return ERR_SUCCESS;
}

int olist_user_bzl(respo_ctrl *resctl, char *ouse_name) {
    OSEVPF("[FUNC]:olist_user_bzl\n");
    if (ouse_name) {
        // OSEVPF("ouse_name:|%s|\n", ouse_name);
        user_privi *uepriv = FIND_USER_CACHE(_user_priv_lm_.osev_user_hm, ouse_name);
        if (!uepriv) {
            PDAT_EXCEPTIO_TAIL(resctl, FIND_USER_EXPT)
            return ERR_FAULT;
        }
        filli_user_name(resctl, uepriv);
    } else filli_user_all(resctl, _user_priv_lm_.ouse_list);
    //
    return ERR_SUCCESS;
}

//

int blist_role_bzl(respo_ctrl *resctl, char *role_name) {
    OSEVPF("[FUNC]:blist_role_bzl\n");
    if (role_name) {
        OSEVPF("role_name:|%s|\n", role_name);
        role_privi *ropriv = find_base_role(_user_priv_lm_.role_list, role_name);
        if (!ropriv) {
            PDAT_EXCEPTIO_TAIL(resctl, FIND_ROLE_EXPT)
            return ERR_FAULT;
        }
        role_privi role_memo;
        if (!find_role_data(&role_memo, &ropriv->role_obid)) {
            PDAT_EXCEPTIO_TAIL(resctl, FIND_ROLE_EXPT)
            return ERR_FAULT;
        }
        bprin_role_name(resctl, ropriv, &role_memo);
    } else bprin_role_all(resctl, _user_priv_lm_.role_list);
    //
    return ERR_SUCCESS;
}

int blist_user_bzl(respo_ctrl *resctl, char *buse_name) {
    OSEVPF("[FUNC]:blist_user_bzl\n");
    if (buse_name) {
        OSEVPF("buse_name:|%s|\n", buse_name);
        user_privi *uepriv = FIND_USER_CACHE(_user_priv_lm_.base_user_hm, buse_name);
        if (!uepriv) {
            PDAT_EXCEPTIO_TAIL(resctl, FIND_USER_EXPT)
            return ERR_FAULT;
        }
        filli_user_name(resctl, uepriv);
    } else filli_user_all(resctl, _user_priv_lm_.buse_list);
    //
    return ERR_SUCCESS;
}

//

int oadd_role_bzl(respo_ctrl *resctl, char *role_name) {
    OSEVPF("[FUNC]:oadd_role_bzl, role_name: %s\n", role_name);
    if (!role_name) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return ERR_FAULT;
    }
    base_valu *admbv = FIND_BADATN_BZL(OSEV_ADMINIS_VALUE);
    if (!admbv) {
        PDAT_EXCEPTIO_TAIL(resctl, BASE_ADMIN_EXPT)
        return ERR_FAULT;
    }
    // OSEVPF("check roles data ERROR!\n");
    if (find_osev_role(_user_priv_lm_.role_list, role_name)) {
        PDAT_EXCEPTIO_TAIL(resctl, FIND_ROLE_EXPT)
        return ERR_FAULT;
    }
    if (!oadd_role_data(admbv, &_user_priv_lm_.role_list, role_name)) {
        PDAT_EXCEPTIO_TAIL(resctl, ADDI_ROLE_EXPT)
        return ERR_FAULT;
    }
    //
    PDAT_PRODUCEN_TAIL(resctl)
    return ERR_SUCCESS;
}

int odel_role_bzl(respo_ctrl *resctl, char *role_name) {
    OSEVPF("[FUNC]:odel_role_bzl\n");
    if (!role_name) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return ERR_FAULT;
    }
    base_valu *admbv = FIND_BADATN_BZL(OSEV_ADMINIS_VALUE);
    if (!admbv) {
        PDAT_EXCEPTIO_TAIL(resctl, BASE_ADMIN_EXPT)
        return ERR_FAULT;
    }
    // OSEVPF("check roles data ERROR!\n");
    if (osev_role_used(_user_priv_lm_.ouse_list, role_name)) {
        PDAT_EXCEPTIO_TAIL(resctl, ROLE_USED_EXPT)
        return ERR_FAULT;
    }
    if (odel_role_data(admbv, &_user_priv_lm_.role_list, role_name)) {
        PDAT_EXCEPTIO_TAIL(resctl, DELE_ROLE_EXPT)
        return ERR_FAULT;
    }
    //
    PDAT_PRODUCEN_TAIL(resctl)
    return ERR_SUCCESS;
}

// destination

int ogran_priv_bzl(respo_ctrl *resctl, char *role_name, uint32 priv_code) {
    OSEVPF("[FUNC]:ogran_priv_bzl\n");
    OSEVPF("role_name:|%s| priv_code:|%08X|\n", role_name, priv_code);
    base_valu *admbv = FIND_BADATN_BZL(OSEV_ADMINIS_VALUE);
    if (!admbv) {
        PDAT_EXCEPTIO_TAIL(resctl, BASE_ADMIN_EXPT)
        return ERR_FAULT;
    }
    // OSEVPF("check roles data ERROR!\n");
    dist_privi priv_dist;
    if (opriv_dist_lvoid(&priv_dist.dist_obid, priv_code)) {
        PDAT_EXCEPTIO_TAIL(resctl, DISTI_OBID_EXPT)
        return ERR_FAULT;
    }
    priv_dist.privile_code = priv_code;
    //
    role_privi *ropriv = find_osev_role(_user_priv_lm_.role_list, role_name);
    if (!ropriv) {
        PDAT_EXCEPTIO_TAIL(resctl, FIND_ROLE_EXPT)
        return ERR_FAULT;
    }
    if (orole_privi_exist(AUTH_ROLES_CONT, &ropriv->role_obid, &priv_dist)) {
        PDAT_EXCEPTIO_TAIL(resctl, ROLE_PRIV_EXIS)
        return ERR_FAULT;
    }
    if (ogran_priv_data(admbv, ropriv, &priv_dist)) {
        PDAT_EXCEPTIO_TAIL(resctl, GRAN_PRIV_EXPT)
        return ERR_FAULT;
    }
    //
    PDAT_PRODUCEN_TAIL(resctl)
    return ERR_SUCCESS;
}

int orevk_priv_bzl(respo_ctrl *resctl, char *role_name, uint32 priv_code) {
    OSEVPF("[FUNC]:orevk_priv_bzl\n");
    OSEVPF("role_name:|%s| priv_code:|%08X|\n", role_name, priv_code);
    base_valu *admbv = FIND_BADATN_BZL(OSEV_ADMINIS_VALUE);
    if (!admbv) {
        PDAT_EXCEPTIO_TAIL(resctl, BASE_ADMIN_EXPT)
        return ERR_FAULT;
    }
    // OSEVPF("check roles data ERROR!\n");
    dist_privi priv_dist;
    if (opriv_dist_lvoid(&priv_dist.dist_obid, priv_code)) {
        PDAT_EXCEPTIO_TAIL(resctl, DISTI_OBID_EXPT)
        return ERR_FAULT;
    }
    priv_dist.privile_code = priv_code;
    //
    role_privi *ropriv = find_osev_role(_user_priv_lm_.role_list, role_name);
    if (!ropriv) {
        PDAT_EXCEPTIO_TAIL(resctl, FIND_ROLE_EXPT)
        return ERR_FAULT;
    }
    if (orevk_priv_data(admbv, ropriv, &priv_dist)) {
        PDAT_EXCEPTIO_TAIL(resctl, REVK_PRIV_EXPT)
        return ERR_FAULT;
    }
    //
    PDAT_PRODUCEN_TAIL(resctl)
    return ERR_SUCCESS;
}

//

int badd_role_bzl(respo_ctrl *resctl, char *role_name) {
    OSEVPF("[FUNC]:badd_role_bzl\n");
    base_valu *admbv = FIND_BADATN_BZL(OSEV_ADMINIS_VALUE);
    if (!admbv) {
        PDAT_EXCEPTIO_TAIL(resctl, BASE_ADMIN_EXPT)
        return ERR_FAULT;
    }
    // OSEVPF("check roles data ERROR!\n");
    if (find_base_role(_user_priv_lm_.role_list, role_name)) {
        PDAT_EXCEPTIO_TAIL(resctl, FIND_ROLE_EXPT)
        return ERR_FAULT;
    }
    if (!badd_role_data(admbv, &_user_priv_lm_.role_list, role_name)) {
        PDAT_EXCEPTIO_TAIL(resctl, ADDI_ROLE_EXPT)
        return ERR_FAULT;
    }
    //
    PDAT_PRODUCEN_TAIL(resctl)
    return ERR_SUCCESS;
}

int bdel_role_bzl(respo_ctrl *resctl, char *role_name) {
    OSEVPF("[FUNC]:bdel_role_bzl\n");
    base_valu *admbv = FIND_BADATN_BZL(OSEV_ADMINIS_VALUE);
    if (!admbv) {
        PDAT_EXCEPTIO_TAIL(resctl, BASE_ADMIN_EXPT)
        return ERR_FAULT;
    }
    // OSEVPF("check roles data ERROR!\n");
    if (base_role_used(_user_priv_lm_.buse_list, role_name)) {
        PDAT_EXCEPTIO_TAIL(resctl, ROLE_USED_EXPT)
        return ERR_FAULT;
    }
    if (bdel_role_data(admbv, &_user_priv_lm_.role_list, role_name)) {
        PDAT_EXCEPTIO_TAIL(resctl, DELE_ROLE_EXPT)
        return ERR_FAULT;
    }
    //
    PDAT_PRODUCEN_TAIL(resctl)
    return ERR_SUCCESS;
}

int bgran_priv_bzl(respo_ctrl *resctl, char *role_name, char *dist_iden, uint32 priv_code) {
    OSEVPF("[FUNC]:bgran_priv_bzl\n");
    OSEVPF("role_name:|%s| dist_iden:|%s| priv_code:|%08X|\n", role_name, dist_iden, priv_code);
    base_valu *admbv = FIND_BADATN_BZL(OSEV_ADMINIS_VALUE);
    if (!admbv) {
        PDAT_EXCEPTIO_TAIL(resctl, BASE_ADMIN_EXPT)
        return ERR_FAULT;
    }
    // OSEVPF("check roles data ERROR!\n");
    uint32 lvmsk_code = INVA_PRIVI;
    dist_privi priv_dist;
    if (bpriv_dist_lvoid(&priv_dist.dist_obid, &lvmsk_code, dist_iden, priv_code)) {
        PDAT_EXCEPTIO_TAIL(resctl, DISTI_OBID_EXPT)
        return ERR_FAULT;
    }
    priv_dist.privile_code = priv_code;
    //
    role_privi *ropriv = find_base_role(_user_priv_lm_.role_list, role_name);
    if (!ropriv) {
        PDAT_EXCEPTIO_TAIL(resctl, FIND_ROLE_EXPT)
        return ERR_FAULT;
    }
    if (brole_privi_exist(AUTH_ROLES_CONT, &ropriv->role_obid, &priv_dist)) {
        PDAT_EXCEPTIO_TAIL(resctl, ROLE_PRIV_EXIS)
        return ERR_FAULT;
    }
    if (bgran_priv_data(admbv, ropriv, &priv_dist, lvmsk_code)) {
        PDAT_EXCEPTIO_TAIL(resctl, GRAN_PRIV_EXPT)
        return ERR_FAULT;
    }
    //
    PDAT_PRODUCEN_TAIL(resctl)
    return ERR_SUCCESS;
}

int brevk_priv_bzl(respo_ctrl *resctl, char *role_name, char *dist_iden, uint32 priv_code) {
    OSEVPF("[FUNC]:brevk_priv_bzl\n");
    OSEVPF("role_name:|%s| dist_iden:|%s| priv_code:|%08X|\n", role_name, dist_iden, priv_code);
    base_valu *admbv = FIND_BADATN_BZL(OSEV_ADMINIS_VALUE);
    if (!admbv) {
        PDAT_EXCEPTIO_TAIL(resctl, BASE_ADMIN_EXPT)
        return ERR_FAULT;
    }
    // OSEVPF("check roles data ERROR!\n");
    uint32 lvmsk_code = INVA_PRIVI;
    dist_privi priv_dist;
    if (bpriv_dist_lvoid(&priv_dist.dist_obid, &lvmsk_code, dist_iden, priv_code)) {
        PDAT_EXCEPTIO_TAIL(resctl, DISTI_OBID_EXPT)
        return ERR_FAULT;
    }
    priv_dist.privile_code = priv_code;
    //
    role_privi *ropriv = find_base_role(_user_priv_lm_.role_list, role_name);
    if (!ropriv) {
        PDAT_EXCEPTIO_TAIL(resctl, FIND_ROLE_EXPT)
        return ERR_FAULT;
    }
    if (brevk_priv_data(admbv, ropriv, &priv_dist, lvmsk_code)) {
        PDAT_EXCEPTIO_TAIL(resctl, REVK_PRIV_EXPT)
        return ERR_FAULT;
    }
    //
    PDAT_PRODUCEN_TAIL(resctl)
    return ERR_SUCCESS;
}

//

int oadd_user_bzl(respo_ctrl *resctl, char *ouse_name, unsigned char *salt_paswd) {
    OSEVPF("[FUNC]:oadd_user_bzl\n");
    if (!ouse_name || !salt_paswd) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return ERR_FAULT;
    }
    base_valu *admbv = FIND_BADATN_BZL(OSEV_ADMINIS_VALUE);
    if (!admbv) {
        PDAT_EXCEPTIO_TAIL(resctl, BASE_ADMIN_EXPT)
        return ERR_FAULT;
    }
    // OSEVPF("check ouser data ERROR!\n");
    if (FIND_USER_CACHE(_user_priv_lm_.osev_user_hm, ouse_name)) {
        PDAT_EXCEPTIO_TAIL(resctl, FIND_USER_EXPT)
        return ERR_FAULT;
    }
    user_privi *uepriv = addi_ouser_data(admbv, &_user_priv_lm_.ouse_list, ouse_name, salt_paswd);
    if (!uepriv) {
        PDAT_EXCEPTIO_TAIL(resctl, ADDI_USER_EXPT)
        return ERR_FAULT;
    }
    ADDI_USER_CACHE(_user_priv_lm_.osev_user_hm, uepriv);
    // PRIN_user_all(_user_priv_lm_.ouse_list);
    PDAT_PRODUCEN_TAIL(resctl)
    return ERR_SUCCESS;
}

int odel_user_bzl(respo_ctrl *resctl, char *ouse_name) {
    OSEVPF("[FUNC]:odel_user_bzl\n");
    base_valu *admbv = FIND_BADATN_BZL(OSEV_ADMINIS_VALUE);
    if (!admbv) {
        PDAT_EXCEPTIO_TAIL(resctl, BASE_ADMIN_EXPT)
        return ERR_FAULT;
    }
    // OSEVPF("check ouser data ERROR!\n");
    user_privi *uepriv = FIND_USER_CACHE(_user_priv_lm_.osev_user_hm, ouse_name);
    if (!uepriv) {
        PDAT_EXCEPTIO_TAIL(resctl, FIND_USER_EXPT)
        return ERR_FAULT;
    }
    DELE_USER_CACHE(_user_priv_lm_.osev_user_hm, uepriv);
    if (dele_ouser_data(admbv, &_user_priv_lm_.ouse_list, uepriv)) {
        PDAT_EXCEPTIO_TAIL(resctl, DELE_USER_EXPT)
        return ERR_FAULT;
    }
    //
    PDAT_PRODUCEN_TAIL(resctl)
    return ERR_SUCCESS;
}

int ogran_role_bzl(respo_ctrl *resctl, char *ouse_name, char *role_name) {
    OSEVPF("[FUNC]:ogran_role_bzl\n");
    OSEVPF("ouse_name:|%s| role_name:|%s|\n", ouse_name, role_name);
    if (!ouse_name || !role_name) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return ERR_FAULT;
    }
    base_valu *admbv = FIND_BADATN_BZL(OSEV_ADMINIS_VALUE);
    if (!admbv) {
        PDAT_EXCEPTIO_TAIL(resctl, BASE_ADMIN_EXPT)
        return ERR_FAULT;
    }
    // OSEVPF("check ouser data ERROR!\n");
    role_privi *ropriv = find_osev_role(_user_priv_lm_.role_list, role_name);
    if (!ropriv) {
        PDAT_EXCEPTIO_TAIL(resctl, FIND_ROLE_EXPT)
        return ERR_FAULT;
    }
    user_privi *uepriv = find_user_privi(_user_priv_lm_.ouse_list, ouse_name);
    if (!uepriv) {
        PDAT_EXCEPTIO_TAIL(resctl, FIND_USER_EXPT)
        return ERR_FAULT;
    }
    //
    if (!osev_role_exis(uepriv, ropriv)) {
        PDAT_EXCEPTIO_TAIL(resctl, USER_ROLE_EXIS)
        return ERR_FAULT;
    }
    if (ogran_role_data(admbv, uepriv, ropriv)) {
        PDAT_EXCEPTIO_TAIL(resctl, GRAN_ROLE_EXPT)
        return ERR_FAULT;
    }
    //
    PDAT_PRODUCEN_TAIL(resctl)
    return ERR_SUCCESS;
}

int orevk_role_bzl(respo_ctrl *resctl, char *ouse_name, char *role_name) {
    OSEVPF("[FUNC]:orevk_role_bzl\n");
    OSEVPF("ouse_name:|%s| role_name:|%s|\n", ouse_name, role_name);
    if (!ouse_name || !role_name) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return ERR_FAULT;
    }
    base_valu *admbv = FIND_BADATN_BZL(OSEV_ADMINIS_VALUE);
    if (!admbv) {
        PDAT_EXCEPTIO_TAIL(resctl, BASE_ADMIN_EXPT)
        return ERR_FAULT;
    }
    // OSEVPF("check ouser data ERROR!\n");
    role_privi *ropriv = find_osev_role(_user_priv_lm_.role_list, role_name);
    if (!ropriv) {
        PDAT_EXCEPTIO_TAIL(resctl, FIND_ROLE_EXPT)
        return ERR_FAULT;
    }
    user_privi *uepriv = find_user_privi(_user_priv_lm_.ouse_list, ouse_name);
    if (!uepriv) {
        PDAT_EXCEPTIO_TAIL(resctl, FIND_USER_EXPT)
        return ERR_FAULT;
    }
    if (osev_role_exis(uepriv, ropriv)) {
        PDAT_EXCEPTIO_TAIL(resctl, USER_ROLE_NOTFOUND)
        return ERR_FAULT;
    }
    if (orevk_role_data(admbv, uepriv, ropriv)) {
        PDAT_EXCEPTIO_TAIL(resctl, REVK_ROLE_EXPT)
        return ERR_FAULT;
    }
    //
    PDAT_PRODUCEN_TAIL(resctl)
    return ERR_SUCCESS;
}

//

int badd_user_bzl(respo_ctrl *resctl, char *buse_name, unsigned char *salt_paswd) {
    OSEVPF("[FUNC]:badd_user_bzl\n");
    if (!buse_name || !salt_paswd) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return ERR_FAULT;
    }
    base_valu *admbv = FIND_BADATN_BZL(OSEV_ADMINIS_VALUE);
    if (!admbv) {
        PDAT_EXCEPTIO_TAIL(resctl, BASE_ADMIN_EXPT)
        return ERR_FAULT;
    }
    // OSEVPF("check users data ERROR!\n");
    if (FIND_USER_CACHE(_user_priv_lm_.base_user_hm, buse_name)) {
        PDAT_EXCEPTIO_TAIL(resctl, FIND_USER_EXPT)
        return ERR_FAULT;
    }
    user_privi *uepriv = addi_buser_data(admbv, &_user_priv_lm_.buse_list, buse_name, salt_paswd);
    if (!uepriv) {
        PDAT_EXCEPTIO_TAIL(resctl, ADDI_USER_EXPT)
        return ERR_FAULT;
    }
    ADDI_USER_CACHE(_user_priv_lm_.base_user_hm, uepriv);
    //
    PDAT_PRODUCEN_TAIL(resctl)
    return ERR_SUCCESS;
}

int bdel_user_bzl(respo_ctrl *resctl, char *buse_name) {
    OSEVPF("[FUNC]:bdel_user_bzl\n");
    base_valu *admbv = FIND_BADATN_BZL(OSEV_ADMINIS_VALUE);
    if (!admbv) {
        PDAT_EXCEPTIO_TAIL(resctl, BASE_ADMIN_EXPT)
        return ERR_FAULT;
    }
    // OSEVPF("check users data ERROR!\n");
    user_privi *uepriv = FIND_USER_CACHE(_user_priv_lm_.base_user_hm, buse_name);
    if (!uepriv) {
        PDAT_EXCEPTIO_TAIL(resctl, FIND_USER_EXPT)
        return ERR_FAULT;
    }
    DELE_USER_CACHE(_user_priv_lm_.base_user_hm, uepriv);
    if (dele_buser_data(admbv, &_user_priv_lm_.buse_list, uepriv)) {
        PDAT_EXCEPTIO_TAIL(resctl, DELE_USER_EXPT)
        return ERR_FAULT;
    }
    //
    PDAT_PRODUCEN_TAIL(resctl)
    return ERR_SUCCESS;
}

int bgran_role_bzl(respo_ctrl *resctl, char *buse_name, char *role_name) {
    OSEVPF("[FUNC]:bgran_role_bzl\n");
    OSEVPF("buse_name:|%s| role_name:|%s|\n", buse_name, role_name);
    if (!buse_name || !role_name) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return ERR_FAULT;
    }
    base_valu *admbv = FIND_BADATN_BZL(OSEV_ADMINIS_VALUE);
    if (!admbv) {
        PDAT_EXCEPTIO_TAIL(resctl, BASE_ADMIN_EXPT)
        return ERR_FAULT;
    }
    // OSEVPF("check users data ERROR!\n");
    role_privi *ropriv = find_base_role(_user_priv_lm_.role_list, role_name);
    if (!ropriv) {
        PDAT_EXCEPTIO_TAIL(resctl, FIND_ROLE_EXPT)
        return ERR_FAULT;
    }
    user_privi *uepriv = find_user_privi(_user_priv_lm_.buse_list, buse_name);
    if (!uepriv) {
        PDAT_EXCEPTIO_TAIL(resctl, FIND_USER_EXPT)
        return ERR_FAULT;
    }
    //
    if (!base_role_exis(uepriv, ropriv)) {
        PDAT_EXCEPTIO_TAIL(resctl, USER_ROLE_EXIS)
        return ERR_FAULT;
    }
    if (bgran_role_data(admbv, uepriv, ropriv)) {
        PDAT_EXCEPTIO_TAIL(resctl, GRAN_ROLE_EXPT)
        return ERR_FAULT;
    }
    //
    PDAT_PRODUCEN_TAIL(resctl)
    return ERR_SUCCESS;
}

int brevk_role_bzl(respo_ctrl *resctl, char *buse_name, char *role_name) {
    OSEVPF("[FUNC]:brevk_role_bzl\n");
    OSEVPF("buse_name:|%s| role_name:|%s|\n", buse_name, role_name);
    if (!buse_name || !role_name) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return ERR_FAULT;
    }
    base_valu *admbv = FIND_BADATN_BZL(OSEV_ADMINIS_VALUE);
    if (!admbv) {
        PDAT_EXCEPTIO_TAIL(resctl, BASE_ADMIN_EXPT)
        return ERR_FAULT;
    }
    // OSEVPF("check users data ERROR!\n");
    role_privi *ropriv = find_base_role(_user_priv_lm_.role_list, role_name);
    if (!ropriv) {
        PDAT_EXCEPTIO_TAIL(resctl, FIND_ROLE_EXPT)
        return ERR_FAULT;
    }
    //
    user_privi *uepriv = find_user_privi(_user_priv_lm_.buse_list, buse_name);
    if (!uepriv) {
        PDAT_EXCEPTIO_TAIL(resctl, FIND_USER_EXPT)
        return ERR_FAULT;
    }
    if (base_role_exis(uepriv, ropriv)) {
        PDAT_EXCEPTIO_TAIL(resctl, USER_ROLE_NOTFOUND)
        return ERR_FAULT;
    }
    if (brevk_role_data(admbv, uepriv, ropriv)) {
        PDAT_EXCEPTIO_TAIL(resctl, REVK_ROLE_EXPT)
        return ERR_FAULT;
    }
    //
    PDAT_PRODUCEN_TAIL(resctl)
    return ERR_SUCCESS;
}

//

int reset_baspriv_bzl(base_valu *baval, uint32 lvmsk_code) {
    OSEVPF("[FUNC]:reset_baspriv_bzl\n");
#ifdef _DEBUG
    char obid_stri[OBJE_IDENTI_ZLEN];
    OSEVPF("reset pirvi obid:|%s|\n", oidstr(obid_stri, &baval->base_obid));
#endif
    if (baval->lvmsk_code == lvmsk_code) {
        OSEVPF("baval->lvmsk_code:|%08x| lvmsk_code:|%08x|\n", baval->lvmsk_code, lvmsk_code);
        return 0x00;
    }
    base_valu *admbv = FIND_BADATN_BZL(OSEV_ADMINIS_VALUE);
    if (!admbv) {
        _LOG_WARN("Not found %s odb!", OSEV_ADMINIS_VALUE);
        return -1;
    }
    cachemap *baval_ca = initi_baval_cache();
    if (!baval_ca) return -1;
    //
    role_privi role_memo;
    valu_memo_t role_dat;
    MINIT_VALU(&role_dat, &role_memo, sizeof (role_privi));
    liv_list *rlist = _user_priv_lm_.role_list;
    for (; rlist; rlist = rlist->next) {
        OSEVPF("----- name:|%s|\n", ((role_privi *) rlist->liv_data)->role_name);
        if (!check_privi_obid((role_privi *) rlist->liv_data, &baval->base_obid, baval_ca)) {
            OSEVPF("Need reset role name:|%s|\n", ((role_privi *) rlist->liv_data)->role_name);
            if (live_load(&role_dat, admbv, AUTH_ROLES_CONT, &((role_privi *) rlist->liv_data)->role_obid)) {
                final_baval_cache(baval_ca);
                return -1;
            }
            if (reset_privile_code((role_privi *) rlist->liv_data, &role_memo, &baval->base_obid, lvmsk_code, baval_ca)) {
                final_baval_cache(baval_ca);
                return -1;
            }
            // memcpy(rlist->liv_data, &role_dat, sizeof (role_privi));
        }
    }
    baval->lvmsk_code = lvmsk_code;
    //
    final_baval_cache(baval_ca);
    return 0x00;
}

//

int load_baspriv_bzl(base_valu *baval, uint32 lvmsk_code) {
    OSEVPF("[FUNC]:load_baspriv_bzl\n");
    base_valu *admbv = FIND_BADATN_BZL(OSEV_ADMINIS_VALUE);
    if (!admbv) return -1;
    cachemap *baval_ca = initi_baval_cache();
    if (!baval_ca) return -1;
    //
    role_privi role_memo;
    valu_memo_t role_dat;
    MINIT_VALU(&role_dat, &role_memo, sizeof (role_privi));
    liv_list *rlist = _user_priv_lm_.role_list;
    for (; rlist; rlist = rlist->next) {
        if (!check_privi_obid((role_privi *) rlist->liv_data, &baval->base_obid, baval_ca)) {
            if (live_load(&role_dat, admbv, AUTH_ROLES_CONT, &((role_privi *) rlist->liv_data)->role_obid)) {
                final_baval_cache(baval_ca);
                return -1;
            }
            if (reset_privile_code((role_privi *) rlist->liv_data, &role_memo, &baval->base_obid, lvmsk_code, baval_ca)) {
                final_baval_cache(baval_ca);
                return -1;
            }
            // memcpy(rlist->liv_data, &role_dat, sizeof (role_privi));
        }
    }
    baval->lvmsk_code = lvmsk_code;
    // OSEVPF("end, load_baspriv_bzl\n");
    final_baval_cache(baval_ca);
    return 0x00;
}

//

int crevk_privi_bzl(osv_oid_t *cont_obid) {
    OSEVPF("[FUNC]:crevk_privi_bzl\n");
#ifdef _DEBUG
    char obid_stri[OBJE_IDENTI_ZLEN];
    OSEVPF("cont_obid:|%s|\n", oidstr(obid_stri, cont_obid));
#endif
    base_valu *admbv = FIND_BADATN_BZL(OSEV_ADMINIS_VALUE);
    if (!admbv) return ERR_FAULT;
    // OSEVPF("check roles data ERROR!\n");
    role_privi *ropriv;
    liv_list *rlist = _user_priv_lm_.role_list;
    for (; rlist; rlist = rlist->next) {
        ropriv = (role_privi *) rlist->liv_data;
        if (ROLE_TYPE_BASE == ropriv->role_type)
            crevk_priv_data(admbv, ropriv, cont_obid);
    }
    //
    return ERR_SUCCESS;
}

int drevk_privi_bzl(osv_oid_t *base_obid) {
    OSEVPF("[FUNC]:drevk_privi_bzl\n");
#ifdef _DEBUG
    char obid_stri[OBJE_IDENTI_ZLEN];
    OSEVPF("cont_obid:|%s|\n", oidstr(obid_stri, base_obid));
#endif
    base_valu *admbv = FIND_BADATN_BZL(OSEV_ADMINIS_VALUE);
    if (!admbv) return ERR_FAULT;
    // OSEVPF("check roles data ERROR!\n");
    role_privi *ropriv;
    liv_list *rlist = _user_priv_lm_.role_list;
    for (; rlist; rlist = rlist->next) {
        ropriv = (role_privi *) rlist->liv_data;
        if (ROLE_TYPE_BASE == ropriv->role_type)
            drevk_priv_data(admbv, ropriv, base_obid);
    }
    //
    return ERR_SUCCESS;
}


#include "commo_header.h"
#include "kcomm_header.h"

#include "privi_code.h"
#include "live_utili.h"

#include "debug_funct_cp.h"
#include "grant_revke.h"
#include "liv_list.h"

//

int inse_role_cache(user_privi *uepriv, role_privi *ropriv) {
    OSEVPF("[FUNC]:inse_role_cache\n");
    role_privi **user_role = uepriv->ropriv;
    unsigned int inde = 0x00;
    for (; (MAX_ROLE_SIZE > inde) && user_role[0x00]; ++inde, ++user_role);
    if (MAX_ROLE_SIZE == inde) return -1;
    user_role[0x00] = ropriv;
    //
    return 0x00;
}

int inse_role_data(base_valu *admbv, char *contn, osv_oid_t *user_obid, role_privi *ropriv) {
    OSEVPF("[FUNC]:inse_role_data\n");
    user_privi user_memo;
    loop_memo_t user_dat;
    minit_dest(&user_dat, &user_memo, sizeof (user_privi));
    if (loop_load(&user_dat, admbv, contn, user_obid)) {
        free_dest(&user_dat);
        return -1;
    }
    //
    osv_oid_t *role_obid = user_memo.role_obid;
    unsigned int inde = 0x00;
    for (; (MAX_ROLE_SIZE > inde) && CHK_ZERO_OBID(role_obid); ++inde, ++role_obid);
    if (MAX_ROLE_SIZE == inde) {
        free_dest(&user_dat);
        return -1;
    }
    OBID_BINARY_COPY(role_obid, & ropriv->role_obid)
            //
    if (loop_save(admbv, contn, &user_dat, user_obid)) {
        free_dest(&user_dat);
        return -1;
    }
    //
    free_dest(&user_dat);
    return 0x00;
}

//

static void redu_role_poin(role_privi **user_role, int posi) {
    role_privi **role_inde = user_role + 0x01;
    ++posi;
    while ((MAX_ROLE_SIZE > posi) && role_inde[0x00]) {
        user_role[0x00] = role_inde[0x00];
        ++user_role;
        ++role_inde;
        ++posi;
    }
    //
    memset(user_role, '\0', sizeof (role_privi *));
}

int dele_role_cache(user_privi *uepriv, role_privi *ropriv) {
    OSEVPF("[FUNC]:dele_role_cache\n");
    role_privi **user_role = uepriv->ropriv;
    unsigned int inde = 0x00;
    for (; (MAX_ROLE_SIZE > inde) && user_role[0x00]; ++inde, ++user_role) {
        if (ropriv == user_role[0x00]) {
            // user_role[0x00] = INVA_POIN_VALU;
            redu_role_poin(user_role, inde);
            return 0x00;
        }
    }
    //
    return -1;
}

static void redu_role_obid(osv_oid_t *role_obid, int posi) {
    osv_oid_t *role_inde = role_obid + 0x01;
    ++posi;
    while ((MAX_ROLE_SIZE > posi) && CHK_ZERO_OBID(role_obid)) {
        OBID_BINARY_COPY(role_obid, role_inde);
        ++role_obid;
        ++role_inde;
        ++posi;
    }
    // memset(role_obid, '\0', sizeof (osv_oid_t));
    MAKE_ZERO_OBID(role_obid)
}

int dele_role_data(base_valu *admbv, char *contn, osv_oid_t *user_obid, role_privi *ropriv) {
    OSEVPF("[FUNC]:dele_role_data\n");
    user_privi user_memo;
    loop_memo_t user_dat;
    minit_dest(&user_dat, &user_memo, sizeof (user_privi));
    if (loop_load(&user_dat, admbv, contn, user_obid)) {
        free_dest(&user_dat);
        return -1;
    }
    //
    osv_oid_t *role_obid = user_memo.role_obid;
    unsigned int inde = 0x00;
    for (; (MAX_ROLE_SIZE > inde) && CHK_ZERO_OBID(role_obid); ++inde, ++role_obid) {
        if (STOID_EQUALI(&ropriv->role_obid, role_obid)) {
            redu_role_obid(role_obid, inde);
            //
            if (loop_save(admbv, contn, &user_dat, user_obid)) {
                free_dest(&user_dat);
                return -1;
            }
            free_dest(&user_dat);
            return 0x00;
        }
    }
    //   
    free_dest(&user_dat);
    return -1;
}

//

int bins_priv_cache(role_privi *ropriv, dist_privi *priv_dist, uint32 lvmsk_code) {
    OSEVPF("[FUNC]:bins_priv_cache\n");
    dist_privi *priv_poin = ropriv->priv_array;
    unsigned int inde = 0x00;
    for (; MAX_PRIVI_SIZE > inde; ++inde, ++priv_poin) {
        if (PRIVI_SCOPE(priv_dist->privile_code & priv_poin->privile_code) && OBID_EQUALI(&priv_dist->dist_obid, &priv_poin->dist_obid)) {
            priv_poin->privile_code |= ((PRIVI_SCOPE_CODE | lvmsk_code) & priv_dist->privile_code);
            return 0x00;
        } else if (DIST_PRIVI_IS_ZERO(priv_poin)) {
            OBID_BINARY_COPY(&priv_poin->dist_obid, &priv_dist->dist_obid)
            priv_poin->privile_code = ((PRIVI_SCOPE_CODE | lvmsk_code) & priv_dist->privile_code);
            return 0x00;
        }
    }
    //
    return -1;
}

int oins_priv_cache(role_privi *ropriv, dist_privi *priv_dist) {
    OSEVPF("[FUNC]:oins_priv_cache\n");
    dist_privi *priv_poin = ropriv->priv_array;
    unsigned int inde = 0x00;
    for (; MAX_PRIVI_SIZE > inde; ++inde, ++priv_poin) {
        if (OBID_EQUALI(&priv_dist->dist_obid, &priv_poin->dist_obid)) {
            priv_poin->privile_code |= priv_dist->privile_code;
            return 0x00;
        } else if (DIST_PRIVI_IS_ZERO(priv_poin)) {
            OBID_BINARY_COPY(&priv_poin->dist_obid, &priv_dist->dist_obid)
            priv_poin->privile_code = priv_dist->privile_code;
            return 0x00;
        }
    }
    //
    return -1;
}

int bins_priv_data(base_valu *admbv, char *contn, osv_oid_t *role_obid, dist_privi *priv_dist) {
    OSEVPF("[FUNC]:bins_priv_data\n");
    role_privi role_memo;
    loop_memo_t role_dat;
    minit_dest(&role_dat, &role_memo, sizeof (role_privi));
    if (loop_load(&role_dat, admbv, contn, role_obid)) {
        free_dest(&role_dat);
        return -1;
    }
    //
    dist_privi *priv_poin = role_memo.priv_array;
    unsigned int inde = 0x00;
    for (; MAX_PRIVI_SIZE > inde; ++inde, ++priv_poin) {
        if (PRIVI_SCOPE(priv_dist->privile_code & priv_poin->privile_code) && OBID_EQUALI(&priv_dist->dist_obid, &priv_poin->dist_obid)) {
            priv_poin->privile_code |= priv_dist->privile_code;
            if (loop_save(admbv, contn, &role_dat, role_obid)) {
                free_dest(&role_dat);
                return -1;
            }
            free_dest(&role_dat);
            return 0x00;
        } else if (DIST_PRIVI_IS_ZERO(priv_poin)) {
            OBID_BINARY_COPY(&priv_poin->dist_obid, &priv_dist->dist_obid)
            priv_poin->privile_code = priv_dist->privile_code;
            if (loop_save(admbv, contn, &role_dat, role_obid)) {
                free_dest(&role_dat);
                return -1;
            }
            free_dest(&role_dat);
            return 0x00;
        }
    }
    //
    free_dest(&role_dat);
    return -1;
}

//

int oins_priv_data(base_valu *admbv, char *contn, osv_oid_t *role_obid, dist_privi *priv_dist) {
    OSEVPF("[FUNC]:oins_priv_data\n");
    role_privi role_memo;
    loop_memo_t role_dat;
    minit_dest(&role_dat, &role_memo, sizeof (role_privi));
    if (loop_load(&role_dat, admbv, contn, role_obid)) {
        free_dest(&role_dat);
        return -1;
    }
    //
    dist_privi *priv_poin = role_memo.priv_array;
    unsigned int inde = 0x00;
    for (; MAX_PRIVI_SIZE > inde; ++inde, ++priv_poin) {
        if (OBID_EQUALI(&priv_dist->dist_obid, &priv_poin->dist_obid)) {
            OSEVPF("OBID_EQUALI\n");
            priv_poin->privile_code |= priv_dist->privile_code;
            if (loop_save(admbv, contn, &role_dat, role_obid)) {
                free_dest(&role_dat);
                return -1;
            }
            free_dest(&role_dat);
            return 0x00;
        } else if (DIST_PRIVI_IS_ZERO(priv_poin)) {
            OSEVPF("DIST_PRIVI_IS_ZERO\n");
            OBID_BINARY_COPY(&priv_poin->dist_obid, &priv_dist->dist_obid)
            priv_poin->privile_code = priv_dist->privile_code;
            if (loop_save(admbv, contn, &role_dat, role_obid)) {
                free_dest(&role_dat);
                return -1;
            }
            OSEVPF("1 xxxxxxxxxxxxxxxxx\n");
            free_dest(&role_dat);
            return 0x00;
        }
    }
    //
    OSEVPF("2 xxxxxxxxxxxxxxxxx\n");
    free_dest(&role_dat);
    OSEVPF("end oins_priv_data\n");
    return 0x00;
}

//

static void redu_priv_data(dist_privi *priv_poin, int posi) {
    OSEVPF("[FUNC]:redu_priv_data\n");
    dist_privi *priv_inde = priv_poin + 0x01;
    ++posi;
    while ((MAX_PRIVI_SIZE > posi) && DIST_PRIVI_NOT_ZERO(priv_inde)) {
        PRIV_BINCPY(priv_poin, priv_inde)
                ++priv_poin;
        ++priv_inde;
        ++posi;
    }
    //
    MAKE_PRIV_ZERO(priv_poin)
}

int bdel_priv_cache(role_privi *ropriv, dist_privi *priv_dist, uint32 lvmsk_code) {
    OSEVPF("[FUNC]:bdel_priv_cache\n");
    // OSEVPF("priv_dist->privile_code:|%08x| lvmsk_code:|%08x|\n", priv_dist->privile_code, lvmsk_code);
    dist_privi *priv_poin = ropriv->priv_array;
    unsigned int inde = 0x00;
    for (; (MAX_PRIVI_SIZE > inde) && DIST_PRIVI_NOT_ZERO(priv_poin); ++inde, ++priv_poin) {
        if (PRIVI_SCOPE(priv_dist->privile_code & priv_poin->privile_code) && STOID_EQUALI(&priv_dist->dist_obid, &priv_poin->dist_obid)) {
            // OSEVPF("priv_poin->privile_code:|%08x|\n", priv_poin->privile_code);
            priv_poin->privile_code &= (PRIVI_SCOPE_CODE | ~(lvmsk_code & priv_dist->privile_code));
            // OSEVPF("priv_poin->privile_code:|%08x|\n", priv_poin->privile_code);
            if (!PRIVI_VALUE(priv_poin->privile_code))
                redu_priv_data(priv_poin, inde);
            return 0x00;
        }
    }
    // OSEVPF("end bdel_priv_cache\n");
    return -1;
}

int cdel_priv_cache(role_privi *ropriv, osv_oid_t *cont_obid) {
    OSEVPF("[FUNC]:cdel_priv_cache\n");
    dist_privi *priv_poin = ropriv->priv_array;
    unsigned int inde = 0x00;
    for (; (MAX_PRIVI_SIZE > inde) && DIST_PRIVI_NOT_ZERO(priv_poin); ++inde, ++priv_poin) {
        if (STOID_EQUALI(cont_obid, &priv_poin->dist_obid)) {
            redu_priv_data(priv_poin, inde);
            return 0x00;
        }
    }
    // OSEVPF("end cdel_priv_cache\n");
    return -1;
}

int ddel_priv_cache(role_privi *ropriv, osv_oid_t *base_obid) {
    OSEVPF("[FUNC]:ddel_priv_cache\n");
    dist_privi *priv_poin = ropriv->priv_array;
    unsigned int inde = 0x00;
    for (; (MAX_PRIVI_SIZE > inde) && DIST_PRIVI_NOT_ZERO(priv_poin); ++inde, ++priv_poin) {
        if (STOID_EQUALI(base_obid, &priv_poin->dist_obid)) {
            redu_priv_data(priv_poin, inde);
            return 0x00;
        }
    }
    // OSEVPF("end cdel_priv_cache\n");
    return -1;
}

int odel_priv_cache(role_privi *ropriv, dist_privi *priv_dist) {
    OSEVPF("[FUNC]:odel_priv_cache\n");
    dist_privi *priv_poin = ropriv->priv_array;
    unsigned int inde = 0x00;
    for (; (MAX_PRIVI_SIZE > inde) && DIST_PRIVI_NOT_ZERO(priv_poin); ++inde, ++priv_poin) {
        if (STOID_EQUALI(&priv_dist->dist_obid, &priv_poin->dist_obid)) {
            priv_poin->privile_code &= (PRIVI_SCOPE_CODE | ~priv_dist->privile_code);
            if (!PRIVI_VALUE(priv_poin->privile_code))
                redu_priv_data(priv_poin, inde);
            return 0x00;
        }
    }
    // OSEVPF("end odel_priv_cache\n");
    return -1;
}

//

int bdel_priv_data(base_valu *admbv, char *contn, osv_oid_t *role_obid, dist_privi *priv_dist) {
    OSEVPF("[FUNC]:bdel_priv_data\n");
    role_privi role_memo;
    loop_memo_t role_dat;
    minit_dest(&role_dat, &role_memo, sizeof (role_privi));
    if (loop_load(&role_dat, admbv, contn, role_obid)) {
        free_dest(&role_dat);
        return -1;
    }
    //
    dist_privi * priv_poin = role_memo.priv_array;
    unsigned int inde = 0x00;
    for (; (MAX_PRIVI_SIZE > inde) && DIST_PRIVI_NOT_ZERO(priv_poin); ++inde, ++priv_poin) {
        if (PRIVI_SCOPE(priv_dist->privile_code & priv_poin->privile_code) && STOID_EQUALI(&priv_dist->dist_obid, &priv_poin->dist_obid)) {
            priv_poin->privile_code &= (PRIVI_SCOPE_CODE | ~priv_dist->privile_code);
            PRIN_dist_privi(priv_poin);
            if (!PRIVI_VALUE(priv_poin->privile_code))
                redu_priv_data(priv_poin, inde);
            //
            if (loop_save(admbv, contn, &role_dat, role_obid)) {
                free_dest(&role_dat);
                return -1;
            }
            free_dest(&role_dat);
            return 0x00;
        }
    }
    // OSEVPF("end bdel_priv_data\n");
    free_dest(&role_dat);
    return -1;
}

int cdel_priv_data(base_valu *admbv, char *contn, osv_oid_t *role_obid, osv_oid_t *cont_obid) {
    OSEVPF("[FUNC]:cdel_priv_data\n");
    role_privi role_memo;
    loop_memo_t role_dat;
    minit_dest(&role_dat, &role_memo, sizeof (role_privi));
    if (loop_load(&role_dat, admbv, contn, role_obid)) {
        free_dest(&role_dat);
        return -1;
    }
    //
    dist_privi * priv_poin = role_memo.priv_array;
    unsigned int inde = 0x00;
    for (; (MAX_PRIVI_SIZE > inde) && DIST_PRIVI_NOT_ZERO(priv_poin); ++inde, ++priv_poin) {
        if (STOID_EQUALI(cont_obid, &priv_poin->dist_obid)) {
            redu_priv_data(priv_poin, inde);
            if (loop_save(admbv, contn, &role_dat, role_obid)) {
                free_dest(&role_dat);
                return -1;
            }
            free_dest(&role_dat);
            return 0x00;
        }
    }
    // OSEVPF("end bdel_priv_data\n");
    free_dest(&role_dat);
    return -1;
}

int ddel_priv_data(base_valu *admbv, char *contn, osv_oid_t *role_obid, osv_oid_t *base_obid) {
    OSEVPF("[FUNC]:ddel_priv_data\n");
    role_privi role_memo;
    loop_memo_t role_dat;
    minit_dest(&role_dat, &role_memo, sizeof (role_privi));
    if (loop_load(&role_dat, admbv, contn, role_obid)) {
        free_dest(&role_dat);
        return -1;
    }
    //
    dist_privi * priv_poin = role_memo.priv_array;
    unsigned int inde = 0x00;
    for (; (MAX_PRIVI_SIZE > inde) && DIST_PRIVI_NOT_ZERO(priv_poin); ++inde, ++priv_poin) {
        if (STOID_EQUALI(base_obid, &priv_poin->dist_obid)) {
            redu_priv_data(priv_poin, inde);
            if (loop_save(admbv, contn, &role_dat, role_obid)) {
                free_dest(&role_dat);
                return -1;
            }
            free_dest(&role_dat);
            return 0x00;
        }
    }
    // OSEVPF("end bdel_priv_data\n");
    free_dest(&role_dat);
    return -1;
}

//

int odel_priv_data(base_valu *admbv, char *contn, osv_oid_t *role_obid, dist_privi *priv_dist) {
    OSEVPF("[FUNC]:odel_priv_data\n");
    role_privi role_memo;
    loop_memo_t role_dat;
    minit_dest(&role_dat, &role_memo, sizeof (role_privi));
    if (loop_load(&role_dat, admbv, contn, role_obid)) {
        free_dest(&role_dat);
        return -1;
    }
    //
    dist_privi * priv_poin = role_memo.priv_array;
    unsigned int inde = 0x00;
    for (; (MAX_PRIVI_SIZE > inde) && DIST_PRIVI_NOT_ZERO(priv_poin); ++inde, ++priv_poin) {
        if (STOID_EQUALI(&priv_dist->dist_obid, &priv_poin->dist_obid)) {
            priv_poin->privile_code &= (PRIVI_SCOPE_CODE | ~priv_dist->privile_code);
            if (!PRIVI_VALUE(priv_poin->privile_code))
                redu_priv_data(priv_poin, inde);
            //
            if (loop_save(admbv, contn, &role_dat, role_obid)) {
                free_dest(&role_dat);
                return -1;
            }
            free_dest(&role_dat);
            return 0x00;
        }
    }
    //OSEVPF("end odel_priv_data\n");
    free_dest(&role_dat);
    return -1;
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_header.h"

#include "astri_utili.h"
#include "seion_struct.h"
#include "cache_utili.h"
#include "privi_code.h"
#include "basev_bzl.h"
#include "live_utili.h"
#include "privile_obje.h"
#include "baseda_cache.h"

#include "privi_utili.h"
#include "liv_list.h"
#include "debug_funct_cp.h"

//

static void comp_role_list(liv_list *role_list) {
    OSEVPF("[FUNC]:comp_role_list\n");
#ifdef _DEBUG
    char strTemp[1024];
    char *last_str = lscpy(strTemp, "comp_role_list\n");
#endif
    unsigned int inde;
    liv_list * rlist = role_list;
    for (; rlist; rlist = rlist->next) {
#ifdef _DEBUG
        last_str = PRIN_echo_role_privi(last_str, (role_privi *) rlist->liv_data);
#endif
        dist_privi *priv_poin = ((role_privi *) rlist->liv_data)->priv_array;
        inde = 0x00;
        for (; (MAX_PRIVI_SIZE > inde) && DIST_PRIVI_NOT_ZERO(priv_poin); ++inde, ++priv_poin) {
            // last_str = PRIN_echo_dist_privi(last_str, priv_poin);
            FILL_UNIQUE_OBID(&priv_poin->dist_obid);
#ifdef _DEBUG
            last_str = PRIN_echo_dist_privi(last_str, priv_poin);
#endif
        }
    }
#ifdef _DEBUG
    OSEVPF("%s\n", strTemp);
#endif
}

//

int load_privi_data(usep_lsmp *usep_ca, base_valu *admbv) {
    OSEVPF("[FUNC]:load_privi_data\n");
    if (load_privi_list(usep_ca, admbv))
        return -1;
    comp_role_list(usep_ca->role_list);
    //
    if (creat_ouser_cache(usep_ca->osev_user_hm, usep_ca->role_list, usep_ca->ouse_list))
        return -1;
    if (creat_buser_cache(usep_ca->base_user_hm, usep_ca->role_list, usep_ca->buse_list))
        return -1;
    //
    return 0x00;
}

// 0x01:exists 0x00:not exists

role_privi *find_osev_role(liv_list *role_list, char *role_name) {
    role_privi *ropriv;
    liv_list *rlist = role_list;
    for (; rlist; rlist = rlist->next) {
        ropriv = (role_privi *) rlist->liv_data;
        if ((ROLE_TYPE_OSEV == ropriv->role_type) && !strcmp(role_name, ropriv->role_name))
            return ropriv;
    }
    //
    return NULL;
}

// 0x00;unused 0x01:used

int osev_role_used(liv_list *ouse_list, char *role_name) {
    role_privi **ropriv;
    liv_list *ulist = ouse_list;
    int role_inde;
    for (; ulist; ulist = ulist->next) {
        ropriv = ((user_privi *) ulist->liv_data)->ropriv;
        role_inde = 0x00;
        for (; (MAX_ROLE_SIZE > role_inde) && ropriv[0x00]; ++role_inde, ++ropriv) {
            OSEVPF("ropriv->role_type:|%d|, ropriv->role_name:|%s|\n", ropriv[0x00]->role_type, ropriv[0x00]->role_name);
            if ((ROLE_TYPE_OSEV == ropriv[0x00]->role_type) && !strcmp(role_name, ropriv[0x00]->role_name))
                return 0x01;
        }
    }
    //
    return 0x00;
}

//

role_privi *find_base_role(liv_list *role_list, char *role_name) {
    role_privi *ropriv;
    liv_list *rlist = role_list;
    for (; rlist; rlist = rlist->next) {
        ropriv = (role_privi *) rlist->liv_data;
        if ((ROLE_TYPE_BASE == ropriv->role_type) && !strcmp(role_name, ropriv->role_name))
            return ropriv;
    }
    //
    return NULL;
}

int base_role_used(liv_list *buse_list, char *role_name) {
    role_privi **ropriv;
    liv_list *ulist = buse_list;
    int role_inde;
    for (; ulist; ulist = ulist->next) {
        ropriv = ((user_privi *) ulist->liv_data)->ropriv;
        role_inde = 0x00;
        for (; (MAX_ROLE_SIZE > role_inde) && ropriv[0x00]; ++role_inde, ++ropriv) {
            OSEVPF("ropriv->role_type:|%d|, ropriv->role_name:|%s|\n", ropriv[0x00]->role_type, ropriv[0x00]->role_name);
            if ((ROLE_TYPE_BASE == ropriv[0x00]->role_type) && !strcmp(role_name, ropriv[0x00]->role_name))
                return 0x01;
        }
    }
    //
    return 0x00;
}


//

user_privi *find_user_privi(liv_list *user_list, char *user_name) {
    liv_list *ulist = user_list;
    for (; ulist; ulist = ulist->next) {
        if (!strcmp(user_name, ((user_privi *) ulist->liv_data)->user_name))
            return (user_privi *) ulist->liv_data;
    }
    //
    return NULL;
}

//

int check_privi_obid(role_privi *ropriv, osv_oid_t *base_obid, cachemap *baval_ca) {
    OSEVPF("[FUNC]:check_privi_obid\n");
    if (ROLE_TYPE_OSEV == ropriv->role_type)
        return -1;
    //
    dist_privi *priv_poin = ropriv->priv_array;
    unsigned int inde = 0x00;
    for (; (MAX_PRIVI_SIZE > inde) && DIST_PRIVI_NOT_ZERO(priv_poin); ++inde, ++priv_poin) {
        if (SCOP_BASE & priv_poin->privile_code) {
            if (OBID_EQUALI(base_obid, &priv_poin->dist_obid)) {
#ifdef _DEBUG
                char obid_stri[OBJE_IDENTI_ZLEN];
                OSEVPF("SCOP_BASE found obid:|%s|\n", oidstr(obid_stri, &ropriv->role_obid));
#endif
                return 0x00;
            }
        } else if (SCOP_CONT & priv_poin->privile_code) {
            base_valu *baval = find_baval_bcoid(&priv_poin->dist_obid, baval_ca);
            if (!baval) {
                char coid_stri[OBJE_IDENTI_ZLEN];
                _LOG_WARN("Privile not found contain:|%s|", oidstr(coid_stri, &priv_poin->dist_obid));
                continue;
            }
            if (OBID_EQUALI(base_obid, &baval->base_obid)) {
#ifdef _DEBUG
                char obid_stri[OBJE_IDENTI_ZLEN];
                OSEVPF("SCOP_CONT found obid:|%s|\n", oidstr(obid_stri, &ropriv->role_obid));
#endif
                return 0x00;
            }
        }
    }
    //
    OSEVPF("end check_privi_obid\n");
    return -1;
}

//

static uint32 meth_privi_code(uint32 priv_code, uint32 lvmsk_code) {
    uint32 resul_code = INVA_PRIVI;
    // level three
    if ((ENTP_POST & priv_code) && (BLVH_WRITE & lvmsk_code))
        resul_code |= ENTP_POST;
    if ((ENTP_STATU & priv_code) && (BLVH_READ & lvmsk_code))
        resul_code |= ENTP_STATU;
    if ((ENTP_CREAT & priv_code) && (BLVH_WRITE & lvmsk_code))
        resul_code |= ENTP_CREAT;
    if ((ENTP_DROP & priv_code) && (BLVH_WRITE & lvmsk_code))
        resul_code |= ENTP_DROP;
    if ((ENTP_UPDAT & priv_code) && (BLVH_WRITE & lvmsk_code))
        resul_code |= ENTP_UPDAT;
    if ((ENTP_INSER & priv_code) && (BLVH_WRITE & lvmsk_code))
        resul_code |= ENTP_INSER;
    if ((ENTP_SEARO & priv_code) && (BLVH_READ & lvmsk_code))
        resul_code |= ENTP_SEARO;
    if ((ENTP_INVOK & priv_code) && (BLVH_EXECU & lvmsk_code))
        resul_code |= ENTP_INVOK;
    // level foup
    if ((QUEP_POST & priv_code) && (BLVF_WRITE & lvmsk_code))
        resul_code |= QUEP_POST;
    if ((QUEP_STATU & priv_code) && (BLVF_READ & lvmsk_code))
        resul_code |= QUEP_STATU;
    if ((QUEP_CREAT & priv_code) && (BLVF_WRITE & lvmsk_code))
        resul_code |= QUEP_CREAT;
    if ((QUEP_DROP & priv_code) && (BLVF_WRITE & lvmsk_code))
        resul_code |= QUEP_DROP;
    if ((QUEP_UPDAT & priv_code) && (BLVF_WRITE & lvmsk_code))
        resul_code |= QUEP_UPDAT;
    if ((QUEP_INSER & priv_code) && (BLVF_WRITE & lvmsk_code))
        resul_code |= QUEP_INSER;
    if ((QUEP_SEARQ & priv_code) && ((BLVF_READ | BLVF_WRITE) & lvmsk_code))
        resul_code |= QUEP_SEARQ;
    if ((QUEP_INVOK & priv_code) && (BLVF_EXECU & lvmsk_code))
        resul_code |= QUEP_INVOK;
    if ((QUEP_FACTO & priv_code) && ((BLVF_READ | BLVF_WRITE) & lvmsk_code))
        resul_code |= QUEP_FACTO;
    //
    return PRIVI_SCOPE(priv_code) | resul_code;
}

// PRIV_BINCPY(PRI1, PRI2)

int reset_privile_code(role_privi *ropriv, role_privi *sto_ropri, osv_oid_t *base_obid, uint32 lvmsk_code, cachemap *baval_ca) {
    OSEVPF("[FUNC]:reset_privile_code\n");
    OSEVPF("lvmsk_code:|%08x|\n", lvmsk_code);
    dist_privi *priv_poin = ropriv->priv_array;
    dist_privi *stor_poin = sto_ropri->priv_array;
    unsigned int inde = 0x00;
    for (; (MAX_PRIVI_SIZE > inde) && DIST_PRIVI_NOT_ZERO(priv_poin); ++inde, ++priv_poin, ++stor_poin) {
        FILL_UNIQUE_OBID(&stor_poin->dist_obid);
        if (!OBID_EQUALI(&priv_poin->dist_obid, &stor_poin->dist_obid))
            continue;
        //
        if (SCOP_BASE & priv_poin->privile_code) {
            if (OBID_EQUALI(base_obid, &priv_poin->dist_obid)) {
                OSEVPF("b SCOP_BASE priv_poin->privile_code:|%08x|\n", priv_poin->privile_code);
                priv_poin->privile_code = (PRIVI_SCOPE_CODE | lvmsk_code) & stor_poin->privile_code;
                OSEVPF("a priv_poin->privile_code:|%08x|\n", priv_poin->privile_code);
            }
        } else if (SCOP_CONT & priv_poin->privile_code) {
            base_valu *baval = find_baval_bcoid(&priv_poin->dist_obid, baval_ca);
            if (!baval) {
                char coid_stri[OBJE_IDENTI_ZLEN];
                _LOG_WARN("Privile not found contain:|%s|", oidstr(coid_stri, &priv_poin->dist_obid));
                continue;
            }
            if (OBID_EQUALI(base_obid, &baval->base_obid)) {
                OSEVPF("b SCOP_CONT priv_poin->privile_code:|%08x|\n", priv_poin->privile_code);
                priv_poin->privile_code = meth_privi_code(stor_poin->privile_code, lvmsk_code);
                OSEVPF("a priv_poin->privile_code:|%08x|\n", priv_poin->privile_code);
            }
        }
    }
    //
    OSEVPF("end reset_privile_code\n");
    return 0x00;
}

//

int opriv_dist_lvoid(osv_oid_t *dist_obid, uint32 priv_code) {
    OSEVPF("[FUNC]:opriv_dist_lvoid\n");
    if (SCOP_OSEV & priv_code) {
        gener_osev_obid(dist_obid);
    } else if ((SCOP_BASE | SCOP_CONT) & priv_code)
        return -1;
    //
    return 0x00;
}

//

int bpriv_dist_lvoid(osv_oid_t *dist_obid, uint32 *lvmsk_code, char *dist_iden, uint32 priv_code) {
    OSEVPF("[FUNC]:bpriv_dist_lvoid\n");
    char basen[BASE_LENGTH];
    char conta[OBJN_LENGTH];
    //
    if (SCOP_BASE & priv_code) {
        base_valu *baval = FIND_BADATN_BZL(dist_iden);
        if (!baval) return -1;
        OBID_BINARY_COPY(dist_obid, &baval->base_obid)
        lvmsk_code[0x00] = baval->lvmsk_code;
    } else if (SCOP_CONT & priv_code) {
        if (split_conta(basen, conta, dist_iden))
            return -1;
        OSEVPF("basen:|%s| conta:|%s| dist_iden:|%s|\n", basen, conta, dist_iden);
        base_valu *baval = FIND_BADATN_BZL(basen);
        if (!baval) return -1;
        lvmsk_code[0x00] = baval->lvmsk_code;
        contain *contp = (contain *) cache_value(conta, baval->conda_stm.lev3n_hm);
        if (!contp) {
            if (strcmp(BASE_DEFAULT_VALUE, conta))
                return -1;
            OBID_BINARY_COPY(dist_obid, &baval->base_obid)
        } else OBID_BINARY_COPY(dist_obid, &contp->cont_obid);
    } else if (SCOP_OSEV & priv_code) return -1;
    //
    return 0x00;
}

int bpriv_dist_obid(osv_oid_t *dist_obid, char *dist_iden, uint32 priv_code) {
    OSEVPF("[FUNC]:bpriv_dist_obid\n");
    char basen[BASE_LENGTH];
    char conta[OBJN_LENGTH];
    //
    if (SCOP_BASE & priv_code) {
        base_valu *baval = FIND_BADATN_BZL(dist_iden);
        if (!baval) return -1;
        OBID_BINARY_COPY(dist_obid, &baval->base_obid)
    } else if (SCOP_CONT & priv_code) {
        if (split_conta(basen, conta, dist_iden))
            return -1;
        base_valu *baval = FIND_BADATN_BZL(basen);
        if (!baval) return -1;
        contain *contp = (contain *) cache_value(conta, baval->conda_stm.lev3n_hm);
        if (!contp) return -1;
        OBID_BINARY_COPY(dist_obid, &contp->cont_obid)
    } else if (SCOP_OSEV & priv_code) return -1;
    //
    return 0x00;
}


// 0x00:exists -1:error / not found

int osev_role_exis(user_privi *uepriv, role_privi * ropriv) {
    OSEVPF("[FUNC]:osev_role_exis\n");
    if (ROLE_TYPE_OSEV != ropriv->role_type)
        return -1;
    //
    role_privi **user_role = uepriv->ropriv;
    unsigned int inde = 0x00;
    for (; (MAX_ROLE_SIZE > inde) && user_role[0x00]; ++inde, ++user_role) {
        if (ropriv == user_role[0x00])
            return 0x00;
    }
    //
    return -1;
}

// 0x00:exists -1:error / not found

int base_role_exis(user_privi *uepriv, role_privi * ropriv) {
    OSEVPF("[FUNC]:base_role_exis\n");
    if (ROLE_TYPE_BASE != ropriv->role_type)
        return -1;
    //
    role_privi **user_role = uepriv->ropriv;
    unsigned int inde = 0x00;
    for (; (MAX_ROLE_SIZE > inde) && user_role[0x00]; ++inde, ++user_role) {
        if (ropriv == user_role[0x00])
            return 0x00;
    }
    //
    return -1;
}

//

int orole_privi_exist(char *contn, osv_oid_t *role_obid, dist_privi * priv_dist) {
    OSEVPF("[FUNC]:orole_privi_exist\n");
    if (!(SCOP_OSEV & priv_dist->privile_code) || ((SCOP_BASE | SCOP_CONT) & priv_dist->privile_code))
        return -1;
    //
    role_privi role_memo;
    valu_memo_t role_dat;
    base_valu *admbv = FIND_BADATN_BZL(OSEV_ADMINIS_VALUE);
    if (!admbv) return -1;
    MINIT_VALU(&role_dat, &role_memo, sizeof (role_privi));
    if (live_load(&role_dat, admbv, contn, role_obid))
        return -1;
    //
    dist_privi *priv_poin = role_memo.priv_array;
    unsigned int inde = 0x00;
    for (; (MAX_PRIVI_SIZE > inde) && DIST_PRIVI_NOT_ZERO(priv_poin); ++inde, ++priv_poin) {
        FILL_UNIQUE_OBID(&priv_poin->dist_obid);
        if (OBID_EQUALI(&priv_dist->dist_obid, &priv_poin->dist_obid)) {
            if (PRIVI_VALUE(priv_dist->privile_code & priv_poin->privile_code))
                return -1;
        }
    }
    //
    return 0x00;
}

int brole_privi_exist(char *contn, osv_oid_t *role_obid, dist_privi * priv_dist) {
    OSEVPF("[FUNC]:brole_privi_exist\n");
    if (!((SCOP_BASE | SCOP_CONT) & priv_dist->privile_code) || (SCOP_OSEV & priv_dist->privile_code))
        return -1;
    //
    role_privi role_memo;
    valu_memo_t role_dat;
    base_valu *admbv = FIND_BADATN_BZL(OSEV_ADMINIS_VALUE);
    if (!admbv) return -1;
    MINIT_VALU(&role_dat, &role_memo, sizeof (role_privi));
    if (live_load(&role_dat, admbv, contn, role_obid))
        return -1;
    //
    dist_privi * priv_poin = role_memo.priv_array;
    unsigned int inde = 0x00;
    if (SCOP_BASE & priv_dist->privile_code) {
        for (; (MAX_PRIVI_SIZE > inde) && DIST_PRIVI_NOT_ZERO(priv_poin); ++inde, ++priv_poin) {
            FILL_UNIQUE_OBID(&priv_poin->dist_obid);
            if ((SCOP_BASE & priv_poin->privile_code) && OBID_EQUALI(&priv_dist->dist_obid, &priv_poin->dist_obid)) {
                if (PRIVI_VALUE(priv_dist->privile_code & priv_poin->privile_code))
                    return -1;
            }
        }
    } else if (SCOP_CONT & priv_dist->privile_code) {
        for (; (MAX_PRIVI_SIZE > inde) && DIST_PRIVI_NOT_ZERO(priv_poin); ++inde, ++priv_poin) {
            FILL_UNIQUE_OBID(&priv_poin->dist_obid);
            if ((SCOP_CONT & priv_poin->privile_code) && OBID_EQUALI(&priv_dist->dist_obid, &priv_poin->dist_obid)) {
                if (PRIVI_VALUE(priv_dist->privile_code & priv_poin->privile_code))
                    return -1;
            }
        }
    }
    //
    return 0x00;
}

//

role_privi * find_role_data(role_privi *role_memo, osv_oid_t * role_obid) {
    // OSEVPF("[FUNC]:find_role_data\n");
    base_valu *admbv = FIND_BADATN_BZL(OSEV_ADMINIS_VALUE);
    if (!admbv) return NULL;
    valu_memo_t role_dat;
    MINIT_VALU(&role_dat, role_memo, sizeof (role_privi));
    if (live_load(&role_dat, admbv, AUTH_ROLES_CONT, role_obid))
        return NULL;
    // OSEVPF("end find_role_data\n");
    return role_memo;
}

//

static int initi_privi_value(liv_list *role_list, base_valu *admbv, base_valu *base_valu, cachemap *baval_ca) {
    OSEVPF("[FUNC]:initi_privi_value\n");
    role_privi role_memo;
    valu_memo_t role_dat;
    MINIT_VALU(&role_dat, &role_memo, sizeof (role_privi));
    liv_list *rlist = role_list;
    for (; rlist; rlist = rlist->next) {
        if (!check_privi_obid((role_privi *) rlist->liv_data, &base_valu->base_obid, baval_ca)) {
            if (live_load(&role_dat, admbv, AUTH_ROLES_CONT, &((role_privi *) rlist->liv_data)->role_obid))
                return -1;
            if (reset_privile_code((role_privi *) rlist->liv_data, &role_memo, &base_valu->base_obid, base_valu->lvmsk_code, baval_ca))
                return -1;
            // memcpy(rlist->liv_data, &role_dat, sizeof (role_privi));
        }
    }
    //
    return 0x00;
}

int initi_privile_level(liv_list *role_list, base_valu * admbv) {
    OSEVPF("[FUNC]:initi_privile_level\n");
    cachemap *baval_ca = initi_baval_cache();
    if (!baval_ca) return -1;
    //
    basv_list *blsnd = GET_BLIST_BZL();
    for (; blsnd; blsnd = blsnd->next) {
        if (strcmp(OSEV_ADMINIS_VALUE, blsnd->_base_)) {
            if (initi_privi_value(role_list, admbv, &blsnd->basval, baval_ca)) {
                OSEVPF("ERROR: initi_privi_value\n");
                final_baval_cache(baval_ca);
                return -1;
            }
        }
    }
    //
    final_baval_cache(baval_ca);
    return 0x00;
}
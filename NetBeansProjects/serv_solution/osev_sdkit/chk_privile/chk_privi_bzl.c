
#include "commo_header.h"
#include "kcomm_header.h"

#include "basev_bzl.h"
#include "privile_bzl.h"
#include "privi_utili.h"
#include "chk_utili.h"

#include "chk_privi_bzl.h"
#include "liv_list.h"

//

int osau_privile_bzl(user_privi *uepriv, uint32 priv_code) {
    OSEVPF("[FUNC]:osau_privile_bzl\n");
    OSEVPF("priv_code:|%08X|\n", priv_code);
    if (!uepriv) return -1;
    dist_privi *priv_poin;
    role_privi **ropriv = uepriv->ropriv;
    //
    int role_inde = 0x00, priv_inde;
    for (; (MAX_ROLE_SIZE > role_inde) && ropriv[0x00]; ++role_inde, ++ropriv) {
        OSEVPF("ropriv->role_type:|%d|, ropriv->role_name:|%s|\n", ropriv[0x00]->role_type, ropriv[0x00]->role_name);
        priv_poin = ropriv[0x00]->priv_array;
        priv_inde = 0x00;
        for (; (MAX_PRIVI_SIZE > priv_inde) && DIST_PRIVI_NOT_ZERO(priv_poin); ++priv_inde, ++priv_poin) {
            OSEVPF("priv_poin->privile_code:|%08X|\n", priv_poin->privile_code);
            if (PRIVI_SCOPE(priv_code & priv_poin->privile_code))
                return 0x00;
        }
    }
    //
    OSEVPF("end osau_privile_bzl\n");
    return -1;
}

int bsau_privile_bzl(user_privi *uepriv, base_valu *baval, uint32 priv_code) {
    OSEVPF("[FUNC]:bsau_privile_bzl\n");
    OSEVPF("priv_code:|%08X|\n", priv_code);
    if (!uepriv) return -1;

    //
    dist_privi *priv_poin;
    role_privi **ropriv = uepriv->ropriv;
    //
    int role_inde = 0x00, priv_inde;
    for (; (MAX_ROLE_SIZE > role_inde) && ropriv[0x00]; ++role_inde, ++ropriv) {
        OSEVPF("ropriv->role_type:|%d|, ropriv->role_name:|%s|\n", ropriv[0x00]->role_type, ropriv[0x00]->role_name);
        priv_poin = ropriv[0x00]->priv_array;
        priv_inde = 0x00;
        for (; (MAX_PRIVI_SIZE > priv_inde) && DIST_PRIVI_NOT_ZERO(priv_poin); ++priv_inde, ++priv_poin) {
            OSEVPF("priv_poin->privile_code:|%08X|\n", priv_poin->privile_code);
            if ((SCOP_BASE & priv_poin->privile_code) && STOID_EQUALI(&baval->base_obid, &priv_poin->dist_obid)) {
                if (PRIVI_SCOPE(priv_code & priv_poin->privile_code))
                    return 0x00;
            } else if (SCOP_CONT & priv_poin->privile_code) {
                if (cache_value(&priv_poin->dist_obid, baval->conda_stm.lev3o_hm))
                    return 0x00;
                // :odb QCREA
                if ((QUEP_CREAT & priv_poin->privile_code) && STOID_EQUALI(&baval->base_obid, &priv_poin->dist_obid))
                    return 0x00;
            }
        }
    }
    //
    OSEVPF("end bsau_privile_bzl\n");
    return -1;
}

//

int osev_privile_bzl(user_privi *uepriv, uint32 priv_code) {
    OSEVPF("[FUNC]:osev_privile_bzl\n");
    if (!uepriv) return -1;
    OSEVPF("Need priv_code:|%08X|\n", priv_code);
    dist_privi *priv_poin;
    role_privi **ropriv = uepriv->ropriv;
    // OSEVPF("ropriv[0x00]:|%p|\n", ropriv[0x00]);
    //
    int role_inde = 0x00, priv_inde;
    for (; (MAX_ROLE_SIZE > role_inde) && ropriv[0x00]; ++role_inde, ++ropriv) {
        // OSEVPF("ropriv->role_type:|%d|, ropriv->role_name:|%s|\n", ropriv[0x00]->role_type, ropriv[0x00]->role_name);
        priv_poin = ropriv[0x00]->priv_array;
        priv_inde = 0x00;
        for (; (MAX_PRIVI_SIZE > priv_inde) && DIST_PRIVI_NOT_ZERO(priv_poin); ++priv_inde, ++priv_poin) {
            // OSEVPF("priv_poin->privile_code:|%08X|\n", priv_poin->privile_code);
            if (PRIVI_SCOPE(priv_code & priv_poin->privile_code) && PRIVI_VALUE(priv_code & priv_poin->privile_code))
                return 0x00;
        }
    }
    // OSEVPF("Not fonnd privile!\n");
    return -1;
}

//

int levci_privile_bzl(user_privi *uepriv, osv_oid_t *base_obid, uint32 priv_code) {
    OSEVPF("[FUNC]:levci_privile_bzl\n");
    OSEVPF("priv_code:|%08X|\n", priv_code);
    if (!uepriv) return -1;
    dist_privi * priv_poin;
    role_privi **ropriv = uepriv->ropriv;
    //
    int role_inde = 0x00, priv_inde;
    for (; (MAX_ROLE_SIZE > role_inde) && ropriv[0x00]; ++role_inde, ++ropriv) {
        priv_poin = ropriv[0x00]->priv_array;
        priv_inde = 0x00;
        for (; (MAX_PRIVI_SIZE > priv_inde) && DIST_PRIVI_NOT_ZERO(priv_poin); ++priv_inde, ++priv_poin) {
            if ((SCOP_BASE & priv_poin->privile_code) && STOID_EQUALI(base_obid, &priv_poin->dist_obid)) {
                if (PRIVI_VALUE(priv_code & priv_poin->privile_code))
                    return 0x00;
            }
        }
    }
    //
    return -1;
}

//

int levco_privile_bzl(user_privi *uepriv, osv_oid_t *base_obid, osv_oid_t *cont_obid, coqu_pvmk *priv_code) {
    OSEVPF("[FUNC]:levco_privile_bzl\n");
    OSEVPF("priv_code->blv_pmk:|%08X| priv_code->met_pmk:|%08X|\n", priv_code->blv_pmk, priv_code->met_pmk);
    if (!uepriv) return -1;
    dist_privi * priv_poin;
    role_privi **ropriv = uepriv->ropriv;
    //
    int role_inde = 0x00, priv_inde;
    for (; (MAX_ROLE_SIZE > role_inde) && ropriv[0x00]; ++role_inde, ++ropriv) {
        priv_poin = ropriv[0x00]->priv_array;
        priv_inde = 0x00;
        for (; (MAX_PRIVI_SIZE > priv_inde) && DIST_PRIVI_NOT_ZERO(priv_poin); ++priv_inde, ++priv_poin) {
            if ((SCOP_BASE & priv_poin->privile_code) && STOID_EQUALI(base_obid, &priv_poin->dist_obid)) {
                if (PRIVI_VALUE(priv_code->blv_pmk & priv_poin->privile_code))
                    return 0x00;
            } else if ((SCOP_CONT & priv_poin->privile_code) && STOID_EQUALI(cont_obid, &priv_poin->dist_obid)) {
                if (PRIVI_VALUE(priv_code->met_pmk & priv_poin->privile_code))
                    return 0x00;
            }
        }
    }
    //
    return -1;
}

//

int levqu_privile_bzl(user_privi *uepriv, osv_oid_t *base_obid, valid_cobid *vaoid, coqu_pvmk *priv_code) {
    OSEVPF("[FUNC]:levqu_privile_bzl\n");
    OSEVPF("priv_code->blv_pmk:|%08X| priv_code->met_pmk:|%08X|\n", priv_code->blv_pmk, priv_code->met_pmk);
    if (!uepriv) return -1;
    dist_privi * priv_poin;
    role_privi **ropriv = uepriv->ropriv;
    //
    int role_inde = 0x00, priv_inde;
    for (; (MAX_ROLE_SIZE > role_inde) && ropriv[0x00]; ++role_inde, ++ropriv) {
        priv_poin = ropriv[0x00]->priv_array;
        priv_inde = 0x00;
        for (; (MAX_PRIVI_SIZE > priv_inde) && DIST_PRIVI_NOT_ZERO(priv_poin); ++priv_inde, ++priv_poin) {
            if ((SCOP_BASE & priv_poin->privile_code) && STOID_EQUALI(base_obid, &priv_poin->dist_obid)) {
                if (priv_code->blv_pmk == PRIVI_VALUE(priv_code->blv_pmk & priv_poin->privile_code))
                    return 0x00;
            } else if (SCOP_CONT & priv_poin->privile_code) {
                osv_oid_t *vali_poin = vaoid->chk_obid;
                unsigned char *cont_code = vaoid->vali_code;
                while (cont_code[0x00]) {
                    if (STOID_EQUALI(vali_poin, &priv_poin->dist_obid)) {
                        if (PRIVI_VALUE(priv_code->met_pmk & priv_poin->privile_code))
                            cont_code[0x00] = 0x00;
                        break;
                    }
                    ++vali_poin;
                    ++cont_code;
                }
                if (!vaoid->vali_numb) return 0x00;
            }
        }
    }
    //
    return -1;
}

//
#define PPAM_ROLE_TYPE    0x00
#define PPAM_ROLE_NAME    0x01
#define PPAM_DIST_IDEN    0x02
#define OPPAM_PRIVILE     0x02
#define BPPAM_PRIVILE     0x03

// osev:privile:role(GRANT, "admin", ALL_PRIVILE);
// osev:privile:role(REVOKE, "admin", ALL_PRIVILE);

int orole_privile_bzl(respo_ctrl *resctl, user_privi *uepriv, pams_valu *pamvu) {
    OSEVPF("[FUNC]:orole_privile_bzl\n");
    if (!uepriv) return -1;
    // pamvu >= 2
    if (!pamvu->pamcon[0x00] || !pamvu->pamcon[0x01]) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    OSEVPF("PPAM_ROLE_TYPE:|%08X|\n", *((uint32 *) pamvu->pamcon[PPAM_ROLE_TYPE]));
    if ((GRANT_PRIV == *((uint32 *) pamvu->pamcon[PPAM_ROLE_TYPE]))
            || (REVOKE_PRIV == *((uint32 *) pamvu->pamcon[PPAM_ROLE_TYPE]))) {
        // pamvu = 3
        if (!pamvu->pamcon[0x02] || pamvu->pamcon[0x03]) {
            PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
            OSEVPF("PAMVU EXCEPITON!\n");
            return -1;
        }
        //
        uint32 priv_code = *((uint32 *) pamvu->pamcon[OPPAM_PRIVILE]);
        OSEVPF("priv_code:|%08X|\n", priv_code);
        dist_privi *priv_poin;
        role_privi **ropriv = uepriv->ropriv;
        //
        int role_inde = 0x00, priv_inde;
        for (; (MAX_ROLE_SIZE > role_inde) && ropriv[0x00]; ++role_inde, ++ropriv) {
            OSEVPF("ropriv->role_type:|%d|, ropriv->role_name:|%s|\n", ropriv[0x00]->role_type, ropriv[0x00]->role_name);
            priv_poin = ropriv[0x00]->priv_array;
            priv_inde = 0x00;
            for (; (MAX_PRIVI_SIZE > priv_inde) && DIST_PRIVI_NOT_ZERO(priv_poin); ++priv_inde, ++priv_poin) {
                OSEVPF("priv_poin->privile_code:|%08X|\n", priv_poin->privile_code);
                priv_code &= ~priv_poin->privile_code;
            }
        }
        if (PRIVI_VALUE(priv_code)) return -1;
    }
    //
    OSEVPF("end orole_privile_bzl\n");
    return 0x00;
}


// odb:privile:role(GRANT, "admin", "todb", ALL_PRIVILE);
// odb:privile:role(GRANT, "admin", "odb:odb", ALL_PRIVILE);
// odb:privile:role(GRANT, "admin", "odb:1,2p,3,4p", ALL_PRIVILE);
// odb:privile:role(REVOKE, "admin", "todb", ALL_PRIVILE);

int brole_privile_bzl(respo_ctrl *resctl, user_privi *uepriv, pams_valu *pamvu) {
    OSEVPF("[FUNC]:brole_privile_bzl\n");
    if (!uepriv) return -1;
    // pamvu >= 2
    if (!pamvu->pamcon[0x00] || !pamvu->pamcon[0x01]) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    OSEVPF("PPAM_ROLE_TYPE:|%08X|\n", *((uint32 *) pamvu->pamcon[PPAM_ROLE_TYPE]));
    if ((GRANT_PRIV == *((uint32 *) pamvu->pamcon[PPAM_ROLE_TYPE]))
            || (REVOKE_PRIV == *((uint32 *) pamvu->pamcon[PPAM_ROLE_TYPE]))) {
        // pamvu = 4
        if (!pamvu->pamcon[0x02] || !pamvu->pamcon[0x03] || pamvu->pamcon[0x04]) {
            PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
            OSEVPF("PAMVU EXCEPITON!\n");
            return -1;
        }
        //
        uint32 priv_code = *((uint32 *) pamvu->pamcon[BPPAM_PRIVILE]);
        OSEVPF("priv_code:|%08X|\n", priv_code);
        osv_oid_t base_obid;
        if (bpriv_dist_obid(&base_obid, pamvu->pamcon[PPAM_DIST_IDEN], priv_code)) {
            PDAT_EXCEPTIO_TAIL(resctl, DISTI_OBID_EXPT)
            return ERR_FAULT;
        }
        //
        dist_privi *priv_poin;
        role_privi **ropriv = uepriv->ropriv;
        int role_inde = 0x00, priv_inde;
        for (; (MAX_ROLE_SIZE > role_inde) && ropriv[0x00]; ++role_inde, ++ropriv) {
            OSEVPF("ropriv->role_type:|%d|, ropriv->role_name:|%s|\n", ropriv[0x00]->role_type, ropriv[0x00]->role_name);
            priv_poin = ropriv[0x00]->priv_array;
            priv_inde = 0x00;
            for (; (MAX_PRIVI_SIZE > priv_inde) && DIST_PRIVI_NOT_ZERO(priv_poin); ++priv_inde, ++priv_poin) {
                OSEVPF("priv_poin->privile_code:|%08X|\n", priv_poin->privile_code);
                if (OBID_EQUALI(&base_obid, &priv_poin->dist_obid))
                    priv_code &= ~priv_poin->privile_code;
            }
        }
        if (PRIVI_VALUE(priv_code)) return -1;
    }
    //
    OSEVPF("end brole_privile_bzl\n");
    return 0x00;
}

//

int lechq_privile_bzl(user_privi *uepriv, osv_oid_t *base_obid, uint32 blv_pmk) {
    OSEVPF("[FUNC]:lechq_privile_bzl\n");
    OSEVPF("blv_pmk:|%08X|\n", blv_pmk);
    if (!uepriv) return -1;
    dist_privi * priv_poin;
    role_privi **ropriv = uepriv->ropriv;
    //
    int role_inde = 0x00, priv_inde;
    for (; (MAX_ROLE_SIZE > role_inde) && ropriv[0x00]; ++role_inde, ++ropriv) {
        priv_poin = ropriv[0x00]->priv_array;
        priv_inde = 0x00;
        for (; (MAX_PRIVI_SIZE > priv_inde) && DIST_PRIVI_NOT_ZERO(priv_poin); ++priv_inde, ++priv_poin) {
            if ((SCOP_BASE & priv_poin->privile_code) && STOID_EQUALI(base_obid, &priv_poin->dist_obid)) {
                if (PRIVI_VALUE(blv_pmk & priv_poin->privile_code))
                    return 0x00;
            }
        }
    }
    //
    return -1;
}

int mechq_privile_bzl(user_privi *uepriv, osv_oid_t *cont_obid, uint32 met_pmk) {
    OSEVPF("[FUNC]:mechq_privile_bzl\n");
    OSEVPF("priv_code->met_pmk:|%08X|\n", met_pmk);
    if (!uepriv) return -1;
    dist_privi *priv_poin;
    role_privi **ropriv = uepriv->ropriv;
    //
    int role_inde = 0x00, priv_inde;
    for (; (MAX_ROLE_SIZE > role_inde) && ropriv[0x00]; ++role_inde, ++ropriv) {
        priv_poin = ropriv[0x00]->priv_array;
        priv_inde = 0x00;
        for (; (MAX_PRIVI_SIZE > priv_inde) && DIST_PRIVI_NOT_ZERO(priv_poin); ++priv_inde, ++priv_poin) {
            if ((SCOP_CONT & priv_poin->privile_code) && STOID_EQUALI(cont_obid, &priv_poin->dist_obid)) {
                if (PRIVI_VALUE(met_pmk & priv_poin->privile_code))
                    return 0x00;
            }
        }
    }
    //
    return -1;
}
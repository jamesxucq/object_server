
/* 
 * File:   chk_privi_bzl.h
 * Author: James Xu
 *
 * Created on 2023.4.10, PM 3:10
 */

#ifndef CHK_PRIVI_BZL_H
#define CHK_PRIVI_BZL_H

#include "privi_code.h"
#include "chk_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
#define OPRIV_AUTHE     (SCOP_OSEV)
#define BPRIV_AUTHE     (SCOP_BASE)

    //
#define OPRIV_POST      (SCOP_OSEV | OVBP_POST)
#define BPRIV_POST      (SCOP_OSEV | OVBP_POST)

#define OPRIV_STATU     (SCOP_OSEV | OVBP_STATU)
#define BPRIV_STATU     (SCOP_OSEV | OVBP_STATU)

#define OPRIV_COMND     (SCOP_OSEV | OVBP_COMND)
#define BPRIV_COMND     (SCOP_OSEV | OVBP_COMND)

#define OPRIV_PRIVI     (SCOP_OSEV | OVBP_PRIVI)
#define BPRIV_PRIVI     (SCOP_OSEV | OVBP_PRIVI)

    //
    int osau_privile_bzl(user_privi *uepriv, uint32 priv_code);
    int bsau_privile_bzl(user_privi *uepriv, base_valu *baval, uint32 priv_code);
    //
    int osev_privile_bzl(user_privi *uepriv, uint32 priv_code);
    //
    int levci_privile_bzl(user_privi *uepriv, osv_oid_t *base_obid, uint32 priv_code);
    int levco_privile_bzl(user_privi *uepriv, osv_oid_t *base_obid, osv_oid_t *cont_obid, coqu_pvmk *priv_code);

    // pamvu = 1 // instru

    inline int bvali_qpcont_bzl(valid_cobid *vaoid, base_valu *baval, pams_valu *pamvu) {
        OBID_BINARY_COPY(&vaoid->chk_obid[0x00], &baval->base_obid);
        vaoid->vali_numb = 0xFF;
        return 0x00;
    }

    // bvali_conta_bzl 0x00:ok -1:error
    // QUER_STATU:echo(ECHO); :echo(NAME);
    // pamvu = 0 = 1

    inline int bvali_qeconton_bzl(valid_cobid *vaoid, base_valu *baval, pams_valu *pamvu, void *uepriv) {
        switch (pamvu->pamtyp[0x00]) {
            case DATY_INVAL:
                _LOG_WARN("case: DATY_INVAL");
                qecho_multi_data(vaoid, pamvu->pamcon, uepriv);
                break;
            case DATY_OBID:
                if (qecho_conto_valid(vaoid, (osv_oid_t *) pamvu->pamcon[0x00]))
                    return -1;
                break;
            case DATY_STRI:
                if (qecho_contn_valid(vaoid, &baval->conda_stm, pamvu->pamcon[0x00]))
                    return -1;
                break;
            default:
                _LOG_WARN("default: bvali_qeconton_bzl");
                return -1;
                break;
        }
        return 0x00;
    }

    // pamvu = 1

    inline int bvali_qecontas_bzl(valid_cobid *vaoid, base_valu *baval, pams_valu *pamvu) {
        switch (pamvu->pamtyp[0x00]) {
            case DATY_INVAL:
                _LOG_WARN("case: DATY_INVAL");
                return -1;
                break;
            case DATY_UINT:
                if (base_default_valid(vaoid, &baval->base_obid))
                    return -1;
                break;
            case DATY_OBID:
                if (qecho_conto_valid(vaoid, (osv_oid_t *) pamvu->pamcon[0x00]))
                    return -1;
                break;
            case DATY_STRI:
                if (qecho_contn_valid(vaoid, &baval->conda_stm, pamvu->pamcon[0x00]))
                    return -1;
                break;
            default:
                _LOG_WARN("default: bvali_qecontas_bzl");
                return -1;
                break;
        }
        return 0x00;
    }

    // QUER_CREAT:pamvu->pamcon[0x00] is a contain
    // pamvu >= 3

    inline int bvali_qccont_bzl(valid_cobid *vaoid, base_valu *baval, pams_valu *pamvu) {
        switch (pamvu->pamtyp[0x00]) {
            case DATY_INVAL:
                _LOG_WARN("case: DATY_INVAL");
                return -1;
                break;
            case DATY_STRI:
                if (creat_conta_valid(vaoid, &baval->base_obid))
                    return -1;
                break;
            default:
                _LOG_WARN("default: bvali_qccont_bzl");
                return -1;
                break;
        }
        return 0x00;
    }

    // QUER_DROP:pamvu->pamcon[0x00] is a contain
    // pamvu = 1

    inline int bvali_qdcont_bzl(valid_cobid *vaoid, base_valu *baval, pams_valu *pamvu) {
        switch (pamvu->pamtyp[0x00]) {
            case DATY_INVAL:
                _LOG_WARN("case: DATY_INVAL");
                return -1;
                break;
            case DATY_STRI:
                if (single_conta_valid(vaoid, &baval->conda_stm, pamvu->pamcon[0x00]))
                    return -1;
                break;
            default:
                _LOG_WARN("default: bvali_qdcont_bzl");
                return -1;
                break;
        }
        return 0x00;
    }

    // QUER_UPDAT:pamvu->pamcon[0x00] is a contain
    // pamvu = 2

    inline int bvali_qucont_bzl(valid_cobid *vaoid, base_valu *baval, pams_valu *pamvu) {
        switch (pamvu->pamtyp[0x00]) {
            case DATY_INVAL:
                _LOG_WARN("case: DATY_INVAL");
                return -1;
                break;
            case DATY_STRI:
                if (single_conta_valid(vaoid, &baval->conda_stm, pamvu->pamcon[0x00]))
                    return -1;
                break;
            default:
                _LOG_WARN("default: bvali_qucont_bzl");
                return -1;
                break;
        }
        return 0x00;
    }

    // QUER_INSER:pamvu->pamcon[0x00] is a contain
    // pamvu = 2

    inline int bvali_qicont_bzl(valid_cobid *vaoid, base_valu *baval, pams_valu *pamvu) {
        switch (pamvu->pamtyp[0x00]) {
            case DATY_INVAL:
                _LOG_WARN("case: DATY_INVAL");
                return -1;
                break;
            case DATY_STRI:
                if (single_conta_valid(vaoid, &baval->conda_stm, pamvu->pamcon[0x00]))
                    return -1;
                break;
            default:
                _LOG_WARN("default: bvali_qicont_bzl");
                return -1;
                break;
        }
        return 0x00;
    }

    // QUER_SEARQ:pamvu->pamcon[0x01] may a contain, pamvu->pamcon[0x01] is >= 1 contain
    // pamvu >= 2

    inline int bvali_qscont_bzl(valid_cobid *vaoid, base_valu *baval, pams_valu *pamvu) {
        switch (pamvu->pamtyp[0x00]) {
            case DATY_INVAL:
                _LOG_WARN("case: DATY_INVAL");
                return -1;
                break;
            case DATY_STRI:
                if (DATY_STRI != pamvu->pamtyp[0x01])
                    return -1;
                if (searc_conta_valid(vaoid, &baval->conda_stm, pamvu->pamcon[0x00], pamvu->pamcon[0x01]))
                    return -1;
                break;
            default:
                _LOG_WARN("default: bvali_qscont_bzl");
                return -1;
                break;
        }
        return 0x00;
    }

    // QUER_INVOK:pamvu->pamcon[0x01] is >= 1 contain
    // pamvu >= 2

    inline int bvali_qvcont_bzl(valid_cobid *vaoid, base_valu *baval, pams_valu *pamvu) {
        switch (pamvu->pamtyp[0x01]) {
            case DATY_INVAL:
                _LOG_WARN("case: DATY_INVAL");
                return -1;
                break;
            case DATY_STRI:
                if (multip_conta_valid(vaoid, &baval->conda_stm, pamvu->pamcon[0x01]))
                    return -1;
                break;
            default:
                _LOG_WARN("default: bvali_qvcont_bzl");
                return -1;
                break;
        }
        return 0x00;
    }

    // QUER_FACTO:pamvu->pamcon[0x01] is >= 1 contain
    // pamvu >= 2

    inline int bvali_qfcont_bzl(valid_cobid *vaoid, base_valu *baval, pams_valu *pamvu) {
        switch (pamvu->pamtyp[0x00]) {
            case DATY_INVAL:
                _LOG_WARN("case: DATY_INVAL");
                return -1;
                break;
            case DATY_STRI:
                if (DATY_STRI != pamvu->pamtyp[0x01])
                    return -1;
                if (facto_conta_valid(vaoid, &baval->conda_stm, pamvu->pamcon[0x00], pamvu->pamcon[0x01]))
                    return -1;
                break;
            default:
                _LOG_WARN("default: bvali_qfcont_bzl");
                return -1;
                break;
        }
        return 0x00;
    }

    int levqu_privile_bzl(user_privi *uepriv, osv_oid_t *base_obid, valid_cobid *vaoid, coqu_pvmk *priv_code);

    //
    int orole_privile_bzl(respo_ctrl *resctl, user_privi *uepriv, pams_valu *pamvu);
    int brole_privile_bzl(respo_ctrl *resctl, user_privi *uepriv, pams_valu *pamvu);

    //
    int lechq_privile_bzl(user_privi *uepriv, osv_oid_t *base_obid, uint32 blv_pmk);
    int mechq_privile_bzl(user_privi *uepriv, osv_oid_t *cont_obid, uint32 met_pmk);

#ifdef __cplusplus
}
#endif

#endif /* CHK_PRIVI_BZL_H */


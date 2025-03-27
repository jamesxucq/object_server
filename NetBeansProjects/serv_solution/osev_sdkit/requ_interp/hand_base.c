#include "commo_header.h"
#include "kcomm_header.h"

#include "rstatu_bzl.h"
#include "basev_bzl.h"
#include "chk_reque_param.h"
#include "privile_bzl.h"

#include "hand_base.h"
// #include "../debug_funct_os.h"

//
#define CHECK_RETURN(FUNC_INVO) if (FUNC_INVO) return -1;

// authen
#define APAM_USER_NAME     0x00
#define APAM_REQU_VALID    0x01
#define APAM_REQU_SALT     0x02
#define APAM_OSEV_BASE     0x03

int base_authen_hand(respo_ctrl *resctl, session *seion, pams_valu *pamvu) {
    OSEVPF("[FUNC]:base_authen_hand\n");
    char **pamvp = pamvu->pamcon;
    priv_auth *apval;
    // pamvu = 4
    if (!pamvp[0x00] || !pamvp[0x01] || !pamvp[0x02] || !pamvp[0x03] || pamvp[0x04]) {
        OSEVPF("[0x00]:|%s| [0x02]:|%s| [0x03]:|%s| [0x04]:|%s|\n", pamvp[0x00], pamvp[0x02], pamvp[0x03], pamvp[0x04]);
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    // connect to odb
    if (VALID_OPEN_BZL(pamvp[APAM_OSEV_BASE])) {
        PDAT_EXCEPTIO_TAIL(resctl, OPEN_BASE_EXPT)
        return -1;
    } else {
        seion->baval = FIND_BADATN_BZL(pamvp[APAM_OSEV_BASE]);
        if ((apval = base_apval_bzl(pamvp[APAM_USER_NAME], &seion->baval->base_obid, pamvp[APAM_OSEV_BASE]))) {
            if (chk_reque_bzl((unsigned char *) pamvp[APAM_REQU_VALID], apval->auth_valid, pamvp[APAM_REQU_SALT])) {
                // error, unauthorized
                // _LOG_INFO("inval->seion_id:%s", inval->seion_id);
                erase_auth_cache_end(apval->_action_key_);
                // UNAUTHORIZED;
                PDAT_PRODUCEN_TAIL(resctl)
                return 0x01;
            } else {
                // success
                seion->apval = apval;
                // ruturn obid text
                // memcpy(resctl->resp_memo, &apval->obid_stri, OBJE_IDENTI_SLEN);
                OBID_BINARY_COPY((osv_oid_t *) resctl->resp_memo, &apval->prau_obid)
                PDAT_PRODUCEO_TAIL(resctl, OBJE_IDENTI_BLEN)
            }
        } else {
            // UNAUTHORIZED;
            PDAT_PRODUCEN_TAIL(resctl)
            return 0x01;
        }
    }
    //
    return 0x00;
}

int none_bauthe_hand(respo_ctrl *resctl, session *seion, inte_value *inval) {
    OSEVPF("[FUNC]:none_bauthe_hand\n");
    char **pamvp = inval->pamvs.pamcon;
    priv_auth *apval;
    // pamvu = 4
    if (!pamvp[0x00] || !pamvp[0x01] || !pamvp[0x02] || !pamvp[0x03] || pamvp[0x04]) {
        OSEVPF("pamvp[0x00]:|%s| pamvp[0x01]:|%s| pamvp[0x02]:|%s| pamvp[0x03]:|%s| pamvp[0x04]:|%s|\n",
                pamvp[0x00], pamvp[0x01], pamvp[0x02], pamvp[0x03], pamvp[0x04]);
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    // connect to odb
    if (VALID_OPEN_BZL(pamvp[APAM_OSEV_BASE])) {
        PDAT_EXCEPTIO_TAIL(resctl, OPEN_BASE_EXPT)
        return -1;
    } else {
        seion->baval = FIND_BADATN_BZL(pamvp[APAM_OSEV_BASE]);
        if ((apval = nodb_apval_bzl(pamvp[APAM_USER_NAME], &seion->baval->base_obid, pamvp[APAM_OSEV_BASE]))) {
            seion->apval = apval;
            // ruturn obid text
            // memcpy(resctl->resp_memo, &apval->obid_stri, OBJE_IDENTI_SLEN);
            OBID_BINARY_COPY((osv_oid_t *) resctl->resp_memo, &apval->prau_obid)
            PDAT_PRODUCEO_TAIL(resctl, OBJE_IDENTI_BLEN)
        } else {
            // INTERNAL_SERVER_ERROR;
            PDAT_PRODUCEN_TAIL(resctl)
            return 0x01;
        }
    }
    //
    return 0x00;
}

// post
// osev: testdb:status:status(SET_RUN_LEVEL, "12p");
// osev: testdb:status:status(RELOAD_PRIVILE);

//
#define SPAM_STAT_TYPE 0x00
#define SPAM_STAT_NAID 0x01
#define SPAM_STAT_SETRLEV 0x02

int base_post_hand(respo_ctrl *resctl, pams_valu *pamvu) {
    OSEVPF("[FUNC]:base_post_hand\n");
    // pamvu >= 1
    if (!pamvu->pamcon[0x00]) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    //
    switch (*((uint32 *) pamvu->pamcon[SPAM_STAT_TYPE])) {
        case STATU_RESET_RLEVE:
            CHECK_COUPLE_PARAM(resctl, INVA_PARAM_EXPT, pamvu->pamcon[SPAM_STAT_NAID], pamvu->pamcon[SPAM_STAT_SETRLEV])
            if (reset_brlev_bzl((osv_oid_t *) pamvu->pamcon[SPAM_STAT_NAID], *((uint32 *) pamvu->pamcon[SPAM_STAT_SETRLEV]))) {
                PDAT_EXCEPTIO_TAIL(resctl, BASE_SETLV_EXPT)
                return -1;
            }
            PDAT_PRODUCEN_TAIL(resctl)
            break;
        case STATU_RELOAD_PRIVI:
            PDAT_PRODUCEN_TAIL(resctl)
            break;
        default:
            _LOG_WARN("default: base_status:%u", *((uint32 *) pamvu->pamcon[SPAM_STAT_TYPE]));
            PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
            return -1;
    }
    //
    return 0x00;
}

// odb:open();

#define CPAM_BASE_OBID 0x00
#define CPAM_OPEN_LEVE 0x01

int base_comd_open_hand(respo_ctrl *resctl, pams_valu *pamvu) {
    OSEVPF("[FUNC]:base_comd_open_hand\n");
    // pamvu = 2
    if (!pamvu->pamcon[0x00] || !pamvu->pamcon[0x01] || pamvu->pamcon[0x02]) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    //
    if (open_base_bzl((osv_oid_t *) pamvu->pamcon[CPAM_BASE_OBID], *((uint32 *) pamvu->pamcon[CPAM_OPEN_LEVE]))) {
        PDAT_EXCEPTIO_TAIL(resctl, OPEN_BASE_EXPT)
        return -1;
    }
    //
    PRODU_OBIDE_BZL(resctl, (osv_oid_t *) pamvu->pamcon[CPAM_BASE_OBID]);
    return 0x00;
}

// odb:close();

int base_comd_close_hand(respo_ctrl *resctl, pams_valu *pamvu) {
    OSEVPF("[FUNC]:base_comd_close_hand\n");
    // pamvu = 1
    if (!pamvu->pamcon[0x00] || pamvu->pamcon[0x01]) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    if (close_base_bzl((osv_oid_t *) pamvu->pamcon[CPAM_BASE_OBID])) {
        PDAT_EXCEPTIO_TAIL(resctl, CLOSE_BASE_EXPT)
        return -1;
    }
    //
    PDAT_PRODUCEN_TAIL(resctl)
    return 0x00;
}

// status
// odb:echo(); => odb:echo("todb");
// odb:echo(); // echo base obid

//
#define SPAM_ECHO_VALU 0x00

int base_statu_echo_hand(respo_ctrl *resctl, pams_valu *pamvu) {
    OSEVPF("[FUNC]:base_statu_echo_hand\n");
#ifdef _DEBUG
    char obid_stri[OBJE_IDENTI_ZLEN];
    OSEVPF("param[0x00]:|%s|\n", pamvu->pamcon[0x00]);
    OSEVPF("param[0x00]:|%s|\n", oidstr(obid_stri, (osv_oid_t *) pamvu->pamcon[0x00]));
    OSEVPF("param[0x01]:|%s|\n", pamvu->pamcon[0x01]);
#endif
    // pamvu = 1
    if (!pamvu->pamcon[0x00] || pamvu->pamcon[0x01]) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    // base_obid, authen status, running level
    if (echo_base_bzl(resctl, (osv_oid_t *) pamvu->pamcon[SPAM_ECHO_VALU])) {
        PDAT_EXCEPTIO_TAIL(resctl, BASE_ECHO_EXPT)
        return -1;
    }
    //
    return 0x00;
}

// osev: testdb:status:status(SET_RUN_LEVEL, "12p");
// osev: testdb:status:status(RELOAD_PRIVILE);

//
#define SPAM_STAT_TYPE 0x00
#define SPAM_STAT_NAID 0x01
#define SPAM_STAT_SETRLEV 0x02

int base_statu_statu_hand(respo_ctrl *resctl, pams_valu *pamvu) {
    OSEVPF("[FUNC]:base_statu_statu_hand\n");
    // pamvu >= 1
    if (!pamvu->pamcon[0x00]) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    //
    switch (*((uint32 *) pamvu->pamcon[SPAM_STAT_TYPE])) {
        case STATU_RESET_RLEVE:
            CHECK_COUPLE_PARAM(resctl, INVA_PARAM_EXPT, pamvu->pamcon[SPAM_STAT_NAID], pamvu->pamcon[SPAM_STAT_SETRLEV])
            if (reset_brlev_bzl((osv_oid_t *) pamvu->pamcon[SPAM_STAT_NAID], *((uint32 *) pamvu->pamcon[SPAM_STAT_SETRLEV]))) {
                PDAT_EXCEPTIO_TAIL(resctl, BASE_SETLV_EXPT)
                return -1;
            }
            PDAT_PRODUCEN_TAIL(resctl)
            break;
        case STATU_RELOAD_PRIVI:
            PDAT_PRODUCEN_TAIL(resctl)
            break;
        default:
            _LOG_WARN("default: base_status:%u", *((uint32 *) pamvu->pamcon[SPAM_STAT_TYPE]));
            PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
            return -1;
    }
    //
    return 0x00;
}

// statistics
// odb:statis(); => odb:statis("todb");
// odb:statis();
// odb:statis() | kits:format(XML);

//
#define SPAM_STAI_OBID  0x00

int base_statu_stati_hand(respo_ctrl *resctl, pams_valu *pamvu) {
    OSEVPF("[FUNC]:base_statu_stati_hand\n");
    // pamvu = 1
    if (!pamvu->pamcon[0x00] || pamvu->pamcon[0x01]) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    // base running status / running level / clear status
    if (bstai_base_bzl(resctl, (osv_oid_t *) pamvu->pamcon[SPAM_STAI_OBID])) {
        PDAT_EXCEPTIO_TAIL(resctl, STATI_BASE_EXPT)
        return -1;
    }
    //
    return 0x00;
}

// admin
// odb:privile:list(ROLE);
// odb:privile:list(ROLE, "admin");
// odb:privile:list(USER);
// odb:privile:list(USER, "xman");
// odb:privile:list(ROLE, "develop");

//
#define PPAM_LIST_TYPE    0x00
#define PPAM_LIST_NAME    0x01

int base_priv_list_hand(respo_ctrl *resctl, pams_valu *pamvu) {
    OSEVPF("[FUNC]:base_priv_list_hand\n");
    // pamvu = 1 = 2
    if (!pamvu->pamcon[0x00] || (pamvu->pamcon[0x01] && pamvu->pamcon[0x02])) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    //
    switch (*((uint32 *) pamvu->pamcon[PPAM_LIST_TYPE])) {
        case LIST_ROLE:
            CHECK_RETURN(blist_role_bzl(resctl, pamvu->pamcon[PPAM_LIST_NAME]))
            break;
        case LIST_USER:
            CHECK_RETURN(blist_user_bzl(resctl, pamvu->pamcon[PPAM_LIST_NAME]))
            break;
        default:
            _LOG_WARN("default: osev_list 1:%u", *((uint32 *) pamvu->pamcon[PPAM_LIST_TYPE]));
            PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
            return -1;
    }
    //
    return 0x00;
}

// admin
// odb:privile:role(ADD, "admin");
// odb:privile:role(DEL, "admin");
// odb:privile:role(GRANT, "admin", "todb", ALL_PRIVILE);
// odb:privile:role(REVOKE, "admin", "todb", ALL_PRIVILE);
// odb:privile:role(GRANT, "admin", "todb", ALL_PRIVILE);
// odb:privile:role(REVOKE, "admin", "todb", ALL_PRIVILE);
// odb:privile:list(ROLE) | kits:format(XML);
// odb:privile:role(GRANT, "dvxxx", "todb", ALL_PRIVILE);

//
#define PPAM_ROLE_TYPE    0x00
#define PPAM_ROLE_NAME    0x01
#define PPAM_DIST_IDEN    0x02
#define BPPAM_PRIVILE     0x03

int base_priv_role_hand(respo_ctrl *resctl, pams_valu *pamvu) {
    OSEVPF("[FUNC]:base_priv_role_hand\n");
    // pamvu >= 2
    if (!pamvu->pamtyp[0x00] || !pamvu->pamtyp[0x01]) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    if (USRN_LENGTH <= pamvu->req_len[PPAM_ROLE_NAME]) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_LENG)
        return -1;
    }
    //
    switch (*((uint32 *) pamvu->pamcon[PPAM_ROLE_TYPE])) {
        case ADDI_ROLE:
            CHECK_RETURN(badd_role_bzl(resctl, pamvu->pamcon[PPAM_ROLE_NAME]))
            break;
        case DELE_ROLE:
            CHECK_RETURN(bdel_role_bzl(resctl, pamvu->pamcon[PPAM_ROLE_NAME]))
            break;
        case GRANT_PRIV:
            CHECK_COUPLE_PARAM(resctl, INVA_PARAM_EXPT, pamvu->pamtyp[PPAM_DIST_IDEN], pamvu->pamtyp[BPPAM_PRIVILE])
            CHECK_RETURN(bgran_priv_bzl(resctl, pamvu->pamcon[PPAM_ROLE_NAME], pamvu->pamcon[PPAM_DIST_IDEN], *((uint32 *) pamvu->pamcon[BPPAM_PRIVILE])))
            break;
        case REVOKE_PRIV:
            CHECK_COUPLE_PARAM(resctl, INVA_PARAM_EXPT, pamvu->pamtyp[PPAM_DIST_IDEN], pamvu->pamtyp[BPPAM_PRIVILE])
            CHECK_RETURN(brevk_priv_bzl(resctl, pamvu->pamcon[PPAM_ROLE_NAME], pamvu->pamcon[PPAM_DIST_IDEN], *((uint32 *) pamvu->pamcon[BPPAM_PRIVILE])))
            break;
        default:
            _LOG_WARN("default: base_role:%u", *((uint32 *) pamvu->pamcon[PPAM_ROLE_TYPE]));
            PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
            return -1;
    }
    //
    return 0x00;
}

// admin
// odb:privile:user(ADD, "david", "123456")
// odb:privile:user(DEL, "david")
// odb:privile:user(GRANT, "david", "role")
// odb:privile:user(REVOKE, "david", "role")

//
#define PPAM_USER_TYPE    0x00
#define PPAM_USER_NAME    0x01
#define PPAM_SALT_PASWD   0x02   
#define PPAM_ROLE_EXTE    0x02

int base_priv_user_hand(respo_ctrl *resctl, pams_valu *pamvu) {
    OSEVPF("[FUNC]:base_priv_user_hand\n");
    // pamvu >= 2
    if (!pamvu->pamtyp[0x00] || !pamvu->pamtyp[0x01]) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    if (USRN_LENGTH <= pamvu->req_len[PPAM_USER_NAME]) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_LENG)
        return -1;
    }
    //
    switch (*((uint32 *) pamvu->pamcon[PPAM_USER_TYPE])) {
        case ADDI_USER:
            CHECK_RETURN(badd_user_bzl(resctl, pamvu->pamcon[PPAM_USER_NAME], (unsigned char *) pamvu->pamcon[PPAM_SALT_PASWD]))
            break;
        case DELE_USER:
            CHECK_RETURN(bdel_user_bzl(resctl, pamvu->pamcon[PPAM_USER_NAME]))
            break;
        case GRANT_ROLE:
            CHECK_RETURN(bgran_role_bzl(resctl, pamvu->pamcon[PPAM_USER_NAME], pamvu->pamcon[PPAM_ROLE_EXTE]))
            break;
        case REVOKE_ROLE:
            CHECK_RETURN(brevk_role_bzl(resctl, pamvu->pamcon[PPAM_USER_NAME], pamvu->pamcon[PPAM_ROLE_EXTE]))
            break;
        default:
            _LOG_WARN("default: base_buser:%u", *((uint32 *) pamvu->pamcon[PPAM_USER_TYPE]));
            PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
            return -1;
    }
    //
    return 0x00;
}



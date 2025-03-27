#include "commo_header.h"
#include "kcomm_header.h"

#include "chk_reque_param.h"
#include "privile_bzl.h"
#include "rstatu_bzl.h"
#include "authen_bzl.h"
#include "basev_bzl.h"

#include "hand_osev.h"

//
#define CHECK_RETURN(FUNC_INVO) if (FUNC_INVO) return -1;

//
// authen
#define APAM_USER_NAME     0x00
#define APAM_REQU_VALID    0x01
#define APAM_REQU_SALT     0x02
#define APAM_OSEV_BASE     0x03

int osev_authen_hand(respo_ctrl *resctl, session *seion, pams_valu *pamvu) {
    OSEVPF("[FUNC]:osev_authen_hand\n");
    char **pamvp = pamvu->pamcon;
    priv_auth *apval;
    // pamvu = 4
    if (!pamvp[0x00] || !pamvp[0x01] || !pamvp[0x02] || !pamvp[0x03] || pamvp[0x04]) {
        OSEVPF("[0x00]:|%s| [0x02]:|%s| [0x03]:|%s| [0x04]:|%s|\n", pamvp[0x00], pamvp[0x02], pamvp[0x03], pamvp[0x04]);
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    // connect to osev
    if ((apval = osev_apval_bzl(pamvp[APAM_USER_NAME]))) {
        if (chk_reque_bzl((unsigned char *) pamvp[APAM_REQU_VALID], apval->auth_valid, pamvp[APAM_REQU_SALT])) {
            // _LOG_INFO("inval->seion_id:%s", inval->seion_id);
            erase_auth_cache_end(apval->_action_key_);
            // UNAUTHORIZED;
            PDAT_PRODUCEN_TAIL(resctl)
            return 0x01;
        } else {
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
    //
    return 0x00;
}

//

int none_oauthe_hand(respo_ctrl *resctl, session *seion, inte_value *inval) {
    OSEVPF("[FUNC]:none_oauthe_hand\n");
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
    // connect to osev
    if ((apval = nosv_apval_bzl(pamvp[APAM_USER_NAME]))) {
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
    //
    return 0x00;
}

// post
// osev: status:status(SET_RUN_LEVEL, "testdb", "12p");
// osev: status:status(RELOAD_PRIVILE);

#define SPAM_STAT_TYPE 0x00
#define SPAM_STAT_NAID 0x01
#define SPAM_STAT_SETRLEV 0x02

int osev_post_hand(respo_ctrl *resctl, pams_valu *pamvu) {
    OSEVPF("[FUNC]:osev_statu_statu_hand\n");
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
            if (reset_orlev_bzl(pamvu->pamcon[SPAM_STAT_NAID], *((uint32 *) pamvu->pamcon[SPAM_STAT_SETRLEV]))) {
                PDAT_EXCEPTIO_TAIL(resctl, OSEV_SETLV_EXPT)
                return -1;
            }
            PDAT_PRODUCEN_TAIL(resctl)
            break;
        case STATU_RELOAD_PRIVI:
            PDAT_PRODUCEN_TAIL(resctl)
            break;
        default:
            _LOG_WARN("default: osev_status:%u", *((uint32 *) pamvu->pamcon[SPAM_STAT_TYPE]));
            PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
            return -1;
    }
    //
    return 0x00;
}

// osev: command:open(earth);
// osev:open("todb");
// osev:open("admin");

#define CPAM_BASE_NAME 0x00
#define CPAM_OPEN_LEVE 0x01

int osev_comd_open_hand(respo_ctrl *resctl, pams_valu *pamvu) {
    OSEVPF("[FUNC]:osev_comd_open_hand\n");
    // pamvu = 2
    if (!pamvu->pamtyp[0x00] || !pamvu->pamtyp[0x01] || pamvu->pamtyp[0x02]) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    if (BASE_LENGTH <= pamvu->req_len[CPAM_BASE_NAME]) {
        PDAT_EXCEPTIM_TAIL(resctl, INVA_PARAM_LENG)
        return -1;
    }
    //
    osv_oid_t base_obid;
    if (open_osev_bzl(&base_obid, pamvu->pamcon[CPAM_BASE_NAME], *((uint32 *) pamvu->pamcon[CPAM_OPEN_LEVE]))) {
        PDAT_EXCEPTIO_TAIL(resctl, OPEN_BASE_EXPT)
        return -1;
    }
    //
    PRODU_OBIDE_BZL(resctl, &base_obid);
    return 0x00;
}

// osev:close("todb");

int osev_comd_close_hand(respo_ctrl *resctl, pams_valu *pamvu) {
    OSEVPF("[FUNC]:osev_comd_close_hand\n");
    // pamvu = 1
    if (!pamvu->pamcon[0x00] || pamvu->pamcon[0x01]) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    //
    if (close_osev_bzl(pamvu->pamcon[CPAM_BASE_NAME])) {
        PDAT_EXCEPTIO_TAIL(resctl, CLOSE_BASE_EXPT)
        return -1;
    }
    //
    PDAT_PRODUCEN_TAIL(resctl)
    return 0x00;
}

// status
// osev:echo(); // echo osev base obid
// osev:echo("xodb"); // echo base obid

//
#define SPAM_ECHO_VALU 0x00

int osev_statu_echo_hand(respo_ctrl *resctl, pams_valu *pamvu) {
    OSEVPF("[FUNC]:osev_statu_echo_hand\n");
    // pamvu = 0 = 1
    if (pamvu->pamcon[0x00] && pamvu->pamcon[0x01]) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    // authen status
    if (echo_osev_bzl(resctl, pamvu->pamcon[SPAM_ECHO_VALU])) {
        PDAT_EXCEPTIO_TAIL(resctl, OSEV_ECHO_EXPT)
        return -1;
    }
    //
    return 0x00;
}

// osev: status:status(SET_RUN_LEVEL, "testdb", "12p");
// osev: status:status(RELOAD_PRIVILE);

#define SPAM_STAT_TYPE 0x00
#define SPAM_STAT_NAID 0x01
#define SPAM_STAT_SETRLEV 0x02

int osev_statu_statu_hand(respo_ctrl *resctl, pams_valu *pamvu) {
    OSEVPF("[FUNC]:osev_statu_statu_hand\n");
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
            if (reset_orlev_bzl(pamvu->pamcon[SPAM_STAT_NAID], *((uint32 *) pamvu->pamcon[SPAM_STAT_SETRLEV]))) {
                PDAT_EXCEPTIO_TAIL(resctl, OSEV_SETLV_EXPT)
                return -1;
            }
            PDAT_PRODUCEN_TAIL(resctl)
            break;
        case STATU_RELOAD_PRIVI:
            PDAT_PRODUCEN_TAIL(resctl)
            break;
        default:
            _LOG_WARN("default: osev_status:%u", *((uint32 *) pamvu->pamcon[SPAM_STAT_TYPE]));
            PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
            return -1;
    }
    //
    return 0x00;
}

// statistics
// statis(OSEV) | kits:format(XML);
// osev:statis(OSEV);
// osev:statis(ODB); 
// statis(ODB) | kits:format(XML);

#define SPAM_STAI_TYPE 0x00

int osev_statu_stati_hand(respo_ctrl *resctl, pams_valu *pamvu) {
    OSEVPF("[FUNC]:osev_statu_stati_hand\n");
    // pamvu = 1
    if (!pamvu->pamcon[0x00] || pamvu->pamcon[0x01]) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    //
    switch (*((uint32 *) pamvu->pamcon[SPAM_STAI_TYPE])) {
        case OSEV_STATI_OSEV: // base_obid, authen status
            if (ostai_osev_bzl(resctl)) {
                PDAT_EXCEPTIO_TAIL(resctl, STATI_OSEV_EXPT)
                return -1;
            }
            break;
        case OSEV_STATI_BASE: // all base running status / running level / clear status
            if (ostai_base_bzl(resctl)) {
                PDAT_EXCEPTIO_TAIL(resctl, STATI_BASE_EXPT)
                return -1;
            }
            break;
        default:
            _LOG_WARN("default: SPAM_STAI_TYPE");
            PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
            return -1;
            break;
    }
    //
    return 0x00;
}

// privile // admin
// osev:privile:list(ROLE);
// osev:privile:list(ROLE, "admin");
// osev:privile:list(USER);
// osev:privile:list(USER, "xman");

//
#define PPAM_LIST_TYPE    0x00
#define PPAM_LIST_NAME    0x01

int osev_priv_list_hand(respo_ctrl *resctl, pams_valu *pamvu) {
    OSEVPF("[FUNC]:osev_priv_list_hand\n");
    // pamvu = 1 = 2
    if (!pamvu->pamcon[0x00] || (pamvu->pamcon[0x01] && pamvu->pamcon[0x02])) {
        PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
        OSEVPF("PAMVU EXCEPITON!\n");
        return -1;
    }
    //
    switch (*((uint32 *) pamvu->pamcon[PPAM_LIST_TYPE])) {
        case LIST_ROLE:
            CHECK_RETURN(olist_role_bzl(resctl, pamvu->pamcon[PPAM_LIST_NAME]))
            break;
        case LIST_USER:
            CHECK_RETURN(olist_user_bzl(resctl, pamvu->pamcon[PPAM_LIST_NAME]))
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
// osev:privile:role(ADD, "admin");
// osev:privile:role(DEL, "admin");
// osev:privile:role(GRANT, "admin", ALL_PRIVILE);
// osev:privile:role(REVOKE, "admin", ALL_PRIVILE);

//
#define PPAM_ROLE_TYPE    0x00
#define PPAM_ROLE_NAME    0x01
#define OPPAM_PRIVILE     0x02

int osev_priv_role_hand(respo_ctrl *resctl, pams_valu *pamvu) {
    OSEVPF("[FUNC]:osev_priv_role_hand\n");
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
            CHECK_RETURN(oadd_role_bzl(resctl, pamvu->pamcon[PPAM_ROLE_NAME]))
            break;
        case DELE_ROLE:
            CHECK_RETURN(odel_role_bzl(resctl, pamvu->pamcon[PPAM_ROLE_NAME]))
            break;
        case GRANT_PRIV:
            CHECK_SINGLE_PARAM(resctl, INVA_PARAM_EXPT, pamvu->pamtyp[OPPAM_PRIVILE])
            CHECK_RETURN(ogran_priv_bzl(resctl, pamvu->pamcon[PPAM_ROLE_NAME], *((uint32 *) pamvu->pamcon[OPPAM_PRIVILE])))
            break;
        case REVOKE_PRIV:
            CHECK_SINGLE_PARAM(resctl, INVA_PARAM_EXPT, pamvu->pamtyp[OPPAM_PRIVILE])
            CHECK_RETURN(orevk_priv_bzl(resctl, pamvu->pamcon[PPAM_ROLE_NAME], *((uint32 *) pamvu->pamcon[OPPAM_PRIVILE])))
            break;
        default:
            _LOG_WARN("default: osev_role [0x00]:%u", *((uint32 *) pamvu->pamcon[PPAM_ROLE_TYPE]));
            _LOG_WARN("default: [0x01]:%s", pamvu->pamcon[PPAM_ROLE_NAME]);
            PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
            return -1;
    }
    //
    return 0x00;
}

// admin
// osev:privile:user(ADD, "david", "123456");
// osev:privile:user(DEL, "david");
// osev:privile:user(GRANT, "david", "role");
// osev:privile:user(REVOKE, "david", "role");

// osev: privile:user(ADD, "xman", "123456");
// osev: privile:user(GRANT, "xman", "admin");

//
#define PPAM_USER_TYPE    0x00
#define PPAM_USER_NAME    0x01
#define PPAM_SALT_PASWD   0x02   
#define PPAM_ROLE_EXTE    0x02

int osev_priv_user_hand(respo_ctrl *resctl, pams_valu *pamvu) {
    OSEVPF("[FUNC]:osev_priv_user_hand\n");
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
            CHECK_RETURN(oadd_user_bzl(resctl, pamvu->pamcon[PPAM_USER_NAME], (unsigned char *) pamvu->pamcon[PPAM_SALT_PASWD]))
            break;
        case DELE_USER:
            CHECK_RETURN(odel_user_bzl(resctl, pamvu->pamcon[PPAM_USER_NAME]))
            break;
        case GRANT_ROLE:
            CHECK_RETURN(ogran_role_bzl(resctl, pamvu->pamcon[PPAM_USER_NAME], pamvu->pamcon[PPAM_ROLE_EXTE]))
            break;
        case REVOKE_ROLE:
            CHECK_RETURN(orevk_role_bzl(resctl, pamvu->pamcon[PPAM_USER_NAME], pamvu->pamcon[PPAM_ROLE_EXTE]))
            break;
        default:
            _LOG_WARN("default: osev_ouser:%u", *((uint32 *) pamvu->pamcon[PPAM_USER_TYPE]));
            PDAT_EXCEPTIO_TAIL(resctl, INVA_PARAM_EXPT)
            return -1;
    }
    //
    return 0x00;
}

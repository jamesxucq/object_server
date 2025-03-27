#include <stdio.h>

#include "../cli_macro.h"
#include "../cstri_utili.h"
#include "../cli_struct.h"

#include "defau_utili.h"
#include "../debug_funct_sh.h"

//
#define OPEN_DEFAULT_VALUE "12p34p"

int defva_ocomd_open(char **pamvp, char *_sline_) {
    if (!pamvp[0x00]) return -1;
    // quote_decode(pamvp[0x00]);
    if (!strcmp(OSEV_DEFAULT_VALUE, pamvp[0x00]) || !strcmp(BASE_DEFAULT_VALUE, pamvp[0x00]))
        return -1;
    if (!pamvp[0x01]) {
        expand_tail(pamvp + 0x01, pamvp[0x00]);
        pamvp[0x02] = NULL;
        strcpy(pamvp[0x01], OPEN_DEFAULT_VALUE);
    }
    //
    return 0x00;
}

int defva_bcomd_open(char **pamvp, char *_sline_) {
    if (!pamvp[0x00]) {
        pamvp[0x00] = _sline_;
        strcpy(_sline_, OPEN_DEFAULT_VALUE);
        pamvp[0x01] = NULL;
    }
    if (pamvp[0x01]) return -1;
    //
    return 0x00;
}

// // odb:echo(); => odb:echo("todb");

int defva_ostat_echo(char **pamvp, char *_sline_) {
    CLIEPF("[FUNC]:defva_ostat_echo\n");
    //
    return 0x00;
}

int defva_bstat_echo(char **pamvp, char *_sline_) {
    CLIEPF("[FUNC]:defva_bstat_echo\n");
    //
    return 0x00;
}

//
// LSCPY_O(pamvp[0x00], "AUTH", last_str);
// LSCPY_O(pamvp[0x01], "STAT", last_str);

void defva_ostat_status(char **pamvp, char *_sline_) {
    if (!pamvp[0x00]) {
        LSCPY_O(pamvp[0x00], "SET_RUN_LEVEL", _sline_);
        pamvp[0x01] = NULL;
    }
}

void defva_bstat_status(char **pamvp, char *_sline_) {
    if (!pamvp[0x00]) {
        LSCPY_O(pamvp[0x00], "SET_RUN_LEVEL", _sline_);
        pamvp[0x01] = NULL;
    }
}

///

void defva_ostat_statis(char **pamvp, char *_sline_) {
    if (!pamvp[0x00]) {
        pamvp[0x00] = _sline_;
        lscpy(_sline_, "OSEV");
        pamvp[0x01] = NULL;
    }
}

void defva_bstat_statis(char **pamvp, char *_sline_) {
    // if (!pamvp[0x00]) {
    // pamvp[0x00] = _sline_;
    // lscpy(_sline_, "OSEV");
    // pamvp[0x01] = NULL;
    // }
}

//

// odb:privile:role(ADD, "rd3");
// odb:privile:role(DEL, "rd3");
// osev:privile:role(GRANT, "rd3", ALL_PRIVILE);
// osev:privile:role(REVOKE, "rd3", ALL_PRIVILE);

// odb:privile:role(GRANT, "rd3", "odb:1,2p,3", ALL_PRIVILE);
// odb:privile:role(GRANT, "rd3", "todb", ALL_PRIVILE);
// odb:privile:role(REVOKE, "rd3", "todb", ALL_PRIVILE);

#define GRANT_DEFAULT_VALUE "GRANT"
#define REVOKE_DEFAULT_VALUE "REVOKE"

static osv_str_t OSEV_DEFAULT_TOK = osv_stri("osev");
static osv_str_t BASE_DEFAULT_TOK = osv_stri("odb");

// objide = osev:privile / odb:privile

int defva_opriv_role(char **pamvp, const char *objide) {
    // CLIEPF("[FUNC]:defva_opriv_role\n");
    // CLIEPF("objide:|%s|\n", objide);
    // pamvu >= 2
    if (!pamvp[0x00] || !pamvp[0x01])
        return -1;
    //
    if (!strcmp(GRANT_DEFAULT_VALUE, pamvp[0x00]) || !strcmp(REVOKE_DEFAULT_VALUE, pamvp[0x00])) {
        if (!strncmp(OSEV_DEFAULT_TOK.data, objide, OSEV_DEFAULT_TOK.slen)) {
            if (!pamvp[0x02] || pamvp[0x03])
                return -1;
        } else if (!strncmp(BASE_DEFAULT_TOK.data, objide, BASE_DEFAULT_TOK.slen)) {
            if (!pamvp[0x02] || !pamvp[0x03] || pamvp[0x04])
                return -1;
        }
    }
    //
    return 0x00;
}

int defva_bpriv_role(char **pamvp, const char *objide) {
    // CLIEPF("[FUNC]:defva_opriv_role\n");
    // CLIEPF("objide:|%s|\n", objide);
    // pamvu >= 2
    if (!pamvp[0x00] || !pamvp[0x01])
        return -1;
    //
    if (!strcmp(GRANT_DEFAULT_VALUE, pamvp[0x00]) || !strcmp(REVOKE_DEFAULT_VALUE, pamvp[0x00])) {
        if (!strncmp(OSEV_DEFAULT_TOK.data, objide, OSEV_DEFAULT_TOK.slen)) {
            if (!pamvp[0x02] || pamvp[0x03])
                return -1;
        } else if (!strncmp(BASE_DEFAULT_TOK.data, objide, BASE_DEFAULT_TOK.slen)) {
            if (!pamvp[0x02] || !pamvp[0x03] || pamvp[0x04])
                return -1;
        }
    }
    //
    return 0x00;
}

//

int defva_opriv_user(char **pamvp) {
    // CLIEPF("[FUNC]:defva_opriv_user\n");
    // pamvu >= 2
    if (!pamvp[0x00] || !pamvp[0x01])
        return -1;
    //
    if (!strcmp(GRANT_DEFAULT_VALUE, pamvp[0x00]) || !strcmp(REVOKE_DEFAULT_VALUE, pamvp[0x00])) {
        if (!pamvp[0x02] || pamvp[0x03])
            return -1;
    }
    //
    return 0x00;
}

int defva_bpriv_user(char **pamvp) {
    // CLIEPF("[FUNC]:defva_bpriv_user\n");
    // pamvu >= 2
    if (!pamvp[0x00] || !pamvp[0x01])
        return -1;
    //
    if (!strcmp(GRANT_DEFAULT_VALUE, pamvp[0x00]) || !strcmp(REVOKE_DEFAULT_VALUE, pamvp[0x00])) {
        if (!pamvp[0x02] || pamvp[0x03])
            return -1;
    }
    //
    return 0x00;
}

// osev:privile:list(ROLE);
// osev:privile:list(ROLE, "admin");
// osev:privile:list(USER);
// osev:privile:list(USER, "xman");

int defva_opriv_list(char **pamvp) {
    // CLIEPF("[FUNC]:defva_opriv_user\n");
    // pamvu = 1 = 2
    if (!pamvp[0x00] || (pamvp[0x01] && pamvp[0x02]))
        return -1;
    //
    return 0x00;
}

int defva_bpriv_list(char **pamvp) {
    // CLIEPF("[FUNC]:defva_opriv_user\n");
    // pamvu = 1 = 2
    if (!pamvp[0x00] || (pamvp[0x01] && pamvp[0x02]))
        return -1;
    //
    return 0x00;
}

//

int defva_leve_one(unsigned int levivk, char **pamvp, char *_sline_) {
    CLIEPF("[FUNC]:defva_leve_one\n");
    switch (levivk) {
        case LEVO_POST:
        case LEVO_LIST:
        case LEVO_CREAT:
        case LEVO_DROP:
        case LEVO_REPLA:
        case LEVO_INTEGRA:
        case LEVO_RELOAD:
            break;
        case LEVO_INVAL:
        default:
            _LOG_WARN("default: levivk");
            break;
    }
    //
    return 0x00;
}

//

int defva_leve_twop(unsigned int levivk, char **pamvp, char *_sline_) {
    CLIEPF("[FUNC]:defva_leve_twop\n");
    switch (levivk) {
        case LVTP_POST:
        case LVTP_LIST:
        case LVTP_CREAT:
        case LVTP_DROP:
        case LVTP_REPLA:
        case LVTP_INTEGRA:
        case LVTP_RELOAD:
            break;
        case LVTP_INVAL:
        default:
            _LOG_WARN("default: levivk");
            break;
    }
    //
    return 0x00;
}

int defva_leve_thre(unsigned int levivk, char **pamvp, char *_sline_) {
    CLIEPF("[FUNC]:defva_leve_thre\n");
    switch (levivk) {
        case LEVT_POST:
            KILL_QUOTE(pamvp)
            break;
        case LEVT_ECHO:
            KILL_QUOTE(pamvp)
            if (pamvp[0x00]) return -1;
            break;
        case LEVT_CREAT:
            break;
        case LEVT_UPDAT:
        case LEVT_INSER:
            break;
        case LEVT_DROP:
        case LEVT_SEARO:
            KILL_QUOTE(pamvp)
            break;
        case LEVT_INVOK:
            break;
        case LEVT_INVAL:
        default:
            _LOG_WARN("default: levivk");
            break;
    }
    //
    return 0x00;
}

//
#define DEFVA_LVFPP_ECHO "OBJID"
#define DYNAMIC_PREDICATE_DEFAULT "*"

static const struct stst_node refer_conta_dict[] = {
    {"RCON_ONE", "1I"}, // RCON_ONE
    {"RCON_TWO", "2I"}, // RCON_TWO
    {"RCON_THREE", "3I"}, // RCON_THREE
    {"RCON_FOUR", "4I"}, // RCON_FOUR
    {NULL, "INVA"}
};

int defva_leve_foup(unsigned int levivk, char **pamvp, char *_sline_) {
    CLIEPF("[FUNC]:defva_leve_foup\n");
    switch (levivk) {
        case LVFP_POST:
            break;
        case LVFP_ECHO:
            break;
        case LVFP_CREAT:
            if (pamvp[0x03]) {
                if (!found_value(pamvp[0x03], (struct stst_node *) refer_conta_dict)) {
                    if (!pamvp[0x04]) {
                        expand_tail(pamvp + 0x04, pamvp[0x03]);
                        pamvp[0x05] = NULL;
                        strcpy(pamvp[0x04], DYNAMIC_PREDICATE_DEFAULT);
                    }
                }
            }
            break;
        case LVFP_DROP:
        case LVFP_UPDAT:
        case LVFP_INSER:
        case LVFP_SEARQ:
        case LVFP_FACTO:
        case LVFP_INVOK:
            break;
        case LVFP_INVAL:
        default:
            _LOG_WARN("default: levivk");
            break;
    }
    //
    return 0x00;
}

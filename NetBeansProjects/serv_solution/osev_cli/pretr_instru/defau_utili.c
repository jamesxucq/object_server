#include <stdio.h>

#include "../clit_macro.h"
#include "../cstri_utili.h"
#include "../clit_struct.h"
#include "../clit_obje.h"

#include "defau_utili.h"
#include "../debug_funct_sh.h"

// LSCPY_O(pamvp[0x00], "AUTH", last_str);
// LSCPY_O(pamvp[0x01], "STAT", last_str);

void defva_opost(char **pamvp, char *_sline_) {
    if (!pamvp[0x00]) {
        LSCPY_O(pamvp[0x00], "SET_RUN_LEVEL", _sline_);
        pamvp[0x01] = NULL;
    }
}

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

//

void defva_bpost(char **pamvp, char *_sline_) {
    if (!pamvp[0x00]) {
        LSCPY_O(pamvp[0x00], "SET_RUN_LEVEL", _sline_);
        pamvp[0x01] = NULL;
    }
}

// osev: earth:command:open(); => osev: earth:command:open("12p34p");

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
    CLIT_PF("[FUNC]:defva_ostat_echo\n");
    //
    return 0x00;
}

int defva_bstat_echo(char **pamvp, char *_sline_) {
    CLIT_PF("[FUNC]:defva_bstat_echo\n");
    //
    return 0x00;
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

// objide = osev:privile / odb:privile

int defva_opriv_role(char **pamvp, const char *objide) {
    // CLIT_PF("[FUNC]:defva_opriv_role\n");
    //
    return 0x00;
}

int defva_bpriv_role(char **pamvp, const char *objide) {
    // CLIT_PF("[FUNC]:defva_bpriv_role\n");
    //
    return 0x00;
}

//

int defva_opriv_user(char **pamvp) {
    // CLIT_PF("[FUNC]:defva_opriv_user\n");
    //
    return 0x00;
}

int defva_bpriv_user(char **pamvp) {
    // CLIT_PF("[FUNC]:defva_bpriv_user\n");
    //
    return 0x00;
}

// osev:privile:list(ROLE);
// osev:privile:list(ROLE, "admin");
// osev:privile:list(USER);
// osev:privile:list(USER, "xman");

int defva_opriv_list(char **pamvp) {
    // CLIT_PF("[FUNC]:defva_opriv_list\n");
    //
    return 0x00;
}

int defva_bpriv_list(char **pamvp) {
    // CLIT_PF("[FUNC]:defva_bpriv_list\n");
    //
    return 0x00;
}

//

int defva_levon_exten(unsigned int levivk, char **pamvp, char *_sline_) {
    CLIT_PF("[FUNC]:defva_levon_exten\n");
    switch (levivk) {
        case LEVO_POST:
        case LEVO_STATUS:
        case LEVO_CREATE:
        case LEVO_DROP:
            break;
        case LEVO_REPLACE:
            break;
        case LEVO_INTEGRA:
        case LEVO_RELOAD:
            break;
        case LEVO_INVALID:
        default:
            _LOG_WARN("default: levivk");
            break;
    }
    //
    char *tokep;
    char *last_str;
    char **pam_tok = pamvp;
    if (pamvp[0x00]) {
        for (; pam_tok[0x00]; ++pam_tok);
        last_str = strend((--pam_tok)[0x00]);
        ++last_str;
        // 
        char pamcon[PARAM_LENGTH];
        for (pam_tok = pamvp; pam_tok[0x00]; ++pam_tok) {
            if (':' == (*pam_tok)[0x00]) {
                tokep = lscpy(pamcon, _leve_defa_obje_.obje_iden);
                lscpy(tokep, pam_tok[0x00]);
                LSCPY_O(pam_tok[0x00], pamcon, last_str);
            }
        }
    }
    //
    return 0x00;
}

int defva_levon_pamvs(unsigned int levivk, char **pamvp, char *_sline_) {
    CLIT_PF("[FUNC]:defva_levon_pamvs\n");
    switch (levivk) {
        case LEVO_POST:
        case LEVO_STATUS:
        case LEVO_CREATE:
        case LEVO_DROP:
            break;
        case LEVO_REPLACE:
            break;
        case LEVO_INTEGRA:
        case LEVO_RELOAD:
            break;
        case LEVO_INVALID:
        default:
            _LOG_WARN("default: levivk");
            break;
    }
    //
    char *tokep;
    char *last_str;
    char **pam_tok = pamvp;
    if (pamvp[0x00]) {
        for (; pam_tok[0x00]; ++pam_tok);
        last_str = strend((--pam_tok)[0x00]);
        ++last_str;
        // 
        char pamcon[PARAM_LENGTH];
        for (pam_tok = pamvp; pam_tok[0x00]; ++pam_tok) {
            if (':' == (*pam_tok)[0x00]) {
                tokep = lscpy(pamcon, LEVO_DEFI_OBJE);
                lscpy(tokep, pam_tok[0x00]);
                LSCPY_O(pam_tok[0x00], pamcon, last_str);
            }
        }
    }
    //
    return 0x00;
}

//

int defva_levtp_pamvs(unsigned int levivk, char **pamvp, char *_sline_) {
    CLIT_PF("[FUNC]:defva_levtp_pamvs\n");
    switch (levivk) {
        case LVTP_POST:
        case LVTP_STATUS:
        case LVTP_CREATE:
        case LVTP_DROP:
            break;
        case LVTP_REPLACE:
            break;
        case LVTP_INTEGRA:
        case LVTP_RELOAD:
            break;
        case LVTP_INVALID:
        default:
            _LOG_WARN("default: levivk");
            break;
    }
    //
    char *tokep;
    char *last_str;
    char **pam_tok = pamvp;
    if (pamvp[0x00]) {
        for (; pam_tok[0x00]; ++pam_tok);
        last_str = strend((--pam_tok)[0x00]);
        ++last_str;
        // 
        char pamcon[PARAM_LENGTH];
        for (pam_tok = pamvp; pam_tok[0x00]; ++pam_tok) {
            if (':' == (*pam_tok)[0x00]) {
                tokep = lscpy(pamcon, LVTP_DEFI_OBJE);
                lscpy(tokep, pam_tok[0x00]);
                LSCPY_O(pam_tok[0x00], pamcon, last_str);
            }
        }
    }
    //
    return 0x00;
}

int defva_levth_exten(unsigned int levivk, char **pamvp, char *_sline_) {
    CLIT_PF("[FUNC]:defva_levth_exten\n");
    switch (levivk) {
        case LEVT_POST:
            KILL_QUOTE(pamvp)
            break;
        case LEVT_STATUS:
            KILL_QUOTE(pamvp)
            if (pamvp[0x00]) return -1;
            break;
        case LEVT_CREATE:
            break;
        case LEVT_UPDATE:
        case LEVT_INSERT:
            break;
        case LEVT_DROP:
        case LEVT_SEARCH:
            KILL_QUOTE(pamvp)
            break;
        case LEVT_INVOKE:
            break;
        case LEVT_INVALID:
        default:
            _LOG_WARN("default: levivk");
            break;
    }
    //
    char *tokep;
    char *last_str;
    char **pam_tok = pamvp;
    if (pamvp[0x00]) {
        for (; pam_tok[0x00]; ++pam_tok);
        last_str = strend((--pam_tok)[0x00]);
        ++last_str;
        // 
        char pamcon[PARAM_LENGTH];
        for (pam_tok = pamvp; pam_tok[0x00]; ++pam_tok) {
            if (':' == (*pam_tok)[0x00]) {
                tokep = lscpy(pamcon, _leve_defa_obje_.obje_iden);
                lscpy(tokep, pam_tok[0x00]);
                LSCPY_O(pam_tok[0x00], pamcon, last_str);
            }
        }
    }
    //
    return 0x00;
}

int defva_levth_pamvs(unsigned int levivk, char **pamvp, char *_sline_) {
    CLIT_PF("[FUNC]:defva_levth_pamvs\n");
    switch (levivk) {
        case LEVT_POST:
            KILL_QUOTE(pamvp)
            break;
        case LEVT_STATUS:
            KILL_QUOTE(pamvp)
            if (pamvp[0x00]) return -1;
            break;
        case LEVT_CREATE:
            break;
        case LEVT_UPDATE:
        case LEVT_INSERT:
            break;
        case LEVT_DROP:
        case LEVT_SEARCH:
            KILL_QUOTE(pamvp)
            break;
        case LEVT_INVOKE:
            break;
        case LEVT_INVALID:
        default:
            _LOG_WARN("default: levivk");
            break;
    }
    //
    char *tokep;
    char *last_str;
    char **pam_tok = pamvp;
    if (pamvp[0x00]) {
        for (; pam_tok[0x00]; ++pam_tok);
        last_str = strend((--pam_tok)[0x00]);
        ++last_str;
        // 
        char pamcon[PARAM_LENGTH];
        for (pam_tok = pamvp; pam_tok[0x00]; ++pam_tok) {
            if (':' == (*pam_tok)[0x00]) {
                tokep = lscpy(pamcon, LEVT_DEFI_OBJE);
                lscpy(tokep, pam_tok[0x00]);
                LSCPY_O(pam_tok[0x00], pamcon, last_str);
            }
        }
    }
    //
    return 0x00;
}

//
#define DEFVA_LVFPP_ECHO "ECHO"
#define DYNAMIC_PREDICATE_DEFAULT "*"

static const struct stst_node refer_conta_dict[] = {
    {"RSCON_ONE", "1I"}, // RSCON_ONE
    {"RSCON_TWO", "2I"}, // RSCON_TWO
    {"RSCON_THREE", "3I"}, // RSCON_THREE
    {"RSCON_FOUR", "4I"}, // RSCON_FOUR
    {NULL, "INVA"}
};

static void defva_qstat_statis(char **pamvp, char *_sline_) {
    if (!pamvp[0x00]) {
        pamvp[0x00] = _sline_;
        lscpy(_sline_, "ODB");
        pamvp[0x01] = NULL;
    }
}

static void defva_query_creat(char **pamvp) {
    if (pamvp[0x03]) {
        if (!found_value(pamvp[0x03], (struct stst_node *) refer_conta_dict)) {
            if (!pamvp[0x04]) {
                expand_tail(pamvp + 0x04, pamvp[0x03]);
                pamvp[0x05] = NULL;
                strcpy(pamvp[0x04], DYNAMIC_PREDICATE_DEFAULT);
            }
        }
    }
}

int defva_levfp_pamvs(unsigned int levivk, unsigned int invok, char **pamvp, char *_sline_) {
    CLIT_PF("[FUNC]:defva_levfp_pamvs\n");
    switch (levivk) {
        case LVFP_POST:
            break;
        case LVFP_STATUS:
            if (QSTATU_STATIS == invok)
                defva_qstat_statis(pamvp, _sline_);
            break;
        case LVFP_CREATE:
            defva_query_creat(pamvp);
            break;
        case LVFP_DROP:
        case LVFP_UPDATE:
        case LVFP_INSERT:
        case LVFP_SEARCH:
        case LVFP_FACTORY:
        case LVFP_INVOKE:
            break;
        case LVFP_INVALID:
        default:
            _LOG_WARN("default: levivk");
            break;
    }
    //
    char *tokep;
    char *last_str;
    char **pam_tok = pamvp;
    if (pamvp[0x00]) {
        for (; pam_tok[0x00]; ++pam_tok);
        last_str = strend((--pam_tok)[0x00]);
        ++last_str;
        // 
        char pamcon[PARAM_LENGTH];
        for (pam_tok = pamvp; pam_tok[0x00]; ++pam_tok) {
            if (':' == (*pam_tok)[0x00]) {
                tokep = lscpy(pamcon, LVFP_DEFI_OBJE);
                lscpy(tokep, pam_tok[0x00]);
                LSCPY_O(pam_tok[0x00], pamcon, last_str);
            }
        }
    }
    //
    return 0x00;
}

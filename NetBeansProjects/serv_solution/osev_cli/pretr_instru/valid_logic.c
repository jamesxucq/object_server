
#include <stdio.h>

#include "../clit_macro.h"
#include "../cstri_utili.h"
#include "../clit_struct.h"

#include "valid_logic.h"
#include "../debug_funct_sh.h"

//
static const struct stst_node post_type_dict[] = {
    {"SET_RUN_LEVEL", "0I"}, // STATU_RESET_RLEVE
    {"RELOAD_PRIVILE", "1I"}, // STATU_RELOAD_PRIVI
    {NULL, "INVA"}
};

int ochk_post(char **pamvp) {
    PAMVS_VALUE(pamvp[0x00], post_type_dict);
    if (!strcmp("INVA", pamvp[0x00])) return -1;
    return 0x00;
}

int bchk_post(char **pamvp) {
    PAMVS_VALUE(pamvp[0x00], post_type_dict);
    if (!strcmp("INVA", pamvp[0x00])) return -1;
    return 0x00;
}

//
static const struct stst_node stati_otype_dict[] = {
    {"OSEV", "0I"}, // OSEV_STATI_OSEV
    {"ODB", "1I"}, // OSEV_STATI_BASE
    {NULL, "INVA"}
};

//

int ochk_statu_stati(char **pamvp) {
    PAMVS_VALUE(pamvp[0x00], stati_otype_dict);
    if (!strcmp("INVA", pamvp[0x00])) return -1;
    return 0x00;
}

int bchk_statu_stati(char **pamvp) {
    if (pamvp[0x00]) return -1;
    return 0x00;
}

//

int valid_levon_exten(unsigned int levivk, char **pamvp) {
    CLIT_PF("[FUNC]:valid_levon_exten\n");
    int valid_valu = 0x00;
    switch (levivk) {
        case LVTP_POST:
            break;
        case LVTP_STATUS:
        case LVTP_CREATE:
        case LVTP_DROP:
            break;
        case LVTP_REPLACE: // check external // forced
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
    return valid_valu;
}

int valid_levon_pamvs(unsigned int levivk, char **pamvp) {
    CLIT_PF("[FUNC]:valid_levon_pamvs\n");
    int valid_valu = 0x00;
    switch (levivk) {
        case LVTP_POST:
            break;
        case LVTP_STATUS:
        case LVTP_CREATE:
        case LVTP_DROP:
            break;
        case LVTP_REPLACE: // check external // forced
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
    return valid_valu;
}

//

int valid_levtp_pamvs(unsigned int levivk, unsigned int invok, char **pamvp) {
    CLIT_PF("[FUNC]:valid_levtp_pamvs\n");
    int valid_valu = 0x00;
    switch (levivk) {
        case LVTP_POST:
            break;
        case LVTP_STATUS:
            if (CSTATU_LIST == invok) {
                // pamvu = 0 = 2
                if ((pamvp[0x00] && !pamvp[0x01]) || (pamvp[0x00] && pamvp[0x02]))
                    valid_valu = -1;
            }
            break;
        case LVTP_CREATE:
        case LVTP_DROP:
            break;
        case LVTP_REPLACE: // check external // forced
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
    return valid_valu;
}

//

static const struct stst_node stati_qtype_dict[] = {
    {"ODB", "0I"}, // QUARY_STATI_BASE
    {"CONTAIN", "1I"}, // QUARY_STATI_CONTAIN
    {NULL, "INVA"}
};

#define QCHK_STATIS_PAMVS(PAMVP) \
    PAMVS_WORTH(PAMVP[0x00], stati_qtype_dict)

int valid_levfp_pamvs(unsigned int levivk, unsigned int invok, char **pamvp) {
    CLIT_PF("[FUNC]:valid_levfp_pamvs\n");
    int valid_valu = 0x00;
    switch (levivk) {
        case LVFP_POST:
            break;
        case LVFP_STATUS:
            if (QSTATU_STATIS == invok) {
                QCHK_STATIS_PAMVS(pamvp);
            }
            break;
        case LVFP_CREATE:
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
    return valid_valu;
}

//
#define GRANT_DEFAULT_VALUE "GRANT"
#define REVOKE_DEFAULT_VALUE "REVOKE"

static osv_str_t OSEV_DEFAULT_TOK = osv_stri("osev");
static osv_str_t BASE_DEFAULT_TOK = osv_stri("odb");

//

int ochk_priv_role(char **pamvp, const char *objide) {
    // CLIT_PF("[FUNC]:ochk_priv_role\n");
    // CLIT_PF("objide:|%s|\n", objide);
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

int bchk_priv_role(char **pamvp, const char *objide) {
    // CLIT_PF("[FUNC]:bchk_priv_role\n");
    // CLIT_PF("objide:|%s|\n", objide);
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

int ochk_priv_user(char **pamvp) {
    // CLIT_PF("[FUNC]:ochk_priv_user\n");
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

int bchk_priv_user(char **pamvp) {
    // CLIT_PF("[FUNC]:bchk_priv_user\n");
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

int ochk_priv_list(char **pamvp) {
    // CLIT_PF("[FUNC]:ochk_priv_list\n");
    // pamvu = 1 = 2
    if (!pamvp[0x00] || (pamvp[0x01] && pamvp[0x02]))
        return -1;
    //
    return 0x00;
}

int bchk_priv_list(char **pamvp) {
    // CLIT_PF("[FUNC]:bchk_priv_list\n");
    // pamvu = 1 = 2
    if (!pamvp[0x00] || (pamvp[0x01] && pamvp[0x02]))
        return -1;
    //
    return 0x00;
}
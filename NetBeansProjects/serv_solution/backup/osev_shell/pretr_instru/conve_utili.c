
#include <stdio.h>
#include <pthread.h>

#include "commo_macro.h"
#include "osev_datyp.h"
#include "chk_invok_parms.h"
#include "../cstri_utili.h"
#include "../cli_macro.h"
#include "../privi_utili.h"
#include "../cli_bzl.h"
#include "cont_name_obid.h"
#include "post_inner_valu.h"

#include "conve_utili.h"
#include "../debug_funct_sh.h"

//
static const struct stst_node statu_type_dict[] = {
    {"SET_RUN_LEVEL", "0I"}, // STATU_RESET_RLEVE
    {"RELOAD_PRIVILE", "1I"}, // STATU_RELOAD_PRIVI
    {NULL, "INVA"}
};

int ochk_status_pamvs(char **pamvp) {
    PAMVS_VALUE(pamvp[0x00], statu_type_dict);
    if (!strcmp("INVA", pamvp[0x00])) return -1;
    return 0x00;
}

int bchk_status_pamvs(char **pamvp) {
    PAMVS_VALUE(pamvp[0x00], statu_type_dict);
    if (!strcmp("INVA", pamvp[0x00])) return -1;
    return 0x00;
}

//
static const struct stst_node stati_type_dict[] = {
    {"OSEV", "0I"}, // STATI_OSEV
    {"ODB", "1I"}, // STATI_BASE
    {NULL, "INVA"}
};

int ochk_statis_pamvs(char **pamvp) {
    PAMVS_VALUE(pamvp[0x00], stati_type_dict);
    if (!strcmp("INVA", pamvp[0x00])) return -1;
    return 0x00;
}

int bchk_statis_pamvs(char **pamvp) {
    if (pamvp[0x00]) return -1;
    return 0x00;
}

//

// osev: command:open(earth);
// osev:open("xxx", "12p34p");
// xxx:open("12p34p");
// xxx:open("12p34p"); => odb:open("xxx", "12p34p");

int oconv_open_styl(char **pamvp) {
    CLIEPF("[FUNC]:oconv_open_styl\n");
    uint32 leve_valu;
    // quote_decode(pamvp[0x01]);
    leve_valu = gengr_level(pamvp[0x01]);
    sprintf(pamvp[0x01], "%uI", leve_valu);
    //
    return 0x00;
}

int bconv_open_styl(char **pamvp, const char *objide, osev_clie *oclie) {
    CLIEPF("[FUNC]:bconv_open_styl\n");
    uint32 leve_valu;
    // quote_decode(pamvp[0x00]);
    leve_valu = gengr_level(pamvp[0x00]);
    expand_tail(pamvp + 0x01, pamvp[0x00]);
    sprintf(pamvp[0x01], "%uI", leve_valu);
    //
    char last_obje[OBJN_LENGTH];
    split_last_obje(last_obje, objide);
    //
    osv_oid_t *base_obid = find_base_obid(last_obje, oclie);
    if (!base_obid) {
        CLIEPF("Not found %s !\n", last_obje);
        return -1;
    }
    // 
    expand_tail(pamvp, pamvp[0x01]);
    pamvp[0x02] = NULL;
    ESMCPY_OBID(pamvp[0x00], base_obid);
    strcpy((char *) objide, BASE_DEFAULT_VALUE);
    //
    return 0x00;
}

// xxx:close(); => odb:close("xxx");

int oconv_close_styl(char **pamvp) {
    CLIEPF("[FUNC]:oconv_close_styl\n");
    if (!pamvp[0x00] || pamvp[0x01])
        return -1;
    //
    return 0x00;
}

int bconv_close_styl(char **pamvp, const char *objide, char *_sline_, osev_clie *oclie) {
    CLIEPF("[FUNC]:bconv_close_styl\n");
    if (pamvp[0x00]) return -1;
    char last_obje[OBJN_LENGTH];
    split_last_obje(last_obje, objide);
    //
    osv_oid_t *base_obid = find_base_obid(last_obje, oclie);
    if (!base_obid) {
        CLIEPF("Not found %s !\n", last_obje);
        return -1;
    }
    // 
    pamvp[0x00] = _sline_;
    ESMCPY_OBID(pamvp[0x00], base_obid);
    pamvp[0x01] = NULL;
    strcpy((char *) objide, BASE_DEFAULT_VALUE);
    //
    return 0x00;
}

// odb:echo(); => odb:echo("todb");

int oconv_echo_styl(char **pamvp) {
    CLIEPF("[FUNC]:oconv_echo_styl\n");
    if (pamvp[0x00] && pamvp[0x01])
        return -1;
    //
    return 0x00;
}

int bconv_echo_styl(char **pamvp, const char *objide, char *_sline_, osev_clie *oclie) {
    CLIEPF("[FUNC]:bconv_echo_styl, objide:|%s|\n", objide);
    if (pamvp[0x00]) return -1;
    char last_obje[OBJN_LENGTH];
    split_last_obje(last_obje, objide);
    // CLIEPF("last_obje:|%s|\n", last_obje);
    osv_oid_t *base_obid = find_base_obid(last_obje, oclie);
    if (!base_obid) {
        CLIEPF("Not found %s !\n", last_obje);
        return -1;
    }
    // 
    pamvp[0x00] = _sline_;
    ESMCPY_OBID(pamvp[0x00], base_obid);
    pamvp[0x01] = NULL;
    strcpy((char *) objide, BASE_DEFAULT_VALUE);
    //
    return 0x00;
}

//

// osev:status(SET_RUN_LEVEL, "xodb", "1,2p");
// osev:status(RELOAD_PRIVILE, "xodb")

// odb:status(SET_RUN_LEVEL, "1,2p"); => odb:status(SET_RUN_LEVEL, todb_OID, "1,2p");
// odb:status(RELOAD_PRIVILE); => odb:status(RELOAD_PRIVILE, todb_OID);

//    {"SET_RUN_LEVEL", "0I"}, // STATU_RESET_RLEVE
//    {"RELOAD_PRIVILE", "1I"}, // STATU_RELOAD_PRIVI

int oconv_status_styl(char **pamvp) {
    CLIEPF("[FUNC]:oconv_status_styl\n");
    uint32 leve_valu;
    //
    if (!strcmp("0I", pamvp[0x00])) { // STATU_RESET_RLEVE
        // quote_decode(pamvp[0x02]);
        leve_valu = gengr_level(pamvp[0x02]);
        sprintf(pamvp[0x02], "%uI", leve_valu);
    }
    //
    return 0x00;
}

int bconv_status_styl(char **pamvp, const char *objide, osev_clie *oclie) {
    CLIEPF("[FUNC]:bconv_status_styl, objide:|%s|\n", objide);
    uint32 leve_valu;
    //
    char last_obje[OBJN_LENGTH];
    split_last_obje(last_obje, objide);
    //
    osv_oid_t *base_obid = find_base_obid(last_obje, oclie);
    if (!base_obid) {
        CLIEPF("Not found %s !\n", last_obje);
        return -1;
    }
    if (!strcmp("0I", pamvp[0x00])) { // STATU_RESET_RLEVE
        // quote_decode(pamvp[0x01]);
        leve_valu = gengr_level(pamvp[0x01]);
        sprintf(pamvp[0x01], "%uI", leve_valu);
        //
        expand_tail(pamvp + 0x02, pamvp[0x01]);
        ESMCPY_OBID(pamvp[0x02], base_obid);
        STRI_EXCHANGE(pamvp[0x01], pamvp[0x02], pamvp[0x03])
    } else if (!strcmp("1I", pamvp[0x00])) { // STATU_RELOAD_PRIVI
        expand_tail(pamvp + 0x01, pamvp[0x00]);
        pamvp[0x02] = NULL;
        ESMCPY_OBID(pamvp[0x01], base_obid);
    }
    strcpy((char *) objide, BASE_DEFAULT_VALUE);
    //
    return 0x00;
}

//
// xxx:statis(BASE); => odb:statis(BASE, "xxx");

int oconv_statis_styl(char **pamvp) {
    CLIEPF("[FUNC]:oconv_statis_styl\n");
    if (!pamvp[0x00] || pamvp[0x01])
        return -1;
    //
    return 0x00;
}

int bconv_statis_styl(char **pamvp, const char *objide, char *_sline_, osev_clie *oclie) {
    CLIEPF("[FUNC]:bconv_statis_styl\n");
    char last_obje[OBJN_LENGTH];
    split_last_obje(last_obje, objide);
    //
    osv_oid_t *base_obid = find_base_obid(last_obje, oclie);
    if (!base_obid) {
        CLIEPF("Not found %s !\n", last_obje);
        return -1;
    }
    // 
    if (!pamvp[0x00]) {
        pamvp[0x00] = _sline_;
        ESMCPY_OBID(pamvp[0x00], base_obid);
        pamvp[0x01] = NULL;
    }
    //
    strcpy((char *) objide, BASE_DEFAULT_VALUE);
    //
    return 0x00;
}

//
// osev:privile:list(ROLE, "admin");
// odb:privile:list(ROLE, "admin");

// osev:privile:role(ADD, "admin");
// odb:privile:role(ADD, "admin");

// osev:privile:user(ADD, "david", "123456");
// odb:privile:user(ADD, "david", "123456")

//
static const struct stst_node priv_role_dict[] = {
    {"ADD", "0I"}, // ADDI_ROLE
    {"DEL", "1I"}, // DELE_ROLE
    {"GRANT", "2I"}, // GRANT_PRIV
    {"REVOKE", "3I"}, // REVOKE_PRIV
    {NULL, "INVA"}
};

// osev:privile:role(GRANT, "rd3", ALL_PRIVILE);
// osev:privile:role(REVOKE, "rd3", ALL_PRIVILE);
// privile:role(GRANT, "rd3", OSEV, ALL_PRIVILE);
// privile:role(REVOKE, "rd3", OSEV, ALL_PRIVILE);
// pamvp[0x02]:dist_iden, pamvp[0x03]:privi, pamvp[0x00]:role_type

static uint32 conv_privi_code(uint32 lev_valu, uint32 blev_privi) {
    uint32 privi_code = INVA_PRIVI;
    //
    if (SBLV_ONE & lev_valu) {
        if (BLVP_EXECU & blev_privi) privi_code |= BLVO_EXECU;
        if (BLVP_WRITE & blev_privi) privi_code |= BLVO_WRITE;
        if (BLVP_READ & blev_privi) privi_code |= BLVO_READ;
    }
    if (SBLV_TWOP & lev_valu) {
        if (BLVP_EXECU & blev_privi) privi_code |= BLVT_EXECU;
        if (BLVP_WRITE & blev_privi) privi_code |= BLVT_WRITE;
        if (BLVP_READ & blev_privi) privi_code |= BLVT_READ;
    }
    if (SBLV_THRE & lev_valu) {
        if (BLVP_EXECU & blev_privi) privi_code |= BLVH_EXECU;
        if (BLVP_WRITE & blev_privi) privi_code |= BLVH_WRITE;
        if (BLVP_READ & blev_privi) privi_code |= BLVH_READ;
    }
    if (SBLV_FOUP & lev_valu) {
        if (BLVP_EXECU & blev_privi) privi_code |= BLVF_EXECU;
        if (BLVP_WRITE & blev_privi) privi_code |= BLVF_WRITE;
        if (BLVP_READ & blev_privi) privi_code |= BLVF_READ;
    }
    //
    return privi_code;
}

int oconv_role_pamvs(char **pamvp, const char *objide) {
    CLIEPF("[FUNC]:oconv_role_pamvs\n");
    PAMVS_VALUE(pamvp[0x00], priv_role_dict);
    if (!strcmp("INVA", pamvp[0x00])) return -1;
    //
    uint32 scope_valu, privi_valu;
    uint32 lev_valu = INVA_SBLV;
    // GRANT_PRIV / REVOKE_PRIV
    if (!strcmp("2I", pamvp[0x00]) || !strcmp("3I", pamvp[0x00])) {
        scope_valu = parse_disti_scope(&lev_valu, pamvp[0x02], objide);
        if (!scope_valu) return -1;
        CLIEPF("scope_valu:%u pamvp[0x02]:|%s|\n", scope_valu, pamvp[0x02]);
        if (SCOP_OSEV & scope_valu) {
            privi_valu = parse_osev_privi(pamvp[0x02]);
            CLIEPF("pamvp[0x03]:|%s| privi_valu:%d\n", pamvp[0x03], privi_valu);
            if (!privi_valu) return -1;
            if (ochk_priv_valu(privi_valu)) return -1;
            sprintf(pamvp[0x02], "%uI", scope_valu | privi_valu);
        } else if (SCOP_BASE & scope_valu) {
            privi_valu = parse_base_privi(pamvp[0x03]);
            CLIEPF("pamvp[0x03]:|%s| privi_valu:%d\n", pamvp[0x03], privi_valu);
            if (!privi_valu) return -1;
            if (bchk_priv_valu(privi_valu))
                return -1;
            privi_valu = conv_privi_code(lev_valu, privi_valu);
            sprintf(pamvp[0x03], "%uI", scope_valu | privi_valu);
        } else if (SCOP_CONT & scope_valu) {
            privi_valu = parse_cont_privi(pamvp[0x03]);
            CLIEPF("pamvp[0x03]:|%s| privi_valu:%d\n", pamvp[0x03], privi_valu);
            if (!privi_valu) return -1;
            if (cchk_priv_valu(privi_valu))
                return -1;
            sprintf(pamvp[0x03], "%uI", scope_valu | privi_valu);
        }
    }
    //
    return 0x00;
}

int bconv_role_pamvs(char **pamvp, const char *objide) {
    CLIEPF("[FUNC]:bconv_role_pamvs\n");
    PAMVS_VALUE(pamvp[0x00], priv_role_dict);
    if (!strcmp("INVA", pamvp[0x00])) return -1;
    //
    uint32 scope_valu, privi_valu;
    uint32 lev_valu = INVA_SBLV;
    // GRANT_PRIV / REVOKE_PRIV
    if (!strcmp("2I", pamvp[0x00]) || !strcmp("3I", pamvp[0x00])) {
        scope_valu = parse_disti_scope(&lev_valu, pamvp[0x02], objide);
        if (!scope_valu) return -1;
        CLIEPF("scope_valu:%u pamvp[0x02]:|%s|\n", scope_valu, pamvp[0x02]);
        if (SCOP_OSEV & scope_valu) {
            privi_valu = parse_osev_privi(pamvp[0x02]);
            CLIEPF("pamvp[0x03]:|%s| privi_valu:%d\n", pamvp[0x03], privi_valu);
            if (!privi_valu) return -1;
            if (ochk_priv_valu(privi_valu)) return -1;
            sprintf(pamvp[0x02], "%uI", scope_valu | privi_valu);
        } else if (SCOP_BASE & scope_valu) {
            privi_valu = parse_base_privi(pamvp[0x03]);
            CLIEPF("pamvp[0x03]:|%s| privi_valu:%d\n", pamvp[0x03], privi_valu);
            if (!privi_valu) return -1;
            if (bchk_priv_valu(privi_valu))
                return -1;
            privi_valu = conv_privi_code(lev_valu, privi_valu);
            sprintf(pamvp[0x03], "%uI", scope_valu | privi_valu);
        } else if (SCOP_CONT & scope_valu) {
            privi_valu = parse_cont_privi(pamvp[0x03]);
            CLIEPF("pamvp[0x03]:|%s| privi_valu:%d\n", pamvp[0x03], privi_valu);
            if (!privi_valu) return -1;
            if (cchk_priv_valu(privi_valu))
                return -1;
            sprintf(pamvp[0x03], "%uI", scope_valu | privi_valu);
        }
    }
    //
    return 0x00;
}

//
static const struct stst_node priv_list_dict[] = {
    {"ROLE", "0I"}, // LIST_ROLE
    {"USER", "1I"}, // LIST_USER
    {NULL, "INVA"}
};

static struct stst_node priv_user_dict[] = {
    {"ADD", "0I"}, // ADDI_USER
    {"DEL", "1I"}, // DELE_USER
    {"GRANT", "2I"}, // GRANT_ROLE
    {"REVOKE", "3I"}, // REVOKE_ROLE
    {NULL, "INVA"}
};

int oconv_list_pamvs(char **pamvp) {
    CLIEPF("[FUNC]:oconv_list_pamvs\n");
    // CLIEPF("pamvp[0x00]:|%s|\n", pamvp[0x00]);
    PAMVS_VALUE(pamvp[0x00], priv_list_dict);
    if (!strcmp("INVA", pamvp[0x00])) return -1;
    CLIEPF("pamvp[0x00]:|%s|\n", pamvp[0x00]);
    return 0x00;
}

int bconv_list_pamvs(char **pamvp) {
    CLIEPF("[FUNC]:bconv_list_pamvs\n");
    // CLIEPF("pamvp[0x00]:|%s|\n", pamvp[0x00]);
    PAMVS_VALUE(pamvp[0x00], priv_list_dict);
    if (!strcmp("INVA", pamvp[0x00])) return -1;
    CLIEPF("pamvp[0x00]:|%s|\n", pamvp[0x00]);
    return 0x00;
}

int oconv_user_pamvs(char **pamvp) {
    CLIEPF("[FUNC]:oconv_user_pamvs\n");
    // CLIEPF("pamvp[0x00]:|%s| pamvp[0x01]:|%s| pamvp[0x02]:|%s| pamvp[0x03]:|%s|\n", pamvp[0x00], pamvp[0x01], pamvp[0x02], pamvp[0x03]);
    PAMVS_VALUE(pamvp[0x00], priv_user_dict);
    if (!strcmp("INVA", pamvp[0x00])) return -1;
    //
    if (!strcmp("0I", pamvp[0x00])) {
        // params < 3
        CHECK_PARAM_ONE(pamvp[0x02])
                unsigned char salt_paswd[SALT_LENGTH + PASWD_LENGTH];
        unsigned char *salt = salt_paswd;
        unsigned char *paswd = salt_paswd + SALT_LENGTH;
        if (USRN_LENGTH < strlen(pamvp[0x01]) || PASWD_LENGTH < strlen(pamvp[0x02]))
            return -1;
        //
        random_salt(salt);
        unsigned char ecb_key[KEY_LENGTH];
        produ_authen_key(ecb_key, salt);
        if (!crypto_encode_ecb(paswd, (unsigned char *) pamvp[0x02], ecb_key))

            return -1;
        ESMCPY_BINARY(pamvp[0x02], salt_paswd, SALT_LENGTH + PASWD_LENGTH);
        pamvp[0x03] = NULL;
    }
    //
    return 0x00;
}

int bconv_user_pamvs(char **pamvp) {
    CLIEPF("[FUNC]:bconv_user_pamvs\n");
    // CLIEPF("pamvp[0x00]:|%s| pamvp[0x01]:|%s| pamvp[0x02]:|%s| pamvp[0x03]:|%s|\n", pamvp[0x00], pamvp[0x01], pamvp[0x02], pamvp[0x03]);
    PAMVS_VALUE(pamvp[0x00], priv_user_dict);
    if (!strcmp("INVA", pamvp[0x00])) return -1;
    //
    if (!strcmp("0I", pamvp[0x00])) {
        // params < 3
        CHECK_PARAM_ONE(pamvp[0x02])
                unsigned char salt_paswd[SALT_LENGTH + PASWD_LENGTH];
        unsigned char *salt = salt_paswd;
        unsigned char *paswd = salt_paswd + SALT_LENGTH;
        if (USRN_LENGTH < strlen(pamvp[0x01]) || PASWD_LENGTH < strlen(pamvp[0x02]))
            return -1;
        //
        random_salt(salt);
        unsigned char ecb_key[KEY_LENGTH];
        produ_authen_key(ecb_key, salt);
        if (!crypto_encode_ecb(paswd, (unsigned char *) pamvp[0x02], ecb_key))

            return -1;
        ESMCPY_BINARY(pamvp[0x02], salt_paswd, SALT_LENGTH + PASWD_LENGTH);
        pamvp[0x03] = NULL;
    }
    //
    return 0x00;
}

//
#define LEV0_DEFI_OBJE "odb"

int lconv_levon_pamvs(unsigned int levivk, char **pamvp) {
    CLIEPF("[FUNC]:lconv_levon_param\n");
    char *tokep;
    char *last_str;
    //
    char **pam_tok = pamvp;
    if (pamvp[0x00]) {
        for (; pam_tok[0x00]; ++pam_tok);
        last_str = strend((--pam_tok)[0x00]);
        ++last_str;
        // 
        char pamcon[PARAM_LENGTH];
        for (pam_tok = pamvp; pam_tok[0x00]; ++pam_tok) {
            if (':' == (*pam_tok)[0x00]) {

                tokep = lscpy(pamcon, LEV0_DEFI_OBJE);
                lscpy(tokep, pam_tok[0x00]);
                LSCPY_O(pam_tok[0x00], pamcon, last_str);
            }
        }
    }
    //
    int conv_valu = 0x00;
    switch (levivk) {
        case LEVO_POST:
            if (ipti_inner_inst(pamvp))
                conv_valu = -1;
            break;
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
    return conv_valu;
}

//

int lconv_levon_exten(unsigned int levivk, char **pamvp, char *_sline_) {
    CLIEPF("[FUNC]:lconv_levon_exten\n");
    char *tokep;
    char *last_str;
    //
    char **pam_tok = pamvp;
    if (!pamvp[0x00]) { // fixme, 20220313
        last_str = _sline_;
        LSCPY_O(pam_tok[0x00], _leve_defa_obje_.obje_iden, last_str);
        (++pam_tok)[0x00] = NULL;
    } else {
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
    int conv_valu = 0x00;
    switch (levivk) {
        case LEVO_POST:
            if (ipti_inner_inst(pamvp))
                conv_valu = -1;
            break;
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
    return conv_valu;
}

//
#define LVTP_DEFI_OBJE "odb"

int lconv_levtp_pamvs(unsigned int levivk, char **pamvp) {
    CLIEPF("[FUNC]:lconv_levtp_param\n");
    char *tokep;
    char *last_str;
    //
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
    int conv_valu = 0x00;
    switch (levivk) {
        case LVTP_POST:
            if (cpti_inner_inst(pamvp))
                conv_valu = -1;
            break;
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
    return conv_valu;
}

// Server
// #define EECHO_CONT_OBJID    0x00
// #define EECHO_CONT_NAME     0x01
// #define EECHO_LEVT_ATTRIB   0x02
// #define EECHO_LEVT_STATIS   0x03

#define LEVT_DEFI_OBJE "odb"

int lconv_levth_pamvs(unsigned int levivk, char **pamvp) {
    CLIEPF("[FUNC]:lconv_levth_param pamvp, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", pamvp[0x00], pamvp[0x01], pamvp[0x02], pamvp[0x03]);
    CLIEPF("levivk:|%u|\n", levivk);
    char *tokep;
    char *last_str;
    //
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
    osv_oid_t binary_obid[MAX_SCONT_COUNT];
    int boidcoun;
    int conv_valu = 0x00;
    switch (levivk) {
        case LEVT_POST:
            if (epti_inner_inst(pamvp))
                conv_valu = -1;
            break;
        case LEVT_ECHO:
            // CLIEPF("1 pamvp[0x00]:|%s|\n", pamvp[0x00]);
            break;
        case LEVT_CREAT:
            // quote_decode(pamvp[0x01]);
            break;
        case LEVT_UPDAT:
        case LEVT_INSER:
            if (pamvp[0x00] && PREDI_TYPE_OBJID == check_predi_type(pamvp[0x00])) {
                boidcoun = pretr_source_obid(binary_obid, pamvp[0x00]);
                // CLIEPF("boidcoun:|%d|\n", boidcoun);
                if (0x00 < boidcoun)
                    PACK_COMPLEX_OBID(pamvp[0x00], (void *) binary_obid, boidcoun);
            } else conv_valu = -1;
            break;
        case LEVT_DROP:
        case LEVT_SEARO:
            if (pamvp[0x00] && PREDI_TYPE_OBJID == check_predi_type(pamvp[0x00])) {
                boidcoun = pretr_source_obid(binary_obid, pamvp[0x00]);
                // CLIEPF("boidcoun:|%d|\n", boidcoun);
                if (0x00 < boidcoun)
                    PACK_COMPLEX_OBID(pamvp[0x00], (void *) binary_obid, boidcoun);
            }
            break;
        case LEVT_INVOK:
            if (pamvp[0x01] && PREDI_TYPE_OBJID == check_predi_type(pamvp[0x01])) {
                boidcoun = pretr_source_obid(binary_obid, pamvp[0x01]);
                // CLIEPF("boidcoun:|%d|\n", boidcoun);
                if (0x00 < boidcoun)
                    PACK_COMPLEX_OBID(pamvp[0x01], (void *) binary_obid, boidcoun);
            }
            break;
        case LEVT_INVAL:
        default:
            _LOG_WARN("default: levivk");
            break;
    }
    //
    return conv_valu;
}

//

int lconv_levth_exten(unsigned int levivk, char **pamvp, char *_sline_) {
    CLIEPF("[FUNC]:lconv_levth_exten\n");
    CLIEPF("[0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", pamvp[0x00], pamvp[0x01], pamvp[0x02], pamvp[0x03]);
    CLIEPF("levivk:|%u|\n", levivk);
    char *tokep;
    char *last_str;
    //
    char **pam_tok = pamvp;
    if (!pamvp[0x00]) { // disable by james, 20220313 . for create blank object
        // last_str = _sline_;
        // LSCPY_O(pam_tok[0x00], _leve_defa_obje_.obje_iden, last_str);
        // (++pam_tok)[0x00] = NULL;
    } else {
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
    osv_oid_t binary_obid[MAX_SCONT_COUNT];
    int boidcoun;
    int conv_valu = 0x00;
    switch (levivk) {
        case LEVT_POST:
            if (epti_inner_inst(pamvp))
                conv_valu = -1;
            break;
        case LEVT_ECHO:
            // CLIEPF("1 pamvp[0x00]:|%s|\n", pamvp[0x00]);
            break;
        case LEVT_CREAT:
            // quote_decode(pamvp[0x01]);
            if (pretr_functi_pamvs((const char **) pamvp))
                conv_valu = -1;
            break;
        case LEVT_UPDAT:
        case LEVT_INSER:
            // quote_decode(pamvp[0x01]);
            if (pretr_functi_pamvs((const char **) pamvp))
                conv_valu = -1;
            break;
        case LEVT_DROP:
        case LEVT_SEARO:
            if (pamvp[0x00] && PREDI_TYPE_OBJID == check_predi_type(pamvp[0x00])) {
                boidcoun = pretr_source_obid(binary_obid, pamvp[0x00]);
                // CLIEPF("boidcoun:|%d|\n", boidcoun);
                if (0x00 < boidcoun)
                    PACK_COMPLEX_OBID(pamvp[0x00], (void *) binary_obid, boidcoun);
            }
            break;
        case LEVT_INVOK:
            if (pamvp[0x01] && PREDI_TYPE_OBJID == check_predi_type(pamvp[0x01])) {
                boidcoun = pretr_source_obid(binary_obid, pamvp[0x01]);
                CLIEPF("boidcoun:|%d|\n", boidcoun);
                if (0x00 < boidcoun)
                    PACK_COMPLEX_OBID(pamvp[0x01], (void *) binary_obid, boidcoun);
            }
            break;
        case LEVT_INVAL:
        default:
            _LOG_WARN("default: levivk");
            break;
    }
    // CLIEPF("end lconv_levth_exten param\n");
    return conv_valu;
}

//

static const struct stst_node stora_engine_dict[] = {
    {"sharp", "0I"}, // ENGINE_SHARP
    {"imemo", "1I"}, // ENGINE_IMEMO
    {"leap", "2I"}, // ENGINE_LEAP
    {"witi", "3I"}, // ENGINE_WTIGER
    {NULL, "INVA"}
};

static const struct stst_node refer_conta_dict[] = {
    {"RCON_ONE", "1I"}, // RCON_ONE
    {"RCON_TWO", "2I"}, // RCON_TWO
    {"RCON_THREE", "3I"}, // RCON_THREE
    {"RCON_FOUR", "4I"}, // RCON_FOUR
    {NULL, "INVA"}
};

///

#define LVFP_DEFI_OBJE "odb"

int lconv_levfp_pamvs(unsigned int levivk, char **pamvp) {
    CLIEPF("[FUNC]:lconv_levfp_param param, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", pamvp[0x00], pamvp[0x01], pamvp[0x02], pamvp[0x03]);
    CLIEPF("levivk:|%u|\n", levivk);
    char *tokep;
    char *last_str;
    //
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
    osv_oid_t binary_obid[MAX_SCONT_COUNT];
    int boidcoun;
    int conv_valu = 0x00;
    switch (levivk) {
        case LVFP_POST:
            if (qpti_inner_inst(pamvp))
                conv_valu = -1;
            break;
        case LVFP_ECHO:
            // quote_decode(pamvp[0x00]);
            break;
        case LVFP_CREAT:
            // quote_decode(pamvp[0x01]);
            PAMVS_VALUE(pamvp[0x01], stora_engine_dict);
            if (!strcmp("INVA", pamvp[0x01])) conv_valu = -1;
            if (pamvp[0x03])
                found_conve_value(pamvp[0x03], (struct stst_node *) refer_conta_dict);
            break;
        case LVFP_DROP:
            break;
        case LVFP_UPDAT:
        case LVFP_INSER:
            if (pretr_functi_pamvs((const char **) pamvp))
                conv_valu = -1;
            if (OBJE_IDENT_TYPE != ((char *) pamvp[0x00])[ESCA_NODTYP_PART]) {
                if (pretr_conta_obid(pamvp))
                    conv_valu = -1;
            }
            break;
        case LVFP_SEARQ:
        case LVFP_FACTO:
        case LVFP_INVOK:
            if (pamvp[0x02] && PREDI_TYPE_OBJID == check_predi_type(pamvp[0x02])) {
                boidcoun = pretr_source_obid(binary_obid, pamvp[0x02]); //
                if (0x00 < boidcoun)
                    PACK_COMPLEX_OBID(pamvp[0x02], (void *) binary_obid, boidcoun);
            }
            break;
        case LVFP_INVAL:
        default:
            _LOG_WARN("default: levivk");
            break;
    }
    //
    return conv_valu;
}





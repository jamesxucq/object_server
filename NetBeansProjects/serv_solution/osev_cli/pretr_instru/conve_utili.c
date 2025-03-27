
#include <stdio.h>
#include <pthread.h>

#include "commo_macro.h"
#include "osev_datyp.h"
#include "chk_invok_parms.h"
#include "../cstri_utili.h"
#include "../clit_macro.h"
#include "../privi_utili.h"
#include "../clit_bzl.h"
#include "cont_name_obid.h"
#include "post_inner_valu.h"
#include "statu_inner_valu.h"
#include "repla_inner_valu.h"

#include "conve_utili.h"
#include "../debug_funct_sh.h"

//

// osev: command:open(earth);
// osev: command:open("earth", "12p34p");

int oconv_open_styl(char **pamvp) {
    CLIT_PF("[FUNC]:oconv_open_styl\n");
    OSEVPF("pamvp[0x00]:|%s| pamvp[0x01]:|%s| pamvp[0x02]:|%s|\n", pamvp[0x00], pamvp[0x01], pamvp[0x02]);
    uint32 leve_valu;
    // quote_decode(pamvp[0x01]);
    leve_valu = gengr_level_numb(pamvp[0x01]);
    sprintf(pamvp[0x01], "%uI", leve_valu);
    OSEVPF("leve_valu:|%u|\n", leve_valu);
    OSEVPF("pamvp[0x00]:|%s| pamvp[0x01]:|%s| pamvp[0x02]:|%s|\n", pamvp[0x00], pamvp[0x01], pamvp[0x02]);
    //
    return 0x00;
}

// osev: earth:command:open("12p34p"); => osev: odb:command:open("earth", 12p34p");

int bconv_open_styl(char **pamvp, const char *objide, osev_clie *oclie) {
    CLIT_PF("[FUNC]:bconv_open_styl\n");
    uint32 leve_valu;
    // quote_decode(pamvp[0x00]);
    OSEVPF("pamvp[0x00]:|%s| pamvp[0x01]:|%s|\n", pamvp[0x00], pamvp[0x01]);
    leve_valu = gengr_level_numb(pamvp[0x00]);
    expand_tail(pamvp + 0x01, pamvp[0x00]);
    sprintf(pamvp[0x01], "%uI", leve_valu);
    OSEVPF("leve_valu:|%u|\n", leve_valu);
    //
    char last_obje[OBJN_LENGTH];
    split_last_obje(last_obje, objide);
    //
    osv_oid_t *base_obid = seek_base_obid(last_obje, oclie);
    if (!base_obid) {
        CLIT_PF("Not found %s !\n", last_obje);
        return -1;
    }
#ifdef _DEBUG
    char obid_stri[OBJE_IDENTI_ZLEN];
    CLIT_PF("seek_base_obid, last_obje:|%s| obid:|%s|\n", last_obje, oidstr(obid_stri, base_obid));
#endif
    // 
    expand_tail(pamvp, pamvp[0x01]);
    pamvp[0x02] = NULL;
    ESMCPY_OBID(pamvp[0x00], base_obid);
    strcpy((char *) objide, BASE_DEFAULT_VALUE);
    // OSEVPF("pamvp[0x00]:|%s|\n", pamvp[0x00]);
    OSEVPF("pamvp[0x01]:|%s|\n", pamvp[0x01]);
    OSEVPF("pamvp[0x02]:|%s|\n", pamvp[0x02]);
    return 0x00;
}

// xxx:close(); => odb:close("xxx");

int oconv_close_styl(char **pamvp) {
    CLIT_PF("[FUNC]:oconv_close_styl\n");
    if (!pamvp[0x00] || pamvp[0x01])
        return -1;
    //
    return 0x00;
}

int bconv_close_styl(char **pamvp, const char *objide, char *_sline_, osev_clie *oclie) {
    CLIT_PF("[FUNC]:bconv_close_styl\n");
    if (pamvp[0x00]) return -1;
    char last_obje[OBJN_LENGTH];
    split_last_obje(last_obje, objide);
    //
    osv_oid_t *base_obid = seek_base_obid(last_obje, oclie);
    if (!base_obid) {
        CLIT_PF("Not found %s !\n", last_obje);
        return -1;
    }
#ifdef _DEBUG
    char obid_stri[OBJE_IDENTI_ZLEN];
    CLIT_PF("seek_base_obid, last_obje:|%s| obid:|%s|\n", last_obje, oidstr(obid_stri, base_obid));
#endif
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
    CLIT_PF("[FUNC]:oconv_echo_styl\n");
    if (pamvp[0x00] && pamvp[0x01])
        return -1;
    //
    return 0x00;
}

int bconv_echo_styl(char **pamvp, const char *objide, char *_sline_, osev_clie *oclie) {
    CLIT_PF("[FUNC]:bconv_echo_styl, objide:|%s|\n", objide);
    if (pamvp[0x00]) return -1;
    char last_obje[OBJN_LENGTH];
    split_last_obje(last_obje, objide);
    // CLIT_PF("last_obje:|%s|\n", last_obje);
    osv_oid_t *base_obid = seek_base_obid(last_obje, oclie);
    if (!base_obid) {
        CLIT_PF("Not found %s !\n", last_obje);
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

int oconv_post_styl(char **pamvp) {
    CLIT_PF("[FUNC]:oconv_post_styl\n");
    uint32 leve_valu;
    //
    if (!strcmp("0I", pamvp[0x00])) { // STATU_RESET_RLEVE
        // quote_decode(pamvp[0x02]);
        leve_valu = gengr_level_numb(pamvp[0x02]);
        sprintf(pamvp[0x02], "%uI", leve_valu);
    }
    //
    return 0x00;
}

int bconv_post_styl(char **pamvp, const char *objide, osev_clie *oclie) {
    CLIT_PF("[FUNC]:bconv_post_styl, objide:|%s|\n", objide);
    uint32 leve_valu;
    //
    char last_obje[OBJN_LENGTH];
    split_last_obje(last_obje, objide);
    //
    osv_oid_t *base_obid = seek_base_obid(last_obje, oclie);
    if (!base_obid) {
        CLIT_PF("Not found %s !\n", last_obje);
        return -1;
    }
    if (!strcmp("0I", pamvp[0x00])) { // STATU_RESET_RLEVE
        // quote_decode(pamvp[0x01]);
        leve_valu = gengr_level_numb(pamvp[0x01]);
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
    CLIT_PF("[FUNC]:oconv_statis_styl\n");
    if (!pamvp[0x00] || pamvp[0x01])
        return -1;
    //
    return 0x00;
}

int bconv_statis_styl(char **pamvp, const char *objide, char *_sline_, osev_clie *oclie) {
    CLIT_PF("[FUNC]:bconv_statis_styl\n");
    char last_obje[OBJN_LENGTH];
    split_last_obje(last_obje, objide);
    //
    osv_oid_t *base_obid = seek_base_obid(last_obje, oclie);
    if (!base_obid) {
        CLIT_PF("Not found %s !\n", last_obje);
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
    CLIT_PF("[FUNC]:oconv_role_pamvs\n");
    PAMVS_VALUE(pamvp[0x00], priv_role_dict);
    if (!strcmp("INVA", pamvp[0x00])) return -1;
    //
    uint32 scope_valu, privi_valu;
    uint32 lev_valu = INVA_SBLV;
    // GRANT_PRIV / REVOKE_PRIV
    if (!strcmp("2I", pamvp[0x00]) || !strcmp("3I", pamvp[0x00])) {
        scope_valu = parse_disti_scope(&lev_valu, pamvp[0x02], objide);
        if (!scope_valu) return -1;
        CLIT_PF("scope_valu:%u pamvp[0x02]:|%s|\n", scope_valu, pamvp[0x02]);
        if (SCOP_OSEV & scope_valu) {
            privi_valu = parse_osev_privi(pamvp[0x02]);
            CLIT_PF("pamvp[0x02]:|%s| privi_valu:%d\n", pamvp[0x02], privi_valu);
            if (!privi_valu) return -1;
            if (ochk_priv_valu(privi_valu)) return -1;
            sprintf(pamvp[0x02], "%uI", scope_valu | privi_valu);
        } else if (SCOP_BASE & scope_valu) {
            privi_valu = parse_base_privi(pamvp[0x03]);
            CLIT_PF("pamvp[0x03]:|%s| privi_valu:%d\n", pamvp[0x03], privi_valu);
            if (!privi_valu) return -1;
            if (bchk_priv_valu(privi_valu))
                return -1;
            privi_valu = conv_privi_code(lev_valu, privi_valu);
            sprintf(pamvp[0x03], "%uI", scope_valu | privi_valu);
        } else if (SCOP_CONT & scope_valu) {
            privi_valu = parse_cont_privi(pamvp[0x03]);
            CLIT_PF("pamvp[0x03]:|%s| privi_valu:%d\n", pamvp[0x03], privi_valu);
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
    CLIT_PF("[FUNC]:bconv_role_pamvs\n");
    PAMVS_VALUE(pamvp[0x00], priv_role_dict);
    if (!strcmp("INVA", pamvp[0x00])) return -1;
    //
    uint32 scope_valu, privi_valu;
    uint32 lev_valu = INVA_SBLV;
    // GRANT_PRIV / REVOKE_PRIV
    if (!strcmp("2I", pamvp[0x00]) || !strcmp("3I", pamvp[0x00])) {
        scope_valu = parse_disti_scope(&lev_valu, pamvp[0x02], objide);
        if (!scope_valu) return -1;
        CLIT_PF("scope_valu:%u pamvp[0x02]:|%s|\n", scope_valu, pamvp[0x02]);
        if (SCOP_OSEV & scope_valu) {
            privi_valu = parse_osev_privi(pamvp[0x02]);
            CLIT_PF("pamvp[0x02]:|%s| privi_valu:%d\n", pamvp[0x02], privi_valu);
            if (!privi_valu) return -1;
            if (ochk_priv_valu(privi_valu)) return -1;
            sprintf(pamvp[0x02], "%uI", scope_valu | privi_valu);
        } else if (SCOP_BASE & scope_valu) {
            privi_valu = parse_base_privi(pamvp[0x03]);
            CLIT_PF("pamvp[0x03]:|%s| privi_valu:%d\n", pamvp[0x03], privi_valu);
            if (!privi_valu) return -1;
            if (bchk_priv_valu(privi_valu))
                return -1;
            privi_valu = conv_privi_code(lev_valu, privi_valu);
            sprintf(pamvp[0x03], "%uI", scope_valu | privi_valu);
        } else if (SCOP_CONT & scope_valu) {
            privi_valu = parse_cont_privi(pamvp[0x03]);
            CLIT_PF("pamvp[0x03]:|%s| privi_valu:%d\n", pamvp[0x03], privi_valu);
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
    CLIT_PF("[FUNC]:oconv_list_pamvs\n");
    // CLIT_PF("pamvp[0x00]:|%s|\n", pamvp[0x00]);
    PAMVS_VALUE(pamvp[0x00], priv_list_dict);
    if (!strcmp("INVA", pamvp[0x00])) return -1;
    CLIT_PF("pamvp[0x00]:|%s|\n", pamvp[0x00]);
    return 0x00;
}

int bconv_list_pamvs(char **pamvp) {
    CLIT_PF("[FUNC]:bconv_list_pamvs\n");
    // CLIT_PF("pamvp[0x00]:|%s|\n", pamvp[0x00]);
    PAMVS_VALUE(pamvp[0x00], priv_list_dict);
    if (!strcmp("INVA", pamvp[0x00])) return -1;
    CLIT_PF("pamvp[0x00]:|%s|\n", pamvp[0x00]);
    return 0x00;
}

int oconv_user_pamvs(char **pamvp) {
    CLIT_PF("[FUNC]:oconv_user_pamvs\n");
    // CLIT_PF("pamvp[0x00]:|%s| pamvp[0x01]:|%s| pamvp[0x02]:|%s| pamvp[0x03]:|%s|\n", pamvp[0x00], pamvp[0x01], pamvp[0x02], pamvp[0x03]);
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
    CLIT_PF("[FUNC]:bconv_user_pamvs\n");
    // CLIT_PF("pamvp[0x00]:|%s| pamvp[0x01]:|%s| pamvp[0x02]:|%s| pamvp[0x03]:|%s|\n", pamvp[0x00], pamvp[0x01], pamvp[0x02], pamvp[0x03]);
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

// contain level

int lconv_levon_pamvs(unsigned int levivk, char **pamvp) {
    CLIT_PF("[FUNC]:lconv_levon_param\n");
    int conv_valu = 0x00;
    switch (levivk) {
        case LEVO_POST:
            if (ipot_inner_inst(pamvp))
                conv_valu = -1;
            break;
        case LEVO_STATUS:
        case LEVO_CREATE:
        case LEVO_DROP:
            break;
        case LEVO_REPLACE:
            if (irep_inner_inst(pamvp))
                conv_valu = -1;
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
    return conv_valu;
}

//

int lconv_levon_exten(unsigned int levivk, char **pamvp, char *_sline_) {
    CLIT_PF("[FUNC]:lconv_levon_exten\n");
    int conv_valu = 0x00;
    switch (levivk) {
        case LEVO_POST:
            if (ipot_inner_inst(pamvp))
                conv_valu = -1;
            break;
        case LEVO_STATUS:
        case LEVO_CREATE:
        case LEVO_DROP:
            break;
        case LEVO_REPLACE:
            if (irep_inner_inst(pamvp))
                conv_valu = -1;
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
    return conv_valu;
}

//

int lconv_levtp_pamvs(unsigned int levivk, unsigned int invok, char **pamvp) {
    CLIT_PF("[FUNC]:lconv_levtp_param\n");
    int conv_valu = 0x00;
    switch (levivk) {
        case LVTP_POST:
            if (cpot_inner_inst(pamvp))
                conv_valu = -1;
            break;
        case LVTP_STATUS:
            if (CSTATU_LIST == invok) {
                if (csta_inner_inst(pamvp))
                    conv_valu = -1;
            }
            break;
        case LVTP_CREATE:
        case LVTP_DROP:
            break;
        case LVTP_REPLACE:
            if (crep_inner_inst(pamvp))
                conv_valu = -1;
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
    return conv_valu;
}

// Server
// #define EECHO_CONT_OBJID    0x00
// #define EECHO_CONT_NAME     0x01
// #define EECHO_LEVT_ATTRIB   0x02
// #define EECHO_LEVT_STATIS   0x03

int lconv_levth_pamvs(unsigned int levivk, char **pamvp) {
    CLIT_PF("[FUNC]:lconv_levth_param pamvp, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", pamvp[0x00], pamvp[0x01], pamvp[0x02], pamvp[0x03]);
    CLIT_PF("levivk:|%u|\n", levivk);
    osv_oid_t binary_obid[MAX_SCONT_COUNT];
    int boidcoun;
    int conv_valu = 0x00;
    switch (levivk) {
        case LEVT_POST:
            if (epot_inner_inst(pamvp))
                conv_valu = -1;
            break;
        case LEVT_STATUS:
            // CLIT_PF("1 pamvp[0x00]:|%s|\n", pamvp[0x00]);
            break;
        case LEVT_CREATE:
            // quote_decode(pamvp[0x01]);
            break;
        case LEVT_UPDATE:
        case LEVT_INSERT:
            if (pamvp[0x00] && PREDI_TYPE_OBJID == check_predi_type(pamvp[0x00])) {
                boidcoun = pretr_source_obid(binary_obid, pamvp[0x00]);
                // CLIT_PF("boidcoun:|%d|\n", boidcoun);
                if (0x00 < boidcoun)
                    PACK_COMPLEX_OBID(pamvp[0x00], (void *) binary_obid, boidcoun);
            } else conv_valu = -1;
            break;
        case LEVT_DROP:
        case LEVT_SEARCH:
            if (pamvp[0x00] && PREDI_TYPE_OBJID == check_predi_type(pamvp[0x00])) {
                boidcoun = pretr_source_obid(binary_obid, pamvp[0x00]);
                // CLIT_PF("boidcoun:|%d|\n", boidcoun);
                if (0x00 < boidcoun)
                    PACK_COMPLEX_OBID(pamvp[0x00], (void *) binary_obid, boidcoun);
            }
            break;
        case LEVT_INVOKE:
            if (pamvp[0x01] && PREDI_TYPE_OBJID == check_predi_type(pamvp[0x01])) {
                boidcoun = pretr_source_obid(binary_obid, pamvp[0x01]);
                // CLIT_PF("boidcoun:|%d|\n", boidcoun);
                if (0x00 < boidcoun)
                    PACK_COMPLEX_OBID(pamvp[0x01], (void *) binary_obid, boidcoun);
            }
            break;
        case LEVT_INVALID:
        default:
            _LOG_WARN("default: levivk");
            break;
    }
    //
    return conv_valu;
}

//

int lconv_levth_exten(unsigned int levivk, char **pamvp, char *_sline_) {
    CLIT_PF("[FUNC]:lconv_levth_exten\n");
    CLIT_PF("[0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", pamvp[0x00], pamvp[0x01], pamvp[0x02], pamvp[0x03]);
    CLIT_PF("levivk:|%u|\n", levivk);
    osv_oid_t binary_obid[MAX_SCONT_COUNT];
    int boidcoun;
    int conv_valu = 0x00;
    switch (levivk) {
        case LEVT_POST:
            if (epot_inner_inst(pamvp))
                conv_valu = -1;
            break;
        case LEVT_STATUS:
            // CLIT_PF("1 pamvp[0x00]:|%s|\n", pamvp[0x00]);
            break;
        case LEVT_CREATE:
            // quote_decode(pamvp[0x01]);
            if (pretr_functi_pamvs((const char **) pamvp))
                conv_valu = -1;
            break;
        case LEVT_UPDATE:
        case LEVT_INSERT:
            // quote_decode(pamvp[0x01]);
            if (pretr_functi_pamvs((const char **) pamvp))
                conv_valu = -1;
            break;
        case LEVT_DROP:
        case LEVT_SEARCH:
            if (pamvp[0x00] && PREDI_TYPE_OBJID == check_predi_type(pamvp[0x00])) {
                boidcoun = pretr_source_obid(binary_obid, pamvp[0x00]);
                // CLIT_PF("boidcoun:|%d|\n", boidcoun);
                if (0x00 < boidcoun)
                    PACK_COMPLEX_OBID(pamvp[0x00], (void *) binary_obid, boidcoun);
            }
            break;
        case LEVT_INVOKE:
            if (pamvp[0x01] && PREDI_TYPE_OBJID == check_predi_type(pamvp[0x01])) {
                boidcoun = pretr_source_obid(binary_obid, pamvp[0x01]);
                CLIT_PF("boidcoun:|%d|\n", boidcoun);
                if (0x00 < boidcoun)
                    PACK_COMPLEX_OBID(pamvp[0x01], (void *) binary_obid, boidcoun);
            }
            break;
        case LEVT_INVALID:
        default:
            _LOG_WARN("default: levivk");
            break;
    }
    // CLIT_PF("end lconv_levth_exten param\n");
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
    {"RSCON_ONE", "1I"}, // RSCON_ONE
    {"RSCON_TWO", "2I"}, // RSCON_TWO
    {"RSCON_THREE", "3I"}, // RSCON_THREE
    {"RSCON_FOUR", "4I"}, // RSCON_FOUR
    {NULL, "INVA"}
};

///

int lconv_levfp_pamvs(unsigned int levivk, char **pamvp) {
    CLIT_PF("[FUNC]:lconv_levfp_param param, [0]:|%s| [1]:|%s| [2]:|%s| [3]:|%s|\n", pamvp[0x00], pamvp[0x01], pamvp[0x02], pamvp[0x03]);
    CLIT_PF("levivk:|%u|\n", levivk);
    osv_oid_t binary_obid[MAX_SCONT_COUNT];
    int boidcoun;
    int conv_valu = 0x00;
    switch (levivk) {
        case LVFP_POST:
            if (qpot_inner_inst(pamvp))
                conv_valu = -1;
            break;
        case LVFP_STATUS:
            // quote_decode(pamvp[0x00]);
            break;
        case LVFP_CREATE:
            // quote_decode(pamvp[0x01]);
            PAMVS_VALUE(pamvp[0x01], stora_engine_dict);
            if (!strcmp("INVA", pamvp[0x01])) conv_valu = -1;
            if (pamvp[0x03])
                found_conve_value(pamvp[0x03], (struct stst_node *) refer_conta_dict);
            break;
        case LVFP_DROP:
            break;
        case LVFP_UPDATE:
        case LVFP_INSERT:
            if (pretr_functi_pamvs((const char **) pamvp))
                conv_valu = -1;
            if (OBJE_IDENT_TYPE != ((char *) pamvp[0x00])[ESCA_NODTYP_PART]) {
                if (pretr_conta_obid(pamvp))
                    conv_valu = -1;
            }
            break;
        case LVFP_SEARCH:
        case LVFP_FACTORY:
        case LVFP_INVOKE:
            if (pamvp[0x02] && PREDI_TYPE_OBJID == check_predi_type(pamvp[0x02])) {
                boidcoun = pretr_source_obid(binary_obid, pamvp[0x02]); //
                if (0x00 < boidcoun)
                    PACK_COMPLEX_OBID(pamvp[0x02], (void *) binary_obid, boidcoun);
            }
            break;
        case LVFP_INVALID:
        default:
            _LOG_WARN("default: levivk");
            break;
    }
    //
    return conv_valu;
}






#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../clit_macro.h"
#include "../cinstru.h"
#include "../clit_struct.h"
#include "../clit_obje.h"

#include "parse_levivk.h"
#include "../debug_funct_sh.h"

// modify method
// "odb:createUser",
// "odb:runLevel",

static const struct stin_node lev1_levivk_dict[] = {
    {"post", LEVO_POST},
    {"status", LEVO_STATUS},
    {"create", LEVO_CREATE},
    {"drop", LEVO_DROP},
    {"replace", LEVO_REPLACE},
    {"integra", LEVO_INTEGRA},
    {"reload", LEVO_RELOAD},
    {NULL, LEVO_INVALID}
};

static const struct stin_node lev1_statu_dict[] = {
    {"list", ISTATU_LIST},
    {"statis", ISTATU_STATIS},
    {NULL, ISTATU_INVALID}
};

// modify method
static const struct ssin_node lv2p_levivk_dict[] = {
    {"odb", "post", LVTP_POST},
    {"odb", "status", LVTP_STATUS},
    {"odb", "create", LVTP_CREATE},
    {"odb", "drop", LVTP_DROP},
    {"odb", "replace", LVTP_REPLACE},
    {"odb", "integra", LVTP_INTEGRA},
    {"odb", "reload", LVTP_RELOAD},
    {NULL, NULL, LVTP_INVALID}
};

static const struct stin_node lv2p_statu_dict[] = {
    {"list", CSTATU_LIST},
    {"statis", CSTATU_STATIS},
    {NULL, CSTATU_INVALID}
};

// modify method

static const struct stin_node lev3_levivk_dict[] = {
    {"post", LEVT_POST},
    {"status", LEVT_STATUS},
    {"create", LEVT_CREATE},
    {"drop", LEVT_DROP},
    {"update", LEVT_UPDATE},
    {"insert", LEVT_INSERT},
    {"search", LEVT_SEARCH},
    {"invoke", LEVT_INVOKE},
    {NULL, LEVT_INVALID}
};

static const struct stin_node lev3_statu_dict[] = {
    {"echo", ESTATU_ECHO},
    {"attrib", ESTATU_ATTRIB},
    {"statis", ESTATU_STATIS},
    {NULL, ESTATU_INVALID}
};

// modify method

static const struct ssin_node lv4p_levivk_dict[] = {
    {"odb", "post", LVFP_POST},
    {"odb", "status", LVFP_STATUS},
    {"odb", "create", LVFP_CREATE},
    {"odb", "drop", LVFP_DROP},
    {"odb", "search", LVFP_SEARCH},
    {"odb", "update", LVFP_UPDATE},
    {"odb", "insert", LVFP_INSERT},
    {"odb", "invoke", LVFP_INVOKE},
    {"odb", "factory", LVFP_FACTORY},
    {NULL, NULL, LVFP_INVALID}
};

//

static const struct stin_node lv4p_statu_dict[] = {
    {"echo", QSTATU_ECHO},
    {"attrib", QSTATU_ATTRIB},
    {"statis", QSTATU_STATIS},
    {NULL, QSTATU_INVALID}
};

//

static int parse_cont_level(clit_inst *cinst) {
    CLIT_PF("[FUNC]:parse_cont_level\n");
    CLIT_PF("cinst->obje_iden:|%s| cinst->cont_levivk:|%s|\n", cinst->obje_iden, cinst->cont_levivk);
    switch (cinst->inst_levtyp) {
        case INST_LEVO:
            KV_STIN_EQUA(cinst->inst_levivk, lev1_levivk_dict, cinst->cont_levivk)
            if (LEVO_STATUS == cinst->inst_levivk)
                KV_STIN_EQUA(cinst->inst_invok, lev1_statu_dict, cinst->cont_invok);
            break;
        case INST_LVTP:
            KKV_SSIN_EQUA(cinst->inst_levivk, lv2p_levivk_dict, cinst->obje_iden, cinst->cont_levivk)
            if (LVTP_STATUS == cinst->inst_levivk)
                KV_STIN_EQUA(cinst->inst_invok, lv2p_statu_dict, cinst->cont_invok);
            break;
        case INST_LEVT:
            KV_STIN_EQUA(cinst->inst_levivk, lev3_levivk_dict, cinst->cont_levivk)
            if (LEVT_STATUS == cinst->inst_levivk)
                KV_STIN_EQUA(cinst->inst_invok, lev3_statu_dict, cinst->cont_invok);
            break;
        case INST_LVFP:
            KKV_SSIN_EQUA(cinst->inst_levivk, lv4p_levivk_dict, cinst->obje_iden, cinst->cont_levivk)
            if (LVFP_STATUS == cinst->inst_levivk)
                KV_STIN_EQUA(cinst->inst_invok, lv4p_statu_dict, cinst->cont_invok);
            break;
        case INST_INVAL:
        default:
            _LOG_WARN("default: inst_levtyp");
            return -1;
            break;
    }
    //
    CLIT_PF("parse_cont_level inst_levivk:%d reserved:%d\n", cinst->inst_levivk, cinst->reserved);
    return 0x00;
}

//

/*
    "osev:createUser",
    "osev:runLevel",
    "osev:createRole",
    "osev:grantRolesToUser",
    "osev:updateRole",
 */

//
#define INVAL_INVOK 0x00

static const struct ssii_node osvb_osev_dict[] = {
    {NULL, "post", OSEV_POST, INVAL_INVOK},
    {"echo", "status", OSEV_STATUS, STAIU_ECHO},
    {"statis", "status", OSEV_STATUS, STAIU_STATIS},
    {"open", "command", OSEV_COMAND, COMDI_OPEN},
    {"close", "command", OSEV_COMAND, COMDI_CLOSE},
    {"list", "privile", OSEV_PRIVILE, PRIVI_LIST},
    {"role", "privile", OSEV_PRIVILE, PRIVI_ROLE},
    {"user", "privile", OSEV_PRIVILE, PRIVI_USER},
    {NULL, NULL, OSEV_INVALID, PRIVI_INVALID | STAIU_INVALID | COMDI_INVALID}
};

//

static const struct ssii_node osvb_base_dict[] = {
    {NULL, "post", BASE_POST, INVAL_INVOK},
    {"echo", "status", BASE_STATUS, STAIU_ECHO},
    {"statis", "status", BASE_STATUS, STAIU_STATIS},
    {"open", "command", BASE_COMAND, COMDI_OPEN},
    {"close", "command", BASE_COMAND, COMDI_CLOSE},
    {"list", "privile", BASE_PRIVILE, PRIVI_LIST},
    {"role", "privile", BASE_PRIVILE, PRIVI_ROLE},
    {"user", "privile", BASE_PRIVILE, PRIVI_USER},
    {NULL, NULL, BASE_INVALID, PRIVI_INVALID | STAIU_INVALID | COMDI_INVALID}
};

// 0:success -1:error

static int parse_osvb_level(clit_inst *cinst) {
    CLIT_PF("[FUNC]:parse_osvb_level\n");
    CLIT_PF("obje_iden:|%s|\n", cinst->obje_iden);
    CLIT_PF("cont_levivk:|%s|\n", cinst->cont_levivk);
    CLIT_PF("cinst->cont_invok:|%s|\n", cinst->cont_invok);
    int osvb_valu = 0x00;
    //
    switch (cinst->inst_levtyp) {
        case INST_OSEV:
            NKVI_SSII_EQUA(cinst->inst_levivk, cinst->inst_invok, osvb_osev_dict, cinst->cont_invok, cinst->cont_levivk)
            break;
        case INST_BASE:
            NKVI_SSII_EQUA(cinst->inst_levivk, cinst->inst_invok, osvb_base_dict, cinst->cont_invok, cinst->cont_levivk)
            break;
        case INST_INVAL:
        default:
            _LOG_WARN("default: inst_levtyp");
            osvb_valu = -1;
            break;
    }
    //      
    return osvb_valu;
}

//
static const char* clie_comd_tab[] = {
    "clie:help",
    "clie:version",
    "clie:about",
    NULL
};

static int parse_clie_level(clit_inst *cinst) {
    CLIT_PF("[FUNC]:parse_clie_level\n");
    int chk_valu = -1;
    //
    char comd_cont[PARAM_LENGTH * 0x02];
    sprintf(comd_cont, "%s:%s", cinst->obje_iden, cinst->cont_levivk);
    char **comd_strp = (char **) clie_comd_tab;
    for (; comd_strp[0x00]; ++comd_strp) {
        if (!strcasecmp(comd_cont, comd_strp[0x00])) {
            cinst->inst_levivk = -1;
            cinst->inst_attrib = ATTRI_INSTRUC;
            chk_valu = 0x00;
            break;
        }
    }
    //
    return chk_valu;
}

//
static const INSTRU clie_itype_tab[] = {
    INST_CONNE,
    INST_EXIT,
    INST_BYE,
    INST_CLIINF,
    -1
};

static const INSTRU osvb_itype_tab[] = {
    INST_EXIT,
    INST_USE,
    INST_OSEV,
    INST_BASE,
    INST_QUIT,
    -1
};

static const INSTRU leve_itype_tab[] = {
    INST_QUIT,
    INST_CLILEV,
    INST_LEVO,
    INST_LVTP,
    INST_LEVT,
    INST_LVFP,
    -1
};

// 0:success -1:error

int parse_iinstru_levivk(clit_inst *cinst, uint32 cli_mode) {
    CLIT_PF("[FUNC]:parse_iinstru_levivk\n");
    int chk_valu = -1;
    INSTRU *inst_levtyp;
    //
    switch (cli_mode) {
        case CITP_CLIE:
            inst_levtyp = (INSTRU *) clie_itype_tab;
            for (; -1 != inst_levtyp[0x00]; ++inst_levtyp) {
                if (inst_levtyp[0x00] == cinst->inst_levtyp) {
                    chk_valu = 0x00;
                    if (INST_CLIINF == cinst->inst_levtyp)
                        chk_valu = parse_clie_level(cinst);
                    break;
                }
            }
            break;
        case CITP_OSVB:
            inst_levtyp = (INSTRU *) osvb_itype_tab;
            for (; -1 != inst_levtyp[0x00]; ++inst_levtyp) {
                if (inst_levtyp[0x00] == cinst->inst_levtyp) { // INST_STATU, INST_PRIVILE,
                    chk_valu = 0x00;
                    if ((INST_OSEV == cinst->inst_levtyp) || (INST_BASE == cinst->inst_levtyp))
                        chk_valu = parse_osvb_level(cinst);
                    break;
                }
            }
            break;
        case CITP_CLEV:
            inst_levtyp = (INSTRU *) leve_itype_tab;
            for (; -1 != inst_levtyp[0x00]; ++inst_levtyp) {
                if (inst_levtyp[0x00] == cinst->inst_levtyp) {
                    chk_valu = 0x00;
                    if (INST_LVFP == cinst->inst_levtyp
                            || INST_LEVT == cinst->inst_levtyp
                            || INST_LVTP == cinst->inst_levtyp
                            || INST_LEVO == cinst->inst_levtyp)
                        chk_valu = parse_cont_level(cinst);
                    break;
                }
            }
            break;
        default:
            _LOG_WARN("default: cli_mode");
            chk_valu = -1;
            break;
    }
    CLIT_PF("[FUNC]parse_iinstru_levivk chk_valu:%d\n", chk_valu);
    return chk_valu;
}

//

static const TOKIT_INST lev1_exten_tab[] = {
    KITS_LOAD,
    KITS_SAVE,
    KITS_TRANS,
    KITS_FORMAT,
    -1
};

static const TOKIT_INST lev2p_exten_tab[] = {
    KITS_LIST,
    KITS_LOAD,
    KITS_SAVE,
    KITS_TRANS,
    KITS_FORMAT,
    KITS_EXPLAIN,
    -1
};

static const TOKIT_INST lev3_exten_tab[] = {
    KITS_LOAD,
    KITS_SAVE,
    KITS_PRETTY,
    KITS_KEYVAL,
    KITS_FORMAT,
    -1
};

static const TOKIT_INST lev4p_exten_tab[] = {
    KITS_LOAD,
    KITS_SAVE,
    KITS_PRETTY,
    KITS_KEYVAL,
    KITS_FORMAT,
    -1
};

// 0:success 0x01:exception

static int chk_clev_lext(clit_inst *cinst, uint32 run_level) {
    CLIT_PF("[FUNC]:chk_clev_lext run_level:%08X\n", run_level);
    CLIT_PF("comd_cont:%s:%s\n", cinst->obje_iden, cinst->cont_levivk);
    int chk_valu = -1;
    TOKIT_INST *inst_valu;
    switch (ONLY_LEVEL_VALUE(run_level)) {
        case LVTP_ONE:
            inst_valu = (TOKIT_INST *) lev1_exten_tab;
            for (; -1 != *inst_valu; ++inst_valu) {
                if (*inst_valu == cinst->inst_levtyp) {
                    chk_valu = 0x00;
                    break;
                }
            }
            break;
        case LVTP_TWOP:
            inst_valu = (TOKIT_INST *) lev2p_exten_tab;
            for (; -1 != *inst_valu; ++inst_valu) {
                if (*inst_valu == cinst->inst_levtyp) {
                    chk_valu = 0x00;
                    break;
                }
            }
            break;
        case LVTP_THRE:
            inst_valu = (TOKIT_INST *) lev3_exten_tab;
            for (; -1 != *inst_valu; ++inst_valu) {
                if (*inst_valu == cinst->inst_levtyp) {
                    chk_valu = 0x00;
                    break;
                }
            }
            break;
        case LVTP_FOUP:
            inst_valu = (TOKIT_INST *) lev4p_exten_tab;
            for (; -1 != *inst_valu; ++inst_valu) {
                if (*inst_valu == cinst->inst_levtyp) {
                    chk_valu = 0x00;
                    break;
                }
            }
            break;
    }
    //
    return chk_valu;
}

static const TOKIT_INST exten_ltype_tab[] = {
    KITS_LIST,
    KITS_LOAD,
    KITS_SAVE,
    KITS_TRANS,
    KITS_PRETTY,
    KITS_KEYVAL,
    KITS_FORMAT,
    KITS_EXPLAIN,
    -1
};

static const TOKIT_INST exten_otype_tab[] = {
    KITS_FORMAT,
    -1
};

// 0:success -1:error

int parse_kinstru_levivk(clit_inst *cinst, uint32 cli_mode, uint32 run_level) {
    CLIT_PF("[FUNC]:parse_kinstru_levivk\n");
    int chk_valu = -1;
    //
    TOKIT_INST *inst_valu;
    if (CITP_CLEV == cli_mode) {
        inst_valu = (TOKIT_INST *) exten_ltype_tab;
        for (; -1 != inst_valu[0x00]; ++inst_valu) {
            if (inst_valu[0x00] == cinst->inst_levtyp) {
                chk_valu = chk_clev_lext(cinst, run_level);
                break;
            }
        }
    } else if (CITP_OSVB == cli_mode) {
        inst_valu = (TOKIT_INST *) exten_otype_tab;
        // printf("cinst->inst_levtyp:%d\n", cinst->inst_levtyp);
        for (; -1 != inst_valu[0x00]; ++inst_valu) {
            // printf("inst_valu[0x00]:%d\n", inst_valu[0x00]);
            if (inst_valu[0x00] == cinst->inst_levtyp) {
                chk_valu = 0x00;
                break;
            }
        }
    } else if (CITP_CLIE == cli_mode) {

    }
    // CLIT_PF("[FUNC]parse_iinstru_levivk chk_valu:%d\n", chk_valu);
    return chk_valu;
}

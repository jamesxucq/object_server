
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../cli_macro.h"
#include "../cinstru.h"
#include "../cli_struct.h"
#include "../cli_obje.h"

#include "parse_levivk.h"
#include "../debug_funct_sh.h"

// modify method
// "odb:createUser",
// "odb:runLevel",

static const struct stin_node lev1_levivk_dict[] = {
    {"post", LEVO_POST},
    {"list", LEVO_LIST},
    {"create", LEVO_CREAT},
    {"drop", LEVO_DROP},
    {"replace", LEVO_REPLA},
    {"integra", LEVO_INTEGRA},
    {"reload", LEVO_RELOAD},
    {NULL, LEVO_INVAL}
};

// modify method
static const struct ssin_node lv2p_levivk_dict[] = {
    {"odb", "post", LVTP_POST},
    {"odb", "list", LVTP_LIST},
    {"odb", "create", LVTP_CREAT},
    {"odb", "drop", LVTP_DROP},
    {"odb", "replace", LVTP_REPLA},
    {"odb", "integra", LVTP_INTEGRA},
    {"odb", "reload", LVTP_RELOAD},
    {NULL, NULL, LVTP_INVAL}
};

// modify method

static const struct stin_node lev3_levivk_dict[] = {
    {"post", LEVT_POST},
    {"echo", LEVT_ECHO},
    {"create", LEVT_CREAT},
    {"drop", LEVT_DROP},
    {"update", LEVT_UPDAT},
    {"insert", LEVT_INSER},
    {"search", LEVT_SEARO},
    {"invoke", LEVT_INVOK},
    {NULL, LEVT_INVAL}
};

static const struct stin_node lev3_echo_dict[] = {
    {"objid", EEHI_OBJID},
    {"name", EEHI_NAME},
    {"attrib", EEHI_ATTRIB},
    {"statis", EEHI_STATIS},
    {NULL, EEHI_INVAL}
};

// modify method

static const struct ssin_node lv4p_levivk_dict[] = {
    {"odb", "post", LVFP_POST},
    {"odb", "echo", LVFP_ECHO},
    {"odb", "create", LVFP_CREAT},
    {"odb", "drop", LVFP_DROP},
    {"odb", "search", LVFP_SEARQ},
    {"odb", "update", LVFP_UPDAT},
    {"odb", "insert", LVFP_INSER},
    {"odb", "invoke", LVFP_INVOK},
    {"odb", "factory", LVFP_FACTO},
    {NULL, NULL, LVFP_INVAL}
};

//

static const struct stin_node lv4p_echo_dict[] = {
    {"objid", QEHI_OBJID},
    {"name", QEHI_NAME},
    {"attrib", QEHI_ATTRIB},
    {"statis", QEHI_STATIS},
    {NULL, QEHI_INVAL}
};

//

static int parse_cont_level(cli_inst *cinst, uint32 run_level) {
    CLIEPF("[FUNC]:parse_cont_level cont_levivk:%s:%s run_level:%08X\n", cinst->obje_iden, cinst->cont_levivk, run_level);
    int cont_valu = 0x00;
    switch (cinst->inst_levtyp) {
        case INST_LEVO:
            KV_STIN_EQUA(cinst->inst_levivk, lev1_levivk_dict, cinst->cont_levivk)
            break;
        case INST_LVTP:
            KKV_SSIN_EQUA(cinst->inst_levivk, lv2p_levivk_dict, cinst->obje_iden, cinst->cont_levivk)
            break;
        case INST_LEVT:
            if (LEVEL_EXTEND_SPACE & run_level) {
                CLIEPF("_leve_defa_obje_.obje_iden:|%s|\n", _leve_defa_obje_.obje_iden);
                CLIEPF("cinst->obje_iden:|%s|\n", cinst->obje_iden);
                if (strcmp(_leve_defa_obje_.obje_iden, cinst->obje_iden)) cont_valu = -1;
            }
            KV_STIN_EQUA(cinst->inst_levivk, lev3_levivk_dict, cinst->cont_levivk)
            if (LEVT_ECHO == cinst->inst_levivk)
                KV_STIN_EQUA(cinst->inst_invok, lev3_echo_dict, cinst->cont_invok);
            break;
        case INST_LVFP:
            KKV_SSIN_EQUA(cinst->inst_levivk, lv4p_levivk_dict, cinst->obje_iden, cinst->cont_levivk)
            if (LVFP_ECHO == cinst->inst_levivk)
                KV_STIN_EQUA(cinst->inst_invok, lv4p_echo_dict, cinst->cont_invok);
            break;
        case INST_INVAL:
        default:
            _LOG_WARN("default: inst_levtyp");
            cont_valu = -1;
            break;
    }
    //
    CLIEPF("parse_cont_level inst_levivk:%d reserved:%d cont_valu:%d\n", cinst->inst_levivk, cinst->reserved, cont_valu);
    return cont_valu;
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
static const struct ssii_node osvb_osev_dict[] = {
    {"open", "command", OSEV_COMAND, CMDI_OPEN},
    {"close", "command", OSEV_COMAND, CMDI_CLOSE},
    {"echo", "status", OSEV_STATU, STAI_ECHO},
    {"status", "status", OSEV_STATU, STAI_STATUS},
    {"statis", "status", OSEV_STATU, STAI_STATIS},
    {"list", "privile", OSEV_PRIVI, PRII_LIST},
    {"role", "privile", OSEV_PRIVI, PRII_ROLE},
    {"user", "privile", OSEV_PRIVI, PRII_USER},
    {NULL, OSEV_INVAL, PRII_INVAL | STAI_INVAL | CMDI_INVAL}
};

//
static const struct ssii_node osvb_base_dict[] = {
    {"open", "command", BASE_COMAND, CMDI_OPEN},
    {"close", "command", BASE_COMAND, CMDI_CLOSE},
    {"echo", "status", BASE_STATU, STAI_ECHO},
    {"status", "status", BASE_STATU, STAI_STATUS},
    {"statis", "status", BASE_STATU, STAI_STATIS},
    {"list", "privile", BASE_PRIVI, PRII_LIST},
    {"role", "privile", BASE_PRIVI, PRII_ROLE},
    {"user", "privile", BASE_PRIVI, PRII_USER},
    {NULL, BASE_INVAL, PRII_INVAL | STAI_INVAL | CMDI_INVAL}
};

// 0:success -1:error

static int parse_osvb_level(cli_inst *cinst) {
    CLIEPF("[FUNC]:parse_osvb_level\n");
    CLIEPF("cont_levivk:|%s|\n", cinst->cont_levivk);
    int osvb_valu = 0x00;
    //
    switch (cinst->inst_levtyp) {
        case INST_OSEV:
            KKVV_SSII_EQUA(cinst->inst_levivk, cinst->inst_invok, osvb_osev_dict, cinst->cont_invok, cinst->cont_levivk)
            break;
        case INST_BASE:
            KKVV_SSII_EQUA(cinst->inst_levivk, cinst->inst_invok, osvb_base_dict, cinst->cont_invok, cinst->cont_levivk)
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

static int parse_clie_level(cli_inst *cinst) {
    CLIEPF("[FUNC]:parse_clie_level\n");
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

int parse_iinstru_levivk(cli_inst *cinst, uint32 cli_mode, uint32 run_level) {
    CLIEPF("[FUNC]:parse_iinstru_levivk\n");
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
                        chk_valu = parse_cont_level(cinst, run_level);
                    break;
                }
            }
            break;
        default:
            _LOG_WARN("default: cli_mode");
            chk_valu = -1;
            break;
    }
    CLIEPF("[FUNC]parse_iinstru_levivk chk_valu:%d\n", chk_valu);
    return chk_valu;
}

//

static const TOKIT_INST lev1_exten_tab[] = {
    KITS_LOAD,
    KITS_SAVE,
    KITS_CONVE,
    KITS_FORMAT,
    -1
};

static const TOKIT_INST lev2p_exten_tab[] = {
    KITS_LIST,
    KITS_LOAD,
    KITS_SAVE,
    KITS_CONVE,
    KITS_FORMAT,
    KITS_EXPAND,
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

static int chk_clev_lext(cli_inst *cinst, uint32 run_level) {
    CLIEPF("[FUNC]:chk_clev_lext run_level:%08X\n", run_level);
    CLIEPF("comd_cont:%s:%s\n", cinst->obje_iden, cinst->cont_levivk);
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
    KITS_CONVE,
    KITS_PRETTY,
    KITS_KEYVAL,
    KITS_FORMAT,
    KITS_EXPAND,
    -1
};

static const TOKIT_INST exten_otype_tab[] = {
    KITS_FORMAT,
    -1
};

// 0:success -1:error

int parse_kinstru_levivk(cli_inst *cinst, uint32 cli_mode, uint32 run_level) {
    CLIEPF("[FUNC]:parse_kinstru_levivk\n");
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
        for (; -1 != inst_valu[0x00]; ++inst_valu) {
            if (inst_valu[0x00] == cinst->inst_levtyp) {
                chk_valu = 0x00;
                break;
            }
        }
    } else if (CITP_CLIE == cli_mode) {

    }
    // CLIEPF("[FUNC]parse_iinstru_levivk chk_valu:%d\n", chk_valu);
    return chk_valu;
}

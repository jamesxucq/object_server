
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "../cli_macro.h"
#include "../cstri_utili.h"
#include "../cli_struct.h"
#include "../cli_bzl.h"

#include "defaul_objide.h"
#include "parse_ilevoi.h"
#include "../debug_funct_sh.h"

//

static char *split_instru_oili(char *objide, char *levivk, char *invok, char *coline, uint32 cli_mode, uint32 run_level) {
    // CLIEPF("[FUNC]split_instru_oili\n");
    char *pase_tok = pass_blank(coline);
    if (!pase_tok) return NULL;
    // INVA_OLITYP:error  INVOK_INSTRU_OLITYP:only invok / command; OBJE_INVOK_OLITYP:object invok; 
    // LEVE_INVOK_OLITYP:object level invok; OBJE_LEVIVK_OLITYP:level invok
    switch (inst_lvikoi_type(pase_tok)) {
        case INVOK_INSTRU_OLITYP:
            CLIEPF("INVOK_INSTRU_OLITYP\n");
            filli_defau_objid(objide, cli_mode, run_level);
            // CLIEPF("cmd pase_tok:|%s|\n", pase_tok);
            pase_tok = split_levivk_space(levivk, pase_tok);
            // CLIEPF("cmd pase_tok:|%s|\n", pase_tok);
            break;
        case OBJE_INVOK_OLITYP:
            CLIEPF("OBJE_INVOK_OLITYP\n");
            // CLIEPF("method pase_tok:|%s|\n", pase_tok);
            pase_tok = split_objide_levivk(objide, levivk, pase_tok);
            if ((CITP_OSVB == cli_mode) && !valid_osev_objide(objide))
                filli_osev_objide(objide, levivk, invok);
            // CLIEPF("method pase_tok:|%s|\n", pase_tok);
            break;
        case LEVE_INVOK_OLITYP:
            CLIEPF("LEVE_INVOK_OLITYP\n");
            filli_defau_objid(objide, cli_mode, run_level);
            // CLIEPF("cmd pase_tok:|%s|\n", pase_tok);
            pase_tok = split_levivk_invok(levivk, invok, pase_tok);
            // CLIEPF("cmd pase_tok:|%s|\n", pase_tok);
            break;
        case OBJE_LEVIVK_OLITYP:
            CLIEPF("OBJE_LEVIVK_OLITYP\n");
            pase_tok = decod_objide_levivk(objide, levivk, invok, pase_tok);
            break;
        case INVA_OLITYP:
        default:
            CLIEPF("inst_lvikoi_type\n");
            pase_tok = NULL;
            break;
    }
    //
    return pase_tok;
}

//

static const struct ssii_node cli_clie_dict[] = {
    {"clie", "conne", INST_CONNE, ATTRI_INSTRUC},
    {"clie", "exit", INST_EXIT, ATTRI_INSTRUC},
    {"clie", "bye", INST_BYE, ATTRI_INSTRUC},
    {NULL, NULL, INST_CLIINF, ATTRI_INVALID}
};

//

static const struct ssii_node cli_osvb_dict[] = {
    {"clie", "exit", INST_EXIT, ATTRI_INSTRUC},
    {"clie", "use", INST_USE, ATTRI_INSTRUC},
    {"clie", "quit", INST_QUIT, ATTRI_INSTRUC},
    {NULL, NULL, INST_INVAL, ATTRI_INVALID}
};

//

void build_osvb_levtyp(cli_inst *cinst) {
    if (!strcmp(OSEV_DEFAULT_VALUE, cinst->obje_iden)) {
        cinst->inst_levtyp = INST_OSEV;
        cinst->inst_attrib = ATTRI_INSTRUC;
    } else if (!strcmp(BASE_DEFAULT_VALUE, cinst->obje_iden)) {
        cinst->inst_levtyp = INST_BASE;
        cinst->inst_attrib = ATTRI_INSTRUC;
    } else {
        cinst->inst_levtyp = INST_INVAL;
        cinst->inst_attrib = ATTRI_INVALID;
    }
}

//

static const struct ssii_node cli_clev_dict[] = {
    {"clie", "level", INST_CLILEV, ATTRI_INSTRUC},
    {"clie", "quit", INST_QUIT, ATTRI_INSTRUC},
    {NULL, NULL, INST_INVAL, ATTRI_INVALID}
};

void build_clev_levtyp(cli_inst *cinst, uint32 run_level) {
    switch (ONLY_LEVEL_VALUE(run_level)) {
        case LVTP_ONE:
            cinst->inst_levtyp = INST_LEVO;
            cinst->inst_attrib = ATTRI_INSTRUC;
            break;
        case LVTP_TWOP:
            cinst->inst_levtyp = INST_LVTP;
            cinst->inst_attrib = ATTRI_INSTRUC;
            break;
        case LVTP_THRE:
            cinst->inst_levtyp = INST_LEVT;
            cinst->inst_attrib = ATTRI_INSTRUC;
            break;
        case LVTP_FOUP:
            cinst->inst_levtyp = INST_LVFP;
            cinst->inst_attrib = ATTRI_INSTRUC;
            break;
        default:
            cinst->inst_levtyp = INST_INVAL;
            cinst->inst_attrib = ATTRI_INVALID;
            _LOG_WARN("default: run_level");
            break;
    }
}

//

char *parse_iinstru_levoi(cli_inst *cinst, uint32 cli_mode, uint32 run_level) {
    char *pase_tok = split_instru_oili((char *) cinst->obje_iden, cinst->cont_levivk, cinst->cont_invok, cinst->coline, cli_mode, run_level);
    if (!pase_tok) return NULL;
    // CLIEPF("[FUNC]parse_iinstru_levoi, cli_mode:%d cmd:|%s|\n", cli_mode, cinst->comd_cont);
    if (CITP_CLEV == cli_mode) {
        KKVV_SSII_EQUA(cinst->inst_levtyp, cinst->inst_attrib, cli_clev_dict, cinst->obje_iden, cinst->cont_levivk)
        if (INST_INVAL == cinst->inst_levtyp)
            build_clev_levtyp(cinst, run_level);
    } else if (CITP_OSVB == cli_mode) {
        KKVV_SSII_EQUA(cinst->inst_levtyp, cinst->inst_attrib, cli_osvb_dict, cinst->obje_iden, cinst->cont_levivk)
        if (INST_INVAL == cinst->inst_levtyp)
            build_osvb_levtyp(cinst);
    } else if (CITP_CLIE == cli_mode) {
        KKVV_SSII_EQUA(cinst->inst_levtyp, cinst->inst_attrib, cli_clie_dict, cinst->obje_iden, cinst->cont_levivk)
    }
    //
    CLIEPF("[FUNC]parse_iinstru_levoi, obje_iden:|%s| cont_levivk:|%s| cont_invok:|%s|\n", cinst->obje_iden, cinst->cont_levivk, cinst->cont_invok);
    return pase_tok;
}


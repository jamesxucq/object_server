
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "../cli_macro.h"
#include "../cstri_utili.h"
#include "../cli_struct.h"
#include "../cli_bzl.h"

#include "defaul_objide.h"
#include "parse_klevoi.h"
#include "../debug_funct_sh.h"

//

static char *split_instru_util(char *objide, char *levivk, char *invok, char *line_str, uint32 cli_mode, uint32 run_level) {
    char *pase_tok = pass_blank(line_str);
    if (!pase_tok) return NULL;
    // INVA_OLITYP:error  INVOK_INSTRU_OLITYP:only invok / command; OBJE_INVOK_OLITYP:object invok; 
    // LEVE_INVOK_OLITYP:object level invok; OBJE_LEVIVK_OLITYP:level invok
    switch (inst_lvikoi_type(pase_tok)) {
        case INVOK_INSTRU_OLITYP:
            filli_defau_objid(objide, cli_mode, run_level);
            // CLIEPF("cmd pase_tok:|%s|\n", pase_tok);
            pase_tok = split_levivk_space(levivk, pase_tok);
            // CLIEPF("cmd pase_tok:|%s|\n", pase_tok);
            break;
        case OBJE_INVOK_OLITYP:
            // CLIEPF("method pase_tok:|%s|\n", pase_tok);
            pase_tok = split_objide_levivk(objide, levivk, pase_tok);
            if ((CITP_OSVB == cli_mode) && !valid_osev_objide(objide))
                filli_osev_objide(objide, levivk, invok);
            // CLIEPF("method pase_tok:|%s|\n", pase_tok);
            break;
        case LEVE_INVOK_OLITYP:
            filli_defau_objid(objide, cli_mode, run_level);
            // CLIEPF("cmd pase_tok:|%s|\n", pase_tok);
            pase_tok = split_levivk_invok(levivk, invok, pase_tok);
            // CLIEPF("cmd pase_tok:|%s|\n", pase_tok);
            break;
        case OBJE_LEVIVK_OLITYP:
            pase_tok = decod_objide_levivk(objide, levivk, invok, pase_tok);
            break;
        case INVA_OLITYP:
        default:
            pase_tok = NULL;
            break;
    }
    //
    return pase_tok;
}

//

static const struct ssii_node leve_tokit_dict[] = {
    {"kits", "list", KITS_LIST, ATTRI_TOOLKIT},
    {"kits", "load", KITS_LOAD, ATTRI_TOOLKIT},
    {"kits", "save", KITS_SAVE, ATTRI_TOOLKIT},
    {"kits", "convert", KITS_CONVE, ATTRI_TOOLKIT},
    {"kits", "pretty", KITS_PRETTY, ATTRI_TOOLKIT},
    {"kits", "key_value", KITS_KEYVAL, ATTRI_TOOLKIT},
    {"kits", "format", KITS_FORMAT, ATTRI_TOOLKIT},
    {"kits", "expand", KITS_EXPAND, ATTRI_TOOLKIT},
    {NULL, NULL, KITS_INVAL, ATTRI_INVALID}
};

static const struct ssii_node osev_tokit_dict[] = {
    {"kits", "format", KITS_FORMAT, ATTRI_TOOLKIT},
    {NULL, NULL, KITS_INVAL, ATTRI_INVALID}
};

char *parse_kinstru_levoi(cli_inst *cinst, uint32 cli_mode, uint32 run_level) {
    CLIEPF("[FUNC]:parse_kinstru_levoi\n");
    CLIEPF("cli_mode:%d cinst->coline:|%s|\n", cli_mode, cinst->coline);
    char *pase_tok = split_instru_util((char *) cinst->obje_iden, cinst->cont_levivk, cinst->cont_invok, cinst->coline, cli_mode, run_level);
    if (!pase_tok) return NULL;
    CLIEPF("obje_iden:|%s| cont_levivk:|%s|\n", cinst->obje_iden, cinst->cont_levivk);
    if (CITP_CLEV == cli_mode) {
        KKVV_SSII_EQUA(cinst->inst_levtyp, cinst->inst_attrib, leve_tokit_dict, cinst->obje_iden, cinst->cont_levivk)
        cinst->inst_levivk = -1;
    } else if (CITP_OSVB == cli_mode) {
        KKVV_SSII_EQUA(cinst->inst_levtyp, cinst->inst_attrib, osev_tokit_dict, cinst->obje_iden, cinst->cont_levivk)
        cinst->inst_levivk = -1;
    } else if (CITP_CLIE == cli_mode) {
        return NULL;
    }
    //
    CLIEPF("[FUNC]parse_kinstru_levoi, cmde_valu:%d line_str:|%s|\n", cinst->inst_levtyp, cinst->coline);
    return pase_tok;
}

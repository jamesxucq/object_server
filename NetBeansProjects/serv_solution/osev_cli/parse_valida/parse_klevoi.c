
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "../clit_macro.h"
#include "../cstri_utili.h"
#include "../clit_struct.h"
#include "../clit_bzl.h"

#include "defaul_objide.h"
#include "parse_klevoi.h"
#include "../debug_funct_sh.h"

//

static const struct ssii_node leve_tokit_dict[] = {
    {"kits", "list", KITS_LIST, ATTRI_TOOLKIT},
    {"kits", "load", KITS_LOAD, ATTRI_TOOLKIT},
    {"kits", "save", KITS_SAVE, ATTRI_TOOLKIT},
    {"kits", "translate", KITS_TRANS, ATTRI_TOOLKIT},
    {"kits", "pretty", KITS_PRETTY, ATTRI_TOOLKIT},
    {"kits", "key_value", KITS_KEYVAL, ATTRI_TOOLKIT},
    {"kits", "format", KITS_FORMAT, ATTRI_TOOLKIT},
    {"kits", "explain", KITS_EXPLAIN, ATTRI_TOOLKIT},
    {NULL, NULL, KITS_INVAL, ATTRI_INVALID}
};

static const struct ssii_node osvb_tokit_dict[] = {
    {"kits", "format", KITS_FORMAT, ATTRI_TOOLKIT},
    {NULL, NULL, KITS_INVAL, ATTRI_INVALID}
};

char *parse_kinstru_levoi(clit_inst *cinst, uint32 cli_mode) {
    CLIT_PF("[FUNC]:parse_kinstru_levoi\n");
    CLIT_PF("cli_mode:%d cinst->coline:|%s|\n", cli_mode, cinst->coline);
    char *pase_tok = split_objide_levivk((char *) cinst->obje_iden, cinst->cont_levivk, cinst->coline);
    if (!pase_tok) return NULL;
    CLIT_PF("obje_iden:|%s| cont_levivk:|%s|\n", cinst->obje_iden, cinst->cont_levivk);
    if (CITP_CLEV == cli_mode) {
        KKVV_SSII_EQUA(cinst->inst_levtyp, cinst->inst_attrib, leve_tokit_dict, cinst->obje_iden, cinst->cont_levivk)
        cinst->inst_levivk = -1;
    } else if (CITP_OSVB == cli_mode) {
        KKVV_SSII_EQUA(cinst->inst_levtyp, cinst->inst_attrib, osvb_tokit_dict, cinst->obje_iden, cinst->cont_levivk)
        cinst->inst_levivk = -1;
    } else if (CITP_CLIE == cli_mode) {
        return NULL;
    }
    //
    CLIT_PF("[FUNC]parse_kinstru_levoi, cmde_valu:%d line_str:|%s|\n", cinst->inst_levtyp, cinst->coline);
    return pase_tok;
}

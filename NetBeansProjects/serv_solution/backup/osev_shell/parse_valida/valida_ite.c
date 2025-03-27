

#include "../cli_struct.h"
#include "../cinstru.h"
#include "parse_ilevoi.h"
#include "parse_klevoi.h"
#include "pretr_check.h"
#include "conve_lvikoi.h"
#include "parse_levivk.h"
#include "split_pamvs.h"

#include "valida_ite.h"
#include "../debug_funct_sh.h"

static int parse_valid_instruc(cli_inst *cinst, uint32 cli_mode, uint32 run_level) {
    char *pase_tok = parse_iinstru_levoi(cinst, cli_mode, run_level);
    if (!pase_tok) {
        CliePrintErro("Read method error!", -1);
        return -1;
    }
    // PRIN_cli_instru(cinst);
    if (-1 == pretr_check_instru(cinst, cli_mode, run_level)) {
        CliePrintErro("Pretreat check error!", -1);
        return -1;
    }
    //
    char *conve_tok = conve_instru_lvikoi(cinst, cli_mode, run_level);
    if (conve_tok) pase_tok = conve_tok;
    if (-1 == parse_iinstru_levivk(cinst, cli_mode, run_level)) {
        CliePrintErro("Object or Method not found!", -1);
        return -1;
    }
    PRIN_cli_instru(cinst);
    if (-1 == split_instru_pamvus(cinst->pamcon, cinst->_pline_, pase_tok)) {
        CliePrintErro("Parse param error!", -1);
        return -1;
    }
    CLIEPF("parse_valid_instruc, comd_cont:%s:%s\n", cinst->obje_iden, cinst->cont_levivk);
    //
    return 0x00;
}

static int parse_valid_toolkit(cli_inst *cinst, uint32 cli_mode, uint32 run_level) {
    char *pase_tok = parse_kinstru_levoi(cinst, cli_mode, run_level);
    if (!pase_tok) {
        CliePrintErro("Read method error!", -1);
        return -1;
    }
    if (-1 == parse_kinstru_levivk(cinst, cli_mode, run_level)) {
        CliePrintErro("Method not found!", -1);
        return -1;
    }
    if (-1 == split_instru_pamvus(cinst->pamcon, cinst->_pline_, pase_tok)) {
        CliePrintErro("Parse param error!", -1);
        return -1;
    }
    CLIEPF("valid_toolkit, cinst->coline:|%s|\n", cinst->coline);
    //
    return 0x00;
}

//

// obje:search() | clie:pretty("iih"); // fixme
// odb:list() | kits:convert(GCC); // fixme
// odb:list() | kits:convert("xxxx.cpp", MSVC); // fixme
// odb:list() | kits:convert("xxx.java"); // fixme
#define TOOLKIT_TOK  "kits:"

int valid_instru_type(char *comd_line, char *cline_stri) {
    strcpy(comd_line, pass_blank(cline_stri));
    int type_valu = 0x00;
    if (qstrst(cline_stri, TOOLKIT_TOK)) type_valu = 0x01;
    return type_valu;
}

//

int parse_valida_ite(cli_inst *cinst, char *inst_stri, clie_stat_t *cli_stat) {
    int chk_valu = 0x00;
    CLIEPF("[FUNC] parse_valida_ite inst_stri:|%s|\n", inst_stri);
    //
    if (valid_instru_type(cinst->coline, inst_stri)) {
        CLIEPF("utility coline:|%s|\n", cinst->coline);
        chk_valu = parse_valid_toolkit(cinst, cli_stat->cli_mode, cli_stat->run_level);
    } else {
        CLIEPF("coline:|%s|\n", cinst->coline);
        chk_valu = parse_valid_instruc(cinst, cli_stat->cli_mode, cli_stat->run_level);
    }
    // CLIEPF("chk_valu:%d\n", chk_valu);
    return chk_valu;
}

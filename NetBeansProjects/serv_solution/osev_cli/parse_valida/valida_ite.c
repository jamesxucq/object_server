

#include "../clit_struct.h"
#include "../cinstru.h"
#include "parse_ilevoi.h"
#include "parse_klevoi.h"
#include "pretr_check.h"
#include "conve_lvikoi.h"
#include "parse_levivk.h"
#include "split_pamvs.h"

#include "valida_ite.h"
#include "../debug_funct_sh.h"

//

static int parse_valid_instruc(clit_inst *cinst, uint32 cli_mode, uint32 run_level) {
    char *pase_tok = parse_iinstru_levoi(cinst, cli_mode, run_level);
    if (!pase_tok) {
        ClitPrintErro("Read method error!", -1);
        return -1;
    }
    // PRIN_clit_instru(cinst); convert default objid
    if (-1 == pretr_check_instru(cinst, cli_mode, run_level)) {
        ClitPrintErro("Pretreat check error!", -1);
        return -1;
    }
    char *conve_tok = conve_instru_lvikoi(cinst, cli_mode, run_level);
    if (conve_tok) pase_tok = conve_tok;
    if (-1 == pretr_check_instru(cinst, cli_mode, run_level)) {
        ClitPrintErro("Later check error!", -1);
        return -1;
    }
    // levivk invok
    if (-1 == parse_iinstru_levivk(cinst, cli_mode)) {
        ClitPrintErro("Object or Method not found!", -1);
        return -1;
    }
    // pamvus
    if (-1 == split_instru_pamvus(cinst->pamcon, cinst->_pline_, pase_tok)) {
        ClitPrintErro("Parse param error!", -1);
        return -1;
    }
    PRIN_clit_instru(cinst);
    CLIT_PF("parse_valid_instruc, comd_cont:%s:%s\n", cinst->obje_iden, cinst->cont_levivk);
    //
    return 0x00;
}

static int parse_valid_toolkit(clit_inst *cinst, uint32 cli_mode, uint32 run_level) {
    char *pase_tok = parse_kinstru_levoi(cinst, cli_mode);
    if (!pase_tok) {
        ClitPrintErro("Read method error!", -1);
        return -1;
    }
    if (-1 == parse_kinstru_levivk(cinst, cli_mode, run_level)) {
        ClitPrintErro("Method not found!", -1);
        return -1;
    }
    // PRIN_clit_instru(cinst);
    if (-1 == split_instru_pamvus(cinst->pamcon, cinst->_pline_, pase_tok)) {
        ClitPrintErro("Parse param error!", -1);
        return -1;
    }
    CLIT_PF("valid_toolkit, cinst->coline:|%s|\n", cinst->coline);
    //
    return 0x00;
}

//

// obje:search() | clie:pretty("iih"); // fixme
// kits:list() | kits:translate(GCC); // fixme
// kits:list() | kits:translate("xxxx.cpp", MSVC); // fixme
// kits:list() | kits:translate("xxx.java"); // fixme
#define TOOLKIT_TOK  "kits:"

int valid_instru_type(char *comd_line, char *cline_stri) {
    strcpy(comd_line, pass_blank(cline_stri));
    int type_valu = 0x00;
    if (qstrst(cline_stri, TOOLKIT_TOK)) type_valu = 0x01;
    return type_valu;
}

//

int parse_valida_ite(clit_inst *cinst, char *inst_stri, clit_stat_t *clit_stat) {
    int chk_valu = 0x00;
    CLIT_PF("[FUNC] parse_valida_ite inst_stri:|%s|\n", inst_stri);
    //
    if (valid_instru_type(cinst->coline, inst_stri)) {
        CLIT_PF("utility coline:|%s|\n", cinst->coline);
        chk_valu = parse_valid_toolkit(cinst, clit_stat->cli_mode, clit_stat->run_level);
    } else {
        CLIT_PF("instruc coline:|%s|\n", cinst->coline);
        chk_valu = parse_valid_instruc(cinst, clit_stat->cli_mode, clit_stat->run_level);
    }
    // CLIT_PF("chk_valu:%d\n", chk_valu);
    return chk_valu;
}

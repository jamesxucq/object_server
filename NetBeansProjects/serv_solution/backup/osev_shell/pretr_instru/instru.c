#include "commo_header.h"

#include "../cli_macro.h"
#include "../cli_struct.h"
#include "../cinstru.h"
#include "instr_pretr.h"

#include "instru.h"
#include "../debug_funct_sh.h"

// 0:ok -1:err

int pretr_instruct_comd(cli_inst *cinst, uint32 run_level) {
    CLIEPF("[FUNC]:pretr_instruct_comd, cinst->inst_levtyp:%u\n", cinst->inst_levtyp);
    int hand_valu = 0x00;
    //
    switch (cinst->inst_levtyp) {
        case INST_INVAL:
        case INST_CONNE:
            break;
        case INST_USE:
            hand_valu = check_clie_use((char **) cinst->pamcon);
            break;
        case INST_OSEV:
            hand_valu = pretr_osev_inten(cinst->obje_iden, cinst->inst_levivk, cinst->inst_invok, (char **) cinst->pamcon, cinst->_pline_);
            break;
        case INST_BASE:
            hand_valu = pretr_base_inten(cinst->obje_iden, cinst->inst_levivk, cinst->inst_invok, (char **) cinst->pamcon, cinst->_pline_);
            break;
        case INST_LEVO:
            hand_valu = pretr_cont_levon(run_level, cinst->inst_levivk, (char **) cinst->pamcon, cinst->_pline_);
            break;
        case INST_LVTP:
            hand_valu = pretr_cont_levtp(cinst->inst_levivk, (char **) cinst->pamcon, cinst->_pline_);
            break;
        case INST_LEVT:
            hand_valu = pretr_cont_levth(run_level, cinst->inst_levivk, (char **) cinst->pamcon, cinst->_pline_);
            break;
        case INST_LVFP:
            hand_valu = pretr_cont_levfp(cinst->inst_levivk, (char **) cinst->pamcon, cinst->_pline_);
            break;
        default:
            // _LOG_WARN("default: inst_levtyp");
            break;
    }
    CLIEPF("[FUNC]handle_method hand_valu:%d\n", hand_valu);
    return hand_valu;
}


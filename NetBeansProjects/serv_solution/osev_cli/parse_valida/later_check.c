
#include "commo_header.h"
#include "../clit_bzl.h"

#include "later_check.h"
#include "../debug_funct_sh.h"

//

static int ltchk_cont_level(clit_inst *cinst, uint32 run_level) {
    int leve_valu = -1;
    CLIT_PF("[FUNC]:ltchk_cont_level run_level:%08X\n", run_level);
    switch (ONLY_LEVEL_VALUE(run_level)) {
        case LVTP_ONE:
        case LVTP_TWOP:
            leve_valu = 0x00;
            break;
        case LVTP_THRE:
            if (LEVEL_EXTEND_SPACE & run_level) {
                CLIT_PF("_leve_defa_obje_.obje_iden:|%s|\n", _leve_defa_obje_.obje_iden);
                CLIT_PF("cinst->obje_iden:|%s|\n", cinst->obje_iden);
                if (!strcmp(_leve_defa_obje_.obje_iden, cinst->obje_iden))
                    leve_valu = 0x00;
            } else if (!strcmp(BASE_DEFAULT_VALUE, cinst->obje_iden)) {
                leve_valu = 0x00;
            }
            break;
        case LVTP_FOUP:
            leve_valu = 0x00;
            break;
        default:
            _LOG_WARN("default: run_level");
            leve_valu = -1;
            break;
    }
    //
    CLIT_PF("leve_valu:%d\n", leve_valu);
    return leve_valu;
}

// later

int later_check_instru(clit_inst *cinst, uint32 cli_mode, uint32 run_level) {
    int chk_valu = -1;
    //
    switch (cli_mode) {
        case CITP_CLIE:
        case CITP_OSVB:
            chk_valu = 0x00;
            break;
        case CITP_CLEV:
            chk_valu = 0x00;
            if (INST_LVFP == cinst->inst_levtyp
                    || INST_LEVT == cinst->inst_levtyp
                    || INST_LVTP == cinst->inst_levtyp
                    || INST_LEVO == cinst->inst_levtyp)
                chk_valu = ltchk_cont_level(cinst, run_level);
            break;
        default:
            _LOG_WARN("default: cli_mode");
            chk_valu = -1;
            break;
    }
    CLIT_PF("[FUNC]later_check_instru chk_valu:%d\n", chk_valu);
    return chk_valu;
}
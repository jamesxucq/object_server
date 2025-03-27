
#include "commo_header.h"
#include "../clit_bzl.h"

#include "pretr_check.h"
#include "../debug_funct_sh.h"

//

static int prchk_cont_level(clit_inst *cinst, uint32 run_level) {
    int leve_valu = -1;
    CLIT_PF("[FUNC]:prchk_cont_level run_level:%08X\n", run_level);
    switch (ONLY_LEVEL_VALUE(run_level)) {
        case LVTP_ONE:
            if (LEVEL_EXTEND_SPACE & run_level) {
                CLIT_PF("_leve_defa_obje_.obje_iden:|%s|\n", _leve_defa_obje_.obje_iden);
                CLIT_PF("cinst->obje_iden:|%s|\n", cinst->obje_iden);
                if (!strcmp(_leve_defa_obje_.obje_iden, cinst->obje_iden))
                    leve_valu = 0x00;
            } else if (!strcmp(BASE_DEFAULT_VALUE, cinst->obje_iden)) {
                leve_valu = 0x00;
            }
            break;
        case LVTP_TWOP:
            leve_valu = 0x00;
            break;
        case LVTP_THRE:
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

//
static const INSTRU leve_itype_tab[] = {
    INST_QUIT,
    INST_CLILEV,
    INST_LEVO,
    INST_LVTP,
    INST_LEVT,
    INST_LVFP,
    -1
};

// later

int pretr_check_instru(clit_inst *cinst, uint32 cli_mode, uint32 run_level) {
    int chk_valu = -1;
    INSTRU *inst_levtyp;
    //
    switch (cli_mode) {
        case CITP_CLIE:
        case CITP_OSVB:
            chk_valu = 0x00;
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
                        chk_valu = prchk_cont_level(cinst, run_level);
                    break;
                }
            }
            break;
        default:
            _LOG_WARN("default: cli_mode");
            chk_valu = -1;
            break;
    }
    CLIT_PF("[FUNC]pretr_check_instru chk_valu:%d\n", chk_valu);
    return chk_valu;
}
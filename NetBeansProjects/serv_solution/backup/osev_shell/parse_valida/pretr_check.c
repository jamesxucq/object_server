
#include "commo_header.h"
#include "../cli_bzl.h"

#include "pretr_check.h"
#include "../debug_funct_sh.h"

//

static int prchk_cont_level(cli_inst *cinst, uint32 run_level) {
    int leve_valu = -1;
    CLIEPF("[FUNC]:prchk_leve comd_cont:|%s:%s| run_level:%08X\n", cinst->obje_iden, cinst->cont_levivk, run_level);
    switch (ONLY_LEVEL_VALUE(run_level)) {
        case LVTP_ONE:
            if (LEVEL_EXTEND_SPACE & run_level) {
                CLIEPF("defa_obje:|%s| obje_iden:|%s|\n", _leve_defa_obje_.obje_iden, cinst->obje_iden);
                if (!strcmp(_leve_defa_obje_.obje_iden, cinst->obje_iden)) leve_valu = 0x00;
            }
            if (!strcmp(BASE_DEFAULT_VALUE, cinst->obje_iden)) leve_valu = 0x00;
            break;
        case LVTP_TWOP:
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
    CLIEPF("check_leve inst_levivk:%d reserved:%d leve_valu:%d\n", cinst->inst_levivk, cinst->reserved, leve_valu);
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

int pretr_check_instru(cli_inst *cinst, uint32 cli_mode, uint32 run_level) {
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
    CLIEPF("[FUNC]pretr_check chk_valu:%d\n", chk_valu);
    return chk_valu;
}
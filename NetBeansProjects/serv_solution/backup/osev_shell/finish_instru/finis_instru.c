#include "commo_header.h"

#include "../cinstru.h"
#include "../cli_struct.h"
#include "instru_utili.h"

#include "finis_instru.h"

// 0:ok -1:err

int finish_instru(cli_inst *cinst, clie_resu *resul) {
    switch (cinst->inst_levtyp) {
        case INST_CONNE:
        case INST_EXIT:
        case INST_BYE:
            break;
        case INST_CLIINF:
            clien_finis(resul, cinst->cont_levivk);
            break;
        case INST_USE:
        case INST_QUIT:
            break;
        case INST_OSEV:
            osev_finis(resul, cinst->inst_levivk);
            break;
        case INST_BASE:
            base_finis(resul, cinst->inst_levivk);
            break;
        case INST_CLILEV:
            break;
        case INST_LEVO:
        case INST_LVTP:
        case INST_LEVT:
        case INST_LVFP:
            level_finis(resul);
            break;
        default:
            _LOG_WARN("default: inst_levtyp:%u", cinst->inst_levtyp);
            break;
    }
    // CLIEPF("finish_instru hand_valu:%d\n", hand_valu);
    return 0x00;
}

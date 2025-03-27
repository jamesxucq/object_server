#include "commo_header.h"

#include "../cinstru.h"
#include "../cli_struct.h"
#include "tokit_utili.h"

#include "finis_tolkit.h"

//

int finish_tolkit(cli_inst *cinst, clie_resu *resul) {
    switch (cinst->inst_levtyp) {
        case KITS_LIST:
            list_finis(resul);
            break;
        case KITS_LOAD:
            load_finis(resul);
            break;
        case KITS_SAVE:
            save_finis(resul);
            break;
        case KITS_CONVE:
            conv_finis(resul);
            break;
        case KITS_PRETTY:
            prtyp_finis(resul);
            break;
        case KITS_KEYVAL:
            keyval_finis(resul);
            break;
        case KITS_FORMAT:
            formp_finis(resul);
            break;
        case KITS_EXPAND:
            expand_finis(resul);
            break;
        default:
            _LOG_WARN("default: inst_levtyp");
            break;
    }
    // CLIEPF("finish_instru hand_valu:%d\n", hand_valu);
    return 0x00;
}



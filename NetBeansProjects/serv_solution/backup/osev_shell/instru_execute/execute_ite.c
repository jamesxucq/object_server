
#include "../cli_macro.h"
#include "../cli_struct.h"
#include "../cinstru.h"
#include "execut_instru.h"
#include "../tokit_instru/execu_tokit_ite.h"

#include "execute_ite.h"
#include "../debug_funct_sh.h"

int instru_execute_ite(clie_resu *resul, clie_stat_t *cli_stat, cli_inst *cinst) {
    PRIN_instru(cinst);
    //
    if (ATTRI_INSTRUC & cinst->inst_attrib) {
        CLIEPF("************ EXECUTE MAJOR:|%s| ************\n", cinst->coline);
        if (execu_instru_comd(resul, cli_stat, cinst)) {
            CLIEPF("************ EXECUTE EXCEPTION! ************\n");
            return -1;
        }
    } else if (ATTRI_TOOLKIT & cinst->inst_attrib) {
        CLIEPF("************ EXECUTE KITS:|%s| ************\n", cinst->coline);
        if (execu_tolkit_ite(cinst, resul)) {
            CLIEPF("************ EXECUTE EXCEPTION! ************\n");
            return -1;
        }
    } else {
        CLIEPF("Command attribute exception!");
        CLIEPF("************ EXECUTE EXCEPTION! ************\n");
        return -1;
    }
    //
    CLIEPF("************ END EXECUTE ************\n");
    return 0x00;
}

#include "../clit_macro.h"
#include "../clit_struct.h"
#include "../cinstru.h"
#include "execut_instru.h"
#include "../tokit_instru/execu_tokit_ite.h"

#include "execute_ite.h"
#include "../debug_funct_sh.h"

int instru_execute_ite(clit_resu *resul, clit_stat_t *clit_stat, clit_inst *cinst) {
    PRIN_instru(cinst);
    //
    if (ATTRI_INSTRUC & cinst->inst_attrib) {
        CLIT_PF("************ EXECUTE MAJOR:|%s| ************\n", cinst->coline);
        if (execu_instru_comd(resul, clit_stat, cinst)) {
            CLIT_PF("************ EXECUTE EXCEPTION! ************\n");
            return -1;
        }
    } else if (ATTRI_TOOLKIT & cinst->inst_attrib) {
        CLIT_PF("************ EXECUTE KITS:|%s| ************\n", cinst->coline);
        if (execu_tolkit_ite(cinst, resul)) {
            CLIT_PF("************ EXECUTE EXCEPTION! ************\n");
            return -1;
        }
    } else {
        CLIT_PF("Command attribute exception!");
        CLIT_PF("************ EXECUTE EXCEPTION! ************\n");
        return -1;
    }
    //
    CLIT_PF("************ END EXECUTE ************\n");
    return 0x00;
}
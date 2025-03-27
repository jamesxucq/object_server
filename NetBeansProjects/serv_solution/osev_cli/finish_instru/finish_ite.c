#include "commo_header.h"

#include "../cinstru.h"
#include "../clit_struct.h"
#include "finis_instru.h"
#include "finis_tolkit.h"

#include "finish_ite.h"
#include "../debug_funct_sh.h"

///

int finish_instru_ite(clit_inst *cinst, clit_resu *resul) {
    if (ATTRI_INSTRUC & cinst->inst_attrib) {
        if (finish_instru(cinst, resul)) {
            CLIT_PF("Method finish error!");
            return -1;
        }
    } else if (ATTRI_TOOLKIT & cinst->inst_attrib) {
        if (finish_tolkit(cinst, resul)) {
            CLIT_PF("Toolkit finish error!");
            return -1;
        }
    } else {
        CLIT_PF("Finish attribute error!");
        return -1;
    }
    //
    return 0x00;
}



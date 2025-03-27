#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "third_party.h"
#include "kcomm_header.h"

#include "refre_utili.h"

//

int build_source_contp(contain **sconp, cont_lsmp *conda_stm, cont_versi *rcove) {
    unsigned int inde = 0x00;
    for (; (MAX_RSCON_COUNT > inde) && CHK_ZERO_COVE(rcove); ++inde, ++rcove, ++sconp) {
        sconp[0x00] = (contain *) cache_value(&rcove->lv4p_obid, conda_stm->lev3o_hm);
        if (!sconp[0x00]) return -1;
    }
    sconp[0x00] = NULL;
    //
    return 0x00;
}




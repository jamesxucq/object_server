
#include "commo_header.h"

#include "lev1_decla.h"
#include "lv2p_decla.h"

#include "lv2p_meta.h"

//

void dele_lv2pme(void *lv2me) {
    if (lv2me) {
        if (((lv2pme *) lv2me)->lv2expt)
            free_lv2exp(((lv2pme *) lv2me)->lv2expt);
        free(lv2me);
    }
}


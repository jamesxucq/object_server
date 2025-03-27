
#include <stdlib.h>

#include "lv2p_expan.h"
#include "parse_expand.h"

#include "../../debug_funct_sh.h"

//
#define CONST_LVTEXP(LVTEXPT) { \
        LVTEXPT = (lv2p_expa_t *) malloc(sizeof (lv2p_expa_t)); \
        if (!LVTEXPT) return NULL; \
    }
#define DESTR_LVTEXP(LVTEXPT) free(LVTEXPT);

//

#define CONST_LVTEXP_CONTENT(LVTEXPT) { \
    lv2expt->lv2nod = (lv2p_prop *) malloc(sizeof (lv2p_prop) * (0x01 + LVTEXPT->lv2o_coun)); \
    if (!lv2expt->lv2nod) { \
        free(lv2expt); \
        return NULL; \
    } \
    lv2expt->lv1dat = (lev1_decl_t *) malloc(sizeof (lev1_decl_t) * (0x01 + LVTEXPT->lv1d_coun)); \
    if (!lv2expt->lv1dat) { \
        free(lv2expt->lv2nod); \
        free(lv2expt); \
        return NULL; \
    } \
}

//

lv2p_expa_t *parse_lv2expt_bzl(char *lv2e_cont) {
    // CLIEPF("[FUNC]:parse_lv2expt_bzl\n");
    lv2p_expa_t *lv2expt;
    CONST_LVTEXP(lv2expt)
    if (!parse_lv2expt_count(lv2expt, lv2e_cont)) {
        DESTR_LVTEXP(lv2expt);
        return NULL;
    }
    // CLIEPF("lv2expt->lv2o_coun:%d lv2expt->lv1d_coun:%d\n", lv2expt->lv2o_coun, lv2expt->lv1d_coun);
    //
    CONST_LVTEXP_CONTENT(lv2expt)
    if (!parse_lv2expt_content(lv2expt, lv2e_cont)) {
        free_lv2exp(lv2expt);
        return NULL;
    }
    // PRIN_sh_lv2p_expa_t(lv2expt);
    return lv2expt;
}


// trans-serve
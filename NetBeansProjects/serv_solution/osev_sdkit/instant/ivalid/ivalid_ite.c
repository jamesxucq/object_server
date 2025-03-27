
#include "commo_header.h"
#include "kcomm_header.h"

#include "invok_bzl.h"

#include "ivalid_utili.h"

// lv2p check method  inheri integ legal

int valid_lv2pmi_ite(char *basen, lv2p_decl_t *lv2dt) {
    // OSEVPF("[FUNC]:valid_lv2pmi_ite\n");
    // OSEVPF("check the same lev1n.\n");
    lev1_decl_t *lv1d = lv2dt->meth;
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        // OSEVPF("----- lv1d->ident:|%s| levtyp:|%08X|\n", lv1d->ident, lv1d->levtyp);
        if (chk_same_lev1n(lv2dt->meth, lv1d))
            return -1;
    }
    // OSEVPF("integ_legal_ite, inher_legal_ite\n");
    lv1d = lv2dt->meth;
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        // OSEVPF("----- lv1d->ident:|%s| levtyp:|%08X|\n", lv1d->ident, lv1d->levtyp);
        if (integ_legal_ite(basen, lv1d))
            return -1;
        if (inher_legal_ite(basen, lv1d))
            return -1;
    }
    OSEVPF("PASSED, valid_creac_ite\n");
    return 0x00;
}

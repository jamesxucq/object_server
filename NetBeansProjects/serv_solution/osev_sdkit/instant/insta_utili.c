\
#include "commo_header.h"
#include "kcomm_header.h"
#include "conte_bzl.h"
#include "invok_bzl.h"

//

lv2pme *creat_lv2pm_insda(inst_hmap *insda_stm, base_valu *baval, lv2p_decl_t *lv2dt, char *lv2_dec) {
    OSEVPF("[FUNC]:creat_lv2pm_insda\n");
    OSEVPF("lv2_dec:|%s|\n", lv2_dec);
    lv2p_expa_t *lv2expt = mallo_lv2exp(LVTNOD_COUNT, LEVO_COUNT);
    if (!lv2expt) return NULL;
    if (cole_creat_bzl(lv2expt, baval->base_name, lv2dt)) {
        OSEVPF("Conve class excep!\n");
        free_lv2exp(lv2expt);
        return NULL;
    }
    REDUCE_LEVET_EXPANT(lv2expt);
    //
    osv_oid_t lv2p_obid;
    creat_class_obid(&lv2p_obid);
    lv2pme *lv2me = lv2in_lv2me_bzl(insda_stm, &baval->lv2pm_stm, lv2_dec, lv2expt, &lv2p_obid);
    if (!lv2me) {
        OSEVPF("Creat class meta excep!\n");
        free_lv2exp(lv2expt);
        return NULL;
    }
    //
    return lv2me;
}

// free_lv2exp(lv2expt);

lv2p_expa_t *creat_lv2pe_insda(base_valu *baval, lv2p_decl_t *lv2dt) {
    // OSEVPF("[FUNC]:creat_lv2pe_insda\n");
    lv2p_expa_t *lv2expt = mallo_lv2exp(LVTNOD_COUNT, LEVO_COUNT);
    if (!lv2expt) return NULL;
    if (cole_creat_bzl(lv2expt, baval->base_name, lv2dt)) {
        // OSEVPF("Conve class excep!\n");
        free_lv2exp(lv2expt);
        return NULL;
    }
    // OSEVPF("lv2expt->lv2o_coun:%d lv2expt->lv1d_coun:%d\n", lv2expt->lv2o_coun, lv2expt->lv1d_coun);
    // REDUCE_LEVET_EXPANT(lv2expt); // disable by james
    return lv2expt;
}





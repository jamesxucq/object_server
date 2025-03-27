#include "commo_header.h"
#include "kcomm_header.h"

#include "ivalid/ivalid_ite.h"
#include "invok_bzl.h"
#include "lv2in_utili.h"
#include "insta_utili.h"

#include "instda_obje.h"
#include "instda_bzl.h"

//

lv2pme *lv2me_interp_bzl(base_valu *baval, char *lv2_dec) {
    OSEVPF("[FUNC]:lv2me_interp_bzl\n");
    cachemap *lv2pao_hm = baval->lv2pm_stm.lv2pao_hm;
    inst_hmap *insda_stm = &baval->insda_stm;
    //
    instda *inst_lv2in = (instda *) action_value(lv2_dec, insda_stm->lv2pid_hm);
    lv2pme *inst_lv2me = (lv2pme *) action_value(lv2_dec, insda_stm->lv2pme_hm);
    if (inst_lv2me && inst_lv2in) { // check version
        inher_versi *invep = inst_lv2in->inhver;
        for (; NOT_INVER_ZERO(invep); ++invep) {
            lv2p_attri *lv2ai = (lv2p_attri *) cache_value(&invep->lv2p_obid, lv2pao_hm);
            if (!lv2ai || (invep->versio != lv2ai->versio))
                break;
        }
        if (IS_INVER_ZERO(invep))
            return inst_lv2me;
    }
    // OSEVPF("destr_lv2p_meta, destr_insta_data\n");
    if (inst_lv2me) destr_lv2p_meta(insda_stm, lv2_dec);
    if (inst_lv2in) destr_insta_data(insda_stm, lv2_dec);
    //
    lv2p_decl_t lv2dt;
    if (build_lv2pd_nonam(&lv2dt, lv2_dec, baval->base_name))
        return NULL;
    if (valid_lv2pmi_ite(baval->base_name, &lv2dt))
        return NULL;
    inst_lv2me = creat_lv2pm_insda(insda_stm, baval, &lv2dt, lv2_dec);
    if (!inst_lv2me) return NULL;
    //
    return inst_lv2me;
}

//

lv2p_expa_t *lv2expt_interp_bzl(base_valu *baval, char *lv2_dec) {
    // OSEVPF("[FUNC]:lv2expt_interp_bzl\n");
    lv2p_decl_t lv2dt;
    if (build_lv2pd_nonam(&lv2dt, lv2_dec, baval->base_name))
        return NULL;
    if (valid_lv2pmi_ite(baval->base_name, &lv2dt))
        return NULL;
    //
    lv2p_expa_t *lv2expt = creat_lv2pe_insda(baval, &lv2dt);
    if (!lv2expt) return NULL;
    //
    return lv2expt;
}
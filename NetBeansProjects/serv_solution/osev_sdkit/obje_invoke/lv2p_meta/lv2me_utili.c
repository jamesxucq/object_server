
#include "commo_header.h"
#include "kcomm_header.h"

// #include "leve_libr/lv2p_dlsym.h"
#include "lv2me_utili.h"
#include "instda.h"

// 

lv2pme *open_lv2p_meta(lv2pm_hmap *lv2pm_stm, osv_oid_t *lv2p_obid, char *lv2pn, lv2p_expa_t *lv2expt) {
    lv2pme *lv2me = mallo_lv2pme(lv2expt);
    if (!lv2me) return NULL;
    //
    OBID_BINARY_COPY(&(lv2me->lv2p_obid), lv2p_obid)
    strcpy(lv2me->lv2pn, lv2pn);
    //
    cache_insert(lv2me->lv2pn, lv2me, lv2pm_stm->lv2pmn_hm);
    cache_insert(&(lv2me->lv2p_obid), lv2me, lv2pm_stm->lv2pmo_hm);
    return lv2me;
}

// 0x00:hand refer zero. >0x00:refer number <0x00:error

int close_lv2p_meta(lv2pm_hmap *lv2pm_stm, osv_oid_t *lv2p_obid) {
    lv2pme *lv2me = (lv2pme *) cache_value(lv2p_obid, lv2pm_stm->lv2pmo_hm);
    if (!lv2me) return -1;
    //
    cache_remove(lv2me->lv2pn, lv2pm_stm->lv2pmn_hm);
    cache_remove(lv2p_obid, lv2pm_stm->lv2pmo_hm);
    dele_lv2pme(lv2me);
    //
    return 0x00;
}

int delet_lv2p_meta(lv2pm_hmap *lv2pm_stm, char *lv2pn) {
    lv2pme *lv2me = (lv2pme *) cache_value(lv2pn, lv2pm_stm->lv2pmn_hm);
    if (!lv2me) return -1;
    //
    cache_remove(&lv2me->lv2p_obid, lv2pm_stm->lv2pmo_hm);
    cache_remove(lv2pn, lv2pm_stm->lv2pmn_hm);
    dele_lv2pme(lv2me);
    //
    return 0x00;
}

//

lv2pme *creat_lv2p_meta(inst_hmap *insda_stm, instda *lv2in, lv2p_expa_t *lv2expt, osv_oid_t *lv2p_obid) {
    lv2pme *lv2me = mallo_lv2pme(lv2expt);
    if (!lv2me) return NULL;
    //
    OBID_BINARY_COPY(&(lv2me->lv2p_obid), lv2p_obid)
    lv2me->lv2pn[0x00] = '\0';
    //
    action_insert(lv2in->lv2p_decl, lv2me, insda_stm->lv2pme_hm);
    return lv2me;
}

// 0x00:hand refer zero. >0x00:refer number <0x00:error
// destr_insta_data(insda_stm, lv2_dec);
int destr_lv2p_meta(inst_hmap *insda_stm, char *lv2_dec) {
    lv2pme *lv2me = (lv2pme *) action_value(lv2_dec, insda_stm->lv2pme_hm);
    if (!lv2me) return -1;
    action_remove(lv2_dec, insda_stm->lv2pme_hm);
    //
    return 0x00;
}
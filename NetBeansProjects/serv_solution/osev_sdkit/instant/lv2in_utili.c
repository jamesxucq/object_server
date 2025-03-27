
#include "commo_header.h"
#include "kcomm_header.h"

#include "insta_cache.h"

#include "lv2in_utili.h"
#include "instda.h"

//

instda *creat_insta_data(inst_hmap *insda_stm, char *lv2_dec) {
    instda *lv2in = mallo_instda(lv2_dec);
    if (!lv2in) return NULL;
    lv2in->versio = CLASS_INIT_VERSION;
    SET_INVER_ZERO(lv2in->inhver)
    //
    action_insert(lv2in->lv2p_decl, lv2in, insda_stm->lv2pid_hm);
    return lv2in;
}

// 0x00:hand refer zero. >0x00:refer number <0x00:error
// destr_lv2p_meta(insda_stm, lv2_dec);
int destr_insta_data(inst_hmap *insda_stm, char *lv2_dec) {
    instda *lv2in = (instda *) action_value(lv2_dec, insda_stm->lv2pid_hm);
    if (!lv2in) return -1;
    action_remove(lv2_dec, insda_stm->lv2pid_hm);
    //
    return 0x00;
}
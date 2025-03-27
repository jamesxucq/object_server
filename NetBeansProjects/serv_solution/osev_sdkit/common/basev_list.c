#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "instda.h"

#include "basev_list.h"

//
// #include "lv2p_meta.h"
void dele_lev1me(void *lv1me);

static inline void base_value_initi(base_valu *baval) {
    HANDO_CACHE_INITI(baval->hando_stm, dele_lev1me, INVOK_BACKET_SIZE)
    LVTPM_CACHE_INITI(baval->lv2pm_stm, COLLE_BACKET_SIZE)
    //
    conta_cache_initi(&baval->conda_stm, CONTA_BACKET_SIZE);
    INSTA_CACHE_INITI(baval->insda_stm, dele_lv2pme, dele_instda, COLLE_BACKET_SIZE)
}

basv_list *creat_basv_list() {
    basv_list *blsnd = (basv_list *) malloc(sizeof (basv_list));
    if (!blsnd) return NULL;
    // memset(blstmp, '\0', sizeof (base_list));
    //
    blsnd->_base_ = blsnd->basval.base_name;
    blsnd->_oid_ = &blsnd->basval.base_obid;
    //
    base_value_initi(&blsnd->basval);
    return blsnd;
}

//

static inline void final_base_value(base_valu *baval) {
    FINAL_INSTA_CACHE(baval->insda_stm)
    final_conta_cache(&baval->conda_stm);
    //
    FINAL_LVTPM_CACHE(baval->lv2pm_stm)
    FINAL_HANDO_CACHE(baval->hando_stm)
}

void destr_basv_list(basv_list *blist) {
    final_base_value(&blist->basval);
    free(blist);
}

void dele_base_list(basv_list *blist) {
    basv_list *blsnd;
    while ((blsnd = blist)) {
        blist = blist->next;
        final_base_value(&blsnd->basval);
        free(blsnd);
    }
}

//

void dele_blist(basv_list **blsth, basv_list *blist) {
    LL_DELETE(*blsth, blist)
    final_base_value(&blist->basval);
    free(blist);
}

//
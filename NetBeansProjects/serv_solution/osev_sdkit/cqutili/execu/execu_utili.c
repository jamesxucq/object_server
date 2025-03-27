
#include "commo_header.h"

#include "kcomm_header.h"
#include "lexic/valtok.h"
#include "gramm/synta_tree.h"
#include "utili/cstri_utili.h"
#include "ustri_utili.h"

#include "execu_utili.h"


//

lev1me *find_lev1_meta(hand_hmap *hando_stm, char *invop, leaf_list *leli, char *lv2pn) {
    char iclan[LVTN_LENGTH];
    char imetn[LVON_LENGTH];
    if (split_invok(iclan, imetn, invop, lv2pn))
        return NULL;
    OSEVPF("iclan:|%s| imetn:|%s|\n", iclan, imetn);
    //
    char handn[HANDN_LENGTH];
    if (!filli_origi_handn(handn, iclan, imetn, leli))
        return NULL;
    OSEVPF("cuo handn:|%s| lv2pn:|%s|\n", handn, iclan);
    lev1me *lv1me = (lev1me *) action_value(handn, hando_stm->lev1n_hm);
    if (!lv1me) {
        OSEVPF("doh lv1me:%p levn_hm:%p\n", lv1me, hando_stm->lev1n_hm);
        return NULL;
    }
    //
    OSEVPF("find_lev1_meta\n");
    return lv1me;
}

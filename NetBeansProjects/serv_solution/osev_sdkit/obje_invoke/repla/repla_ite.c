
#include "commo_header.h"
#include "kcomm_header.h"
#include "repla/repla_utili.h"

#include "repla/repla_ite.h"
#include "lv2p_decla.h"

//

// data must more, can del or add method, binding changed

int build_replc_list_ite(replc_list **rep_lsh, lv2p_decl_t *elv2dt, lv2p_decl_t *nlv2pd) {
    OSEVPF("[FUNC]:build_replc_list_ite\n");
    // check class data changed
    if (chk_lv2p_prop(rep_lsh, elv2dt->lv2nod, nlv2pd->lv2nod)) {
        dele_replc_list(rep_lsh[0x00]);
        return -1;
    }
    if (chk_bind_meth(rep_lsh, elv2dt->meth, nlv2pd->meth)) {
        dele_replc_list(rep_lsh[0x00]);
        return -1;
    }
    //
    OSEVPF("build_replc_list_ite. end!\n");
    return 0x00;
}
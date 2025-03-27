
#include "commo_header.h"
#include "kcomm_header.h"

#include "lv2p_expan.h"

//

int lv2d_expan_count(lv2p_prop *lv2nod) {
    // OSEVPF("[FUNC]:lv2d_expan_count\n");
    unsigned int inde = 0x00;
    for (; ACCE_COTRL_INVAL != lv2nod->access; ++inde, ++lv2nod);
    return inde;
}

//

int lv1d_expan_count(lev1_decl_t *lv1d) {
    // OSEVPF("[FUNC]:lv1d_expan_count\n");
    unsigned int inde = 0x00;
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++inde, ++lv1d);
    return inde;
}

//
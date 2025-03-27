
#include "commo_header.h"

#include "osev_clie_clang.h"
#include "lvtp_explain/explain_ite.h"

#include "explain.h"
#include "../debug_funct_sh.h"


// odb-lv2p> kits:explain("<[xx int32, ax int32, cx int32], tpp(cx, ax, xx)>");
// odb-lv2p> kits:explain("<[xx int32, ax int32, cx int32], tpp(cx, ax, xx)>");
// odb-lv2p> kits:explain("<[xx int32, ax int32, cx int32]>") | kits:format(XML);
// test // odb-lv2p> kits:explain("<[xx int32, ax int32, cx int32], tpp(cx, ax, xx)>>") | kits:format(XML);
// odb-lv2p> kits:explain("<[xx int32, ax int32, cx int32], tpp(cx, ax, xx)>") | kits:format(XML);
// odb-lv2p> kits:explain("<[xx int32, ax int32, cx int32], tpp(cx, ax, xx)>") | kits:format(XML);

// 0x00:OK -1:error

int kits_explain(char **pamvp, clit_resu *resul, osev_clie *oclie) {
    CLIT_PF("[FUNC]:kits_explain.\n");
    // pamvu = 1
    if (!pamvp[0x00] || pamvp[0x01])
        return -1;
    quote_decode(pamvp[0x00]);
    CLIT_PF("pamvp[0x00]:|%s|\n", pamvp[0x00]);
    //
    CLIT_PF("--- LIST_LVTP_EXPLAIN\n");
    ssize_t revlen;
    if (-1 == (revlen = requ_lv2pd_explain(resul->resu_data, pamvp[0x00], oclie)))
        return -1;
    resul->resu_leng = revlen;
    resul->resu_type = 0x00;
    // 
    return 0x00;
}
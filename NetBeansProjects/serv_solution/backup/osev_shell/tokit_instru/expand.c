
#include "commo_header.h"

#include "osev_clie_clang.h"
#include "lvtp_expand/expand_ite.h"

#include "expand.h"
#include "../debug_funct_sh.h"


// kits:expand("<[xx int32, ax int32, cx int32], tpp(cx, ax, xx)>");
// kits:expand("<[xx int32, ax int32, cx int32], tpp(cx, ax, xx)>");
// kits:expand("<[xx int32, ax int32, cx int32]>") | kits:format(XML);
// test // kits:expand("<[xx int32, ax int32, cx int32], tpp(cx, ax, xx)>>") | kits:format(XML);
// kits:expand("<[xx int32, ax int32, cx int32], tpp(cx, ax, xx)>") | kits:format(XML);

// 0x00:OK -1:error

int kits_expand(char **pamvp, clie_resu *resul, osev_clie *oclie) {
    CLIEPF("[FUNC]:kits_expand.\n");
    // pamvu = 1
    if (!pamvp[0x00] || pamvp[0x01])
        return -1;
    quote_decode(pamvp[0x00]);
    CLIEPF("pamvp[0x00]:|%s|\n", pamvp[0x00]);
    //
    CLIEPF("--- LIST_LVTP_EXPAND\n");
    ssize_t revlen;
    if (-1 == (revlen = requ_lv2pd_expand(resul->resu_data, pamvp[0x00], oclie)))
        return -1;
    resul->resu_leng = revlen;
    resul->resu_type = 0x00;
    // 
    return 0x00;
}
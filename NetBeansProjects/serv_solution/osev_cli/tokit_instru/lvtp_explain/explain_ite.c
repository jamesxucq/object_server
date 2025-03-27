
#include "commo_header.h"

#include "../../debug_funct_sh.h"
#include "../../cstri_utili.h"

// #define CPOST_INSTRU_CLEAINST   0x00
// #define CPOST_INSTRU_EXPLAIN     0x01
// #define CPOST_INSTRU_CLEAINST   0x01

#define CPOST_DEFAU_EXPLAIN  "1I"// "EXPLAIN"

//

int requ_lv2pd_explain(char *lv2p_cont, const char *lv2p_decl, osev_clie *oclie) {
    const char *parms[0x03] = {CPOST_DEFAU_EXPLAIN, lv2p_decl, NULL};
    resp_data_t lv2p_resp;
    //
    if (lv2p_colle_post(&lv2p_resp, oclie, parms)) {
        OSEVPrintErro("colle list error!", lv2p_resp.status_code);
        outpu_excep_code(&lv2p_resp);
        return -1;
    }
    memcpy(lv2p_cont, lv2p_resp.resp_memo, lv2p_resp.content_length);
    lv2p_cont[lv2p_resp.content_length] = '\0';
    //
    return lv2p_resp.content_length;
}
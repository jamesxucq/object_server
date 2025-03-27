
#include "commo_header.h"

#include "post_inner_valu.h"

//
// default
// level-2+> odb:post(CLEAR_INSTANT);
// level-2+> odb:post(EXPAND, "<[xx int32, ax int32, cx int32]>");

// #define CPOST_DEFAULT_CLEAINST   0x00
// #define CPOST_DEFAULT_EXPAND     0x01
// #define CPOST_DEFAULT_CLEAINST   0x01

// lv2p
// level-2+> odb:post("taat", EXTERN, TRUE);

// #define CPOST_LVTP_EXTERN   0x00
// #define CPOST_LVTP_EXTERN   0x00
// #define CPOST_LVTP_EXTERN   0x01

// EXTERN
static osv_str_t CPTI_LVTP_EXTERN = osv_stri("EXTERN");

static const struct stst_node cpost_defau_dict[] = {
    {"CLEAR_INSTANT", "0I"}, // CPOST_DEFAULT_CLEAINST
    {"EXPAND", "1I"}, // CPOST_DEFAULT_EXPAND
    {NULL, "INVA"}
};

int cpti_inner_inst(char **pamvp) {
    // OSEVPF("[FUNC]:cpti_inner_inst\n");
    if (!pamvp[0x00]) return -1;
    //
    if (!found_conve_value(pamvp[0x00], (struct stst_node *) cpost_defau_dict)) {
        if (!pamvp[0x01] || !pamvp[0x02]) return -1;
        //
        if (!strncmp(CPTI_LVTP_EXTERN.data, pamvp[0x01], CPTI_LVTP_EXTERN.slen)) {
            strcpy(pamvp[0x01], "0I");
        } else return -1;
        //
        if (stri_BOOL(pamvp[0x02])) {
            strcpy(pamvp[0x02], "1I");
        } else strcpy(pamvp[0x02], "0I");
    }
    //
    return 0x00;
}


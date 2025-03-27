
#include "commo_header.h"

#include "post_inner_valu.h"

// lev1 instruct
// [txxt]lev1> odb:post(REPLACE, "txxt:tpp"); // replaceability

// #define IPOST_INSTRU_REPLACE     0x00

// lev1 attrib
// odb-lv2p> odb:post("taat", EXTERN, TRUE);

// #define CPOST_ATTRIB_EXTERN   0x00

// EXTERN
static osv_str_t IPOST_ATTRIB_EXTERN = osv_stri("EXTERN");

static const struct stst_node ipost_instru_dict[] = {
    {"REPLACE", "0I"}, // IPOST_INSTRU_REPLACE
    {NULL, "INVA"}
};

int ipot_inner_inst(char **pamvp) {
    // OSEVPF("[FUNC]:ipot_inner_inst\n");
    if (!pamvp[0x00]) return -1;
    //
    if (!found_conve_value(pamvp[0x00], (struct stst_node *) ipost_instru_dict)) {
        if (!pamvp[0x01] || !pamvp[0x02]) return -1;
        //
        if (!strncmp(IPOST_ATTRIB_EXTERN.data, pamvp[0x01], IPOST_ATTRIB_EXTERN.slen)) {
            strcpy(pamvp[0x01], "0I");
        } else return -1;
        //
        switch (stri_BOOL(pamvp[0x02])) {
            case FALSE_OSV:
                strcpy(pamvp[0x02], "0I");
                break;
            case TRUE_OSV:
                strcpy(pamvp[0x02], "1I");
                break;
            case INVAL_OSV:
                return -1;
                break;
        }
    }
    //
    return 0x00;
}

// instruct lv2p
// odb-lv2p> odb:post(CLEAR_INSTANT);
// odb-lv2p> odb:post(EXPLAIN, "<[xx int32, ax int32, cx int32]>");

// #define CPOST_INSTRU_CLEAINST   0x00
// #define CPOST_INSTRU_EXPLAIN    0x01
// #define CPOST_INSTRU_REPLACE    0x02

// attrib lv2p
// odb-lv2p> odb:post("taat", EXTERN, TRUE);

// #define CPOST_ATTRIB_EXTERN   0x00
// #define CPOST_ATTRIB_EXTERN   0x00
// #define CPOST_ATTRIB_EXTERN   0x01

// EXTERN
static osv_str_t CPOST_ATTRIB_EXTERN = osv_stri("EXTERN");

static const struct stst_node cpost_instru_dict[] = {
    {"CLEAR_INSTANT", "0I"}, // CPOST_INSTRU_CLEAINST
    {"EXPLAIN", "1I"}, // CPOST_INSTRU_EXPLAIN
    {"REPLACE", "2I"}, // CPOST_INSTRU_REPLACE
    {NULL, "INVA"}
};

int cpot_inner_inst(char **pamvp) {
    // OSEVPF("[FUNC]:cpot_inner_inst\n");
    if (!pamvp[0x00]) return -1;
    //
    if (!found_conve_value(pamvp[0x00], (struct stst_node *) cpost_instru_dict)) {
        if (!pamvp[0x01] || !pamvp[0x02]) return -1;
        //
        if (!strncmp(CPOST_ATTRIB_EXTERN.data, pamvp[0x01], CPOST_ATTRIB_EXTERN.slen)) {
            strcpy(pamvp[0x01], "0I");
        } else return -1;
        //
        switch (stri_BOOL(pamvp[0x02])) {
            case FALSE_OSV:
                strcpy(pamvp[0x02], "0I");
                break;
            case TRUE_OSV:
                strcpy(pamvp[0x02], "1I");
                break;
            case INVAL_OSV:
                return -1;
                break;
        }
    }
    //
    return 0x00;
}


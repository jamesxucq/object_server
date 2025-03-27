
#include "commo_header.h"

#include "repla_inner_valu.h"


//
#define REPLA_INTERN_FORCED    "FORCED"

// default, lv2p

int irep_inner_inst(char **pamvp) {
    if (!pamvp[0x00]) return -1;
    //
    if (pamvp[0x01]) {
        if (strcmp(REPLA_INTERN_FORCED, pamvp[0x01])) {
            strcpy(pamvp[0x01], "0I");
        } else strcpy(pamvp[0x01], "1I");
    }
    //
    return 0x00;
}

// default, lv2p

int crep_inner_inst(char **pamvp) {
    if (!pamvp[0x00]) return -1;
    //
    if (pamvp[0x01]) {
        if (strcmp(REPLA_INTERN_FORCED, pamvp[0x01])) {
            strcpy(pamvp[0x01], "0I");
        } else strcpy(pamvp[0x01], "1I");
    }
    //
    return 0x00;
}

#include "commo_header.h"

#include "../cli_obje.h"
#include "../debug_funct_sh.h"

#include "cont_name_obid.h"

// char *cont_iden, char*last_pamv

int pretr_conta_obid(char **pamvp) {
    osv_oid_t *cont_obid;
    cont_obid = find_conta_obid(pamvp[0x00], &_ocli_clie_);
    if (!cont_obid) {
        CLIEPF("Not find the conta.\n");
        return -1;
    }
    //
    if (!pamvp[0x02]) {
        expand_tail(pamvp, pamvp[0x01]);
        ESMCPY_OBID(((char *) pamvp[0x00]), cont_obid);
    }
    //
    return 0x00;
}

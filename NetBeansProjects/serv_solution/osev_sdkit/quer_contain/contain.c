#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_header.h"

#include "basev_bzl.h"
#include "conattr.h"
#include "query_utili.h"
#include "seion_struct.h"
#include "rive_bzl.h"

#include "contain.h"

//

contain *build_conta_meta(contain *contp, char *basen, char *contn) {
    OSEVPF("[FUNC]:build_conta_meta, contn:|%s|\n", contn);
    cont_atti_i canod;
    if (find_cont_atti(&canod, contn, basen))
        return NULL;
    // p_cont_atti_i(&canod);
    // CONVE_CATTR_CONTA
    CONVE_CATTR_CONTA(contp, canod, basen);
    //
    return contp;
}

//

int qload_conta_meta(basv_list *blist) {
    OSEVPF("[FUNC]:qload_conta_meta\n");
    cont_list *clist;
    basv_list *blsnd = blist;
    for (; blsnd; blsnd = blsnd->next) {
        fprintf(stdout, "qload_conta_meta:%s\n", blsnd->_base_);
        clist = load_catti_base(blsnd->_base_);
        inser_conta_list(&blsnd->basval.conda_stm, clist);
    }
    // OSEVPF("[FUNC]:end qload_conta_meta\n");
    return 0x00;
}

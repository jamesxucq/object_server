#include "commo_header.h"
#include "kcomm_header.h"

#include "basev_bzl.h"
#include "baseda_cache.h"
#include "seion_struct.h"
#include "basev_list.h"

// find cont_obid in base, find base on base_obid

base_valu *find_baval_bcoid(osv_oid_t *chk_obid, cachemap *baval_ca) {
    OSEVPF("[FUNC]:find_baval_bcoid\n");
#ifdef _DEBUG
    char obid_stri[OBJE_IDENTI_ZLEN];
    OSEVPF("chk_obid:|%s|\n", oidstr(obid_stri, chk_obid));
#endif
    contain *contp;
    basv_list *blsnd;
    //
    base_valu *baval = (base_valu *) cache_value(chk_obid, baval_ca);
    if (!baval) {
        BORRO_BLIST_BZL(blsnd)
        for (; blsnd; blsnd = blsnd->next) {
            if (STOID_EQUALI(chk_obid, blsnd->_oid_)) {
                cache_insert(blsnd->_oid_, (void *) &blsnd->basval, baval_ca);
                GIVBK_BLIST_BZL()
                return &blsnd->basval;
            }
            contp = (contain *) cache_value(chk_obid, blsnd->basval.conda_stm.lev3o_hm);
            if (contp) {
                cache_insert(&contp->cont_obid, (void *) &blsnd->basval, baval_ca);
                GIVBK_BLIST_BZL()
                return &blsnd->basval;
            }
        }
        GIVBK_BLIST_BZL()
    }
    // OSEVPF("end find_baval_bcoid\n");
    return baval;
}





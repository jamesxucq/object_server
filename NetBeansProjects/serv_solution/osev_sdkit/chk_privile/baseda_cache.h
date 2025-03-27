
/* 
 * File:   baseda_cache.h
 * Author: James Xu
 *
 * Created on 2023.4.21, AM 8:52
 */

#ifndef BASEDA_CACHE_H
#define BASEDA_CACHE_H

#ifdef __cplusplus
extern "C" {
#endif

    // cachemap *_badat_hm_;

    inline cachemap *initi_baval_cache() {
        OSEVPF("[FUNC]:initi_baval_cache\n");
        cachemap *baval_ca = creat_obid_cache(CONTA_BACKET_SIZE);
        return baval_ca;
    }

    inline void final_baval_cache(cachemap *baval_ca) {
        OSEVPF("[FUNC]:final_baval_cache\n");
        cache_destroy(baval_ca);
    }

    // find cont_obid in base, find base on base_obid
    base_valu *find_baval_bcoid(osv_oid_t *chk_obid, cachemap *baval_ca);

#ifdef __cplusplus
}
#endif

#endif /* BASEDA_CACHE_H */


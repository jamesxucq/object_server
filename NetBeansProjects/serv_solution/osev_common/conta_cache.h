
/* 
 * File:   conta_cache.h
 * Author: James Xu
 *
 * Created on 2023.5.3, AM 10:58
 */

#ifndef CONTA_CACHE_H
#define CONTA_CACHE_H

#include "cont_list.h"
#include "debug_funct_osv.h"

#ifdef __cplusplus
extern "C" {
#endif

    struct _cont_listmap_ {
        cont_list *clist; // container list
        cachemap *lev3o_hm; // container object id map
        cachemap *lev3n_hm; // container name map
    };

    typedef struct _cont_listmap_ cont_lsmp;

    //

    inline void conta_cache_remove(cont_lsmp *conta_ca, contain *contp) {
        OSEVPF("[FUNC]:conta_cache_remove\n");
        cache_remove(&contp->cont_obid, conta_ca->lev3o_hm);
        cache_remove(contp->cont_name, conta_ca->lev3n_hm);
        dele_clist_cont(&conta_ca->clist, contp);
    }

    inline void conta_cache_insert(cont_lsmp *conta_ca, contain *contp) {
        OSEVPF("[FUNC]:conta_cache_insert\n");
        cache_insert(&contp->cont_obid, (void *) contp, conta_ca->lev3o_hm);
        cache_insert(contp->cont_name, (void *) contp, conta_ca->lev3n_hm);
    }

    inline void conta_cache_initi(cont_lsmp *conta_ca, unsigned long long backet_size) {
        OSEVPF("[FUNC]:conta_cache_initi\n");
        conta_ca->clist = NULL;
        conta_ca->lev3o_hm = creat_obid_cache(backet_size);
        conta_ca->lev3n_hm = creat_cache(backet_size);
    }

    inline void final_conta_cache(cont_lsmp *conta_ca) {
        OSEVPF("[FUNC]:final_conta_cache\n");
        cache_destroy(conta_ca->lev3n_hm);
        cache_destroy(conta_ca->lev3o_hm);
        dele_cont_list(conta_ca->clist);
    }


#ifdef __cplusplus
}
#endif

#endif /* CONTA_CACHE_H */



/* 
 * File:   basev_obje.h
 * Author: James Xu
 *
 * Created on 2023.4.20, PM 4:38
 */

#ifndef BASEV_OBJE_H
#define BASEV_OBJE_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    extern basv_lsmp _base_cache_;
    extern pthread_mutex_t _base_cache_mutex_;

    //
    int find_base_obid(OUT char *basen, osv_oid_t *find_boid);


#ifdef __cplusplus
}
#endif

#endif /* BASEV_OBJE_H */


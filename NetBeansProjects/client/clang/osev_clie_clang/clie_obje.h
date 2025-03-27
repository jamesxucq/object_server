
/* 
 * File:   clie_obje.h
 * Author: James Xu
 *
 * Created on 2024.1.10, PM 3:47
 */

#include <pthread.h>

#ifndef CLIE_OBJE_H
#define CLIE_OBJE_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    extern osv_atomic_t clie_creat_count;

    //
    extern oidoidmap *_cache_conatt_hm_;
    extern pthread_mutex_t _cache_conatt_mutex_;

    int creat_conatt_cache();
    void destr_contatt_cache();

#ifdef __cplusplus
}
#endif

#endif /* CLIE_OBJE_H */



/* 
 * File:   clie_obje.h
 * Author: James Xu
 *
 * Created on 2017.9.7
 */

#ifndef CLIE_OBJE_H
#define CLIE_OBJE_H

#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

//
    void dele_cont(void *conta);

    //
    extern oidoidmap *_cache_conatt_hm_;
    extern pthread_mutex_t _cache_conatt_mutex_;
    
    int creat_conatt_cache();
    void destr_contatt_cache();
    
#ifdef __cplusplus
}
#endif

#endif /* CLIE_OBJE_H */


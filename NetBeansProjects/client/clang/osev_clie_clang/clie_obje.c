#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "commo_header.h"
#include "conatt.h"

#include "clie_obje.h"

//
osv_atomic_t clie_creat_count;

//
oidoidmap *_cache_conatt_hm_;
pthread_mutex_t _cache_conatt_mutex_ = PTHREAD_MUTEX_INITIALIZER;

//

int creat_conatt_cache() {
    pthread_mutex_lock(&_cache_conatt_mutex_);
    if (!_cache_conatt_hm_)
        _cache_conatt_hm_ = creat_ooid_actio(dele_conat, CONTA_BACKET_SIZE << 0x02); // 16k
    pthread_mutex_unlock(&_cache_conatt_mutex_);
    if (!_cache_conatt_hm_) return -1;
    return 0x00;
}

void destr_contatt_cache() {
    pthread_mutex_lock(&_cache_conatt_mutex_);
    if (_cache_conatt_hm_) {
        oidoid_destroy(_cache_conatt_hm_);
        _cache_conatt_hm_ = NULL;
    }
    pthread_mutex_unlock(&_cache_conatt_mutex_);
}


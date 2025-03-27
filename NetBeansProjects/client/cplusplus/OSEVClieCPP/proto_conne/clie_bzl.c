
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <pthread.h>

#include "osev_common/commo_header.h"
// #include "osev_common/hash_table_ex.h"
#include "osco_socks.h"
#include "hand_method.h"
// #include "osev_clie.h"
#include "conatt.h"
#include "clie_obje.h"

#include "clie_bzl.h"


//

cont_atti *find_conatt_bzl(cont_atti *conat, osv_oid_t *base_obid, osv_oid_t *cont_obid) {
    cont_atti *orig_coat;
    pthread_mutex_lock(&_cache_conatt_mutex_);
    orig_coat = (cont_atti *) oidoid_value(base_obid, cont_obid, _cache_conatt_hm_);
    if (orig_coat) memcpy(conat, orig_coat, sizeof (cont_atti));
    pthread_mutex_unlock(&_cache_conatt_mutex_);
    //
    return orig_coat;
}

void updat_conatt_bzl(cont_atti *orig_coat, cont_atti *conat) {
    pthread_mutex_lock(&_cache_conatt_mutex_);
    memcpy(orig_coat, conat, sizeof (cont_atti));
    pthread_mutex_unlock(&_cache_conatt_mutex_);
}

void inser_conatt_bzl(osv_oid_t *base_obid, osv_oid_t *cont_obid, cont_atti *conat) {
    cont_atti *orig_coat = (cont_atti *) malloc(sizeof (cont_atti));
    if (orig_coat) {
        memcpy(orig_coat, conat, sizeof (cont_atti));
        pthread_mutex_lock(&_cache_conatt_mutex_);
        oidoid_insert(base_obid, cont_obid, orig_coat, _cache_conatt_hm_);
        pthread_mutex_unlock(&_cache_conatt_mutex_);
    }
}


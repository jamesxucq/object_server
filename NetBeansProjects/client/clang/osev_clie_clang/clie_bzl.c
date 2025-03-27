
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <pthread.h>

#include "commo_header.h"
#include "osco_socks.h"
#include "clie_obje.h"
#include "osev_clie_clang.h"
#include "conatt.h"

#include "clie_bzl.h"

// 0x00:success -1:error

int clie_oscrea_bzl(resp_data_t *crea_resp, int conne_sock, pamstyl_t *pamsty) {
    requ_data_t req_dat;
    req_dat.requ_type = REQU_MEMORY_TYPE;
    osev_requ *rosev = (osev_requ *) req_dat.requ_memo;
    CAT_REQHAD_PTR(rosev, OSVP_OSEV, OAUTHEN, &INVA_OBID_VALU, pamsty->colen)
    memcpy(rosev->requ_binary, pamsty->pamstyl_memo, pamsty->colen);
    CAT_REQDAT_QLN(req_dat, rosev)
    return hand_respon(crea_resp, conne_sock, &req_dat);
}

int clie_bscrea_bzl(resp_data_t *crea_resp, int conne_sock, pamstyl_t *pamsty) {
    requ_data_t req_dat;
    req_dat.requ_type = REQU_MEMORY_TYPE;
    base_requ *rbase = (base_requ *) req_dat.requ_memo;
    CAT_REQHAD_PTR(rbase, OSVP_BASE, BAUTHEN, &INVA_OBID_VALU, pamsty->colen)
    memcpy(rbase->requ_binary, pamsty->pamstyl_memo, pamsty->colen);
    CAT_REQDAT_QLN(req_dat, rbase)
    return hand_respon(crea_resp, conne_sock, &req_dat);
}

// 0x00:success -1:error

int clie_destroy_bzl(resp_head *dest_resp, int conne_sock, const osv_oid_t *clie_obid) {
    // printf("clie_destroy_bzl\n");
    requ_data_t req_dat;
    req_dat.requ_type = REQU_MEMORY_TYPE;
    done_requ *rdone = (done_requ *) req_dat.requ_memo;
    CAT_REQHAD_PTR(rdone, OSVP_DONE, ZERO_LEVEL_INVK, clie_obid, ONLY_HEADER_SECTION)
    CAT_REQDAT_QLN(req_dat, rdone)
    // printf("end clie_destroy_bzl\n");
    return hand_reques(dest_resp, conne_sock, &req_dat);
}

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

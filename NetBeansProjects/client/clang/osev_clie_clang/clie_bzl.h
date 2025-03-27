
/* 
 * File:   clie_bzl.h
 * Author: James Xu
 *
 * Created on 2017.5.17, PM4:45
 */

#ifndef CLIE_BZL_H
#define CLIE_BZL_H

//
#include "reque_respo.h"
#include "reque_conne.h"
#include "dstri_utili.h"
#include "hand_method.h"
#include "conatt.h"

#ifdef __cplusplus
extern "C" {
#endif

    //


    // osco_init();
    // osco_cleanup();
    //
    // 0x00:success -1:error
    // clie_create_bzl
    int clie_oscrea_bzl(resp_data_t *crea_resp, int conne_sock, pamstyl_t *pamsty);
    int clie_bscrea_bzl(resp_data_t *crea_resp, int conne_sock, pamstyl_t *pamsty);
    int clie_destroy_bzl(resp_head *dest_resp, int conne_sock, const osv_oid_t *clie_obid);

    // 0x00:success -1:error

#define CLIE_OSEV_BZL(STATU_RESP, CONNE_SOCK, LEVIVK, OSEV_OBID, PAMSTYL) { \
        requ_data_t req_dat; \
        req_dat.requ_type = REQU_MEMORY_TYPE; \
        osev_requ *rstatu = (osev_requ *) req_dat.requ_memo; \
        CAT_REQHAD_PTR(rstatu, OSVP_OSEV, LEVIVK, OSEV_OBID, (PAMSTYL)->colen) \
        memcpy(rstatu->requ_binary, (PAMSTYL)->pamstyl_memo, (PAMSTYL)->colen); \
        CAT_REQDAT_QLN(req_dat, rstatu) \
        if(hand_respon(STATU_RESP, CONNE_SOCK, &req_dat)) \
            return -1; \
    }

    // 0x00:success -1:error

#define CLIE_BASE_BZL(PRIVI_RESP, CONNE_SOCK, LEVIVK, BASE_OBID, PAMSTYL) { \
        requ_data_t req_dat; \
        req_dat.requ_type = REQU_MEMORY_TYPE; \
        base_requ *rprivi = (base_requ *) req_dat.requ_memo; \
        CAT_REQHAD_PTR(rprivi, OSVP_BASE, LEVIVK, BASE_OBID, (PAMSTYL)->colen) \
        memcpy(rprivi->requ_binary, (PAMSTYL)->pamstyl_memo, (PAMSTYL)->colen); \
        CAT_REQDAT_QLN(req_dat, rprivi) \
        if(hand_respon(PRIVI_RESP, CONNE_SOCK, &req_dat)) \
            return -1; \
    }

    // 0x00:success -1:error

#define CLIE_KALIVE_BZL(KALIV_RESP, CONNE_SOCK, KALI_OBID) { \
        requ_data_t req_dat; \
        req_dat.requ_type = REQU_MEMORY_TYPE; \
        kaliv_requ *rkaliv = (kaliv_requ *) req_dat.requ_memo; \
        CAT_REQHAD_PTR(rkaliv, OSVP_KALIVE, ZERO_LEVEL_INVK, KALI_OBID, ONLY_HEADER_SECTION) \
        CAT_REQDAT_QLN(req_dat, rkaliv) \
        if(hand_reques(KALIV_RESP, CONNE_SOCK, &req_dat)) \
            return -1; \
    }

    // 0x00:success -1:error

#define CLIE_INVOK_BZL(INVOK_RESP, CONNE_SOCK, INVOTYP, LVTP_OBID, PAMSTYL) { \
        requ_data_t req_dat; \
        req_dat.requ_type = REQU_MEMORY_TYPE; \
        invok_requ *rinvok = (invok_requ *) req_dat.requ_memo; \
        CAT_REQHAD_PTR(rinvok, OSVP_INVOKE, INVOTYP, LVTP_OBID, (PAMSTYL)->colen) \
        memcpy(rinvok->requ_binary, (PAMSTYL)->pamstyl_memo, (PAMSTYL)->colen); \
        CAT_REQDAT_QLN(req_dat, rinvok) \
        if(hand_respon(INVOK_RESP, CONNE_SOCK, &req_dat)) \
            return -1; \
    }

    // trans-serve    
    // 0x00:success -1:error

#define CLIE_COLLE_BZL(CONLLE_RESP, CONNE_SOCK, COLLTYP, BASE_OBID, PAMSTYL) { \
        requ_data_t req_dat; \
        req_dat.requ_type = REQU_MEMORY_TYPE; \
        colle_requ *rcolle = (colle_requ *) req_dat.requ_memo; \
        CAT_REQHAD_PTR(rcolle, OSVP_COLLE, COLLTYP, BASE_OBID, (PAMSTYL)->colen) \
        memcpy(rcolle->requ_binary, (PAMSTYL)->pamstyl_memo, (PAMSTYL)->colen); \
        CAT_REQDAT_QLN(req_dat, rcolle) \
        if(hand_respon(CONLLE_RESP, CONNE_SOCK, &req_dat)) \
            return -1; \
    }

    // 0x00:success -1:error

#define CLIE_CONST_BZL(CONST_RESP, CONNE_SOCK, CONSTYP, CONT_OBID, PAMSTYL) { \
        requ_data_t req_dat; \
        req_dat.requ_type = REQU_MEMORY_TYPE; \
        const_requ *rconst = (const_requ *) req_dat.requ_memo; \
        CAT_REQHAD_PTR(rconst, OSVP_CONST, CONSTYP, CONT_OBID, (PAMSTYL)->colen) \
        memcpy(rconst->requ_binary, (PAMSTYL)->pamstyl_memo, (PAMSTYL)->colen); \
        CAT_REQDAT_QLN(req_dat, rconst) \
        if(hand_respon(CONST_RESP, CONNE_SOCK, &req_dat)) \
            return -1; \
    }

    // 0x00:success -1:error

#define CLIE_QUERY_BZL(QUERY_RESP, CONNE_SOCK, QUERTYP, BASE_OBID, PAMSTYL) { \
        requ_data_t req_dat; \
        req_dat.requ_type = REQU_MEMORY_TYPE; \
        query_requ *rquery = (query_requ *) req_dat.requ_memo; \
        CAT_REQHAD_PTR(rquery, OSVP_QUERY, QUERTYP, BASE_OBID, (PAMSTYL)->colen) \
        memcpy(rquery->requ_binary, (PAMSTYL)->pamstyl_memo, (PAMSTYL)->colen); \
        CAT_REQDAT_QLN(req_dat, rquery) \
        if(hand_respon(QUERY_RESP, CONNE_SOCK, &req_dat)) \
            return -1; \
    }

    // _cache_conatt_hm_
#define INITI_CONATT_BZL(REV_ERRNO) { \
    if(!OSV_ATOMIC_FETCH_ADD(&clie_creat_count, 0x01)) { \
        if(!_cache_conatt_hm_) { \
            if(creat_conatt_cache()) \
                return REV_ERRNO; \
        } \
    } \
}

#define FINAL_CONATT_BZL() { \
    if(!OSV_ATOMIC_SUB_FETCH(&clie_creat_count, 0x01)) { \
        if(_cache_conatt_hm_) { \
            destr_contatt_cache(); \
        } \
    } \
}

    cont_atti *find_conatt_bzl(cont_atti *conat, osv_oid_t *base_obid, osv_oid_t *cont_obid);
    void updat_conatt_bzl(cont_atti *orig_coat, cont_atti *conat);
    void inser_conatt_bzl(osv_oid_t *base_obid, osv_oid_t *cont_obid, cont_atti *conat);


#ifdef __cplusplus
}
#endif

#endif /* CLIE_BZL_H */


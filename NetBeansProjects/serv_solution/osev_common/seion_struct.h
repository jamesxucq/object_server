
/* 
 * File:   seion_struct.h
 * Author: James Xu
 *
 * Created on 2016.12.17, PM 3:14
 */

#ifndef SEION_STRUCT_H
#define SEION_STRUCT_H

#include "hash_table_ex.h"
#include "commo_macro.h"
#include "osev_datyp.h"
#include "osev_struct.h"
#include "osev_macro.h"
#include "rive_macro.h"
#include "rive_struct.h"
#include "obid.h"
#include "ostproto.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    struct _priv_auth_ {
        osv_oid_t prau_obid; // osev base obid
        char osev_base[OSEV_LENGTH];
        // char obid_stri[OBJE_IDENTI_SLEN]; // prau_obid plain
        unsigned char auth_valid[PLAIN_VALID_LENGTH];
        void *use_privi; // NULL:no auth privile, type is user_privi
        char _action_key_[ACTION_KEY_LENGTH]; // user_name:osev_name/base_name
        unsigned int _refer_inde_; // reference
    };

    typedef struct _priv_auth_ priv_auth;

    //

    struct _inte_value_ {
        osv_oid_t inte_obid; // lv1/lv3:contain obid // lv2/lv4:base obid
        // unsigned int isosev; // 0x00:osev !0x00:base
        pams_valu pamvs;
        char _data_line_[LARGE_CONTE_SIZE];
    };

    typedef struct _inte_value_ inte_value;

    //

    struct _rcvse_ctrl_ {
        uint64 content_length; // recv send length // havent reset
        // request receive
        FILE *requ_stram; // auto reset
        BYTE requ_memo[RSBUF_SIZE];
        char *posi_requ; // point to requ_memo // manual reset
        // respon send
        unsigned char status_code; // STATUS_CODE // auto reset
        FILE *resp_stram; // auto reset
        BYTE resp_memo[RSBUF_SIZE];
        char *posi_resp; // point to resp_memo // manual reset
    };

    typedef struct _rcvse_ctrl_ rcvse_ctrl;
    typedef struct _rcvse_ctrl_ reque_ctrl;
    typedef struct _rcvse_ctrl_ respo_ctrl;

    /* session ctrl */

    struct _session_ {
        priv_auth *apval; // priv auth data
        base_valu *baval; // odb / contain info
        inte_value inval; // inte value
        rcvse_ctrl rvsctl; // recv send ctrl
    };

    typedef struct _session_ session;

    //

    inline session *creat_session() {
        session *seion = (session *) malloc(sizeof (session));
        if (!seion) return NULL;
        // initial resctl
        if (!(seion->rvsctl.requ_stram = tmpfile64())) {
            free(seion);
            return NULL;
        }
        seion->rvsctl.status_code = OK;
        if (!(seion->rvsctl.resp_stram = tmpfile64())) {
            free(seion);
            return NULL;
        }
        return seion;
    }

    inline void destro_session(session *seion) {
        FCLOSE_SAFETY(seion->rvsctl.resp_stram);
        FCLOSE_SAFETY(seion->rvsctl.requ_stram);
        free(seion);
    }

    inline void reset_session(session *seion) {
        seion->rvsctl.status_code = OK;
    }

#ifdef __cplusplus
}
#endif

#endif /* SEION_STRUCT_H */


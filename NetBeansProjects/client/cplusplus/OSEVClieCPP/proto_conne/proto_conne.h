
/* 
 * File:   proto_conne.h
 * Author: James Xu
 *
 * Created on 2023.11.4, AM 10:53
 */

#ifndef PROTO_CONNE_H
#define PROTO_CONNE_H

//
#include "osev_common/commo_macro.h"
#include "osev_common/reque_conne.h"

#include "clie_struct.h"
#include "reque_respo.h"
#include "osvp_auth.h"
#include "osco_socks.h"
#include "cstri_utili.h"
#include "clie_bzl.h"

#ifdef __cplusplus
extern "C" {
#endif

    // trans-serve

    struct _osev_clie_ {
        // char osvp_uri[OSVPURI_LENGTH];
        osv_oid_t clie_obid; // base, contain obid
        char clie_name[OSEV_LENGTH]; // base, contain name
        int conne_sock;
    };

    typedef struct _osev_clie_ osev_clie;

    // 0x00:ok , -1:error

    inline int osev_clie_create(OUT resp_data_t *crea_resp, OUT osev_clie *clie, osvp_auth *clie_auth) {
        // OSEVPF("[FUNC]:osev_clie_create\n");
        // OSEVPF("addr:|%s| port:%d\n", addr, port);
        // OSEVPF("osev_base:|%s| uname:|%s| paswd:|%s|\n", osev_base, uname, paswd);
        unsigned char req_valid_memo[ESCA_ENTICON_PART + VALID_LENGTH];
        unsigned char salt_memo[ESCA_ENTICON_PART + SALT_LENGTH];
        MAKE_ESCHEAD_BINA(req_valid_memo, VALID_LENGTH);
        MAKE_ESCHEAD_BINA(salt_memo, SALT_LENGTH);
        const char *parms[0x05] = {clie_auth->authe.user_name, (char *) req_valid_memo, (char *) salt_memo, clie_auth->osev_base, NULL};
        //
        creat_authe_iacv(ESCA_ECONTE_POSI(req_valid_memo), ESCA_ECONTE_POSI(salt_memo), clie_auth->authe.user_name, clie_auth->authe.pass_word);
        pamstyl_t pamsty;
        if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, parms))
            return -1;
        //
        strcpy(clie->clie_name, clie_auth->osev_base);
        clie->conne_sock = osco_connect(&clie_auth->saddr);
        if (-1 == clie->conne_sock) {
            // OSEVPF("client connect execep!\n");
            OSCO_CLOSE(clie->conne_sock);
            return -1;
        }
        if (clie_oscrea_bzl(crea_resp, clie->conne_sock, &pamsty)) {
            // OSEVPF("client create error!\n");
            OSCO_CLOSE(clie->conne_sock);
            return -1;
        }
        if (OK != crea_resp->status_code) {
            // OSEVPF("client create execep!\n");
            OSCO_CLOSE(clie->conne_sock);
            return crea_resp->status_code;
        }
        // stroid(&clie->clie_obid, crea_resp->resp_memo);
        OBID_BINARY_COPY(&clie->clie_obid, (osv_oid_t *) crea_resp->resp_memo)
#ifdef _DEBUG
                // OSEVPF("[DEBUG] osev_base:|%s| user_name:|%s|\n", authi->auth.osev_base, authi->auth.user_name);
                // char temp[33];
                // OSEVPF("[DEBUG] clie->clie_obid:|%s|\n", oidstr(temp, &clie->clie_obid));
                // OSEVPF("Client create OK!\n");
#endif
                return 0x00;
    }

    // 0x00:ok , -1:error

    inline int base_clie_create(OUT resp_data_t *crea_resp, OUT osev_clie *clie, osvp_auth *clie_auth) {
        // OSEVPF("[FUNC]:base_clie_create\n");
        // OSEVPF("addr:|%s| port:%d\n", addr, port);
        // OSEVPF("osev_base:|%s| uname:|%s| paswd:|%s|\n", osev_base, uname, paswd);
        unsigned char req_valid_memo[ESCA_ENTICON_PART + VALID_LENGTH];
        unsigned char salt_memo[ESCA_ENTICON_PART + SALT_LENGTH];
        MAKE_ESCHEAD_BINA(req_valid_memo, VALID_LENGTH);
        MAKE_ESCHEAD_BINA(salt_memo, SALT_LENGTH);
        const char *parms[0x05] = {clie_auth->authe.user_name, (char *) req_valid_memo, (char *) salt_memo, clie_auth->osev_base, NULL};
        //
        creat_authe_iacv(ESCA_ECONTE_POSI(req_valid_memo), ESCA_ECONTE_POSI(salt_memo), clie_auth->authe.user_name, clie_auth->authe.pass_word);
        pamstyl_t pamsty;
        if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, parms))
            return -1;
        //
        strcpy(clie->clie_name, clie_auth->osev_base);
        clie->conne_sock = osco_connect(&clie_auth->saddr);
        if (-1 == clie->conne_sock) {
            // OSEVPF("client connect execep!\n");
            OSCO_CLOSE(clie->conne_sock);
            return -1;
        }
        if (clie_bscrea_bzl(crea_resp, clie->conne_sock, &pamsty)) {
            // OSEVPF("client create error!\n");
            OSCO_CLOSE(clie->conne_sock);
            return -1;
        }
        if (OK != crea_resp->status_code) {
            // OSEVPF("client create execep!\n");
            OSCO_CLOSE(clie->conne_sock);
            return crea_resp->status_code;
        }
        // stroid(&clie->clie_obid, crea_resp->resp_memo);
        OBID_BINARY_COPY(&clie->clie_obid, (osv_oid_t *) crea_resp->resp_memo)
#ifdef _DEBUG
                // OSEVPF("[DEBUG] osev_base:|%s| user_name:|%s|\n", authi->auth.osev_base, authi->auth.user_name);
                // char temp[33];
                // OSEVPF("[DEBUG] clie->clie_obid:|%s|\n", oidstr(temp, &clie->clie_obid));
                // OSEVPF("Client create OK!\n");
#endif
                return 0x00;
    }

#define CLIE_DESTROY_DELAY  0x01
    // trans-serve
#define CLIE_DESTROY_TIMES  0x06

    inline int done_clie_destroy(resp_head *dest_resp, const osev_clie *clie) {
        int desv, inde = CLIE_DESTROY_TIMES;
        for (; inde; --inde) {
            if (!(desv = clie_destroy_bzl(dest_resp, clie->conne_sock, &clie->clie_obid))) {
                if (OK == dest_resp->status_code) {
                    OSCO_CLOSE(clie->conne_sock);
                    return 0x00;
                }
            }
            sleep(CLIE_DESTROY_DELAY);
        }
        OSCO_CLOSE(clie->conne_sock);
        return desv ? desv : dest_resp->status_code;
    }

    inline int kaliv_clie_continue(resp_head *kaliv_resp, const osev_clie *clie) {
        CLIE_KALIVE_BZL(kaliv_resp, clie->conne_sock, &clie->clie_obid);
        return (OK == kaliv_resp->status_code) ? 0x00 : kaliv_resp->status_code;
    }

    // construct
    // construct // modify method

    // #define     EPOST_INSTRU   0x00
    // #define     EPOST_ATTRIB   0x01

    inline int lev3_const_post(resp_data_t *const_resp, const osev_clie *clie, osv_oid_t *cont_obid, const char **pamvp) {
        pamstyl_t pamsty;
        if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
            return -1;
        CLIE_CONST_BZL(const_resp, clie->conne_sock, ENTI_POST, cont_obid, &pamsty)
                //
        return (OK == const_resp->status_code) ? 0x00 : const_resp->status_code;
    }

    //#define     ESTAT_ECHO    0x00
    //#define     ESTAT_ATTRIB   0x01
    //#define     ESTAT_STATIS   0x02

    inline int lev3_const_statu(resp_data_t *const_resp, const osev_clie *clie, osv_oid_t *cont_obid, unsigned int layout, const char **pamvp) {
        pamstyl_t pamsty;
        if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
            return -1;
        CLIE_CONST_BZL(const_resp, clie->conne_sock, ENTI_STATU | layout, cont_obid, &pamsty)
                //
        return (OK == const_resp->status_code) ? 0x00 : const_resp->status_code;
    }

    inline int lev3_const_creat(resp_data_t *const_resp, const osev_clie *clie, osv_oid_t *cont_obid, const char **pamvp) {
        pamstyl_t pamsty;
        if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
            return -1;
        CLIE_CONST_BZL(const_resp, clie->conne_sock, ENTI_CREAT, cont_obid, &pamsty)
                //
        return (OK == const_resp->status_code) ? 0x00 : const_resp->status_code;
    }

    inline int lev3_const_drop(resp_data_t *const_resp, const osev_clie *clie, osv_oid_t *cont_obid, const char **pamvp) {
        pamstyl_t pamsty;
        if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
            return -1;
        CLIE_CONST_BZL(const_resp, clie->conne_sock, ENTI_DROP, cont_obid, &pamsty)
                //
        return (OK == const_resp->status_code) ? 0x00 : const_resp->status_code;
    }

    inline int lev3_const_updat(resp_data_t *const_resp, const osev_clie *clie, osv_oid_t *cont_obid, const char **pamvp) {
        pamstyl_t pamsty;
        if (INVA_ULOLO_VALU == pack_binpak_pamstyl(&pamsty, pamvp))
            return -1;
        CLIE_CONST_BZL(const_resp, clie->conne_sock, ENTI_UPDAT, cont_obid, &pamsty)
                //
        return (OK == const_resp->status_code) ? 0x00 : const_resp->status_code;
    }

    inline int lev3_const_inser(resp_data_t *const_resp, const osev_clie *clie, osv_oid_t *cont_obid, const char **pamvp) {
        pamstyl_t pamsty;
        if (INVA_ULOLO_VALU == pack_binpak_pamstyl(&pamsty, pamvp))
            return -1;
        CLIE_CONST_BZL(const_resp, clie->conne_sock, ENTI_INSER, cont_obid, &pamsty)
                //
        return (OK == const_resp->status_code) ? 0x00 : const_resp->status_code;
    }

    inline int lev3_const_searo(resp_data_t *const_resp, const osev_clie *clie, osv_oid_t *cont_obid, const char **pamvp) {
        pamstyl_t pamsty;
        if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
            return -1;
        CLIE_CONST_BZL(const_resp, clie->conne_sock, ENTI_SEARO, cont_obid, &pamsty)
                //
        return (OK == const_resp->status_code) ? 0x00 : const_resp->status_code;
    }

    inline int lev3_const_invok(resp_data_t *const_resp, const osev_clie *clie, osv_oid_t *cont_obid, const char **pamvp) {
        pamstyl_t pamsty;
        if (INVA_ULOLO_VALU == pack_einvo_pamstyl(&pamsty, (char **) pamvp))
            return -1;
        CLIE_CONST_BZL(const_resp, clie->conne_sock, ENTI_INVOK, cont_obid, &pamsty)
                //
        return (OK == const_resp->status_code) ? 0x00 : const_resp->status_code;
    }

    // query // modify method

    // #define     QPOST_INSTRU   0x00
    // #define     QPOST_ATTRIB   0x01

    inline int lv4p_query_post(resp_data_t *query_resp, const osev_clie *clie, const char **pamvp) {
        pamstyl_t pamsty;
        if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
            return -1;
        CLIE_QUERY_BZL(query_resp, clie->conne_sock, QUER_POST, &clie->clie_obid, &pamsty)
                //
        return (OK == query_resp->status_code) ? 0x00 : query_resp->status_code;
    }

    //#define     QSTAT_ECHO    0x00
    //#define     QSTAT_ATTRIB   0x01
    //#define     QSTAT_STATIS   0x02

    inline int lv4p_query_statu(resp_data_t *query_resp, const osev_clie *clie, unsigned int layout, const char **pamvp) {
        pamstyl_t pamsty;
        if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
            return -1;
        CLIE_QUERY_BZL(query_resp, clie->conne_sock, QUER_STATU | layout, &clie->clie_obid, &pamsty)
                //
        return (OK == query_resp->status_code) ? 0x00 : query_resp->status_code;
    }

    inline int lv4p_query_creat(resp_data_t *query_resp, const osev_clie *clie, const char **pamvp) {
        pamstyl_t pamsty;
        if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
            return -1;
        CLIE_QUERY_BZL(query_resp, clie->conne_sock, QUER_CREAT, &clie->clie_obid, &pamsty)
                //
        return (OK == query_resp->status_code) ? 0x00 : query_resp->status_code;
    }

    inline int lv4p_query_drop(resp_data_t *query_resp, const osev_clie *clie, const char **pamvp) {
        pamstyl_t pamsty;
        if (INVA_ULOLO_VALU == pack_dstri_pamstyl(&pamsty, pamvp))
            return -1;
        CLIE_QUERY_BZL(query_resp, clie->conne_sock, QUER_DROP, &clie->clie_obid, &pamsty)
                //
        return (OK == query_resp->status_code) ? 0x00 : query_resp->status_code;
    }

    inline int lv4p_query_updat(resp_data_t *query_resp, const osev_clie *clie, const char **pamvp) {
        pamstyl_t pamsty;
        if (INVA_ULOLO_VALU == pack_binnak_pamstyl(&pamsty, pamvp))
            return -1;
        CLIE_QUERY_BZL(query_resp, clie->conne_sock, QUER_UPDAT, &clie->clie_obid, &pamsty)
                //
        return (OK == query_resp->status_code) ? 0x00 : query_resp->status_code;
    }

    inline int lv4p_query_inser(resp_data_t *query_resp, const osev_clie *clie, const char **pamvp) {
        pamstyl_t pamsty;
        if (INVA_ULOLO_VALU == pack_binnak_pamstyl(&pamsty, pamvp))
            return -1;
        CLIE_QUERY_BZL(query_resp, clie->conne_sock, QUER_INSER, &clie->clie_obid, &pamsty)
                //
        return (OK == query_resp->status_code) ? 0x00 : query_resp->status_code;
    }

    inline int lv4p_query_searq(resp_data_t *query_resp, const osev_clie *clie, const char **pamvp) {
        pamstyl_t pamsty;
        if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
            return -1;
        CLIE_QUERY_BZL(query_resp, clie->conne_sock, QUER_SEARQ, &clie->clie_obid, &pamsty)
                //
        return (OK == query_resp->status_code) ? 0x00 : query_resp->status_code;
    }

    inline int lv4p_query_invok(resp_data_t *query_resp, const osev_clie *clie, const char **pamvp) {
        pamstyl_t pamsty;
        if (INVA_ULOLO_VALU == pack_qinvo_pamstyl(&pamsty, pamvp))
            return -1;
        CLIE_QUERY_BZL(query_resp, clie->conne_sock, QUER_INVOK, &clie->clie_obid, &pamsty)
                //
        return (OK == query_resp->status_code) ? 0x00 : query_resp->status_code;
    }

    inline int lv4p_query_facto(resp_data_t *query_resp, const osev_clie *clie, const char **pamvp) {
        pamstyl_t pamsty;
        if (INVA_ULOLO_VALU == pack_disti_pamstyl(&pamsty, pamvp))
            return -1;
        CLIE_QUERY_BZL(query_resp, clie->conne_sock, QUER_FACTO, &clie->clie_obid, &pamsty)
                //
        return (OK == query_resp->status_code) ? 0x00 : query_resp->status_code;
    }

    // get lv2pn version
    // trans-serve
    int lv2p_colle_versi(unsigned long long *lv2p_versi, const osev_clie *clie, const char *lv2pn);
#define FMTST_TIMEOUT_SECON  960 // 960s equl 16m
    int lev3_const_conat(cont_atti *conat, const osev_clie *clie, osv_oid_t *cont_obid, long time_out);
    //
    int lv2p_colle_attrib(unsigned long long *lv2p_versi, unsigned int *lv2p_extern, const osev_clie *clie, const char *lv2pn);

#ifdef __cplusplus
}
#endif

#endif /* PROTO_CONNE_H */


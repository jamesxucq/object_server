
#ifndef OSEV_CLIE_CLAN_H
#define OSEV_CLIE_CLAN_H

//
#include "function/funct_header.h"

#include "clie_macro.h"
#include "dstri_utili.h"
#include "reque_respo.h"
#include "excep_msg.h"
#include "osvp_auth.h"
#include "conatt.h"
#include "clie_obje.h"
#include "clie_bzl.h"

#include "parse_respo.h"

#ifdef __cplusplus
extern "C" {
#endif

    // trans-serve

    struct _osev_clie_ {
        // char osvp_uri[OSVPURI_LENGTH];
        osv_oid_t clie_obid; // osev / base obid
        char clie_name[OSEV_LENGTH]; // osev / base name
        int conne_sock;
    };

    typedef struct _osev_clie_ osev_clie;

    // 0x00:ok , -1:error

    int osev_clie_create(OUT resp_data_t *crea_resp, OUT osev_clie *clie, osvp_auth *clie_auth);
    int base_clie_create(OUT resp_data_t *crea_resp, OUT osev_clie *clie, osvp_auth *clie_auth);

    //

#define CLIE_DESTROY_DELAY  0x01
    // trans-serve
#define CLIE_DESTROY_TIMES  0x06

    inline int done_clie_destroy(resp_head *dest_resp, const osev_clie *clie) {
        int desv, inde = CLIE_DESTROY_TIMES;
        for (; inde; --inde) {
            if (!(desv = clie_destroy_bzl(dest_resp, clie->conne_sock, &clie->clie_obid))) {
                if (OK == dest_resp->status_code) {
                    OSCO_CLOSE(clie->conne_sock);
                    FINAL_CONATT_BZL()
                    return 0x00;
                }
            }
            sleep(CLIE_DESTROY_DELAY);
        }
        OSCO_CLOSE(clie->conne_sock);
        return desv ? -1 : dest_resp->status_code;
    }

    //
    int kaliv_clie_continue(resp_head *kaliv_resp, const osev_clie *clie);

    //
    // osev status // modify method // stat_obid: osev base obid;
    // osev privile // modify method // priv_obid: osev base obid
    // #define OPOST        0x10
    int osev_inten_post(resp_data_t *post_resp, const osev_clie *clie, osv_oid_t *post_obid, const char **pamvp);
    // #define     OSTAT_ECHO       0x00
    // #define     OSTAT_STATIS     0x01
    int osev_inten_statu(resp_data_t *statu_resp, const osev_clie *clie, osv_oid_t *stat_obid, unsigned int layout, const char **pamvp);
    // #define     OCOMD_OPEN       0x00 // start Create
    // #define     OCOMD_CLOSE      0x01 // shutdown
    int osev_inten_comnd(resp_data_t *comnd_resp, const osev_clie *clie, osv_oid_t *comd_obid, unsigned int layout, const char **pamvp);
    // #define     OPRIV_LIST       0x00
    // #define     OPRIV_ROLE       0x01
    // #define     OPRIV_USER       0x02
    int osev_inten_privi(resp_data_t *privi_resp, const osev_clie *clie, osv_oid_t *priv_obid, unsigned int layout, const char **pamvp);

    // base status // modify method // stat_obid: osev base obid;
    // base privile // modify method // priv_obid: osev base obid
    // #define BPOST        0x10
    int base_inten_post(resp_data_t *post_resp, const osev_clie *clie, osv_oid_t *post_obid, const char **pamvp);
    // #define     BSTAT_ECHO      0x00
    // #define     BSTAT_STATIS    0x01
    int base_inten_statu(resp_data_t *statu_resp, const osev_clie *clie, osv_oid_t *stat_obid, unsigned int layout, const char **pamvp);
    // #define     BCOMD_OPEN      0x00 // start Create
    // #define     BCOMD_CLOSE     0x01 // shutdown
    int base_inten_comnd(resp_data_t *comnd_resp, const osev_clie *clie, osv_oid_t *comd_obid, unsigned int layout, const char **pamvp);
    // #define     BPRIV_LIST       0x00
    // #define     BPRIV_ROLE       0x01
    // #define     BPRIV_USER       0x02
    int base_inten_privi(resp_data_t *privi_resp, const osev_clie *clie, osv_oid_t *priv_obid, unsigned int layout, const char **pamvp);

    // method invoke
    int lev1_invok_post(resp_data_t *invok_resp, const osev_clie *clie, osv_oid_t *lv2p_obid, const char **pamvp);
    // #define     ISTAT_LIST    0x00
    // #define     ISTAT_STATIS  0x01
    // parm[0x00]:name space parm[0x01]:list type
    int lev1_invok_statu(resp_data_t *invok_resp, const osev_clie *clie, osv_oid_t *lv2p_obid, unsigned int layout, const char **pamvp);
    int lev1_invok_creat(resp_data_t *invok_resp, const osev_clie *clie, osv_oid_t *lv2p_obid, const char **pamvp);
    int lev1_invok_repla(resp_data_t *invok_resp, const osev_clie *clie, osv_oid_t *lv2p_obid, const char **pamvp);
    int lev1_invok_drop(resp_data_t *invok_resp, const osev_clie *clie, osv_oid_t *lv2p_obid, const char **pamvp);
    int lev1_invok_integra(resp_data_t *invok_resp, const osev_clie *clie, osv_oid_t *lv2p_obid, const char **pamvp);
    int lev1_invok_reload(resp_data_t *invok_resp, const osev_clie *clie, osv_oid_t *lv2p_obid, const char **pamvp);

    // class invoke
    // class colle // modify method
    int lv2p_colle_post(resp_data_t *colle_resp, const osev_clie *clie, const char **pamvp);
    // #define     CSTAT_LIST    0x00
    // #define     CSTAT_STATIS  0x01
    // parm[0x00]:name space parm[0x01]:list type
    int lv2p_colle_statu(resp_data_t *colle_resp, const osev_clie *clie, unsigned int layout, const char **pamvp);
    int lv2p_colle_creat(resp_data_t *colle_resp, const osev_clie *clie, const char **pamvp);
    int lv2p_colle_repla(resp_data_t *colle_resp, const osev_clie *clie, const char **pamvp);
    int lv2p_colle_drop(resp_data_t *colle_resp, const osev_clie *clie, const char **pamvp);
    int lv2p_colle_integra(resp_data_t *colle_resp, const osev_clie *clie, const char **pamvp);
    int lv2p_colle_reload(resp_data_t *colle_resp, const osev_clie *clie, const char **pamvp);

    // construct
    // construct // modify method
    int lev3_const_post(resp_data_t *const_resp, const osev_clie *clie, osv_oid_t *cont_obid, const char **pamvp);
    // #define     ESTAT_ECHO    0x00
    // #define     ESTAT_ATTRIB   0x01
    // #define     ESTAT_STATIS   0x02
    int lev3_const_statu(resp_data_t *const_resp, const osev_clie *clie, osv_oid_t *cont_obid, unsigned int layout, const char **pamvp);
    int lev3_const_creat(resp_data_t *const_resp, const osev_clie *clie, osv_oid_t *cont_obid, const char **pamvp);
    int lev3_const_drop(resp_data_t *const_resp, const osev_clie *clie, osv_oid_t *cont_obid, const char **pamvp);
    int lev3_const_updat(resp_data_t *const_resp, const osev_clie *clie, osv_oid_t *cont_obid, const char **pamvp, cont_atti *conat);
    int lev3_const_inser(resp_data_t *const_resp, const osev_clie *clie, osv_oid_t *cont_obid, const char **pamvp, cont_atti *conat);
    int lev3_const_searo(resp_data_t *const_resp, const osev_clie *clie, osv_oid_t *cont_obid, const char **pamvp);
    int lev3_const_invok(resp_data_t *const_resp, const osev_clie *clie, osv_oid_t *cont_obid, const char **pamvp);

    // query // modify method
    // #define     QPOST_INSTRU   0x00
    // #define     QPOST_ATTRIB   0x01
    int lv4p_query_post(resp_data_t *query_resp, const osev_clie *clie, const char **pamvp);
    // #define     QSTAT_ECHO    0x00
    // #define     QSTAT_ATTRIB   0x01
    // #define     QSTAT_STATIS   0x02
    int lv4p_query_statu(resp_data_t *query_resp, const osev_clie *clie, unsigned int layout, const char **pamvp);
    int lv4p_query_creat(resp_data_t *query_resp, const osev_clie *clie, const char **pamvp);
    int lv4p_query_drop(resp_data_t *query_resp, const osev_clie *clie, const char **pamvp);
    int lv4p_query_updat(resp_data_t *query_resp, const osev_clie *clie, const char **pamvp, cont_atti *conat);
    int lv4p_query_inser(resp_data_t *query_resp, const osev_clie *clie, const char **pamvp, cont_atti *conat);
    int lv4p_query_searq(resp_data_t *query_resp, const osev_clie *clie, const char **pamvp);
    int lv4p_query_invok(resp_data_t *query_resp, const osev_clie *clie, const char **pamvp);
    int lv4p_query_facto(resp_data_t *query_resp, const osev_clie *clie, const char **pamvp);

    // get lv2pn version
    // trans-serve
    int lv2p_colle_versi(unsigned long long *lv2p_versi, const osev_clie *clie, const char *lv2pn);
    int lv2p_colle_extern(bool_osv *lv2p_extern, const osev_clie *clie, const char *lv2pn);
    int lv2p_colle_conte(char *lv2p_conte, const osev_clie *clie, const char *lv2pn);
    int lev1_invok_conte(char *lev1_conte, const osev_clie *clie, osv_oid_t *lv2p_obid, const char *lev1n);
#define FMTST_TIMEOUT_SECON  960 // 960s equl 16m
    int lev3_const_conat(cont_atti *conat, const osev_clie *clie, osv_oid_t *cont_obid, long time_out);
    int lv4p_query_conat(cont_atti *conat, const osev_clie *clie, const char *cont_iden, long time_out);


#ifdef __cplusplus
}
#endif

#endif /* OSEV_CLIE_CLAN_H */


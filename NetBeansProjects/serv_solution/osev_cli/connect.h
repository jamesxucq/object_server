
#ifndef CONNECT_H
#define CONNECT_H

#include "commo_header.h"
#include "osev_clie_clang.h"
#include "osvp_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    // 0:ok -1:err
    int conne_osev(osev_clie *oclie, osvp_auth *clie_auth);
    int conne_base(osev_clie *oclie, osvp_auth *clie_auth);

    // 0:ok -1:err
    int reconne_base(osev_clie *oclie, osvp_auth *clie_auth);
    void quit_osev(osev_clie *oclie);

    // resp_data *statu_resp
    int osev_leve_inte(resp_data_t *osev_resp, unsigned int levivk, unsigned int invok, osev_clie *oclie, osv_oid_t *osev_obid, const char **pamvp);
    int base_leve_inte(resp_data_t *base_resp, unsigned int levivk, unsigned int invok, osev_clie *oclie, osv_oid_t *base_obid, const char **pamvp);

    //
    // 0:ok -1:err
    int quit_cont(osev_clie *oclie, osvp_auth *clie_auth);
    void _quit_osev_(osev_clie *oclie);
    int leve_cont_one(resp_data_t *lev1_resp, unsigned int levivk, unsigned int invok, osev_clie *oclie, osv_oid_t *lv2p_obid, const char **pamvp);
    int leve_cont_twop(resp_data_t *lv2p_resp, unsigned int levivk, unsigned int invok, osev_clie *oclie, const char **pamvp);
    int leve_cont_thre(resp_data_t *lev3_resp, unsigned int levivk, unsigned int invok, osev_clie *oclie, osv_oid_t *cont_obid, const char **pamvp);
    int leve_cont_foup(resp_data_t *lv4p_resp, unsigned int levivk, unsigned int invok, osev_clie *oclie, const char **pamvp);


#ifdef __cplusplus
}
#endif

#endif /* CONNECT_H */


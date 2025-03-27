
/* 
 * File:   query_bzl.h
 * Author: James Xu
 *
 * Created on 2017.1.4, AM 9:22
 */

#ifndef QUERY_BZL_H
#define QUERY_BZL_H

#include "conattr.h"
#include "contain.h"

#ifdef __cplusplus
extern "C" {
#endif

    //int querbzl_create(char *data_directory);
    //int querbzl_destroy();

    //

#define QLOAD_CONTA_BZL(BLIST) qload_conta_meta(BLIST)


    // conta metadata
#define CREAT_CATTR_BZL(BASEN) creat_cont_atti(BASEN)
#define SEARC_CONTA_BZL(RESUL, BASEN, CONT_NAME, LVTP_TYPE) searc_conta_attri(RESUL, BASEN, CONT_NAME, LVTP_TYPE)
#define CHECK_LVTP_BZL(BASEN, LVTP_TYPE) check_catti_lv2p(BASEN, LVTP_TYPE)

    //
    int quer_statu_objid_bzl(respo_ctrl *resctl, base_valu *baval, char *contn);
    int quer_statu_name_bzl(respo_ctrl *resctl, base_valu *baval, osv_oid_t *cont_obid);
    int quer_statu_whole_bzl(respo_ctrl *resctl, base_valu *baval, user_privi *uepriv);
    //
    int quer_statu_attri_bzl(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu);
    int quer_statu_ustai_bzl(respo_ctrl *resctl, base_valu *baval, uint32 ustai_type); // statis
    int quer_statu_ostai_bzl(respo_ctrl *resctl, base_valu *baval, osv_oid_t *cont_obid); // statis
    int quer_statu_nstai_bzl(respo_ctrl *resctl, base_valu *baval, char *contn); // statis
    //
    int quer_creat_bzl(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu);
    int quer_drop_bzl(base_valu *baval, pams_valu *pamvu);

    //

    int quer_searq_bzl(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu);
    int quer_facto_bzl(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu);
    int quer_invok_bzl(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu);

    //
    int quer_updat_bzl(base_valu *baval, pams_valu *pamvu);
    int quer_inser_bzl(respo_ctrl *resctl, base_valu *baval, pams_valu *pamvu);

#ifdef __cplusplus
}
#endif

#endif /* QUERY_BZL_H */


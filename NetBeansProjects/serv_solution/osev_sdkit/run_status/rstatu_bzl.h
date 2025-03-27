
/* 
 * File:   rstatu_bzl.h
 * Author: James Xu
 *
 * Created on 2016.12.27, PM 1:49
 */

#ifndef RSTATU_BZL_H
#define RSTATU_BZL_H

#include "commo_header.h"
#include "rstat_utili.h"
#include "filli_statu.h"

#ifdef __cplusplus
extern "C" {
#endif


    //
    int rstabzl_create(char *data_directory);
    int rstabzl_destroy();

    // 0x00:ok -1:err
#define VALID_OPEN_BZL(BASEN) valid_base_opened(BASEN)
    //
    int echo_osev_bzl(respo_ctrl *resctl, char *basen);
    int echo_base_bzl(respo_ctrl *resctl, osv_oid_t *base_obid);

    //
#define STATU_RESET_RLEVE   0x00
#define STATU_RELOAD_PRIVI  0x01
    int reset_orlev_bzl(char *basen, uint32 lvmsk_code);
    int reset_brlev_bzl(osv_oid_t *base_obid, uint32 lvmsk_code);

    //
#define OSEV_STATI_OSEV 0x00
#define OSEV_STATI_BASE 0x01
    int ostai_osev_bzl(respo_ctrl *resctl);
    int ostai_base_bzl(respo_ctrl *resctl);

    int bstai_base_bzl(respo_ctrl *resctl, osv_oid_t *base_obid);

    //
#define QUARY_STATI_BASE 0x00
#define QUARY_STATI_CONTAIN 0x01 
    int quer_stasti_base_bzl(respo_ctrl *resctl, osv_oid_t *base_obid);

    //
    int opened_base_bzl(OUT char **base_openp, char *_oline_);

    //
#define ENAB_AUTHEN_BZL enab_authen_flag
#define DISAB_AUTHEN_BZL disab_authen_flag
#define VALID_AUTHEN_BZL valid_authen_enab

    //
#define PRODU_OBIDE_BZL(RESCTL, BASE_OBID) filli_obje_iden(RESCTL, BASE_OBID)

    //
    int init_runpriv_bzl(uint32 *run_level, char *basen);

    //
#define BASE_EXIST_BZL(BASEN) check_base_exist(BASEN)
#define OPEN_BASRLEV_BZL(BASEN, RUN_LEVEL) open_base_rlev(BASEN, RUN_LEVEL)
#define CLOSE_BASRLEV_BZL(BASEN) close_base_rlev(BASEN)

#ifdef __cplusplus
}
#endif

#endif /* RSTATU_BZL_H */


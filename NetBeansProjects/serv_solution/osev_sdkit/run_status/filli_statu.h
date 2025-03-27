
/* 
 * File:   filli_statu.h
 * Author: James Xu
 *
 * Created on 2017.1.5, AM 10:53
 */

#ifndef FILLI_STATU_H
#define FILLI_STATU_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    void filli_ostat_echo(respo_ctrl *resctl, osv_oid_t *osev_obid, int auth_stat);
    void filli_bstat_echo_running(respo_ctrl *resctl, char *basen, osv_oid_t *base_obid, int auth_stat, base_rstat *rstatu);
    void filli_bstat_echo_stopped(respo_ctrl *resctl, char *basen, osv_oid_t *base_obid, int auth_stat);

    //
    void filli_ostai_osev(respo_ctrl *resctl, osv_oid_t *osev_obid, int auth_stat);
    void filli_ostai_base(respo_ctrl *resctl, char **basnp);
    char *filli_bstai_base(respo_ctrl *resctl, char *basen, osv_oid_t *base_obid);
    char *filli_qstai_base(respo_ctrl *resctl, char *basen, osv_oid_t *base_obid);

    //
    void filli_obje_iden(respo_ctrl *resctl, osv_oid_t *base_obid);


#ifdef __cplusplus
}
#endif

#endif /* FILLI_STATU_H */


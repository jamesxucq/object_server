
/* 
 * File:   searq_decla_reco.h
 * Author: James Xu
 *
 * Created on 2022.10.31, PM 3:21
 */

#ifndef SEARQ_DECLA_RECO_H
#define SEARQ_DECLA_RECO_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    int condi_qdecl_reco(respo_ctrl *resctl, char *lv2pn, contain *scont, base_valu *baval, char *condi);
    int objid_qdecl_reco(respo_ctrl *resctl, rive_conne *rivcon, char *lv2pn, contain *scont, osv_oid_i *searq_obid);
    int trave_qdecl_reco(respo_ctrl *resctl, rive_conne *rivcon, char *lv2pn, contain *scont);

#ifdef __cplusplus
}
#endif

#endif /* SEARQ_DECLA_RECO_H */


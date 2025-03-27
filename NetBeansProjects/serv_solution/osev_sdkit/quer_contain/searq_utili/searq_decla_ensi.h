
/* 
 * File:   searq_decla_ensi.h
 * Author: James Xu
 *
 * Created on 2022.9.23, PM 4:31
 */

#ifndef SEARQ_DECLA_ENSI_H
#define SEARQ_DECLA_ENSI_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    int condi_qdecl_ensi(respo_ctrl *resctl, contain *scont, base_valu *baval, lv2pme *lv2me, char *condi);
    int objid_qdecl_ensi(respo_ctrl *resctl, rive_conne *rivcon, contain *scont, lv2pme *lv2me, osv_oid_i *searq_obid);
    int trave_qdecl_ensi(respo_ctrl *resctl, rive_conne *rivcon, contain *scont, lv2pme *lv2me);


#ifdef __cplusplus
}
#endif

#endif /* SEARQ_DECLA_ENSI_H */


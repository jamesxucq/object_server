
/* 
 * File:   searq_decla_resi.h
 * Author: James Xu
 *
 * Created on 2022.10.26, PM 3:42
 */

#ifndef SEARQ_DECLA_RESI_H
#define SEARQ_DECLA_RESI_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    int condi_qdecl_resi(respo_ctrl *resctl, char *lv2pn, contain *scont, base_valu *baval, char *condi);
    int objid_qdecl_resi(respo_ctrl *resctl, rive_conne *rivcon, char *lv2pn, contain *scont, osv_oid_i *searq_obid);
    int trave_qdecl_resi(respo_ctrl *resctl, rive_conne *rivcon, char *lv2pn, contain *scont);


#ifdef __cplusplus
}
#endif

#endif /* SEARQ_DECLA_RESI_H */


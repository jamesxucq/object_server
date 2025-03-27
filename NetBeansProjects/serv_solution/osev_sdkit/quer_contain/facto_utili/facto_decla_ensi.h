
/* 
 * File:   facto_decla_ensi.h
 * Author: James Xu
 *
 * Created on 2022.10.10, AM 8:27
 */

#ifndef FACTO_DECLA_ENSI_H
#define FACTO_DECLA_ENSI_H

#ifdef __cplusplus
extern "C" {
#endif

    //

    int condi_fdecl_ensi(respo_ctrl *resctl, contain *scont, base_valu *baval, lv2pme *lv2me, char *condi);
    int objid_fdecl_ensi(respo_ctrl *resctl, rive_conne *rivcon, contain *scont, lv2pme *lv2me, osv_oid_i *searq_obid);
    int trave_fdecl_ensi(respo_ctrl *resctl, rive_conne *rivcon, contain *scont, lv2pme *lv2me);
    
#ifdef __cplusplus
}
#endif

#endif /* FACTO_DECLA_ENSI_H */


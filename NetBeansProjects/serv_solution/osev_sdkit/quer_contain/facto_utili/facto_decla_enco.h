
/* 
 * File:   facto_decla_enco.h
 * Author: James Xu
 *
 * Created on 2022.10.31, PM 3:19
 */

#ifndef FACTO_DECLA_ENCO_H
#define FACTO_DECLA_ENCO_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    
    int condi_fdecl_enco(respo_ctrl *resctl, contain **sconp, base_valu *baval, lv2pme *lv2me, char *condi);
    int objid_fdecl_enco(respo_ctrl *resctl, rive_conne *rivcon, contain **sconp, lv2pme *lv2me, osv_oid_i *facto_obid);
    int trave_fdecl_enco(respo_ctrl *resctl, rive_conne *rivcon, contain **sconp, lv2pme *lv2me);

#ifdef __cplusplus
}
#endif

#endif /* FACTO_DECLA_ENCO_H */


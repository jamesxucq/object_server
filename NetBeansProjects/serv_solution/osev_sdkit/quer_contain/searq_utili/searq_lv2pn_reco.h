
/* 
 * File:   searq_lv2pn_reco.h
 * Author: James Xu
 *
 * Created on 2022.10.31, PM 3:22
 */

#ifndef SEARQ_LVTPN_RECO_H
#define SEARQ_LVTPN_RECO_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    int condi_qlv2n_reco(respo_ctrl *resctl, contain *scont, contain **rconp, base_valu *baval, lv2pme **lv2mep, char *condi);
    int objid_qlv2n_reco(respo_ctrl *resctl, rive_conne *rivcon, contain *scont, contain **rconp, lv2pme **lv2mep, osv_oid_i *searq_obid);
    int trave_qlv2n_reco(respo_ctrl *resctl, rive_conne *rivcon, contain *scont, contain **rconp, lv2pme **lv2mep);

    //
    int objid_qlv2n_oreco(respo_ctrl *resctl, rive_conne *rivcon, contain **rconp, lv2pme **lv2mep, osv_oid_i *searq_obid);
    
#ifdef __cplusplus
}
#endif

#endif /* SEARQ_LVTPN_RECO_H */


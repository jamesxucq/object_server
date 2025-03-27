
/* 
 * File:   searq_lv2pn_resi.h
 * Author: James Xu
 *
 * Created on 2022.10.26, PM 3:42
 */

#ifndef SEARQ_LVTPN_RESI_H
#define SEARQ_LVTPN_RESI_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    int condi_qlv2n_resi(respo_ctrl *resctl, contain *scont, contain *rcont, base_valu *baval, lv2pme **lv2mep, char *condi);
    int objid_qlv2n_resi(respo_ctrl *resctl, rive_conne *rivcon, contain *scont, contain *rcont, lv2pme **lv2mep, osv_oid_i *searq_obid);
    int trave_qlv2n_resi(respo_ctrl *resctl, rive_conne *rivcon, contain *scont, contain *rcont, lv2pme **lv2mep);

    //
    int objid_qlv2n_oresi(respo_ctrl *resctl, rive_conne *rivcon, contain *rcont, lv2pme **lv2mep, osv_oid_i *searq_obid);

#ifdef __cplusplus
}
#endif

#endif /* SEARQ_LVTPN_RESI_H */


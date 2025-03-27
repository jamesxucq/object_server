
/* 
 * File:   facto_lv2pn_enco.h
 * Author: James Xu
 *
 * Created on 2022.10.31, PM 3:19
 */

#ifndef FACTO_LVTPN_ENCO_H
#define FACTO_LVTPN_ENCO_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    int condi_flv2n_enco(respo_ctrl *resctl, contain **sconp, base_valu *baval, lv2pme **lv2mep, char *condi);
    int objid_flv2n_enco(respo_ctrl *resctl, rive_conne *rivcon, contain **sconp, lv2pme **lv2mep, osv_oid_i *facto_obid);
    int trave_flv2n_enco(respo_ctrl *resctl, rive_conne *rivcon, contain **sconp, lv2pme **lv2mep);


#ifdef __cplusplus
}
#endif

#endif /* FACTO_LVTPN_ENCO_H */


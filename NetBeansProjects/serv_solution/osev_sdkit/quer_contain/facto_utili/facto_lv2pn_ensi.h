
/* 
 * File:   facto_lv2pn_ensi.h
 * Author: James Xu
 *
 * Created on 2022.10.10, AM 8:28
 */

#ifndef FACTO_LVTPN_ENSI_H
#define FACTO_LVTPN_ENSI_H

#ifdef __cplusplus
extern "C" {
#endif

    // ensi
    int condi_flv2n_ensi(respo_ctrl *resctl, contain *scont, base_valu *baval, lv2pme **lv2mep, char *condi);
    int objid_flv2n_ensi(respo_ctrl *resctl, rive_conne *rivcon, contain *scont, lv2pme **lv2mep, osv_oid_i *facto_obid);
    int trave_flv2n_ensi(respo_ctrl *resctl, rive_conne *rivcon, contain *scont, lv2pme **lv2mep);

    // enob
    int condi_flv2n_enob(respo_ctrl *resctl, contain *scont, base_valu *baval, lv2pme **lv2mep, char *condi);
    int objid_flv2n_enob(respo_ctrl *resctl, rive_conne *rivcon, contain *scont, lv2pme **lv2mep, osv_oid_i *facto_obid);
    int trave_flv2n_enob(respo_ctrl *resctl, rive_conne *rivcon, contain *scont, lv2pme **lv2mep);

    //

#define CONDI_FLTPN_ENSI(FACTO_VALU, RESCTL, SCONT, BAVAL, LVTME, CONDI) { \
        if (OBID_EQUALI(&(LVTME[0x00])->lv2p_obid, &(SCONT->lv2p_type))) { \
            FACTO_VALU = condi_flv2n_enob(RESCTL, SCONT, BAVAL, LVTME, CONDI); \
        } else FACTO_VALU = condi_flv2n_ensi(RESCTL, SCONT, BAVAL, LVTME, CONDI); \
    }

#define OBJID_FLTPN_ENSI(FACTO_VALU, RESCTL, RVCON, SCONT, LVTME, OBJE_OBID) { \
        if (OBID_EQUALI(&(LVTME[0x00])->lv2p_obid, &(SCONT->lv2p_type))) { \
            FACTO_VALU = objid_flv2n_enob(RESCTL, RVCON, SCONT, LVTME, OBJE_OBID); \
        } else FACTO_VALU = objid_flv2n_ensi(RESCTL, RVCON, SCONT, LVTME, OBJE_OBID); \
    }

#define TRAVE_FLTPN_ENSI(FACTO_VALU, RESCTL, RVCON, SCONT, LVTME) { \
        if (OBID_EQUALI(&(LVTME[0x00])->lv2p_obid, &(SCONT->lv2p_type))) { \
            FACTO_VALU = trave_flv2n_enob(RESCTL, RVCON, SCONT, LVTME); \
        } else FACTO_VALU = trave_flv2n_ensi(RESCTL, RVCON, SCONT, LVTME); \
    }

#ifdef __cplusplus
}
#endif

#endif /* FACTO_LVTPN_ENSI_H */


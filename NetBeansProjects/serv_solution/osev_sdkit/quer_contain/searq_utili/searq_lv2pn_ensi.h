
/* 
 * File:   searq_lv2pn_ensi.h
 * Author: James Xu
 *
 * Created on 2022.9.23, PM 4:29
 */

#ifndef SEARQ_LVTPN_ENSI_H
#define SEARQ_LVTPN_ENSI_H

#ifdef __cplusplus
extern "C" {
#endif

    // ensi
    int condi_qlv2n_ensi(respo_ctrl *resctl, contain *scont, base_valu *baval, lv2pme *lv2me, char *condi);
    int objid_qlv2n_ensi(respo_ctrl *resctl, rive_conne *rivcon, contain *scont, lv2pme *lv2me, osv_oid_i *searq_obid);
    int trave_qlv2n_ensi(respo_ctrl *resctl, rive_conne *rivcon, contain *scont, lv2pme *lv2me);

    // enob
    int condi_qlv2n_enob(respo_ctrl *resctl, contain *scont, base_valu *baval, lv2pme *lv2me, char *condi);
    int objid_qlv2n_enob(respo_ctrl *resctl, rive_conne *rivcon, contain *scont, osv_oid_i *searq_obid);
    int trave_qlv2n_enob(respo_ctrl *resctl, rive_conne *rivcon, contain *scont);

    //

#define CONDI_QLTPN_ENSI(SEARQ_VALU, RESCTL, SCONT, BAVAL, LVTME, CONDI) { \
        if (OBID_EQUALI(&(LVTME)->lv2p_obid, &(SCONT->lv2p_type))) { \
            SEARQ_VALU = condi_qlv2n_enob(RESCTL, SCONT, BAVAL, LVTME, CONDI); \
        } else SEARQ_VALU = condi_qlv2n_ensi(RESCTL, SCONT, BAVAL, LVTME, CONDI); \
    }

#define OBJID_QLTPN_ENSI(SEARQ_VALU, RESCTL, RVCON, SCONT, LVTME, OBJE_OBID) { \
        if (OBID_EQUALI(&(LVTME)->lv2p_obid, &(SCONT->lv2p_type))) { \
            SEARQ_VALU = objid_qlv2n_enob(RESCTL, RVCON, SCONT, OBJE_OBID); \
        } else SEARQ_VALU = objid_qlv2n_ensi(RESCTL, RVCON, SCONT, LVTME, OBJE_OBID); \
    }

#define TRAVE_QLTPN_ENSI(SEARQ_VALU, RESCTL, RVCON, SCONT, LVTME) { \
        if (OBID_EQUALI(&(LVTME)->lv2p_obid, &(SCONT->lv2p_type))) { \
            SEARQ_VALU = trave_qlv2n_enob(RESCTL, RVCON, SCONT); \
        } else SEARQ_VALU = trave_qlv2n_ensi(RESCTL, RVCON, SCONT, LVTME); \
    }

#ifdef __cplusplus
}
#endif

#endif /* SEARQ_LVTPN_ENSI_H */


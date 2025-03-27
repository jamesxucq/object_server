
/* 
 * File:   searq_conta_ensi.h
 * Author: James Xu
 *
 * Created on 2022.9.23, PM 4:05
 */

#ifndef SEARQ_CONTA_ENSI_H
#define SEARQ_CONTA_ENSI_H

#include "commo_header.h"
#include "rive_bzl.h"

#ifdef __cplusplus
extern "C" {
#endif

    // ensi
    int condi_qcont_ensi(respo_ctrl *resctl, contain *dcont, stati_scont *scont, base_valu *baval, lv2pme *lv2me, char *condi);
    int objid_qcont_ensi(respo_ctrl *resctl, rive_conne *rivcon, contain *dcont, stati_scont *scont, lv2pme *lv2me, osv_oid_i *searq_obid);
    int trave_qcont_ensi(respo_ctrl *resctl, rive_conne *rivcon, contain *dcont, stati_scont *scont, lv2pme *lv2me);

    // enob
    int condi_qcont_enob(respo_ctrl *resctl, contain *dcont, stati_scont *scont, base_valu *baval, lv2pme *lv2me, char *condi);
    int objid_qcont_enob(respo_ctrl *resctl, rive_conne *rivcon, contain *dcont, stati_scont *scont, osv_oid_i *searq_obid);
    int trave_qcont_enob(respo_ctrl *resctl, rive_conne *rivcon, contain *dcont, stati_scont *scont);

    //

#define CONDI_QCONT_ENSI(SEARQ_VALU, RESCTL, DCONT, SCONT, BAVAL, LVTME, CONDI) { \
        if (OBID_EQUALI(&(DCONT->lv2p_type), SCONT->lv2p_type)) { \
            SEARQ_VALU = condi_qcont_enob(RESCTL, DCONT, SCONT, BAVAL, LVTME, CONDI); \
        } else SEARQ_VALU = condi_qcont_ensi(RESCTL, DCONT, SCONT, BAVAL, LVTME, CONDI); \
    }

#define OBJID_QCONT_ENSI(SEARQ_VALU, RESCTL, RVCON, DCONT, SCONT, LVTME, OBJE_OBID) { \
        if (OBID_EQUALI(&(DCONT->lv2p_type), SCONT->lv2p_type)) { \
            SEARQ_VALU = objid_qcont_enob(RESCTL, RVCON, DCONT, SCONT, OBJE_OBID); \
        } else SEARQ_VALU = objid_qcont_ensi(RESCTL, RVCON, DCONT, SCONT, LVTME, OBJE_OBID); \
    }

#define TRAVE_QCONT_ENSI(SEARQ_VALU, RESCTL, RVCON, DCONT, SCONT, LVTME) { \
        if (OBID_EQUALI(&(DCONT->lv2p_type), SCONT->lv2p_type)) { \
            SEARQ_VALU = trave_qcont_enob(RESCTL, RVCON, DCONT, SCONT); \
        } else SEARQ_VALU = trave_qcont_ensi(RESCTL, RVCON, DCONT, SCONT, LVTME); \
    }


    //
    int build_stati_scont(stati_scont *sscon, contain **sconp);

    //
    int fill_check_rcont(contain *contp, stati_scont *sscon);
    int robk_fichk_rcont(contain *contp, stati_scont *sscon);


#ifdef __cplusplus
}
#endif

#endif /* SEARQ_CONTA_ENSI_H */


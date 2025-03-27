
/* 
 * File:   facto_conta_ensi.h
 * Author: James Xu
 *
 * Created on 2022.10.10, 8:27
 */

#ifndef FACTO_CONTA_ENSI_H
#define FACTO_CONTA_ENSI_H

#include "commo_header.h"
#include "rive_bzl.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int condi_fcont_ensi(respo_ctrl *resctl, contain *dcont, contain *scont, base_valu *baval, lv2pme **lv2mep, char *condi);
    int objid_fcont_ensi(respo_ctrl *resctl, rive_conne *rivcon, contain *dcont, contain *scont, lv2pme **lv2mep, osv_oid_i *facto_obid);
    int trave_fcont_ensi(respo_ctrl *resctl, rive_conne *rivcon, contain *dcont, contain *scont, lv2pme **lv2mep);

    //
    int condi_fcont_enob(respo_ctrl *resctl, contain *dcont, contain *scont, base_valu *baval, lv2pme **lv2mep, char *condi);
    int objid_fcont_enob(respo_ctrl *resctl, rive_conne *rivcon, contain *dcont, contain *scont, lv2pme **lv2mep, osv_oid_i *facto_obid);
    int trave_fcont_enob(respo_ctrl *resctl, rive_conne *rivcon, contain *dcont, contain *scont, lv2pme **lv2mep);

    //
#define CONDI_FCONT_ENSI(FACTO_VALU, RESCTL, DCONT, SCONT, BAVAL, LVTME, CONDI) { \
        if (OBID_EQUALI(&(DCONT->lv2p_type), &(SCONT->lv2p_type))) { \
            FACTO_VALU = condi_fcont_enob(RESCTL, DCONT, SCONT, BAVAL, LVTME, CONDI); \
        } else FACTO_VALU = condi_fcont_ensi(RESCTL, DCONT, SCONT, BAVAL, LVTME, CONDI); \
    }

#define OBJID_FCONT_ENSI(FACTO_VALU, RESCTL, RVCON, DCONT, SCONT, LVTME, OBJE_OBID) { \
        if (OBID_EQUALI(&(DCONT->lv2p_type), &(SCONT->lv2p_type))) { \
            FACTO_VALU = objid_fcont_enob(RESCTL, RVCON, DCONT, SCONT, LVTME, OBJE_OBID); \
        } else FACTO_VALU = objid_fcont_ensi(RESCTL, RVCON, DCONT, SCONT, LVTME, OBJE_OBID); \
    }

#define TRAVE_FCONT_ENSI(FACTO_VALU, RESCTL, RVCON, DCONT, SCONT, LVTME) { \
        if (OBID_EQUALI(&(DCONT->lv2p_type), &(SCONT->lv2p_type))) { \
            FACTO_VALU = trave_fcont_enob(RESCTL, RVCON, DCONT, SCONT, LVTME); \
        } else FACTO_VALU = trave_fcont_ensi(RESCTL, RVCON, DCONT, SCONT, LVTME); \
    }

#ifdef __cplusplus
}
#endif

#endif /* FACTO_CONTA_ENSI_H */


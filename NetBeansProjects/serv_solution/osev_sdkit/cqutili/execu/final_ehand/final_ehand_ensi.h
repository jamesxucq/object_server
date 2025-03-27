
/* 
 * File:   final_ehand_ensi.h
 * Author: James Xu
 *
 * Created on 2021.6.1, PM1:56
 */

#ifndef FINAL_EHAND_ENSI_H
#define FINAL_EHAND_ENSI_H

#include "../conte_resou.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int hand_final_searo_ensi(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha, lv2pme *lv2me, char *contn);

    //
    int hfina_searq_conta_ensi(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha);
    int hfina_searq_conta_enob(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha);
    int hfina_searq_lv2pn_ensi(plan_node_ensi *firspn);
    int hfina_searq_lv2pn_enob(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha, lv2pme *lv2me, plan_node_ensi *finapn);

    //
    int hfina_facto_conta_ensi(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha, plan_node_ensi *finapn);
    int hfina_facto_conta_enob(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha, plan_node_ensi *finapn);
    int hfina_facto_lv2pn_ensi(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha, lv2pme **lv2mep, plan_node_ensi *finapn);
    int hfina_facto_lv2pn_enob(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha, lv2pme **lv2mep, plan_node_ensi *finapn);

    //
    int hand_final_dropo(plan_node_ensi *resupn, rive_conne *rivcon, rive_ha *stora_ha, char *contn);
    int hand_final_invoko(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, char *contn);

    //
    int hfina_refro_rcont_ensi(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha);

#ifdef __cplusplus
}
#endif

#endif /* FINAL_EHAND_ENSI_H */


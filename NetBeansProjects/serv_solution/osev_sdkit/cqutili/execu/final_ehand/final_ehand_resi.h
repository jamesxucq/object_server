
/* 
 * File:   final_ehand_resi.h
 * Author: James Xu
 *
 * Created on 2022.10.27, PM 1:44
 */

#ifndef FINAL_EHAND_RESI_H
#define FINAL_EHAND_RESI_H

//
#include "../conte_resou.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int hand_final_searo_rssi(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha, char *contn);
    int hand_final_searo_rsob(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha, char *contn);

    //
    int hand_final_searo_rdsi(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha, char *contn);
    int hand_final_searo_rdob(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha, char *contn);

    //
    int hfina_searq_lv2pn_resi(plan_node_ensi *firspn, rive_conne *rivcon, rive_ha *stora_ha, lv2pme **lv2mep, plan_node_ensi *finapn);

#ifdef __cplusplus
}
#endif

#endif /* FINAL_EHAND_RESI_H */



/* 
 * File:   final_ehand_reco.h
 * Author: James Xu
 *
 * Created on 2024.6.20, AM 9:40
 */

#ifndef FINAL_EHAND_RECO_H
#define FINAL_EHAND_RECO_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    int hand_final_searo_rsco(plan_node_enco *firspn, rive_conne *rivcon, rive_ha *stora_ha, char *contn);
    int hand_final_searo_rdco(plan_node_enco *firspn, rive_conne *rivcon, rive_ha *stora_ha, char *contn);

    //
    int hfina_searq_lv2pn_reco(plan_node_enco *firspn, rive_conne *rivcon, rive_ha *stora_ha, lv2pme **lv2mep, plan_node_enco *finapn);


#ifdef __cplusplus
}
#endif

#endif /* FINAL_EHAND_RECO_H */


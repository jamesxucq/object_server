
/* 
 * File:   final_ehand_enco.h
 * Author: James Xu
 *
 * Created on 2022.11.1, AM 9:46
 */

#ifndef FINAL_EHAND_ENCO_H
#define FINAL_EHAND_ENCO_H

// #include "plan/quer_plan_enco.h"
#include "../conte_resou.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int hfina_searq_conta_enco(plan_node_enco *firspn, rive_conne *rivcon, rive_ha *stora_ha);
    int hfina_searq_lv2pn_enco(plan_node_enco *firspn);
    int hfina_facto_conta_enco(plan_node_enco *firspn, rive_conne *rivcon, rive_ha *stora_ha, lv2pme **lv2mep, plan_node_enco *finapn);
    int hfina_facto_lv2pn_enco(plan_node_enco *firspn, rive_conne *rivcon, rive_ha *stora_ha, lv2pme **lv2mep, plan_node_enco *finapn);


#ifdef __cplusplus
}
#endif

#endif /* FINAL_EHAND_ENCO_H */


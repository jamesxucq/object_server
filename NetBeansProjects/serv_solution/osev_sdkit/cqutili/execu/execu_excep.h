
/* 
 * File:   execu_excep.h
 * Author: James Xu
 *
 * Created on 2022.4.21, 9:49
 */

#ifndef EXECU_EXCEP_H
#define EXECU_EXCEP_H

// #include "plan/quer_plan_ensi.h"
// #include "plan/quer_plan_enco.h"
#include "conte_resou.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    int hand_searo_excep_ensi(plan_node_ensi *quer_tok, plan_node_ensi *resupn, physi_conte *phys_cont, rive_conne *rivcon, rive_ha *stora_ha);
    int hand_searo_excep_enco(plan_node_enco *quer_tok, plan_node_enco *resupn, physi_conte *phys_cont, rive_conne *rivcon, rive_ha *stora_ha);

    //
    int hand_searq_excep_ensi(plan_node_ensi *quer_tok, plan_node_ensi *resupn, physi_conte *phys_cont, rive_conne *rivcon, rive_ha *stora_ha);
    int hand_searq_excep_enco(plan_node_enco *quer_tok, plan_node_enco *resupn, physi_conte *phys_cont, rive_conne *rivcon, rive_ha *stora_ha);

    //
    int hand_facto_excep_ensi(plan_node_ensi *quer_tok, plan_node_ensi *resupn, physi_conte *phys_cont, rive_conne *rivcon, rive_ha *stora_ha);
    int hand_facto_excep_enco(plan_node_enco *quer_tok, plan_node_enco *resupn, physi_conte *phys_cont, rive_conne *rivcon, rive_ha *stora_ha);

    //

    int hand_invoko_excep(plan_node_ensi *quer_tok, plan_node_ensi *resupn, physi_conte *phys_cont, rive_conne *rivcon, rive_ha *stora_ha);

    //
    int hand_dropo_excep(plan_node_ensi *quer_tok, plan_node_ensi *resupn, physi_conte *phys_cont, rive_conne *rivcon, rive_ha *stora_ha);

#ifdef __cplusplus
}
#endif

#endif /* EXECU_EXCEP_H */


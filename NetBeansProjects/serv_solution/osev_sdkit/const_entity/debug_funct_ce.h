
/* 
 * File:   debug_funct_ce.h
 * Author: James Xu
 *
 * Created on 2022.11.17, PM 4:10
 */

#ifndef DEBUG_FUNCT_CE_H
#define DEBUG_FUNCT_CE_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    void p_plan_node(plan_node_ensi *quer_tok);
    void p_lev1me(lev1me *lv1me);

#ifdef _DEBUG
#define PRIN_plan_node p_plan_node
#define PRIN_lev1me p_lev1me
#else
#define PRIN_plan_node(...)
#define PRIN_lev1me(...)
#endif

#ifdef __cplusplus
}
#endif

#endif /* DEBUG_FUNCT_CE_H */


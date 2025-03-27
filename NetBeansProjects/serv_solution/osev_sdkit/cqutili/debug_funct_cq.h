
/* 
 * File:   debug_funct_cq.h
 * Author: James Xu
 *
 * Created on 2022.11.1, PM 4:23
 */

#ifndef DEBUG_FUNCT_CQ_H
#define DEBUG_FUNCT_CQ_H

#include "kcomm_header.h"
// #include "plan/field_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    void p_state(pastat *state);
    void p_leaf_vato(valu_toke *valtok);
    void p_invo_vato(valu_toke *valtok);
    void p_invok(leaf_list *lealst);
    void p_synt_node(oper_node *synt_node);
    void p_field_resul_enco(field_resul_co *fieres);

#ifdef _DEBUG
#define PRIN_state p_state
#define PRIN_leaf_vato p_leaf_vato
#define PRIN_invo_vato p_invo_vato
#define PRIN_invok p_invok
#define PRIN_synt_node p_synt_node
#define PRIN_field_resul_enco p_field_resul_enco
#else
#define PRIN_state(...)
#define PRIN_leaf_vato(...)
#define PRIN_invo_vato(...)
#define PRIN_invok(...)
#define PRIN_synt_node(...)
#define PRIN_field_resul_enco(...)
#endif
    
    
#ifdef __cplusplus
}
#endif

#endif /* DEBUG_FUNCT_CQ_H */


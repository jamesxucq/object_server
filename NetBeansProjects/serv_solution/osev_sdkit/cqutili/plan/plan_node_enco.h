
/* 
 * File:   plan_node_enco.h
 * Author: James Xu
 *
 * Created on 2022.4.20, 2:09
 */

#ifndef PLAN_NODE_ENCO_H
#define PLAN_NODE_ENCO_H

#include "commo_header.h"
// #include "gramm/synta_tree.h"
#include "plan_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    struct _plan_node_enco_ {
        unsigned int acti_oper;
        char cont_name[CONTA_LENGTH]; // container name

        union { // resul_set;
            FILE *resul_set;
            respo_ctrl *resctl;
        };

        union {
            struct _plan_node_enco_ *left_chil;
            struct _plan_node_enco_ *resul_node;
            char source_str[LVTNOD_LENGTH];
        };

        union {
            leaf_list *parm_list;
            field_resul_co *fieres;
        };

        union {
            struct _plan_node_enco_ *righ_chil;
            long long lolo_valu;
            unsigned long long ullo_valu;
            double doub_valu;
            char stri_valu[MAX_TLENG];
        };

    };

    typedef struct _plan_node_enco_ plan_node_enco;

    //
    plan_node_enco *open_curso_enco(plan_node_enco *querpn, contain **qcontp);
    plan_node_enco *close_curso_enco(plan_node_enco *querpn, contain **qcontp);
    plan_node_enco *open_curso_rsco(plan_node_enco *querpn, stati_scont *qscont);
    plan_node_enco *close_curso_rsco(plan_node_enco *querpn, stati_scont *qscont);

    // recurs synta plan multi
    plan_node_enco *synt_plan_enco(plan_node_enco *querpn, oper_node *synt_node, contain **qcontp);
    plan_node_enco *synt_plan_rsco(plan_node_enco *querpn, oper_node *synt_node, stati_scont *qscont);

    // LVTNOD_COUNT
#define CREA_LVTP_NDCO(NODE_COUN) ((lv2p_prop *) malloc(NODE_COUN * sizeof (lv2p_prop)))
#define DELE_LVTP_NDCO(L2_DAT) (free(L2_DAT))

    //
    plan_node_enco *CREAT_PLAN_NODE_ENCO(int count);
    void DESTR_PLAN_NODE_ENCO(plan_node_enco *querpn);

    //
    void set_initi_valu_enco(plan_node_enco *querpn, plan_node_enco *plan_head);


#ifdef __cplusplus
}
#endif

#endif /* PLAN_NODE_ENCO_H */


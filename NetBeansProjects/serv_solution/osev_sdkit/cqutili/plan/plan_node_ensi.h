
/* 
 * File:   plan_node_ensi.h
 * Author: James
 *
 * Created on 2018.12.14, PM 2:27
 */

#ifndef PLAN_NODE_ENSI_H
#define PLAN_NODE_ENSI_H

#include "commo_header.h"
// #include "gramm/synta_tree.h"
#include "plan_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    struct _plan_node_ensi_ {
        unsigned int acti_oper;
        char cont_name[CONTA_LENGTH]; // container name

        union { // resul_set;
            FILE *resul_set;
            respo_ctrl *resctl;
        };

        union {
            struct _plan_node_ensi_ *left_chil;
            struct _plan_node_ensi_ *resul_node;
            char source_str[LVTNOD_LENGTH];
        };

        leaf_list *parm_list;

        union {
            struct _plan_node_ensi_ *righ_chil;
            long long lolo_valu;
            unsigned long long ullo_valu;
            double doub_valu;
            char stri_valu[MAX_TLENG];
        };
    };

    typedef struct _plan_node_ensi_ plan_node_ensi;

    //
    plan_node_ensi *CREAT_PLAN_NODE_ENSI(int count);
    void DESTR_PLAN_NODE_ENSI(plan_node_ensi *querpn);


    //
    plan_node_ensi *open_curso_ensi(plan_node_ensi *querpn, contain *qcontp);
    plan_node_ensi *close_curso_ensi(plan_node_ensi *querpn, contain *qcontp);
    plan_node_ensi *open_curso_rssi(plan_node_ensi *querpn, stati_scont *qscont);
    plan_node_ensi *close_curso_rssi(plan_node_ensi *querpn, stati_scont *qscont);

    // recurs synta plan single
    plan_node_ensi *synt_plan_ensi(plan_node_ensi *querpn, oper_node *synt_node, contain *qcontp);
    plan_node_ensi *synt_plan_rssi(plan_node_ensi *querpn, oper_node *synt_node, stati_scont *qscont);
    void set_initi_valu_ensi(plan_node_ensi *querpn, plan_node_ensi *plan_head);

#define CREA_LVTP_DASI(NODE_COUN) ((lv2p_prop *) malloc(NODE_COUN * sizeof (lv2p_prop)))
#define DELE_LVTP_DASI(L2_DAT) (free(L2_DAT))


#ifdef __cplusplus
}
#endif

#endif /* PLAN_NODE_ENSI_H */


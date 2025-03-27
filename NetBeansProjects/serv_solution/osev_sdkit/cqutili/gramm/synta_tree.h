
/* 
 * File:   synta_tree.h
 * Author: James
 *
 * Created on 2018.12.10, PM 4:43
 */

#ifndef SYNTA_TREE_H
#define SYNTA_TREE_H

#ifdef __cplusplus
extern "C" {
#endif
    //
#include <stdlib.h>
#include "lexic/valtok.h"


    // abstract syntax tree
    //  typedef struct _leaf_node_ {
    //      termin term_type;
    //      long long lolo_valu;
    //      double doub_valu;
    //      char stri[MAX_TOKE_SIZE];
    //  } leaf_node;

    typedef struct _valu_toke_ leaf_node;

    //

    struct _leaf_list_ {
        struct _leaf_list_ *next;
        //
        leaf_node *leno;
    };

    typedef struct _leaf_list_ leaf_list;

    //
#define NEW_LEAF_NODE(LEAF_NODE) \
    LEAF_NODE = (leaf_node *) malloc(sizeof (leaf_node)); \
    memset(LEAF_NODE, '\0', sizeof(leaf_node));

#define NEW_LEAF_VATO(LEAF_NODE, VALU_TOKE) \
    LEAF_NODE = (leaf_node *) malloc(sizeof (leaf_node)); \
    memcpy(LEAF_NODE, VALU_TOKE, sizeof(leaf_node));

#define LEAF_NODE_DELE(LEAF_NODE)    free(LEAF_NODE)

    //
    leaf_node *new_leaf_vato(valu_toke *valtok);
    leaf_list *new_leaf_sign(uint sinum, valu_toke *valtok);
    leaf_list *appe_leaf_vato(leaf_list *leli, valu_toke *valtok);
    leaf_list *appe_leaf_vats(leaf_list *leli, uint sinum, valu_toke *valtok);
    leaf_list *appe_leaf_type(leaf_list *leli, valu_toke *valtok);

    //
    leaf_list *new_leaf_list(valu_toke *valtok);

    inline void leaf_list_dele(leaf_list *leli) {
        leaf_list *lels;
        while ((lels = leli)) {
            leli = leli->next;
            free(lels->leno);
            free(lels);
        }
    }

#define GET_LEAF_LIST(DEST, SOUR) DEST = SOUR; SOUR = NULL;
    //

    struct _oper_node_ {
        unsigned int node_type;

        union {
            struct _oper_node_ *left_chil;
            leaf_node *leno;
        }; // leop

        union {
            struct _oper_node_ *righ_chil;
            leaf_list *lealst;
        }; // riop
    };

    typedef struct _oper_node_ oper_node;

    //

    struct _oper_list_ {
        struct _oper_list_ *next;
        //
        oper_node *opno;
    };

    typedef struct _oper_list_ oper_list;

    //
#define PARSE_SUCCESS     0x00
#define PARSE_FAULT       -1

    struct _pastat_ {
        oper_node *synt_head;
        int accept;
        char *erro_msg;
    };

    typedef struct _pastat_ pastat;

    //
    oper_node *new_oper_leaf(uint opnum, leaf_node *leno);

    //
#define NEW_OPERA_NODE(OPER_NODE) \
    OPER_NODE = (oper_node *) malloc(sizeof (oper_node)); \
    memset(OPER_NODE, '\0', sizeof(oper_node));

    //
    oper_node *new_oper_node(pastat *state, uint opnum, oper_node *leno, oper_node *riod);
    oper_list *new_oper_list(oper_list *olist, oper_node *opno);

    //
    void recu_dele(oper_node *ople_node);
#define DESTROY_STREE(TREE_HEAD)    recu_dele(TREE_HEAD)

    //
#define OPER_NODE_DELE(OPER_NODE)    free(OPER_NODE)
    void oper_list_dele(oper_list *olist);

    //
    oper_node *expr_add_collate(pastat *state, uint opnum, leaf_node *leno, oper_node *riod);
    oper_node *expr_function(valu_toke *valtok, leaf_list *leli);
    oper_node *binary_unary_null(pastat *state, oper_node *leno, oper_node *riod, uint opnum);





#ifdef __cplusplus
}
#endif

#endif /* SYNTA_TREE_H */


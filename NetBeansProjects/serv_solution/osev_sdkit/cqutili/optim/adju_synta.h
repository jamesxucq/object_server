
/* 
 * File:   adju_synta.h
 * Author: James Xu
 *
 * Created on 2021.7.7, AM9:04
 */

#ifndef ADJU_SYNTA_H
#define ADJU_SYNTA_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    int adju_noeq_node(oper_node *syno, oper_node *leno, oper_node *rino);
    int adju_equa_node(oper_node *syno, oper_node *leno, oper_node *rino);
    int adju_grth_node(oper_node *syno, oper_node *leno, oper_node *rino);
    int adju_leeq_node(oper_node *syno, oper_node *leno, oper_node *rino);
    int adju_leth_node(oper_node *syno, oper_node *leno, oper_node *rino);
    int adju_greq_node(oper_node *syno, oper_node *leno, oper_node *rino);
    int adju_plus_node(oper_node *syno, oper_node *leno, oper_node *rino);
    int adju_minu_node(oper_node *syno, oper_node *leno, oper_node *rino);



#ifdef __cplusplus
}
#endif

#endif /* ADJU_SYNTA_H */



/* 
 * File:   solve_bound.h
 * Author: James Xu
 *
 * Created on 2023.6.1, PM 2:54
 */

#ifndef SOLVE_BOUND_H
#define SOLVE_BOUND_H

#ifdef __cplusplus
extern "C" {
#endif

    // 
    int bound_objec_data(valu_memo_t *obje_memp, unsigned long long *key, PK_ITEM *value, lv2pme *lv2me);

    //
    int bound_objec_loop(loop_memo_t *obje_memp, unsigned long long *key, PK_ITEM *value, lv2pme *lv2me);
    int solve_objec_loop(PK_ITEM *key, PK_ITEM *value, loop_memo_t *obje_memp, lv2pme *lv2me);
    int solve_value_loop(PK_ITEM *value, loop_memo_t *obje_memp, lv2pme *lv2me);

#ifdef __cplusplus
}
#endif

#endif /* SOLVE_BOUND_H */


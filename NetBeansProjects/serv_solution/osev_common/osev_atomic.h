
/* 
 * File:   osev_atomic.h
 * Author: James Xu
 *
 * Created on 2017.2.1, PM 2:18
 */

#ifndef OSV_ATOMIC_H
#define OSV_ATOMIC_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    typedef volatile unsigned long osv_atomic_t;

    //
#define OSV_ATOMIC_ADD_FETCH(VALUE, ADD) __sync_add_and_fetch(VALUE, ADD)
#define OSV_ATOMIC_SUB_FETCH(VALUE, SUB) __sync_sub_and_fetch(VALUE, SUB)

    //
#define OSV_ATOMIC_FETCH_ADD(VALUE, ADD) __sync_fetch_and_add(VALUE, ADD)
#define OSV_ATOMIC_FETCH_SUB(VALUE, SUB) __sync_fetch_and_sub(VALUE, SUB)

#ifdef __cplusplus
}
#endif

#endif /* OSV_ATOMIC_H */


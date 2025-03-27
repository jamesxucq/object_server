
/* 
 * File:   os_alloc.h
 * Author: james
 *
 * Created on 2022.10.7, AM 11:03
 */

#ifndef OS_ALLOC_H
#define OS_ALLOC_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    int __pk_calloc(size_t number, size_t size, void *retp);

    //
    void __pk_free_int(const void *p_arg);


#ifdef __cplusplus
}
#endif

#endif /* OS_ALLOC_H */



/* 
 * File:   valtok.h
 * Author: James
 *
 * Created on 2019.3.22, 10:19
 */

#ifndef VALTOK_H
#define VALTOK_H

#ifdef __cplusplus
extern "C" {
#endif

    // #include "gramm/exptoke.h"

#define STACK_SIZE 256

#define MAX_TOKE_SIZE 512

    /*
     * && AND || OR ! NOT ( ) < > == != >= <= BETWEEN IN
     */

    /*
     * () (l-r)
     * ! NOT (r-l)
     * < > >= <= (l-r)
     * == != (l-r)
     * BETWEEN IN (l-r)
     * && AND (l-r)
     * || OR (l-r)
     */

    //

    struct _valu_toke_ {
        unsigned int vtok_kind;
        long long lolo_valu;
        unsigned long long ullo_valu;
        double doub_valu;
        char stri_valu[MAX_TOKE_SIZE];
    };

    typedef struct _valu_toke_ valu_toke;

    //

#ifdef __cplusplus
}
#endif

#endif /* VALTOK_H */


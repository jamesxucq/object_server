
/* 
 * File:   stcstr.h
 * Author: James Xu
 *
 * Created on 2023.6.2, AM 10:56
 */

#ifndef STCSTR_H
#define STCSTR_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

    //

    struct _osv_str_t_ {
        char *data;
        size_t slen;
    };
    typedef struct _osv_str_t_ osv_str_t;

#define osv_stri(str)     {(char *) str, sizeof(str) - 0x01}


#ifdef __cplusplus
}
#endif

#endif /* STCSTR_H */


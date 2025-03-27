
/* 
 * File:   shap_struct.h
 * Author: James Xu
 *
 * Created on 2018.1.25, PM 2:33
 */

#ifndef SHAP_STRUCT_H
#define SHAP_STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/file.h>

#ifdef __cplusplus
extern "C" {
#endif

    //

    struct shap_list {
        struct shap_list *prev;
        struct shap_list *next;
        //
        uint32 einde;
        char idata[];
    };

    //

    typedef struct {
        char file_name[MAX_PATH * 3];
        FILE *fpiden;
        int32 isize;
        struct shap_list * elist; // entry list;
    } shap_live;

    //


#ifdef __cplusplus
}
#endif

#endif /* SHAP_STRUCT_H */


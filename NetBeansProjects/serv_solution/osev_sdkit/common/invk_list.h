
/* 
 * File:   invk_list.h
 * Author: James Xu
 *
 * Created on 2016.12.21, AM 10:57
 */

#ifndef IVK_LIST_H
#define IVK_LIST_H

#include "commo_macro.h"
#include "osev_datyp.h"
#include "osev_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

    struct _invk_list_ {
        char meth_name[LVON_LENGTH];
        char package_name[PACKAGE_LEN];
        void *meth_funcer;
        //
        struct _invk_list_ *next;
    };

    typedef struct _invk_list_ invk_list;

    //
    invk_list *appe_ivklist_new(invk_list **ivklsth);

    inline void ivklist_dele(invk_list *ivklist) {
        invk_list *ilsnd;
        while (ivklist) {
            ilsnd = ivklist;
            ivklist = ivklist->next;
            free(ilsnd);
        }
    }

#ifdef __cplusplus
}
#endif

#endif /* IVK_LIST_H */


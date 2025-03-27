
/* 
 * File:   odata_list.h
 * Author: Administrator
 *
 * Created on 2017.1.9, PM 2:03
 */

#ifndef ODATA_LIST_H
#define ODATA_LIST_H

#include "common_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

    struct odata_list {
        char osdb_name[OSDB_LENGTH];
        actionmap *odata_hm;
        struct odata_list *next;
    };

    //
    extern struct odata_list *_odata_list_;

    //
    struct odata_list *appe_olist_new(struct odata_list **olsth);
    inline void olist_dele(struct odata_list *olist);


#ifdef __cplusplus
}
#endif

#endif /* ODATA_LIST_H */


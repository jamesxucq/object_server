
/* 
 * File:   shap_entry.h
 * Author: James Xu
 *
 * Created on 2018.2.5, AM 9:57
 */

#ifndef SHAP_ENTRY_H
#define SHAP_ENTRY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/file.h>

#include "shap_common.h"
#include "shap_struct.h"

#ifdef __cplusplus
extern "C" {
#endif

    struct entry_id {
        uint32 prev_sibli;
        uint32 next_sibli;
        char idata[];
    };
    
//
    uint32 load_entry(struct shap_list **entry_lsth, FILE *fpiden, int32 isize);


#ifdef __cplusplus
}
#endif

#endif /* SHAP_ENTRY_H */



/* 
 * File:   shap_cache.h
 * Author: James Xu
 *
 * Created on 2018.2.5, AM 10:50
 */

#ifndef SHAP_CACHE_H
#define SHAP_CACHE_H

#include "shap_common.h"
#include "shap_struct.h"
#include "utlist.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
#define appe_shap_list(SHAP_DATA, ENTRY_LIST, EINDE, IDATA, ISIZE, ERRO_CODE) { \
    SHAP_DATA = (struct shap_list *) malloc(sizeof (struct shap_list)+ISIZE); \
    if(!SHAP_DATA) return ERRO_CODE; \
    DL_APPEND(ENTRY_LIST, SHAP_DATA) \
    SHAP_DATA->einde = EINDE; \
    memcpy(SHAP_DATA->idata, IDATA, ISIZE); \
}

    //
#define dele_shap_list(ENTRY_LIST, SHAP_LIST) { \
    DL_DELETE(ENTRY_LIST, SHAP_LIST) \
    free(SHAP_LIST); \
}


    //
    void save_cache(struct shap_list *elist);

    //
    struct shap_list *cache_find(struct shap_list *elist, char *idata);

#ifdef __cplusplus
}
#endif

#endif /* SHAP_CACHE_H */


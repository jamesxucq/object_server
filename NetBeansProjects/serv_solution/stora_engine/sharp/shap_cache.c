
#include "shap_cache.h"

//

void save_cache(struct shap_list *elist) {
    struct shap_list *shap_data;
    for (; elist;) {
        shap_data = elist;
        elist = elist->next;
        free(shap_data);
    }
}

//

struct shap_list *cache_find(struct shap_list *elist, char *idata) {
    for (; elist;) {
        if (idata == elist->idata) return elist;
        elist = elist->next;
    }
    //
    return NULL;
}
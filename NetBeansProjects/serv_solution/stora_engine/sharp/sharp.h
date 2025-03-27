/* 
 * File:   sharp.h
 * Author: James Xu
 */

#ifndef SHARP_H
#define SHARP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shap_common.h"
#include "sstri_utili.h"
#include "shap_struct.h"

////

#ifdef __cplusplus
extern "C" {
#endif

    //
#define SLIVE_INITI_POINT(PLIVE, ISIZE, FNAME) \
    PLIVE->isize = ISIZE; \
    PLIVE->elist = NULL; \
    shap_lscpy(PLIVE->file_name, FNAME);

    //
#define SLIVE_INITI_DATA(SLIVE, ISIZE, FNAME) \
    SLIVE.isize = ISIZE; \
    SLIVE.elist = NULL; \
    shap_lscpy(SLIVE.file_name, FNAME);

    //
    int32 shap_create(shap_live *pliv);
    int32 shap_destroy(shap_live *pliv);
    int32 shap_initial(shap_live *pliv);
    int32 shap_final(shap_live *pliv);
    //
    void *shap_insert(shap_live *pliv, char *idata);
    int32 shap_remove(shap_live *pliv, char *idata);
    int32 shap_remove_ex(shap_live *pliv, struct shap_list *elist);

    //
    int shap_load(char *idata, shap_live *pliv, uint32 einde);
    int shap_save(shap_live *pliv, uint32 einde, char *idata);
    // for test
    int32 shap_echo(shap_live *pliv);
    //
#ifdef __cplusplus
}
#endif

//

#endif /* SHARP_H */


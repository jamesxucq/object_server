/* 
 * File:   shap_utility.h
 * Author: James Xu
 */

#ifndef SHAP_UTILITY_H
#define SHAP_UTILITY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>

//

#include "shap_common.h"

//
#ifdef __cplusplus
extern "C" {
#endif

    //
    uint32 fill_head_iden(FILE *fpiden, int32 isize);
    uint32 fill_idle_iden(FILE *fpiden, int32 isize);
    
    //
    uint32 find_idle_iden(FILE *fpiden, int32 isize);
    uint32 addi_idle_iden(FILE *fpiden, int32 ainde, int32 isize);
    
//
    uint32 read_iden_data(char *idata, int32 isize, FILE *fpiden, uint32 ainde);
    uint32 write_iden_data(FILE *fpiden, uint32 ainde, char *idata, int32 isize);

    
    //
#ifdef __cplusplus
}
#endif

#endif /* SHAP_UTILITY_H */


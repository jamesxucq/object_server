
/* 
 * File:   creat_sharp.h
 * Author: James Xu
 *
 * Created on 2018.2.5, AM 9:57
 */

#ifndef CREAT_SHARP_H
#define CREAT_SHARP_H

#include "shap_common.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    uint32 build_sharp_enviro(char *file_name, int32 isize);
    uint32 destroy_sharp_enviro(char *file_name);



#ifdef __cplusplus
}
#endif

#endif /* CREAT_SHARP_H */


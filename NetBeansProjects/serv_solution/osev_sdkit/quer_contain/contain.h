/* 
 * File:   contain.h
 * Author: James Xu
 *
 * Created on 2016.12.17, PM 3:00
 */

#ifndef CONTAIN_H
#define CONTAIN_H

#include "commo_header.h"
#include "kcomm_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    contain *build_conta_meta(contain *contp, char *basen, char *contn);
    int qload_conta_meta(basv_list *blist);

    //


#ifdef __cplusplus
}
#endif

#endif /* CONTAIN_H */


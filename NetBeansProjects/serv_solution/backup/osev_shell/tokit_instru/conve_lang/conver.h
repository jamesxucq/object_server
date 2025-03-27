
/* 
 * File:   conver.h
 * Author: James Xu
 *
 * Created on 2017.6.22, PM 3:22
 */

#ifndef CONVER_H
#define CONVER_H

#include "lv2p_list.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    char *conve_lv2p_conte(char *clang_cont, class_meta *clsmt, lv2p_expa_t *lv2expt);
    int conve_lev1_conte(char *clang_cont, class_meta *clsmt, lv2p_expa_t *lv2expt, char *basen);

#ifdef __cplusplus
}
#endif

#endif /* CONVER_H */


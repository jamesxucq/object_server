
/* 
 * File:   translate.h
 * Author: James Xu
 *
 * Created on 2017.6.22, PM 3:22
 */

#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "lv2p_list.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    char *trans_lv2p_conte(char *clang_cont, class_meta *clsmt, lv2p_expa_t *lv2expt);
    int trans_lev1_conte(char *clang_cont, class_meta *clsmt, lv2p_expa_t *lv2expt/*, char *basen*/);

#ifdef __cplusplus
}
#endif

#endif /* TRANSLATE_H */


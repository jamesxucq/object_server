
/* 
 * File:   parse_lv2p_atti.h
 * Author: James Xu
 *
 * Created on 2017.6.23, AM 8:49
 */

#ifndef PARSE_LVTP_ATTI_H
#define PARSE_LVTP_ATTI_H

#include "lv2p_list.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    char *parse_lv2p_atti(class_meta *clsmt, char *lv2p_cont);

    //
    char *split_lv2p_atti(char *acont, char *lv2p_cont);
    char *find_lv2p_atti(char *lv2p_cont);

    //
    unsigned int split_conte_type(char *lv2e_cont, char *lv2p_cont, char *lev1_cont, char *leve_data);

#ifdef __cplusplus
}
#endif

#endif /* PARSE_LVTP_ATTI_H */


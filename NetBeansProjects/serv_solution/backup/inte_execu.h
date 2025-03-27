
/* 
 * File:   inte_execu.h
 * Author: Administrator
 *
 * Created on 2016.12.29, PM 1:51
 */

#ifndef INTE_EXECU_H
#define INTE_EXECU_H

#include "common_header.h"

#ifdef __cplusplus
extern "C" {
#endif

//
    
    struct cmdi_execu {
        int clas_meth; // 0x00:method 0x01:class
        enum execu_type exec_type;
        char space_str[CLASS_LENGTH];
        char meth_str[METH_LENGTH];
        char para_str[PARAM_LENGTH];
        char execu_line[LARGE_TEXT_SIZE];
    };
    //
    int parse_execute(struct cmdi_execu *cmd_exec, char *execu);
    int valid_execute(char *osdb, struct cmdi_execu *cmd_exec);

    //
#define EPARA_CLAS_METH     0x00
#define EPARA_INVOKE        0x00
#define EPARA_METH_STR      0x01
#define EPARA_PARA_STR      0x02
    extern int (**hand_execu_tab[])(prod_data *, hand_data *, hand_data *, char *, char **);


#ifdef __cplusplus
}
#endif

#endif /* INTE_EXECU_H */


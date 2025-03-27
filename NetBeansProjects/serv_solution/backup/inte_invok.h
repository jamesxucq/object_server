
/* 
 * File:   inte_invok.h
 * Author: Administrator
 *
 * Created on 2016.12.29, PM 1:51
 */

#ifndef INTE_INVOK_H
#define INTE_INVOK_H

#include "common_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    struct cmdi_invok {
        enum invok_type invo_type;
        char obje_ident[OBJE_LENGTH];
        char meth_str[METH_LENGTH];
        char invok_line[LINE_LENGTH];
        char *paras[PARAM_NUMB];
    };
    //
    int parse_invoke(struct cmdi_invok *cmd_invo, char *invok);
    int valid_invoke(char *osev_osdb, struct cmdi_invok *cmd_invo);
    
    //
#define IPARA_OBJE_IDEN     0x00
#define IPARA_METH_STR      0x01
#define IPARA_PARA_POS      0x02
    extern int (*hand_invok_tab[])(prod_data *, void *, char **);

#ifdef __cplusplus
}
#endif

#endif /* INTE_INVOK_H */


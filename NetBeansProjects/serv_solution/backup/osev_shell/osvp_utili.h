
/* 
 * File:   osvp_utili.h
 * Author: james
 *
 * Created on 2023.3.29, PM2:01
 */

#ifndef OSVP_UTILI_H
#define OSVP_UTILI_H

#include "osev_clie_clang.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
#define NULL_CONNE -1
#define OSEV_CONNE 0x00
#define BASE_CONNE 0x01
    int get_conne_type(char *conne_str);

    //
    char *hide_instru(char *line_str);

    //

#define OSVPURI_ILLEGAL  -1
#define HOST_ONLY_URI   0x01
#define USER_HOST_BASE  0x02
#define HOST_BASE_URI   0x03
#define USER_HOST_URI   0x04

    int parse_conne_ospuri(osvp_auth *clie_auth, const char *osvp_uri);
    //
    char *split_ospuri_base(char *osev_base, const char *osvp_uri);


#ifdef __cplusplus
}
#endif

#endif /* OSVP_UTILI_H */



/* 
 * File:   osvp_auth.h
 * Author: James Xu
 *
 * Created on 2023.11.8, PM 4:16
 */

#ifndef OSVP_AUTH_H
#define OSVP_AUTH_H

// 
#include "clie_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    struct _auth_meta_ {
        char user_name[USRN_LENGTH];
        char pass_word[PASWD_LENGTH];
    };

    typedef struct _auth_meta_ auth_meta;

#define MAKE_AUTH_ZERO(AUTH) { \
        AUTH->user_name[0x00] = '\0'; \
        AUTH->pass_word[0x00] = '\0'; \
    }

    struct _osvp_auth_ {
        char osev_base[OSEV_LENGTH];
        serv_addr saddr;
        auth_meta authe;
    };

    typedef struct _osvp_auth_ osvp_auth;


#ifdef __cplusplus
}
#endif

#endif /* OSVP_AUTH_H */


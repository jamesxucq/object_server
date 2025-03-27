
/* 
 * File:   astri_utili.h
 * Author: James Xu
 *
 * Created on 2018.3.23, AM 10:14
 */

#ifndef ASTRI_UTILI_H
#define ASTRI_UTILI_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    uint32 split_conta(char *basen, char *contn, char *base_conta);

    // void creat_action_key(char *action_key, char *user_name, char *osev_base);

    inline void creat_action_key(char *action_key, char *user_name, char *osev_base) {
        action_key = lscpy(action_key, user_name);
        action_key = lccpy(action_key, ':');
        lscpy(action_key, osev_base);
    }

#ifdef __cplusplus
}
#endif

#endif /* ASTRI_UTILI_H */


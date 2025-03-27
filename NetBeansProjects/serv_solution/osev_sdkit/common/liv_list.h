
/* 
 * File:   liv_list.h
 * Author: James Xu
 *
 * Created on 2018.3.30, AM 10:12
 */

#ifndef LIV_LIST_H
#define LIV_LIST_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    // user<[uid int, uname char[32], salt char[16], password char[32], roleId int[32]] INVISI>;
    // userContain
#define MAX_PRIVI_SIZE   64
#define MAX_ROLE_SIZE  8

    // authen
#pragma pack(1)

    struct _dist_privi_ {
        osv_oid_t dist_obid;
        uint32 privile_code; // privilege
    };
#pragma pack()

    typedef struct _dist_privi_ dist_privi;

    //

#define PRIV_BINCPY(PRI1, PRI2) { \
    ((osv_oid_i *)&PRI1->dist_obid)->stoid = ((osv_oid_i *)&PRI2->dist_obid)->stoid; \
    (&PRI1->dist_obid)->osev_unique = (&PRI2->dist_obid)->osev_unique; \
    PRI1->privile_code = PRI2->privile_code; \
} 

#define MAKE_PRIV_ZERO(PRI) { \
    ((osv_oid_i *)&PRI->dist_obid)->stoid = 0x00; \
    (&PRI->dist_obid)->osev_unique = 0x00; \
    PRI->privile_code = 0x00; \
} 

    //
#define DIST_PRIVI_NOT_ZERO(DIST_PRIVI) (DIST_PRIVI->privile_code || CHK_ZERO_OBID(&DIST_PRIVI->dist_obid))
#define DIST_PRIVI_IS_ZERO(DIST_PRIVI) (!DIST_PRIVI->privile_code && IS_ZERO_OBID(&DIST_PRIVI->dist_obid))

    // container
#define ROLE_TYPE_OSEV 0x00
#define ROLE_TYPE_BASE 0x01
#pragma pack(1)

    struct _role_privi_ {
        osv_oid_t role_obid;
        char role_type; // 0x00:osev 0x01:data
        char role_name[USRN_LENGTH];
        dist_privi priv_array[MAX_PRIVI_SIZE];
    };
#pragma pack()

    typedef struct _role_privi_ role_privi;

    // container

#pragma pack(1)

    struct _user_privi_ {
        osv_oid_t user_obid;
        char user_name[USRN_LENGTH];
        unsigned char password[PASWD_LENGTH];
        unsigned char salt[SALT_LENGTH];

        union {
            osv_oid_t role_obid[MAX_ROLE_SIZE]; // storage
            role_privi *ropriv[MAX_ROLE_SIZE]; // memory cache
        };
    };
#pragma pack()

    typedef struct _user_privi_ user_privi;

    //

    struct _liv_list_ {
        void *liv_data;
        //
        struct _liv_list_ *next;
    };

    typedef struct _liv_list_ liv_list;

    //
    liv_list *appe_live_list(liv_list **llsth, void *liv_data, int liv_len);
    liv_list *addi_live_list(liv_list **llsth, int liv_len);

    inline void dele_live_list(liv_list *llist) {
        liv_list *llsnd;
        while (llist) {
            llsnd = llist;
            llist = llist->next;
            free(llsnd->liv_data);
            free(llsnd);
        }
    }

#define DELE_LIVE_LIST(LLIST) dele_live_list(LLIST); LLIST = NULL;

    inline void dele_livlst(liv_list **llsth, liv_list *llist) {
        LL_DELETE(*llsth, llist)
        free(llist->liv_data);
        free(llist);
    }

#define LL_DELETE_LIV(posi, head, dele) { \
    LDECLTYPE(head) _tmp; \
    if ((head)->liv_data == (dele)) (head)=(head)->next; \
    else { \
        _tmp = head; \
        while (_tmp->next && ((_tmp->next)->liv_data != (dele))) _tmp = _tmp->next; \
        if (_tmp->next) { \
            posi = _tmp->next; \
            _tmp->next = posi->next; \
        } \
    } \
}

    inline void dele_livdat(liv_list **llsth, void *livdat) {
        liv_list *llist = NULL;
        LL_DELETE_LIV(llist, *llsth, livdat)
        if (llist) {
            free(llist->liv_data);
            free(llist);
        }
    }

    // cache_insert(uepriv->user_name, uepriv, user_hm);

    struct _usep_listmap_ {
        liv_list *role_list;
        liv_list *ouse_list;
        cachemap *osev_user_hm;
        liv_list *buse_list;
        cachemap *base_user_hm;
    };

    typedef struct _usep_listmap_ usep_lsmp;

    //

#ifdef __cplusplus
}
#endif

#endif /* LIV_LIST_H */


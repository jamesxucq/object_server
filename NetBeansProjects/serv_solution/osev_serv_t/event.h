/*
 * File:   event.h
 * Author: James Xu
 *
 * Created on 2012
 */

#ifndef EVENT_H
#define EVENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "session.h"

    //

    struct _evdata_ {
        BYTE *head_ptr;
        // unsigned long long hlen; // fixed: RESP_HEAD_BLEN
        BYTE *body_ptr;
        unsigned long long blen;
    };

    typedef struct _evdata_ evdata;

    //

    struct _event_ {
        evdata evdat;
        session *seion;
        //
        unsigned int levtyp; // OSEV_METHOD
        unsigned int levivk; // COMDI_OPEN, COLE_DROP, QUER_FACTO
        // receive send process
        unsigned int (*recv_initial_hand)(session *, evdata *);
        unsigned int (*recv_binary_hand)(reque_ctrl *, evdata *);
        void (*recv_finaliz_hand)(session *);
        unsigned int (*send_initial_hand)(session *, evdata *);
        unsigned int (*send_binary_hand)(respo_ctrl *, evdata *);
        void (*send_finaliz_hand)(session *);
        void (*rvse_excepti_hand)(session *);
    };

    typedef struct _event_ _event;

    //
#define CREATE_EVENT(BEV) { \
    BEV = (_event *) malloc(sizeof (_event)); \
    if(!BEV) return ERR_FAULT; \
    memset(BEV, '\0', sizeof (_event)); \
    BEV->seion = creat_session(); \
    if(!BEV->seion) { \
        free(BEV); \
        return ERR_FAULT; \
    } \
}

#define DESTROY_EVENT(BEV) { \
    if(BEV->seion) destro_session(BEV->seion); \
    BEV->seion = NULL; \
    if(BEV) return free(BEV); \
    BEV = NULL; \
}

#define INITIAL_EVENT(BEV) reset_session(BEV->seion)

    //

#ifdef __cplusplus
}
#endif

#endif /* EVENT_H */


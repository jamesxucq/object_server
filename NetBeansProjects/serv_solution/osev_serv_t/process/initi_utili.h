
/* 
 * File:   init_utili.h
 * Author: James Xu
 *
 * Created on 2016.12.28, PM 1:55
 */

#ifndef INIT_UTILI_H
#define INIT_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

    // parse head
#define CHECK_AUTHEN_HEAD(RESCTL, EVDAT) { \
    if((EVDAT)->blen != (RESCTL)->content_length) { \
        (RESCTL)->status_code = INTERNAL_SERVER_ERROR; \
        return REQU_STOP; \
    } \
}

    // pretreat, parse head
#define CHECK_POST_INVAL(RESCTL, INVAL, EVDAT) { \
    if((EVDAT)->blen != (RESCTL)->content_length) { \
        (RESCTL)->status_code = INTERNAL_SERVER_ERROR; \
        return REQU_STOP; \
    } \
}

    // pretreat, parse head
#define CHECK_STATU_INVAL(RESCTL, INVAL, EVDAT) { \
    if((EVDAT)->blen != (RESCTL)->content_length) { \
        (RESCTL)->status_code = INTERNAL_SERVER_ERROR; \
        return REQU_STOP; \
    } \
}

#define CHECK_COMAND_HEAD(RESCTL, EVDAT) { \
    if((EVDAT)->blen != (RESCTL)->content_length) { \
        (RESCTL)->status_code = INTERNAL_SERVER_ERROR; \
        return REQU_STOP; \
    } \
}

    // pretreat, parse head
#define CHECK_PRIVI_INVAL(RESCTL, INVAL, EVDAT) { \
    if((EVDAT)->blen != (RESCTL)->content_length) { \
        (RESCTL)->status_code = INTERNAL_SERVER_ERROR; \
        return REQU_STOP; \
    } \
}

    // parse head
#define CHECK_KALIVE_HEAD(RESCTL, EVDAT) { \
    if((EVDAT)->blen != (RESCTL)->content_length) { \
        (RESCTL)->status_code = INTERNAL_SERVER_ERROR; \
        return REQU_STOP; \
    } \
}

    // parse head
#define CHECK_DONE_HEAD(RESCTL, EVDAT) { \
    if((EVDAT)->blen != (RESCTL)->content_length) { \
        (RESCTL)->status_code = INTERNAL_SERVER_ERROR; \
        return REQU_STOP; \
    } \
}

    // produ data
#define PRODU_AUTHEN_SEND(EVDAT, RESCTL) { \
    resp_head *authe_head = (resp_head *) EVDAT->head_ptr; \
    authe_head->status_code = (RESCTL).status_code; \
    authe_head->content_length = (RESCTL).content_length; \
}

    // produ data
#define PRODU_POST_SEND(EVDAT, RESCTL) { \
    resp_head *post_head = (resp_head *) EVDAT->head_ptr; \
    post_head->status_code = (RESCTL).status_code; \
    post_head->content_length = (RESCTL).content_length; \
}

    // produ data
#define PRODU_STATUS_SEND(EVDAT, RESCTL) { \
    resp_head *statu_head = (resp_head *) EVDAT->head_ptr; \
    statu_head->status_code = (RESCTL).status_code; \
    statu_head->content_length = (RESCTL).content_length; \
}

#define PRODU_COMAND_SEND(EVDAT, RESCTL) { \
    resp_head *comnd_head = (resp_head *) EVDAT->head_ptr; \
    comnd_head->status_code = (RESCTL).status_code; \
    comnd_head->content_length = (RESCTL).content_length; \
}

    // produ data
#define PRODU_PRIVILE_SEND(EVDAT, RESCTL) { \
    resp_head *privi_head = (resp_head *) EVDAT->head_ptr; \
    privi_head->status_code = (RESCTL).status_code; \
    privi_head->content_length = (RESCTL).content_length; \
}

    // produ data
#define PRODU_KALIVE_SEND(EVDAT, RESCTL) { \
    resp_head *kaliv_head = (resp_head *) EVDAT->head_ptr; \
    kaliv_head->status_code = (RESCTL).status_code; \
    EVDAT->blen = ONLY_HEADER_SECTION; \
}

    // produ data
#define PRODU_INVOKE_SEND(EVDAT, RESCTL) { \
    resp_head *invok_head = (resp_head *) EVDAT->head_ptr; \
    invok_head->status_code = (RESCTL).status_code; \
    invok_head->content_length = (RESCTL).content_length; \
}

    // produ data
#define PRODU_COLLE_SEND(EVDAT, RESCTL) { \
    resp_head *colle_head = (resp_head *) EVDAT->head_ptr; \
    colle_head->status_code = (RESCTL).status_code; \
    colle_head->content_length = (RESCTL).content_length; \
}

    // produ data
#define PRODU_CONST_SEND(EVDAT, RESCTL) { \
    resp_head *const_head = (resp_head *) EVDAT->head_ptr; \
    const_head->status_code = (RESCTL).status_code; \
    const_head->content_length = (RESCTL).content_length; \
}

    // produ data
#define PRODU_QUERY_SEND(EVDAT, RESCTL) { \
    resp_head *query_head = (resp_head *) EVDAT->head_ptr; \
    query_head->status_code = (RESCTL).status_code; \
    query_head->content_length = (RESCTL).content_length; \
}

    // produ data
#define PRODU_DONE_SEND(EVDAT, RESCTL) { \
    resp_head *done_head = (resp_head *)EVDAT->head_ptr; \
    done_head->status_code = (RESCTL).status_code; \
    EVDAT->blen = ONLY_HEADER_SECTION; \
}

#ifdef __cplusplus
}
#endif

#endif /* INIT_UTILI_H */


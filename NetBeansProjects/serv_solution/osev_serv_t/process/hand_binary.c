
#include "commo_header.h"
#include "kcomm_header.h"

#include "../event.h"

#include "hand_binary.h"

//epoll serv handle recv and create send

static unsigned int HAND_INVA_RECV(reque_ctrl *reqctl, evdata *evdat) {
    OSEVPF("[FUNC]:HAND_INVA_RECV\n");
    return 0x00;
}

static unsigned int hand_monce_recv(reque_ctrl *reqctl, evdata *evdat) {
    OSEVPF("[FUNC]:hand_monce_recv\n");
    // if (!reqctl->content_length) return REQU_STOP;
    memcpy(reqctl->requ_memo, evdat->body_ptr, evdat->blen);
    // reqctl->content_length -= evdat->blen;
    return REQU_STOP;
}

static unsigned int hand_memo_recv(reque_ctrl *reqctl, evdata *evdat) {
    OSEVPF("[FUNC]:hand_memo_recv\n");
    // if (!reqctl->content_length) return REQU_STOP;
    OSEVPF("content_length:%llu, blen:%llu\n", reqctl->content_length, evdat->blen);
    memcpy(reqctl->posi_requ, evdat->body_ptr, evdat->blen);
    reqctl->posi_requ += evdat->blen;
    //
    reqctl->content_length -= evdat->blen;
    OSEVPF("content_length:%llu\n", reqctl->content_length);
    return reqctl->content_length;
}

static unsigned int hand_stem_recv(reque_ctrl *reqctl, evdata *evdat) {
    OSEVPF("[FUNC]:hand_stem_recv\n");
    // if (!reqctl->content_length) return REQU_STOP;
    OSEVPF("content_length:%llu, blen:%llu\n", reqctl->content_length, evdat->blen);
    evdat->blen = fwrite(evdat->body_ptr, 0x01, evdat->blen, reqctl->requ_stram);
    //
    reqctl->content_length -= evdat->blen;
    OSEVPF("content_length:%llu\n", reqctl->content_length);
    return reqctl->content_length;
}

//

#define HAND_OSEV_RECV_TAB { \
    /*AUTHEN*/ \
    hand_monce_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*POST*/ \
    hand_monce_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*STAT_ECHO STAT_STATIS*/ \
    hand_monce_recv, hand_monce_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*COMAND:COMDI_OPEN COMDI_CLOSE*/ \
    hand_monce_recv, hand_monce_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*PRIV_LIST PRIV_ROLE PRIV_USER*/ \
    hand_monce_recv, hand_monce_recv, hand_monce_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV \
}

//

#define HAND_BASE_RECV_TAB { \
    /*AUTHEN*/ \
    hand_monce_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*POST*/ \
    hand_monce_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*STAT_ECHO STAT_STATIS*/ \
    hand_monce_recv, hand_monce_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*COMAND:COMDI_OPEN COMDI_CLOSE*/ \
    hand_monce_recv, hand_monce_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*PRIV_LIST PRIV_ROLE PRIV_USER*/ \
    hand_monce_recv, hand_monce_recv, hand_monce_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV \
}

//

#define HAND_INVOK_RECV_TAB { \
    /*INVO_POST*/ \
    hand_monce_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*INVO_STATU*/ \
    hand_monce_recv, hand_monce_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*INVO_CREAT*/ \
    hand_monce_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*INVO_REPLA*/ \
    hand_monce_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
   /*INVO_DROP*/ \
    hand_monce_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*INVO_INTEGRA*/ \
    hand_monce_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*INVO_RELOAD*/ \
    hand_monce_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV \
}

//

#define HAND_COLLE_RECV_TAB { \
    /*COLE_POST*/ \
    hand_monce_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*COLE_STATU*/ \
    hand_monce_recv, hand_monce_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*COLE_CREAT*/ \
    hand_monce_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*COLE_REPLA*/ \
    hand_monce_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*COLE_DROP*/ \
    hand_monce_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*COLE_INTEGRA*/ \
    hand_monce_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*COLE_RELOAD*/ \
    hand_monce_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV \
}

// HAND_CONST_RECV_TAB

#define HAND_CONST_RECV_TAB { \
    /*POST*/ \
    hand_memo_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*STATU*/ \
    hand_memo_recv, hand_memo_recv, hand_memo_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*CREATE*/ \
    hand_memo_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*DROP*/ \
    hand_memo_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*UPDATE*/ \
    hand_memo_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*INSERT*/ \
    hand_memo_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*SEARCH*/ \
    hand_memo_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*INVOKE*/ \
    hand_memo_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV \
}

// HAND_QUERY_RECV_TAB

#define HAND_QUERY_RECV_TAB { \
    /*POST*/ \
    hand_memo_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*STATU*/ \
    hand_memo_recv, hand_memo_recv, hand_memo_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*CREATE*/ \
    hand_memo_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*DROP*/ \
    hand_memo_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*UPDATE*/ \
    hand_stem_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*INSERT*/ \
    hand_stem_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*SEARCH*/ \
    hand_memo_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*INVOKE*/ \
    hand_memo_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, \
    /*FACTORY*/ \
    hand_memo_recv, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV, HAND_INVA_RECV \
}

//

static unsigned int hand_none_recv(reque_ctrl *reqctl, evdata *evdat) {
    return REQU_STOP;
}

// {hand_memo_recv}, // authen
unsigned int(*requ_handler_tab[LEVTYP_COUNT][LEVIVK_COUNT])(reque_ctrl *, evdata *) = {
    HAND_OSEV_RECV_TAB,
    HAND_BASE_RECV_TAB,
    {hand_none_recv}, // klive
    HAND_INVOK_RECV_TAB,
    HAND_COLLE_RECV_TAB,
    HAND_CONST_RECV_TAB,
    HAND_QUERY_RECV_TAB,
    {hand_none_recv} // done
};

// HAND_CONST_SEND_TAB HAND_QUERY_SEND_TAB

static unsigned int HAND_INVA_SEND(respo_ctrl *resctl, evdata *evdat) {
    OSEVPF("[FUNC]:HAND_INVA_SEND\n");
    return 0x00;
}

/* creat send */
// HAND_AUTHEN_SEND HAND_STATUS_SEND HAND_PRIVILE_SEND HAND_INVOKE_SEND HAND_COLLE_SEND

static unsigned int hand_monce_send(respo_ctrl *resctl, evdata *evdat) {
    OSEVPF("[FUNC]:hand_monce_send\n");
    memcpy((char *) evdat->body_ptr, resctl->resp_memo, resctl->content_length);
    evdat->blen = resctl->content_length;
    return RESP_STOP;
}

static unsigned int hand_memo_send(respo_ctrl *resctl, evdata *evdat) {
    OSEVPF("[FUNC]:hand_memo_send\n");
    // 0x00 == resctl->content_length
    if (resctl->content_length <= evdat->blen)
        evdat->blen = resctl->content_length;
    OSEVPF("blen:%llu content_length:%llu\n", evdat->blen, resctl->content_length);
    memcpy(evdat->body_ptr, resctl->posi_resp, evdat->blen);
    resctl->posi_resp += evdat->blen;
    //
    resctl->content_length -= evdat->blen;
    return resctl->content_length;
}

static unsigned int hand_stem_send(respo_ctrl *resctl, evdata *evdat) {
    OSEVPF("[FUNC]:hand_stem_send\n");
    // 0x00 == resctl->content_length
    if (resctl->content_length <= evdat->blen)
        evdat->blen = resctl->content_length;
    evdat->blen = fread(evdat->body_ptr, 0x01, evdat->blen, resctl->resp_stram);
    if (!evdat->blen) {
        _LOG_WARN("constr file error!");
    }
    //     OSEVPF("blen:%llu content_length:%llu send_valu:%d\n", evdat->blen, resctl->content_length, send_valu);
    // log_binary_file(evdat->body_ptr, evdat->blen, "./binary_code.bin_s");
    resctl->content_length -= evdat->blen;
    return resctl->content_length;
}

//

#define HAND_OSEV_SEND_TAB { \
    /*AUTHEN*/ \
    hand_monce_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*POST*/ \
    hand_monce_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*STAT_ECHO STAT_STATIS*/ \
    hand_monce_send, hand_monce_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*COMAND:COMDI_OPEN COMDI_CLOSE*/ \
    hand_monce_send, hand_monce_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*PRIV_LIST PRIV_ROLE PRIV_USER*/ \
    hand_monce_send, hand_monce_send, hand_monce_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND \
}

//

#define HAND_BASE_SEND_TAB { \
    /*AUTHEN*/ \
    hand_monce_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*POST*/ \
    hand_monce_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*STAT_ECHO STAT_STATIS*/ \
    hand_monce_send, hand_monce_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*COMAND:COMDI_OPEN COMDI_CLOSE*/ \
    hand_monce_send, hand_monce_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*PRIV_LIST PRIV_ROLE PRIV_USER*/ \
    hand_monce_send, hand_monce_send, hand_monce_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND \
}

//

#define HAND_INVOK_SEND_TAB { \
    /*INVO_POST*/ \
    hand_monce_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*INVO_STATU*/ \
    hand_monce_send, hand_monce_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*INVO_CREAT*/ \
    hand_monce_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*INVO_REPLA*/ \
    hand_monce_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*INVO_DROP*/ \
    hand_monce_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*INVO_INTEGRA*/ \
    hand_monce_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*INVO_RELOAD*/ \
    hand_monce_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND \
}

//

#define HAND_COLLE_SEND_TAB { \
    /*COLE_POST*/ \
    hand_monce_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*COLE_STATU*/ \
    hand_monce_send, hand_monce_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*COLE_CREAT*/ \
    hand_monce_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*COLE_REPLA*/ \
    hand_monce_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*COLE_DROP*/ \
    hand_monce_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*COLE_INTEGRA*/ \
    hand_monce_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*COLE_RELOAD*/ \
    hand_monce_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND \
}

// modify method

#define HAND_CONST_SEND_TAB { \
    /*POST rm*/ \
    hand_memo_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*STATU rm*/ \
    hand_memo_send, hand_memo_send, hand_memo_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*CREATE rm*/ \
    hand_memo_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*DROP rm*/ \
    hand_memo_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*UPDATE rm*/ \
    hand_memo_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*INSERT rm*/ \
    hand_memo_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*SEARCH rm*/ \
    hand_stem_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*INVOKE rm*/ \
    hand_stem_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND \
}

// modify method

#define HAND_QUERY_SEND_TAB { \
    /*POST rm*/ \
    hand_memo_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*STATU rm*/ \
    hand_memo_send, hand_memo_send, hand_memo_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*CREATE rm*/ \
    hand_memo_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*DROP rm*/ \
    hand_memo_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*UPDATE rf*/ \
    hand_memo_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*INSERT rf*/ \
    hand_stem_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*SEARCH rm*/ \
    hand_stem_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*INVOKE rm*/ \
    hand_stem_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, \
    /*FACTORY rm*/ \
    hand_stem_send, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND, HAND_INVA_SEND \
}

//

static unsigned int hand_none_send(respo_ctrl *resctl, evdata *evdat) {
    OSEVPF("[FUNC]:hand_none_send\n");
    return RESP_STOP;
}

// hand_monce_send, // authen
unsigned int (*resp_handler_tab[LEVTYP_COUNT][LEVIVK_COUNT])(respo_ctrl *, evdata *) = {
    HAND_OSEV_SEND_TAB,
    HAND_BASE_SEND_TAB,
    {hand_none_send}, // kliv
    HAND_INVOK_SEND_TAB,
    HAND_COLLE_SEND_TAB,
    HAND_CONST_SEND_TAB,
    HAND_QUERY_SEND_TAB,
    {hand_none_send} //done
};

//


/* 
 * File:   initi_privile.h
 * Author: James Xu
 *
 * Created on 2023.12.22, AM 10:56
 */

#ifndef INITI_PRIVILE_H
#define INITI_PRIVILE_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    unsigned int INIT_INVA_RECV(session *seion, evdata *evdat);
    unsigned int init_bauth_recv(session *seion, evdata *evdat);
    unsigned int init_bpost_recv(session *seion, evdata *evdat);
    // status
    unsigned int init_bstatu_recv(session *seion, evdata *evdat);
    unsigned int init_bcomd_recv(session *seion, evdata *evdat);
    // privile
    unsigned int init_bpriv_list_recv(session *seion, evdata *evdat);
    unsigned int init_bpriv_role_recv(session *seion, evdata *evdat);
    unsigned int init_bpriv_user_recv(session *seion, evdata *evdat);

#define INIT_BASE_RECV_TAB { \
    /*AUTHEN*/ \
    init_bauth_recv, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, \
    /*POST*/ \
    init_bpost_recv, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, \
    /*STAT_ECHO STAT_STATIS*/ \
    init_bstatu_recv, init_bstatu_recv, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, \
    /*COMAND:COMDI_OPEN COMDI_CLOSE*/ \
    init_bcomd_recv, init_bcomd_recv, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, \
    /*PRIV_LIST PRIV_ROLE PRIV_USER*/ \
    init_bpriv_list_recv, init_bpriv_role_recv, init_bpriv_user_recv, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV \
}

    //
    unsigned int INIT_INVA_SEND(session *seion, evdata *evdat);
    unsigned int init_bauth_send(session *seion, evdata *evdat);
    unsigned int init_bpost_send(session *seion, evdata *evdat);
    unsigned int init_bstatu_send(session *seion, evdata *evdat);
    unsigned int init_bcomd_send(session *seion, evdata *evdat);
    unsigned int init_bprivi_send(session *seion, evdata *evdat);

#define INIT_BASE_SEND_TAB { \
    /*AUTHEN*/ \
    init_bauth_send, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, \
    /*POST*/ \
    init_bpost_send, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, \
    /*STAT_ECHO STAT_STATIS*/ \
    init_bstatu_send, init_bstatu_send, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, \
    /*COMAND:COMDI_OPEN COMDI_CLOSE*/ \
    init_bcomd_send, init_bcomd_send, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, \
    /*PRIV_LIST PRIV_ROLE PRIV_USER*/ \
    init_bprivi_send, init_bprivi_send, init_bprivi_send, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, 0x00 \
}


#ifdef __cplusplus
}
#endif

#endif /* INITI_PRIVILE_H */


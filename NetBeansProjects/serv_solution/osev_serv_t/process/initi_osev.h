
/* 
 * File:   initi_osev.h
 * Author: James Xu
 *
 * Created on 2023.12.22, AM 10:53
 */

#ifndef INITI_OSEV_H
#define INITI_OSEV_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    unsigned int INIT_INVA_RECV(session *seion, evdata *evdat);
    unsigned int init_oauth_recv(session *seion, evdata *evdat);
    unsigned int init_opost_recv(session *seion, evdata *evdat);
    // status
    unsigned int init_ostatu_recv(session *seion, evdata *evdat);
    unsigned int init_ocomd_recv(session *seion, evdata *evdat);
    // privile
    unsigned int init_opriv_list_recv(session *seion, evdata *evdat);
    unsigned int init_opriv_role_recv(session *seion, evdata *evdat);
    unsigned int init_opriv_user_recv(session *seion, evdata *evdat);

#define INIT_OSEV_RECV_TAB { \
    /*AUTHEN*/ \
    init_oauth_recv, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, \
    /*POST*/ \
    init_opost_recv, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, \
    /*STAT_ECHO STAT_STATIS*/ \
    init_ostatu_recv, init_ostatu_recv, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, \
    /*COMAND:COMDI_OPEN COMDI_CLOSE*/ \
    init_ocomd_recv, init_ocomd_recv, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, \
    /*PRIV_LIST PRIV_ROLE PRIV_USER*/ \
    init_opriv_list_recv, init_opriv_role_recv, init_opriv_user_recv, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV, INIT_INVA_RECV \
}

    //
    unsigned int INIT_INVA_SEND(session *seion, evdata *evdat);
    unsigned int init_oauth_send(session *seion, evdata *evdat);
    unsigned int init_opost_send(session *seion, evdata *evdat);
    unsigned int init_ostatu_send(session *seion, evdata *evdat);
    unsigned int init_ocomd_send(session *seion, evdata *evdat);
    unsigned int init_opriv_send(session *seion, evdata *evdat);

#define INIT_OSEV_SEND_TAB { \
    /*AUTHEN*/ \
    init_oauth_send, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, \
    /*POST*/ \
    init_opost_send, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, \
    /*STAT_ECHO STAT_STATIS*/ \
    init_ostatu_send, init_ostatu_send, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, \
    /*COMAND:COMDI_OPEN COMDI_CLOSE*/ \
    init_ocomd_send, init_ocomd_send, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, \
    /*PRIV_LIST PRIV_ROLE PRIV_USER*/ \
    init_opriv_send, init_opriv_send, init_opriv_send, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND, INIT_INVA_SEND \
}

#ifdef __cplusplus
}
#endif

#endif /* INITI_OSEV_H */


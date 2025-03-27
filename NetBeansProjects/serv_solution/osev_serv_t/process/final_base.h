
/* 
 * File:   final_base.h
 * Author: James Xu
 *
 * Created on 2023.12.22, AM 10:42
 */

#ifndef FINAL_BASE_H
#define FINAL_BASE_H

#ifdef __cplusplus
extern "C" {
#endif

    // END_BASE_RECV_TAB
    void END_INVA_RECV(session *seion);
    void end_bauth_recv(session *seion);
    // post
    void end_bpost_recv(session *seion);
    // status
    void end_bstatu_echo_recv(session *seion);
    // void end_bstat_statu_recv(session *seion);
    void end_bstat_stati_recv(session *seion);
    // bcomd
    void end_bcomd_open_recv(session *seion);
    void end_bcomd_close_recv(session *seion);
    // privile
    void end_bpriv_list_recv(session *seion);
    void end_bpriv_role_recv(session *seion);
    void end_bpriv_user_recv(session *seion);

#define END_BASE_RECV_TAB { \
    /*AUTHEN*/ \
    end_bauth_recv, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, \
    /*POST*/ \
    end_bpost_recv, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, \
    /*STAT_ECHO STAT_STATIS*/ \
    end_bstatu_echo_recv, end_bstat_stati_recv, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, \
    /*COMAND: COMDI_OPEN COMDI_CLOSE*/ \
    end_bcomd_open_recv, end_bcomd_close_recv, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, \
    /*PRIV_LIST PRIV_ROLE PRIV_USER*/ \
    end_bpriv_list_recv, end_bpriv_role_recv, end_bpriv_user_recv, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV \
}

    //
    void END_INVA_SEND(session *seion);
    void end_bauth_send(session *seion);
    void end_bpost_send(session *seion);
    void end_bstatu_send(session *seion);
    void end_bcomd_send(session *seion);
    void end_bprivi_send(session *seion);

#define END_BASE_SEND_TAB { \
    /*AUTHEN*/ \
    end_bauth_send, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, \
    /*POST*/ \
    end_bpost_send, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, \
    /*STAT_STATIS:STAT_ECHO STAT_STATIS*/ \
    end_bstatu_send, end_bstatu_send, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, \
    /*COMAND:COMDI_OPEN COMDI_CLOSE*/ \
    end_bcomd_send, end_bcomd_send, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, \
    /*PRIV_LIST PRIV_ROLE PRIV_USER*/ \
    end_bprivi_send, end_bprivi_send, end_bprivi_send, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND \
}




#ifdef __cplusplus
}
#endif

#endif /* FINAL_BASE_H */


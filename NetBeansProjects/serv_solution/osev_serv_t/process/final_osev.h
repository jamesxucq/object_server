
/* 
 * File:   final_osev.h
 * Author: James Xu
 *
 * Created on 2023.12.22, AM 10:41
 */

#ifndef FINAL_OSEV_H
#define FINAL_OSEV_H

#ifdef __cplusplus
extern "C" {
#endif

    // END_OSEV_RECV_TAB
    void END_INVA_RECV(session *seion);
    void end_oauth_recv(session *seion);
    void end_opost_recv(session *seion);
    void end_ostatu_echo_recv(session *seion);
    // void end_ostat_statu_recv(session *seion);
    void end_ostat_stati_recv(session *seion);
    void end_ocomd_open_recv(session *seion);
    void end_ocomd_close_recv(session *seion);
    void end_opriv_list_recv(session *seion);
    void end_opriv_role_recv(session *seion);
    void end_opriv_user_recv(session *seion);

#define END_OSEV_RECV_TAB { \
    /*AUTHEN*/ \
    end_oauth_recv, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, \
    /*POST*/ \
    end_opost_recv, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, \
    /*STAT_ECHO STAT_STATIS*/ \
    end_ostatu_echo_recv, end_ostat_stati_recv, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, \
    /*COMAND:COMDI_OPEN COMDI_CLOSE*/ \
    end_ocomd_open_recv, end_ocomd_close_recv, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, \
    /*PRIV_LIST PRIV_ROLE PRIV_USER*/ \
    end_opriv_list_recv, end_opriv_role_recv, end_opriv_user_recv, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV \
}

    //
    void END_INVA_SEND(session *seion);
    void end_oauth_send(session *seion);
    void end_opost_send(session *seion);
    void end_ostatu_send(session *seion);
    void end_ocomd_send(session *seion);
    void end_opriv_send(session *seion);

#define END_OSEV_SEND_TAB { \
    /*AUTHEN*/ \
    end_oauth_send, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, \
    /*POST*/ \
    end_opost_send, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, \
    /*STAT_ECHO STAT_STATIS*/ \
    end_ostatu_send, end_ostatu_send, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, \
    /*COMAND:COMDI_OPEN COMDI_CLOSE*/ \
    end_ocomd_send, end_ocomd_send, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, \
    /*PRIV_LIST PRIV_ROLE PRIV_USER*/ \
    end_opriv_send, end_opriv_send, end_opriv_send, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND \
}


#ifdef __cplusplus
}
#endif

#endif /* FINAL_OSEV_H */


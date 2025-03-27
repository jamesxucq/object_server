
/* 
 * File:   final_constr.h
 * Author: James Xu
 *
 * Created on 2023.12.22, AM 10:44
 */

#ifndef FINAL_CONSTR_H
#define FINAL_CONSTR_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    void END_INVA_RECV(session *seion);
    void end_enti_post_recv(session *seion);
    void end_enti_statu_echo_recv(session *seion);
    void end_enti_statu_attri_recv(session *seion);
    void end_enti_statu_stati_recv(session *seion);
    //
    void end_enti_creat_recv(session *seion);
    void end_enti_drop_recv(session *seion);
    void end_enti_updat_recv(session *seion);
    void end_enti_inser_recv(session *seion);
    void end_enti_searc_recv(session *seion);
    void end_enti_invok_recv(session *seion);

    //
#define END_CONST_RECV_TAB { \
    /*POST*/ \
    end_enti_post_recv, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, \
    /*STATU*/ \
    end_enti_statu_echo_recv, end_enti_statu_attri_recv, end_enti_statu_stati_recv, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, \
    /*CREATE*/ \
    end_enti_creat_recv, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, \
    /*DROP*/ \
    end_enti_drop_recv, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, \
    /*UPDATE*/ \
    end_enti_updat_recv, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, \
    /*INSERT*/ \
    end_enti_inser_recv, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, \
    /*SEARCH*/ \
    end_enti_searc_recv, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, \
    /*INVOKE*/ \
    end_enti_invok_recv, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV, END_INVA_RECV \
}

    // END_CONST_SEND_TAB END_QUERY_SEND_TAB
    void END_INVA_SEND(session *seion);
    void end_enti_staco_send(session *seion);
    void end_enti_respo_send(session *seion);

    // END_CONST_SEND_TAB END_QUERY_SEND_TAB
#define END_CONST_SEND_TAB { \
    /*POST*/ \
    end_enti_staco_send, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, \
    /*STATU*/ \
    end_enti_staco_send, end_enti_staco_send, end_enti_staco_send, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, \
    /*CREATE*/ \
    end_enti_staco_send, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, \
    /*DROP*/ \
    end_enti_staco_send, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, \
    /*UPDATE*/ \
    end_enti_staco_send, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, \
    /*INSERT*/ \
    end_enti_staco_send, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, \
    /*SEARCH*/ \
    end_enti_respo_send, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, \
    /*INVOKE*/ \
    end_enti_respo_send, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND, END_INVA_SEND \
}

#ifdef __cplusplus
}
#endif

#endif /* FINAL_CONSTR_H */


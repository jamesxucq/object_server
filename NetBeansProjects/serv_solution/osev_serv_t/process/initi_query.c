
#include "chk_privi_bzl.h"

#include "../event.h"
#include "../session.h"

#include "initi_utili.h"
#include "initi_query.h"

// query

unsigned int init_quer_post_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_quer_post_recv\n");
    OPEN_QUERY_MEMO_SE(&seion->rvsctl, REQU_STOP)
    return REQU_CONTINUE;
}

unsigned int init_quer_statu_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_quer_statu_recv\n");
    OPEN_QUERY_MEMO_SE(&seion->rvsctl, REQU_STOP)
    return REQU_CONTINUE;
}

unsigned int init_quer_creat_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_quer_creat_recv\n");
    OPEN_QUERY_MEMO_SE(&seion->rvsctl, REQU_STOP)
    return REQU_CONTINUE;
}

unsigned int init_quer_drop_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_quer_drop_recv\n");
    OPEN_QUERY_MEMO_SE(&seion->rvsctl, REQU_STOP)
    return REQU_CONTINUE;
}

unsigned int init_quer_updat_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_quer_updat_recv\n");
    OPEN_QUERY_FILE_SE(REQU_STOP)
    return REQU_CONTINUE;
}

unsigned int init_quer_inser_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_quer_inser_recv\n");
    OPEN_QUERY_FILE_SE(REQU_STOP)
    return REQU_CONTINUE;
}

unsigned int init_quer_searc_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_quer_searc_recv\n");
    OPEN_QUERY_MEMO_SE(&seion->rvsctl, REQU_STOP)
    return REQU_CONTINUE;
}

unsigned int init_quer_invok_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_quer_invok_recv\n");
    OPEN_QUERY_MEMO_SE(&seion->rvsctl, REQU_STOP)
    return REQU_CONTINUE;
}

unsigned int init_quer_facto_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_quer_facto_recv\n");
    OPEN_QUERY_MEMO_SE(&seion->rvsctl, REQU_STOP)
    return REQU_CONTINUE;
}

//

unsigned int init_query_send(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_query_send\n");
    PRODU_QUERY_SEND(evdat, seion->rvsctl);
    return RESP_CONTINUE;
}



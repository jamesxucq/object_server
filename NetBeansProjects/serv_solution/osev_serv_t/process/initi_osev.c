
#include "chk_privi_bzl.h"

#include "../event.h"
#include "../session.h"

#include "initi_utili.h"
#include "initi_osev.h"

// authen

unsigned int INIT_INVA_RECV(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:INIT_INVA_RECV\n");
    return REQU_STOP;
}

unsigned int init_oauth_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_oauth_recv\n");
    CHECK_AUTHEN_HEAD(&seion->rvsctl, evdat)
    OPEN_AUTHEN_SE(REQU_STOP)
    return REQU_CONTINUE;
}

unsigned int init_opost_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_opost_recv\n");
    CHECK_POST_INVAL(&seion->rvsctl, &seion->inval, evdat);
    CHECK_POST_PRIVILE(&seion->rvsctl, seion->apval, OPRIV_POST, REQU_STOP)
    //
    OPEN_POST_SE(REQU_STOP)
    return REQU_CONTINUE;
}

// status

unsigned int init_ostatu_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_ostatu_recv\n");
    CHECK_STATU_INVAL(&seion->rvsctl, &seion->inval, evdat);
    CHECK_STATUS_PRIVILE(&seion->rvsctl, seion->apval, OPRIV_STATU, REQU_STOP)
    //
    OPEN_STATUS_SE(REQU_STOP)
    return REQU_CONTINUE;
}

// COMAND

unsigned int init_ocomd_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_ocomd_recv\n");
    CHECK_COMAND_HEAD(&seion->rvsctl, evdat)
    CHECK_COMMAND_PRIVILE(&seion->rvsctl, seion->apval, OPRIV_COMND, REQU_STOP)
    //
    OPEN_COMAND_SE(REQU_STOP)
    return REQU_CONTINUE;
}

// privile

unsigned int init_opriv_list_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_opriv_list_recv\n");
    CHECK_PRIVI_INVAL(&seion->rvsctl, &seion->inval, evdat);
    CHECK_OPRIVLU_PRIVILE(&seion->rvsctl, seion->apval, OPRIV_PRIVI, REQU_STOP)
    //
    OPEN_PRIVILE_SE(REQU_STOP)
    return REQU_CONTINUE;
}

unsigned int init_opriv_role_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_opriv_role_recv\n");
    CHECK_PRIVI_INVAL(&seion->rvsctl, &seion->inval, evdat);
    //
    OPEN_PRIVILE_SE(REQU_STOP)
    return REQU_CONTINUE;
}

unsigned int init_opriv_user_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_opriv_user_recv\n");
    CHECK_PRIVI_INVAL(&seion->rvsctl, &seion->inval, evdat);
    CHECK_OPRIVLU_PRIVILE(&seion->rvsctl, seion->apval, OPRIV_PRIVI, REQU_STOP)
    //
    OPEN_PRIVILE_SE(REQU_STOP)
    return REQU_CONTINUE;
}

//

unsigned int INIT_INVA_SEND(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:INIT_INVA_SEND\n");
    return RESP_STOP;
}

unsigned int init_oauth_send(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_oauth_send\n");
    PRODU_AUTHEN_SEND(evdat, seion->rvsctl);
    return RESP_CONTINUE;
}

//

unsigned int init_opost_send(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_opost_send\n");
    PRODU_POST_SEND(evdat, seion->rvsctl);
    return RESP_CONTINUE;
}

unsigned int init_ostatu_send(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_ostatu_send\n");
    PRODU_STATUS_SEND(evdat, seion->rvsctl);
    return RESP_CONTINUE;
}

unsigned int init_ocomd_send(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_ocomd_send\n");
    PRODU_COMAND_SEND(evdat, seion->rvsctl);
    return RESP_CONTINUE;
}

unsigned int init_opriv_send(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_opriv_send\n");
    PRODU_PRIVILE_SEND(evdat, seion->rvsctl);
    return RESP_CONTINUE;
}
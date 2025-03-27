
#include "chk_privi_bzl.h"

#include "../event.h"
#include "../session.h"

#include "initi_utili.h"
#include "initi_base.h"

// authen

unsigned int init_bauth_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_bauth_recv\n");
    CHECK_AUTHEN_HEAD(&seion->rvsctl, evdat)
    OPEN_AUTHEN_SE(REQU_STOP)
    return REQU_CONTINUE;
}

// status

unsigned int init_bpost_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_bpost_recv\n");
    CHECK_POST_INVAL(&seion->rvsctl, &seion->inval, evdat);
    CHECK_POST_PRIVILE(&seion->rvsctl, seion->apval, BPRIV_POST, REQU_STOP)
    //
    OPEN_POST_SE(REQU_STOP)
    return REQU_CONTINUE;
}

// status

unsigned int init_bstatu_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_bstatu_recv\n");
    CHECK_STATU_INVAL(&seion->rvsctl, &seion->inval, evdat);
    CHECK_STATUS_PRIVILE(&seion->rvsctl, seion->apval, BPRIV_STATU, REQU_STOP)
    //
    OPEN_STATUS_SE(REQU_STOP)
    return REQU_CONTINUE;
}

// COMAND

unsigned int init_bcomd_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_bcomd_recv\n");
    CHECK_COMAND_HEAD(&seion->rvsctl, evdat)
    CHECK_COMMAND_PRIVILE(&seion->rvsctl, seion->apval, BPRIV_COMND, REQU_STOP)
    //
    OPEN_COMAND_SE(REQU_STOP)
    return REQU_CONTINUE;
}

// privile

unsigned int init_bpriv_list_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_bpriv_list_recv\n");
    CHECK_PRIVI_INVAL(&seion->rvsctl, &seion->inval, evdat);
    CHECK_BPRIVI_PRIVILE(&seion->rvsctl, seion->apval, BPRIV_PRIVI, REQU_STOP)
    //
    OPEN_PRIVILE_SE(REQU_STOP)
    return REQU_CONTINUE;
}

unsigned int init_bpriv_role_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_bpriv_role_recv\n");
    CHECK_PRIVI_INVAL(&seion->rvsctl, &seion->inval, evdat);
    CHECK_BPRIVI_PRIVILE(&seion->rvsctl, seion->apval, BPRIV_PRIVI, REQU_STOP)
    //
    OPEN_PRIVILE_SE(REQU_STOP)
    return REQU_CONTINUE;
}

unsigned int init_bpriv_user_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_bpriv_user_recv\n");
    CHECK_PRIVI_INVAL(&seion->rvsctl, &seion->inval, evdat);
    CHECK_BPRIVI_PRIVILE(&seion->rvsctl, seion->apval, BPRIV_PRIVI, REQU_STOP)
    //
    OPEN_PRIVILE_SE(REQU_STOP)
    return REQU_CONTINUE;
}

//

unsigned int init_bauth_send(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_bauth_send\n");
    PRODU_AUTHEN_SEND(evdat, seion->rvsctl);
    return RESP_CONTINUE;
}
//

unsigned int init_bpost_send(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_bpost_send\n");
    PRODU_POST_SEND(evdat, seion->rvsctl);
    return RESP_CONTINUE;
}

//

unsigned int init_bstatu_send(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_bstatu_send\n");
    PRODU_STATUS_SEND(evdat, seion->rvsctl);
    return RESP_CONTINUE;
}

//

unsigned int init_bcomd_send(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_bcomd_send\n");
    PRODU_COMAND_SEND(evdat, seion->rvsctl);
    return RESP_CONTINUE;
}

//

unsigned int init_bprivi_send(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_bprivi_send\n");
    PRODU_PRIVILE_SEND(evdat, seion->rvsctl);
    return RESP_CONTINUE;
}

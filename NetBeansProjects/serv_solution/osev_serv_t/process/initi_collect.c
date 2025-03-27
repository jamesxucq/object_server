
#include "chk_privi_bzl.h"

#include "../event.h"
#include "../session.h"

#include "initi_utili.h"
#include "initi_collect.h"

// colle

unsigned int init_coll_post_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_coll_post_recv\n");
    CHECK_LEVCI_PRIVILE(&seion->rvsctl, seion->apval, CPOST_PRIVI, REQU_STOP)
    //
    OPEN_COLLE_SE(REQU_STOP)
    return REQU_CONTINUE;
}

unsigned int init_coll_statu_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_coll_statu_recv\n");
    CHECK_LEVCI_PRIVILE(&seion->rvsctl, seion->apval, CLIST_PRIVI, REQU_STOP)
    //
    OPEN_COLLE_SE(REQU_STOP)
    return REQU_CONTINUE;
}

unsigned int init_coll_creat_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_coll_creat_recv\n");
    CHECK_LEVCI_PRIVILE(&seion->rvsctl, seion->apval, CCREAT_PRIVI, REQU_STOP)
    //
    OPEN_COLLE_SE(REQU_STOP)
    return REQU_CONTINUE;
}

unsigned int init_coll_repla_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_coll_repla_recv\n");
    CHECK_LEVCI_PRIVILE(&seion->rvsctl, seion->apval, CREPLA_PRIVI, REQU_STOP)
    //
    OPEN_COLLE_SE(REQU_STOP)
    return REQU_CONTINUE;
}

unsigned int init_coll_drop_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_coll_drop_recv\n");
    CHECK_LEVCI_PRIVILE(&seion->rvsctl, seion->apval, CDROP_PRIVI, REQU_STOP)
    //
    OPEN_COLLE_SE(REQU_STOP)
    return REQU_CONTINUE;
}

unsigned int init_coll_integra_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_coll_integra_recv\n");
    CHECK_LEVCI_PRIVILE(&seion->rvsctl, seion->apval, CINTEGRA_PRIVI, REQU_STOP)
    //
    OPEN_COLLE_SE(REQU_STOP)
    return REQU_CONTINUE;
}

unsigned int init_coll_reload_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_coll_reload_recv\n");
    CHECK_LEVCI_PRIVILE(&seion->rvsctl, seion->apval, CRELOAD_PRIVI, REQU_STOP)
    //
    OPEN_COLLE_SE(REQU_STOP)
    return REQU_CONTINUE;
}

//

unsigned int init_colle_send(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_colle_send\n");
    PRODU_COLLE_SEND(evdat, seion->rvsctl);
    return RESP_CONTINUE;
}


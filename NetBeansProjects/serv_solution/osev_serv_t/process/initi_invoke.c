
#include "chk_privi_bzl.h"

#include "../event.h"
#include "../session.h"

#include "initi_utili.h"
#include "initi_invoke.h"

// invoke

unsigned int init_invo_post_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_invo_post_recv\n");
    CHECK_LEVCI_PRIVILE(&seion->rvsctl, seion->apval, IPOST_PRIVI, REQU_STOP)
    //
    OPEN_INVOKE_SE(REQU_STOP)
    return REQU_CONTINUE;
}

unsigned int init_invo_statu_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_invo_statu_recv\n");
    CHECK_LEVCI_PRIVILE(&seion->rvsctl, seion->apval, IECHO_PRIVI, REQU_STOP)
    //
    OPEN_INVOKE_SE(REQU_STOP)
    return REQU_CONTINUE;
}
//

unsigned int init_invo_creat_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_invo_creat_recv\n");
    CHECK_LEVCI_PRIVILE(&seion->rvsctl, seion->apval, ICREAT_PRIVI, REQU_STOP)
    //
    OPEN_INVOKE_SE(REQU_STOP)
    return REQU_CONTINUE;
}
// 

unsigned int init_invo_repla_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_invo_repla_recv\n");
    CHECK_LEVCI_PRIVILE(&seion->rvsctl, seion->apval, IREPLA_PRIVI, REQU_STOP)
    //
    OPEN_INVOKE_SE(REQU_STOP)
    return REQU_CONTINUE;
}

// 

unsigned int init_invo_drop_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_invo_drop_recv\n");
    CHECK_LEVCI_PRIVILE(&seion->rvsctl, seion->apval, IDROP_PRIVI, REQU_STOP)
    //
    OPEN_INVOKE_SE(REQU_STOP)
    return REQU_CONTINUE;
}
//

unsigned int init_invo_integra_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_invo_integra_recv\n");
    CHECK_LEVCI_PRIVILE(&seion->rvsctl, seion->apval, IINTEGRA_PRIVI, REQU_STOP)
    //
    OPEN_INVOKE_SE(REQU_STOP)
    return REQU_CONTINUE;
}
// 

unsigned int init_invo_reload_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_invo_reload_recv\n");
    CHECK_LEVCI_PRIVILE(&seion->rvsctl, seion->apval, IRELOAD_PRIVI, REQU_STOP)
    //
    OPEN_INVOKE_SE(REQU_STOP)
    return REQU_CONTINUE;
}

//

unsigned int init_invok_send(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_invok_send\n");
    PRODU_INVOKE_SEND(evdat, seion->rvsctl);
    return RESP_CONTINUE;
}

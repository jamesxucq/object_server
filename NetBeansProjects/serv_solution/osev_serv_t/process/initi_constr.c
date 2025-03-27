
#include "chk_privi_bzl.h"

#include "../event.h"
#include "../session.h"

#include "initi_utili.h"
#include "initi_constr.h"

// constr

unsigned int init_enti_post_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_enti_post_recv\n");
    CHECK_LEVEN_PRIVILE(&seion->rvsctl, seion->apval, &seion->inval.inte_obid, &epost_privi, REQU_STOP)
    //
    OPEN_CONST_SE(&seion->rvsctl, REQU_STOP)
    return REQU_CONTINUE;
}

unsigned int init_enti_statu_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_enti_statu_recv\n");
    CHECK_LEVEN_PRIVILE(&seion->rvsctl, seion->apval, &seion->inval.inte_obid, &eecho_privi, REQU_STOP)
    //
    OPEN_CONST_SE(&seion->rvsctl, REQU_STOP)
    return REQU_CONTINUE;
}

unsigned int init_enti_creat_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_enti_creat_recv\n");
    CHECK_LEVEN_PRIVILE(&seion->rvsctl, seion->apval, &seion->inval.inte_obid, &ecrea_privi, REQU_STOP)
    //
    OPEN_CONST_SE(&seion->rvsctl, REQU_STOP)
    return REQU_CONTINUE;
}

unsigned int init_enti_drop_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_enti_drop_recv\n");
    CHECK_LEVEN_PRIVILE(&seion->rvsctl, seion->apval, &seion->inval.inte_obid, &edrop_privi, REQU_STOP)
    //
    OPEN_CONST_SE(&seion->rvsctl, REQU_STOP)
    return REQU_CONTINUE;
}

unsigned int init_enti_updat_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_enti_updat_recv\n");
    CHECK_LEVEN_PRIVILE(&seion->rvsctl, seion->apval, &seion->inval.inte_obid, &eupda_privi, REQU_STOP)
    //
    OPEN_CONST_SE(&seion->rvsctl, REQU_STOP)
    return REQU_CONTINUE;
}

unsigned int init_enti_inser_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_oonst_recv\n");
    CHECK_LEVEN_PRIVILE(&seion->rvsctl, seion->apval, &seion->inval.inte_obid, &einse_privi, REQU_STOP)
    //
    OPEN_CONST_SE(&seion->rvsctl, REQU_STOP)
    return REQU_CONTINUE;
}

unsigned int init_enti_searc_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_enti_searc_recv\n");
    CHECK_LEVEN_PRIVILE(&seion->rvsctl, seion->apval, &seion->inval.inte_obid, &esear_privi, REQU_STOP)
    //
    OPEN_CONST_SE(&seion->rvsctl, REQU_STOP)
    return REQU_CONTINUE;
}

unsigned int init_enti_invok_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_enti_invok_recv\n");
    CHECK_LEVEN_PRIVILE(&seion->rvsctl, seion->apval, &seion->inval.inte_obid, &einvo_privi, REQU_STOP)
    //
    OPEN_CONST_SE(&seion->rvsctl, REQU_STOP)
    return REQU_CONTINUE;
}

//

unsigned int init_const_send(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_const_send\n");
    PRODU_CONST_SEND(evdat, seion->rvsctl);
    return RESP_CONTINUE;
}

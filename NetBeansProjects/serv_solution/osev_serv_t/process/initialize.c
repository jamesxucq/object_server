
#include "commo_header.h"
#include "kcomm_header.h"

#include "../event.h"
#include "initi_utili.h"
#include "initi_osev.h"
#include "initi_base.h"
#include "initi_invoke.h"
#include "initi_constr.h"
#include "initi_collect.h"
#include "initi_query.h"

#include "initialize.h"

//epoll serv handle recv and create send
// kalive

static unsigned int init_kaliv_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_kaliv_recv\n");
    CHECK_KALIVE_HEAD(&seion->rvsctl, evdat);
    OPEN_KALIVE_SE(REQU_STOP);
    return REQU_CONTINUE;
}

//

static unsigned int init_done_recv(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_done_recv\n");
    CHECK_DONE_HEAD(&seion->rvsctl, evdat);
    OPEN_DONE_SE(REQU_STOP);
    return REQU_CONTINUE;
}

//　lev
unsigned int (*requ_initialize_tab[LEVTYP_COUNT][LEVIVK_COUNT])(session *, evdata *) = {
    INIT_OSEV_RECV_TAB,
    INIT_BASE_RECV_TAB,
    {init_kaliv_recv},
    INIT_INVOK_RECV_TAB,
    INIT_COLLE_RECV_TAB,
    INIT_CONST_RECV_TAB,
    INIT_QUERY_RECV_TAB,
    {init_done_recv}
};

//

static unsigned int init_kaliv_send(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_kaliv_send\n");
    PRODU_KALIVE_SEND(evdat, seion->rvsctl)
    return RESP_CONTINUE;
}

//

static unsigned int init_done_send(session *seion, evdata *evdat) {
    OSEVPF("[FUNC]:init_done_send\n");
    PRODU_DONE_SEND(evdat, seion->rvsctl)
    return RESP_CONTINUE;
}

unsigned int (*resp_initialize_tab[LEVTYP_COUNT][LEVIVK_COUNT])(session *, evdata *) = {
    INIT_OSEV_SEND_TAB,
    INIT_BASE_SEND_TAB,
    {init_kaliv_send},
    INIT_INVOK_SEND_TAB,
    INIT_COLLE_SEND_TAB,
    INIT_CONST_SEND_TAB,
    INIT_QUERY_SEND_TAB,
    {init_done_send}
};

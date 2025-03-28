
#include "authen_bzl.h"
#include "../session.h"
// #include "finalize.h"

#include "exceptio.h"

//

static void INVA_EXCEP(session *seion) {
    OSEVPF("[FUNC]:INVA_EXCEP\n");
}

//

static void authe_excep(session *seion) {
    OSEVPF("[FUNC]:authe_excep\n");
    authe_epoll_exceptio(seion->apval->_action_key_);
    CLOSE_AUTHEN_SE(&seion->rvsctl);
}

static void post_excep(session *seion) {
    OSEVPF("[FUNC]:post_excep\n");
    authe_epoll_exceptio(seion->apval->_action_key_);
    CLOSE_POST_SE(&seion->rvsctl);
}

//

static void statu_excep(session *seion) {
    OSEVPF("[FUNC]:statu_excep\n");
    authe_epoll_exceptio(seion->apval->_action_key_);
    CLOSE_STATUS_SE(&seion->rvsctl);
}

//

static void comnd_excep(session *seion) {
    OSEVPF("[FUNC]:comnd_excep\n");
    authe_epoll_exceptio(seion->apval->_action_key_);
    CLOSE_COMAND_SE(&seion->rvsctl);
}

//

static void privi_excep(session *seion) {
    OSEVPF("[FUNC]:privi_excep\n");
    authe_epoll_exceptio(seion->apval->_action_key_);
    CLOSE_PRIVILE_SE(&seion->rvsctl);
}

#define OSEV_EXCEPTIO_TAB { \
     /*AUTHEN*/ \
    authe_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, \
     /*POST*/ \
    post_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, \
    /*STAT_ECHO STAT_STATIS*/ \
    statu_excep, statu_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, \
    /* COMAND:COMDI_OPEN COMDI_CLOSE*/ \
    comnd_excep, comnd_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, \
    /*PRIV_LIST PRIV_ROLE PRIV_USER*/ \
    privi_excep, privi_excep, privi_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP \
}



#define BASE_EXCEPTIO_TAB { \
    /*AUTHEN*/ \
    authe_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, \
    /*POST*/ \
    post_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, \
    /*STAT_ECHO STAT_STATIS*/ \
    statu_excep, statu_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, \
    /*COMDI_OPEN COMDI_CLOSE*/ \
    comnd_excep, comnd_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, /*COMAND*/ \
    /*PRIV_LIST PRIV_ROLE PRIV_USER*/ \
    privi_excep, privi_excep, privi_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP \
}

//

static void kaliv_excep(session *seion) {
    OSEVPF("[FUNC]:kaliv_excep\n");
    authe_epoll_exceptio(seion->apval->_action_key_);
    CLOSE_KALIVE_SE(&seion->rvsctl);
}

//

static void invok_excep(session *seion) {
    OSEVPF("[FUNC]:invok_excep\n");
    authe_epoll_exceptio(seion->apval->_action_key_);
    CLOSE_INVOKE_SE(&seion->rvsctl);
}

#define INVOK_EXCEPTIO_TAB { \
    invok_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, /*INVO_POST*/ \
    invok_excep, invok_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, /*INVO_STATU*/ \
    invok_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, /*INVO_CREAT*/ \
    invok_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, /*INVO_REPLA*/ \
    invok_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, /*INVO_DROP*/ \
    invok_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, /*INVO_INTEGRA*/ \
    invok_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP /*INVO_RELOAD*/ \
}

//

static void colle_excep(session *seion) {
    OSEVPF("[FUNC]:colle_excep\n");
    authe_epoll_exceptio(seion->apval->_action_key_);
    CLOSE_COLLE_SE(&seion->rvsctl);
}

#define COLLE_EXCEPTIO_TAB { \
    colle_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, /*COLE_POST*/ \
    colle_excep, colle_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, /*COLE_STATU*/ \
    colle_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, /*COLE_CREAT*/ \
    colle_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, /*COLE_REPLA*/ \
    colle_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, /*COLE_DROP*/ \
    colle_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, /*COLE_INTEGRA*/ \
    colle_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP /*COLE_RELOAD*/ \
}

//

static void const_staco_excep(session *seion) {
    OSEVPF("[FUNC]:const_staco_excep\n");
    authe_epoll_exceptio(seion->apval->_action_key_);
    CLOSE_CONST_STACO_SE(&seion->rvsctl)
}

static void const_respo_excep(session *seion) {
    OSEVPF("[FUNC]:const_respo_excep\n");
    authe_epoll_exceptio(seion->apval->_action_key_);
    CLOSE_CONST_RESPO_SE(&seion->rvsctl)
}

// CLOSE_CONST_SE
#define CONST_EXCEPTIO_TAB { \
    const_staco_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, /*POST*/ \
    const_staco_excep, const_staco_excep, const_staco_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, /*STATU*/ \
    const_staco_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, /*CREATE*/ \
    const_staco_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, /*DROP*/ \
    const_staco_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, /*UPDATE*/ \
    const_staco_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, /*INSERT*/ \
    const_respo_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, /*SEARCH*/ \
    const_respo_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP /*INVOKE*/ \
}

// CLOSE_QUERY_SE

static void query_staco_excep(session *seion) {
    OSEVPF("[FUNC]:query_staco_excep\n");
    authe_epoll_exceptio(seion->apval->_action_key_);
    CLOSE_QUERY_STACO_SE(&seion->rvsctl)
}

static void query_reque_excep(session *seion) {
    OSEVPF("[FUNC]:query_reque_excep\n");
    authe_epoll_exceptio(seion->apval->_action_key_);
    CLOSE_QUERY_REQUE_SE(&seion->rvsctl)
}

static void query_respo_excep(session *seion) {
    OSEVPF("[FUNC]:query_respo_excep\n");
    authe_epoll_exceptio(seion->apval->_action_key_);
    CLOSE_QUERY_RESPO_SE(&seion->rvsctl)
}

static void query_quesp_excep(session *seion) {
    OSEVPF("[FUNC]:query_quesp_excep\n");
    authe_epoll_exceptio(seion->apval->_action_key_);
    CLOSE_QUERY_QUESP_SE(&seion->rvsctl)
}

#define QUERY_EXCEPTIO_TAB { \
    query_staco_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, /*POST*/ \
    query_staco_excep, query_staco_excep, query_staco_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, /*STATU*/ \
    query_staco_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, /*CREATE*/ \
    query_staco_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, /*DROP*/ \
    query_reque_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, /*UPDATE*/ \
    query_quesp_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, /*INSERT*/ \
    query_respo_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, /*SEARCH*/ \
    query_respo_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, /*INVOKE*/ \
    query_respo_excep, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP, INVA_EXCEP /*FACTORY*/ \
}

//

static void done_excep(session *seion) {
    OSEVPF("[FUNC]:done_excep\n");
    authe_epoll_exceptio(seion->apval->_action_key_);
    CLOSE_DONE_SE(&seion->rvsctl);
}

//
void (*rvse_exceptio_tab[LEVTYP_COUNT][LEVIVK_COUNT])(session*) = {
    OSEV_EXCEPTIO_TAB,
    BASE_EXCEPTIO_TAB,
    {kaliv_excep},
    INVOK_EXCEPTIO_TAB,
    COLLE_EXCEPTIO_TAB,
    CONST_EXCEPTIO_TAB,
    QUERY_EXCEPTIO_TAB,
    {done_excep}
};
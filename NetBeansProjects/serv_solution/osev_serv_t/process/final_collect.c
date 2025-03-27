
// #include "chk_privi_bzl.h"
#include "reqin_ite.h"

#include "../session.h"

#include "final_collect.h"


// END_COLLE_RECV_TAB

void end_coll_post_recv(session *seion) {
    OSEVPF("[FUNC]:end_coll_post_recv\n");
    PARSE_CPOST_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_CPOST_ITE(&seion->rvsctl, seion->baval, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

//

// void end_coll_list_recv

void end_coll_statu_list_recv(session *seion) {
    OSEVPF("[FUNC]:end_coll_statu_list_recv\n");
    PARSE_CSTATU_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_CSTATU_LIST_ITE(&seion->rvsctl, seion->baval, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_coll_statu_stati_recv(session *seion) {
    OSEVPF("[FUNC]:end_coll_statu_stati_recv\n");
    PARSE_CSTATU_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_CSTATU_STATI_ITE(&seion->rvsctl, seion->baval, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_coll_creat_recv(session *seion) {
    OSEVPF("[FUNC]:end_coll_creat_recv\n");
    PARSE_CCREAT_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_CCREAT_ITE(&seion->rvsctl, seion->baval, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_coll_repla_recv(session *seion) {
    OSEVPF("[FUNC]:end_coll_repla_recv\n");
    PARSE_CREPLA_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_CREPLA_ITE(&seion->rvsctl, seion->baval, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_coll_drop_recv(session *seion) {
    OSEVPF("[FUNC]:end_coll_drop_recv\n");
    PARSE_CDROP_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_CDROP_ITE(&seion->rvsctl, seion->baval, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_coll_integra_recv(session *seion) {
    OSEVPF("[FUNC]:end_coll_integra_recv\n");
    PARSE_CINTEGRA_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_CINTEGRA_ITE(&seion->rvsctl, seion->baval->base_name, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_coll_reload_recv(session *seion) {
    OSEVPF("[FUNC]:end_coll_reload_recv\n");
    PARSE_CRELOAD_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_CRELOAD_ITE(&seion->rvsctl, seion->baval, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

//

void end_colle_send(session *seion) {
    OSEVPF("[FUNC]:end_colle_send\n");
    CLOSE_COLLE_SE(&seion->rvsctl);
}



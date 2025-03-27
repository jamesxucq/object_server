
// #include "chk_privi_bzl.h"
#include "reqin_ite.h"

#include "../session.h"

#include "final_invoke.h"


// END_INVOK_RECV_TAB

void end_invo_post_recv(session *seion) {
    OSEVPF("[FUNC]:end_invo_post_recv\n");
    PARSE_IPOST_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_IPOST_ITE(&seion->rvsctl, seion->baval, &seion->inval.inte_obid, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

//

// end_invo_list_recv

void end_invo_statu_list_recv(session *seion) {
    OSEVPF("[FUNC]:end_invo_statu_list_recv\n");
    PARSE_ISTATU_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_ISTATU_LIST_ITE(&seion->rvsctl, seion->baval, &seion->inval.inte_obid, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_invo_statu_stati_recv(session *seion) {
    OSEVPF("[FUNC]:end_invo_statu_stati_recv\n");
    PARSE_ISTATU_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_ISTATU_STATI_ITE(&seion->rvsctl, seion->baval, &seion->inval.inte_obid, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_invo_creat_recv(session *seion) {
    OSEVPF("[FUNC]:end_invo_creat_recv\n");
    PARSE_ICREAT_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_ICREAT_ITE(&seion->rvsctl, seion->baval, &seion->inval.inte_obid, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_invo_repla_recv(session *seion) {
    OSEVPF("[FUNC]:end_invo_repla_recv\n");
    PARSE_IREPLA_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_IREPLA_ITE(&seion->rvsctl, seion->baval, &seion->inval.inte_obid, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_invo_drop_recv(session *seion) {
    OSEVPF("[FUNC]:end_invo_drop_recv\n");
    PARSE_IDROP_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_IDROP_ITE(&seion->rvsctl, seion->baval, &seion->inval.inte_obid, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_invo_integra_recv(session *seion) {
    OSEVPF("[FUNC]:end_invo_integra_recv\n");
    PARSE_IINTEGRA_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_IINTEGRA_ITE(&seion->rvsctl, seion->baval, &seion->inval.inte_obid, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_invo_reload_recv(session *seion) {
    OSEVPF("[FUNC]:end_invo_reload_recv\n");
    PARSE_IRELOAD_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_IRELOAD_ITE(&seion->rvsctl, seion->baval, &seion->inval.inte_obid, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

//

void end_invok_send(session *seion) {
    OSEVPF("[FUNC]:end_invok_send\n");
    CLOSE_INVOKE_SE(&seion->rvsctl);
}


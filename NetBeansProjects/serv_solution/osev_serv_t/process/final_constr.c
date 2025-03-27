
// #include "chk_privi_bzl.h"
#include "reqin_ite.h"

#include "../session.h"

#include "final_constr.h"

// END_CONST_RECV_TAB

void end_enti_post_recv(session *seion) {
    OSEVPF("[FUNC]:end_enti_post_recv\n");
    PARSE_EPOST_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_EPOST_ITE(&seion->rvsctl, (void *) seion->baval, &seion->inval.inte_obid, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

//

void end_enti_statu_echo_recv(session *seion) {
    OSEVPF("[FUNC]:end_enti_statu_echo_recv\n");
    PARSE_ESTATU_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_ESTATU_ECHO_ITE(&seion->rvsctl, (void *) seion->baval, &seion->inval.inte_obid, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

/*
void end_enti_echo_name_recv(session *seion) {
    OSEVPF("[FUNC]:end_enti_echo_name_recv\n");
    PARSE_ESTATU_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_ESTATU_NAME_ITE(&seion->rvsctl, (void *) seion->baval, &seion->inval.inte_obid, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}
*/

void end_enti_statu_attri_recv(session *seion) {
    OSEVPF("[FUNC]:end_enti_statu_attri_recv\n");
    PARSE_ESTATU_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_ESTATU_ATTRI_ITE(&seion->rvsctl, (void *) seion->baval, &seion->inval.inte_obid, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_enti_statu_stati_recv(session *seion) {
    OSEVPF("[FUNC]:end_enti_statu_stati_recv\n");
    PARSE_ESTATU_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_ESTATU_STATI_ITE(&seion->rvsctl, (void *) seion->baval, &seion->inval.inte_obid, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_enti_creat_recv(session *seion) {
    OSEVPF("[FUNC]:end_enti_creat_recv\n");
    PARSE_ECREAT_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_ECREAT_ITE(&seion->rvsctl, (void *) seion->baval, &seion->inval.inte_obid, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_enti_drop_recv(session *seion) {
    OSEVPF("[FUNC]:end_enti_drop_recv\n");
    PARSE_EDROP_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_EDROP_ITE(&seion->rvsctl, (void *) seion->baval, &seion->inval.inte_obid, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_enti_updat_recv(session *seion) {
    OSEVPF("[FUNC]:end_enti_updat_recv\n");
    PARSE_EUPDAT_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_EUPDAT_ITE(&seion->rvsctl, (void *) seion->baval, &seion->inval.inte_obid, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_enti_inser_recv(session *seion) {
    OSEVPF("[FUNC]:end_enti_inser_recv\n");
    PARSE_EINSER_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_EINSER_ITE(&seion->rvsctl, (void *) seion->baval, &seion->inval.inte_obid, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_enti_searc_recv(session *seion) {
    OSEVPF("[FUNC]:end_enti_searc_recv\n");
    PARSE_ESEARC_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_ESEARC_ITE(&seion->rvsctl, (void *) seion->baval, &seion->inval.inte_obid, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_enti_invok_recv(session *seion) {
    OSEVPF("[FUNC]:end_enti_invok_recv\n");
    PARSE_EINVOK_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_EINVOK_ITE(&seion->rvsctl, (void *) seion->baval, &seion->inval.inte_obid, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

// END_CONST_SEND_TAB END_QUERY_SEND_TAB

void end_enti_staco_send(session *seion) {
    OSEVPF("[FUNC]:end_enti_staco_send\n");
    // CLOSE_CONST_SE // CLOSE_QUERY_SE
    CLOSE_CONST_STACO_SE(&seion->rvsctl)
}

void end_enti_respo_send(session *seion) {
    OSEVPF("[FUNC]:end_enti_respo_send\n");
    // CLOSE_CONST_SE // CLOSE_QUERY_SE
    CLOSE_CONST_RESPO_SE(&seion->rvsctl)
}



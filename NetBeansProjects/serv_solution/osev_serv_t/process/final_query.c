
#include "chk_privi_bzl.h"
#include "reqin_ite.h"

#include "../session.h"

#include "final_query.h"

// END_QUERY_RECV_TAB

void end_quer_post_recv(session *seion) {
    OSEVPF("[FUNC]:end_quer_post_recv\n");
    PARSE_QPOST_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    CHECK_LEVQUP_PRIVILE(&seion->rvsctl, seion->apval, seion->baval, &seion->inval.pamvs, &qpost_privi)
            //
    if (HAND_QPOST_ITE(&seion->rvsctl, (void *) seion->baval, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

//

void end_quer_statu_echo_recv(session *seion) {
    OSEVPF("[FUNC]:end_quer_statu_echo_recv\n");
    PARSE_QSTATU_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    CHECK_LEVQUE_STAEHO_PRIVILE(&seion->rvsctl, seion->apval, seion->baval, &seion->inval.pamvs, &qecho_privi)
            //
    if (HAND_QSTATU_ECHO_ITE(&seion->rvsctl, (void *) seion->baval, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

/*
void end_quer_echo_name_recv(session *seion) {
    OSEVPF("[FUNC]:end_quer_echo_name_recv\n");
    PARSE_QSTATU_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    CHECK_LEVQUE_STAEHO_PRIVILE(&seion->rvsctl, seion->apval, seion->baval, &seion->inval.pamvs, &qecho_privi)
            //
    if (HAND_QSTATU_NAME_ITE(&seion->rvsctl, (void *) seion->baval, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}
*/

void end_quer_statu_attri_recv(session *seion) {
    OSEVPF("[FUNC]:end_quer_echo_recv\n");
    PARSE_QSTATU_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    OSEVPF("1 pamvu->pamcon[0x00]:|%d|\n", *((uint32 *) seion->inval.pamvs.pamcon[0x00]));
    OSEVPF("1 pamvu->pamcon[0x01]:|%s|\n", seion->inval.pamvs.pamcon[0x01]);
    CHECK_LEVQUE_ATTSTA_PRIVILE(&seion->rvsctl, seion->apval, seion->baval, &seion->inval.pamvs, &qecho_privi)
            //
    if (HAND_QSTATU_ATTRI_ITE(&seion->rvsctl, (void *) seion->baval, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
    OSEVPF("2 pamvu->pamcon[0x00]:|%d|\n", *((uint32 *) seion->inval.pamvs.pamcon[0x00]));
    OSEVPF("2 pamvu->pamcon[0x01]:|%s|\n", seion->inval.pamvs.pamcon[0x01]);
}

void end_quer_statu_stati_recv(session *seion) {
    OSEVPF("[FUNC]:end_quer_echo_recv\n");
    PARSE_QSTATU_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    OSEVPF("1 pamvu->pamcon[0x00]:|%d|\n", *((uint32 *) seion->inval.pamvs.pamcon[0x00]));
    OSEVPF("1 pamvu->pamcon[0x01]:|%s|\n", seion->inval.pamvs.pamcon[0x01]);
    CHECK_LEVQUE_ATTSTA_PRIVILE(&seion->rvsctl, seion->apval, seion->baval, &seion->inval.pamvs, &qecho_privi)
            //
    if (HAND_QSTATU_STATI_ITE(&seion->rvsctl, (void *) seion->baval, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
    OSEVPF("2 pamvu->pamcon[0x00]:|%d|\n", *((uint32 *) seion->inval.pamvs.pamcon[0x00]));
    OSEVPF("2 pamvu->pamcon[0x01]:|%s|\n", seion->inval.pamvs.pamcon[0x01]);
}
//

void end_quer_creat_recv(session *seion) {
    OSEVPF("[FUNC]:end_quer_creat_recv\n");
    PARSE_QCREAT_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    CHECK_LEVQUC_PRIVILE(&seion->rvsctl, seion->apval, seion->baval, &seion->inval.pamvs, &qcrea_privi)
            //
    if (HAND_QCREAT_ITE(&seion->rvsctl, (void *) seion->baval, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_quer_drop_recv(session *seion) {
    OSEVPF("[FUNC]:end_quer_drop_recv\n");
    PARSE_QDROP_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    CHECK_LEVQUD_PRIVILE(&seion->rvsctl, seion->apval, seion->baval, &seion->inval.pamvs, &qdrop_privi)
            //
    if (HAND_QDROP_ITE(&seion->rvsctl, (void *) seion->baval, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_quer_updat_recv(session *seion) {
    OSEVPF("[FUNC]:end_quer_updat_recv\n");
    PARSE_QUPDAT_ITE(&seion->inval.pamvs, seion->inval._data_line_, seion->rvsctl.requ_stram);
    CHECK_LEVQUU_PRIVILE(&seion->rvsctl, seion->apval, seion->baval, &seion->inval.pamvs, &qupda_privi)
            //
    if (HAND_QUPDAT_ITE(&seion->rvsctl, (void *) seion->baval, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_quer_inser_recv(session *seion) {
    OSEVPF("[FUNC]:end_quer_inser_recv\n");
    PARSE_QINSER_ITE(&seion->inval.pamvs, seion->inval._data_line_, seion->rvsctl.requ_stram);
    CHECK_LEVQUI_PRIVILE(&seion->rvsctl, seion->apval, seion->baval, &seion->inval.pamvs, &qinse_privi)
            //
    if (HAND_QINSER_ITE(&seion->rvsctl, (void *) seion->baval, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_quer_searc_recv(session *seion) {
    OSEVPF("[FUNC]:end_quer_searc_recv\n");
    PARSE_QSEARC_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    CHECK_LEVQUS_PRIVILE(&seion->rvsctl, seion->apval, seion->baval, &seion->inval.pamvs, &qsear_privi)
            //
    if (HAND_QSEARC_ITE(&seion->rvsctl, (void *) seion->baval, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_quer_invok_recv(session *seion) {
    OSEVPF("[FUNC]:end_quer_invok_recv\n");
    PARSE_QINVOK_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    CHECK_LEVQUV_PRIVILE(&seion->rvsctl, seion->apval, seion->baval, &seion->inval.pamvs, &qinvo_privi)
            //
    if (HAND_QINVOK_ITE(&seion->rvsctl, (void *) seion->baval, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_quer_facto_recv(session *seion) {
    OSEVPF("[FUNC]:end_quer_facto_recv\n");
    PARSE_FACTO_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    CHECK_LEVQUF_PRIVILE(&seion->rvsctl, seion->apval, seion->baval, &seion->inval.pamvs, &qfact_privi)
            //
    if (HAND_QFACTO_ITE(&seion->rvsctl, (void *) seion->baval, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

// END_CONST_SEND_TAB END_QUERY_SEND_TAB

void end_quer_staco_send(session *seion) {
    OSEVPF("[FUNC]:end_quer_staco_send\n");
    // CLOSE_CONST_SE // CLOSE_QUERY_SE
    CLOSE_QUERY_STACO_SE(&seion->rvsctl)
}

void end_quer_reque_send(session *seion) {
    OSEVPF("[FUNC]:end_quer_reque_send\n");
    // CLOSE_CONST_SE // CLOSE_QUERY_SE
    CLOSE_QUERY_REQUE_SE(&seion->rvsctl)
}

void end_quer_respo_send(session *seion) {
    OSEVPF("[FUNC]:end_quer_respo_send\n");
    // CLOSE_CONST_SE // CLOSE_QUERY_SE
    CLOSE_QUERY_RESPO_SE(&seion->rvsctl)
}

void end_quer_quesp_send(session *seion) {
    OSEVPF("[FUNC]:end_quer_quesp_send\n");
    // CLOSE_CONST_SE // CLOSE_QUERY_SE
    CLOSE_QUERY_QUESP_SE(&seion->rvsctl)
}

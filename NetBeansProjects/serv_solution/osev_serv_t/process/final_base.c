
#include "chk_privi_bzl.h"
#include "reqin_ite.h"

#include "../session.h"

#include "final_base.h"
#include "../debug_funct_os.h"

//

void end_bauth_recv(session *seion) {
    OSEVPF("[FUNC]:end_bauth_recv\n");
    PARSE_BAUTHEN_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    PRIN_authen(&seion->inval);
#ifdef NOAUTH
    if (HAND_BNAUTH_ITE(&seion->rvsctl, seion, &seion->inval))
        seion->rvsctl.status_code = INTERNAL_SERVER_ERROR;
#else
    // connect to odb
    if (HAND_BAUTHE_ITE(&seion->rvsctl, seion, &seion->inval.pamvs)) {
        _LOG_WARN("Base authen failed!");
        seion->rvsctl.status_code = UNAUTHORIZED;
    } else {
        OSEVPF("seion->apval:|%p|\n", seion->apval);
        CHECK_BSAUTH_PRIVILE(&seion->rvsctl, seion, BPRIV_AUTHE)
    }
#endif // NOAUTH
}

//

void end_bpost_recv(session *seion) {
    OSEVPF("[FUNC]:end_bpost_recv\n");
    PARSE_BPOST_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_BPOST_ITE(&seion->rvsctl, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

/*
void end_bstat_statu_recv(session *seion) {
    OSEVPF("[FUNC]:end_bstat_statu_recv\n");
    PARSE_BSTAT_STATU_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_BSTAT_STATU_ITE(&seion->rvsctl, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}
*/

//

void end_bcomd_open_recv(session *seion) {
    OSEVPF("[FUNC]:end_bcomd_open_recv\n");
    PARSE_BCOMD_OPEN_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_BCOMD_OPEN_ITE(&seion->rvsctl, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_bcomd_close_recv(session *seion) {
    OSEVPF("[FUNC]:end_bcomd_close_recv\n");
    PARSE_BCOMD_CLOSE_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_BCOMD_CLOSE_ITE(&seion->rvsctl, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

// END_OSEV_RECV_TAB

void end_bstatu_echo_recv(session *seion) {
    OSEVPF("[FUNC]:end_bstatu_echo_recv\n");
    PARSE_BSTAT_ECHO_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_BSTAT_ECHO_ITE(&seion->rvsctl, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_bstat_stati_recv(session *seion) {
    OSEVPF("[FUNC]:end_bstat_stati_recv\n");
    PARSE_BSTAT_STATI_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_BSTAT_STATI_ITE(&seion->rvsctl, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

// END_BASE_RECV_TAB

void end_bpriv_list_recv(session *seion) {
    OSEVPF("[FUNC]:end_bpriv_list_recv\n");
    PARSE_BPRIV_LIST_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_BPRIV_LIST_ITE(&seion->rvsctl, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_bpriv_role_recv(session *seion) {
    OSEVPF("[FUNC]:end_bpriv_role_recv\n");
    PARSE_BPRIV_ROLE_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_BPRIV_ROLE_ITE(&seion->rvsctl, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_bpriv_user_recv(session *seion) {
    OSEVPF("[FUNC]:end_bpriv_user_recv\n");
    PARSE_BPRIV_USER_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_BPRIV_USER_ITE(&seion->rvsctl, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

//

void end_bauth_send(session *seion) {
    OSEVPF("[FUNC]:end_bauth_send\n");
    CLOSE_AUTHEN_SE(&seion->rvsctl);
}

void end_bpost_send(session *seion) {
    OSEVPF("[FUNC]:end_bpost_send\n");
    CLOSE_POST_SE(&seion->rvsctl);
}

//

void end_bcomd_send(session *seion) {
    OSEVPF("[FUNC]:end_bcomd_send\n");
    CLOSE_COMAND_SE(&seion->rvsctl);
}

//

void end_bstatu_send(session *seion) {
    OSEVPF("[FUNC]:end_bstatu_send\n");
    CLOSE_STATUS_SE(&seion->rvsctl);
}

//

void end_bprivi_send(session *seion) {
    OSEVPF("[FUNC]:end_bprivi_send\n");
    CLOSE_PRIVILE_SE(&seion->rvsctl);
}


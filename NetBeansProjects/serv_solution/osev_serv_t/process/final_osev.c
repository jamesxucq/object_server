
#include "chk_privi_bzl.h"
#include "reqin_ite.h"

#include "../session.h"

#include "final_osev.h"
#include "../debug_funct_os.h"

//

void END_INVA_RECV(session *seion) {
    OSEVPF("[FUNC]:END_INVA_RECV\n");
}

void end_oauth_recv(session *seion) {
    OSEVPF("[FUNC]:end_oauth_recv\n");
    PARSE_OAUTHEN_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    PRIN_authen(&seion->inval);
#ifdef NOAUTH
    if (HAND_ONAUTH_ITE(&seion->rvsctl, seion, &seion->inval))
        seion->rvsctl.status_code = INTERNAL_SERVER_ERROR;
#else
    // connect to osev
    if (HAND_OAUTHE_ITE(&seion->rvsctl, seion, &seion->inval.pamvs)) {
        _LOG_WARN("OSEV authen failed!");
        seion->rvsctl.status_code = UNAUTHORIZED;
    } else {
        OSEVPF("seion->apval:|%p|\n", seion->apval);
        CHECK_OSAUTH_PRIVILE(&seion->rvsctl, seion->apval, OPRIV_AUTHE)
    }
#endif // NOAUTH
}

//

void end_opost_recv(session *seion) {
    OSEVPF("[FUNC]:end_opost_recv\n");
    PARSE_OPOST_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_OPOST_ITE(&seion->rvsctl, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

/*
void end_ostat_statu_recv(session *seion) {
    OSEVPF("[FUNC]:end_ostat_statu_recv\n");
    PARSE_OSTAT_STATU_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_OSTAT_STATU_ITE(&seion->rvsctl, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}
*/

//

void end_ocomd_open_recv(session *seion) {
    OSEVPF("[FUNC]:end_ocomd_open_recv\n");
    PARSE_OCOMD_OPEN_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_OCOMD_OPEN_ITE(&seion->rvsctl, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_ocomd_close_recv(session *seion) {
    OSEVPF("[FUNC]:end_ocomd_close_recv\n");
    PARSE_OCOMD_CLOSE_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_OCOMD_CLOSE_ITE(&seion->rvsctl, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

// END_OSEV_RECV_TAB

void end_ostatu_echo_recv(session *seion) {
    OSEVPF("[FUNC]:end_ostatu_echo_recv\n");
    PARSE_OSTAT_ECHO_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_OSTAT_ECHO_ITE(&seion->rvsctl, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_ostat_stati_recv(session *seion) {
    OSEVPF("[FUNC]:end_ostat_stati_recv\n");
    PARSE_OSTAT_STATI_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_OSTAT_STATI_ITE(&seion->rvsctl, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

// END_BASE_RECV_TAB

void end_opriv_list_recv(session *seion) {
    OSEVPF("[FUNC]:end_opriv_list_recv\n");
    PARSE_OPRIV_LIST_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_OPRIV_LIST_ITE(&seion->rvsctl, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_opriv_role_recv(session *seion) {
    OSEVPF("[FUNC]:end_opriv_role_recv\n");
    PARSE_OPRIV_ROLE_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    CHECK_OPRIVRO_PRIVILE(&seion->rvsctl, seion->apval, OPRIV_PRIVI, &seion->inval.pamvs)
            //
    if (HAND_OPRIV_ROLE_ITE(&seion->rvsctl, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

void end_opriv_user_recv(session *seion) {
    OSEVPF("[FUNC]:end_opriv_user_recv\n");
    PARSE_OPRIV_USER_ITE(&seion->inval.pamvs, seion->inval._data_line_, (char *) seion->rvsctl.requ_memo);
    if (HAND_OPRIV_USER_ITE(&seion->rvsctl, &seion->inval.pamvs))
        seion->rvsctl.status_code = BAD_REQUEST;
}

//

void END_INVA_SEND(session *seion) {
    OSEVPF("[FUNC]:END_INVA_SEND\n");
}

void end_oauth_send(session *seion) {
    OSEVPF("[FUNC]:end_oauth_send\n");
    CLOSE_AUTHEN_SE(&seion->rvsctl);
}

//

void end_opost_send(session *seion) {
    OSEVPF("[FUNC]:end_opost_send\n");
    CLOSE_POST_SE(&seion->rvsctl);
}

//

void end_ocomd_send(session *seion) {
    OSEVPF("[FUNC]:end_ocomd_send\n");
    CLOSE_COMAND_SE(&seion->rvsctl);
}

//

void end_ostatu_send(session *seion) {
    OSEVPF("[FUNC]:end_ostatu_send\n");
    CLOSE_STATUS_SE(&seion->rvsctl);
}

//

void end_opriv_send(session *seion) {
    OSEVPF("[FUNC]:end_opriv_send\n");
    CLOSE_PRIVILE_SE(&seion->rvsctl);
}

#include "authen_bzl.h"
#include "chk_privi_bzl.h"
#include "reqin_ite.h"

#include "../session.h"
#include "final_osev.h"
#include "final_base.h"
#include "final_invoke.h"
#include "final_collect.h"
#include "final_constr.h"
#include "final_query.h"


#include "finalize.h"
#include "../debug_funct_os.h"

//

static void end_kaliv_recv(session *seion) {
    OSEVPF("[FUNC]:end_kaliv_recv\n");
}

//

static void end_done_recv(session *seion) {
    OSEVPF("[FUNC]:end_done_recv\n");
    if (erase_auth_cache_end(seion->apval->_action_key_))
        seion->rvsctl.status_code = INTERNAL_SERVER_ERROR;
}

//
void (*requ_finalize_tab[LEVTYP_COUNT][LEVIVK_COUNT])(session*) = {
    END_OSEV_RECV_TAB, // osev
    END_BASE_RECV_TAB, // base
    {end_kaliv_recv}, // kaliv
    END_INVOK_RECV_TAB, // invok
    END_COLLE_RECV_TAB, // colle
    END_CONST_RECV_TAB, // const
    END_QUERY_RECV_TAB, // query
    {end_done_recv} // done
};

//

static void end_kaliv_send(session *seion) {
    OSEVPF("[FUNC]:end_kaliv_send\n");
    CLOSE_KALIVE_SE(&seion->rvsctl);
}

//

static void end_done_send(session *seion) {
    OSEVPF("[FUNC]:end_done_send\n");
    CLOSE_DONE_SE(&seion->rvsctl);
}

//
void (*resp_finalize_tab[LEVTYP_COUNT][LEVIVK_COUNT])(session*) = {
    END_OSEV_SEND_TAB, // osev
    END_BASE_SEND_TAB, // base
    {end_kaliv_send}, // kaliv
    END_INVOK_SEND_TAB, // invok
    END_COLLE_SEND_TAB, // colle
    END_CONST_SEND_TAB, // const
    END_QUERY_SEND_TAB, // query
    {end_done_send} // done
};

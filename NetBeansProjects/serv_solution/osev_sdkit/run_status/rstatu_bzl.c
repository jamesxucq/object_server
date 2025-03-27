#include "commo_header.h"
#include "third_party.h"

#include "kcomm_header.h"
#include "rstri_utili.h"
#include "rstat_utili.h"
#include "conte_bzl.h"
#include "query_bzl.h"
#include "filli_statu.h"
#include "basev_bzl.h"
#include "privile_bzl.h"
#include "rive_bzl.h"
#include "authen_bzl.h"

//
#include "rstatu_obje.h"
#include "rstatu_bzl.h"

int rstabzl_create(char *data_directory) {
    fprintf(stdout, "[FUNC]:rstabzl create start!\n");
    commo_directory_init(data_directory);
    //
    char osevn[OSEV_LENGTH];
    osv_oid_t osev_obid;
    if (PARSE_OATTRI_BZL(osevn, &osev_obid, data_directory)) {
        fprintf(stdout, "Not found osev_attri.sdo!\n");
        if (CREAT_OATTRI_BZL(osevn, &osev_obid, data_directory)) {
            fprintf(stderr, "mkdir:%s error[%d]:%s\n", data_directory, errno, strerror(errno));
            return -1;
        }
    }
    init_osev_name(osevn);
    INIT_OSEV_OBID(&osev_obid);
    //
    fprintf(stdout, "[FUNC]:rstabzl create end!\n");
    return 0x00; //succ
}

int rstabzl_destroy() {
    fprintf(stdout, "[FUNC]:rstabzl destroy start!\n");
    fprintf(stdout, "[FUNC]:rstabzl destroy end!\n");
    return ERR_SUCCESS; //succ
}

// base_obid, authen status

int echo_osev_bzl(respo_ctrl *resctl, char *basen) {
    OSEVPF("[FUNC]:echo_osev_bzl\n");
    OSEVPF("basen:|%s|\n", basen);
    int auth_stat = auth_status_bzl();
    if (basen) {
        osv_oid_t base_obid;
        if (parse_base_attri(&base_obid, basen))
            return -1;
        base_rstat rstatu;
        switch (load_base_rstat(&rstatu, basen)) {
            case 0x01:
                filli_bstat_echo_stopped(resctl, basen, &base_obid, auth_stat);
                break;
            case 0x00:
                filli_bstat_echo_running(resctl, basen, &base_obid, auth_stat, &rstatu);
                break;
            case -1:
                return -1;
                break;
        }
    } else {
        osv_oid_t *osev_obid = GET_OSEV_OBID();
        filli_ostat_echo(resctl, osev_obid, auth_stat);
    }
    //
    return 0x00;
}

// base_obid, authen status, running level

int echo_base_bzl(respo_ctrl *resctl, osv_oid_t *base_obid) {
    OSEVPF("[FUNC]:echo_base_bzl\n");
#ifdef _DEBUG
    char obid_stri[OBJE_IDENTI_ZLEN];
    OSEVPF("base_obid:|%s|\n", oidstr(obid_stri, base_obid));
#endif
    if (!base_obid) return -1;
    int auth_stat = auth_status_bzl();
    //
    char basen[BASE_LENGTH];
    if (find_base_obid(basen, base_obid)) return -1;
    base_rstat rstatu;
    switch (load_base_rstat(&rstatu, basen)) {
        case 0x01:
            filli_bstat_echo_stopped(resctl, basen, base_obid, auth_stat);
            break;
        case 0x00:
            filli_bstat_echo_running(resctl, basen, base_obid, auth_stat, &rstatu);
            break;
        case -1:
            return -1;
            break;
    }
    //
    return 0x00;
}

int ostai_osev_bzl(respo_ctrl *resctl) {
    OSEVPF("[FUNC]:ostai_osev_bzl\n");
    osv_oid_t *osev_obid = GET_OSEV_OBID();
    int auth_stat = auth_status_bzl();
    //
    filli_ostai_osev(resctl, osev_obid, auth_stat);
    return 0x00;
}

//

int ostai_base_bzl(respo_ctrl *resctl) {
    OSEVPF("[FUNC]:ostai_base_bzl\n");
    char *base_array[MAX_BASE_COUNT];
    char _base_line_[LARGE_CONTE_SIZE];
    if (list_base(base_array, _base_line_, _COMMO_DIRECTORY_))
        return -1;
    filli_ostai_base(resctl, base_array);
    //
    return 0x00;
}

int bstai_base_bzl(respo_ctrl *resctl, osv_oid_t *base_obid) {
    OSEVPF("[FUNC]:bstai_base_bzl.\n");
    char basen[BASE_LENGTH];
    if (find_base_obid(basen, base_obid)) return -1;
    filli_bstai_base(resctl, basen, base_obid);
    //
    return 0x00;
}

int quer_stasti_base_bzl(respo_ctrl *resctl, osv_oid_t *base_obid) {
    OSEVPF("[FUNC]:quer_stasti_base_bzl.\n");
    char basen[BASE_LENGTH];
    if (find_base_obid(basen, base_obid)) return -1;
    filli_qstai_base(resctl, basen, base_obid);
    //
    return 0x00;
}

//

int opened_base_bzl(char **base_openp, char *_oline_) {
    fprintf(stdout, "[FUNC]:opened_base_bzl\n");
    char *base_array[MAX_BASE_COUNT];
    char _base_line_[LARGE_CONTE_SIZE];
    if (list_base(base_array, _base_line_, _COMMO_DIRECTORY_))
        return -1;
    //
    char **base_namp = base_array;
    for (; base_namp[0x00]; ++base_namp) {
        OSEVPF("check base:|%s|\n", base_namp[0x00]);
        if (!valid_base_opened(base_namp[0x00])) {
            LSCPY_O(base_openp[0x00], base_namp[0x00], _oline_)
            OSEVPF("base:|%s| opened!\n", base_openp[0x00]);
            base_openp++;
        }
    }
    base_openp[0x00] = NULL;
    // _LOG_TRACE("end opened_base_bzl");
    return 0x00;
}

//

int reset_orlev_bzl(char *basen, uint32 lvmsk_code) {
    OSEVPF("[FUNC]:reset_orlev_bzl\n");
    OSEVPF("basen:|%s| lvmsk_code:%08x\n", basen, lvmsk_code);
    base_valu *baval = FIND_BADATN_BZL(basen);
    if (!baval) return -1;
    if (reset_baspriv_bzl(baval, lvmsk_code))
        return -1;
    if (reset_base_rlev(basen, lvmsk_code))
        return -1;
    //
    return 0x00;
}

// odb:status(SET_RUN_LEVEL, "12p34p");

int reset_brlev_bzl(osv_oid_t *base_obid, uint32 lvmsk_code) {
    OSEVPF("[FUNC]:reset_brlev_bzl\n");
#ifdef _DEBUG
    char obid_stri[OBJE_IDENTI_ZLEN];
    OSEVPF("base_obid:|%s| lvmsk_code:%08x\n", oidstr(obid_stri, base_obid), lvmsk_code);
#endif
    base_valu *baval = FIND_BADATO_BZL(base_obid);
    if (!baval) {
        OSEVPF("ERROR: not found base!\n");
        return -1;
    }
    if (reset_baspriv_bzl(baval, lvmsk_code))
        return -1;
    if (reset_base_rlev(baval->base_name, lvmsk_code))
        return -1;
    //
    return 0x00;
}

//

int init_runpriv_bzl(uint32 *run_level, char *basen) {
    base_rstat rstatu;
    if (load_base_rstat(&rstatu, basen))
        return -1;
    run_level[0x00] = rstatu.running_level;
    //
    return 0x00;
}


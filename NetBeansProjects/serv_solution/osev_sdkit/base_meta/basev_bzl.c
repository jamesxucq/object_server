
#include "commo_header.h"
#include "kcomm_header.h"

#include "rive_bzl.h"
#include "conte_bzl.h"
#include "rstatu_bzl.h"
#include "query_bzl.h"
#include "privile_bzl.h"
#include "base_utili.h"
#include "base_cache.h"
#include "basev_obje.h"

#include "basev_bzl.h"
#include "basev_list.h"

//

static int initi_blist_cache(basv_lsmp *basv_ca, char **base_openp) {
    fprintf(stdout, "[FUNC]:initi_blist_cache\n");
    base_cache_initi(basv_ca);
    //
    basv_list *blsnd;
    for (; base_openp[0x00]; ++base_openp) {
        fprintf(stdout, "-------- |%s| opened.\n", base_openp[0x00]);
        blsnd = creat_basv_list();
        if (!blsnd) return -1;
        strcpy(blsnd->basval.base_name, base_openp[0x00]);
        if (parse_base_attri(&blsnd->basval.base_obid, base_openp[0x00])) {
            fprintf(stdout, "ERROR: |%s| parse_base_attri!\n", base_openp[0x00]);
            destr_basv_list(blsnd);
            continue;
        }
        if (init_runpriv_bzl(&blsnd->basval.lvmsk_code, base_openp[0x00])) {
            fprintf(stdout, "ERROR: |%s| init_runpriv_bzl! lvmsk_code:|%08x|\n", base_openp[0x00], blsnd->basval.lvmsk_code);
            destr_basv_list(blsnd);
            continue;
        }
        //
        base_cache_insert(basv_ca, blsnd);
    }
    //
    return 0x00;
}

//

static int rive_initi_conn(basv_list *blist) {
    basv_list *blsnd = blist;
    for (; blsnd; blsnd = blsnd->next) {
        if (open_rive_bzl(blsnd->basval.rivcon, blsnd->_base_))
            return -1;
        fprintf(stdout, "[FUNC]:rive_initi_conn:%s\n", blsnd->_base_);
    }
    //
    return 0x00;
}

//

int basebzl_create() {
    fprintf(stdout, "[FUNC]:basebzl_create start!\n");
    char *base_opened[MAX_BASE_COUNT];
    char _oline_[LARGE_CONTE_SIZE];
    //
    if (opened_base_bzl(base_opened, _oline_)) {
        fprintf(stderr, "[FUNC]:opened_base_bzl ERROR!\n");
        return ERR_FAULT;
    }
    if (initi_blist_cache(&_base_cache_, base_opened)) {
        fprintf(stderr, "[FUNC]:initi_blist_cache ERROR!\n");
        return ERR_FAULT;
    }
    if (rive_initi_conn(_base_cache_.base_list)) {
        fprintf(stderr, "[FUNC]:rive_initi_conn ERROR!\n");
        return ERR_FAULT;
    }
    if (hload_lv2dat_bzl(_base_cache_.base_list)) {
        fprintf(stderr, "[FUNC]:hload_lv2dat_bzl ERROR!\n");
        return ERR_FAULT;
    }
    if (QLOAD_CONTA_BZL(_base_cache_.base_list)) {
        fprintf(stderr, "[FUNC]:QLOAD_CONTA_BZL ERROR!\n");
        return ERR_FAULT;
    }
    //
    fprintf(stdout, "[FUNC]:basebzl_create end!\n");
    return 0x00;
}

int basebzl_destroy() {
    char *base_opened[MAX_BASE_COUNT];
    char _oline_[LARGE_CONTE_SIZE];
    fprintf(stdout, "[FUNC]:basebzl_destroy strat!\n");
    //
    if (opened_base_bzl(base_opened, _oline_))
        return -1;
    //
    // if (qunlo_conta_bzl(_base_cache_->base_list)) return -1; // fixme: 20161716
    // if (hunlo_odata_bzl(_base_cache_->base_list)) return -1;
    // if (rive_final_conn(_base_cache_->base_list)) return -1;
    // if (final_conta_list(_base_cache_->base_list, base_array)) return -1;
    //
    fprintf(stdout, "[FUNC]:basebzl_destroy end!\n");
    return 0x00;
}

//

basv_list *open_blist_bzl(char *basen, uint32 lvmsk_code) {
    basv_list *blsnd = creat_basv_list();
    if (!blsnd) return NULL;
    strcpy(blsnd->basval.base_name, basen);
    if (parse_base_attri(&blsnd->basval.base_obid, basen)) {
        destr_basv_list(blsnd);
        return NULL;
    }
    blsnd->basval.lvmsk_code = lvmsk_code;
    if (!blsnd->basval.lvmsk_code) {
        destr_basv_list(blsnd);
        return NULL;
    }
    base_cache_insert(&_base_cache_, blsnd);
    //
    return blsnd;
}

//

#define EXCEP_RETU(BLIST, REVAL) { \
    CLOSE_BLIST_BZL(BLIST); \
    return REVAL; \
}

//

int open_osev_bzl(osv_oid_t *base_obid, char *basen, uint32 lvmsk_code) {
    OSEVPF("[FUNC]:open_osev_bzl, basen:%s lvmsk_code:%08x\n", basen, lvmsk_code);
    switch (BASE_EXIST_BZL(basen)) {
        case BASE_OPENED:
            _LOG_WARN("ODB OPENED: %s", basen);
            if (parse_base_attri(base_obid, basen))
                return -1;
            break;
        case BASE_NOEXIS:
            _LOG_WARN("ODB NOT EXISTS, CREATE: %s", basen);
            if (creat_base_conte(basen))
                return -1;
            CREAT_HATTR_BZL(basen)
            CREAT_CATTR_BZL(basen);
        case BASE_EXISTS:
            OSEVPF("ODB EXISTS, OPEN: %s\n", basen);
            basv_list *blsnd = open_blist_bzl(basen, lvmsk_code);
            if (!blsnd) return -1;
#ifndef NOAUTH
            if (load_baspriv_bzl(&blsnd->basval, lvmsk_code))
                EXCEP_RETU(blsnd, -1)
#endif // NOAUTH
                OBID_BINARY_COPY(base_obid, &blsnd->basval.base_obid)
                if (open_rive_bzl(blsnd->basval.rivcon, basen))
                    EXCEP_RETU(blsnd, -1)
                    if (open_lv2dat_bzl(&blsnd->basval, basen))
                        EXCEP_RETU(blsnd, -1)
                        // reset run_level
                        if (OPEN_BASRLEV_BZL(basen, blsnd->basval.lvmsk_code))
                            EXCEP_RETU(blsnd, -1)
                            break;
        default:
            _LOG_WARN("default: exist");
            return -1;
            break;
    }
    //
    return 0x00;
}

//

int close_osev_bzl(char *basen) {
    OSEVPF("[FUNC]:close_osev_bzl:|%s|\n", basen);
    osv_oid_t base_obid;
    //
    basv_list *blsnd = FIND_BLISTN_BZL(basen);
    if (!blsnd) return -1;
    if (CLOSE_BASRLEV_BZL(basen))
        return -1;
    //
    if (close_rive_bzl(blsnd->basval.rivcon))
        return -1;
    if (close_lv2dat_bzl(&blsnd->basval, basen))
        return -1;
    OBID_BINARY_COPY(&base_obid, blsnd->_oid_);
    CLOSE_BLIST_BZL(blsnd);
    //
    if (!valid_base_clean(basen)) {
        _LOG_WARN("odb is clean, drop %s.", basen);
        if (drop_base_conte(basen))
            return -1;
        // drop base privile
        drevk_privi_bzl(&base_obid);
    }
    //
    return 0x00;
}

//

int open_base_bzl(osv_oid_t *base_obid, uint32 lvmsk_code) {
#ifdef _DEBUG
    char obid_stri[33];
    OSEVPF("[FUNC]:open_base_bzl:|%s|\n", oidstr(obid_stri, base_obid));
#endif
    char basen[BASE_LENGTH]; // odb name
    if (find_base_obid(basen, base_obid))
        return -1;
    OSEVPF("[FUNC]:open_osev_bzl, basen:%s lvmsk_code:%08x\n", basen, lvmsk_code);
    //
    switch (BASE_EXIST_BZL(basen)) {
        case BASE_OPENED:
            _LOG_WARN("ODB OPENED: %s", basen);
            break;
        case BASE_NOEXIS:
            _LOG_WARN("ODB %s NOT EXISTS!", basen);
            return -1;
            break;
        case BASE_EXISTS:
            OSEVPF("ODB EXISTS, OPEN: %s\n", basen);
            basv_list *blsnd = open_blist_bzl(basen, lvmsk_code);
            if (!blsnd) return -1;
#ifndef NOAUTH
            if (load_baspriv_bzl(&blsnd->basval, lvmsk_code))
                EXCEP_RETU(blsnd, -1)
#endif // NOAUTH
                OBID_BINARY_COPY(base_obid, &blsnd->basval.base_obid)
                if (open_rive_bzl(blsnd->basval.rivcon, basen))
                    EXCEP_RETU(blsnd, -1)
                    if (open_lv2dat_bzl(&blsnd->basval, basen))
                        EXCEP_RETU(blsnd, -1)
                        // reset run_level
                        if (OPEN_BASRLEV_BZL(basen, blsnd->basval.lvmsk_code))
                            EXCEP_RETU(blsnd, -1)
                            break;
        default:
            _LOG_WARN("default: exist");
            return -1;
            break;
    }
    //
    return 0x00;
}

//

int close_base_bzl(osv_oid_t *base_obid) {
    char basen[BASE_LENGTH];
#ifdef _DEBUG
    char temp[33];
    OSEVPF("[FUNC]:close_base_bzl:|%s|\n", oidstr(temp, base_obid));
#endif
    basv_list *blsnd = FIND_BLISTO_BZL(base_obid);
    if (!blsnd) return -1;
    if (CLOSE_BASRLEV_BZL(blsnd->_base_))
        return -1;
    //
    if (close_rive_bzl(blsnd->basval.rivcon))
        return -1;
    if (close_lv2dat_bzl(&blsnd->basval, blsnd->_base_))
        return -1;
    strcpy(basen, blsnd->_base_);
    CLOSE_BLIST_BZL(blsnd);
    //
    if (!valid_base_clean(basen)) {
        _LOG_WARN("odb is clean, drop %s.", basen);
        if (drop_base_conte(basen))
            return -1;
        // drop base privile
        drevk_privi_bzl(base_obid);
    }
    //
    return 0x00;
}

#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#include "commo_header.h"
#include "kcomm_header.h"
#include "nstri_utili.h"
#include "lv2p_meta.h"

#include "lev1_dlsym.h"

//
#define OPEN_INVOK_SYMB(LVOME, DYHAND, FUNC_NAME) { \
    LVOME->libr_hand = DYHAND->handle; \
    LVOME->method.invoke = dlsym(DYHAND->handle, FUNC_NAME); \
    if (dlerror() != NULL) { \
        _LOG_FATAL("invok get_handlers dlsym: %s", dlerror()); \
        return -1; \
    } \
}

//
#define OPEN_CONST_SYMB(LVOME, DYHAND, FUNC_NAME) { \
    LVOME->libr_hand = DYHAND->handle; \
    LVOME->method.constr = dlsym(DYHAND->handle, FUNC_NAME); \
    if (dlerror() != NULL) { \
        _LOG_FATAL("const get_handlers dlsym: %s", dlerror()); \
        return -1; \
    } \
}

//

int open_meth_hand(lev1me *lv1me, hand_hmap *hando_stm, char *libr_path) {
    // OSEVPF("[FUNC]:open_meth_hand\n");
    // OSEVPF("lv1me->handn:|%s| libr_path:|%s|\n", lv1me->handn, libr_path);
    dyli_hand * dyhand = open_dyhand(&hando_stm->dyha_list, libr_path, lv1me->handn);
    if (!dyhand) return -1;
    // OSEVPF("Open dyhand OK!\n");
    if (lv1me->norma_const) {
        OPEN_INVOK_SYMB(lv1me, dyhand, lv1me->handn)
    } else OPEN_CONST_SYMB(lv1me, dyhand, lv1me->handn);
    // OSEVPF("insert handn:|%s| lv1me:%p lev1n_hm:%p\n", lv1me->handn, lv1me, hando_stm->lev1n_hm);
    return 0x00;
}

//

int open_meth_hand_librn(lev1me *lv1me, hand_hmap *hando_stm, char *libr_path, char *lev1_librn) {
    // OSEVPF("[FUNC]:open_meth_hand_librn, lv2pn:|%s| libr_path:|%s|\n", lv2pn, libr_path);
    dyli_hand * dyhand = open_dyhand(&hando_stm->dyha_list, libr_path, lev1_librn);
    if (!dyhand) return -1;
    // OSEVPF("Open dyhand OK!\n");
    if (lv1me->norma_const) {
        OPEN_INVOK_SYMB(lv1me, dyhand, lv1me->handn)
    } else OPEN_CONST_SYMB(lv1me, dyhand, lv1me->handn);
    // OSEVPF("insert handn:|%s| lv1me:%p lev1n_hm:%p\n", lv1me->handn,  lv1me,  hando_stm->lev1n_hm);
    return 0x00;
}



#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#include "third_party.h"
#include "commo_header.h"
// #include "base_value.h"

#include "lev1_meta.h"
#include "debug_funct_osv.h"

//
#define DYLIST_PREPEND(head, add) { \
    add->next = head; \
    head = add; \
}

#define DYLIST_DELETE(head,del) { \
    LDECLTYPE(head) _tmp; \
    if ((head) == (del)) (head)=(head)->next; \
    else { \
        _tmp = head; \
        while (_tmp->next && (_tmp->next != (del))) _tmp = _tmp->next; \
        if (_tmp->next) _tmp->next = ((del)->next); \
    } \
}

//

static inline dyli_hand *find_dyhand(dyli_hand *dyhand, char *lev1_librn) {
    for (; dyhand; dyhand = dyhand->next) {
        if (!strcmp(lev1_librn, dyhand->lev1_librn))
            break;
    }
    return dyhand;
}

static dyli_hand *appe_dyhand(dyli_hand **dylsth) {
    dyli_hand *dylind = (dyli_hand *) malloc(sizeof (dyli_hand));
    if (!dylind) return NULL;
    memset(dylind, '\0', sizeof (dyli_hand));
    DYLIST_PREPEND(*dylsth, dylind);
    //
    return dylind;
}

static inline void deco_dyhand(dyli_hand **dylsth, dyli_hand *dyhand) {
    DYLIST_DELETE(*dylsth, dyhand)
    if (dyhand->handle) dlclose(dyhand->handle);
    FREE_DYHAND(dyhand)
}

dyli_hand *open_dyhand(dyli_hand **dylsth, char *libr_path, char *lev1_librn) {
    // OSEVPF("[FUNC]:open_dyhand, lev1_librn:|%s| libr_path:|%s|\n", lev1_librn, libr_path);
    dyli_hand *dyhand = find_dyhand(*dylsth, lev1_librn);
    if (dyhand) {
        // OSEVPF("open_dyhand found. dyhand->refer_inde:%d\n", dyhand->refer_inde);
        dyhand->refer_inde++;
        return dyhand;
    }
    dyhand = appe_dyhand(dylsth);
    if (dyhand) {
        dyhand->handle = dlopen(libr_path, RTLD_LAZY);
        if (!dyhand->handle) {
            deco_dyhand(dylsth, dyhand);
            _LOG_ERROR("dlerror:|%s| libr_path:%s", dlerror(), libr_path);
            return NULL;
        }
        strcpy(dyhand->lev1_librn, lev1_librn);
        dyhand->refer_inde++;
        // OSEVPF("OK! not found, open libr_path:|%s|\n", libr_path);
    }
    //    
    return dyhand;
}

// 0x00:hand refer zero. >0x00:refer number <0x00:error

int close_dyhand(OUT char *lev1_librn, dyli_hand **dylsth, void *libr_hand) {
    dyli_hand *dylind = *dylsth;
    for (; dylind; dylind = dylind->next) {
        if (libr_hand == dylind->handle) {
            if (lev1_librn) strcpy(lev1_librn, dylind->lev1_librn);
            dylind->refer_inde--;
            if (!dylind->refer_inde) {
                DYLIST_DELETE(*dylsth, dylind)
                        // OSEVPF("close_dyhand, refer_inde:%d lev1_librn:|%s|\n", dylind->refer_inde, dylind->lev1_librn);
                if (dylind->handle) dlclose(dylind->handle);
                FREE_DYHAND(dylind)
                return 0x00;
            }
            break;
        }
    }
    // OSEVPF("close_dyhand, refer_inde:%d lev1_librn:|%s|\n", dylind->refer_inde, dylind->lev1_librn);
    return dylind->refer_inde;
}

//

void dele_dyhand(dyli_hand *dyhand) {
    dyli_hand *dylind;
    while (dyhand) {
        dylind = dyhand;
        dyhand = dyhand->next;
        if (dylind->handle) dlclose(dylind->handle);
        free(dylind);
    }
}

//


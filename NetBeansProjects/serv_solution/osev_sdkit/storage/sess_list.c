
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "rive_bzl.h"

#include "sess_list.h"

//

stor_seio *activ_seion(seio_list **seio_lsth, rive_ha *stora_ha, riv_conne_t *conne) {
    OSEVPF("[FUNC]:activ_seion \n");
#ifdef _DEBUG
    int reth;
#endif
    stor_seio *sto_seio = NULL;
    //
    if (seio_lsth[0x00]) {
        OSEVPF("get sto_seio\n");
        sto_seio = seio_lsth[0x00];
        seio_lsth[0x00] = sto_seio->next;
#ifdef _DEBUG
        if ((reth = stora_ha->reset_sessi(sto_seio->seion))) {
            OSEVPF("reset_sessi, reth:%d, strerror(reth):|%s|\n", reth, wiredtiger_strerror(reth));
            if ((reth = stora_ha->close_sessi(sto_seio->seion))) {
                OSEVPF("close_sessi, reth:%d, strerror(reth):|%s|\n", reth, wiredtiger_strerror(reth));
                sto_seio->next = seio_lsth[0x00];
                seio_lsth[0x00] = sto_seio;
                // OSEVPF("alloc sto_seio\n");
                sto_seio = (stor_seio *) malloc(sizeof (stor_seio));
                if (!sto_seio) return NULL;
                if ((reth = stora_ha->open_sessi(conne, &sto_seio->seion))) {
                    OSEVPF("open_sessi, reth:%d, strerror(reth):|%s|\n", reth, wiredtiger_strerror(reth));
                    free(sto_seio);
                    return NULL;
                }
            } else {
                if ((reth = stora_ha->open_sessi(conne, &sto_seio->seion))) {
                    OSEVPF("open_sessi, reth:%d, strerror(reth):|%s|\n", reth, wiredtiger_strerror(reth));
                    free(sto_seio);
                    return NULL;
                }
            }
        }
#else 
        if (stora_ha->reset_sessi(sto_seio->seion)) {
            if (stora_ha->close_sessi(sto_seio->seion)) {
                sto_seio->next = seio_lsth[0x00];
                seio_lsth[0x00] = sto_seio;
                // OSEVPF("alloc sto_seio\n");
                sto_seio = (stor_seio *) malloc(sizeof (stor_seio));
                if (!sto_seio) return NULL;
                if (stora_ha->open_sessi(conne, &sto_seio->seion)) {
                    free(sto_seio);
                    return NULL;
                }
            } else {
                if (stora_ha->open_sessi(conne, &sto_seio->seion)) {
                    free(sto_seio);
                    return NULL;
                }
            }
        }
#endif
    } else {
        OSEVPF("alloc sto_seio\n");
        sto_seio = (stor_seio *) malloc(sizeof (stor_seio));
        if (!sto_seio) return NULL;
#ifdef _DEBUG
        if ((reth = stora_ha->open_sessi(conne, &sto_seio->seion))) {
            OSEVPF("open_sessi, reth:%d, strerror(reth):|%s|\n", reth, wiredtiger_strerror(reth));
            free(sto_seio);
            return NULL;
        }
#else 
        if (stora_ha->open_sessi(conne, &sto_seio->seion)) {
            free(sto_seio);
            return NULL;
        }
#endif
    }
    OSEVPF("end activ_seion\n");
    return sto_seio;
}

//

void quiet_seion(seio_list **seio_lsth, stor_seio *sto_seio) {
    OSEVPF("[FUNC]:quiet_seion \n");
    sto_seio->next = seio_lsth[0x00];
    seio_lsth[0x00] = sto_seio;
}

//

void destroy_seion(seio_list *selist, rive_ha *stora_ha) {
    OSEVPF("[FUNC]:destroy_seion \n");
    for (; selist; selist = selist->next) {
        stora_ha->close_sessi(selist->seion);
    }
}
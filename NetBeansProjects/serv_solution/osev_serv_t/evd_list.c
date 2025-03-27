#include "event.h"
#include "evd_list.h"

int init_evd_list(evd_list *elist, event_data *evds, int events_tatol) {
    levd_list *elsnd;
    if (!elist || !evds) return ERR_FAULT;
    memset(elist, '\0', sizeof (evd_list));
    //
    unsigned int inde = 0x00;
    for (; inde < events_tatol; ++inde) {
        elsnd = (levd_list *) malloc(sizeof (levd_list));
        if (!elsnd) {
            _LOG_WARN("new elist item failed");
            return ERR_FAULT;
        }
        memset(elsnd, '\0', sizeof (levd_list));
        elsnd->evd = &evds[inde];
        CDL_APPEND(elist->sleep, elsnd);
    }
    //
    return ERR_SUCCESS;
}

levd_list *get_levd_list(evd_list *elist) {
    levd_list *elsnd = elist->sleep;
    //
    if (!elist->sleep) return NULL;
    CDL_DELETE(elist->sleep, elsnd);
    CDL_APPEND(elist->active, elsnd);
    if (!elist->chkpos)
        elist->chkpos = elist->active;
    //
    return elsnd;
}

levd_list *set_levd_list(evd_list *elist, event_data *evd) {
    levd_list *elsnd;
    //
    if (!elist->active) return NULL;
    // for(el=head; el; el=(el->next==head?0L:el->next)) 
    CDL_FOREACH(elist->active, elsnd)
    if (elsnd->evd == evd) break;
    if (!elsnd) return NULL;
    //
    if (elsnd == elist->chkpos) {
        if (elsnd->next == elsnd) elist->chkpos = NULL;
        else elist->chkpos = elsnd->next;
    }
    CDL_DELETE(elist->active, elsnd);
    CDL_APPEND(elist->sleep, elsnd);
    //
    return elsnd;
}

void dele_evd_list(evd_list *elist) {
    //
}

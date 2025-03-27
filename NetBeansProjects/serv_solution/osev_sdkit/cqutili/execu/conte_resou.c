
#include "commo_header.h"
#include "kcomm_header.h"

#include "rive_bzl.h"
#include "cqutili.h"
#include "data_compa/data_compa.h"

#include "conte_resou.h"

//
// cursa operation

int hand_open_conte_ensi(physi_conte *phys_cont, rive_conne *rivcon, rive_ha *stora_ha) {
    if (!phys_cont->initi) {
        phys_cont->sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
        if (!phys_cont->sto_seio) return -1;
        phys_cont->initi = 0x01;
    }
    //
    return 0x00;
}

int hand_open_conte_enco(physi_conte *phys_cont, rive_conne *rivcon, rive_ha *stora_ha) {
    if (!phys_cont->initi) {
        phys_cont->sto_seio = ACTIV_SESSION_BZL(rivcon, stora_ha);
        if (!phys_cont->sto_seio) return -1;
        phys_cont->initi = 0x01;
    }
    //
    return 0x00;
}

int hand_close_conte_ensi(physi_conte *phys_cont, rive_conne *rivcon, rive_ha *stora_ha) {
    if (phys_cont->initi) {
        QUIET_SESSION_BZL(rivcon, stora_ha, phys_cont->sto_seio);
        phys_cont->initi = 0x00;
    }
    //
    return 0x00;
}

//

int hand_close_conte_enco(physi_conte *phys_cont, rive_conne *rivcon, rive_ha *stora_ha) {
    if (phys_cont->initi) {
        QUIET_SESSION_BZL(rivcon, stora_ha, phys_cont->sto_seio);
        phys_cont->initi = 0x00;
    }
    //
    return 0x00;
}



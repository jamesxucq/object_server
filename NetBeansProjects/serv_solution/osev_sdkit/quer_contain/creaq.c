
#include "commo_header.h"
#include "kcomm_header.h"

#include "basev_bzl.h"
#include "invok_bzl.h"
#include "conattr.h"

#include "qstri_utili.h"
#include "creaq.h"


//
#define QPAM_CREA_CONTN     0x00
#define QPAM_CREA_ENGIN     0x01
#define QPAM_CREA_LVTYP     0x02

// odb-lv4p> witi:witi("test_con", "test");
// pamvu->pamcon[QPAM_CREA_CONTN]
// pamvp[QPAM_CREA_CONTN]
// *((uint32 *) pamvp[QPAM_CREA_ENGIN])

int creat_qcont_normal(base_valu *baval, char **pamvp) {
    OSEVPF("[FUNC]:creat_qcont_normal\n");
    lv2pme *lv2me = (lv2pme *) cache_value(pamvp[QPAM_CREA_LVTYP], baval->lv2pm_stm.lv2pmn_hm);
    if (!lv2me) return -1;
    //
    char lv2p_prop[LVTNOD_COUNT][PARAM_LENGTH];
    char forma_types[TYPES_LENGTH];
    OSEVPF("base:|%s| contn:|%s| clas_type:|%s|\n", baval->base_name, pamvp[QPAM_CREA_CONTN], lv2me->lv2pn);
    if (split_cprop_bzl(lv2p_prop, baval->base_name, lv2me->lv2pn)) {
        _LOG_INFO("Can not find class!");
        return -1;
    }
    if (conve_conta_types(forma_types, lv2p_prop))
        return -1;
    OSEVPF("forma_types:|%s|\n", forma_types);
    //
    rive_ha *stora_ha = GET_STORAHA_BZL(*((uint32 *) pamvp[QPAM_CREA_ENGIN]));
    stor_seio *sto_seio = ACTIV_SESSION_BZL(baval->rivcon, stora_ha);
    if (!sto_seio) return -1;
    //
    if (stora_ha->creat_contai(sto_seio->seion, pamvp[QPAM_CREA_CONTN], forma_types)) {
        QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
        return -1;
    }
    QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
    _LOG_DEBUG("Creat contain %s OK!", pamvp[QPAM_CREA_CONTN]);
    if (addi_cont_atti(pamvp[QPAM_CREA_CONTN], &lv2me->lv2p_obid, *((uint32 *) pamvp[QPAM_CREA_ENGIN]), baval->base_name))
        return -1;
    OSEVPF("Addi cattr OK!\n");
    //
    return 0x00;
}

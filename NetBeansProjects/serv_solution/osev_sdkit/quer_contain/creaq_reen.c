
#include "commo_header.h"
#include "kcomm_header.h"

#include "basev_bzl.h"
#include "invok_bzl.h"
#include "conattr.h"

#include "creaq_utili/creaq_utili.h"
#include "qstri_utili.h"
#include "creaq_reen.h"

//
// odb-lv4p> witi:witi("test_rsc", "txxt", RSCON_ONE);
// odb-lv4p> witi:witi("test_rsc", "txxt", RSCON_TWO);
// odb-lv4p> witi:witi("test_rsc", "txxt", RSCON_THREE);
// odb-lv4p> witi:witi("test_rsc", "txxt", RSCON_FOUR);
// odb-lv4p> witi:witi("test_rdc", "txxt", "scon1, scon2");
// odb-lv4p> witi:witi("test_rdc", "txxt", "scon1, scon2", "xxx=0x00");

// pamvp[0x00]  char *cont_name
// *((uint32 *) pamvp[0x03])  uint32 refe_coun
// *((uint32 *) pamvp[0x01])  uint32 stora_type
// pamvp[0x02]  char *clas_type

#define QPAM_CREA_CONTN     0x00
#define QPAM_CREA_ENGIN     0x01
#define QPAM_CREA_LVTYP     0x02
#define QPAM_CREA_RCOUN     0x03
#define QPAM_CREA_RCONT     0x03
#define QPAM_CREA_CONDIT    0x04

int creat_qcont_static_reen(base_valu *baval, char **pamvp) {
    OSEVPF("[FUNC]:creat_qcont_static_reen\n");
    if (MAX_SCONT_COUNT < *((uint32 *) pamvp[QPAM_CREA_RCOUN]))
        return -1;
    lv2pme *lv2me = (lv2pme *) cache_value(pamvp[QPAM_CREA_LVTYP], baval->lv2pm_stm.lv2pmn_hm);
    if (!lv2me) return -1;
    //
    char forma_types[TYPES_LENGTH];
    OSEVPF("base:|%s| contn:|%s| clas_type:|%s|\n", baval->base_name, pamvp[QPAM_CREA_CONTN], lv2me->lv2pn);
    if (!stati_rcont_types(forma_types, *((uint32 *) pamvp[QPAM_CREA_RCOUN])))
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
    if (addi_rscont_atti(pamvp[QPAM_CREA_CONTN], &lv2me->lv2p_obid, *((uint32 *) pamvp[QPAM_CREA_RCOUN]), *((uint32 *) pamvp[QPAM_CREA_ENGIN]), baval->base_name))
        return -1;
    OSEVPF("Addi cattr OK!\n");
    //
    return 0x00;
}

// -1:error 0x00:ok 0x01:exception

int creat_qcont_dynamic_reen(base_valu *baval, char **pamvp, unsigned char creat_conditype) {
    OSEVPF("[FUNC]:creat_qcont_dynamic_reen\n");
    uint32 rcoun;
    osv_oid_t refe_cont[MAX_RDCON_COUNT];
    unsigned int cont_type;
    rcoun = parse_refere_contn(refe_cont, &cont_type, &(baval->conda_stm), pamvp[QPAM_CREA_RCONT]);
    if (!rcoun || (REFER_CONTA_TYPE & cont_type))
        return -1;
    // OSEVPF("rcoun:|%u| cont_type:|%u|\n", rcoun, cont_type);
    lv2pme *lv2me = (lv2pme *) cache_value(pamvp[QPAM_CREA_LVTYP], baval->lv2pm_stm.lv2pmn_hm);
    if (!lv2me) return -1;
    //
    char forma_types[TYPES_LENGTH];
    OSEVPF("base:|%s| contn:|%s| clas_type:|%s|\n", baval->base_name, pamvp[QPAM_CREA_CONTN], lv2me->lv2pn);
    if (!dynam_rcont_types(forma_types, rcoun))
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
    //
    uint32 conditype = build_condit_type(pamvp[QPAM_CREA_CONDIT], creat_conditype);
    if (INVA_UINT_VALU == conditype)
        return -1;
    if (addi_rdcont_atti(pamvp[QPAM_CREA_CONTN], &lv2me->lv2p_obid, rcoun, refe_cont, conditype, pamvp[QPAM_CREA_CONDIT], *((uint32 *) pamvp[QPAM_CREA_ENGIN]), baval->base_name))
        return -1;
    OSEVPF("Addi cattr OK!\n");
    //
    return 0x00;
}


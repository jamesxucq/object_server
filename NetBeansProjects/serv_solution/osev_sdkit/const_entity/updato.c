
#include <ctype.h>

#include "third_party.h"
#include "commo_header.h"
#include "kcomm_header.h"
#include "lv2p_meta.h"

#include "updato.h"
//
/*
 #pragma pack(1) 
struct _test_ { 
osv_oid_t obje_obid; 
int xx; 
int ax; 
int cx; 
};
#pragma pack() 
 */

//
#define EPAM_UPDAT_VALUE     0x00

int updat_const_entit(riv_curso_t *dcurso, rive_ha *stora_ha, lv2pme *lv2me, pams_valu *pamvu) {
    OSEVPF("[FUNC]:updat_const_entit\n");
    OSEVPF("cuo lv2pn:|%s| lv2me:%p\n", lv2me->lv2pn, lv2me);
    PK_PACK_STREAM *pkps;
    if (paki_stream_open(lv2me->lv2p_fmtsd_tm, (void *) pamvu->pamcon[EPAM_UPDAT_VALUE], pamvu->req_len[EPAM_UPDAT_VALUE], &pkps))
        return -1;
    OSEVPF("lv2me->lv2p_fmtsd:|%s| pamvu->req_len[EPAM_UPDAT_VALUE]:%llu\n", lv2me->lv2p_fmtsd_tm, pamvu->req_len[EPAM_UPDAT_VALUE]);
    osv_oid_t *exis_obid;
    PK_ITEM key, valu;
    if (paki_unpack_entit(pkps, &exis_obid, &valu)) {
        paki_stream_close(pkps, NULL);
        OSEVPF("paki_unpack_entit error!\n");
        return -1;
    }
    char temp[33];
    printf("obid:|%s|\n", oidstr(temp, exis_obid));
    printf("uniq:|%s|\n", unistr(temp, &INSTAN_UNIQUE));
    printf("valu.size:|%lu|\n", valu.size);
    if (INSTAN_UNIQUE != exis_obid->osev_unique) {
        paki_stream_close(pkps, NULL);
        OSEVPF("INSTAN_UNIQUE error!\n");
        return -1;
    }
    //
    key.data = &((osv_oid_i *) exis_obid)->stoid;
    key.size = sizeof (unsigned long long);
    stora_ha->set_key(dcurso, &key);
    stora_ha->set_value(dcurso, &valu);
    OSEVPF("a error!\n");
    int updat_valu = stora_ha->update_curso(dcurso);
    //
    OSEVPF("b updat_valu:|%d|\n", updat_valu);
    paki_stream_close(pkps, NULL);
    return updat_valu;
}
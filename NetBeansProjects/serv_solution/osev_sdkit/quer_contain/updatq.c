
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_header.h"

#include "updatq.h"

//

static long long updat_qcont_entit(riv_curso_t *dcurso, rive_ha *stora_ha, lv2pme *lv2me, unsigned char *updat_binary, unsigned long long updat_size) {
    // OSEVPF("[FUNC]:updat_qcont_entit\n");
    // OSEVPF("cuo lv2pn:|%s| lv2me:%p\n", lv2me->lv2pn, lv2me);
    if (!updat_binary) return -1;
    PK_PACK_STREAM *pkps;
    if (paki_stream_open(lv2me->lv2p_fmtsd_tm, (void *) updat_binary, updat_size, &pkps))
        return -1;
    //
    long long updat_valu = -1;
    osv_oid_t *exis_obid;
    PK_ITEM key, valu;
    key.size = sizeof (unsigned long long);
    while (!paki_unpack_entit(pkps, &exis_obid, &valu)) {
        if (INSTAN_UNIQUE != exis_obid->osev_unique) {
            paki_stream_close(pkps, NULL);
            return -1;
        }
        key.data = &((osv_oid_i *) exis_obid)->stoid;
        stora_ha->set_key(dcurso, &key);
        stora_ha->set_value(dcurso, &valu);
        updat_valu = stora_ha->update_curso(dcurso);
        if (updat_valu) break;
        paki_stream_reset(pkps, RESET_STREAM_FORMAT);
    }
    if (!updat_valu) updat_valu = updat_size - paki_stream_leng(pkps);
    //
    paki_stream_close(pkps, NULL);
    return updat_valu;
}

//
#define QPAM_UPDAT_CONTA     0x00
#define QPAM_UPDAT_VALUE     0x01

int updat_qcont_conta(base_valu *baval, contain *dcont, pams_valu *pamvu) {
    OSEVPF("updat_qcont_conta\n");
    lv2pme *lv2me = (lv2pme *) cache_value(&dcont->lv2p_type, baval->lv2pm_stm.lv2pmo_hm);
    if (!lv2me) {
        OSEVPF("fdd lv2me:%p lv2pm:%p\n", lv2me, &baval->lv2pm_stm);
        return -1;
    }
    //
    rive_ha *stora_ha = dcont->stora_ha;
    riv_curso_t *dcurso;
    stor_seio *sto_seio = ACTIV_SESSION_BZL(baval->rivcon, stora_ha);
    if (!sto_seio) return -1;
    // OSEVPF("dcont->cont_name:|%s|\n", dcont->cont_name);
    if (stora_ha->open_curso_cont(&dcurso, sto_seio->seion, dcont->cont_name, "raw")) {
        QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
        return -1;
    }
    //
    unsigned long long enti_data = *((unsigned long long *) (pamvu->pamcon[QPAM_UPDAT_VALUE]));
    unsigned long long enti_size = pamvu->req_len[QPAM_UPDAT_VALUE];
    pmmap64 *mmap = pmmap_file64(pamvu->pamstem, enti_data + enti_size, MAX_MAP_SIZE, CHKS_CHUNK);
    if (!mmap) {
        stora_ha->close_curso(dcurso);
        QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
        return -1;
    }
    int updaq_valu = 0x00;
    unsigned long long remain;
    unsigned long long posi = enti_data;
    if (CHKS_CHUNK < remain) {
        remain = enti_data + enti_size - CHKS_CHUNK;
        for (; remain >= posi; posi += (CHKS_CHUNK - updaq_valu)) {
            updaq_valu = updat_qcont_entit(dcurso, stora_ha, lv2me, pmmap_ptr64(mmap, posi, CHKS_CHUNK), CHKS_CHUNK);
            if (0x00 > updaq_valu) {
                unpmmap_file64(mmap);
                stora_ha->close_curso(dcurso);
                QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
                return -1;
            }
        }
        //
        remain = enti_data + enti_size - posi;
    } else remain = enti_size;
    if (remain > 0x00)
        updaq_valu = updat_qcont_entit(dcurso, stora_ha, lv2me, pmmap_ptr64(mmap, posi, remain), remain);
    //
    unpmmap_file64(mmap);
    stora_ha->close_curso(dcurso);
    QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
    //
    return updaq_valu;
}
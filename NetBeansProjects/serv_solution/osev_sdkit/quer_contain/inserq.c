
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_header.h"

#include "inserq.h"

//

/*
void print_test(unsigned char *inser_binary, unsigned long long inser_size) {
    OSEVPF("[FUNC]:print_test\n");
    OSEVPF("--------------\n");
    PK_PACK_STREAM *pkps;
    if (paki_stream_open("oiii", (void *) inser_binary, inser_size, &pkps))
        return;
    //
    osv_oid_t *obid;
    paki_unpack_obid(pkps, &obid);
    char obid_stri[33];
    OSEVPF("obid_stri:|%s|\n", oidstr(obid_stri, obid));
    int tint;
    paki_unpack_int32(pkps, &tint);
    OSEVPF("paki_unpack_int32:%d\n", tint);
    paki_unpack_int32(pkps, &tint);
    OSEVPF("paki_unpack_int32:%d\n", tint);
    paki_unpack_int32(pkps, &tint);
    OSEVPF("paki_unpack_int32:%d\n", tint);
    //
    paki_stream_close(pkps, NULL);
    OSEVPF("--------------\n");
}
 */

static long long inser_qcont_entit(respo_ctrl *resctl, riv_curso_t *dcurso, rive_ha *stora_ha, lv2pme *lv2me, unsigned char *inser_binary, unsigned long long inser_size) {
    // OSEVPF("[FUNC]:inser_qcont_entit\n");
    // OSEVPF("cuo lv2pn:|%s| lv2me:%p lv2me->lv2p_fmtsd_tm:|%s|\n", lv2me->lv2pn, lv2me, lv2me->lv2p_fmtsd_tm);
    if (!inser_binary) return -1;
    // OSEVPF("inser_size:%llu\n", inser_size);
    PK_PACK_STREAM *pkps;
    if (paki_stream_open(lv2me->lv2p_fmtsd_tm, (void *) inser_binary, inser_size, &pkps))
        return -1;
    //
    long long inser_valu = -1;
    osv_oid_t *exis_obid;
    PK_ITEM new_key, valu;
    while (!paki_unpack_entit(pkps, &exis_obid, &valu)) {
        if (INSTAN_UNIQUE == exis_obid->osev_unique) {
            paki_stream_close(pkps, NULL);
            return -1;
        }
        osv_oid_t inse_obid;
        creat_objec_obid((osv_oid_t *) & inse_obid);
        new_key.data = &(((osv_oid_i *) & inse_obid)->stoid);
        new_key.size = sizeof (unsigned long long);
        //
        stora_ha->set_key(dcurso, &new_key);
        stora_ha->set_value(dcurso, &valu);
        inser_valu = stora_ha->inser_curso(dcurso);
        if (inser_valu) break;
        // FDAT_PRODUCE_PCAT
        OBID_LASTBIN_COPY(resctl->posi_resp, & inse_obid);
        OBID_LASTBIN_COPY(resctl->posi_resp, ((osv_oid_i *) exis_obid));
        //
        paki_stream_reset(pkps, RESET_STREAM_FORMAT);
    }
    if (!inser_valu)
        inser_valu = inser_size - paki_stream_leng(pkps);
    //
    paki_stream_close(pkps, NULL);
    return inser_valu;
}

//
#define QPAM_INSER_CONTA     0x00
#define QPAM_INSER_VALUE     0x01

int inser_qcont_conta(respo_ctrl *resctl, base_valu *baval, contain *dcont, pams_valu *pamvu) {
    OSEVPF("inser_qcont_conta\n");
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
    unsigned long long enti_data = *((unsigned long long *) (pamvu->pamcon[QPAM_INSER_VALUE]));
    unsigned long long enti_size = pamvu->req_len[QPAM_INSER_VALUE];
    pmmap64 *mmap = pmmap_file64(pamvu->pamstem, enti_data + enti_size, MAX_MAP_SIZE, CHKS_CHUNK);
    if (!mmap) {
        stora_ha->close_curso(dcurso);
        QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
        return -1;
    }
    FDAT_PRODUCE_INITI(resctl)
            int inser_valu = 0x00;
    unsigned long long remain;
    unsigned long long posi = enti_data;
    if (CHKS_CHUNK < enti_size) {
        remain = enti_data + enti_size - CHKS_CHUNK;
        for (; remain >= posi; posi += (CHKS_CHUNK - inser_valu)) {
            inser_valu = inser_qcont_entit(resctl, dcurso, stora_ha, lv2me, pmmap_ptr64(mmap, posi, CHKS_CHUNK), CHKS_CHUNK);
            if (0x00 > inser_valu) {
                unpmmap_file64(mmap);
                stora_ha->close_curso(dcurso);
                QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
                return -1;
            }
            FDAT_PRODUCE_FCAT(resctl, mmap, dcurso, baval, stora_ha, sto_seio)
        }
        //
        remain = enti_data + enti_size - posi;
    } else remain = enti_size;
    if (remain > 0x00) {
        inser_valu = inser_qcont_entit(resctl, dcurso, stora_ha, lv2me, pmmap_ptr64(mmap, posi, remain), remain);
        if (0x00 > inser_valu) {
            unpmmap_file64(mmap);
            stora_ha->close_curso(dcurso);
            QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
            return -1;
        }
        FDAT_PRODUCE_FCAT(resctl, mmap, dcurso, baval, stora_ha, sto_seio)
    }
    FDAT_PRODUCE_FINAL(resctl)
    //
    unpmmap_file64(mmap);
    stora_ha->close_curso(dcurso);
    QUIET_SESSION_BZL(baval->rivcon, stora_ha, sto_seio);
    //
    return inser_valu;
}


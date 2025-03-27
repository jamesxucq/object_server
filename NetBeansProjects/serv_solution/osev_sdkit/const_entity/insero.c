
#include <ctype.h>

#include "third_party.h"
#include "commo_header.h"
#include "kcomm_header.h"
#include "insero.h"
#include "lev1_decla.h"
#include "lv2p_decla.h"
#include "lv2p_meta.h"

//
#define OBID_KEYVAL_COUP 0x02
#define EPAM_INSER_VALUE     0x00

int inser_const_entit(respo_ctrl *resctl, riv_curso_t *dcurso, rive_ha *stora_ha, lv2pme *lv2me, pams_valu *pamvu) {
    OSEVPF("cuo lv2pn:|%s| lv2pm_stm:%p\n", lv2me->lv2pn, lv2me);
    PK_PACK_STREAM *pkps;
    if (paki_stream_open(lv2me->lv2p_fmtsd_tm, (void *) pamvu->pamcon[EPAM_INSER_VALUE], pamvu->req_len[EPAM_INSER_VALUE], &pkps))
        return -1;
    // OSEVPF("lv2me->lv2p_fmtsd:|%s| pamvu->req_len[EPAM_INSER_VALUE]:%llu\n", lv2me->lv2p_fmtsd_tm, pamvu->req_len[EPAM_INSER_VALUE]);
    osv_oid_t *exis_obid;
    PK_ITEM new_key, valu;
    if (paki_unpack_entit(pkps, &exis_obid, &valu)) {
        paki_stream_close(pkps, NULL);
        OSEVPF("paki_unpack_entit error!\n");
        return -1;
    }
    if (INSTAN_UNIQUE == exis_obid->osev_unique) {
        paki_stream_close(pkps, NULL);
        OSEVPF("INSTAN_UNIQUE error!\n");
        return -1;
    }
    osv_oid_t inse_obid;
    creat_objec_obid((osv_oid_t *) & inse_obid);
    new_key.data = &(((osv_oid_i *) & inse_obid)->stoid);
    new_key.size = sizeof (unsigned long long);
    //
    stora_ha->set_key(dcurso, &new_key);
    stora_ha->set_value(dcurso, &valu);
    int inser_valu = stora_ha->inser_curso(dcurso);
    // OSEVPF("inser_curso inser_valu:%d\n", inser_valu);
    if (!inser_valu) {
        unsigned char *last_memo = resctl->resp_memo;
        OBID_LASTBIN_COPY(last_memo, & inse_obid);
        OBID_BINARY_COPY((osv_oid_i *) last_memo, ((osv_oid_i *) exis_obid));
        PDAT_PRODUCEM_TAIL(resctl, OBJE_IDENTI_BLEN * OBID_KEYVAL_COUP)
    }
    // OSEVPF("inser_size:%lld paki_stream_leng(pkps):%ld\n", pamvu->req_len[EPAM_INSER_VALUE], paki_stream_leng(pkps));
    paki_stream_close(pkps, NULL);
    return inser_valu;
}
/*
        if (is_potyp_obid(pamvu->pamcon[EPAM_INSER_VALUE]))
            return -1;
        OSEVPF("1\n");
        slov_memo_t obje_memo;
        if (!slov_malloc(&obje_memo, pamvu->req_len[EPAM_INSER_VALUE]))
            return -1;
        OSEVPF("2\n");
        PK_ITEM key, valu;
        osv_oid_t inser_obid;
        creat_objec_obid((osv_oid_t *) & inser_obid);
        key.data = &(((osv_oid_i *) & inser_obid)->stoid);
        key.size = sizeof (unsigned long long);
        if (solve_obje_valu(&valu, &obje_memo, pamvu->pamcon, lv2me)) {
            free_slov(&obje_memo);
            return -1;
        }
        OSEVPF("3\n");
        stora_ha->set_key(dcurso, &key);
        stora_ha->set_value(dcurso, &valu);
        int inser_valu = stora_ha->inser_curso(dcurso);
        if (!inser_valu) {
            OBID_BINARY_COPY((osv_oid_t *) resctl->resp_memo, & inser_obid);
            PDAT_PRODUCEM_TAIL(resctl, OBJE_IDENTI_BLEN)
        }
        OSEVPF("4 inser_valu:%d\n", inser_valu);
        free_slov(&obje_memo);
        return inser_valu;
 */
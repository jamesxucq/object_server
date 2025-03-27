
/* 
 * File:   fmtst_utili.h
 * Author: James Xu
 *
 * Created on 2023.5.31, PM 2:28
 */

#ifndef FMTST_UTILI_H
#define FMTST_UTILI_H

#include "commo_header.h"
#include "kcstr_utili.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    inline uint64 count_lv2pd_size(char *fmtst) {
        // OSEVPF("[FUNC]:count_lv2pd_size, fmtst:|%s|\n", fmtst);
#ifdef _DEBUG
        uint64 sleng = 0x00;
#else /* _DEBUG */
        uint64 sleng;
#endif /* _DEBUG */
        char *endsize;
        uint64 data_size = OBJE_IDENTI_BLEN;
        for (; fmtst[0x00]; ++fmtst) {
            if (isdigit(fmtst[0x00])) {
                sleng = strtoul(fmtst, &endsize, 10);
                fmtst = endsize;
            }
            switch (fmtst[0x00]) {
                case 'b':
                case 't':
                case 'B':
                    data_size += sizeof (uint8_t);
                    break;
                case 'h':
                case 'H':
                    data_size += sizeof (uint16_t);
                    break;
                case 'i':
                case 'l':
                case 'I':
                case 'L':
                    data_size += sizeof (uint32_t);
                    break;
                case 'q':
                case 'Q':
                case 'r':
                case 'R':
                    data_size += sizeof (uint64_t);
                    break;
                case 'o':
                    data_size += sizeof (osv_oid_t);
                    break;
                case 'f':
                    data_size += sizeof (float);
                    break;
                case 'd':
                    data_size += sizeof (double);
                    break;
                case 's':
                    data_size += sleng;
                    break;
                case 'S':
                    data_size += sizeof (strz_t);
                    break;
                case 'u':
                default:
                    _LOG_WARN("default: fmtst");
                    break;
            }
        }
        // OSEVPF("data_size:|%llu|\n", data_size);
        return data_size;
    }

    // lv2nod->name
    // trans-serve

    inline void build_lv2p_fmtsd(char *fmtsd, lv2p_prop *lv2nod) {
        char fmtch;
        if (ACCE_COTRL_INVAL != lv2nod->access) {
            for (; ACCE_COTRL_INVAL != lv2nod->access; ++lv2nod) {
                fmtch = potyp_fmtst_tab[lv2nod->potyp];
                if ('s' == fmtch)
                    fmtsd = lsprif(fmtsd, "%u", lv2nod->size);
                fmtsd = lccpy(fmtsd, fmtch);
            }
        }
    }

    //

    inline uint64 count_pamik_size(char *fmtst) {
        // OSEVPF("[FUNC]:count_lv2pd_size, fmtst:|%s|\n", fmtst);
#ifdef _DEBUG
        uint64 sleng = 0x00;
#else /* _DEBUG */
        uint64 sleng;
#endif /* _DEBUG */
        char *endsize;
        uint64 data_size = 0x00;
        for (; fmtst[0x00]; ++fmtst) {
            if (isdigit(fmtst[0x00])) {
                sleng = strtoul(fmtst, &endsize, 10);
                fmtst = endsize;
            }
            switch (fmtst[0x00]) {
                case 'b':
                case 't':
                case 'B':
                    data_size += sizeof (uint8_t);
                    break;
                case 'h':
                case 'H':
                    data_size += sizeof (uint16_t);
                    break;
                case 'i':
                case 'l':
                case 'I':
                case 'L':
                    data_size += sizeof (uint32_t);
                    break;
                case 'q':
                case 'Q':
                case 'r':
                case 'R':
                    data_size += sizeof (uint64_t);
                    break;
                case 'o':
                    data_size += sizeof (osv_oid_t);
                    break;
                case 'f':
                    data_size += sizeof (float);
                    break;
                case 'd':
                    data_size += sizeof (double);
                    break;
                case 's':
                    data_size += sleng;
                    break;
                case 'S':
                    data_size += sizeof (strz_t);
                    break;
                case 'u':
                default:
                    _LOG_WARN("default: fmtst");
                    break;
            }
        }
        // OSEVPF("data_size:|%llu|\n", data_size);
        return data_size;
    }


#ifdef __cplusplus
}
#endif

#endif /* FMTST_UTILI_H */


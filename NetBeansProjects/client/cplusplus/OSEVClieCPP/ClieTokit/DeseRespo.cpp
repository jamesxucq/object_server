
/* 
 * File:   DeseRespo.cpp
 * Author: James Xu
 * 
 * Created on 2024.4.18, PM 3:33
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <string>
using std::string;

#include "third_party.h"
#include "osev_common/commo_header.h"

#include "osev_common/obid.h"
#include "../proto_conne/clie_bzl.h"

#include "DeseRespo.h"

//

#define PARAM_TYPE(FMTOK, SLENG, FMTST) { \
    char *endsize; \
    if (isdigit(FMTST[0x00])) { \
        SLENG = strtoul(FMTST, &endsize, 10); \
        FMTST = endsize; \
    } \
    FMTOK = FMTST[0x00]; \
    ++FMTST; \
}

//

DeseRespo::DeseRespo() {
    m_pkps = NULL;
    m_sFmtstr[0x00] = '\0';
}

DeseRespo::DeseRespo(const DeseRespo& orig) {
}

DeseRespo::DeseRespo(resp_data_t *querResp, const string &sFmtstr) {
    if (FMTST_COUNT_ZTAI > sFmtstr.size()) {
        strcpy(m_sFmtstr, sFmtstr.c_str());
        if (paki_stream_open(m_sFmtstr, (void *) querResp->resp_memo, querResp->content_length, &m_pkps)) {
            m_sFmtstr[0x00] = '\0';
            m_pkps = NULL;
        }
    } else {
        m_sFmtstr[0x00] = '\0';
        m_pkps = NULL;
    }
}

DeseRespo::~DeseRespo() {
    if (m_pkps)
        paki_stream_close(m_pkps, NULL);
}

//

void DeseRespo::Reset() {
    paki_stream_reset(m_pkps, RESET_STREAM_FORMAT | RESET_STREAM_DATA);
}

int DeseRespo::Initial(resp_data_t *querResp, const string &sFmtstr) {
    if (('\0' != m_sFmtstr[0x00]) || m_pkps)
        return -1;
    //
    if (FMTST_COUNT_ZTAI <= sFmtstr.size())
        return -1;
    strcpy(m_sFmtstr, sFmtstr.c_str());
    if (paki_stream_open(m_sFmtstr, (void *) querResp->resp_memo, querResp->content_length, &m_pkps)) {
        m_sFmtstr[0x00] = '\0';
        m_pkps = NULL;
        return -1;
    }
    //
    return 0x00;
}

int DeseRespo::Final(size_t *usedp) {
    m_sFmtstr[0x00] = '\0';
    paki_stream_close(m_pkps, usedp);
    m_pkps = NULL;
    return 0x00;
}

int DeseRespo::LoopDeseri(osv_oid_t *resp_obid, ...) {
    char fmtok;
    uint64 sleng;
    int upakValu;
    void *deseValu;
    //
    if (('\0' == m_sFmtstr[0x00]) || !m_pkps)
        return -1;
    //
    paki_stream_reset(m_pkps, RESET_STREAM_FORMAT);
    char *fmtstr = m_sFmtstr;
    //
    PARAM_TYPE(fmtok, sleng, fmtstr)
    if ('o' != fmtok) return -1;
    upakValu = paki_unpack_OBID(m_pkps, resp_obid);
    if (upakValu)
        return (ENOMEM == upakValu) ? 0x01 : -1;
    //
    va_list ap;
    va_start(ap, resp_obid);
    //
    PARAM_TYPE(fmtok, sleng, fmtstr)
    while ('\0' != fmtok) {
        // CLIEPF("sleng:%llu fmtok:|%c|\n", sleng, fmtok);
        deseValu = va_arg(ap, void *);
        switch (fmtok) {
            case 'b':
                upakValu = paki_unpack_byte(m_pkps, (int8_t *) deseValu);
                if (upakValu) {
                    va_end(ap);
                    return (ENOMEM == upakValu) ? 0x01 : -1;
                }
                break;
            case 'B':
            case 't':
                upakValu = paki_unpack_ubyte(m_pkps, (uint8_t *) deseValu);
                if (upakValu) {
                    va_end(ap);
                    return (ENOMEM == upakValu) ? 0x01 : -1;
                }
                break;
            case 'h':
                upakValu = paki_unpack_short(m_pkps, (int16_t *) deseValu);
                if (upakValu) {
                    va_end(ap);
                    return (ENOMEM == upakValu) ? 0x01 : -1;
                }
                break;
            case 'H':
                upakValu = paki_unpack_ushort(m_pkps, (uint16_t *) deseValu);
                if (upakValu) {
                    va_end(ap);
                    return (ENOMEM == upakValu) ? 0x01 : -1;
                }
                break;
            case 'i':
            case 'l':
                upakValu = paki_unpack_int32(m_pkps, (int32_t *) deseValu);
                if (upakValu) {
                    va_end(ap);
                    return (ENOMEM == upakValu) ? 0x01 : -1;
                }
                break;
            case 'I':
            case 'L':
                upakValu = paki_unpack_uint32(m_pkps, (uint32_t *) deseValu);
                if (upakValu) {
                    va_end(ap);
                    return (ENOMEM == upakValu) ? 0x01 : -1;
                }
                break;
            case 'q':
                upakValu = paki_unpack_int64(m_pkps, (int64_t *) deseValu);
                if (upakValu) {
                    va_end(ap);
                    return (ENOMEM == upakValu) ? 0x01 : -1;
                }
                break;
            case 'Q':
            case 'R':
                upakValu = paki_unpack_uint64(m_pkps, (uint64_t *) deseValu);
                if (upakValu) {
                    va_end(ap);
                    return (ENOMEM == upakValu) ? 0x01 : -1;
                }
                break;
            case 'o':
                upakValu = paki_unpack_OBID(m_pkps, (osv_oid_t *) deseValu);
                if (upakValu) {
                    va_end(ap);
                    return (ENOMEM == upakValu) ? 0x01 : -1;
                }
                break;
            case 'f':
                upakValu = paki_unpack_float(m_pkps, (float *) deseValu);
                if (upakValu) {
                    va_end(ap);
                    return (ENOMEM == upakValu) ? 0x01 : -1;
                }
                break;
            case 'd':
                upakValu = paki_unpack_double(m_pkps, (double *) deseValu);
                if (upakValu) {
                    va_end(ap);
                    return (ENOMEM == upakValu) ? 0x01 : -1;
                }
                break;
            case 's':
                upakValu = paki_unpack_STRI(m_pkps, (char *) deseValu, sleng);
                if (upakValu) {
                    va_end(ap);
                    return (ENOMEM == upakValu) ? 0x01 : -1;
                }
                break;
            case 'S':
                upakValu = paki_unpack_STRZ(m_pkps, (char *) deseValu);
                if (upakValu) {
                    va_end(ap);
                    return (ENOMEM == upakValu) ? 0x01 : -1;
                }
                break;
            default:
                break;
        }
        PARAM_TYPE(fmtok, sleng, fmtstr)
    }
    //
    va_end(ap);
    //
    return 0x00;
}
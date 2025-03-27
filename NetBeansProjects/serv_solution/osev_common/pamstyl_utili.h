
/* 
 * File:   pamstyl_utili.h
 * Author: James Xu
 *
 * Created on 2018.3.16, PM 1:46
 */

#ifndef PAMSTYL_UTILI_H
#define PAMSTYL_UTILI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ctype.h>

#include "utility/last_stri.h"
#include "parms_style.h"
#include "compa_style.h"
#include "osev_struct.h"

#ifdef __cplusplus
extern "C" {
#endif

    // ("aa", "bb", "cc", "dd");

    inline unsigned long long encod_stri_loop(char *pscon, const char **pamvp) {
        unsigned long long lenval = 0x00;
        for (; pamvp[0x00]; ++pamvp) {
            STRI_PAMSTYL(pscon, lenval, pamvp[0x00])
        }
        return lenval;
    }

    // (obj1, obj2, obj3, obj4);

    inline unsigned long long encod_binary_loop(char *pscon, const char **pamvp) {
        unsigned long long binlen;
        unsigned long long lenval = 0x00;
        for (; pamvp[0x00]; ++pamvp) {
            if (BINA_ENTIT_TYPE != pamvp[0x00][ESCA_NODTYP_PART])
                return INVA_ULOLO_VALU;
            binlen = ((unsigned long long*) (pamvp[0x00] + ESCA_ENCOLEN_PART))[0x00];
            BINARY_PAMSTYL(pscon, lenval, ((char *) pamvp[0x00] + ESCA_ENTICON_PART), binlen)
        }
        return lenval;
    }

    // (pack1);

    inline unsigned long long encod_binnak_once(char *pscon, const char **pamvp) {
        if (BINA_ENTIT_TYPE != pamvp[0x00][ESCA_NODTYP_PART])
            return INVA_ULOLO_VALU;
        unsigned long long lenval = ((unsigned long long*) (pamvp[0x00] + ESCA_ENCOLEN_PART))[0x00];
        BINARY_PAMSTYL_NAKED(pscon, ((char *) pamvp[0x00] + ESCA_ENTICON_PART), lenval)
        return lenval;
    }

    // PARAM_LENGTH // DATY_STRI ("bb");

    inline char *decod_stri_once(char **pamvp, char *_data_line_, char *req_dat) {
        LSCPY_INI(pamvp[0x00], _data_line_);
        if (!pamstyl_stri(pamvp[0x00], req_dat)) {
            pamvp[0x00] = NULL;
            return NULL;
        }
        LSCPY_FIN(_data_line_, pamvp[0x00]);
        pamvp[0x01] = NULL;
        return _data_line_;
    }

    // PARAM_LENGTH // DATY_STRZ ("bb");

    inline char *decod_strz_once(char **pamvp, char *_data_line_, char *req_dat) {
        LSCPY_INI(pamvp[0x00], _data_line_);
        if (!pamstyl_strz(pamvp[0x00], req_dat)) {
            pamvp[0x00] = NULL;
            return NULL;
        }
        LSCPY_FIN(_data_line_, pamvp[0x00]);
        pamvp[0x01] = NULL;
        return _data_line_;
    }

    // LARGE_TEXT_SIZE // DATY_STRI ("aaaaa");
    char *decod_txti_once(char **pamvp, char *_data_line_, char *req_dat);

    // LARGE_TEXT_SIZE // DATY_STRZ ("aaaaa");
    char *decod_txtz_once(char **pamvp, char *_data_line_, char *req_dat);

    // DATY_UINT (333);

    inline char *decod_uint32_once(char **pamvp, char *_data_line_, char *req_dat) {
        LAMCPY_INS(pamvp[0x00], sizeof (unsigned int), _data_line_)
        if (!pamstyl_uint((unsigned int *) pamvp[0x00], req_dat)) {
            pamvp[0x00] = NULL;
            return NULL;
        }
        pamvp[0x01] = NULL;
        return _data_line_;
    }

    // DATY_BINARY (object)

    char *decod_binary_once(char **pamvp, char *_data_line_, char *req_dat);
    char *decod_obid_once(char **pamvp, char *_data_line_, char *req_dat);

    inline char *decod_binary_paki(char **pamvp, char *_data_line_, char *req_dat, unsigned long long req_len) {
        LAMCPY_BIN(pamvp[0x00], req_dat, req_len, _data_line_);
        pamvp[0x01] = NULL;
        return _data_line_;
    }

    // (11, "bb", 22, "dd"); result is object

    inline char *decod_binary_loop(char **pamvp, char *_data_line_, char *req_dat, unsigned long long req_len) {
        char *pamcon;
        char *end_tok = req_dat + req_len;
        unsigned long long enlen;
        for (; end_tok > req_dat; ++pamvp) {
            pamcon = req_dat;
            req_dat = decode_pamstyl_enleng(&enlen, req_dat);
            if (!req_dat) {
                pamvp[0x00] = NULL;
                return NULL;
            }
            LAMCPY_BIN(pamvp[0x00], pamcon, enlen, _data_line_);
            // printf("enlen:%llu\n", enlen);
        }
        pamvp[0x00] = NULL;
        return _data_line_;
    }

    // DATY_STRI ("aa", "bb", "cc", "dd");

    inline char *decod_stri_loop(char **pamvp, char *_data_line_, char *req_dat, unsigned long long req_len) {
        char *end_tok = req_dat + req_len;
        for (; end_tok > req_dat; ++pamvp) {
            LSCPY_INI(pamvp[0x00], _data_line_);
            req_dat = pamstyl_stri(pamvp[0x00], req_dat);
            if (!req_dat) {
                pamvp[0x00] = NULL;
                return NULL;
            }
            LSCPY_FIN(_data_line_, pamvp[0x00]);
            // OSEVPF("dstri:|%s| parse_len:%d enlen:%d req_len:%d\n", pamvp[0x00], parse_len, enlen, req_len);
        }
        pamvp[0x00] = NULL;
        return _data_line_;
    }

    // DATY_STRZ ("aa", "bb", "cc", "dd");

    inline char *decod_strz_loop(char **pamvp, char *_data_line_, char *req_dat, unsigned long long req_len) {
        char *end_tok = req_dat + req_len;
        for (; end_tok > req_dat; ++pamvp) {
            LSCPY_INI(pamvp[0x00], _data_line_);
            req_dat = pamstyl_strz(pamvp[0x00], req_dat);
            if (!req_dat) {
                pamvp[0x00] = NULL;
                return NULL;
            }
            LSCPY_FIN(_data_line_, pamvp[0x00]);
            // OSEVPF("dstri:|%s| parse_len:%d enlen:%d req_len:%d\n", pamvp[0x00], parse_len, enlen, req_len);
        }
        pamvp[0x00] = NULL;
        return _data_line_;
    }

    // decod general multiple
    // (11, "bb", 22, "dd");
    char *decod_gener_loop(char **pamvp, char *_data_line_, char *req_dat, unsigned long long req_len);

    // decod gener type multiple
    // pams_valu *pamvu, (11, "bb", 22, "dd");
    char *decod_getyp_loop(pams_valu *pamvu, char *_data_line_, char *req_dat);

    //

    char *decod_getyp_stram(pams_valu *pamvu, char *_data_line_, char *req_dat, char *req_sta);

    // decod gener type single
    // pams_valu *pamvu, (11) ("bb") (22) ("dd");
    char *decod_getyp_once(pams_valu *pamvu, char *_data_line_, char *req_dat);

    //

#ifdef __cplusplus
}
#endif

#endif /* PAMSTYL_UTILI_H */


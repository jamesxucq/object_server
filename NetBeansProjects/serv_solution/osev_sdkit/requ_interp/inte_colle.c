#include "commo_header.h"
#include "kcomm_header.h"

#include "istri_utili.h"
#include "inte_colle.h"

//

void colle_post_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:colle_post_inpe\n");
    char *pase_tok = unpak_conte_leng(pamvu->req_len, requ_memo);
    if (pase_tok) {
        if (!decod_getyp_loop(pamvu, _data_line_, pase_tok)) {
            pamvu->pamtyp[0x00] = DATY_INVAL;
            pamvu->pamcon[0x00] = NULL;
        }
    } else {
        pamvu->pamtyp[0x00] = DATY_INVAL;
        pamvu->pamcon[0x00] = NULL;
    }
}

//

void colle_statu_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:colle_statu_inpe\n");
    char *pase_tok = unpak_conte_leng(pamvu->req_len, requ_memo);
    if (pase_tok) {
        if (!decod_getyp_loop(pamvu, _data_line_, pase_tok)) {
            pamvu->pamtyp[0x00] = DATY_INVAL;
            pamvu->pamcon[0x00] = NULL;
        }
    } else {
        pamvu->pamtyp[0x00] = DATY_INVAL;
        pamvu->pamcon[0x00] = NULL;
    }
}

void colle_creat_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:colle_creat_inpe\n");
    char *pase_tok = unpak_binary_conte(requ_memo);
    if (pase_tok) {
        if (!decod_txti_once(pamvu->pamcon, _data_line_, pase_tok))
            pamvu->pamcon[0x00] = NULL;
    } else pamvu->pamcon[0x00] = NULL;
}

void colle_repla_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:colle_repla_inpe\n");
    char *pase_tok = unpak_conte_leng(pamvu->req_len, requ_memo);
    if (pase_tok) {
        if (!decod_stri_uint(pamvu->pamcon, _data_line_, pase_tok, pamvu->req_len[0x00]))
            pamvu->pamcon[0x00] = NULL;
    } else pamvu->pamcon[0x00] = NULL;
}

void colle_drop_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:colle_drop_inpe\n");
    char *pase_tok = unpak_binary_conte(requ_memo);
    if (pase_tok) {
        if (!decod_stri_once(pamvu->pamcon, _data_line_, pase_tok))
            pamvu->pamcon[0x00] = NULL;
    } else pamvu->pamcon[0x00] = NULL;
}

void colle_integra_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:colle_integra_inpe\n");
    char *pase_tok = unpak_binary_conte(requ_memo);
    if (pase_tok) {
        OSEVPF("parse_stri\n");
        if (!decod_stri_once(pamvu->pamcon, _data_line_, pase_tok))
            pamvu->pamcon[0x00] = NULL;
    } else pamvu->pamcon[0x00] = NULL;
}

void colle_reload_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:colle_reload_inpe\n");
    char *pase_tok = unpak_binary_conte(requ_memo);
    if (pase_tok) {
        if (!decod_stri_once(pamvu->pamcon, _data_line_, pase_tok))
            pamvu->pamcon[0x00] = NULL;
    } else pamvu->pamcon[0x00] = NULL;
}



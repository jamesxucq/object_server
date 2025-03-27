#include "commo_header.h"

#include "istri_utili.h"
#include "inte_base.h"

// odb:echo();
// odb:open();
// odb:close();
// odb:status();

// odb:list();
// odb:user();
// odb:role();

// authen

void base_authe_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    char *pase_tok = unpak_conte_leng(pamvu->req_len, requ_memo);
    if (pase_tok) {
        if (!decod_gener_loop(pamvu->pamcon, _data_line_, pase_tok, pamvu->req_len[0x00]))
            pamvu->pamcon[0x00] = NULL;
    } else pamvu->pamcon[0x00] = NULL;
}

//

void base_post_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:base_post_inpe\n");
    char *pase_tok = unpak_conte_leng(pamvu->req_len, requ_memo);
    if (pase_tok) {
        OSEVPF("parse post, pamvu->req_len[0x00]:%llu\n", pamvu->req_len[0x00]);
        if (!decod_gener_loop(pamvu->pamcon, _data_line_, pase_tok, pamvu->req_len[0x00]))
            pamvu->pamcon[0x00] = NULL;
    } else pamvu->pamcon[0x00] = NULL;
}

//

void base_comd_open_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:base_comd_open_inpe\n");
    char *pase_tok = unpak_conte_leng(pamvu->req_len, requ_memo);
    if (pase_tok) {
        if (!decod_gener_loop(pamvu->pamcon, _data_line_, pase_tok, pamvu->req_len[0x00]))
            pamvu->pamcon[0x00] = NULL;
    } else pamvu->pamcon[0x00] = NULL;
}

void base_comd_close_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:base_comd_close_inpe\n");
    char *pase_tok = unpak_binary_conte(requ_memo);
    if (pase_tok) {
        if (!decod_obid_once(pamvu->pamcon, _data_line_, pase_tok))
            pamvu->pamcon[0x00] = NULL;
    } else pamvu->pamcon[0x00] = NULL;
}

//

void base_stat_echo_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:base_stat_echo_inpe\n");
    char *pase_tok = unpak_binary_conte(requ_memo);
    if (pase_tok) {
        if (!decod_obid_once(pamvu->pamcon, _data_line_, pase_tok))
            pamvu->pamcon[0x00] = NULL;
    } else pamvu->pamcon[0x00] = NULL;
}

void base_stat_stati_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:base_stat_stati_inpe\n");
    char *pase_tok = unpak_conte_leng(pamvu->req_len, requ_memo);
    if (pase_tok) {
        if (!decod_gener_loop(pamvu->pamcon, _data_line_, pase_tok, pamvu->req_len[0x00]))
            pamvu->pamcon[0x00] = NULL;
    } else pamvu->pamcon[0x00] = NULL;
}

// privi

void base_priv_list_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:base_priv_list_inpe\n");
    char *pase_tok = unpak_conte_leng(pamvu->req_len, requ_memo);
    if (pase_tok) {
        if (!decod_gener_loop(pamvu->pamcon, _data_line_, pase_tok, pamvu->req_len[0x00]))
            pamvu->pamcon[0x00] = NULL;
    } else pamvu->pamcon[0x00] = NULL;
}

void base_priv_role_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:base_priv_role_inpe\n");
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

void base_priv_user_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:base_priv_user_inpe\n");
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


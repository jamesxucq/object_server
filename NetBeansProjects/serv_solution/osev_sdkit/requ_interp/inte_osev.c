#include "commo_header.h"

#include "istri_utili.h"
#include "inte_osev.h"

// osev: command:open(earth);
// osev:echo(odb);
// osev:open(odb);
// osev:close(odb);
// osev:status(odb);
//
// osev:list(odb);
// osev:user(odb);
// osev:role(odb);

// authen

void osev_authe_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    char *pase_tok = unpak_conte_leng(pamvu->req_len, requ_memo);
    if (pase_tok) {
        if (!decod_gener_loop(pamvu->pamcon, _data_line_, pase_tok, pamvu->req_len[0x00]))
            pamvu->pamcon[0x00] = NULL;
    } else pamvu->pamcon[0x00] = NULL;
}

//

void osev_comd_open_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:osev_comd_open_inpe\n");
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

void osev_comd_close_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:osev_comd_close_inpe\n");
    char *pase_tok = unpak_binary_conte(requ_memo);
    if (pase_tok) {
        if (!decod_stri_once(pamvu->pamcon, _data_line_, pase_tok))
            pamvu->pamcon[0x00] = NULL;
    } else pamvu->pamcon[0x00] = NULL;
}

//

void osev_stat_echo_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:osev_stat_echo_inpe\n");
    char *pase_tok = unpak_binary_conte(requ_memo);
    if (pase_tok) {
        if (!decod_stri_once(pamvu->pamcon, _data_line_, pase_tok))
            pamvu->pamcon[0x00] = NULL;
    } else pamvu->pamcon[0x00] = NULL;
}

void osev_post_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:osev_post_inpe\n");
    char *pase_tok = unpak_conte_leng(pamvu->req_len, requ_memo);
    if (pase_tok) {
        if (!decod_gener_loop(pamvu->pamcon, _data_line_, pase_tok, pamvu->req_len[0x00]))
            pamvu->pamcon[0x00] = NULL;
    } else pamvu->pamcon[0x00] = NULL;
}

void osev_stat_stati_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:osev_stat_stati_inpe\n");
    char *pase_tok = unpak_conte_leng(pamvu->req_len, requ_memo);
    if (pase_tok) {
        if (!decod_gener_loop(pamvu->pamcon, _data_line_, pase_tok, pamvu->req_len[0x00]))
            pamvu->pamcon[0x00] = NULL;
    } else pamvu->pamcon[0x00] = NULL;
}

void osev_priv_list_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:osev_priv_list_inpe\n");
    char *pase_tok = unpak_conte_leng(pamvu->req_len, requ_memo);
    if (pase_tok) {
        if (!decod_gener_loop(pamvu->pamcon, _data_line_, pase_tok, pamvu->req_len[0x00]))
            pamvu->pamcon[0x00] = NULL;
    } else pamvu->pamcon[0x00] = NULL;
}

void osev_priv_role_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:osev_priv_role_inpe\n");
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
    OSEVPF("pamvu->req_len[0x00]:%llu\n", pamvu->req_len[0x00]);
}

void osev_priv_user_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:osev_priv_user_inpe\n");
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


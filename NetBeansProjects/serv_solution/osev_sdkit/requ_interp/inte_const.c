#include "commo_header.h"
#include "kcomm_header.h"

#include "istri_utili.h"
#include "inte_const.h"

//

void const_post_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:const_post_inpe\n");
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

// xxx:echo();
// xxx:create();
// xxx:drop();
// xxx:rplace();
// xxx:insert();
// xxx:search();
// xxx:invoke();

void const_statu_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:const_statu_inpe\n");
    char *pase_tok = unpak_conte_leng(pamvu->req_len, requ_memo);
    if (pase_tok) {
        if (!decod_gener_loop(pamvu->pamcon, _data_line_, pase_tok, pamvu->req_len[0x00]))
            pamvu->pamcon[0x00] = NULL;
    } else pamvu->pamcon[0x00] = NULL;
}

void const_creat_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:const_creat_inpe\n");
    char *pase_tok = unpak_conte_leng(pamvu->req_len, requ_memo);
    if (pase_tok) {
        if (!decod_binary_loop(pamvu->pamcon, _data_line_, pase_tok, pamvu->req_len[0x00]))
            pamvu->pamcon[0x00] = NULL;
    } else pamvu->pamcon[0x00] = NULL;
}

void const_drop_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:const_drop_inpe\n");
    char *pase_tok = unpak_binary_conte(requ_memo);
    if (pase_tok) {
        if (!decod_getyp_once(pamvu, _data_line_, pase_tok)) {
            pamvu->pamtyp[0x00] = DATY_INVAL;
            pamvu->pamcon[0x00] = NULL;
        }
    } else {
        pamvu->pamtyp[0x00] = DATY_INVAL;
        pamvu->pamcon[0x00] = NULL;
    }
}

/*
#pragma pack(1) 

struct _test_ {
    osv_oid_t parse_ooid;
    int xx;
    int ax;
    int cx;
};
#pragma pack() 
 */

void const_updat_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:const_updat_inpe\n");
    char *pase_tok = unpak_conte_leng(pamvu->req_len, requ_memo);
    if (pase_tok) {
        if (!decod_binary_paki(pamvu->pamcon, _data_line_, pase_tok, pamvu->req_len[0x00]))
            pamvu->pamcon[0x00] = NULL;
    } else pamvu->pamcon[0x00] = NULL;
}

void const_inser_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:const_inser_inpe\n");
    char *pase_tok = unpak_conte_leng(pamvu->req_len, requ_memo);
    if (pase_tok) {
        if (!decod_binary_paki(pamvu->pamcon, _data_line_, pase_tok, pamvu->req_len[0x00]))
            pamvu->pamcon[0x00] = NULL;
    } else pamvu->pamcon[0x00] = NULL;
}

void const_searc_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:const_searc_inpe\n");
    char *pase_tok = unpak_binary_conte(requ_memo);
    if (pase_tok) {
        if (!decod_getyp_once(pamvu, _data_line_, pase_tok)) {
            pamvu->pamtyp[0x00] = DATY_INVAL;
            pamvu->pamcon[0x00] = NULL;
        }
    } else {
        pamvu->pamtyp[0x00] = DATY_INVAL;
        pamvu->pamcon[0x00] = NULL;
    }
}

void const_invok_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:const_invok_inpe\n");
    char *pase_tok = unpak_conte_leng(pamvu->req_len, requ_memo);
    if (pase_tok) {
        if (!decode_const_invok(pamvu, _data_line_, pase_tok)) {
            pamvu->pamtyp[0x00] = DATY_INVAL;
            pamvu->pamcon[0x00] = NULL;
        }
    } else {
        pamvu->pamtyp[0x00] = DATY_INVAL;
        pamvu->pamcon[0x00] = NULL;
    }
}




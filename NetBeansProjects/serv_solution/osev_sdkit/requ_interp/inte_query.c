#include "commo_header.h"
#include "kcomm_header.h"

#include "istri_utili.h"
#include "inte_query.h"

//

void query_post_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:query_post_inpe\n");
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
// odb:echo();
// odb:create();
// odb:drop();
// odb:search();
// odb:invoke();
// odb:factory();

void query_statu_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:query_statu_inpe\n");
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

void query_creat_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:query_creat_inpe\n");
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

void query_drop_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:query_drop_inpe\n");
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

void query_updat_inpe(pams_valu *pamvu, char *_data_line_, FILE *requ_stram) {
    OSEVPF("[FUNC]:query_updat_inpe\n");
    char req_had[READ_HEAD_SIZE];
    if (!read_requ_head(req_had, requ_stram)) {
        char *pase_tok = unpak_conte_leng(pamvu->req_len, req_had);
        if (pase_tok) {
            if (!decod_getyp_stram(pamvu, _data_line_, pase_tok, req_had)) {
                pamvu->pamtyp[0x00] = DATY_INVAL;
                pamvu->pamcon[0x00] = NULL;
            } else pamvu->pamstem = requ_stram;
        } else {
            pamvu->pamtyp[0x00] = DATY_INVAL;
            pamvu->pamcon[0x00] = NULL;
        }
    } else pamvu->pamtyp[0x00] = DATY_INVAL;
}

void query_inser_inpe(pams_valu *pamvu, char *_data_line_, FILE *requ_stram) {
    OSEVPF("[FUNC]:parse_inser_inpe\n");
    char req_had[READ_HEAD_SIZE];
    if (!read_requ_head(req_had, requ_stram)) {
        char *pase_tok = unpak_conte_leng(pamvu->req_len, req_had);
        if (pase_tok) {
            if (!decod_getyp_stram(pamvu, _data_line_, pase_tok, req_had)) {
                pamvu->pamtyp[0x00] = DATY_INVAL;
                pamvu->pamcon[0x00] = NULL;
            } else pamvu->pamstem = requ_stram;
        } else {
            pamvu->pamtyp[0x00] = DATY_INVAL;
            pamvu->pamcon[0x00] = NULL;
        }
    } else pamvu->pamtyp[0x00] = DATY_INVAL;
}

void query_searc_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:query_searc_inpe\n");
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

void query_invok_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:query_invok_inpe\n");
    char *pase_tok = unpak_conte_leng(pamvu->req_len, requ_memo);
    if (pase_tok) {
        if (!decode_query_invok(pamvu, _data_line_, pase_tok)) {
            // OSEVPF("decode_query_invok error.\n");
            pamvu->pamtyp[0x00] = DATY_INVAL;
            pamvu->pamcon[0x00] = NULL;
        }
    } else {
        pamvu->pamtyp[0x00] = DATY_INVAL;
        pamvu->pamcon[0x00] = NULL;
    }
}

void query_facto_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo) {
    OSEVPF("[FUNC]:query_facto_inpe\n");
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



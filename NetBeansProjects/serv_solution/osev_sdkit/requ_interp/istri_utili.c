#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "commo_header.h"
#include "kcomm_header.h"
#include "invok_bzl.h"
#include "istri_utili.h"
#include "lv2p_expand.h"
#include "lev1_decla.h"

//

char *decode_const_invok(pams_valu *pamvu, char *_data_line_, char *req_dat) {
    // OSEVPF("[FUNC]:decode_const_invok\n");
    unsigned char *pamtyp = pamvu->pamtyp;
    char **pamvp = pamvu->pamcon;
    char *end_tok = req_dat + pamvu->req_len[0x00];
    unsigned long long celen;
    //
    pamtyp[0x00] = ((unsigned char *) req_dat)[0x00];
    // OSEVPF("0x00 pamtyp[0x00]:%u\n", pamtyp[0x00]);
    LAMCPY_INI(pamvp[0x00], _data_line_);
    req_dat = pamstyl_binary_ext(pamvp[0x00], &celen, req_dat);
    if (!req_dat) {
        pamtyp[0x00] = DATY_INVAL;
        pamvp[0x00] = NULL;
        return NULL;
    }
    LAMCPY_FIN(_data_line_, celen);
    // OSEVPF("0 req_len:%llu, parse_len:%llu\n", req_len, parse_len);
    if (end_tok > req_dat) {
        (++pamtyp)[0x00] = ((unsigned char *) req_dat)[0x00];
        // OSEVPF("0x01 pamtyp[0x00]:%u\n", pamtyp[0x00]);
        if (DATY_STRI == pamtyp[0x00]) {
            ++pamvp;
            LSCPY_INI(pamvp[0x00], _data_line_);
            req_dat = pamstyl_stri(pamvp[0x00], req_dat);
            if (!req_dat) {
                pamtyp[0x00] = DATY_INVAL;
                pamvp[0x00] = NULL;
                return NULL;
            }
            LSCPY_FIN(_data_line_, pamvp[0x00]);
        } else if (DATY_OBID == pamtyp[0x00]) {
            ++pamvp;
            LAMCPY_INS(pamvp[0x00], sizeof (osv_oid_t), _data_line_)
            req_dat = pamstyl_obid((osv_oid_t *) pamvp[0x00], req_dat);
            if (!req_dat) {
                pamtyp[0x00] = DATY_INVAL;
                pamvp[0x00] = NULL;
                return NULL;
            }
        } else {
            pamtyp[0x00] = DATY_INVAL;
            pamvp[0x00] = NULL;
            return NULL;
        }
        // OSEVPF("1 req_len:%llu, parse_len:%llu\n", req_len, parse_len);
    }
    //
    (++pamtyp)[0x00] = DATY_INVAL;
    (++pamvp)[0x00] = NULL;
    return _data_line_;
}

//

char *decode_query_invok(pams_valu *pamvu, char *_data_line_, char *req_dat) {
    // OSEVPF("[FUNC]:decode_query_invok\n");
    unsigned char *pamtyp = pamvu->pamtyp;
    char **pamvp = pamvu->pamcon;
    char *end_tok = req_dat + pamvu->req_len[0x00];
    unsigned long long celen;
    //
    pamtyp[0x00] = ((unsigned char *) req_dat)[0x00];
    if (DATY_STRI == pamtyp[0x00]) {
        LSCPY_INI(pamvp[0x00], _data_line_);
        req_dat = pamstyl_stri(pamvp[0x00], req_dat);
        if (!req_dat) {
            pamtyp[0x00] = DATY_INVAL;
            pamvp[0x00] = NULL;
            return NULL;
        }
        LSCPY_FIN(_data_line_, pamvp[0x00]);
        // OSEVPF("pamvp[0x00]:|%s|\n", pamvp[0x00]);
    } else if (DATY_OBID == pamtyp[0x00]) {
        LAMCPY_INS(pamvp[0x00], sizeof (osv_oid_t), _data_line_);
        req_dat = pamstyl_obid((osv_oid_t *) pamvp[0x00], req_dat);
        if (!req_dat) {
            pamtyp[0x00] = DATY_INVAL;
            pamvp[0x00] = NULL;
            return NULL;
        }
    } else {
        pamtyp[0x00] = DATY_INVAL;
        pamvp[0x00] = NULL;
        return NULL;
    }
    // OSEVPF("0 req_len:%llu, parse_len:%llu, celen:%llu\n", req_len, parse_len, celen);
    if (end_tok > req_dat) {
        (++pamtyp)[0x00] = ((unsigned char *) req_dat)[0x00];
        // OSEVPF("0x00 pamtyp[0x00]:%u\n", pamtyp[0x00]);
        ++pamvp;
        LAMCPY_INI(pamvp[0x00], _data_line_);
        req_dat = pamstyl_binary_ext(pamvp[0x00], &celen, req_dat);
        if (!req_dat) {
            pamtyp[0x00] = DATY_INVAL;
            pamvp[0x00] = NULL;
            return NULL;
        }
        LAMCPY_FIN(_data_line_, celen);
        // OSEVPF("pamvp[0x00]:|%s|\n", pamvp[0x00]);
        // OSEVPF("1 req_len:%llu, parse_len:%llu, celen:%llu\n", req_len, parse_len, celen);
    }
    //
    if (end_tok > req_dat) {
        (++pamtyp)[0x00] = ((unsigned char *) req_dat)[0x00];
        // OSEVPF("0x02 pamtyp[0x00]:%u\n", pamtyp[0x00]);
        if (DATY_STRI == pamtyp[0x00]) {
            ++pamvp;
            LSCPY_INI(pamvp[0x00], _data_line_);
            req_dat = pamstyl_stri(pamvp[0x00], req_dat);
            if (!req_dat) {
                pamtyp[0x00] = DATY_INVAL;
                pamvp[0x00] = NULL;
                return NULL;
            }
            LSCPY_FIN(_data_line_, pamvp[0x00]);
            // OSEVPF("pamvp[0x00]:|%s|\n", pamvp[0x00]);
        } else if (DATY_OBID == pamtyp[0x00]) {
            ++pamvp;
            LAMCPY_INS(pamvp[0x00], sizeof (osv_oid_t), _data_line_);
            req_dat = pamstyl_obid((osv_oid_t *) pamvp[0x00], req_dat);
            if (!req_dat) {
                pamtyp[0x00] = DATY_INVAL;
                pamvp[0x00] = NULL;
                return NULL;
            }
        } else {
            pamtyp[0x00] = DATY_INVAL;
            pamvp[0x00] = NULL;
            return NULL;
        }
        // OSEVPF("2 req_len:%llu, parse_len:%llu, celen:%llu\n", req_len, parse_len, celen);
    }
    //
    (++pamtyp)[0x00] = DATY_INVAL;
    (++pamvp)[0x00] = NULL;
    return _data_line_;
}

//

char *decode_invok_statu(char **pamvp, char *_data_line_, char *req_dat, unsigned long long req_len) {
    // OSEVPF("[FUNC]:decode_invok_statu\n");
    char *end_tok = req_dat + req_len;
    LSCPY_INI(pamvp[0x00], _data_line_);
    req_dat = pamstyl_stri(pamvp[0x00], req_dat);
    if (!req_dat) {
        pamvp[0x00] = NULL;
        return NULL;
    }
    LSCPY_FIN(_data_line_, pamvp[0x00]);
    // OSEVPF("1 pamvp[0x00]:|%s|\n", pamvp[0x00]);
    ++pamvp;
    LAMCPY_INS(pamvp[0x00], sizeof (unsigned int), _data_line_);
    req_dat = pamstyl_uint((unsigned int*) pamvp[0x00], req_dat);
    if (!req_dat) {
        pamvp[0x00] = NULL;
        return NULL;
    }
    // OSEVPF("2 req_len:%llu, parse_len:%llu, pamvp[0x00]:%u\n", req_len, parse_len, pamvp[0x00]);
    if (end_tok != req_dat) return NULL;
    (++pamvp)[0x00] = NULL;
    return _data_line_;
}

//

char *decod_stri_uint(char **pamvp, char *_data_line_, char *req_dat, unsigned long long req_len) {
    // OSEVPF("[FUNC]:decode_invok_statu\n");
    char *end_tok = req_dat + req_len;
    LSCPY_INI(pamvp[0x00], _data_line_);
    req_dat = pamstyl_stri(pamvp[0x00], req_dat);
    if (!req_dat) {
        pamvp[0x00] = NULL;
        return NULL;
    }
    LSCPY_FIN(_data_line_, pamvp[0x00]);
    // OSEVPF("1 pamvp[0x00]:|%s|\n", pamvp[0x00]);
    if (end_tok > req_dat) {
        ++pamvp;
        LAMCPY_INS(pamvp[0x00], sizeof (unsigned int), _data_line_);
        req_dat = pamstyl_uint((unsigned int*) pamvp[0x00], req_dat);
        if (!req_dat) {
            pamvp[0x00] = NULL;
            return NULL;
        }
    }
    // OSEVPF("2 req_len:%llu, parse_len:%llu, pamvp[0x00]:%u\n", req_len, parse_len, pamvp[0x00]);
    if (end_tok != req_dat) return NULL;
    (++pamvp)[0x00] = NULL;
    return _data_line_;
}

//

char *filli_integ_handn(OUT char *handn, char *lv2pn, char *lev1n, char *ptype) {
    handn = lscpy(handn, lv2pn);
    handn = lccpy(handn, '_');
    handn = lscpy(handn, lev1n);
    handn = lccpy(handn, '_');
    lscpy(handn, ptype);
    //
    return handn;
}

//

lev1id *build_clev1i_lev1d(OUT lev1id *lev1i, lev1_decl_t *lev1d, char *lev1n, lv1_cont *l1lsnd) {
    strcpy(lev1i->crea_lev1n, lev1n);
    //
    char **ilv2np = lev1d->inhe_lv2n;
    char *last_str = lev1i->inhe_lev1i;
    for (; ilv2np[0x00]; ++ilv2np) {
        last_str = lscpy(last_str, ilv2np[0x00]);
        last_str = lccpy(last_str, ':');
    }
    lscpy(last_str, lev1n);
    // strcpy(lev1i->inne_fmtsp_oi, lev1d->innep.inne_fmtsp);
    lev1i->oivk_retyp_oi = l1lsnd->oivk_retyp_oc;
    strcpy(lev1i->oivk_fmtsp_oi, l1lsnd->oivk_fmtsp_oc);
    lev1i->oivk_size_oi = l1lsnd->oivk_size_oc;
    //
    return lev1i;
}

lev1id *build_clev1i_ilv1d(OUT lev1id *lev1i, lev1_decl_t *ilv1d, char **ilv2np, lv1_cont *l1lsnd) {
    strcpy(lev1i->supe_lv2pn, ilv1d->lv2pn);
    strcpy(lev1i->crea_lev1n, ilv1d->ident);
    //
    char *last_str = lev1i->inhe_lev1i;
    for (; ilv2np[0x00]; ++ilv2np) {
        last_str = lscpy(last_str, ilv2np[0x00]);
        last_str = lccpy(last_str, ':');
    }
    lscpy(last_str, ilv1d->ident);
    // strcpy(lev1i->inne_fmtsp_oi, ilv1d->innep.inne_fmtsp);
    lev1i->oivk_retyp_oi = l1lsnd->oivk_retyp_oc;
    strcpy(lev1i->oivk_fmtsp_oi, l1lsnd->oivk_fmtsp_oc);
    lev1i->oivk_size_oi = l1lsnd->oivk_size_oc;
    //
    return lev1i;
}

//

static void echo_random_lev1(char *librn) {
    static osv_atomic_t tatol;
    librn = lscpy(librn, "lev1_");
    snprintf(librn, MAX_PATH, "%u-%lu", (uint32) time(NULL), OSV_ATOMIC_ADD_FETCH(&tatol, 0x01));
}

void librn_decla_lev1(char *librn, lev1_meta *lev1m) {
    librn = lscpy(librn, lev1m->lv2pn);
    librn = lccpy(librn, '_');
    librn = lscpy(librn, lev1m->lev1n);
    librn = lccpy(librn, '_');
    librn = lscpy(librn, lev1m->oivk_fmtsp_om);
    librn = lccpy(librn, '_');
    echo_random_lev1(librn);
}

void librn_metho_lev1(char *librn, lev1_meta *lev1m) {
    librn = lscpy(librn, lev1m->lv2pn);
    librn = lccpy(librn, '_');
    librn = lscpy(librn, lev1m->lev1n);
    librn = lccpy(librn, '_');
    echo_random_lev1(librn);
}

void librn_clasn_lev1(char *librn, char *lv2pn) {
    librn = lscpy(librn, lv2pn);
    librn = lccpy(librn, '_');
    echo_random_lev1(librn);
}

void librn_whole_lev1(char *librn) {
    librn = lscpy(librn, "whole_");
    echo_random_lev1(librn);
}

//

static void echo_random_lv2p(char *librn) {
    static osv_atomic_t tatol;
    librn = lscpy(librn, "lv2p_");
    snprintf(librn, MAX_PATH, "%u-%lu", (uint32) time(NULL), OSV_ATOMIC_ADD_FETCH(&tatol, 0x01));
}

void librn_clasn_lv2p(char *librn, char *lv2pn) {
    librn = lscpy(librn, lv2pn);
    librn = lccpy(librn, '_');
    echo_random_lv2p(librn);
}

void librn_whole_lv2p(char *librn) {
    librn = lscpy(librn, "whole_");
    echo_random_lv2p(librn);
}

//



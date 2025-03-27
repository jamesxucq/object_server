#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_directory.h"
#include "kcstr_utili.h"
#include "trans/trans_utili.h"
#include "lv2p_decla.h"
#include "debug_funct_co.h"

//

#define CLIST_APPEND(head, add) { \
    LDECLTYPE(head) _tmp; \
    if (head) { \
        _tmp = head; \
        while (_tmp->next) _tmp = _tmp->next; \
        _tmp->next = add; \
    } else head = add; \
}

lv1_cont *appe_l1clst_new(lv1_cont **l1clsth) {
    lv1_cont *l1lsnd = (lv1_cont *) malloc(sizeof (lv1_cont));
    if (!l1lsnd) return NULL;
    // memset(l1lsnd, '\0', sizeof (lv1_cont));
    l1lsnd->next = NULL;
    //
    CLIST_APPEND(*l1clsth, l1lsnd);
    return l1lsnd;
}

lv1_cont *appe_l1clst_conte(lv1_cont **l1clsth, char *lev1_cont) {
    lv1_cont *l1lsnd = (lv1_cont *) malloc(sizeof (lv1_cont));
    if (!l1lsnd) return NULL;
    // memset(l1lsnd, '\0', sizeof (lv1_cont));
    l1lsnd->next = NULL;
    //
    CLIST_APPEND(*l1clsth, l1lsnd);
    strcpy(l1lsnd->conte, lev1_cont);
    return l1lsnd;
}

// taat<[xx=8 int, ax int], ttt(), [cx int] auto, teet:tpp(ax), tst(xx, cx), tpp(ax)>;
// user <[user_name char(32), password char(32), salt char(16), role_obid char(96)]>;

int parse_lv2pd_decla(lv2p_decl_t *lv2dt, char *lv2_dec) {
    // OSEVPF("[FUNC]:parse_lv2pd_decla.\n");
    char *detok = split_lv2pn(lv2dt->lv2pn, lv2_dec);
    if (!detok) return -1;
    if (parse_class_meta(lv2dt->lv2nod, detok))
        return -1;
    // OSEVPF("detok:|%s|\n", detok);
    unsigned int inde = 0x00;
    lev1_decl_t *lv1d = lv2dt->meth;
    for (; (LEVO_COUNT > inde) && (detok = parse_lev1d_node(lv1d, detok)); ++inde, ++lv1d) {
        strcpy(lv1d->lv2pn, lv2dt->lv2pn);
        split_inher_clasn(lv1d->inhe_lv2n, lv1d->_cline_);
        // OSEVPF("--- inhe_lv2n:|%s| ident:|%s|\n", lv1d->inhe_lv2n[0x00], lv1d->ident);
        filli_inner_parms(&lv1d->innep, lv2dt->lv2nod);
        // OSEVPF("fmtst:|%s|\n", lv1d->innep.inne_fmtsp);
    }
    lv1d->levtyp = LVTP_TYPE_NONE;
    //
    return 0x00;
}

// <[xx=8 int, ax int], ttt(), [cx int] auto, teet:tpp(ax), tst(xx, cx), tpp(ax)>;
// <[user_name char(32), password char(32), salt char(16), role_obid char(96)]>;

int parse_lv2pd_nonam(lv2p_decl_t *lv2dt, char *lv2_dec) {
    // OSEVPF("[FUNC]:parse_lv2pd_nonam.\n");
    lv2dt->lv2pn[0x00] = '\0';
    char *detok = pass_blank(lv2_dec);
    if (!detok) return -1;
    if (parse_class_meta(lv2dt->lv2nod, detok))
        return -1;
    // OSEVPF("detok:|%s|\n", detok);
    unsigned int inde = 0x00;
    lev1_decl_t *lv1d = lv2dt->meth;
    for (; (LEVO_COUNT > inde) && (detok = parse_lev1d_node(lv1d, detok)); ++inde, ++lv1d) {
        strcpy(lv1d->lv2pn, lv2dt->lv2pn);
        split_inher_clasn(lv1d->inhe_lv2n, lv1d->_cline_);
        // OSEVPF("--- inhe_lv2n:|%s| ident:|%s|\n", lv1d->inhe_lv2n[0x00], lv1d->ident);
        filli_inner_parms(&lv1d->innep, lv2dt->lv2nod);
        // OSEVPF("fmtst:|%s|\n", lv1d->innep.inne_fmtsp);
    }
    lv1d->levtyp = LVTP_TYPE_NONE;
    //
    return 0x00;
}

//

int parse_lv2pd_clasp(lv2p_decl_t *lv2dt, char *lv2d_path) {
    OSEVPF("[FUNC]:parse_lv2pd_clasp\n");
    char lv2p_cont[CLANG_CONTE_SIZE];
    if (!load_data(lv2p_cont, CLANG_CONTE_SIZE, lv2d_path))
        return -1;
    char lv2_dec[LARGE_TEXT_SIZE];
    if (!split_class_conte(lv2_dec, lv2p_cont))
        return -1;
    if (parse_lv2pd_decla(lv2dt, lv2_dec))
        return -1;
    return 0x00;
}

int parse_lv2pd_clasn(lv2p_decl_t *lv2dt, char *basen, char *lv2pn) {
    OSEVPF("[FUNC]:parse_lv2pd_clasn\n");
    char lv2d_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2d_path, basen, lv2pn);
    //
    char lv2p_cont[CLANG_CONTE_SIZE];
    if (!load_data(lv2p_cont, CLANG_CONTE_SIZE, lv2d_path))
        return -1;
    char lv2_dec[LARGE_TEXT_SIZE];
    if (!split_class_conte(lv2_dec, lv2p_cont))
        return -1;
    if (parse_lv2pd_decla(lv2dt, lv2_dec))
        return -1;
    return 0x00;
}

//

int build_lv2pd_clasp(lv2p_decl_t *lv2dt, char *lv2p_path, char *basen) {
    OSEVPF("[FUNC]:build_lv2pd_clasp\n");
    char lv2p_cont[CLANG_CONTE_SIZE];
    if (!load_data(lv2p_cont, CLANG_CONTE_SIZE, lv2p_path))
        return -1;
    char lv2_dec[LARGE_TEXT_SIZE];
    if (!split_class_conte(lv2_dec, lv2p_cont))
        return -1;
    if (parse_lv2pd_decla(lv2dt, lv2_dec))
        return -1;
    //
    char lv2d_path[MAX_PATH * 3];
    lev1_decl_t *lv1d = lv2dt->meth;
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        if (LVTP_LVTP_LEVO == lv1d->levtyp) {
            LVTP_DECLA_FILE(lv2d_path, basen, lv1d->ident);
            if (CLASS_EXIST(lv2d_path)) {
                lv1d->levtyp = LVTP_INHE_LEVO;
            } else lv1d->levtyp = LVTP_INHE_LVTP;
        } else if (LVTP_TYPE_EXCE == lv1d->levtyp)
            return -1;
    }
    return 0x00;
}

int build_lv2pd_clasn(lv2p_decl_t *lv2dt, char *basen, char *lv2pn) {
    OSEVPF("[FUNC]:build_lv2pd_clasn\n");
    char lv2d_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2d_path, basen, lv2pn);
    //
    char lv2p_cont[CLANG_CONTE_SIZE];
    if (!load_data(lv2p_cont, CLANG_CONTE_SIZE, lv2d_path))
        return -1;
    char lv2_dec[LARGE_TEXT_SIZE];
    if (!split_class_conte(lv2_dec, lv2p_cont))
        return -1;
    if (parse_lv2pd_decla(lv2dt, lv2_dec))
        return -1;
    //
    lev1_decl_t *lv1d = lv2dt->meth;
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        if (LVTP_LVTP_LEVO == lv1d->levtyp) {
            LVTP_DECLA_FILE(lv2d_path, basen, lv1d->ident);
            if (CLASS_EXIST(lv2d_path)) {
                lv1d->levtyp = LVTP_INHE_LEVO;
            } else lv1d->levtyp = LVTP_INHE_LVTP;
        } else if (LVTP_TYPE_EXCE == lv1d->levtyp)
            return -1;
    }
    return 0x00;
}

// 

int build_lv2pd_conte(lv2p_decl_t *lv2dt, char *lv2_dec, char *basen) {
    OSEVPF("[FUNC]:build_lv2pd_conte\n");
    if (valid_lv2pd_conte(lv2_dec))
        return -1;
    if (parse_lv2pd_decla(lv2dt, lv2_dec))
        return -1;
    // OSEVPF("1 lv2dt --------\n");
    // PRIN_lv2pd_debug(lv2dt);
    char lv2d_path[MAX_PATH * 3];
    lev1_decl_t *lv1d = lv2dt->meth;
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        PRIN_lev1d_debug(lv1d);
        if (LVTP_LVTP_LEVO == lv1d->levtyp) {
            LVTP_DECLA_FILE(lv2d_path, basen, lv1d->ident);
            if (CLASS_EXIST(lv2d_path)) {
                lv1d->levtyp = LVTP_INHE_LEVO;
            } else lv1d->levtyp = LVTP_INHE_LVTP;
        } else if (LVTP_TYPE_EXCE == lv1d->levtyp)
            return -1;
    }
    OSEVPF("2 lv2dt --------\n");
    PRIN_lv2pd_debug(lv2dt);
    return 0x00;
}

int build_lv2pd_nonam(lv2p_decl_t *lv2dt, char *lv2_dec, char *basen) {
    // OSEVPF("[FUNC]:build_lv2pd_nonam\n");
    if (valid_lv2pd_nonam(lv2_dec))
        return -1;
    if (parse_lv2pd_nonam(lv2dt, lv2_dec))
        return -1;
    // OSEVPF("1 lv2dt --------\n");
    PRIN_lv2pd_debug(lv2dt);
    char lv2d_path[MAX_PATH * 3];
    lev1_decl_t *lv1d = lv2dt->meth;
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        PRIN_lev1d_debug(lv1d);
        if (LVTP_LVTP_LEVO == lv1d->levtyp) {
            LVTP_DECLA_FILE(lv2d_path, basen, lv1d->ident);
            if (CLASS_EXIST(lv2d_path)) {
                lv1d->levtyp = LVTP_INHE_LEVO;
            } else lv1d->levtyp = LVTP_INHE_LVTP;
        } else if (LVTP_TYPE_EXCE == lv1d->levtyp)
            return -1;
    }
    OSEVPF("2 lv2dt --------\n");
    PRIN_lv2pd_debug(lv2dt);
    return 0x00;
}

//

lv2p_prop *find_lv2p_prop(lv2p_prop *lv2_nod, lv2p_prop *lv2d) {
    for (; ACCE_COTRL_INVAL != lv2_nod->access; ++lv2_nod) {
        if (!strcmp(lv2d->name, lv2_nod->name) && (lv2d->potyp == lv2_nod->potyp))
            return lv2_nod;
    }
    return NULL;
}

//

void copy_lv2p_prop(lv2p_prop *l2_nod, lv2p_prop *lv2nod) {
    // OSEVPF("[FUNC]:copy_lv2p_prop\n");
    for (; ACCE_COTRL_INVAL != lv2nod->access; ++lv2nod, ++l2_nod) {
        memcpy(l2_nod, lv2nod, sizeof (lv2p_prop));
        // OSEVPF("1 l2_nod->decla:|%s| type:|%s| colu_data->name:|%s|\n", lv2nod->decla, lv2nod->xxxxxtype, lv2nod->name);
    }
    l2_nod->access = ACCE_COTRL_INVAL;
}

//

//

static char *have_define(char *stri) {
    while (' ' == stri[0x00]) ++stri;
    if ('{' == stri[0x00]) return stri;
    return NULL;
}

//

static char *pass_define(char *stri) {
    int tok_num = 0x00;
    for (; (stri = strpbrk(stri, "{}")); ++stri) {
        if ('{' == stri[0x00]) ++tok_num;
        else if ('}' == stri[0x00]) --tok_num;
        if (!tok_num) break;
    }
    return ++stri;
}

//

static char *find_defin_decla(char *lvnsps, char *lv2p_cont) {
    char *tokep, *toksp;
    toksp = strchr(lv2p_cont, '<');
    if (!toksp) return NULL;
    tokep = strchr(toksp + 0x01, '>');
    if (!tokep) return NULL;
    strzcpy(lvnsps, lv2p_cont, toksp - lv2p_cont);
    if (!have_define(tokep + 0x01)) return ++tokep;
    return pass_define(tokep + 0x01);
}

//

char *find_defin_decla_ext(char *lvnsps, char *lev1_invk, char *lv2p_cont) {
    char *tokep, *toksp;
    toksp = strchr(lv2p_cont, '<');
    if (!toksp) return NULL;
    tokep = strchr(toksp + 0x01, '>');
    if (!tokep) return NULL;
    strzcpy(lvnsps, lv2p_cont, toksp - lv2p_cont);
    strzcpy(lev1_invk, toksp, tokep - toksp + 0x01);
    if (!have_define(tokep + 0x01)) return ++tokep;
    return pass_define(tokep + 0x01);
}

// trans-serve

char *split_class_conte(char *lv2_dec, char *lv2p_cont) {
    char *tokep, *toksp;
    char lvnsps[LVTN_LENGTH];
    //
    if (!(toksp = kill_inval(lv2p_cont)))
        return NULL;
    tokep = find_defin_decla(lvnsps, toksp);
    while (tokep) {
        if (!l1nsps_delim(lvnsps)) {
            strzcpy(lv2_dec, toksp, tokep - toksp);
            break;
        }
        if (!(toksp = kill_inval(tokep)))
            return NULL;
        tokep = find_defin_decla(lvnsps, toksp);
    }
    //
    return tokep;
}

char *split_metho_decla(char *lv2p_cont) {
    char *tokep, *toksp;
    char lvnsps[LVTN_LENGTH];
    //
    if (!(toksp = kill_inval(lv2p_cont)))
        return NULL;
    tokep = find_defin_decla(lvnsps, toksp);
    while (tokep) {
        if (!l1nsps_delim(lvnsps)) break;
        //
        if (!(toksp = kill_inval(tokep)))
            return NULL;
        tokep = find_defin_decla(lvnsps, toksp);
    }
    //
    return tokep;
}

//

int parse_lev2p_prope(OUT lv2p_prop *lv2nod, char *basen, char *lv2pn) {
    OSEVPF("[FUNC]:parse_lev2p_prope\n");
    // OSEVPF("[FUNC]:base:|%s| lv2pn:|%s|\n", basen, lv2pn);
    char lv2d_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2d_path, basen, lv2pn);
    //
    char lv2p_cont[CLANG_CONTE_SIZE];
    if (!load_data(lv2p_cont, CLANG_CONTE_SIZE, lv2d_path))
        return -1;
    char lv2_dec[LARGE_TEXT_SIZE];
    if (!split_class_conte(lv2_dec, lv2p_cont))
        return -1;
    if (parse_class_meta(lv2nod, lv2_dec))
        return -1;
    return 0x00;
}

//

int filli_inner_parms(lev1_inne_t *innep, lv2p_prop *lv2nod) {
    // OSEVPF("[FUNC]:filli_inner_parms, innep->_iline_:|%s|\n", innep->_iline_);
    split_inner_parms(innep->inne_pams, innep->_iline_);
    // OSEVPF("innep->inne_pams, [0x00]:|%s| [0x01]:|%s| [0x02]:|%s|\n", innep->inne_pams[0x00], innep->inne_pams[0x01], innep->inne_pams[0x02]);
    char **pamvp = innep->inne_pams;
    innep->inne_count = 0x00;
    for (; pamvp[0x00]; ++pamvp, ++innep->inne_count);
    // OSEVPF("innep->inne_count:%d\n", innep->inne_count);
    lv2pd_ibind_fmtsp(innep->inne_fmtsp, lv2nod, innep->inne_pams);
    // OSEVPF("[FUNC]:filli_inner_parms end, innep->inne_fmtsp:|%s|\n", innep->inne_fmtsp);
    return 0x00;
}
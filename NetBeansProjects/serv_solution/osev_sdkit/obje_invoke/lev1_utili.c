
#include "commo_header.h"
#include "kcomm_header.h"

#include "trans/trans_utili.h"
#include "lev1_utili.h"

//

lev1_decl_t *parse_lev1_decla(lev1_decl_t *lv1d, char *lv2p_decl) {
    // OSEVPF("parse_lv2pd_decla.\n");
    char lv2pn[LVTN_LENGTH];
    char *detok = split_lv2pn(lv2pn, lv2p_decl);
    if (!detok) return NULL;
    lv2p_prop lv2nod[LVTNOD_COUNT];
    if (parse_class_meta(lv2nod, detok))
        return NULL;
    // OSEVPF("detok:|%s|\n", detok);
    unsigned int inde = 0x00;
    for (; (LEVO_COUNT > inde) && (detok = parse_lev1d_node(lv1d, detok)); ++inde, ++lv1d) {
        strcpy(lv1d->lv2pn, lv2pn);
        split_inher_clasn(lv1d->inhe_lv2n, lv1d->_cline_);
        // OSEVPF("--- lv2pn:|%s| ident:|%s|\n", lv1d->lv2pn, lv1d->ident);
        filli_inner_parms(&lv1d->innep, lv2nod);
        // OSEVPF("--- lv1d->innep.inne_fmtsp:|%s|\n", lv1d->innep.inne_fmtsp);
    }
    lv1d->levtyp = LVTP_TYPE_NONE;
    //
    return lv1d;
}

int parse_lev1d_clasp(lev1_decl_t *lev1d, char *lv2d_path) {
    // OSEVPF("[FUNC]:parse_lev1d_clasp\n");
    char lv2p_cont[OSLAN_CONTE_SIZE];
    if (!load_data(lv2p_cont, OSLAN_CONTE_SIZE, lv2d_path))
        return -1;
    char lv2p_decl[LARGE_TEXT_SIZE];
    if (!split_class_conte(lv2p_decl, lv2p_cont))
        return -1;
    if (!parse_lev1_decla(lev1d, lv2p_decl))
        return -1;
    return 0x00;
}

int parse_lev1d_clasn(lev1_decl_t *lev1d, char *basen, char *lv2pn) {
    // OSEVPF("[FUNC]:parse_lev1d_clasn\n");
    char lv2d_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2d_path, basen, lv2pn);
    //
    char lv2p_cont[OSLAN_CONTE_SIZE];
    if (!load_data(lv2p_cont, OSLAN_CONTE_SIZE, lv2d_path))
        return -1;
    char lv2p_decl[LARGE_TEXT_SIZE];
    if (!split_class_conte(lv2p_decl, lv2p_cont))
        return -1;
    if (!parse_lev1_decla(lev1d, lv2p_decl))
        return -1;
    return 0x00;
}

int build_lev1d_clasp(lev1_decl_t *lev1d, char *lv2p_path, char *basen) {
    // OSEVPF("[FUNC]:build_lev1d_clasp\n");
    char lv2p_cont[OSLAN_CONTE_SIZE];
    if (!load_data(lv2p_cont, OSLAN_CONTE_SIZE, lv2p_path))
        return -1;
    char lv2p_decl[LARGE_TEXT_SIZE];
    if (!split_class_conte(lv2p_decl, lv2p_cont))
        return -1;
    if (!parse_lev1_decla(lev1d, lv2p_decl))
        return -1;
    //
    char lv2d_path[MAX_PATH * 3];
    lev1_decl_t *lv1d = lev1d;
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        if (LVTP_LVTP_LEVO == lv1d->levtyp) {
            LVTP_DECLA_FILE(lv2d_path, basen, lev1d->ident);
            if (CLASS_EXIST(lv2d_path)) {
                lv1d->levtyp = LVTP_INHE_LEVO;
            } else lv1d->levtyp = LVTP_INHE_LVTP;
        } else if (LVTP_TYPE_EXCE == lv1d->levtyp) return -1;
    }
    return 0x00;
}

int build_lev1d_clasn(lev1_decl_t *lev1d, char *basen, char *lv2pn) {
    // OSEVPF("[FUNC]:build_lev1d_clasn\n");
    char lv2d_path[MAX_PATH * 3];
    LVTP_DECLA_FILE(lv2d_path, basen, lv2pn);
    //
    char lv2p_cont[OSLAN_CONTE_SIZE];
    if (!load_data(lv2p_cont, OSLAN_CONTE_SIZE, lv2d_path))
        return -1;
    char lv2p_decl[LARGE_TEXT_SIZE];
    if (!split_class_conte(lv2p_decl, lv2p_cont))
        return -1;
    if (!parse_lev1_decla(lev1d, lv2p_decl))
        return -1;
    //
    lev1_decl_t *lv1d = lev1d;
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        if (LVTP_LVTP_LEVO == lv1d->levtyp) {
            LVTP_DECLA_FILE(lv2d_path, basen, lev1d->ident);
            if (CLASS_EXIST(lv2d_path)) {
                lv1d->levtyp = LVTP_INHE_LEVO;
            } else lv1d->levtyp = LVTP_INHE_LVTP;
        } else if (LVTP_TYPE_EXCE == lv1d->levtyp)
            return -1;
    }
    return 0x00;
}

//

/*
    lev1_cont = taat:tpp<(x int), (a int)int> {f=x int; p=a int; if(f) {return 0x01;} return 0x00;}
    style = HAVE_CLASN|HAVE_METHN|HAVE_DECLA|HAVE_BODY
    lv2pn = taat
    lev1n = tpp
    decla = <(x int), (a int)int>
    body = {f=x int; p=a int; if(f) {return 0x01;} return 0x00;}
 */
static int parse_lev1_conte(lev1_meta *lev1m, char *lev1_cont) {
    lev1m->layout = 0x00;
    char *toksp;
    PASS_TBLANK(toksp, lev1_cont)
            char *tokep = strchr(toksp + 0x01, ':');
    if (!tokep) {
        if (LVTN_LENGTH <= strlen(toksp))
            return -1;
        STRCPY(lev1m->lv2pn, toksp);
        lev1m->layout |= HAVE_CLASN;
        return 0x00;
    }
    if (LVTN_LENGTH <= (tokep - toksp))
        return -1;
    STRZCPY(lev1m->lv2pn, toksp, tokep - toksp);
    lev1m->layout |= HAVE_CLASN;
    //
    toksp = strpbrk(tokep + 0x01, "< ");
    if (!toksp) {
        if (LVON_LENGTH <= strlen(++tokep))
            return -1;
        STRCPY(lev1m->lev1n, tokep);
        lev1m->layout |= HAVE_METHN;
        return 0x00;
    }
    if (LVON_LENGTH <= (toksp - (++tokep)))
        return -1;
    STRZCPY(lev1m->lev1n, tokep, toksp - tokep);
    lev1m->layout |= HAVE_METHN;
    //
    if ('<' != toksp[0x00]) toksp = strchr(toksp + 0x01, '<');
    if (!toksp) return 0x00;
    tokep = strchr(toksp + 0x01, '>');
    if (!tokep) return -1;
    if (LVOD_LENGTH <= ((++tokep) - toksp + 0x01))
        return -1;
    strzcpy(lev1m->decla, toksp, tokep - toksp);
    lev1m->layout |= HAVE_DECLA;
    //
    lev1m->body = pass_blank(tokep);
    if (lev1m->body) lev1m->layout |= HAVE_BODY;
    return 0x00;
}

/*
    lev1_iden = taat:tpp(a int, int)
    style = HAVE_CLASN|HAVE_METHN|HAVE_DECLA
    clasn = taat
    lev1n = tpp
    decla = (a int, int)
    body = 
 */

static int parse_metho_ident(lev1_meta *lev1m, char *lev1_iden) {
    // OSEVPF("parse_metho_ident\n");
    lev1m->layout = 0x00;
    char *toksp;
    PASS_TBLANK(toksp, lev1_iden)
            char *tokep = strchr(toksp + 0x01, ':');
    if (!tokep) {
        STRCPY(lev1m->lv2pn, toksp);
        lev1m->layout |= HAVE_CLASN;
        return 0x00;
    }
    STRZCPY(lev1m->lv2pn, toksp, tokep - toksp);
    lev1m->layout |= HAVE_CLASN;
    //
    toksp = strpbrk(tokep + 0x01, "( ");
    if (!toksp) {
        STRCPY(lev1m->lev1n, tokep + 0x01);
        lev1m->layout |= HAVE_METHN;
        return 0x00;
    }
    STRZCPY(lev1m->lev1n, tokep + 0x01, toksp - tokep - 0x01);
    lev1m->layout |= HAVE_METHN;
    //
    if ('(' != toksp[0x00]) toksp = strchr(toksp + 0x01, '(');
    if (!toksp) return 0x00;
    tokep = strchr(toksp + 0x01, ')');
    if (!tokep) return -1;
    strzcpy(lev1m->decla, toksp, tokep - toksp + 0x01);
    lev1m->layout |= HAVE_DECLA;
    //
    return 0x00;
}

// lev1_iden = int taat
// lev1_iden = int taat:tpp
// lev1_iden = int taat:tpp<(x int), (a int)int>
// lev1_iden = int taat:tpp(a int, int)

int build_metho_ident(lev1_meta *lev1m, char *lev1_iden) {
    int spli_valu;
    if (strchr(lev1_iden, '<')) {
        spli_valu = parse_lev1_conte(lev1m, lev1_iden);
    } else spli_valu = parse_metho_ident(lev1m, lev1_iden);
    //
    if (!spli_valu && (HAVE_DECLA & lev1m->layout)) {
        if (0x00 > (lev1m->oivk_retyp_om = conv_oinvk_retyp(lev1m->decla)))
            return -1;
        if (conv_oinvk_fmtsp(lev1m->oivk_fmtsp_om, lev1m->decla))
            return -1;
        lev1m->oivk_size_om = count_pamik_size(lev1m->oivk_fmtsp_om);
        if (0x00 > lev1m->oivk_size_om)
            return -1;
    }
    //
    return spli_valu;
}

//

int parse_metho_conte(lev1_meta *lev1m, char *lev1_cont) {
    int spli_valu = parse_lev1_conte(lev1m, lev1_cont);
    if (!spli_valu && (HAVE_DECLA & lev1m->layout)) {
        if (0x00 > (lev1m->oivk_retyp_om = conv_oinvk_retyp(lev1m->decla)))
            return -1;
        if (conv_oinvk_fmtsp(lev1m->oivk_fmtsp_om, lev1m->decla))
            return -1;
        lev1m->oivk_size_om = count_pamik_size(lev1m->oivk_fmtsp_om);
        if (0x00 > lev1m->oivk_size_om)
            return -1;
    }
    //
    return spli_valu;
}

// trans-serve

int build_metho_conte(lev1_meta *lev1m, char *lev1_cont) {
    // if (!strchr(lev1_cont, '<')) return -1;
    if (valid_lev1_conte(lev1_cont))
        return -1;
    //
    int spli_valu = parse_lev1_conte(lev1m, lev1_cont);
    if (!spli_valu && (HAVE_DECLA & lev1m->layout)) {
        if (0x00 > (lev1m->oivk_retyp_om = conv_oinvk_retyp(lev1m->decla)))
            return -1;
        if (conv_oinvk_fmtsp(lev1m->oivk_fmtsp_om, lev1m->decla))
            return -1;
        lev1m->oivk_size_om = count_pamik_size(lev1m->oivk_fmtsp_om);
        if (0x00 > lev1m->oivk_size_om)
            return -1;
    }
    //
    return spli_valu;
}

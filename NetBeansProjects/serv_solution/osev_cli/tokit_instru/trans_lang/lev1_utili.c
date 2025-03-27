
#include "tstri_utili.h"

#include "lev1_decla.h"
#include "trans_utili.h"

#include "lev1_utili.h"

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

// trans-serve

int parse_metho_conte(lev1_meta *lev1m, char *lev1_cont) {
    if (!strchr(lev1_cont, '<')) return -1;
    //
    int spli_valu = parse_lev1_conte(lev1m, lev1_cont);
    if (!spli_valu && (HAVE_DECLA & lev1m->layout)) {
        if (conv_oinvk_ident(lev1m->oivk_fmtsp_om, lev1m->decla))
            return -1;
    }
    //
    return spli_valu;
}

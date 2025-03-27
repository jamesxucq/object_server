#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "commo_header.h"
#include "kstri_utili.h"

//

static inline char *have_define(char *stri) {
    while (' ' == stri[0x00]) ++stri;
    if ('{' == stri[0x00])
        return stri;
    return NULL;
}

static inline char *pass_define(char *stri) {
    int tok_num = 0x00;
    char *detok = stri;
    for (; (detok = strpbrk(detok, "{}")); ++detok) {
        if ('{' == detok[0x00]) ++tok_num;
        else if ('}' == detok[0x00]) --tok_num;
        if (!tok_num) break;
    }
    //
    return ++detok;
}

//

static inline char *pass_declare(char *stri) {
    while (' ' == stri[0x00]) ++stri;
    if (';' == stri[0x00])
        return ++stri;
    return stri;
}

char *find_metho_decla(char *l1nsps, char *lv2p_cont) {
    // printf("[FUNC]:find_metho_decla\n");
    char *tokep, *toksp;
    //
    toksp = strchr(lv2p_cont, '<');
    if (!toksp) return NULL;
    tokep = strchr(toksp + 0x01, '>');
    if (!tokep) return NULL;
    strzcpy(l1nsps, lv2p_cont, toksp - lv2p_cont);
    //
    tokep = strchr(tokep + 0x01, ';');
    if (!tokep) return NULL;
    return ++tokep;
}

//

char *find_metho_defin(char *l1nsps, char *lv2p_cont) {
    char *tokep, *toksp;
    toksp = strchr(lv2p_cont, '<');
    if (!toksp) return NULL;
    tokep = strchr(toksp + 0x01, '>');
    if (!tokep) return NULL;
    strzcpy(l1nsps, lv2p_cont, toksp - lv2p_cont);
    if (!have_define(tokep + 0x01))
        return NULL;
    return pass_define(tokep + 0x01);
}

//

static char *find_defin_decla(char *lvnsps, char *lv2p_cont) {
    char *tokep, *toksp;
    toksp = strchr(lv2p_cont, '<');
    if (!toksp) return NULL;
    tokep = strchr(toksp + 0x01, '>');
    if (!tokep) return NULL;
    strzcpy(lvnsps, lv2p_cont, toksp - lv2p_cont);
    if (!have_define(tokep + 0x01))
        return ++tokep;
    return pass_define(tokep + 0x01);
}

//

char *next_conte_type(char *line_cont, unsigned int *line_type, char *lv2p_cont) {
    char lvnsps[LVTN_LENGTH];
    char *cotoksp = kill_semic(lv2p_cont);
    if (!cotoksp) return NULL;
    //
    char *cotokep = strchr(cotoksp, '<');
    if (!cotokep) return NULL;
    strzcpy(lvnsps, cotoksp, cotokep - cotoksp);
    cotokep = strchr(cotokep + 0x01, '>');
    if (!cotokep) return NULL;
    ++cotokep;
    //
    if (l1nsps_delim(lvnsps)) {
        if (have_define(cotokep)) {
            line_type[0x00] = TYPE_LEVO_CONTE;
            cotokep = pass_define(cotokep);
        } else {
            line_type[0x00] = TYPE_LVTP_CONTE;
            cotokep = pass_declare(cotokep);
        }
    } else line_type[0x00] = TYPE_LVTP_DEFINE;
    //
    strzcpy(line_cont, cotoksp, cotokep - cotoksp);
    return cotokep;
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

//
static osv_str_t UTIL_LIST_LEVO = osv_stri("LEVO");
static osv_str_t UTIL_LIST_LVTP = osv_stri("LVTP");

static inline unsigned int list_type_valu(char *list_type) {
    if (!strncmp(UTIL_LIST_LEVO.data, list_type, UTIL_LIST_LEVO.slen))
        return KLST_LVTP_ATTRIB | KLST_LVTP_EXPAND | KLST_LEVO_CONTE;
    else if (!strncmp(UTIL_LIST_LVTP.data, list_type, UTIL_LIST_LVTP.slen))
        return KLST_LVTP_ATTRIB | KLST_LVTP_EXPAND | KLST_LVTP_CONTE;
    //
    return 0x00;
}

//

unsigned int build_klist_type(char *list_type) {
    // OSEVPF("[FUNC]:build_list_type.\n");
    if (!list_type)
        return KLST_LVTP_ATTRIB | KLST_LVTP_EXPAND | KLST_LEVO_CONTE | KLST_LVTP_CONTE;
    quote_decode(list_type);
    //
    int klval = 0x00;
    list_type = pass_blank(list_type);
    // OSEVPF("list_type:|%s|\n", list_type);
    klval |= list_type_valu(list_type);
    while ((list_type = strchr(list_type, '|'))) {
        list_type = pass_blank(++list_type);
        // OSEVPF("list_type:|%s|\n", list_type);
        klval |= list_type_valu(list_type);
    }
    //
    return klval;
}

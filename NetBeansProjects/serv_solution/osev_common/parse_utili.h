
/* 
 * File:   parse_utili.h
 * Author: James Xu
 *
 * Created on 2017.1.23, PM 3:38
 */

#ifndef PARSE_UTILI_H
#define PARSE_UTILI_H

#include "utility/last_stri.h"

#ifdef __cplusplus
extern "C" {
#endif

    // char *split_space(char *lv2pn, char *lev1n, char *space);

    inline char *split_space(char *lv2pn, char *lev1n, char *space) {
        char *toksp;
        PASS_TBLANK(toksp, space)
                char *tokep = strchr(toksp + 0x01, ':');
        if (!tokep) return NULL;
        strzcpy(lv2pn, toksp, tokep - toksp);
        strcpy(lev1n, tokep + 0x01);
        //
        return lv2pn;
    }

    // char *split_lev1n(char *lev1n, char *parsen, char *lev1_cont);

    inline char *split_lev1n(char *lev1n, char *parsen, char *lev1_cont) {
        char *cotok = strchr(lev1_cont, ':');
        if (!cotok) return NULL;
        strcpy(lev1n, cotok + 0x01);
        parsen = lscpy(parsen, "p_");
        lscpy(parsen, lev1n);
        return lev1n;
    }

    // char *split_clasn(char *lv2pn, char *space);

    inline char *split_clasn(char *lv2pn, char *space) {
        char *toksp;
        PASS_TBLANK(toksp, space)
                char *tokep = strpbrk(toksp, " <");
        if (!tokep) return NULL;
        strzcpy(lv2pn, toksp, tokep - toksp);
        return lv2pn;
    }

#ifdef __cplusplus
}
#endif

#endif /* PARSE_UTILI_H */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utility/last_stri.h"
#include "utility/stcstr.h"
#include "commo_macro.h"
#include "osev_datyp.h"
#include "osev_macro.h"
#include "stri_utili.h"

//

char *get_attval(char *valu, char *attstr, osv_str_t *alab) {
    char *toksp, *tokep;
    //
    toksp = strstr(attstr, alab->data);
    if (!toksp) return NULL;
    toksp = strchr(alab->slen + toksp, '=');
    if (!toksp) return NULL;
    ++toksp;
    PASS_BLANK(toksp)
    if ('"' == toksp[0x00]) {
        ++toksp;
        tokep = strchr(toksp, '"');
        if (!tokep) return NULL;
    } else FIND_TBLANK(tokep, toksp)
        strzcpy(valu, toksp, tokep - toksp);
    //
    return valu;
}

//

char *get_attval2(char *valu1, char *valu2, char *attstr, osv_str_t *alab1, osv_str_t *alab2) {
    char *toksp, *tokep;
    //
    toksp = strstr(attstr, alab1->data);
    if (!toksp) return NULL;
    toksp = strchr(alab1->slen + toksp, '=');
    if (!toksp) return NULL;
    ++toksp;
    PASS_BLANK(toksp)
    if ('"' == toksp[0x00]) {
        ++toksp;
        tokep = strchr(toksp, '"');
        if (!tokep) return NULL;
    } else FIND_TBLANK(tokep, toksp)
        strzcpy(valu1, toksp, tokep - toksp);
    //
    toksp = strstr(++tokep, alab2->data);
    if (!toksp) return NULL;
    toksp = strchr(alab2->slen + toksp, '=');
    if (!toksp) return NULL;
    ++toksp;
    PASS_BLANK(toksp)
    if ('"' == toksp[0x00]) {
        ++toksp;
        tokep = strchr(toksp, '"');
        if (!tokep) return NULL;
    } else FIND_TBLANK(tokep, toksp)
        strzcpy(valu2, toksp, tokep - toksp);
    //
    return valu1;
}

//

char *get_attval3(char *valu1, char *valu2, char *valu3, char *attstr, osv_str_t *alab1, osv_str_t *alab2, osv_str_t *alab3) {
    char *toksp, *tokep;
    //
    toksp = strstr(attstr, alab1->data);
    if (!toksp) return NULL;
    toksp = strchr(alab1->slen + toksp, '=');
    if (!toksp) return NULL;
    ++toksp;
    PASS_BLANK(toksp)
    if ('"' == toksp[0x00]) {
        ++toksp;
        tokep = strchr(toksp, '"');
        if (!tokep) return NULL;
    } else FIND_TBLANK(tokep, toksp)
        strzcpy(valu1, toksp, tokep - toksp);
    //
    toksp = strstr(++tokep, alab2->data);
    if (!toksp) return NULL;
    toksp = strchr(alab2->slen + toksp, '=');
    if (!toksp) return NULL;
    ++toksp;
    PASS_BLANK(toksp)
    if ('"' == toksp[0x00]) {
        ++toksp;
        tokep = strchr(toksp, '"');
        if (!tokep) return NULL;
    } else FIND_TBLANK(tokep, toksp)
        strzcpy(valu2, toksp, tokep - toksp);
    //
    toksp = strstr(++tokep, alab3->data);
    if (!toksp) return NULL;
    toksp = strchr(alab3->slen + toksp, '=');
    if (!toksp) return NULL;
    ++toksp;
    PASS_BLANK(toksp)
    if ('"' == toksp[0x00]) {
        ++toksp;
        tokep = strchr(toksp, '"');
        if (!tokep) return NULL;
    } else FIND_TBLANK(tokep, toksp)
        strzcpy(valu3, toksp, tokep - toksp);
    //
    return valu1;
}

//

char *get_attval4(char *valu1, char *valu2, char *valu3, char *valu4, char *attstr, osv_str_t *alab1, osv_str_t *alab2, osv_str_t *alab3, osv_str_t *alab4) {
    char *toksp, *tokep;
    //
    toksp = strstr(attstr, alab1->data);
    if (!toksp) return NULL;
    toksp = strchr(alab1->slen + toksp, '=');
    if (!toksp) return NULL;
    ++toksp;
    PASS_BLANK(toksp)
    if ('"' == toksp[0x00]) {
        ++toksp;
        tokep = strchr(toksp, '"');
        if (!tokep) return NULL;
    } else FIND_TBLANK(tokep, toksp)
        strzcpy(valu1, toksp, tokep - toksp);
    //
    toksp = strstr(++tokep, alab2->data);
    if (!toksp) return NULL;
    toksp = strchr(alab2->slen + toksp, '=');
    if (!toksp) return NULL;
    ++toksp;
    PASS_BLANK(toksp)
    if ('"' == toksp[0x00]) {
        ++toksp;
        tokep = strchr(toksp, '"');
        if (!tokep) return NULL;
    } else FIND_TBLANK(tokep, toksp)
        strzcpy(valu2, toksp, tokep - toksp);
    //
    toksp = strstr(++tokep, alab3->data);
    if (!toksp) return NULL;
    toksp = strchr(alab3->slen + toksp, '=');
    if (!toksp) return NULL;
    ++toksp;
    PASS_BLANK(toksp)
    if ('"' == toksp[0x00]) {
        ++toksp;
        tokep = strchr(toksp, '"');
        if (!tokep) return NULL;
    } else FIND_TBLANK(tokep, toksp)
        strzcpy(valu3, toksp, tokep - toksp);
    //
    toksp = strstr(++tokep, alab4->data);
    if (!toksp) return NULL;
    toksp = strchr(alab4->slen + toksp, '=');
    if (!toksp) return NULL;
    ++toksp;
    PASS_BLANK(toksp)
    if ('"' == toksp[0x00]) {
        ++toksp;
        tokep = strchr(toksp, '"');
        if (!tokep) return NULL;
    } else FIND_TBLANK(tokep, toksp)
        strzcpy(valu4, toksp, tokep - toksp);
    //
    return valu1;
}

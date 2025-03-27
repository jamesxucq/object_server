
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcstr_utili.h"

//

static char *split_type_valu(char *type, char *valu, char *conte) {
    char *tvtok = strlchr(conte);
    //
    if (')' == tvtok[0x00]) {
        for (; conte != tvtok && '(' != tvtok[0x00]; --tvtok);
        if (conte == tvtok) return NULL;
        for (tvtok--; conte != tvtok && ' ' == tvtok[0x00]; --tvtok);
    }
    for (; conte != tvtok && ' ' != tvtok[0x00]; --tvtok);
    if (conte == tvtok) return NULL;
    strcpy(type, tvtok);
    strzcpy(valu, conte, tvtok - conte);
    //
    return conte;
}

//

static void split_valu(char *valu) {
    char *vatok = strchr(valu, '=');
    if (vatok) vatok[0x00] = '\0';
}

static void split_type(char *size, char *type) {
    char *toksp = strchr(type, '(');
    if (toksp) {
        MK_ZERO(toksp);
        char *tokep = strchr(++toksp, ')');
        strzcpy(size, toksp, tokep - toksp);
    } else MK_ZERO(size);
}

//

int split_data_styl(char *type, char *valu, char *size, char *data) {
    if (!split_type_valu(type, valu, data))
        return -1;
    // OSEVPF("1 type:|%s| valu:|%s|\n", type, valu);
    split_valu(valu);
    blank_decode(valu);
    //
    split_type(size, type);
    blank_decode(size);
    blank_decode(type);
    // OSEVPF("2 type:|%s| valu:|%s| size:|%s|\n", type, valu, size);
    return 0x00;
}

//

char *split_lv2pn(char *lv2pn, char *lv2_dec) {
    char *toksp;
    PASS_TBLANK(toksp, lv2_dec)
            char *tokep = strpbrk(toksp, " <");
    if (!tokep) return NULL;
    if (LVTN_LENGTH <= (tokep - toksp))
        return NULL;
    strzcpy(lv2pn, toksp, tokep - toksp);
    //
    for (; ' ' == tokep[0x00]; ++tokep);
    return tokep;
}

//

int comp_stri_array(char **lv2pnp1, char **lv2pnp2) {
    for (; lv2pnp1[0x00] && lv2pnp2[0x00]; ++lv2pnp1, ++lv2pnp2) {
        if (strcmp(lv2pnp1[0x00], lv2pnp2[0x00]))
            return 0x01;
    }
    return (lv2pnp1[0x00] == lv2pnp2[0x00]) ? 0x00 : -1;
}

//

char *check_extend(char *lv2pn, char *file_name, char *name_extend) {
    char *last_str = strlchr(file_name);
    for (; '.' != last_str[0x00]; --last_str) {
        if (file_name == last_str) return NULL;
    }
    if (strcmp(name_extend, (last_str + 0x01)))
        return NULL;
    strzcpy(lv2pn, file_name, last_str - file_name);
    return lv2pn;
}


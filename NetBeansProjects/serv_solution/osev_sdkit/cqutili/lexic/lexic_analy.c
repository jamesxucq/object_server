#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "gramm/expre_analy.h"
#include "gramm/exptoke.h"

#include "valtok.h"
#include "lexic_analy.h"

/*
 * && AND || OR ! NOT ( ) < > == != <= >= BETWEEN IN
 */

char *get_valu_toke(valu_toke *valtok, char *line_txt) {
    char *paspo = line_txt;
    char *tokpo = valtok->stri_valu;
    char cha0, cha1;

    //
    valtok->vtok_kind = INVA_TOKE;
    for (; ' ' == paspo[0x00]; ++paspo);
    if ('\0' == paspo[0x00])
        return NULL;
    //
    cha0 = paspo[0x00];
    if (isalpha(cha0)) {
        valtok->vtok_kind = ALPHA_TOKE;
        for (; (':' == paspo[0x00]) || ('_' == paspo[0x00]) || isalnum(paspo[0x00]); ++paspo) {
            if (':' == paspo[0x00]) valtok->vtok_kind = ID_TOKE; // VARIABLE_TOKE; modify by james 20210701
            tokpo[0x00] = paspo[0x00];
            ++tokpo;
        }
        tokpo[0x00] = '\0';
    } else if (isdigit(cha0)) {
        valtok->vtok_kind = LOLO_NUMB_TOKE;
        for (; ('.' == paspo[0x00]) || isdigit(paspo[0x00]); ++paspo) {
            if ('.' == paspo[0x00]) valtok->vtok_kind = DOUB_NUMB_TOKE;
            tokpo[0x00] = paspo[0x00];
            ++tokpo;
        }
        tokpo[0x00] = '\0';
        if (LOLO_NUMB_TOKE == valtok->vtok_kind)
            valtok->lolo_valu = atoll(valtok->stri_valu);
        else valtok->doub_valu = atof(valtok->stri_valu);
    } else if (':' == cha0) {
        for (; (':' == paspo[0x00]) || ('_' == paspo[0x00]) || isalnum(paspo[0x00]); ++paspo) {
            tokpo[0x00] = paspo[0x00];
            ++tokpo;
        }
        tokpo[0x00] = '\0';
        valtok->vtok_kind = ID_TOKE; // VARIABLE_TOKE; modify by james 20210701
    } else if ('"' == cha0) {
        ++paspo;
        for (; ('"' != paspo[0x00]) && ('\0' != paspo[0x00]); ++paspo) {
            tokpo[0x00] = paspo[0x00];
            ++tokpo;
            if ('\\' == paspo[0x00]) {
                ++paspo;
                tokpo[0x00] = paspo[0x00];
                ++tokpo;
            }
        }
        if ('"' == paspo[0x00]) ++paspo;
        tokpo[0x00] = '\0';
        valtok->vtok_kind = TEXT_TOKE;
    } else {
        cha1 = paspo[0x01];
        switch (cha0) {
            case '|':
                if ('|' == cha1) {
                    valtok->vtok_kind = OR_TOKE;
                    paspo += 0X02;
                }
                break;
            case '&':
                if ('&' == cha1) {
                    valtok->vtok_kind = AND_TOKE;
                    paspo += 0X02;
                }
                break;
            case '!':
                if ('=' == cha1) {
                    valtok->vtok_kind = NOT_EQUAL_TOKE;
                    paspo += 0X02;
                } else {
                    valtok->vtok_kind = NOT_TOKE;
                    ++paspo;
                }
                break;
            case '=':
                if ('>' == cha1) {
                    valtok->vtok_kind = GREAT_EQUAL_TOKE;
                    paspo += 0X02;
                } else if ('<' == cha1) {
                    valtok->vtok_kind = LESS_EQUAL_TOKE;
                    paspo += 0X02;
                } else {
                    valtok->vtok_kind = EQUAL_TOKE;
                    ++paspo;
                }
                break;
            case '>':
                if ('=' == cha1) {
                    valtok->vtok_kind = GREAT_EQUAL_TOKE;
                    paspo += 0X02;
                } else {
                    valtok->vtok_kind = GREAT_THAN_TOKE;
                    ++paspo;
                }
                break;
            case '<':
                if ('=' == cha1) {
                    valtok->vtok_kind = LESS_EQUAL_TOKE;
                    paspo += 0X02;
                } else {
                    valtok->vtok_kind = LESS_THAN_TOKE;
                    ++paspo;
                }
                break;
            case '(':
                valtok->vtok_kind = LEFT_PARENT_TOKE;
                ++paspo;
                break;
            case ')':
                valtok->vtok_kind = RIGHT_PARENT_TOKE;
                ++paspo;
                break;
            case '+':
                valtok->vtok_kind = PLUS_TOKE;
                ++paspo;
                break;
            case '-':
                valtok->vtok_kind = MINUS_TOKE;
                ++paspo;
                break;
            case '*':
                valtok->vtok_kind = STAR_TOKE;
                ++paspo;
                break;
            case '/':
                valtok->vtok_kind = SLASH_TOKE;
                ++paspo;
                break;
            case '#':
                valtok->vtok_kind = REM_TOKE;
                ++paspo;
                break;
            case ',':
                valtok->vtok_kind = COMMA_TOKE;
                ++paspo;
                break;
        }
    }

    //
    return paspo;
}
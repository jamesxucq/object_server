
#include "commo_header.h"

#include "valid_lev1d_ite.h"

// txxt:tpp<(xo int32, ao int32)int32, (ci int32, ai int32, xi int32)> {xi = xo; ai = ao; return ci;}

static char *split_lev1d_head(char *lev1_head, char *lev1_cont) {
    char *body_toke;
    char *cotok = lev1_cont;
    //
    if (!isalpha((cotok)[0x00]))
        return NULL;
    cotok = strchr(++cotok, ':');
    if (!cotok) return NULL;
    if (!isalpha((++cotok)[0x00]))
        return NULL;
    cotok = strchr(++cotok, '<');
    if (!cotok) return NULL;
    cotok = pass_blank(++cotok);
    if (!cotok) return NULL;
    cotok = strchr(cotok, '(');
    if (!cotok) return NULL;
    cotok = pass_blank(++cotok);
    if (!cotok) return NULL;
    if (!isalpha((cotok)[0x00]))
        return NULL;
    cotok = strchr(++cotok, ')');
    if (!cotok) return NULL;
    cotok = strchr(++cotok, ',');
    if (!cotok) return NULL;
    cotok = pass_blank(++cotok);
    if (!cotok) return NULL;
    cotok = strchr(cotok, '(');
    if (!cotok) return NULL;
    cotok = pass_blank(++cotok);
    if (!cotok) return NULL;
    if (!isalpha((cotok)[0x00]))
        return NULL;
    cotok = strchr(++cotok, ')');
    if (!cotok) return NULL;
    cotok = pass_blank(++cotok);
    if (!cotok) return NULL;
    if ('>' != cotok[0x00])
        return NULL;
    ++cotok;
    //
    strzcpy(lev1_head, lev1_cont, cotok - lev1_cont);
    PASS_TBLANK(body_toke, cotok)
            //
    return body_toke;
}

// txxt:tpp<(xo int32, ao int32)int32, (ci int32, ai int32, xi int32)> {xi = xo; ai = ao; return ci;}
// <> angle brackets
// () parenthesis

static int valid_lev1d_head(char *lev1_head) {
    int angle_brake = 0x00;
    int parenth = 0x00;
    //
    char *detok = lev1_head;
    for (; detok[0x00]; ++detok) {
        // if( == detok[0x00])
        switch (detok[0x00]) {
            case '(':
                if (parenth || (0x01 != angle_brake))
                    return -1;
                ++parenth;
                break;
            case ')':
                --parenth;
                if (parenth || (0x01 != angle_brake))
                    return -1;
                break;
            case '<':
                if (angle_brake) return -1;
                ++angle_brake;
                break;
            case '>':
                --angle_brake;
                if (angle_brake) return -1;
                break;
            default:
                break;
        }
    }
    //
    if (angle_brake || parenth)
        return -1;
    //
    return 0x00;
}

// txxt:tpp<(xo int32, ao int32)int32, (ci int32, ai int32, xi int32)> {xi = xo; ai = ao; return ci;}
// {} brace
// "" quote

static int valid_lev1d_body(char *lev1_body) {
    char *botok = lev1_body;
    int brace_deep = 0x00;
    //
    for (; '\0' != *botok; ++botok) {
        if ('\\' == *botok) ++botok;
        else if ('"' == *botok) {
            for (++botok; '"' != *botok; ++botok) {
                if (!*botok) return -1;
                if ('\\' == *botok) ++botok;
            }
        } else if ('{' == *botok) ++brace_deep;
        else if ('}' == *botok) {
            --brace_deep;
            if (!brace_deep) return 0x00;
        }
    }
    //
    return -1;
}

//

int valid_lev1_conte(char *lev1_cont) {
    char lev1_head[TEXT_LENGTH];
    //
    char *lev1_body = split_lev1d_head(lev1_head, lev1_cont);
    if (!lev1_body) return -1;
    //
    if (valid_lev1d_head(lev1_head))
        return -1;
    if (valid_lev1d_body(lev1_body))
        return -1;
    //
    return 0x00;
}
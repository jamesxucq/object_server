#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "commo_header.h"
#include "../../debug_funct_sh.h"

#include "fmt_xmlang.h"

//

/*
static char *get_xmlang_node(char *line_cont, char *xml_cont) {
    char *toksp = xml_cont;
    //
    KILL_INVAL(toksp, xml_cont)
    if ('<' != toksp[0x00]) return NULL;
    //
    char *tokep = toksp + 0x01;
    char *eleme;
    int quote = 0x00;
    for (; tokep[0x00]; ++tokep) {
        if (quote) {
            if ('\\' == tokep[0x00]) {
                ++tokep;
                if ('"' == tokep[0x00]) --quote;
            }
            continue;
        }
        //
        switch (tokep[0x00]) {
            case '\\':
                ++tokep;
                if ('"' == tokep[0x00]) ++quote;
                break;
            case '>':
                eleme = kill_inval(++tokep);
                if (!eleme || '<' == eleme[0x00]) {
                    strzcpy(line_cont, toksp, tokep - toksp);
                    return tokep;
                }
                break;
            case '/':
                ++tokep;
                if ('>' == tokep[0x00]) {
                    ++tokep;
                    strzcpy(line_cont, toksp, tokep - toksp);
                    return tokep;
                }
                break;
            default:
                break;
        }
    }
    //
    return tokep;
}
 */


static char *find_head_end(char *line_cont) {
    // printf("[FUNC]:find_head_end\n");
    char *cotok;
    KILL_INVAL(cotok, line_cont)
            int quote = 0x00;
    for (; cotok[0x00]; ++cotok) {
        if (quote) {
            if ('\\' == cotok[0x00]) {
                ++cotok;
                if ('"' == cotok[0x00]) --quote;
            }
            continue;
        }
        //
        switch (cotok[0x00]) {
            case '\\':
                ++cotok;
                if ('"' == cotok[0x00]) ++quote;
                break;
            case '?':
                ++cotok;
                if ('>' != cotok[0x00]) return NULL;
                ++cotok;
                return cotok;
                break;
            default:
                break;
        }
    }
    //
    return cotok;
}

static char *find_node_end(char *line_cont) {
    // printf("[FUNC]:find_node_end\n");
    char *cotok;
    KILL_INVAL(cotok, line_cont)
            int quote = 0x00;
    for (; cotok[0x00]; ++cotok) {
        if (quote) {
            if ('\\' == cotok[0x00]) {
                ++cotok;
                if ('"' == cotok[0x00]) --quote;
            }
            continue;
        }
        //
        switch (cotok[0x00]) {
            case '\\':
                ++cotok;
                if ('"' == cotok[0x00]) ++quote;
                break;
            case '>':
                ++cotok;
                return cotok;
                break;
            default:
                break;
        }
    }
    //
    return cotok;
}

#define END_LABE_ENDTYP 0x0001 // "/>"
#define END_LABE_STATYP 0x0002 // '>'

static char *find_label_end(int *end_type, char *line_cont) {
    // printf("[FUNC]:find_label_end\n");
    char *cotok;
    KILL_INVAL(cotok, line_cont)
            int quote = 0x00;
    for (; cotok[0x00]; ++cotok) {
        if (quote) {
            if ('\\' == cotok[0x00]) {
                ++cotok;
                if ('"' == cotok[0x00]) --quote;
            }
            continue;
        }
        //
        switch (cotok[0x00]) {
            case '\\':
                ++cotok;
                if ('"' == cotok[0x00]) ++quote;
                break;
            case '>':
                ++cotok;
                end_type[0x00] = END_LABE_STATYP;
                return cotok;
                break;
            case '/':
                ++cotok;
                if ('>' != cotok[0x00]) return NULL;
                ++cotok;
                end_type[0x00] = END_LABE_ENDTYP;
                return cotok;
                break;
            default:
                break;
        }
    }
    //
    return cotok;
}

#define START_LABE_ENDTYP 0x0001 // "</"
#define START_LABE_STATYP 0x0002 // '<'

static char *find_label_start(int *start_type, char *line_cont) {
    // printf("[FUNC]:find_label_start.....\n");
    // printf("line_cont:\n|%s|\n", line_cont);
    char *cotok;
    KILL_INVAL(cotok, line_cont)
            int quote = 0x00;
    for (; cotok[0x00]; ++cotok) {
        // printf("cotok[0x00]:|%c|\n", cotok[0x00]);
        if (quote) {
            if ('\\' == cotok[0x00]) {
                ++cotok;
                if ('"' == cotok[0x00]) --quote;
            }
            continue;
        }
        //
        switch (cotok[0x00]) {
            case '\\':
                ++cotok;
                if ('"' == cotok[0x00]) ++quote;
                break;
            case '<':
                ++cotok;
                // printf("----------- cotok[0x00]:|%c|\n", cotok[0x00]);
                if ('/' != cotok[0x00]) {
                    start_type[0x00] = START_LABE_STATYP;
                    return line_cont;
                }
                ++cotok;
                start_type[0x00] = START_LABE_ENDTYP;
                return cotok;
                break;
            default:
                break;
        }
    }
    //
    return cotok;
}

static char *get_xmlang_node(char *line_cont, char *xml_cont) {
    // printf("[FUNC]:get_xmlang_node\n");
    int label_type = 0x00;
    char *toksp;
    //
    KILL_INVAL(toksp, xml_cont)
    if ('<' != toksp[0x00])
        return NULL;
    //
    char *tokep = toksp + 0x01;
    if ('\0' == tokep[0x00])
        return NULL;
    switch (tokep[0x00]) {
        case '?':
            tokep = find_head_end(++tokep);
            if (!tokep) return NULL;
            strzcpy(line_cont, toksp, tokep - toksp);
            break;
        case '/':
            tokep = find_node_end(++tokep);
            strzcpy(line_cont, toksp, tokep - toksp);
            break;
        default:
            tokep = find_label_end(&label_type, tokep);
            if (!tokep) return NULL;
            // printf("a label_type:|%d|\n", label_type);
            if (END_LABE_STATYP == label_type) {
                tokep = find_label_start(&label_type, tokep);
                // printf("b label_type:|%d|\n", label_type);
                if (START_LABE_ENDTYP == label_type) {
                    tokep = find_label_end(&label_type, tokep);
                    if (!tokep) return NULL;
                    // printf("c label_type:|%d|\n", label_type);
                    if (END_LABE_STATYP != label_type)
                        return NULL;
                    strzcpy(line_cont, toksp, tokep - toksp);
                } else if (START_LABE_STATYP == label_type)
                    strzcpy(line_cont, toksp, tokep - toksp);
            } else if (END_LABE_ENDTYP == label_type)
                strzcpy(line_cont, toksp, tokep - toksp);
            break;
    }
    //
    return tokep;
}

// start:0x01 element:0x03

static int eleme_start(char *line_str) {
    char *lstok = line_str;
    //
    int quote = 0x00;
    for (; lstok[0x00]; ++lstok) {
        if (quote) {
            if ('\\' == lstok[0x00]) {
                ++lstok;
                if ('"' == lstok[0x00]) --quote;
            }
            continue;
        }
        //
        switch (lstok[0x00]) {
            case '\\':
                ++lstok;
                if ('"' == lstok[0x00]) ++quote;
                break;
            case '>':
                ++lstok;
                if ('\0' == lstok[0x00]) return 0x01;
                return 0x03;
                break;
            case '/':
                ++lstok;
                if ('>' == lstok[0x00]) return 0x03;
                break;
            default:
                break;
        }
    }
    //
    return 0x00;
}

// node_type

static int chk_xmlang_type(char *line_cont) {
    int xml_type = -1;
    char *cotok = line_cont;
    //
    if ('<' != cotok[0x00]) return -1;
    ++cotok;
    switch (cotok[0x00]) {
        case '\0':
            break;
        case '?':
            xml_type = 0x00;
            break;
        case '/':
            xml_type = 0x02;
            break;
        default: // start:0x01 element:0x03
            xml_type = eleme_start(cotok);
            break;
    }
    //
    return xml_type;
}

static inline char *prin_head(char *resul_cont, char *head_cont) {
    resul_cont = lscpy(resul_cont, head_cont);
    return resul_cont;
}

#define PRIN_END(LAST_STR) LAST_STR = lccpy(LAST_STR, '\n')

static inline char *prin_conte(char *resul_cont, char *node_cont, int xml_deep) {
    resul_cont = lccpy(resul_cont, '\n');
    while (xml_deep--) resul_cont = lscpy(resul_cont, "    ");
    resul_cont = lscpy(resul_cont, node_cont);
    return resul_cont;
}

static inline char *prin_excep(char *resul_cont, char *excep_cont) {
    char *cotok;
    KILL_INVAL(cotok, excep_cont)
    if ('\0' != cotok[0x00]) {
        resul_cont = lscpy(resul_cont, "\nFORMAT EXCEPTION:\n");
        resul_cont = lscpy(resul_cont, cotok);
        return resul_cont;
    }
    return resul_cont;
}

int format_xmlang(clie_resu *resul) {
    CLIEPF("[FUNC]:format_xmlang\n");
    char resp_data[LARGE_CONTE_SIZE];
    char node_cont[LINE_LENGTH];
    //
    if (LARGE_CONTE_SIZE < resul->resu_leng) {
        CliePrintErro("Result leng more than LARGE_CONTE_SIZE!", -1);
        return -1;
    }
    //
    if (resul->resu_type) {
        rewind(resul->resu_stram);
        if (0x00 >= fread(resp_data, resul->resu_leng, 0x01, resul->resu_stram)) {
            CliePrintErro("Fread result data error!", -1);
            return -1;
        }
    } else strzcpy(resp_data, resul->resu_data, resul->resu_leng);
    char *posi_str = resp_data;
    char *last_str = resul->resu_data;
    //
    int xml_deep = 0x00;
    // CLIEPF("----------------------------------\n");
    // CLIEPF("posi_str:|%s|\n", posi_str);
    char *posi_excep = posi_str;
    while ((posi_str = get_xmlang_node(node_cont, posi_str))) {
        // CLIEPF("---- node_cont:|%s|\n", node_cont);
        switch (chk_xmlang_type(node_cont)) {
            case 0x00: // head
                last_str = prin_head(last_str, node_cont);
                xml_deep = 0x00;
                break;
            case 0x01: // start
                last_str = prin_conte(last_str, node_cont, xml_deep);
                ++xml_deep;
                break;
            case 0x02: // end
                --xml_deep;
                last_str = prin_conte(last_str, node_cont, xml_deep);
                if (!xml_deep) PRIN_END(last_str);
                break;
            case 0x03: // element
                last_str = prin_conte(last_str, node_cont, xml_deep);
                break;
            default:
                _LOG_WARN("default: node_type");
                break;
        }
        // CLIEPF("----------------------------------\n");
        // CLIEPF("posi_str:|%s|\n", posi_str);
        posi_excep = posi_str;
    }
    last_str = prin_excep(last_str, posi_excep);
    //
    resul->resu_leng = last_str - resul->resu_data;
    resul->resu_type = 0x00;
    return 0x00;
}

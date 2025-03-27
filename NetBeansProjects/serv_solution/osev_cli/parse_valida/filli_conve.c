#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "../cinstru.h"
#include "../cstri_utili.h"
#include "../clit_bzl.h"

#include "filli_conve.h"
// #include "../debug_funct_sh.h"

//
#define LEVE_OBJE_TOK "odb"
#define OBJE_CREAT_TOK "create"

// test:test(33); tvtv:create(33);

char *filli_creat_eobje_exte(char *cont_iden, char *levivk, char *line_str) {
    char parms_cont[LARGE_TEXT_SIZE];
    if (!analy_const_eobje_exte(parms_cont, line_str))
        return NULL;
    // CLIT_PF("[FUNC]:filli_creat_eobje_exte, FIX ME!\n");
    line_str = lscpy(line_str, _leve_defa_obje_.obje_iden);
    line_str = lccpy(line_str, ':');
    char *echo_tok = line_str = lscpy(line_str, OBJE_CREAT_TOK);
    // CLIT_PF("[FUNC]:echo_creat_eobje, line_str:|%s|\n", line_str);
    line_str = lccpy(line_str, '(');
    line_str = lscpy(line_str, parms_cont);
    line_str = lscpy(line_str, ");");
    //
    lscpy(cont_iden, _leve_defa_obje_.obje_iden);
    lscpy(levivk, OBJE_CREAT_TOK);
    //
    return echo_tok;
}

// test:test(33) > tvtv; => tvtv:create(33);

char *filli_creat_eobje_redi(char *objide, char *levivk, char *line_str) {
    char redi_obje[OBJN_LENGTH];
    char parms_cont[LARGE_TEXT_SIZE];
    if (!analy_const_eobje_redi(redi_obje, parms_cont, line_str))
        return NULL;
    //
    line_str = lscpy(line_str, redi_obje);
    line_str = lccpy(line_str, ':');
    char *echo_tok = line_str = lscpy(line_str, OBJE_CREAT_TOK);
    // CLIT_PF("[FUNC]:echo_creat_eobje, line_str:|%s|\n", line_str);
    line_str = lccpy(line_str, '(');
    line_str = lscpy(line_str, parms_cont);
    line_str = lscpy(line_str, ");");
    //
    lscpy(objide, redi_obje);
    lscpy(levivk, OBJE_CREAT_TOK);
    //
    return echo_tok;
}


// odb-lv4p> witi:witi("taat_con", "txxt") > odb;
// rive:rive("tvtv", "test") > odb; => odb:create("tvtv", "rive", "test");

char *filli_creat_cobje(char *objide, char *levivk, char *line_str) {
    char parms_cont[LARGE_TEXT_SIZE];
    // CLIT_PF("line_str:|%s| objide:|%s|\n", line_str, objide);
#ifdef _CREAT_COBJE_REDIRECT
    char redi_obje[OBJN_LENGTH];
    if (!analy_const_cobje(redi_obje, parms_cont, line_str, objide))
        return NULL;
    line_str = lscpy(line_str, redi_obje);
#else
    if (!analy_const_cobje(parms_cont, line_str, objide))
        return NULL;
    line_str = lscpy(line_str, LEVE_OBJE_TOK);
#endif // _CREAT_COBJE_REDIRECT
    // CLIT_PF("[FUNC]:filli_creat_cobje, redi_obje:|%s| parms_cont:|%s|\n", redi_obje, parms_cont);
    line_str = lccpy(line_str, ':');
    char *echo_tok = line_str = lscpy(line_str, OBJE_CREAT_TOK);
    // CLIT_PF("const_str:|%s|\n", const_str);
    line_str = lccpy(line_str, '(');
    line_str = lscpy(line_str, parms_cont);
    line_str = lscpy(line_str, ");");
    //
#ifdef _CREAT_COBJE_REDIRECT
    lscpy(objide, redi_obje);
#else
    lscpy(objide, LEVE_OBJE_TOK);
#endif // _CREAT_COBJE_REDIRECT
    lscpy(levivk, OBJE_CREAT_TOK);
    //
    return echo_tok;
}

//
// ;ttt; => odb:create("xxx; ttt;");

char *filli_creat_metho_exte(char *objide, char *levivk, char *line_str) {
    char line_txt[LARGE_TEXT_SIZE];
    strcpy(line_txt, line_str);
    line_str = lscpy(line_str, objide);
    line_str = lccpy(line_str, ':');
    char *echo_tok = line_str = lscpy(line_str, OBJE_CREAT_TOK);
    // CLIT_PF("[FUNC]:filli_creat_metho, line_str:|%s|\n", line_str);
    line_str = lscpy(line_str, "(\"");
    line_str = lscpy(line_str, objide);
    line_str = lscpy(line_str, line_txt);
    line_str = lscpy(line_str, "\");");
    //
    lscpy(levivk, OBJE_CREAT_TOK);
    //
    return echo_tok;
}

// xxx; ttt; => odb:create("xxx; ttt;");

char *filli_creat_metho(char *objide, char *levivk, char *line_str) {
    char line_txt[LARGE_TEXT_SIZE];
    strcpy(line_txt, line_str);
    line_str = lscpy(line_str, objide);
    line_str = lccpy(line_str, ':');
    char *echo_tok = line_str = lscpy(line_str, OBJE_CREAT_TOK);
    // CLIT_PF("[FUNC]:filli_creat_metho, line_str:|%s|\n", line_str);
    line_str = lscpy(line_str, "(\"");
    line_str = lscpy(line_str, line_txt);
    line_str = lscpy(line_str, "\");");
    //
    lscpy(levivk, OBJE_CREAT_TOK);
    //
    return echo_tok;
}

// xxx; ttt; => odb:create("xxx; ttt;");

char *filli_creat_class(char *objide, char *levivk, char *line_str) {
    char line_txt[LARGE_TEXT_SIZE];
    strcpy(line_txt, line_str);
    line_str = lscpy(line_str, LEVE_OBJE_TOK);
    line_str = lccpy(line_str, ':');
    char *echo_tok = line_str = lscpy(line_str, OBJE_CREAT_TOK);
    // CLIT_PF("[FUNC]:filli_creat_metho, line_str:|%s|\n", line_str);
    line_str = lscpy(line_str, "(\"");
    line_str = lscpy(line_str, line_txt);
    line_str = lscpy(line_str, "\");");
    //
    lscpy(objide, LEVE_OBJE_TOK);
    lscpy(levivk, OBJE_CREAT_TOK);
    //
    return echo_tok;
}

//

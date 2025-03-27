
/* 
 * File:   clit_bzl.h
 * Author: James Xu
 *
 * Created on 2017.4.20, AM10:46
 */

#ifndef CLIT_BZL_H
#define CLIT_BZL_H

#include "clit_obje.h"
#include "connect.h"
#include "osvp_utili.h"
#include "cinstru.h"
#include "clit_macro.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    void completion_caba(const char *buff, linenoiseCompletions *lc);
    extern char* history_table[];

#define LINENOISE_INITIALIZE_BZL(COMPLETION, HISTORY_FILE) \
    linenoiseSetMultiLine(1); \
    linenoiseSetCompletionCallback(COMPLETION); \
    linenoiseHistoryLoad(HISTORY_FILE);

#define LINENOISE_FINALIZE_BZL linenoiseAtExit();

    //
#define OCLIE_HISTORY_ADDI_BZL(LINE_STR, CLI_TYPE) \
    char prev_line[LARGE_TEXT_SIZE]; \
    if(CITP_CLIE == CLI_TYPE) hide_instru(LINE_STR); \
    if(strcmp(prev_line, LINE_STR)) { \
        linenoiseHistoryAdd(LINE_STR); \
        strcpy(prev_line, LINE_STR); \
        linenoiseFree(LINE_STR); \
    }

    //
    int creat_clit_bzl(char (**pinst_stri)[LARGE_TEXT_SIZE]);
    void destroy_clit_bzl(char (*inst_stri)[LARGE_TEXT_SIZE]);

    //
    extern char* history_dire[];
    extern char* history_level[];
    uint32 cli_status_bzl(clit_stat_t *clit_stat, clit_inst *cinst);

    //
#define GET_BLANK_BZL() _blank_prompt_
    char *get_osev_base_bzl(char *osev_base);

#ifdef __cplusplus
}
#endif

#endif /* CLIT_BZL_H */


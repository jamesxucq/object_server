#include <pthread.h>

#include "commo_header.h"
#include "third_party.h"
#include "clit_obje.h"
#include "cinstru.h"
#include "cstatu.h"

#include "clit_bzl.h"
#include "debug_funct_sh.h"

//
char* history_dire[] = {
    ".osev-cli",
    "base"
};

char* history_table[] = {
    "clie",
    "osev",
    "base"
};

char* history_level[] = {
    "lev1",
    "lv2p",
    "lev3",
    "lv4p"
};

//

void completion_caba(const char *buff, linenoiseCompletions *lc) {
    if (buff[0x00] == 'c') {
        linenoiseAddCompletion(lc, "clie:");
    } else if (buff[0x00] == 'o') {
        linenoiseAddCompletion(lc, "odb:");
        linenoiseAddCompletion(lc, "osev:");
    }
}

//

int creat_clit_bzl(char (**pinst_stri)[LARGE_TEXT_SIZE]) {
    pinst_stri[0x00] = (char (*)[LARGE_TEXT_SIZE]) malloc(PARAM_COUNT * LARGE_TEXT_SIZE);
    if (!pinst_stri[0x00]) return -1;
    //
    if (creat_base_cache())
        return -1;
    if (creat_conta_cache())
        return -1;
    if (creat_colle_cache())
        return -1;
    //
    CLIT_PF("Check auth cache OK!\n");
    return ERR_SUCCESS; //succ
}

void destroy_clit_bzl(char (*inst_stri)[LARGE_TEXT_SIZE]) {
    creat_colle_cache();
    destr_conta_cache();
    destr_base_cache();
    //
    if (inst_stri) free(inst_stri);
}

//

uint32 cli_status_bzl(clit_stat_t *clit_stat, clit_inst *cinst) {
    // CLIT_PF("[FUNC]1 cli_status_bzl, cli_mode:%d run_level:%08X\n", clit_stat->cli_mode, clit_stat->run_level);
    _last_cli_stat_.cli_mode = clit_stat->cli_mode;
    _last_cli_stat_.run_level = clit_stat->run_level;
    //
    if (ATTRI_INSTRUC & cinst->inst_attrib) {
        uint32 clit_type = clit_runni_type(cinst, clit_stat->cli_mode);
        if (CLI_TYPE_EXIT == clit_type)
            return CLI_TYPE_EXIT;
        if (clit_type != _last_cli_stat_.cli_mode) {
            if (CITP_CLEV == clit_type)
                linenoiseHistoryReload(levecomd_name(history_table[CITP_CLEV], history_level[ONLY_LEVEL_VALUE(clit_stat->run_level)]));
            else linenoiseHistoryReload(runcomd_name(history_table[clit_type]));
            clit_stat->cli_mode = clit_type;
        }
        if (CITP_CLEV == clit_type) {
            uint32 level_type = clit_runni_level(cinst, _last_cli_stat_.run_level);
            if (level_type != _last_cli_stat_.run_level) {
                linenoiseHistoryReload(levecomd_name(history_table[CITP_CLEV], history_level[ONLY_LEVEL_VALUE(level_type)]));
                CLIT_PF("[FUNC] clit_stat->run_level:%08X level_type:%08X\n", clit_stat->run_level, level_type);
                clit_stat->run_level = level_type;
            }
        }
    }
    // CLIT_PF("[FUNC]2 cli_status_bzl, cli_mode:%d run_level:%08X\n", clit_stat->cli_mode, clit_stat->run_level);
    return clit_stat->cli_mode;
}

//

char *get_osev_base_bzl(char *osev_base) {
    if (_ocli_auth_.osev_base[0x00])
        strcpy(osev_base, _ocli_auth_.osev_base);
    else strcpy(osev_base, OSEV_DEFAULT_VALUE);
    return osev_base;
}
#include <pthread.h>

#include "commo_header.h"
#include "third_party.h"
#include "cli_obje.h"
#include "cinstru.h"
#include "clien_statu.h"

#include "cli_bzl.h"
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
    CLIEPF("Check auth cache OK!\n");
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

uint32 cli_status_bzl(clie_stat_t *cli_stat, cli_inst *cinst) {
    // CLIEPF("[FUNC]1 cli_status_bzl, cli_mode:%d run_level:%08X\n", cli_stat->cli_mode, cli_stat->run_level);
    _last_cli_stat_.cli_mode = cli_stat->cli_mode;
    _last_cli_stat_.run_level = cli_stat->run_level;
    //
    if (ATTRI_INSTRUC & cinst->inst_attrib) {
        uint32 cli_type = clie_runni_type(cinst, cli_stat->cli_mode);
        if (CLI_TYPE_EXIT == cli_type)
            return CLI_TYPE_EXIT;
        if (cli_type != _last_cli_stat_.cli_mode) {
            if (CITP_CLEV == cli_type)
                linenoiseHistoryReload(levecomd_name(history_table[CITP_CLEV], history_level[ONLY_LEVEL_VALUE(cli_stat->run_level)]));
            else linenoiseHistoryReload(runcomd_name(history_table[cli_type]));
            cli_stat->cli_mode = cli_type;
        }
        if (CITP_CLEV == cli_type) {
            uint32 level_type = clie_runni_level(cinst, _last_cli_stat_.run_level);
            if (level_type != _last_cli_stat_.run_level) {
                linenoiseHistoryReload(levecomd_name(history_table[CITP_CLEV], history_level[ONLY_LEVEL_VALUE(level_type)]));
                CLIEPF("[FUNC] cli_stat->run_level:%08X level_type:%08X\n", cli_stat->run_level, level_type);
                cli_stat->run_level = level_type;
            }
        }
    }
    // CLIEPF("[FUNC]2 cli_status_bzl, cli_mode:%d run_level:%08X\n", cli_stat->cli_mode, cli_stat->run_level);
    return cli_stat->cli_mode;
}

//

char *get_osev_base_bzl(char *osev_base) {
    if (_ocli_auth_.osev_base[0x00]) 
        strcpy(osev_base, _ocli_auth_.osev_base);
    else strcpy(osev_base, OSEV_DEFAULT_VALUE);
    return osev_base;
}
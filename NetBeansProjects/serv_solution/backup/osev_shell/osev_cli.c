
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "third_party.h"
#include "cstri_utili.h"
#include "options.h"
#include "cli_struct.h"
#include "cli_bzl.h"
#include "pretr_prompt/prompt_ite.h"
#include "finish_cline/cline_valid_ite.h"
#include "parse_valida/valida_ite.h"
#include "pretr_instru/pre_instru_ite.h"
#include "instru_execute/execute_ite.h"
#include "finish_instru/finish_ite.h"

#include "osev_cli.h"
#include "debug_funct_sh.h"

//

int main(int argc, char** argv) {
    creat_runcomd_directory(history_dire[0x00], history_dire[0x01]);
    if (parse_args(argc, argv)) return 0x01;
    //
    LINENOISE_INITIALIZE_BZL(completion_caba, runcomd_name(history_table[0x00]))
            char (*inst_stri)[LARGE_TEXT_SIZE];
    if (creat_clit_bzl(&inst_stri))
        return -1;
    // initial osev driver
    clie_stat_t cli_stat = {CITP_CLIE, LVTP_FOUP};
    char *line_str;
    static clie_resu resul;
    int hand_valu = 0x00;
    //
    if (resul_initial(&resul))
        return -1;
    char *prompt = initi_prompt_ite(cli_stat.cli_mode);
    while ((line_str = linenoise(prompt)) != NULL) {
        // CLIEPF("[FUNC]line_str:|%s|\n", line_str);
        hand_valu = finish_coline_ite(inst_stri, line_str, cli_stat.cli_mode, cli_stat.run_level);
        OCLIE_HISTORY_ADDI_BZL(line_str, cli_stat.cli_mode)
        switch (hand_valu) {
            case 0x01:
                // CLIEPF("[FUNC]hand_valu:0x01\n");
                prompt = blank_prompt_ite(prompt, &cli_stat);
                continue;
            case 0x02:
                // CLIEPF("[FUNC]hand_valu:0x02\n");
                continue;
            case -1:
                CliePrintErro("Syntactic error!", -1);
                continue;
        }
        //
        cli_inst cinst;
        reset_result(&resul);
        char (*instr)[LARGE_TEXT_SIZE] = inst_stri;
        for (; '\0' != (*instr)[0x00]; ++instr) {
            CLIEPF("*** instr[0x00]:|%s| ***\n", instr[0x00]);
            memset(&cinst, '\0', sizeof (cli_inst));
            if ((hand_valu = parse_valida_ite(&cinst, instr[0x00], &cli_stat))) {
                CLIEPF("Check method ERROR!\n");
                break;
            }
            // build query method
            if ((hand_valu = instru_prepare_ite(&cinst, &cli_stat))) {
                CLIEPF("Preptre method ERROR!\n");
                break;
            }
            // handle query from osev
            if ((hand_valu = instru_execute_ite(&resul, &cli_stat, &cinst))) {
                CLIEPF("Execute exception!\n");
                break;
            }
        }
        // CLIEPF("hand_valu:%d\n", hand_valu);
        if (!hand_valu) { // finish method
            if (finish_instru_ite(&cinst, &resul))
                CLIEPF("Method finish ERROR!\n");
            //
            CliePrintErro("OK!", 0);
            if (CLI_TYPE_EXIT == cli_status_bzl(&cli_stat, &cinst)) {
                CliePrintErro("Bye!", 0);
                break;
            }
            prompt = pretr_prompt_ite(prompt, &cli_stat);
            // CLIEPF("[FUNC]prompt:|%s|\n", prompt);
        } else if (GET_BLANK_BZL()) prompt = produ_prompt_ite(&cli_stat);
    }
    //cleanup osev env
    final_result(&resul);
    destroy_clit_bzl(inst_stri);
    LINENOISE_FINALIZE_BZL
            //
    return 0x00;
}



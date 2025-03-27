
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "third_party.h"
#include "cstri_utili.h"
#include "options.h"
#include "clit_struct.h"
#include "clit_bzl.h"
#include "pretr_prompt/prompt_ite.h"
#include "finish_cline/cline_valid_ite.h"
#include "parse_valida/valida_ite.h"
#include "pretr_instru/pre_instru_ite.h"
#include "instru_execute/execute_ite.h"
#include "finish_instru/finish_ite.h"

#include "osev_clit.h"
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
    clit_stat_t clit_stat = {CITP_CLIE, LVTP_FOUP};
    char *line_str;
    static clit_resu resul;
    int hand_valu = 0x00;
    //
    if (resul_initial(&resul))
        return -1;
    char *prompt = initi_prompt_ite(clit_stat.cli_mode);
    while ((line_str = linenoise(prompt)) != NULL) {
        // CLIT_PF("[FUNC]line_str:|%s|\n", line_str);
        hand_valu = finish_coline_ite(inst_stri, line_str, clit_stat.cli_mode, clit_stat.run_level);
        OCLIE_HISTORY_ADDI_BZL(line_str, clit_stat.cli_mode)
        switch (hand_valu) {
            case 0x01:
                // CLIT_PF("[FUNC]hand_valu:0x01\n");
                prompt = blank_prompt_ite(prompt, &clit_stat);
                continue;
            case 0x02:
                // CLIT_PF("[FUNC]hand_valu:0x02\n");
                continue;
            case -1:
                ClitPrintErro("Syntactic error!", -1);
                continue;
        }
        //
        clit_inst cinst;
        reset_result(&resul);
        char (*instr)[LARGE_TEXT_SIZE] = inst_stri;
        for (; '\0' != (*instr)[0x00]; ++instr) {
            CLIT_PF("*** instr[0x00]:|%s| ***\n", instr[0x00]);
            memset(&cinst, '\0', sizeof (clit_inst));
            if ((hand_valu = parse_valida_ite(&cinst, instr[0x00], &clit_stat))) {
                ClitPrintErro("Check method error!", hand_valu);
                break;
            }
            // build query method
            if ((hand_valu = instru_prepare_ite(&cinst, &clit_stat))) {
                ClitPrintErro("Preptre method error!", hand_valu);
                break;
            }
            // handle query from osev
            if ((hand_valu = instru_execute_ite(&resul, &clit_stat, &cinst))) {
                ClitPrintErro("Execute exception!", hand_valu);
                break;
            }
        }
        // CLIT_PF("hand_valu:%d\n", hand_valu);
        if (!hand_valu) { // finish method
            if (finish_instru_ite(&cinst, &resul))
                ClitPrintErro("Method finish error!", hand_valu);
            //
            ClitPrintInfo("OK!");
            if (CLI_TYPE_EXIT == cli_status_bzl(&clit_stat, &cinst)) {
                ClitPrintInfo("Bye!");
                break;
            }
            prompt = pretr_prompt_ite(prompt, &clit_stat);
            // CLIT_PF("[FUNC]prompt:|%s|\n", prompt);
        } else if (GET_BLANK_BZL()) prompt = produ_prompt_ite(&clit_stat);
    }
    //cleanup osev env
    final_result(&resul);
    destroy_clit_bzl(inst_stri);
    LINENOISE_FINALIZE_BZL
            //
    return 0x00;
}



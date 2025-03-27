
#include "commo_macro.h"
#include "osev_datyp.h"
#include "../cli_struct.h"
#include "../cli_bzl.h"
#include "prompt_utili.h"

#include "prompt_ite.h"
#include "../debug_funct_sh.h"

//

char *blank_prompt_ite(char *prompt, clie_stat_t *cli_stat) {
    if (!_blank_prompt_) {
        switch (cli_stat->cli_mode) {
            case CITP_CLIE:
            case CITP_OSVB:
                prompt = (char *) multi_blank_tab[0x00];
                break;
            case CITP_CLEV:
                switch (ONLY_LEVEL_VALUE(cli_stat->run_level)) {
                    case LVTP_ONE:
                    case LVTP_THRE:
                        prompt = (char *) multi_blank_tab[0x01];
                        break;
                    case LVTP_TWOP:
                    case LVTP_FOUP:
                        prompt = (char *) multi_blank_tab[0x02];
                        break;
                }
                break;
        }
    }
    //
    _blank_prompt_ = 0x01;
    return prompt;
}

//

char *pretr_prompt_ite(char *prompt, clie_stat_t *cli_stat) {
    // CLIEPF("1 pretr_prompt_ite, prompt:|%s|, cli_mode:|%d|, run_level:|%08X|\n", prompt, _last_cli_stat_.cli_mode, _last_cli_stat_.run_level);
    if (CITP_CLEV == cli_stat->cli_mode) {
        if (_blank_prompt_) {
            prompt = prompt_level(cli_stat->run_level);
            _blank_prompt_ = 0x00;
        } else if (_leve_defa_obje_.changed) {
            prompt = prompt_level(cli_stat->run_level);
            _leve_defa_obje_.changed = 0x00;
        } else if ((_last_cli_stat_.run_level != cli_stat->run_level) || (_last_cli_stat_.cli_mode != cli_stat->cli_mode))
            prompt = prompt_level(cli_stat->run_level);
    } else if (_blank_prompt_) {
        prompt = (char *) cmode_tab[cli_stat->cli_mode];
        _blank_prompt_ = 0x00;
    } else if (_last_cli_stat_.cli_mode != cli_stat->cli_mode)
        prompt = (char *) cmode_tab[cli_stat->cli_mode];
    // CLIEPF("2 pretr_prompt_ite, prompt:|%s|, cli_mode:|%d|, run_level:|%08X|\n", prompt, cli_stat->cli_mode, cli_stat->run_level);
    return prompt;
}



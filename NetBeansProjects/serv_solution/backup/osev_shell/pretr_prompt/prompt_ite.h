
/* 
 * File:   prompt_ite.h
 * Author: james
 *
 * Created on 2023.4.14, PM 3:17
 */

#ifndef PROMPT_ITE_H
#define PROMPT_ITE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "prompt_utili.h"
    
    //

    inline char *initi_prompt_ite(uint32 cli_mode) {
        return (char *) cmode_tab[cli_mode];
    }

    //
    char *blank_prompt_ite(char *prompt, clie_stat_t *cli_stat);

    //
    char *pretr_prompt_ite(char *prompt, clie_stat_t *cli_stat);

    // 

    inline char *produ_prompt_ite(clie_stat_t *cli_stat) {
        _blank_prompt_ = 0x00;
        return prompt_level(cli_stat->run_level);
    }

#ifdef __cplusplus
}
#endif

#endif /* PROMPT_ITE_H */


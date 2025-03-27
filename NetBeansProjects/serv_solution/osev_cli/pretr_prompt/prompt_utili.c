
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "../clit_struct.h"
#include "../clit_bzl.h"

#include "prompt_utili.h"

//

const char *cmode_tab[] = {
    "clie: ",
    "osev: ",
    "odb-lv4p> "
};

/*
static const char *level_tab[] = {
    "level-1> ",
    "level-2+> ",
    "level-3> ",
    "level-4+> "
};
 */

static const char *level_tab[] = {
    "odb-lev1> ",
    "odb-lv2p> ",
    "odb-lev3> ",
    "odb-lv4p> "
};

const char *multi_blank_tab[] = {
    "      ",
    "        ",
    "        "
};

// odb.lev1 odb|lev1 odb:lev1 odb-lev1 // pass

// odb-lev1> [txxt]lev1> // dele [txxt]txxt|1>
// odb-lv2p> // dele [odb]lv2p> 
// odb-lev3> [teet_con]lev3> // dele [txxt_con]txxt_con|3>  
// odb-lv4p> // dele odb-lv4p> 

char *prompt_level_label(uint32 run_level) {
    static char display_label[OBJN_LENGTH];
    char *prompt;
    if (LEVEL_EXTEND_SPACE & run_level) {
        if (LVTP_ONE == ONLY_LEVEL_VALUE(run_level)) {
            prompt = lscpy(display_label, "olv1.");
            prompt = lscpy(prompt, _leve_defa_obje_.obje_iden);
            prompt = lscpy(prompt, "> ");
        } else if (LVTP_THRE == ONLY_LEVEL_VALUE(run_level)) {
            prompt = lscpy(display_label, _leve_defa_obje_.obje_iden);
            prompt = lscpy(prompt, "-lev3> ");
        }
        prompt = display_label;
    } else prompt = (char *) level_tab[ONLY_LEVEL_VALUE(run_level)];
    // CLIT_PF("[FUNC]:prompt_level_label, prompt:|%s|, obje_iden:|%s|\n", prompt, _leve_defa_obje_.obje_iden);
    return prompt;
}
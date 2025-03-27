
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "../cli_struct.h"
#include "../cli_bzl.h"

#include "prompt_utili.h"

//

const char *cmode_tab[] = {
    "clie: ",
    "osev: ",
    "level-4+> "
};

static const char *level_tab[] = {
    "level-1> ",
    "level-2+> ",
    "level-3> ",
    "level-4+> "
};


const char *multi_blank_tab[] = {
    "      ",
    "        ",
    "         "
};

// l3|teet_con>  teet_con|l3> teet_con|l1>
// teet_con|3>  level-4+> 

char *prompt_level(uint32 run_level) {
    static char obje_label[OBJN_LENGTH];
    char *prompt;
    if (LEVEL_EXTEND_SPACE & run_level) {
        if (LVTP_ONE == ONLY_LEVEL_VALUE(run_level))
            lscpy(lscpy(obje_label, _leve_defa_obje_.obje_iden), "|1> ");
        else if (LVTP_THRE == ONLY_LEVEL_VALUE(run_level))
            lscpy(lscpy(obje_label, _leve_defa_obje_.obje_iden), "|3> ");
        prompt = obje_label;
    } else prompt = (char *) level_tab[ONLY_LEVEL_VALUE(run_level)];
    // CLIEPF("[FUNC]:prompt_level, prompt:|%s|, obje_iden:|%s|\n", prompt, _leve_defa_obje_.obje_iden);
    return prompt;
}
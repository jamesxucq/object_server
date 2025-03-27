
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "osev_macro.h"
#include "stri_utili.h"
#include "../clit_macro.h"
#include "../cinstru.h"
#include "filli_conve.h"
#include "../clit_bzl.h"

#include "conve_lvikoi.h"
#include "../debug_funct_sh.h"
//

// test:test(777, "first");
// test:test(333, "second") > mycon;

char *conve_instru_lvikoi(clit_inst *cinst, uint32 cli_mode, uint32 run_level) {
    // CLIT_PF("---------- conve start.....\n");
    // PRIN_clit_instru(cinst);
    char *line_str = cinst->coline;
    char *conve_tok = NULL;
    //
    if (CITP_CLEV == cli_mode) {
        switch (ONLY_LEVEL_VALUE(run_level)) {
            case LVTP_ONE:
                if (!is_creat_metho(cinst->obje_iden, cinst->cont_levivk)) {
                    if ((LEVEL_EXTEND_SPACE & run_level) && !have_defa_obje(line_str)) {
                        conve_tok = filli_creat_metho_exte((char *) cinst->obje_iden, cinst->cont_levivk, line_str);
                    } else conve_tok = filli_creat_metho((char *) cinst->obje_iden, cinst->cont_levivk, line_str);
                }
                break;
            case LVTP_TWOP:
                if (!is_creat_class(cinst->obje_iden, cinst->cont_levivk))
                    conve_tok = filli_creat_class((char *) cinst->obje_iden, cinst->cont_levivk, line_str);
                break;
            case LVTP_THRE:
                if (LEVEL_EXTEND_SPACE & run_level) {
                    if (!IS_CREAT_OBJE(cinst->obje_iden, cinst->cont_levivk))
                        conve_tok = filli_creat_eobje_exte((char *) cinst->obje_iden, cinst->cont_levivk, line_str);
                } else if (!check_redirect_obje(line_str)) {
                    if (!IS_CREAT_OBJE(cinst->obje_iden, cinst->cont_levivk))
                        conve_tok = filli_creat_eobje_redi((char *) cinst->obje_iden, cinst->cont_levivk, line_str);
                }
                break;
            case LVTP_FOUP:
                // odb-lv4p> witi:witi("taat_con", "txxt") > odb;
#ifdef _CREAT_COBJE_REDIRECT
                if (!check_redirect_obje(line_str)) {
                    if (!IS_CREAT_OBJE(cinst->obje_iden, cinst->cont_levivk))
                        conve_tok = filli_creat_cobje((char *) cinst->obje_iden, cinst->cont_levivk, line_str);
                }
#else
                if (!IS_CREAT_OBJE(cinst->obje_iden, cinst->cont_levivk))
                    conve_tok = filli_creat_cobje((char *) cinst->obje_iden, cinst->cont_levivk, line_str);
#endif // _CREAT_COBJE_REDIRECT
                break;
        }
    }
    CLIT_PF("---------- conve end\n");
    // PRIN_clit_instru(cinst);
    return conve_tok;
}


//

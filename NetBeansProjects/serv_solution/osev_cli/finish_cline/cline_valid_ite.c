#include "commo_header.h"

#include "parse_cline.h"

#include "cline_valid_ite.h"
#include "../debug_funct_sh.h"

int finish_coline_ite(char (*inst_stri)[LARGE_TEXT_SIZE], char *line_str, uint32 cli_mode, uint32 run_level) {
    // CLIT_PF("[FUNC]finish_coline_ite\n");
    // CLIT_PF("line_str:|%s| cli_mode:%u run_level:%u\n", line_str, cli_mode, run_level);
    static char cline_whole[LARGE_TEXT_SIZE];
    if ('\0' == line_str[0x00]) return 0x02;
    strcat(cline_whole, line_str);
    // 0x00: end
    if (split_instru_conte(inst_stri, cline_whole, cli_mode))
        return 0x01;
    //
    int conti_valu = 0x00;
    for (; '\0' != (*inst_stri)[0x00] && !conti_valu; ++inst_stri) {
        CLIT_PF("inst_stri[0x00]:|%s|\n", inst_stri[0x00]);
        // 0:end 1:contine 0x02:exception -1:error
        conti_valu |= finis_cline_valid(inst_stri[0x00], cli_mode, run_level);
        // CLIT_PF("conti_valu:%d\n", conti_valu);
    }
    switch (conti_valu) {
        case 0x00:
        case -1:
            MK_ZERO(cline_whole);
            break;
        case 0x01:
            if ('\0' != (*inst_stri)[0x00]) {
                MK_ZERO(cline_whole);
                conti_valu = -1;
            }
            break;
        case 0x02:
        default:
            _LOG_WARN("default: exception");
            break;
    }
    //
    return conti_valu;
}





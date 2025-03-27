#include "commo_header.h"

#include "../clit_macro.h"
#include "../cstri_utili.h"

#include "parse_cline.h"
#include "../debug_funct_sh.h"

// 0x00: end

int split_instru_conte(char (*inst_stri)[LARGE_TEXT_SIZE], char *cline_whole, uint32 cli_mode) {
    int conte_valu = 0x00; // 0x00:cmd 0x01:continue -1:error
    switch (cli_mode) {
        case CITP_CLIE:
            conte_valu = single_instru(inst_stri, cline_whole);
            break;
        case CITP_OSVB:
        case CITP_CLEV:
            conte_valu = multi_instru(inst_stri, cline_whole);
            break;
        default:
            break;
    }
    //
    return conte_valu;
}

//
static const char* objtit_tab[] = {
    "clie",
    "osev",
    "odb",
    "kits"
};

static int cline_leve1(char *line_str) {
    CLIT_PF("[FUNC]cline_leve1\n");
    static int continue_step;
    int continue_type = 0x00; //0x00:end 0x01:continue -1:error
    CLIT_PF("1 continue_step:%d continue_type:%d\n", continue_step, continue_type);
    if (!continue_step) {
        if (!accep_base_metho(line_str, objtit_tab[0x00], objtit_tab[0x02], objtit_tab[0x03]))
            continue_step = 0x01;
        else if (!is_defin_metho(line_str)) continue_step = 0x02;
        else if (!is_opera_invok(line_str)) continue_step = 0x03;
        else continue_type = -1;
    }
    CLIT_PF("2 continue_step:%d continue_type:%d\n", continue_step, continue_type);
    switch (continue_step) {
        case 0x01:
            continue_type = invok_metho_finis(line_str);
            break;
        case 0x02:
            continue_type = metho_defin_finis(line_str);
            break;
        case 0x03:
            continue_type = opera_invok_finis(line_str);
            break;
        default:
            break;
    }
    CLIT_PF("3 continue_step:%d continue_type:%d\n", continue_step, continue_type);
    if (0x01 != continue_type) continue_step = 0x00;
    return continue_type;
}

static int cline_lev2p(char *line_str) {
    CLIT_PF("[FUNC]cline_lev2p\n");
    static int continue_step;
    int continue_type = 0x00; //0x00:end 0x01:continue -1:error
    CLIT_PF("1 continue_step:%d continue_type:%d\n", continue_step, continue_type);
    if (!continue_step) {
        if (!accep_base_metho(line_str, objtit_tab[0x00], objtit_tab[0x02], objtit_tab[0x03]))
            continue_step = 0x01;
        else if (!is_defin_metho(line_str)) continue_step = 0x02;
        else if (!is_defin_class(line_str)) continue_step = 0x03;
        else if (!is_opera_colle(line_str)) continue_step = 0x04;
        else continue_type = -1;
    }
    CLIT_PF("2 continue_step:%d continue_type:%d\n", continue_step, continue_type);
    switch (continue_step) {
        case 0x01:
            continue_type = invok_metho_finis(line_str);
            break;
        case 0x02:
            continue_type = metho_defin_finis(line_str);
            break;
        case 0x03:
            continue_type = class_defin_finis(line_str);
            break;
        case 0x04:
            continue_type = opera_colle_finis(line_str);
            break;
        default:
            break;
    }
    CLIT_PF("3 continue_step:%d continue_type:%d\n", continue_step, continue_type);
    if (0x01 != continue_type) continue_step = 0x00;
    return continue_type;
}

static int cline_leve3(char *line_str) {
    // CLIT_PF("[FUNC]cline_leve3\n");
    static int continue_step;
    int continue_type = 0x00; //0x00:end 0x01:continue -1:error
    // CLIT_PF("1 continue_step:%d continue_type:%d\n", continue_step, continue_type);
    if (!continue_step) {
        if (!accep_base_metho(line_str, objtit_tab[0x00], objtit_tab[0x02], objtit_tab[0x03]))
            continue_step = 0x01;
        else if (!is_opera_const(line_str)) continue_step = 0x02;
        else continue_type = -1;
    }
    // CLIT_PF("2 continue_step:%d continue_type:%d\n", continue_step, continue_type);
    switch (continue_step) {
        case 0x01:
            continue_type = invok_metho_finis(line_str);
            break;
        case 0x02:
            continue_type = opera_const_finis(line_str);
            break;
        default:
            break;
    }
    // CLIT_PF("3 continue_step:%d continue_type:%d\n", continue_step, continue_type);
    if (0x01 != continue_type) continue_step = 0x00;
    return continue_type;
}

static int cline_lev4p(char *line_str) {
    // CLIT_PF("[FUNC]cline_lev4p\n");
    static int continue_step;
    int continue_type = 0x00; //0x00:end 0x01:continue -1:error
    // CLIT_PF("1 continue_step:%d continue_type:%d\n", continue_step, continue_type);
    if (!continue_step) {
        if (!accep_base_metho(line_str, objtit_tab[0x00], objtit_tab[0x02], objtit_tab[0x03]))
            continue_step = 0x01;
        else if (!is_opera_query(line_str)) continue_step = 0x02;
        else continue_type = -1;
    }
    // CLIT_PF("2 continue_step:%d continue_type:%d\n", continue_step, continue_type);
    switch (continue_step) {
        case 0x01:
            continue_type = invok_metho_finis(line_str);
            break;
        case 0x02:
            continue_type = opera_query_finis(line_str);
            break;
        default:
            break;
    }
    // CLIT_PF("3 continue_step:%d continue_type:%d\n", continue_step, continue_type);
    if (0x01 != continue_type) continue_step = 0x00;
    return continue_type;
}

//

static int level_check_line(char *line_str, uint32 run_level) {
    static int conti_valu; // 0x00:cmd 0x01:continue -1:error
    // CLIT_PF("[FUNC]level_check_line run_level:%08X line_str:|%s|\n", run_level, line_str);
    switch (ONLY_LEVEL_VALUE(run_level)) {
        case LVTP_ONE:
            conti_valu = cline_leve1(line_str);
            break;
        case LVTP_TWOP:
            conti_valu = cline_lev2p(line_str);
            break;
        case LVTP_THRE:
            conti_valu = cline_leve3(line_str);
            break;
        case LVTP_FOUP:
            conti_valu = cline_lev4p(line_str);
            break;
        default:
            break;
    }
    //CLIT_PF("[FUNC]level_check_line conti_valu:%d\n", conti_valu);
    return conti_valu;
}

static int clie_check_line(char *line_str) {
    static int continue_step;
    int continue_type = 0x00; //0x00:end 0x01:continue -1:error
    //
    if (!continue_step) {
        // CLIT_PF("[FUNC]clie_check_line 1:%d\n", continue_type);
        if (!accep_clie_metho(line_str, objtit_tab[0x00])) {
            continue_step = 0x01;
            // CLIT_PF("[FUNC]clie_check_line 2:%d\n", continue_type);
        } else continue_type = 0x00;
    }
    if (0x01 == continue_step) {
        // CLIT_PF("[FUNC]clie_check_line 3:%d\n", continue_type);
        continue_type = invok_metho_finis(line_str);
    }
    // CLIT_PF("[FUNC]continue_type:%d\n", continue_type);
    if (0x01 != continue_type) continue_step = 0x00;
    return continue_type;
}

static int osev_check_line(char *line_str) {
    static int continue_step;
    int continue_type = 0x00; //0x00:end 0x01:continue -1:error
    //
    if (!continue_step) {
        // CLIT_PF("[FUNC]osev_check_line 1\n");
        if (!accep_osev_metho(line_str, objtit_tab[0x00], objtit_tab[0x01]) ||
                !accep_user_metho(line_str)) {
            continue_step = 0x01;
            // CLIT_PF("[FUNC]osev_check_line 2\n");
        } else continue_type = -1;
    }
    if (0x01 == continue_step) {
        // CLIT_PF("[FUNC]osev_check_line 3\n");
        continue_type = invok_metho_finis(line_str);
    }
    // CLIT_PF("[FUNC]continue_type:%d\n", continue_type);
    if (0x01 != continue_type) continue_step = 0x00;
    return continue_type;
}

// 0:end 1:contine 0x02:exception -1:error

int finis_cline_valid(char *line_str, uint32 cli_mode, uint32 run_level) {
    int conti_valu = 0x00; //0x00:cmd 0x01:continue -1:error
    switch (cli_mode) {
        case CITP_CLEV:
            conti_valu = level_check_line(line_str, run_level);
            break;
        case CITP_OSVB:
            conti_valu = osev_check_line(line_str);
            break;
        case CITP_CLIE:
            conti_valu = clie_check_line(line_str);
            break;
        default:
            break;
    }
    // CLIT_PF("[FUNC]finis_cline_valid conti_valu:%d\n", conti_valu);
    return conti_valu;
}


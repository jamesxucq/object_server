
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "expre_analy.h"
#include "exptoke.h"

//
static const struct stui_node alpha_value_dict[] = {
    {"OR", OR_TOKE},
    {"AND", AND_TOKE},
    {"NOT", NOT_TOKE},
    {"IS", IS_TOKE},
    {"MATCH", MATCH_TOKE},
    {"LIKE", LIKE_KW_TOKE},
    {"BETWEEN", BETWEEN_TOKE},
    {"IN", IN_TOKE},
    {"ESCAPE", ESCAPE_TOKE},
    {"CTIME", CTIME_KW_TOKE},
    {"ISNULL", ISNULL_TOKE},
    {"NOTNULL", NOTNULL_TOKE},
    {"BITAND", BITAND_TOKE},
    {"BITOR", BITOR_TOKE},
    {"LSHIFT", LSHIFT_TOKE},
    {"RSHIFT", RSHIFT_TOKE},
    {"CONCAT", CONCAT_TOKE},
    {"COLLATE", COLLATE_TOKE},
    {"BITNOT", BITNOT_TOKE},
    {"ON", ON_TOKE},
    {"JOIN", JOIN_KW_TOKE},
    {"NULL", NULL_TOKE},
    {NULL, ID_TOKE}
};

unsigned int get_alpha_toke(char *toke_stri) {
    unsigned int alpha_toke;
    KV_STUI_EQUA(alpha_toke, alpha_value_dict, toke_stri);
    return alpha_toke;
}
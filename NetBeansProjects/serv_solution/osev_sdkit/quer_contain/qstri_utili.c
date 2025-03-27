
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_header.h"
#include "kcstr_utili.h"
#include "qstri_utili.h"
#include "lv2p_expand.h"
#include "lv2p_decla.h"


// 0x00: is decla, 0x01: not decla

int chk_lv2p_decl(char *lv2p_cont) {
    char *cotok = strchr(lv2p_cont, '<');
    if (!cotok) return 0x01;
    cotok = strchr(++cotok, '>');
    if (!cotok) return 0x01;
    //
    return 0x00;
}

//

static inline char *conve_columns(char *columns, char *data) {
    columns = lccpy(columns, ',');
    columns = lscpy(columns, data);
    return columns;
}

//

static int creat_columns_types(char *types, char *columns, char (*data)[PARAM_LENGTH]) {
    char type[PARAM_LENGTH], valu[PARAM_LENGTH], size[PARAM_LENGTH];
    //
    for (; '\0' != (*data)[0x00]; ++data) {
        if (split_data_styl(type, valu, size, data[0x00]))
            return -1;
        // OSEVPF("lv2p_prop[inde]:|%s|\n", data[inde]);
        types = conve_types(types, type, size);
        columns = conve_columns(columns, valu);
    }
    return 0x00;
}

// "key_format=3t,value_format=SSS,columns=(id,name,address,phone)"

static char *conte_columns_types(char *forma, char *types, char *columns) {
    forma = lscpy(forma, "key_format=R, value_format=");
    forma = lscpy(forma, types);
    forma = lscpy(forma, ", columns=(stoid");
    forma = lscpy(forma, columns);
    forma = lccpy(forma, ')');
    //
    return forma;
}

int conve_conta_types(char *forma_types, char (*lv2p_prop)[PARAM_LENGTH]) {
    char types[TYPES_LENGTH];
    char columns[COLUMN_LENGTH];
    //
    creat_columns_types(types, columns, lv2p_prop);
    conte_columns_types(forma_types, types, columns);
    // OSEVPF("forma_types:|%s|\n", forma_types);
    return 0x00;
}

//

char *stati_rcont_types(char *forma, uint32 refe_coun) {
    static char *refe_columns[] = {", ss1, si1", ", ss2, si2", ", ss3, si3", ", ss4, si4"};
    forma = lscpy(forma, "key_format=R, value_format=");
    unsigned int inde = 0x00;
    for (; refe_coun > inde; ++inde) {
        forma = lscpy(forma, "RB");
    }
    forma = lscpy(forma, ", columns=(stoid");
    char **rcolum = refe_columns;
    inde = 0x00;
    for (; refe_coun > inde; ++inde, ++rcolum) {
        forma = lscpy(forma, rcolum[0x00]);
    }
    forma = lccpy(forma, ')');
    //
    return forma;
}

//

char *dynam_rcont_types(char *forma, uint32 refe_coun) {
    static char *refe_columns[] = {", ds1", ", ds2", ", ds3", ", ds4"};
    forma = lscpy(forma, "key_format=R, value_format=");
    unsigned int inde = 0x00;
    for (; refe_coun > inde; ++inde) {
        forma = lccpy(forma, 'R');
    }
    forma = lscpy(forma, ", columns=(stoid");
    char **rcolum = refe_columns;
    inde = 0x00;
    for (; refe_coun > inde; ++inde, ++rcolum) {
        forma = lscpy(forma, rcolum[0x00]);
    }
    forma = lccpy(forma, ')');
    //
    return forma;
}

//

static char *find_inne_parm(lev1_decl_t *lv1dats, char *ident, int posi) {
    lev1_decl_t *lv1d = lv1dats;
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        if (!strcmp(ident, lv1d->ident)) {
            if (posi < lv1d->innep.inne_count)
                return lv1d->innep.inne_pams[posi];
        }
    }
    return NULL;
}

char *match_field_lev1d(lev1_decl_t *lv1datd, lev1_decl_t *lv1dats, lv2p_prop *l2_nod) {
    char **innep;
    unsigned int inde;
    lev1_decl_t *lv1d = lv1datd;
    for (; LVTP_TYPE_NONE != lv1d->levtyp; ++lv1d) {
        innep = lv1d->innep.inne_pams;
        inde = 0x00;
        for (; innep[0x00]; ++inde, ++innep) {
            if (!strcmp(l2_nod->name, innep[0x00])) {
                return find_inne_parm(lv1dats, lv1d->ident, inde);
            }
        }
    }
    //
    return NULL;
}

char *match_field_lv2po(lv2p_prop *lv2nod, lv2p_prop *l2_nod) {
    lv2p_prop *l2nod = lv2nod;
    for (; ACCE_COTRL_INVAL != l2nod->access; ++l2nod) {
        if (!strcmp(l2_nod->name, l2nod->name))
            return l2_nod->name;
    }
    return NULL;
}


//




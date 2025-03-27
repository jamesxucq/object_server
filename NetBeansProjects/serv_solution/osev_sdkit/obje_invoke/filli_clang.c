
#include "commo_header.h"
#include "kcomm_header.h"

#include "ostri_utili.h"
#include "trans/trans_utili.h"
#include "lev1_decla.h"
#include "lv2p_decla.h"

#include "filli_clang.h"
#include "debug_funct_oi.h"
// trans-serve

char *filli_lv2po_struct(char *clang_str, char *lv2pn, char (*lv2p_prop)[PARAM_LENGTH]) {
    clang_str = lscpy(clang_str, "#pragma pack(1)\nstruct ");
    clang_str = lscpy(clang_str, lv2pn);
    clang_str = lscpy(clang_str, " {\n");
    clang_str = lscpy(clang_str, "osv_oid_i obje_obid;\n");
    for (; '\0' != (*lv2p_prop)[0x00]; ++lv2p_prop) {
        clang_str = lscpy(clang_str, lv2p_prop[0x00]);
        clang_str = lscpy(clang_str, ";\n");
    }
    clang_str = lscpy(clang_str, "};\n#pragma pack() \n");
    //
    return clang_str;
}

// trans-serve

char *filli_metho_function(char *clang_str, conve_metho *metho) {
    // PRIN_parse_metho(metho); // for test
    clang_str = lscpy(clang_str, "void ");
    clang_str = lscpy(clang_str, metho->lv2pn);
    clang_str = lccpy(clang_str, '_');
    clang_str = lscpy(clang_str, metho->lev1n);
    clang_str = lccpy(clang_str, '_');
    clang_str = lscpy(clang_str, metho->oivk_fmtsp);
    clang_str = lscpy(clang_str, metho->line_oivk);
    clang_str = lscpy(clang_str, metho->lev1_body);
    clang_str = lccpy(clang_str, '\n');
    //
    return clang_str;
}

// trans-serve

char *filli_const_function(char *clang_str, conve_metho *metho) {
    // PRIN_parse_metho(metho); // for test
    clang_str = lscpy(clang_str, "void ");
    clang_str = lscpy(clang_str, metho->lv2pn);
    clang_str = lccpy(clang_str, '_');
    clang_str = lscpy(clang_str, metho->lev1n);
    clang_str = lccpy(clang_str, '_');
    clang_str = lscpy(clang_str, metho->oivk_fmtsp);
    clang_str = lscpy(clang_str, metho->line_oivk);
    clang_str = lscpy(clang_str, metho->lev1_body);
    clang_str = lccpy(clang_str, '\n');
    //
    return clang_str;
}

//

char *filli_oinvk_struct(char *clang_str, conve_metho *metho, char (*oik_dat)[PARAM_LENGTH]) {
    clang_str = lscpy(clang_str, "#pragma pack(1)\nstruct ");
    clang_str = lccpy(clang_str, '_');
    clang_str = lscpy(clang_str, metho->lv2pn);
    clang_str = lccpy(clang_str, '_');
    clang_str = lscpy(clang_str, metho->lev1n);
    clang_str = lccpy(clang_str, '_');
    clang_str = lscpy(clang_str, metho->oivk_fmtsp);
    clang_str = lccpy(clang_str, '_');
    clang_str = lscpy(clang_str, " {\n");
    for (; '\0' != (*oik_dat)[0x00]; ++oik_dat)
        clang_str = lscpy(clang_str, oik_dat[0x00]);
    clang_str = lscpy(clang_str, "};\n#pragma pack() \n");
    return clang_str;
}

//

char *filli_oinvk_istruc(char *clang_str, conve_metho *metho, char (*oik_dat)[PARAM_LENGTH], char *lv2pn) {
    clang_str = lscpy(clang_str, "#pragma pack(1)\nstruct ");
    clang_str = lccpy(clang_str, '_');
    clang_str = lscpy(clang_str, lv2pn);
    clang_str = lccpy(clang_str, '_');
    clang_str = lscpy(clang_str, metho->lev1n);
    clang_str = lccpy(clang_str, '_');
    clang_str = lscpy(clang_str, metho->oivk_fmtsp);
    clang_str = lccpy(clang_str, '_');
    clang_str = lscpy(clang_str, " {\n");
    for (; '\0' != (*oik_dat)[0x00]; ++oik_dat)
        clang_str = lscpy(clang_str, oik_dat[0x00]);
    clang_str = lscpy(clang_str, "};\n#pragma pack() \n");
    return clang_str;
}

//

char *filli_metho_ifunctio(char *clang_str, conve_metho *metho, char *lv2pn) {
    // PRIN_parse_metho(metho); // for test
    clang_str = lscpy(clang_str, "void ");
    clang_str = lscpy(clang_str, lv2pn);
    clang_str = lccpy(clang_str, '_');
    clang_str = lscpy(clang_str, metho->lev1n);
    clang_str = lccpy(clang_str, '_');
    clang_str = lscpy(clang_str, metho->oivk_fmtsp);
    clang_str = lscpy(clang_str, metho->line_oivk);
    clang_str = lscpy(clang_str, metho->lev1_body);
    clang_str = lccpy(clang_str, '\n');
    //
    return clang_str;
}

//

char *filli_rllv2p_conte(char *clang_str, char *lv2pn, lv2p_prop *l2_nod, char *colu_types, colum *colu_data) {
    OSEVPF("[FUNC]:filli_rllv2p_conte\n");
    // OSEVPF("lv2pn:|%s|\n", lv2pn);
    clang_str = filli_include_head(clang_str);
    clang_str = filli_rlv2pd_struct(clang_str, lv2pn, l2_nod);
    //
    clang_str = filli_rloivk_struct(clang_str, lv2pn, colu_types, colu_data);
    clang_str = filli_rloivk_function(clang_str, lv2pn, colu_types, colu_data);
    return clang_str;
}

//

void filli_parms_oinvk(OUT char *oikdat, pamv_node *pamnod) {
    char *clan_type;
    KV_STST_EQUA(clan_type, ostyp_clang_dict, pamnod->type);
    if (PARM_NUMB & pamnod->attri) {
        oikdat = lsprif(oikdat, "%s %s;\n", clan_type, pamnod->name);
    } else if ((PARM_BYTE | PARM_STRI) & pamnod->attri) {
        if (PARM_ARRAY & pamnod->attri)
            oikdat = lsprif(oikdat, "%s %s[%s];\n", clan_type, pamnod->name, pamnod->array);
        else oikdat = lsprif(oikdat, "%s %s;\n", clan_type, pamnod->name);
    } else if (PARM_STRZ & pamnod->attri) {
        oikdat = lsprif(oikdat, "%s %s;\n", clan_type, pamnod->name);
    }
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"

#include "../../clit_struct.h"
#include "tstri_utili.h"
#include "filli_inline.h"
#include "seri_leng.h"
#include "../common/ccomm_types.h"

#include "filli_clang.h"
#include "../../debug_funct_sh.h"

//

int filli_lv2p_conte(clit_resu *resul, char *clang_str, char *lv2pn, char *basen) {
    CLIT_PF("[FUNC]:filli_lv2p_conte\n");
    char resu_cont[CLANG_CONTE_SIZE];
    MK_ZERO(resu_cont);
    //
    char *last_str = filli_lv2p_head(resu_cont, lv2pn, basen);
    last_str = lscpy(last_str, clang_str);
    last_str = filli_lv2p_tail(last_str, lv2pn);
    //
    return produ_resul_conte(resul, resu_cont);
}

//

int filli_lev1_conte(clit_resu *resul, char *clang_str, char *lv2pn, char *basen) {
    CLIT_PF("[FUNC]:filli_lev1_conte\n");
    char resu_cont[CLANG_CONTE_SIZE];
    MK_ZERO(resu_cont);
    //
    char *last_str = filli_lev1_head(resu_cont, lv2pn, basen);
    last_str = lscpy(last_str, clang_str);
    //
    return produ_resul_conte(resul, resu_cont);
}

//
// Serialize

char *filli_meta_seria(char *clang_str, char *lv2pn, lv2p_prop *lv2nod) {
    CLIT_PF("[FUNC]:filli_meta_seria\n");
    clang_str = lsprif(clang_str, "int %s::Serialize(PK_PACK_STREAM *pkps, %s *obje) { \n", lv2pn, lv2pn);
    clang_str = lscpy(clang_str, "if (paki_pack_obid(pkps, &obje->obje_obid)) return -1; \n");
    //
    for (; ACCE_COTRL_INVAL != lv2nod->access; ++lv2nod) {
        switch (lv2nod->potyp) {
            case DATY_INVAL:
                _LOG_WARN("case: DATY_INVAL");
                break;
            case DATY_BYTE:
                clang_str = lsprif(clang_str, "if (paki_pack_byte(pkps, obje->%s)) return -1; \n", lv2nod->name);
                break;
            case DATY_UBYTE:
                clang_str = lsprif(clang_str, "if (paki_pack_ubyte(pkps, obje->%s)) return -1; \n", lv2nod->name);
                break;
            case DATY_SHORT:
                clang_str = lsprif(clang_str, "if (paki_pack_short(pkps, obje->%s)) return -1; \n", lv2nod->name);
                break;
            case DATY_USHORT:
                clang_str = lsprif(clang_str, "if (paki_pack_ushort(pkps, obje->%s)) return -1; \n", lv2nod->name);
                break;
            case DATY_INT:
                clang_str = lsprif(clang_str, "if (paki_pack_int32(pkps, obje->%s)) return -1; \n", lv2nod->name);
                break;
            case DATY_UINT:
                clang_str = lsprif(clang_str, "if (paki_pack_uint32(pkps, obje->%s)) return -1; \n", lv2nod->name);
                break;
            case DATY_LLONG:
                clang_str = lsprif(clang_str, "if (paki_pack_int64(pkps, obje->%s)) return -1; \n", lv2nod->name);
                break;
            case DATY_ULLONG:
                clang_str = lsprif(clang_str, "if (paki_pack_uint64(pkps, obje->%s)) return -1; \n", lv2nod->name);
                break;
            case DATY_OBID:
                clang_str = lsprif(clang_str, "if (paki_pack_obid(pkps, obje->%s)) return -1; \n", lv2nod->name);
                break;
            case DATY_FLOAT:
                clang_str = lsprif(clang_str, "if (paki_pack_float(pkps, obje->%s)) return -1; \n", lv2nod->name);
                break;
            case DATY_DOUBLE:
                clang_str = lsprif(clang_str, "if (paki_pack_double(pkps, obje->%s)) return -1; \n", lv2nod->name);
                break;
            case DATY_STRI:
                // STRI_PAMSTYL(PSCON, LENVAL, SVALU)
                clang_str = lsprif(clang_str, "if (paki_pack_stri(pkps, obje->%s)) return -1; \n", lv2nod->name);
                break;
            case DATY_STRZ:
                // STRZ_PAMSTYL(PSCON, LEN_VALU, SVALU)
                clang_str = lsprif(clang_str, "if (paki_pack_strz(pkps, obje->%s)) return -1; \n", lv2nod->name);
                break;
            case DATY_BINARY:
                // BINARY_PAMSTYL(PSCON, LEN_VALU, SVALU, ENLEN)
                clang_str = lsprif(clang_str, "if (paki_pack_item(pkps, (PK_ITEM *) &obje->%s)) return -1; \n", lv2nod->name);
                break;
            default:
                _LOG_WARN("default: filli_meta_seria");
                break;
        }
    }
    clang_str = lscpy(clang_str, "return 0x00; \n} \n");
    // CLIT_PF("[FUNC]:end filli_meta_seria\n");
    return clang_str;
}

// Deserialize

char *filli_meta_deseri(char *clang_str, char *lv2pn, lv2p_prop *lv2nod) {
    clang_str = lsprif(clang_str, "int %s::Deserialize(%s *obje, PK_PACK_STREAM *pkps) { \n", lv2pn, lv2pn);
    // clang_str = lsprif(clang_str, "memcpy(&obje->obje_obid, &((struct _%s_ *)data)->obje_obid, sizeof(osv_oid_t)); \n", lv2pn);
    clang_str = lscpy(clang_str, "if (paki_unpack_OBID(pkps, &obje->obje_obid)) return -1;\n");
    //
    for (; ACCE_COTRL_INVAL != lv2nod->access; ++lv2nod) {
        switch (lv2nod->potyp) { // fixme: 20231015 xxxxx
            case DATY_INVAL:
                _LOG_WARN("case: DATY_INVAL");
                break;
            case DATY_BYTE:
                clang_str = lsprif(clang_str, "if (paki_unpack_byte(pkps, &obje->%s)) return -1; \n", lv2nod->name);
                break;
            case DATY_UBYTE:
                clang_str = lsprif(clang_str, "if (paki_unpack_ubyte(pkps, &obje->%s)) return -1; \n", lv2nod->name);
                break;
            case DATY_SHORT:
                clang_str = lsprif(clang_str, "if (paki_unpack_short(pkps, &obje->%s)) return -1; \n", lv2nod->name);
                break;
            case DATY_USHORT:
                clang_str = lsprif(clang_str, "if (paki_unpack_ushort(pkps, &obje->%s)) return -1; \n", lv2nod->name);
                break;
            case DATY_INT:
                clang_str = lsprif(clang_str, "if (paki_unpack_int32(pkps, &obje->%s)) return -1;\n", lv2nod->name);
                break;
            case DATY_UINT:
                clang_str = lsprif(clang_str, "if (paki_unpack_uint32(pkps, &obje->%s)) return -1; \n", lv2nod->name);
                break;
            case DATY_LLONG:
                clang_str = lsprif(clang_str, "if (paki_unpack_int64(pkps, &obje->%s)) return -1; \n", lv2nod->name);
                break;
            case DATY_ULLONG:
                clang_str = lsprif(clang_str, "if (paki_unpack_uint64(pkps, &obje->%s)) return -1; \n", lv2nod->name);
                break;
            case DATY_OBID:
                clang_str = lsprif(clang_str, "if (paki_unpack_OBID(pkps, &obje->%s)) return -1; \n", lv2nod->name);
                break;
            case DATY_FLOAT:
                clang_str = lsprif(clang_str, "if (paki_unpack_float(pkps, &obje->%s)) return -1; \n", lv2nod->name);
                break;
            case DATY_DOUBLE:
                clang_str = lsprif(clang_str, "if (paki_unpack_double(pkps, &obje->%s)) return -1; \n", lv2nod->name);
                break;
            case DATY_STRI:
                // COMPA_STRI(NVALU, PSCON, LEN_VALU)
                clang_str = lsprif(clang_str, "if (paki_unpack_STRI(pkps, obje->%s, %u)) return -1; \n", lv2nod->name, lv2nod->size);
                break;
            case DATY_STRZ:
                // COMPA_STRZ(NVALU, PSCON)
                clang_str = lsprif(clang_str, "if (paki_unpack_STRZ(pkps, obje->%s)) return -1; \n", lv2nod->name);
                break;
            case DATY_BINARY:
                // COMPA_BINA(NVALU, PSCON)
                clang_str = lsprif(clang_str, "if (paki_unpack_ITEM(pkps, (PK_ITEM *) obje->%s)) return -1; \n", lv2nod->name);
                break;
            default:
                _LOG_WARN("default: filli_meta_deseri");
                break;
        }
    }
    clang_str = lscpy(clang_str, "return 0x00; \n} \n");
    //
    return clang_str;
}

//

int filli_ointe_comple(char *line_oivk, char (*oivk_data)[PARAM_LENGTH]) {
    // CLIT_PF("[FUNC]:conve_ointe_comple\n");
    line_oivk = lscpy(line_oivk, "(");
    if ('\0' != (*oivk_data)[0x00]) {
        line_oivk = lscpy(line_oivk, oivk_data[0x00]);
        ++oivk_data;
    }
    for (; '\0' != (*oivk_data)[0x00]; ++oivk_data) {
        line_oivk = lscpy(line_oivk, ", ");
        line_oivk = lscpy(line_oivk, oivk_data[0x00]);
    }
    line_oivk = lccpy(line_oivk, ')');
    //
    return 0x00;
}

//

char *this_objec_assign(char *clang_str, lv2p_prop *lv2nod) {
    // DATA_TYPE prop_type;
    for (; ACCE_COTRL_INVAL != lv2nod->access; ++lv2nod) {
        switch (lv2nod->potyp) {
            case DATY_INVAL:
                _LOG_WARN("case: DATY_INVAL");
                break;
            case DATY_BYTE:
            case DATY_UBYTE:
            case DATY_SHORT:
            case DATY_USHORT:
            case DATY_INT:
            case DATY_UINT:
            case DATY_LLONG:
            case DATY_ULLONG:
                clang_str = lsprif(clang_str, "this->%s = %s; \n", lv2nod->name, lv2nod->name);
                break;
            case DATY_OBID:
                clang_str = lsprif(clang_str, "OBID_BINARY_COPY(&this->%s, &%s) \n", lv2nod->name, lv2nod->name);
                break;
            case DATY_FLOAT:
            case DATY_DOUBLE:
                clang_str = lsprif(clang_str, "this->%s = %s; \n", lv2nod->name, lv2nod->name);
                break;
            case DATY_STRI:
                clang_str = lsprif(clang_str, "memxpy(this->%s, %s, %d); \n", lv2nod->name, lv2nod->name, lv2nod->size);
                break;
            case DATY_STRZ:
                clang_str = lsprif(clang_str, "strcpy(this->%s, %s); \n", lv2nod->name, lv2nod->name);
                break;
            case DATY_BINARY:
                clang_str = lsprif(clang_str, "memxpy(this->%s, %s, %d); \n", lv2nod->name, lv2nod->name, lv2nod->size);
                break;
            default:
                _LOG_WARN("default: this_objec_assign");
                break;
        }
    }
    //
    return clang_str;
}

char *filli_lcon_defin(char *clang_str, char *lv2pn, lv2p_prop *lv2nod) {
    // txxt::txxt()
    clang_str = lscpy(clang_str, lv2pn);
    clang_str = lscpy(clang_str, "::");
    clang_str = lscpy(clang_str, lv2pn);
    clang_str = lscpy(clang_str, "() { \n");
    clang_str = lscpy(clang_str, "} \n");

    // txxt::txxt(int xx, int ax, int cx)
    clang_str = lscpy(clang_str, lv2pn);
    clang_str = lscpy(clang_str, "::");
    clang_str = lscpy(clang_str, lv2pn);
    clang_str = lscpy(clang_str, "(");
    int proper = 0x00;
    lv2p_prop *l2_nod = lv2nod;
    for (; ACCE_COTRL_INVAL != l2_nod->access; ++l2_nod) {
        if (proper) clang_str = lsprif(clang_str, ", %s %s", potyp_ostyp_tab[l2_nod->potyp], l2_nod->name);
        else {
            clang_str = lsprif(clang_str, "%s %s", potyp_ostyp_tab[l2_nod->potyp], l2_nod->name);
            proper = 0x01;
        }
    }
    clang_str = lscpy(clang_str, ") { \n");
    clang_str = this_objec_assign(clang_str, lv2nod);
    clang_str = lscpy(clang_str, "} \n");

    // txxt::txxt(osv_oid_t obje_obid, int xx, int ax, int cx)
    clang_str = lscpy(clang_str, lv2pn);
    clang_str = lscpy(clang_str, "::");
    clang_str = lscpy(clang_str, lv2pn);
    clang_str = lscpy(clang_str, "(osv_oid_t obje_obid");
    l2_nod = lv2nod;
    for (; ACCE_COTRL_INVAL != l2_nod->access; ++l2_nod) {
        clang_str = lsprif(clang_str, ", %s %s", potyp_ostyp_tab[l2_nod->potyp], l2_nod->name);
    }
    clang_str = lscpy(clang_str, ") { \n");
    clang_str = lscpy(clang_str, "OBID_BINARY_COPY(&this->obje_obid, &obje_obid) \n");
    clang_str = this_objec_assign(clang_str, lv2nod);
    clang_str = lscpy(clang_str, "} \n");
    //
    return clang_str;
}

//

char *filli_elv2p_decla(char *clang_str, lv2p_prop *lv2nod) {
    clang_str = lscpy(clang_str, "public: \n");
    clang_str = lscpy(clang_str, "osv_oid_t obje_obid; \n");
    //
    int proper = 0x00;
    lv2p_prop *l2_nod = lv2nod;
    for (; ACCE_COTRL_INVAL != l2_nod->access; ++l2_nod) {
        if (ACCE_COTRL_HIDE == l2_nod->access) {
            if (!proper) {
                clang_str = lscpy(clang_str, "private: \n");
                proper = 0x01;
            }
            clang_str = lsprif(clang_str, "%s %s;\n", potyp_ostyp_tab[l2_nod->potyp], l2_nod->name);
        }
    }
    //
    proper = 0x00;
    l2_nod = lv2nod;
    for (; ACCE_COTRL_INVAL != l2_nod->access; ++l2_nod) {
        if (ACCE_COTRL_INVISI == l2_nod->access) {
            if (!proper) {
                clang_str = lscpy(clang_str, "protected: \n");
                proper = 0x01;
            }
            clang_str = lsprif(clang_str, "%s %s;\n", potyp_ostyp_tab[l2_nod->potyp], l2_nod->name);
        }
    }
    //
    proper = 0x00;
    l2_nod = lv2nod;
    for (; ACCE_COTRL_INVAL != l2_nod->access; ++l2_nod) {
        if (ACCE_COTRL_AUTO == l2_nod->access) {
            if (!proper) {
                clang_str = lscpy(clang_str, "public: \n");
                proper = 0x01;
            }
            clang_str = lsprif(clang_str, "%s %s;\n", potyp_ostyp_tab[l2_nod->potyp], l2_nod->name);
        }
    }
    //
    return clang_str;
}

// trans-serve

char *filli_class_text(char *clang_str, char *lv2pn, char (*lv2p_prop)[PARAM_LENGTH]) {
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

//

char *filli_const_defin(char *clang_str, parse_metho *metho) {
    // PRIN_parse_metho(metho); // for test
    clang_str = lscpy(clang_str, metho->oivk_retyp_pm);
    clang_str = lccpy(clang_str, ' ');
    clang_str = lscpy(clang_str, metho->lv2pn);
    clang_str = lscpy(clang_str, "::Create");
    // clang_str = lscpy(clang_str, metho->lev1n);
    clang_str = lscpy(clang_str, metho->line_oivk);
    // clang_str = lscpy(clang_str, metho->lev1_body);
    clang_str = appe_obje_id(clang_str, metho->lev1_body);
    clang_str = lccpy(clang_str, '\n');
    //
    return clang_str;
}

//

char *filli_metho_defin(char *clang_str, parse_metho *metho) {
    // PRIN_parse_metho(metho); // for test
    clang_str = lscpy(clang_str, metho->oivk_retyp_pm);
    clang_str = lccpy(clang_str, ' ');
    clang_str = lscpy(clang_str, metho->lv2pn);
    clang_str = lscpy(clang_str, "::");
    clang_str = lscpy(clang_str, metho->lev1n);
    clang_str = lscpy(clang_str, metho->line_oivk);
    clang_str = lscpy(clang_str, metho->lev1_body);
    clang_str = lccpy(clang_str, '\n');
    //
    return clang_str;
}

// LVTP_BASE_DEFINE(LVTP_NAME, VERSION, INTEGRALITY, SERILENGTH)
// LVTP_BASE_DEFINE(txxt, 1, 0x00, 36)

#define SERIA_HEAD_LENG sizeof(binary_entit) + sizeof (osv_oid_t)

char *filli_lv2p_based(char *clang_str, class_meta *clsmt, lv2p_expa_t *lv2expt) {
    clang_str = lsprif(clang_str, "LVTP_BASE_DEFINE(%s, %llu", clsmt->lv2pn, clsmt->versio);
    if (clsmt->levo_list)
        clang_str = lscpy(clang_str, ", 0x01");
    else clang_str = lscpy(clang_str, ", 0x00");
    //  
    unsigned long long seri_leng = count_seri_leng(lv2expt->lv2nod);
    clang_str = lsprif(clang_str, ", %llu)\n", seri_leng ? SERIA_HEAD_LENG + seri_leng : 0x00);
    //
    return clang_str;
}

char *filli_const_decla(char *clang_str, parse_metho *metho) {
    // PRIN_parse_metho(metho); // for test
    clang_str = lscpy(clang_str, metho->oivk_retyp_pm);
    clang_str = lccpy(clang_str, ' ');
    clang_str = lscpy(clang_str, "Create");
    // clang_str = lscpy(clang_str, metho->lev1n);
    clang_str = lscpy(clang_str, metho->line_oivk);
    clang_str = lscpy(clang_str, "; \n");
    //
    return clang_str;
}

//

char *filli_metho_decla(char *clang_str, parse_metho *metho) {
    // PRIN_parse_metho(metho); // for test
    clang_str = lscpy(clang_str, metho->oivk_retyp_pm);
    clang_str = lccpy(clang_str, ' ');
    clang_str = lscpy(clang_str, metho->lev1n);
    clang_str = lscpy(clang_str, metho->line_oivk);
    clang_str = lscpy(clang_str, "; \n");
    //
    return clang_str;
}

//

char *filli_stati_const(char *clang_str, class_meta *clsmt, lv2p_prop *lv2nod) {
    // CLIT_PF("[FUNC]:filli_stati_const\n");
    clang_str = lsprif(clang_str, "const osv_oid_t %s::soLevTPOBID = {0x%x, 0x%x, 0x00};\n"
            , clsmt->lv2pn, clsmt->lv2p_obid.osev_unique, clsmt->lv2p_obid.time_stamp);
    clang_str = lsprif(clang_str, "const char *%s::spLevTPName = (char *)\"%s\";\n"
            , clsmt->lv2pn, clsmt->lv2pn);
    clang_str = lsprif(clang_str, "unsigned int %s::suChkAttribCount;\n", clsmt->lv2pn);
    char fmtsd[FMTST_COUNT_ZTAI];
    build_lv2p_fmtsd(fmtsd, lv2nod);
    clang_str = lsprif(clang_str, "const char *%s::spFomtStri = (char *)\"o%s\";\n"
            , clsmt->lv2pn, fmtsd);
    return clang_str;
}

//

char *filli_lcon_decla(char *clang_str, char *lv2pn, lv2p_prop *lv2nod) {
    clang_str = lscpy(clang_str, "public:  // construct \n");
    clang_str = lsprif(clang_str, "%s(); \n", lv2pn);
    //
    clang_str = lscpy(clang_str, lv2pn);
    clang_str = lccpy(clang_str, '(');
    int proper = 0x00;
    lv2p_prop *l2_nod = lv2nod;
    for (; ACCE_COTRL_INVAL != l2_nod->access; ++l2_nod) {
        if (proper) clang_str = lsprif(clang_str, ", %s %s", potyp_ostyp_tab[l2_nod->potyp], l2_nod->name);
        else {
            clang_str = lsprif(clang_str, "%s %s", potyp_ostyp_tab[l2_nod->potyp], l2_nod->name);
            proper = 0x01;
        }
    }
    clang_str = lscpy(clang_str, "); \n");
    //
    clang_str = lscpy(clang_str, lv2pn);
    clang_str = lscpy(clang_str, "(osv_oid_t obje_obid");
    l2_nod = lv2nod;
    for (; ACCE_COTRL_INVAL != l2_nod->access; ++l2_nod) {
        clang_str = lsprif(clang_str, ", %s %s", potyp_ostyp_tab[l2_nod->potyp], l2_nod->name);
    }
    clang_str = lscpy(clang_str, "); \n");
    //
    return clang_str;
}


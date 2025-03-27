
/* 
 * File:   filli_inline.h
 * Author: James Xu
 *
 * Created on 2023.10.11, PM 2:22
 */

#ifndef FILLI_INLINE_H
#define FILLI_INLINE_H

#ifdef __cplusplus
extern "C" {
#endif

    //

    static inline char *filli_rlv2pd_struct(char *clang_str, char *lv2pn, lv2p_prop *l2_nod) {
        char *clan_type;
        // OSEVPF("[FUNC]:filli_rlv2pd_struct\n");
        clang_str = lscpy(clang_str, "#pragma pack(1)\nstruct ");
        clang_str = lscpy(clang_str, lv2pn);
        clang_str = lscpy(clang_str, " {\n");
        clang_str = lscpy(clang_str, "osv_oid_i obje_obid;\n");
        for (; ACCE_COTRL_INVAL != l2_nod->access; ++l2_nod) {
            clan_type = potyp_clang_tab[l2_nod->potyp];
            clang_str = lscpy(clang_str, clan_type);
            clang_str = lccpy(clang_str, ' ');
            clang_str = lscpy(clang_str, l2_nod->name);
            if (l2_nod->size)
                clang_str = lsprif(clang_str, "[%u]", l2_nod->size);
            clang_str = lscpy(clang_str, ";\n");
        }
        clang_str = lscpy(clang_str, "};\n#pragma pack() \n");
        // OSEVPF("clang_str:|%s|\n", clang_str);
        return clang_str;
    }

    //

    static inline char *filli_rloivk_struct(char *clang_str, char *lv2pn, char *colu_types, colum *colu_data) {
        clang_str = lscpy(clang_str, "void _bind_");
        clang_str = lscpy(clang_str, lv2pn);
        clang_str = lscpy(clang_str, "_(struct ");
        clang_str = lscpy(clang_str, lv2pn);
        clang_str = lscpy(clang_str, " *obje_data, PK_ITEM *key, PK_ITEM *value) {\n");
        clang_str = lscpy(clang_str, "struct ");
        clang_str = lscpy(clang_str, lv2pn);
        clang_str = lscpy(clang_str, " dupobj;\n");
        clang_str = lscpy(clang_str, "memcpy(((char *) &dupobj) + OBJE_IDENTI_BLEN, ((char *) obje_data) + OBJE_IDENTI_BLEN, sizeof (struct ");
        clang_str = lscpy(clang_str, lv2pn);
        clang_str = lscpy(clang_str, ") -OBJE_IDENTI_BLEN);\n");
        clang_str = lscpy(clang_str, "key->size = sizeof (unsigned long long);\n");
        clang_str = lscpy(clang_str, "key->data = &(obje_data->obje_obid.stoid);\n");
        clang_str = lscpy(clang_str, "value->size = sizeof(struct ");
        clang_str = lscpy(clang_str, lv2pn);
        clang_str = lscpy(clang_str, ") - OBJE_IDENTI_BLEN;\n");
        clang_str = lscpy(clang_str, "value->data = ((char *) obje_data) + OBJE_IDENTI_BLEN;\n");
        clang_str = lscpy(clang_str, "paki_item_pack(value, \"");
        clang_str = lscpy(clang_str, colu_types);
        clang_str = lscpy(clang_str, "\"");
        //
        for (; COLU_END != colu_data->type; ++colu_data) {
            clang_str = lscpy(clang_str, ", dupobj.");
            clang_str = lscpy(clang_str, colu_data->name);
        }
        //
        clang_str = lscpy(clang_str, ");\n");
        clang_str = lscpy(clang_str, "}\n");
        //
        return clang_str;
    }

    //

#define FILLI_VNAME(VNAME, TOKE, INDE) lsprif(VNAME, "%s%d", TOKE, INDE);

    static inline char *filli_rloivk_function(char *clang_str, char *lv2pn, char *colu_types, colum *colu_data) {
        clang_str = lscpy(clang_str, "void _solve_");
        clang_str = lscpy(clang_str, lv2pn);
        clang_str = lccpy(clang_str, '_');
        clang_str = lscpy(clang_str, "(struct ");
        clang_str = lscpy(clang_str, lv2pn);
        clang_str = lscpy(clang_str, " *obje_data, unsigned long long *key, PK_ITEM *value) {\n");
        //
        char vname[PARAM_LENGTH];
        colum *cdata = colu_data;
        unsigned int inde = 0x00, sexi = 0x00;
        for (; COLU_END != cdata->type; ++inde, ++cdata) {
            if ((COLU_BYTE | COLU_CHAR) & cdata->type) {
                if (sexi) {
                    clang_str = lscpy(clang_str, ", ");
                    FILLI_VNAME(vname, "*dat", inde)
                    clang_str = lscpy(clang_str, vname);
                } else {
                    clang_str = lscpy(clang_str, "char ");
                    FILLI_VNAME(vname, "*dat", inde)
                    clang_str = lscpy(clang_str, vname);
                    sexi++;
                }
            }
        }
        if (sexi) clang_str = lscpy(clang_str, ";\n");
        //
        clang_str = lscpy(clang_str, "PACKING_KEY_UNPACK(obje_data->obje_obid.stoid, key);\n");
        clang_str = lscpy(clang_str, "paki_struct_unpack((void *) value->data, sizeof(struct ");
        clang_str = lscpy(clang_str, lv2pn);
        clang_str = lscpy(clang_str, ") - OBJE_IDENTI_BLEN, \"");
        clang_str = lscpy(clang_str, colu_types);
        clang_str = lscpy(clang_str, "\"");
        cdata = colu_data;
        inde = 0x00;
        for (; COLU_END != cdata->type; ++inde, ++cdata) {
            if ((COLU_NUMB | COLU_STRI) & cdata->type) {
                clang_str = lscpy(clang_str, ", &obje_data->");
                clang_str = lscpy(clang_str, cdata->name);
            } else if ((COLU_BYTE | COLU_CHAR) & cdata->type) {
                FILLI_VNAME(vname, ", &dat", inde)
                clang_str = lscpy(clang_str, vname);
            }
        }
        clang_str = lscpy(clang_str, ");\n");
        //
        cdata = colu_data;
        inde = 0x00;
        for (; COLU_END != cdata->type; ++inde, ++cdata) {
            if ((COLU_BYTE | COLU_CHAR) & cdata->type) {
                clang_str = lscpy(clang_str, "memcpy(");
                clang_str = lscpy(clang_str, "obje_data->");
                clang_str = lscpy(clang_str, cdata->name);
                FILLI_VNAME(vname, ", dat", inde)
                clang_str = lscpy(clang_str, vname);
                clang_str = lsprif(clang_str, ", %s);\n", cdata->size);
            } /* else if (COLU_STRI & cdata->type) {
            clang_str = lscpy(clang_str, "strcpy(");
            clang_str = lscpy(clang_str, "obje_data->");
            clang_str = lscpy(clang_str, cdata->name);
            FILLI_VNAME(vname, ", dat", inde)
            clang_str = lscpy(clang_str, vname);
            clang_str = lscpy(clang_str, ");\n");
        } */
        }
        //
        clang_str = lscpy(clang_str, "}\n");
        return clang_str;
    }

    //
#define INCL_SYSTEM_HEAD "#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n#include <stdint.h>\n"
#define INCL_OSVOBID_HEAD "#include <osev_obid.h>\n"
#define INCL_STRZUTI_HEAD "#include <strz_utili.h>\n"
#define INCL_OREVAL_HEAD "#include <osev_reval.h>\n"

    static inline char *filli_include_head(char *clang_str) {
        clang_str = lscpy(clang_str, INCL_SYSTEM_HEAD);
        // clang_str = lscpy(clang_str, INCL_PACKING_HEAD);
        clang_str = lscpy(clang_str, INCL_OSVOBID_HEAD);
        clang_str = lscpy(clang_str, INCL_STRZUTI_HEAD);
        clang_str = lscpy(clang_str, INCL_OREVAL_HEAD);
        return clang_str;
    }

    //

    inline void filli_normal_pmoik(char *line_oivk, char *lv2pn, char *lev1n, char *fmtsop) {
        line_oivk = lscpy(line_oivk, "(oreval *rvalu, struct ");
        line_oivk = lscpy(line_oivk, lv2pn);
        line_oivk = lscpy(line_oivk, " *this, struct ");
        line_oivk = lccpy(line_oivk, '_');
        line_oivk = lscpy(line_oivk, lv2pn);
        line_oivk = lccpy(line_oivk, '_');
        line_oivk = lscpy(line_oivk, lev1n);
        line_oivk = lccpy(line_oivk, '_');
        line_oivk = lscpy(line_oivk, fmtsop);
        line_oivk = lscpy(line_oivk, "_ *pamvp");
        //
        line_oivk = lscpy(line_oivk, ")");
    }

    inline void filli_constr_pmoik(char *line_oivk, char *lv2pn, char *lev1n, char *fmtsop) {
        line_oivk = lscpy(line_oivk, "(struct ");
        line_oivk = lscpy(line_oivk, lv2pn);
        line_oivk = lscpy(line_oivk, " *this, struct ");
        line_oivk = lccpy(line_oivk, '_');
        line_oivk = lscpy(line_oivk, lv2pn);
        line_oivk = lccpy(line_oivk, '_');
        line_oivk = lscpy(line_oivk, lev1n);
        line_oivk = lccpy(line_oivk, '_');
        line_oivk = lscpy(line_oivk, fmtsop);
        line_oivk = lscpy(line_oivk, "_ *pamvp");
        //
        line_oivk = lscpy(line_oivk, ")");
    }

#ifdef __cplusplus
}
#endif

#endif /* FILLI_INLINE_H */


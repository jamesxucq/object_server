
/* 
 * File:   filli_inline.h
 * Author: James Xu
 *
 * Created on 2023.10.11, PM 2:17
 */

#ifndef FILLI_INLINE_H
#define FILLI_INLINE_H

#ifdef __cplusplus
extern "C" {
#endif

    static inline int produ_resul_conte(clit_resu *resul, char *resu_cont) {
        int colen = strlen(resu_cont);
        if (RESP_DATA_SIZE < colen) {
            rewind(resul->resu_stram);
            if (colen != fwrite(resu_cont, 0x01, colen, resul->resu_stram))
                return -1;
            resul->resu_type = 0x01;
        } else {
            memcpy(resul->resu_data, resu_cont, colen);
            resul->resu_type = 0x00;
        }
        resul->resu_leng = colen;
        //
        return 0x00;
    }

    //

    static inline char *filli_lv2p_head(char *clang_str, char *lv2pn, char *basen) {
        char head_macro[MID_TLENG];
        char *last_str = lscpy(head_macro, lv2pn);
        lscpy(last_str, "_H");
        strupr(head_macro);
        //
        last_str = lsprif(clang_str, "#ifndef %s\n#define %s \n\n", head_macro, head_macro);
        last_str = lscpy(last_str, "#include <packing.h> \n");
        last_str = lscpy(last_str, "#include <osev_datyp.h> \n");
        last_str = lscpy(last_str, "#include <LVTPDefine.h> \n\n");
        last_str = lsprif(last_str, "namespace %s::lev2p { \n", basen);
        //
        return last_str;
    }

    static inline char *filli_lv2p_tail(char *clang_str, char *lv2pn) {
        char head_macro[MID_TLENG];
        char *last_str = lscpy(head_macro, lv2pn);
        lscpy(last_str, "_H");
        strupr(head_macro);
        //
        last_str = lsprif(clang_str, "} \n\n");
        last_str = lsprif(last_str, "#endif /* %s */ \n\n", head_macro);
        //
        return last_str;
    }

    //

    static inline char *filli_lev1_head(char *clang_str, char *lv2pn, char *basen) {
        char head_cont[MID_TLENG];
        char *last_str = lscpy(head_cont, lv2pn);
        lscpy(last_str, ".h");
        //
        last_str = lscpy(clang_str, "#include <stdlib.h> \n");
        last_str = lscpy(last_str, "#include <stdio.h> \n");
        last_str = lscpy(last_str, "#include <string.h> \n");
        last_str = lscpy(last_str, "#include <osev_obid.h> \n");
        //
        last_str = lsprif(last_str, "#include \"%s\" \n\n", head_cont);
        last_str = lsprif(last_str, "using namespace %s::lev2p; \n\n", basen);
        //
        return last_str;
    }

    //
#define APPEN_OBJE_ID "creat_objec_obid(&this->obje_obid);"

    static inline char *appe_obje_id(char *clang_str, char *lev1_body) {
        char *last_body = strchr(lev1_body, '{');
        if (!last_body) return clang_str;
        clang_str = lsncpy(clang_str, lev1_body, (++last_body) - lev1_body);
        //
        clang_str = lscpy(clang_str, APPEN_OBJE_ID);
        clang_str = lscpy(clang_str, last_body);
        //
        return clang_str;
    }

    // l2_nod->name
    // trans-serve

    inline void build_lv2p_fmtsd(char *fmtsd, lv2p_prop *lv2nod) {
        char fmtch;
        if (ACCE_COTRL_INVAL != lv2nod->access) {
            for (; ACCE_COTRL_INVAL != lv2nod->access; ++lv2nod) {
                fmtch = potyp_fmtst_tab[lv2nod->potyp];
                if ('s' == fmtch)
                    fmtsd = lsprif(fmtsd, "%u", lv2nod->size);
                fmtsd = lccpy(fmtsd, fmtch);
            }
        }
    }
#ifdef __cplusplus
}
#endif

#endif /* FILLI_INLINE_H */


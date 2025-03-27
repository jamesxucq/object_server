
/* 
 * File:   const_utili.h
 * Author: James Xu
 *
 * Created on 20220312, PM1:44
 */

#ifndef CONST_UTILI_H
#define CONST_UTILI_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    int chk_lev1_type(lv2p_prop *lv2nod, char **pamvp);

    //
    int const_lv2p_prop(loop_memo_t *obje_memp, char **pamvp, lv2pme *lv2me);

    // create
    int solve_lv2p_prop(PK_ITEM *key, PK_ITEM *value, valu_memo_t *obje_memp, char **pamvp, lv2pme *lv2me);

    // update
    int solve_obje_data(PK_ITEM *key, PK_ITEM *value, slov_memo_t *obje_memp, char **obje_datp, lv2pme *lv2me);
    // insert
    int solve_obje_valu(PK_ITEM *value, slov_memo_t *obje_memp, char **obje_datp, lv2pme *lv2me);

    //

    inline uint64 count_pack_size(char **pamvp, lv2pme *lv2me) {
        // OSEVPF("[FUNC]:count_pack_size\n");
        uint64 pack_size = lv2me->data_size;
        char *fmtst = lv2me->lv2p_fmtsd_tm;
        char *endsize;
        for (; fmtst[0x00] && (NULL != pamvp[0x00]); ++fmtst, ++pamvp) {
            if (isdigit(fmtst[0x00])) {
                strtoul(fmtst, &endsize, 10);
                fmtst = endsize;
            }
            if ('S' == fmtst[0x00]) {
                if (DATY_STRZ != ((unsigned char*) pamvp[0x00])[0x00])
                    return 0x00;
                pack_size += ((strz_entit *) pamvp[0x00])->colen;
            }
        }
        return pack_size;
    }

    //

    inline int osev_unique_equal(unsigned int osev_unique, char *obje_enti) {
        // OSEVPF("[FUNC]:osev_unique_equal\n");
        if (DATY_OBID != obje_enti[0x00])
            return -1;
        if (osev_unique != ((osv_oid_i *) &((obid_entit *) obje_enti)->data)->osev_unique)

            return -1;
        return 0x00;
    }

    // OSEVPF("obje_enti[0x00]:|%d|\n", obje_enti[0x00]);
    // char obid_stri[OBJE_IDENTI_ZLEN];
    // OSEVPF("PSCON->data:|%s|\n", oidstr(obid_stri, (osv_oid_t *) &((obid_entit *) obje_enti)->data));

    inline int is_potyp_obid(char *obje_enti) {
        // OSEVPF("[FUNC]:is_potyp_obid\n");
        if (DATY_OBID != obje_enti[0x00])
            return -1;
        return 0x00;
    }

#ifdef __cplusplus
}
#endif

#endif /* CONST_UTILI_H */


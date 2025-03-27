#include "commo_header.h"
#include "kcomm_header.h"
#include "ostri_utili.h"

#include "lv2p_meta/lv2me_ite.h"
#include "cvalid_utili.h"
#include "ivalid_utili.h"
//

int valid_iextem_ite(char *basen, char *lv2pn, char *lev1n) {
    OSEVPF("[FUNC]:valid_iextem_ite\n");
    lv2ex_conte l2ie_cont;
    initi_lv2ex_conte(&l2ie_cont);
    //
    lv2iex *l2e_nod = appe_lv2ie_init(&l2ie_cont, lv2pn);
    if (!l2e_nod) {
        final_lv2ex_conte(&l2ie_cont);
        return -1;
    }
    if (build_extern_inhlst_ite(&l2e_nod->iexter, &l2e_nod->inher_list, basen, lv2pn)) {
        final_lv2ex_conte(&l2ie_cont);
        return -1;
    }
    //
    while (l2e_nod) {
        if (l2e_nod->iexter) {
            final_lv2ex_conte(&l2ie_cont);
            OSEVPF("EXCEPTION, valid_iextem_ite\n");
            return 0x01;
        }
        //
        inherit *ilist = l2e_nod->inher_list;
        for (; ilist; ilist = ilist->next) {
            if ((((INHE_TYPE_METH | INHE_TYPE_LEVO) & ilist->rang_type) && strcmp(lev1n, ilist->lev1n))
                    || (INHE_TYPE_LVTP & ilist->rang_type))
                continue;
            //
            lv2iex *l2ie = appe_lv2ie_new(&l2ie_cont, ilist->lv2pn);
            if (!l2ie) {
                final_lv2ex_conte(&l2ie_cont);
                return -1;
            }
            if (build_extern_inhlst_ite(&l2ie->iexter, &l2ie->inher_list, basen, ilist->lv2pn)) {
                final_lv2ex_conte(&l2ie_cont);
                return -1;
            }
        }
        //
        l2e_nod = get_l2ie_node(&l2ie_cont);
    }
    final_lv2ex_conte(&l2ie_cont);
    //
    OSEVPF("PASSED, valid_iextem_ite\n");
    return 0x00;
}




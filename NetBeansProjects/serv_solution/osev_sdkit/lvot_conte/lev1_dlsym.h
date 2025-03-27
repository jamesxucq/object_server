
/* 
 * File:   lev1_dlsym.h
 * Author: James Xu
 *
 * Created on 2017.1.9, PM 5:12
 */

#ifndef LEVO_DLSYM_H
#define LEVO_DLSYM_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    int open_meth_hand(lev1me *lv1me, hand_hmap *hando_stm, char *libr_path);
    int open_meth_hand_librn(lev1me *lv1me, hand_hmap *hando_stm, char *libr_path, char *lev1_librn);

    // 0x00:hand refer zero. >0x00:refer number

    inline int close_meth_hand(char *lev1_librn, hand_hmap *hando_stm, lev1me *lv1me) {
        if (!close_dyhand(lev1_librn, &hando_stm->dyha_list, lv1me->libr_hand))
            return 0x00;
        return 0x01;
    }
    //

#ifdef __cplusplus
}
#endif

#endif /* LEVO_DLSYM_H */


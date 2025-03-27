/* 
 * File:   invok_obje.h
 * Author: James Xu
 *
 * Created on 2016.12.17, PM 2:33
 */

#ifndef INVOK_OBJE_H
#define INVOK_OBJE_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    int list_clas(char **clas_arrp, char *_cline_, char *data_path);

    //

    inline int clear_insta(inst_hmap *insda_stm) {
        CLEAR_INSTA_CACHE(insda_stm);
        return 0x00;
    }

    //

    int updat_lv2p_extern(lv2pm_hmap *lv2pm_stm, char *basen, char *lv2pn, uint32 value);

#ifdef __cplusplus
}
#endif

#endif /* INVOK_OBJE_H */


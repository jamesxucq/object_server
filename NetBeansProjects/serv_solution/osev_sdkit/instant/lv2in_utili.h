
/* 
 * File:   lv2in_utili.h
 * Author: James Xu
 *
 * Created on 2024.4.1, PM 4:10
 */

#ifndef LVTIN_UTILI_H
#define LVTIN_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    instda *creat_insta_data(inst_hmap *insda_stm, char *lv2_dec);
    int destr_insta_data(inst_hmap *insda_stm, char *lv2_dec);


#ifdef __cplusplus
}
#endif

#endif /* LVTIN_UTILI_H */


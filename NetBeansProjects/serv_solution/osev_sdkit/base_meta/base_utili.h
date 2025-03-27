
/* 
 * File:   base_utili.h
 * Author: James Xu
 *
 * Created on 2023.4.20, PM 4:34
 */

#ifndef BASE_UTILI_H
#define BASE_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    int creat_base_conte(char *basen);
    int drop_base_conte(char *basen);

    // 0x00:empty 0x01:not empty
    int valid_base_clean(char *basen);

#ifdef __cplusplus
}
#endif

#endif /* BASE_UTILI_H */


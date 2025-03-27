
/* 
 * File:   refer_utili.h
 * Author: James Xu
 *
 * Created on 2022.11.10, PM 2:08
 */

#ifndef REFER_UTILI_H
#define REFER_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    void init_dynami_robj(void *obje_memp, int refe_coun);

    //
    extern int (*dynami_unpack_tab[])(void *, PK_ITEM *, PK_ITEM *);

    //
//#pragma pack(1)
//
//    struct _refe_enti_ {
//        osv_sid_i renti;
//        unsigned char rinde;
//    };
//#pragma pack()
//
//    typedef struct _refe_enti_ refe_enti;

    //
    void init_static_robj(void *obje_memp, int refe_coun);

    //
    extern int (*static_unpack_tab[])(void *, PK_ITEM *, PK_ITEM *);


#ifdef __cplusplus
}
#endif

#endif /* REFER_UTILI_H */


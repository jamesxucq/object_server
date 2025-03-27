
/* 
 * File:   refer_struct.h
 * Author: James Xu
 *
 * Created on 2024.6.3, AM 9:05
 */

#ifndef REFER_STRUCT_H
#define REFER_STRUCT_H

#ifdef __cplusplus
extern "C" {
#endif

    // static
#pragma pack(1)

    struct _rsent_sing_ {
        osv_sid_i senti;
        unsigned char sinde;
    };
#pragma pack()

    typedef struct _rsent_sing_ rsent_sing;

    //

#pragma pack(1)

    struct _rsent_coup_ {
        osv_sid_i senti1;
        unsigned char sinde1;
        osv_sid_i senti2;
        unsigned char sinde2;
    };
#pragma pack()

    typedef struct _rsent_coup_ rsent_coup;

    // dynamic

    typedef osv_sid_i rdent_sing;

    //

#pragma pack(1)

    struct _rdent_coup_ {
        osv_sid_i senti1;
        osv_sid_i senti2;
    };
#pragma pack()

    typedef struct _rdent_coup_ _rdent_coup_;

    //

#ifdef __cplusplus
}
#endif

#endif /* REFER_STRUCT_H */


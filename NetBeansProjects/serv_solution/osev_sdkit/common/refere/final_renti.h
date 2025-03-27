
/* 
 * File:   final_renti.h
 * Author: James Xu
 *
 * Created on 2024.6.19, PM 1:59
 */

#ifndef FINAL_RENTI_H
#define FINAL_RENTI_H

#ifdef __cplusplus
extern "C" {
#endif

    //
#pragma pack(1)

    struct _fien_resi_ {
        osv_sid_i renti;
        osv_sid_i senti;
        unsigned char sinde;
    };
#pragma pack()

    typedef struct _fien_resi_ fien_resi;

    //

#pragma pack(1)

    struct _fien_reco_ {
        osv_sid_i renti;
        osv_sid_i senti1;
        unsigned char sinde1;
        osv_sid_i senti2;
        unsigned char sinde2;
    };
#pragma pack()

    typedef struct _fien_reco_ fien_reco;


#ifdef __cplusplus
}
#endif

#endif /* FINAL_RENTI_H */



/* 
 * File:   osev_reval.h
 * Author: James Xu
 *
 * Created on 2023.11.21, PM 2:21
 */

#ifndef OSEV_REVAL_H
#define OSEV_REVAL_H

#ifdef __cplusplus
extern "C" {
#endif

    //

    union _oretyp_ {
        char rchar;
        unsigned char rucha;
        short rshor;
        unsigned short rusho;
        int rint;
        unsigned int ruint;
        long rlong;
        unsigned long rulong;
        long long rllong;
        unsigned long long rullon;
        float rfloa;
        double rdoub;
        char* rchap;
        char* rstrz;
    };

#pragma pack(1)

    struct _oreval_ {
        osv_oid_i obje_obid;
        union _oretyp_ retype;
    };
#pragma pack()

    typedef struct _oreval_ oreval;

    //

#ifdef __cplusplus
}
#endif

#endif /* OSEV_REVAL_H */


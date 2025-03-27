
/* 
 * File:   kcomm_struct.h
 * Author: James Xu
 *
 * Created on 2022.12.21, AM 9:50
 */

#ifndef KCOMM_STRUCT_H
#define KCOMM_STRUCT_H

#ifdef __cplusplus
extern "C" {
#endif

    //
#define FIELD_FROM_EXCEP        0x00
#define FIELD_FROM_ONE          0x01
#define FIELD_FROM_TWO          0x02
#define FIELD_FROM_THREE        0x04
#define FIELD_FROM_FOUR         0x08

    //

    struct _field_resul_co_ {
        char field_str1[LVTNOD_LENGTH];
        char rfmtst1[FMTST_COUNT_ZTAI];
        char field_str2[LVTNOD_LENGTH];
        char rfmtst2[FMTST_COUNT_ZTAI];
        unsigned char rescod [FMTST_COUNT_ZTAI];
        char fmtstd_co[FMTST_COUNT_ZTAI];
        unsigned char fixed_float_co; // 0x00:fixed 0x01:float
        uint64 data_size;
    };

    typedef struct _field_resul_co_ field_resul_co;

    //
#define CREAT_FIELD_RESUL_ENCO() ((field_resul_co *) malloc(sizeof (field_resul_co)))
#define DELET_FIELD_RESUL_ENCO(FIRES) (free(FIRES))

    //

#ifdef __cplusplus
}
#endif

#endif /* KCOMM_STRUCT_H */


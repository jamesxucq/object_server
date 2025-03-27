
/* 
 * File:   osev_macro.h
 * Author: James Xu
 *
 * Created on 2018.3.29, AM 9:08
 */

#ifndef OSEV_MACRO_H
#define OSEV_MACRO_H

#ifdef __cplusplus
extern "C" {
#endif

    //
#ifndef BUFF_SOCKET_SIZE
#define BUFF_SOCKET_SIZE               0x2000  // 8K
#endif

    //
#define XML_LENGTH                    0x2000  // 8K
#define XML_LINE_LENGTH               1024  // 1K
#define ATTRIB_LENGTH                 512
#define ELEMEN_LENGTH                 0x1000  // 4K
    //
#define BUFF_16K_SIZE                 0x4000  // 16K
#define BUFF_32K_SIZE                 0x8000  // 32K
#define BUFF_64K_SIZE                 0x10000  // 64K
    //
#define RSBUF_SIZE                    0x80000  // 512K
#define LARGE_CONTE_SIZE              0x80000  // 512K // OBJE_CONTE_LEN
#define CLANG_CONTE_SIZE              0x8000  // 32K
#define OSLAN_CONTE_SIZE              CLANG_CONTE_SIZE  // 32K
#define LARGE_TEXT_SIZE               0x4000  // 16K
#define TEXT_LENGTH                   0x1000  // 4K
#define LINE_LENGTH                   1024
    //
#define MAX_TLENG    512
#define MID_TLENG    128
#define MIN_TLENG    64


#define TIME_LENGTH             32
#define PASWD_LENGTH            32
#define SALT_LENGTH             16
#define KEY_LENGTH              16
#define USRN_LENGTH             32
#define VALID_LENGTH            16 // MD5_DIGEST_LEN
#define PLAIN_VALID_LENGTH      USRN_LENGTH + PASWD_LENGTH + 0x01

#define _USERN_LENGTH_          128
#define GROUPN_LENGTH           128
#define SERVN_LENGTH            256
#define TIME_LENGTH             32

    //
#define LVON_LENGTH             128
#define PACKAGE_LEN             128

    //
#define OSEV_LENGTH             128
#define BASE_LENGTH             OSEV_LENGTH
#define MAX_BASE_COUNT          128
#define ACTION_KEY_LENGTH       USRN_LENGTH + BASE_LENGTH
#define OBJN_LENGTH             128
#define LEVE_LENGTH             128
#define LVON_LENGTH             128
#define LVOD_LENGTH             256
#define LEVO_COUNT              256 // max: 512
#define LVTN_LENGTH             128
#define LVTP_COUNT              0x1000 // 4K
#define LVTNOD_COUNT            512 // max: 1024
#define LVTNOD_LENGTH           1024
#define INHE_COUNT              32
#define PAMTYP_LENGTH           32
#define PARAM_COUNT             LVTNOD_COUNT
#define PARAM_COUNT_ZTAI        LVTNOD_COUNT + 0x01 // zero tail
#define FMTST_COUNT_ZTAI        LVTNOD_COUNT + 0x01 // zero tail
#define PARAM_LENGTH            128
#define PAMSTYL_LENGTH          1024
#define LVTD_LENGTH             128
#define CONDIT_LENGTH           256

    //
#define CONTA_LENGTH           128
#define TABLE_LENGTH           128
#define TYPES_LENGTH           1024
#define COLUMN_LENGTH          0x1000  // 4K
#define HANDN_LENGTH           256
#define LIBRN_LENGTH           256

    //
#define CONF_LENGTH            2048
#define SPACE_COUNT            32
#define OBJE_CONTE_LEN         0x80000  // 512K // LARGE_CONTE_SIZE
#define BINA_ARRAY_LEN         0x100000  // 1M

    //
#define URI_LENGTH              512
    // #define QURI_LENGTH            256

    //
#define MAX_SCONT_COUNT         0x04 // max source container is 4
#define CINHE_COUNT_ZTAI        (MAX_SCONT_COUNT + 0x01) // max source class is 4
#define SCONT_CONUT_ZTAI        (MAX_SCONT_COUNT + 0x01) // max source container is 4, last is null
#define DCONT_SCONT_COUNT       0x05 // (MAX_SCONT_COUNT + 0x01) // destination and source container is 5
#define DCONT_SCONT_ZTAI        (DCONT_SCONT_COUNT + 0x01) // destination and source container is 6, last is null
#define MAX_RSCON_COUNT         64 // max reference container is 64
#define RCONT_CONUT_ZTAI        (MAX_RSCON_COUNT + 0x01) // max source container is 4, last is null
#define MAX_RDCON_COUNT         MAX_SCONT_COUNT // max reference container is 4


#ifdef __cplusplus
}
#endif

#endif /* OSEV_MACRO_H */


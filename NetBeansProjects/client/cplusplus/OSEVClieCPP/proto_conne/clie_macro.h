
#ifndef CLIE_MACRO_H
#define CLIE_MACRO_H

// commo_macro.h
#define MK_ZERO(TEXT) TEXT[0x00] = '\0'

// clie_macro.h
#define OSEV_DEFAULT_PORT       8848
//
#define CONNE_DATA_SIZE         0x80000 // 512K
#define REQU_DATA_SIZE          0x80000 // 512K
#define RESP_DATA_SIZE          0x80000 // 512K

// osev_macro.h
#define SPACE_COUNT             32
//
#define LARGE_TEXT_SIZE         0x4000 // 16K
#define OBJE_CONTE_LEN          0x80000 // 512K
#define MID_TLENG               128
//
#define SERVN_LENGTH            256
// #define URI_LENGTH                      256
#define USRN_LENGTH             32
#define VALID_LENGTH            16 // MD5_DIGEST_LEN
#define SALT_LENGTH             16
#define OSEV_LENGTH             128
#define OBJN_LENGTH             128
#define PARAM_LENGTH            128
#define PASWD_LENGTH            32

#define LVON_LENGTH             128

//

#endif /* CLIE_MACRO_H */


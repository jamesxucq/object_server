
/* 
 * File:   kcomm_macro.h
 * Author: James Xu
 *
 * Created on 2023.6.14, AM 9:22
 */

#ifndef KCOMM_MACRO_H
#define KCOMM_MACRO_H

#ifdef __cplusplus
extern "C" {
#endif

    //
#define VARI_OBJE_SIZE                  0x40000  // 256K

    // -1:error 0x01:constructor 0x00:normal
#define METHO_CONST_TYPE    0x00
#define METHO_NORMA_TYPE    0x01

    //
#define CLASS_INIT_VERSION      0x01 // 0x00:disable >0x00:is version
#define CLASS_INIT_INTERNAL     FALSE_OSV // 0x00: internal 0x01: external

    //
#define OSEV_DEFAULT_VALUE      "osev"
#define BASE_DEFAULT_VALUE      "odb"
#define OSEV_ADMINIS_VALUE      "admin"

#define OSEV_CAPITAL_VALUE      "OSEV"
#define BASE_CAPITAL_VALUE      "ODB"    
    
#define CLANG_SUFFIX    ".c"
#define OBJEC_SUFFIX    ".o"
#define LIBRA_SUFFIX    ".so"
#define BAKUP_SUFFIX    ".bak"
#define DECLA_SUFFIX    ".dec"
#define ATTRI_SUFFIX    ".ati"
#define EXPAN_SUFFIX    ".exp"
#define CLASS_EXTEND_NAME   "dec"

    //
#define OSEV_CONTE_DATA     "osev_conte.dat"
#define BASE_CONTE_DATA     "base_conte.dat"
#define CONTA_CONTE_DATA    "cont_conte.dat"
#define LEVO_CONTE_DATA     "lev1_conte.dat"
#define LVTP_CONTE_DATA     "lv2p_conte.dat"

    // predicate
#define DYNAMIC_PREDICATE_DEFAULT '*'

#ifdef __cplusplus
}
#endif

#endif /* KCOMM_MACRO_H */


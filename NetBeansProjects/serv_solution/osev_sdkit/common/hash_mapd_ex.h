
/* 
 * File:   hash_mapd_ex.h
 * Author: James Xu
 *
 * Created on 2021.5.14, AM 9:31
 */

#ifndef HASH_MAPD_EX_H
#define HASH_MAPD_EX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "utility/oid_hmd.h"

    //
#define HASHMD_DEFAULT_TNUM 10000000
#define HASHMD_DEFAULT_BNUM 10000000
#define HASHMD_DEFAULT_CNUM 1000000

    //
#define new_oidhmd()  oidhmd_new(HASHMD_DEFAULT_TNUM, HASHMD_DEFAULT_BNUM, HASHMD_DEFAULT_CNUM, sax_hash_hmd, sdbm_hash_hmd)

    //    
    uint32_t sax_hash_hmd(char *key, int ksiz);
    uint32_t sdbm_hash_hmd(char *key, int ksiz);

    //
    OBIDHMD *creat_temp_ohmd();


#ifdef __cplusplus
}
#endif

#endif /* HASH_MAPD_EX_H */


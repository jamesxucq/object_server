
/* 
 * File:   hashdb_ex.h
 * Author: James Xu
 *
 * Created on 2021331, PM 2:09
 */

#ifndef HASHDB_EX_H
#define HASHDB_EX_H

#ifdef __cplusplus
extern "C" {
#endif

    //
#include "utility/hashdb.h"
#include "utility/tex_hdb.h"
#include "utility/oid_hdb.h"

    //
#define HASHDB_DEFAULT_TNUM 10000000
#define HASHDB_DEFAULT_BNUM 10000000
#define HASHDB_DEFAULT_CNUM 1000000

    //
#define new_hashdb()  hashdb_new(HASHDB_DEFAULT_TNUM, HASHDB_DEFAULT_BNUM, HASHDB_DEFAULT_CNUM, sax_hash, sdbm_hash)
#define new_texhdb()  texhdb_new(HASHDB_DEFAULT_TNUM, HASHDB_DEFAULT_BNUM, HASHDB_DEFAULT_CNUM, sax_hash, sdbm_hash)
#define new_oidhdb()  oidhdb_new(HASHDB_DEFAULT_TNUM, HASHDB_DEFAULT_BNUM, HASHDB_DEFAULT_CNUM, sax_hash, sdbm_hash)

    //    
    uint32_t sax_hash(char *key, int ksiz);
    uint32_t sdbm_hash(char *key, int ksiz);

    //
    HASHDB *creat_temp_hadb();
    TEXHDB *creat_temp_thdb();
    OBIDHDB *creat_temp_ohdb();

#ifdef __cplusplus
}
#endif

#endif /* HASHDB_EX_H */


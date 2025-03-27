
/* 
 * File:   oid_hmd.h
 * Author: James Xu
 *
 * Created on 2021.5.12, PM4:46
 */

#ifndef OID_HMD_H
#define OID_HMD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
// #include "jemalloc/jemalloc.h"
#include "bloom.h"
//
#define OHMD_NAME_LENGTH 260

//
#define OHMD_KEY_SZ 12

//

typedef struct {
    uint8_t cached; /* cached or not */
    char key[OHMD_KEY_SZ]; /* key */
    // char valu[OHMD_VALUE_SZ]; // disable by james 20210514
    uint32_t hash; /* second hash value */
    uint64_t off; /* offset of the entity */
    uint64_t left; /* offset of the left child */
    uint64_t right; /* offset of the right child */
} OHMD_ENTIT;
#define OHMD_ENTIT_SZ sizeof(OHMD_ENTIT)

//

typedef struct {
    uint64_t off; /* offset of the first entity in the bucket */
} OHMD_BUCKET;
#define OHMD_BUCKET_SZ sizeof(OHMD_BUCKET)

//
#define OHMD_MAGIC 19911011

typedef struct {
    uint32_t magi; /* magic number */
    uint32_t cnum; /* number of cache items */
    uint32_t bnum; /* number of hash buckets */
    uint64_t tnum; /* number of total items */
    uint64_t boff; /* offset of bloom filter */
    uint64_t hoff; /* offset of hash buckets */
    uint64_t eoff; /* offset of end */
} OHMD_HDR;
#define OHMD_HDR_SZ sizeof(OHMD_HDR)

//
typedef uint32_t(*ohmdfunc_t)(char *, int);

typedef struct {
    char dbname[OHMD_NAME_LENGTH]; /* hashmd filename */
    int fd; /* hashmd fd */
    OHMD_HDR header; /* hashmd header */
    BLOOM *bloom; /* bloom filter */
    OHMD_BUCKET *bucket; /* hash buckets */
    OHMD_ENTIT *cache; /* hash item cache */
    ohmdfunc_t ohmd_func1; /* hash function for hash bucket */
    ohmdfunc_t ohmd_func2; /* hash function for btree in the hash bucket */
} OBIDHMD;

//
OBIDHMD *oidhmd_new(uint64_t tnum, uint32_t bnum, uint32_t cnum, ohmdfunc_t ohmd_func1, ohmdfunc_t ohmd_func2); // ok
int oidhmd_open(OBIDHMD *hmd, const char *path); // ok
int oidhmd_close(OBIDHMD *hmd, int flash); // ok
int oidhmd_insert(OBIDHMD *hmd, char *key);
int oidhmd_find(OBIDHMD *hmd, char *key);
int oidhmd_unlink(OBIDHMD *hmd); // ok
#define oidhmd_dele(HMD)     free(HMD) // ok


#ifdef __cplusplus
}
#endif

#endif /* OID_HMD_H */


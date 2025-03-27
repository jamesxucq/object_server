
#ifndef _OID_HDB_H
#define _OID_HDB_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "bloom.h"
//
#define OBIDHDB_NAME_LENGTH 260

//
#define OBIDHDB_KEY_SZ 12
#define OBIDHDB_VALUE_SZ 8

//

typedef struct {
    uint8_t cached; /* cached or not */
    char key[OBIDHDB_KEY_SZ]; /* key of <key, value> */
    char valu[OBIDHDB_VALUE_SZ]; /* value of <key, value> */
    uint32_t hash; /* second hash value */
    uint64_t off; /* offset of the entity */
    uint64_t left; /* offset of the left child */
    uint64_t right; /* offset of the right child */
} OBIDH_ENTIT;
#define OBIDH_ENTIT_SZ sizeof(OBIDH_ENTIT)

//

typedef struct {
    uint64_t off; /* offset of the first entity in the bucket */
} OBIDH_BUCKET;
#define OBIDH_BUCKET_SZ sizeof(OBIDH_BUCKET)

//
#define OBIDHDB_MAGIC 19811011

typedef struct {
    uint32_t magi; /* magic number */
    uint32_t cnum; /* number of cache items */
    uint32_t bnum; /* number of hash buckets */
    uint64_t tnum; /* number of total items */
    uint64_t boff; /* offset of bloom filter */
    uint64_t hoff; /* offset of hash buckets */
    uint64_t voff; /* offset of hash values */
} OBIDHDB_HDR;
#define OBIDHDB_HDR_SZ sizeof(OBIDHDB_HDR)

//
typedef uint32_t(*oidhfunc_t)(char *, int);

typedef struct {
    char dbname[OBIDHDB_NAME_LENGTH]; /* hashdb filename */
    int fd; /* hashdb fd */
    OBIDHDB_HDR header; /* hashdb header */
    BLOOM *bloom; /* bloom filter */
    OBIDH_BUCKET *bucket; /* hash buckets */
    OBIDH_ENTIT *cache; /* hash item cache */
    oidhfunc_t oidh_func1; /* hash function for hash bucket */
    oidhfunc_t oidh_func2; /* hash function for btree in the hash bucket */
} OBIDHDB;

//
OBIDHDB *oidhdb_new(uint64_t tnum, uint32_t bnum, uint32_t cnum, oidhfunc_t oidh_func1, oidhfunc_t oidh_func2);
int oidhdb_open(OBIDHDB *hdb, const char *path);
int oidhdb_close(OBIDHDB *hdb, int flash);
int oidhdb_set(OBIDHDB *hdb, char *key, void *valu);
int oidhdb_get(OBIDHDB *hdb, char *key, void *valu);
int oidhdb_unlink(OBIDHDB *hdb);
#define oidhdb_dele(HDB)     free(HDB)

#ifdef __cplusplus
}
#endif

#endif

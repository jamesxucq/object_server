
#ifndef _TEX_HDB_H
#define _TEX_HDB_H

#ifdef __cplusplus
extern "C" {
#endif

    //
#include <stdint.h>
#include "bloom.h"

//
#define TEXHDB_NAME_LENGTH 260

//
#define TEXHDB_KEY_MAX_SZ 512
#define TEXHDB_VALUE_MAX_SZ 8

//

typedef struct {
    uint8_t cached; /* cached or not */
    char *key; /* key of <key, value> */
    uint32_t ksiz; /* size of the key */
    void *valu; /* value of <key, value> */
    uint32_t vsiz; /* size of the value */
    uint32_t hash; /* second hash value */
    uint64_t off; /* offset of the entity */
    uint64_t left; /* offset of the left child */
    uint64_t right; /* offset of the right child */
} TEXH_ENTIT;
#define TEXH_ENTIT_SZ sizeof(TEXH_ENTIT)

//

typedef struct {
    uint64_t off; /* offset of the first entity in the bucket */
} TEXH_BUCKET;
#define TEXH_BUCKET_SZ sizeof(TEXH_BUCKET)

//
#define TEXHDB_MAGIC 19810904

typedef struct {
    uint32_t magi; /* magic number */
    uint32_t cnum; /* number of cache items */
    uint32_t bnum; /* number of hash buckets */
    uint64_t tnum; /* number of total items */
    uint64_t boff; /* offset of bloom filter */
    uint64_t hoff; /* offset of hash buckets */
    uint64_t voff; /* offset of hash values */
} TEXHDB_HDR;
#define TEXHDB_HDR_SZ sizeof(TEXHDB_HDR)

//
typedef uint32_t(*texhfunc_t)(char *, int);

typedef struct {
    char dbname[TEXHDB_NAME_LENGTH]; /* hashdb filename */
    int fd; /* hashdb fd */
    TEXHDB_HDR header; /* hashdb header */
    BLOOM *bloom; /* bloom filter */
    TEXH_BUCKET *bucket; /* hash buckets */
    TEXH_ENTIT *cache; /* hash item cache */
    texhfunc_t texh_func1; /* hash function for hash bucket */
    texhfunc_t texh_func2; /* hash function for btree in the hash bucket */
} TEXHDB;

//
TEXHDB *texhdb_new(uint64_t tnum, uint32_t bnum, uint32_t cnum, texhfunc_t texh_func1, texhfunc_t texh_func2);
int texhdb_open(TEXHDB *hdb, const char *path);
int texhdb_close(TEXHDB *hdb, int flash);
int texhdb_set(TEXHDB *hdb, char *key, int ksiz, void *valu, int vsiz);
int texhdb_get(TEXHDB *hdb, char *key, int ksiz, void *valu, int *vsiz);
int texhdb_unlink(TEXHDB *hdb);
#define texhdb_dele(TDB)     free(TDB)

#ifdef __cplusplus
}
#endif

#endif

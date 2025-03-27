
#ifndef _HASHDB_H
#define _HASHDB_H

#ifdef __cplusplus
extern "C" {
#endif

//
#include <stdint.h>
#include "bloom.h"
//
#define HASHDB_NAME_LENGTH 260

//
#define HASHDB_KEY_MAX_SZ 8
#define HASHDB_VALUE_MAX_SZ 8

//

typedef struct {
    uint8_t cached; /* cached or not */
    char key[HASHDB_KEY_MAX_SZ]; /* key of <key, value> */
    uint32_t ksiz; /* size of the key */
    char valu[HASHDB_VALUE_MAX_SZ]; /* value of <key, value> */
    uint32_t vsiz; /* size of the value */
    uint32_t hash; /* second hash value */
    uint64_t off; /* offset of the entity */
    uint64_t left; /* offset of the left child */
    uint64_t right; /* offset of the right child */
} HASH_ENTIT;
#define HASH_ENTIT_SZ sizeof(HASH_ENTIT)

//

typedef struct {
    uint64_t off; /* offset of the first entity in the bucket */
} HASH_BUCKET;
#define HASH_BUCKET_SZ sizeof(HASH_BUCKET)

//
#define HASHDB_MAGIC 19811001

typedef struct {
    uint32_t magi; /* magic number */
    uint32_t cnum; /* number of cache items */
    uint32_t bnum; /* number of hash buckets */
    uint64_t tnum; /* number of total items */
    uint64_t boff; /* offset of bloom filter */
    uint64_t hoff; /* offset of hash buckets */
    uint64_t voff; /* offset of hash values */
} HASHDB_HDR;
#define HASHDB_HDR_SZ sizeof(HASHDB_HDR)

//
typedef uint32_t(*hashfunc_t)(char *, int);

typedef struct {
    char dbname[HASHDB_NAME_LENGTH]; /* hashdb filename */
    int fd; /* hashdb fd */
    HASHDB_HDR header; /* hashdb header */
    BLOOM *bloom; /* bloom filter */
    HASH_BUCKET *bucket; /* hash buckets */
    HASH_ENTIT *cache; /* hash item cache */
    hashfunc_t hash_func1; /* hash function for hash bucket */
    hashfunc_t hash_func2; /* hash function for btree in the hash bucket */
} HASHDB;

//
HASHDB *hashdb_new(uint64_t tnum, uint32_t bnum, uint32_t cnum, hashfunc_t hash_func1, hashfunc_t hash_func2);
int hashdb_open(HASHDB *hdb, const char *path);
int hashdb_close(HASHDB *hdb, int flash);
int hashdb_set(HASHDB *hdb, char *key, int ksiz, void *valu, int vsiz);
int hashdb_get(HASHDB *hdb, char *key, int ksiz, void *valu, int *vsiz);
int hashdb_unlink(HASHDB *hdb);
#define hashdb_dele(HDB)     free(HDB)

#ifdef __cplusplus
}
#endif

#endif

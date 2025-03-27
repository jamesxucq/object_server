
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
// #include "jemalloc/jemalloc.h"
#include "hashdb.h"

//

static int hashdb_swapout(HASHDB *hdb, uint32_t hash1, uint32_t hash2, HASH_ENTIT *he) {
    uint64_t root;
    uint32_t posi;
    int cmpv, lr = 0x00;
    HASH_ENTIT parent;
    //
    if (!hdb) return -1;
    if (!he || !he->cached) return 0x00;
    /* find offset and parent of the hash parent */
    if (0x00 == he->off) {
        posi = hash1 % hdb->header.bnum;
        root = hdb->bucket[posi].off;
        parent.off = 0x00;
        /* search parent with given key and hash in btree */
        while (root) {
            if (-1 == lseek(hdb->fd, root, SEEK_SET))
                return -1;
            if (HASH_ENTIT_SZ != read(hdb->fd, &parent, HASH_ENTIT_SZ))
                return -1;
            //
            if (parent.hash > hash2) {
                root = parent.left;
                lr = 0x00;
            } else if (parent.hash < hash2) {
                root = parent.right;
                lr = 0x01;
            } else {
                cmpv = memcmp(parent.key, he->key, he->ksiz);
                if (cmpv > 0x00) {
                    root = parent.left;
                    lr = 0x00;
                } else if (cmpv < 0x00) {
                    root = parent.right;
                    lr = 0x01;
                } else {
                    /* never happen */
                }
            }
        }
        /* append mode */
        if (-1 == (he->off = lseek(hdb->fd, 0x00, SEEK_END)))
            return -1;
        if (!hdb->bucket[posi].off) hdb->bucket[posi].off = he->off;
        /* make relationship with parent  */
        if (parent.off) {
            (0x00 == lr) ? (parent.left = he->off) : (parent.right = he->off);
            if (-1 == lseek(hdb->fd, parent.off, SEEK_SET))
                return -1;
            if (HASH_ENTIT_SZ != write(hdb->fd, &parent, HASH_ENTIT_SZ))
                return -1;
        }
    }
    /* flush cached hash entit to file */
    if (-1 == lseek(hdb->fd, he->off, SEEK_SET))
        return -1;
    if (HASH_ENTIT_SZ != write(hdb->fd, he, HASH_ENTIT_SZ))
        return -1;
    //
    he->off = 0x00;
    he->left = 0x00;
    he->right = 0x00;
    he->cached = 0x00;
    //
    return 0x00;
}

static int hashdb_swapin(HASHDB *hdb, char *key, int ksiz, uint32_t hash1, uint32_t hash2, HASH_ENTIT *he) {
    uint32_t posi;
    uint64_t root;
    int cmpv;
    HASH_ENTIT entit;
    //
    if (!hdb || !key || he->cached)
        return -1;
    //
    posi = hash1 % hdb->header.bnum;
    root = hdb->bucket[posi].off;
    /* search entit with given key and hash in btree */
    while (root) {
        if (-1 == lseek(hdb->fd, root, SEEK_SET))
            return -1;
        if (HASH_ENTIT_SZ != read(hdb->fd, &entit, HASH_ENTIT_SZ))
            return -1;
        //
        if (entit.hash > hash2) {
            root = entit.left;
        } else if (entit.hash < hash2) {
            root = entit.right;
        } else {
            cmpv = memcmp(entit.key, key, ksiz);
            if (0x00 == cmpv) { /* find the entit */
                memcpy(he, &entit, HASH_ENTIT_SZ);
                he->cached = 0x01;
                return 0x00;
            } else if (cmpv > 0x00) {
                root = entit.left;
            } else {
                root = entit.right;
            }
        }
    }
    //
    return -2;
}

//

HASHDB *hashdb_new(uint64_t tnum, uint32_t bnum, uint32_t cnum, hashfunc_t hash_func1, hashfunc_t hash_func2) {
    HASHDB *hdb;
    if (!(hdb = malloc(sizeof (HASHDB))))
        return NULL;
    //
    hdb->header.tnum = tnum;
    hdb->header.bnum = bnum;
    hdb->header.cnum = cnum;
    hdb->hash_func1 = hash_func1;
    hdb->hash_func2 = hash_func2;
    //
    return hdb;
}

static int hashdb_readahead(HASHDB *hdb) {
    uint32_t max_ent, posi;
    HASH_ENTIT he;
    //
    if (!hdb || !hdb->fd || !hdb->bloom || !hdb->bucket || !hdb->cache)
        return -1;
    //
    max_ent = (hdb->header.cnum < hdb->header.bnum) ? hdb->header.cnum : hdb->header.bnum;
    uint32_t inde = 0x00;
    for (; inde < max_ent; ++inde) {
        if (-1 == lseek(hdb->fd, hdb->bucket[inde].off, SEEK_SET))
            return -1;
        if (HASH_ENTIT_SZ != read(hdb->fd, &he, HASH_ENTIT_SZ))
            return -1;
        //
        posi = hdb->hash_func1(he.key, he.ksiz) % hdb->header.cnum;
        memcpy(&hdb->cache[posi], &he, HASH_ENTIT_SZ);
        hdb->cache[posi].cached = 0x01;
    }
    //
    return 0x00;
}

int hashdb_open(HASHDB *hdb, const char *path) {
    int f_ok;
    ssize_t rwsiz;
    //
    if (!hdb || !path) return -1;
    //
    f_ok = access(path, F_OK);
    strcpy(hdb->dbname, path);
    hdb->fd = open(path, O_RDWR | O_CREAT, 0666);
    if (-1 == hdb->fd) return -1;
    //
    if (0x00 == f_ok) { /* existed hashdb */
        if (HASHDB_HDR_SZ != read(hdb->fd, &(hdb->header), HASHDB_HDR_SZ)) goto _ERRO_RET;
        if (HASHDB_MAGIC != hdb->header.magi) {
            // printf("the file is not hashdb\n");
            goto _ERRO_RET;
        }
    } else { /* new hashdb */
        hdb->header.magi = HASHDB_MAGIC;
        hdb->header.boff = HASHDB_HDR_SZ;
        hdb->header.hoff = hdb->header.boff + (hdb->header.tnum + CHAR_BIT - 1) / CHAR_BIT;
        hdb->header.voff = hdb->header.hoff + (hdb->header.bnum * HASH_BUCKET_SZ);
    }
    /* initial cache  */
    hdb->bloom = bloom_create(hdb->header.tnum);
    if (!hdb->bloom) goto _ERRO_RET;
    hdb->bucket = (HASH_BUCKET *) malloc(hdb->header.bnum * HASH_BUCKET_SZ);
    if (!hdb->bucket) goto _ERRO_RET;
    uint64_t inde = 0x00;
    for (; inde < hdb->header.bnum; ++inde) hdb->bucket[inde].off = 0x00;
    //
    hdb->cache = (HASH_ENTIT *) malloc(hdb->header.cnum * HASH_ENTIT_SZ);
    if (!hdb->cache) goto _ERRO_RET;
    inde = 0x00;
    for (; inde < hdb->header.cnum; ++inde) {
        hdb->cache[inde].cached = 0x00;
        hdb->cache[inde].off = 0x00;
        hdb->cache[inde].left = 0x00;
        hdb->cache[inde].right = 0x00;
    }
    //
    if (0x00 == f_ok) {
        /* if hashdb exists, then read data to fill up cache */
        if (-1 == lseek(hdb->fd, hdb->header.boff, SEEK_SET)) goto _ERRO_RET;
        rwsiz = hdb->header.hoff - hdb->header.boff;
        if (rwsiz != read(hdb->fd, hdb->bloom->a, rwsiz)) goto _ERRO_RET;
        //
        rwsiz = hdb->header.voff - hdb->header.hoff;
        if (rwsiz != read(hdb->fd, hdb->bucket, rwsiz)) goto _ERRO_RET;
        if (-1 == hashdb_readahead(hdb)) goto _ERRO_RET;
    } else {
        /* prealloc space in the file */
        if (-1 == lseek(hdb->fd, 0x00, SEEK_SET)) goto _ERRO_RET;
        if (HASHDB_HDR_SZ != write(hdb->fd, &(hdb->header), HASHDB_HDR_SZ)) goto _ERRO_RET;
        rwsiz = hdb->header.hoff - hdb->header.boff;
        if (rwsiz != write(hdb->fd, hdb->bloom->a, rwsiz)) goto _ERRO_RET;
        rwsiz = hdb->header.voff - hdb->header.hoff;
        if (rwsiz != write(hdb->fd, hdb->bucket, rwsiz)) goto _ERRO_RET;
    }
    return 0x00;
    //
_ERRO_RET:
    close(hdb->fd);
    unlink(hdb->dbname);
    if (hdb->bloom) bloom_destroy(hdb->bloom);
    if (hdb->bucket) free(hdb->bucket);
    if (hdb->cache) free(hdb->cache);
    //
    return -1;
}

int hashdb_close(HASHDB *hdb, int flash) {
    uint32_t hash1, hash2;
    ssize_t wsiz;
    int retv = 0x00;
    //
    if (!hdb || !hdb->bloom || !hdb->bucket || !hdb->cache)
        return -1;
    if (!flash) goto _CLOSE_EXIT;
    /* flush cached data to file */
    uint64_t inde = 0x00;
    for (; inde < hdb->header.cnum; ++inde) {
        if (hdb->cache[inde].cached) {
            hash1 = hdb->hash_func1(hdb->cache[inde].key, hdb->cache[inde].ksiz);
            hash2 = hdb->cache[inde].hash;
            if (-1 == hashdb_swapout(hdb, hash1, hash2, &hdb->cache[inde])) {
                retv = -1;
                goto _CLOSE_EXIT;
            }
        }
    }
    //
    if (-1 == lseek(hdb->fd, 0x00, SEEK_SET)) {
        retv = -1;
        goto _CLOSE_EXIT;
    }
    if (HASHDB_HDR_SZ != write(hdb->fd, &hdb->header, HASHDB_HDR_SZ)) {
        retv = -1;
        goto _CLOSE_EXIT;
    }
    //
    wsiz = hdb->header.hoff - hdb->header.boff;
    if (wsiz != write(hdb->fd, hdb->bloom->a, wsiz)) {
        retv = -1;
        goto _CLOSE_EXIT;
    }
    wsiz = hdb->header.voff - hdb->header.hoff;
    if (wsiz != write(hdb->fd, hdb->bucket, wsiz)) {
        retv = -1;
        goto _CLOSE_EXIT;
    }

_CLOSE_EXIT: /* destroy cache */
    close(hdb->fd);
    if (hdb->bloom) bloom_destroy(hdb->bloom);
    if (hdb->bucket) free(hdb->bucket);
    if (hdb->cache) free(hdb->cache);
    //
    return retv;
}

int hashdb_set(HASHDB *hdb, char *key, int ksiz, void *valu, int vsiz) {
    int posi;
    uint32_t hash1, hash2;
    uint32_t he_hash1, he_hash2;
    //
    if (!hdb || !key || !valu) return -1;
    //
    hash1 = hdb->hash_func1(key, ksiz);
    hash2 = hdb->hash_func2(key, ksiz);
    /* cache swap in/out with set-associative */
    posi = hash1 % hdb->header.cnum;
    if (hdb->cache[posi].cached && ((hash2 != hdb->cache[posi].hash) || memcmp(key, hdb->cache[posi].key, ksiz))) {
        he_hash1 = hdb->hash_func1(hdb->cache[posi].key, hdb->cache[posi].ksiz);
        he_hash2 = hdb->cache[posi].hash;
        if (-1 == hashdb_swapout(hdb, he_hash1, he_hash2, &hdb->cache[posi]))
            return -1;
    }
    //
    if (!hdb->cache[posi].cached && bloom_check(hdb->bloom, 2, hash1, hash2)) {
        if (-1 == hashdb_swapin(hdb, key, ksiz, hash1, hash2, &hdb->cache[posi]))
            return -1;
    }
    //
    if ((HASHDB_KEY_MAX_SZ < ksiz) || (HASHDB_VALUE_MAX_SZ < vsiz))
        return -1;
    /* fill up cache hash entit */
    memcpy(hdb->cache[posi].key, key, ksiz);
    hdb->cache[posi].ksiz = ksiz;
    memcpy(hdb->cache[posi].valu, valu, vsiz);
    hdb->cache[posi].vsiz = vsiz;
    hdb->cache[posi].hash = hash2;
    if (!hdb->cache[posi].cached) { /* it's a new entit */
        hdb->cache[posi].off = 0x00;
        hdb->cache[posi].left = 0x00;
        hdb->cache[posi].right = 0x00;
        bloom_setbit(hdb->bloom, 2, hash1, hash2);
        hdb->cache[posi].cached = 0x01;
    }
    //
    return 0x00;
}

int hashdb_get(HASHDB *hdb, char *key, int ksiz, void *valu, int *vsiz) {
    int posi, retv;
    uint32_t hash1, hash2;
    uint32_t he_hash1, he_hash2;
    //
    if (!hdb || !key) return -1;
    //
    hash1 = hdb->hash_func1(key, ksiz);
    hash2 = hdb->hash_func2(key, ksiz);
    /* check if the valu is set */
    if (!bloom_check(hdb->bloom, 2, hash1, hash2)) return -2;
    posi = hash1 % hdb->header.cnum;
    if (hdb->cache[posi].cached && ((hash2 != hdb->cache[posi].hash) || memcmp(key, hdb->cache[posi].key, ksiz))) {
        he_hash1 = hdb->hash_func1(hdb->cache[posi].key, hdb->cache[posi].ksiz);
        he_hash2 = hdb->cache[posi].hash;
        if (-1 == hashdb_swapout(hdb, he_hash1, he_hash2, &hdb->cache[posi]))
            return -1;
    }
    //
    if (!hdb->cache[posi].cached) {
        if ((retv = hashdb_swapin(hdb, key, ksiz, hash1, hash2, &hdb->cache[posi]))) return retv;
    }
    memcpy(valu, hdb->cache[posi].valu, hdb->cache[posi].vsiz);
    *vsiz = hdb->cache[posi].vsiz;
    //
    return 0x00;
}

int hashdb_unlink(HASHDB *hdb) {
    if (!hdb) return -1;
    unlink(hdb->dbname);
    return 0x00;
}

#ifdef HASHDB_TEST

float time_fly(struct timeval tstart, struct timeval tend) {
    float tf;
    //
    tf = (tend.tv_sec - tstart.tv_sec) * 1000000 + (tend.tv_usec - tstart.tv_usec);
    tf /= 1000000;
    //
    return tf;
}

int main(int argc, char *argv[]) {
    uint32_t inde, retv, vsiz;
    char key[HASHDB_KEY_MAX_SZ] = {0};
    char valu[HASHDB_VALUE_MAX_SZ] = {0};
    char *dbname = NULL;
    uint32_t max = 0x00;
    int verbose = 0x00;
    int delete = 0x00;
    int setget = 0x00;
    HASHDB *hdb = NULL;
    struct timeval ststart = {0}, stend = {0};
    struct timeval gtstart = {0}, gtend = {0};
    //
    if (argc < 6) {
        printf("usage: %s dbname max_record_num [get] [verbose] [delete]\n", argv[0x00]);
        return 0x00;
    }
    //
    dbname = argv[1];
    max = atol(argv[2]);
    if (0x00 == strcmp(argv[3], "get")) {
        setget = 1;
    }
    if (0x00 == strcmp(argv[4], "verbose")) {
        verbose = 1;
    }
    if (0x00 == strcmp(argv[5], "delete")) {
        delete = 1;
    }
    //
    hdb = hashdb_new(HASHDB_DEFAULT_TNUM, HASHDB_DEFAULT_BNUM, HASHDB_DEFAULT_CNUM, sax_hash, sdbm_hash);
    if (!hdb) {
        printf("hashdb_new failed!\n");
        exit(-1);
    }
    //
    if (-1 == hashdb_open(hdb, dbname)) {
        printf("hashdb_open failed!\n");
        exit(-2);
    }
    //
    if (setget == 1) {
        goto GET_TEST;
    }

SET_TEST:
    /* set values */
    gettimeofday(&ststart, NULL);
    for (inde = 0x00; inde < max; ++inde) {
        sprintf(key, "%d", inde);
        sprintf(valu, "%d", inde);
        if (-1 == hashdb_set(hdb, key, valu, strlen(valu))) {
            printf("hashdb_set failed\n");
            goto EXIT;
        }
        if (verbose) {
            printf("set %s valu = %s\n", key, valu);
        }
    }
    gettimeofday(&stend, NULL);

GET_TEST:
    /* get values */
    gettimeofday(&gtstart, NULL);
    for (inde = 0x00; inde <= max; ++inde) {
        sprintf(key, "%d", inde);
        memset(valu, '\0', HASHDB_VALUE_MAX_SZ);
        retv = hashdb_get(hdb, key, valu, &vsiz);
        switch (retv) {
            case -2:
                printf("the valu of #%s is not set\n", key);
                break;
            case -1:
                printf("hashdb_get failed\n");
                goto EXIT;
            case 0x00:
                if (verbose) {
                    printf("get %s valu = %s\n", key, valu);
                }
                break;
        }
    }
    gettimeofday(&gtend, NULL);

EXIT:
    printf("used time for set records = %f seconds\n", time_fly(ststart, stend));
    printf("used time for get records = %f seconds\n", time_fly(gtstart, gtend));
    if (-1 == hashdb_close(hdb, 1)) {
        printf("close hashdb error\n");
    }
    if (delete) {
        hashdb_unlink(hdb);
    }
    free(hdb);
    //
    return 0x00;
}
#endif

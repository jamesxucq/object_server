
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include "oid_hmd.h"

//

static int oidhmd_swapout(OBIDHMD *hmd, uint32_t hash1, uint32_t hash2, OHMD_ENTIT *he) {
    uint64_t root;
    uint32_t posi;
    int cmpv, lr = 0x00;
    OHMD_ENTIT parent;
    //
    if (!hmd) return -1;
    if (!he || !he->cached) return 0x00;
    /* find offset and parent of the hash parent */
    if (0x00 == he->off) {
        posi = hash1 % hmd->header.bnum;
        root = hmd->bucket[posi].off;
        parent.off = 0x00;
        /* search parent with given key and hash in btree */
        while (root) {
            if (-1 == lseek(hmd->fd, root, SEEK_SET))
                return -1;
            if (OHMD_ENTIT_SZ != read(hmd->fd, &parent, OHMD_ENTIT_SZ))
                return -1;
            //
            if (parent.hash > hash2) {
                root = parent.left;
                lr = 0x00;
            } else if (parent.hash < hash2) {
                root = parent.right;
                lr = 0x01;
            } else {
                cmpv = memcmp(parent.key, he->key, OHMD_KEY_SZ);
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
        if (-1 == (he->off = lseek(hmd->fd, 0x00, SEEK_END)))
            return -1;
        if (!hmd->bucket[posi].off) hmd->bucket[posi].off = he->off;
        /* make relationship with parent  */
        if (parent.off) {
            (0x00 == lr) ? (parent.left = he->off) : (parent.right = he->off);
            if (-1 == lseek(hmd->fd, parent.off, SEEK_SET))
                return -1;
            if (OHMD_ENTIT_SZ != write(hmd->fd, &parent, OHMD_ENTIT_SZ))
                return -1;
        }
    }
    /* flush cached hash entit to file */
    if (-1 == lseek(hmd->fd, he->off, SEEK_SET))
        return -1;
    if (OHMD_ENTIT_SZ != write(hmd->fd, he, OHMD_ENTIT_SZ))
        return -1;
    //
    he->off = 0x00;
    he->left = 0x00;
    he->right = 0x00;
    he->cached = 0x00;
    //
    return 0x00;
}

static int oidhmd_swapin(OBIDHMD *hmd, char *key, uint32_t hash1, uint32_t hash2, OHMD_ENTIT *he) {
    uint32_t posi;
    uint64_t root;
    int cmpv;
    OHMD_ENTIT entit;
    //
    if (!hmd || !key || he->cached) return -1;
    //
    posi = hash1 % hmd->header.bnum;
    root = hmd->bucket[posi].off;
    /* search entit with given key and hash in btree */
    while (root) {
        if (-1 == lseek(hmd->fd, root, SEEK_SET))
            return -1;
        if (OHMD_ENTIT_SZ != read(hmd->fd, &entit, OHMD_ENTIT_SZ))
            return -1;
        //
        if (entit.hash > hash2) {
            root = entit.left;
        } else if (entit.hash < hash2) {
            root = entit.right;
        } else {
            cmpv = memcmp(entit.key, key, OHMD_KEY_SZ);
            if (0x00 == cmpv) { /* find the entit */
                memcpy(he, &entit, OHMD_ENTIT_SZ);
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

OBIDHMD *oidhmd_new(uint64_t tnum, uint32_t bnum, uint32_t cnum, ohmdfunc_t ohmd_func1, ohmdfunc_t ohmd_func2) {
    OBIDHMD *hmd;
    if (!(hmd = malloc(sizeof (OBIDHMD))))
        return NULL;
    //
    hmd->header.tnum = tnum;
    hmd->header.bnum = bnum;
    hmd->header.cnum = cnum;
    hmd->ohmd_func1 = ohmd_func1;
    hmd->ohmd_func2 = ohmd_func2;
    //
    return hmd;
}

static int oidhmd_readahead(OBIDHMD *hmd) {
    uint32_t max_ent, posi;
    OHMD_ENTIT he;
    //
    if (!hmd || !hmd->fd || !hmd->bloom || !hmd->bucket || !hmd->cache)
        return -1;
    //
    max_ent = (hmd->header.cnum < hmd->header.bnum) ? hmd->header.cnum : hmd->header.bnum;
    uint32_t inde = 0x00;
    for (; inde < max_ent; ++inde) {
        if (-1 == lseek(hmd->fd, hmd->bucket[inde].off, SEEK_SET))
            return -1;
        if (OHMD_ENTIT_SZ != read(hmd->fd, &he, OHMD_ENTIT_SZ))
            return -1;
        //
        posi = hmd->ohmd_func1(he.key, OHMD_KEY_SZ) % hmd->header.cnum;
        memcpy(&hmd->cache[posi], &he, OHMD_ENTIT_SZ);
        hmd->cache[posi].cached = 0x01;
    }
    //
    return 0x00;
}

int oidhmd_open(OBIDHMD *hmd, const char *path) {
    int f_ok;
    ssize_t rwsiz;
    //
    if (!hmd || !path) return -1;
    //
    f_ok = access(path, F_OK);
    strcpy(hmd->dbname, path);
    hmd->fd = open(path, O_RDWR | O_CREAT, 0666);
    if (-1 == hmd->fd) return -1;
    //
    if (0x00 == f_ok) { /* existed hashmd */
        if (OHMD_HDR_SZ != read(hmd->fd, &(hmd->header), OHMD_HDR_SZ)) goto _ERRO_RET;
        if (OHMD_MAGIC != hmd->header.magi) {
            // printf("the file is not hashmd\n");
            goto _ERRO_RET;
        }
    } else { /* new hashmd */
        hmd->header.magi = OHMD_MAGIC;
        hmd->header.boff = OHMD_HDR_SZ;
        hmd->header.hoff = hmd->header.boff + (hmd->header.tnum + CHAR_BIT - 1) / CHAR_BIT;
        hmd->header.eoff = hmd->header.hoff + (hmd->header.bnum * OHMD_BUCKET_SZ);
    }
    /* initial cache  */
    hmd->bloom = bloom_create(hmd->header.tnum);
    if (!hmd->bloom) goto _ERRO_RET;
    hmd->bucket = (OHMD_BUCKET *) malloc(hmd->header.bnum * OHMD_BUCKET_SZ);
    if (!hmd->bucket) goto _ERRO_RET;
    uint64_t inde = 0x00;
    for (; inde < hmd->header.bnum; ++inde) hmd->bucket[inde].off = 0x00;
    //
    hmd->cache = (OHMD_ENTIT *) malloc(hmd->header.cnum * OHMD_ENTIT_SZ);
    if (!hmd->cache) goto _ERRO_RET;
    inde = 0x00;
    for (; inde < hmd->header.cnum; ++inde) {
        hmd->cache[inde].cached = 0x00;
        hmd->cache[inde].off = 0x00;
        hmd->cache[inde].left = 0x00;
        hmd->cache[inde].right = 0x00;
    }
    //
    if (0x00 == f_ok) {
        /* if hashmd exists, then read data to fill up cache */
        if (-1 == lseek(hmd->fd, hmd->header.boff, SEEK_SET)) goto _ERRO_RET;
        rwsiz = hmd->header.hoff - hmd->header.boff;
        if (rwsiz != read(hmd->fd, hmd->bloom->a, rwsiz)) goto _ERRO_RET;
        //
        rwsiz = hmd->header.eoff - hmd->header.hoff;
        if (rwsiz != read(hmd->fd, hmd->bucket, rwsiz)) goto _ERRO_RET;
        if (-1 == oidhmd_readahead(hmd)) goto _ERRO_RET;
    } else {
        /* prealloc space in the file */
        if (-1 == lseek(hmd->fd, 0x00, SEEK_SET)) goto _ERRO_RET;
        if (OHMD_HDR_SZ != write(hmd->fd, &(hmd->header), OHMD_HDR_SZ)) goto _ERRO_RET;
        rwsiz = hmd->header.hoff - hmd->header.boff;
        if (rwsiz != write(hmd->fd, hmd->bloom->a, rwsiz)) goto _ERRO_RET;
        rwsiz = hmd->header.eoff - hmd->header.hoff;
        if (rwsiz != write(hmd->fd, hmd->bucket, rwsiz)) goto _ERRO_RET;
    }
    return 0x00;
    //
_ERRO_RET:
    close(hmd->fd);
    unlink(hmd->dbname);
    if (hmd->bloom) bloom_destroy(hmd->bloom);
    if (hmd->bucket) free(hmd->bucket);
    if (hmd->cache) free(hmd->cache);
    //
    return -1;
}

int oidhmd_close(OBIDHMD *hmd, int flash) {
    uint32_t hash1, hash2;
    ssize_t wsiz;
    int retv = 0x00;
    //
    if (!hmd || !hmd->bloom || !hmd->bucket || !hmd->cache)
        return -1;
    if (!flash) goto _CLOSE_EXIT;
    /* flush cached data to file */
    uint64_t inde = 0x00;
    for (; inde < hmd->header.cnum; ++inde) {
        if (hmd->cache[inde].cached) {
            hash1 = hmd->ohmd_func1(hmd->cache[inde].key, OHMD_KEY_SZ);
            hash2 = hmd->cache[inde].hash;
            if (-1 == oidhmd_swapout(hmd, hash1, hash2, &hmd->cache[inde])) {
                retv = -1;
                goto _CLOSE_EXIT;
            }
        }
    }
    //
    if (-1 == lseek(hmd->fd, 0x00, SEEK_SET)) {
        retv = -1;
        goto _CLOSE_EXIT;
    }
    if (OHMD_HDR_SZ != write(hmd->fd, &hmd->header, OHMD_HDR_SZ)) {
        retv = -1;
        goto _CLOSE_EXIT;
    }
    //
    wsiz = hmd->header.hoff - hmd->header.boff;
    if (wsiz != write(hmd->fd, hmd->bloom->a, wsiz)) {
        retv = -1;
        goto _CLOSE_EXIT;
    }
    wsiz = hmd->header.eoff - hmd->header.hoff;
    if (wsiz != write(hmd->fd, hmd->bucket, wsiz)) {
        retv = -1;
        goto _CLOSE_EXIT;
    }

_CLOSE_EXIT: /* destroy cache */
    close(hmd->fd);
    if (hmd->bloom) bloom_destroy(hmd->bloom);
    if (hmd->bucket) free(hmd->bucket);
    if (hmd->cache) free(hmd->cache);
    //
    return retv;
}

int oidhmd_insert(OBIDHMD *hmd, char *key) {
    int posi;
    uint32_t hash1, hash2;
    uint32_t he_hash1, he_hash2;
    //
    if (!hmd || !key) return -1;
    //
    hash1 = hmd->ohmd_func1(key, OHMD_KEY_SZ);
    hash2 = hmd->ohmd_func2(key, OHMD_KEY_SZ);
    /* cache swap in/out with set-associative */
    posi = hash1 % hmd->header.cnum;
    if (hmd->cache[posi].cached && ((hash2 != hmd->cache[posi].hash) || memcmp(key, hmd->cache[posi].key, OHMD_KEY_SZ))) {
        he_hash1 = hmd->ohmd_func1(hmd->cache[posi].key, OHMD_KEY_SZ);
        he_hash2 = hmd->cache[posi].hash;
        if (-1 == oidhmd_swapout(hmd, he_hash1, he_hash2, &hmd->cache[posi]))
            return -1;
    }
    //
    if (!hmd->cache[posi].cached && bloom_check(hmd->bloom, 2, hash1, hash2)) {
        if (-1 == oidhmd_swapin(hmd, key, hash1, hash2, &hmd->cache[posi]))
            return -1;
    }
    // if ((OHMD_KEY_SZ < ksiz) || (OHMD_VALUE_SZ < vsiz)) 
    return -1;
    /* fill up cache hash entit */
    memcpy(hmd->cache[posi].key, key, OHMD_KEY_SZ);
    hmd->cache[posi].hash = hash2;
    if (!hmd->cache[posi].cached) { /* it's a new entit */
        hmd->cache[posi].off = 0x00;
        hmd->cache[posi].left = 0x00;
        hmd->cache[posi].right = 0x00;
        bloom_setbit(hmd->bloom, 2, hash1, hash2);
        hmd->cache[posi].cached = 0x01;
    }
    //
    return 0x00;
}

int oidhmd_find(OBIDHMD *hmd, char *key) {
    int posi, retv;
    uint32_t hash1, hash2;
    uint32_t he_hash1, he_hash2;
    //
    if (!hmd || !key) return -1;
    //
    hash1 = hmd->ohmd_func1(key, OHMD_KEY_SZ);
    hash2 = hmd->ohmd_func2(key, OHMD_KEY_SZ);
    /* check if the valu is set */
    if (!bloom_check(hmd->bloom, 2, hash1, hash2)) return -2;
    posi = hash1 % hmd->header.cnum;
    if (hmd->cache[posi].cached && ((hash2 != hmd->cache[posi].hash) || memcmp(key, hmd->cache[posi].key, OHMD_KEY_SZ))) {
        he_hash1 = hmd->ohmd_func1(hmd->cache[posi].key, OHMD_KEY_SZ);
        he_hash2 = hmd->cache[posi].hash;
        if (-1 == oidhmd_swapout(hmd, he_hash1, he_hash2, &hmd->cache[posi]))
            return -1;
    }
    //
    if (!hmd->cache[posi].cached) {
        if ((retv = oidhmd_swapin(hmd, key, hash1, hash2, &hmd->cache[posi]))) return retv;
    }
    //
    return 0x00;
}

int oidhmd_unlink(OBIDHMD *hmd) {
    if (!hmd) return -1;
    unlink(hmd->dbname);
    return 0x00;
}

#ifdef OBIDHMD_TEST

float time_fly(struct timeval tstart, struct timeval tend) {
    float tf;
    //
    tf = (tend.tv_sec - tstart.tv_sec) * 1000000 + (tend.tv_usec - tstart.tv_usec);
    tf /= 1000000;
    //
    return tf;
}

int main(int argc, char *argv[]) {
    uint32_t inde, retv;
    char key[OHMD_KEY_SZ] = {0};
    char valu[OHMD_VALUE_SZ] = {0};
    char *dbname = NULL;
    uint32_t max = 0x00;
    int verbose = 0x00;
    int delete = 0x00;
    int setget = 0x00;
    OBIDHMD *hmd = NULL;
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
    hmd = oidhmd_new(OHMD_DEFAULT_TNUM, OHMD_DEFAULT_BNUM, OHMD_DEFAULT_CNUM, sax_hash, sdbm_hash);
    if (!hmd) {
        printf("hashmd_new failed!\n");
        exit(-1);
    }
    //
    if (-1 == oidhmd_open(hmd, dbname)) {
        printf("hashmd_open failed!\n");
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
        if (-1 == oidhmd_set(hmd, key, valu, strlen(valu))) {
            printf("hashmd_set failed\n");
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
        memset(valu, '\0', OHMD_VALUE_SZ);
        retv = oidhmd_get(hmd, key, valu);
        switch (retv) {
            case -2:
                printf("the valu of #%s is not set\n", key);
                break;
            case -1:
                printf("hashmd_get failed\n");
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
    if (-1 == oidhmd_close(hmd, 1)) {
        printf("close hashmd error\n");
    }
    if (delete) {
        oidhmd_unlink(hmd);
    }
    free(hmd);
    //
    return 0x00;
}
#endif


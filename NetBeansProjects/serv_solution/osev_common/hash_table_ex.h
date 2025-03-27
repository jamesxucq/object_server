#ifndef HASH_TABLE_EXT_H
#define HASH_TABLE_EXT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "utility/hash_table.h"
#include "utility/hash_map.h"
#include "utility/cache_hmap.h"
#include "utility/action_hmap.h"
#include "utility/oidoid_hmap.h"
#include "obid.h"

    //
#define MATCH_BACKET_SIZE     0x80000  // 512K

    // size = 2^n
#define ROLE_BACKET_SIZE      (1 << 9) // 512
#define BASE_BACKET_SIZE      (1 << 9) // 512
#define INVOK_BACKET_SIZE     (1 << 13) // 0x2000  // 8K
#define COLLE_BACKET_SIZE     (1 << 12) // 0x1000  // 4K
#define CONTA_BACKET_SIZE     (1 << 12) // 0x1000  // 4K

    //
#define creat_lh_ht(BACKET_SIZE)                    hash_create(lh_stri_hash, equal_stri, BACKET_SIZE)
#define creat_none_ht(BACKET_SIZE)                  hash_create(none_hash, equal_md5, BACKET_SIZE)
#define creat_hashmap(FREE_FUNC, BACKET_SIZE)       hmap_create(FREE_FUNC, BACKET_SIZE)
    //
#define creat_cache(BACKET_SIZE)                    cache_create(lh_stri_hash, equal_stri, BACKET_SIZE)
#define creat_obid_cache(BACKET_SIZE)               cache_create(lh_obid_hash, equal_obid, BACKET_SIZE)
    // free_func
#define creat_actio(FREE_FUNC, BACKET_SIZE)         action_create(lh_stri_hash, equal_stri, FREE_FUNC, BACKET_SIZE)
#define creat_obid_actio(FREE_FUNC, BACKET_SIZE)    action_create(lh_obid_hash, equal_obid, FREE_FUNC, BACKET_SIZE)
#define creat_ooid_actio(FREE_FUNC, BACKET_SIZE)    oidoid_create(lh_ooid_hash, equal_ooid, FREE_FUNC, BACKET_SIZE)

    unsigned int none_hash(const void *stri);
    int equal_md5(const void *k1, const void *k2);
    unsigned int lh_stri_hash(const void *stri);
    int equal_stri(const void *k1, const void *k2);
    unsigned int lh_obid_hash(const void *obid);
    int equal_obid(const void *k1, const void *k2);
    unsigned int lh_ooid_hash(const void *obid1, const void *obid2);
    int equal_ooid(const void *k1, const void *k2, const void *k3, const void *k4);

#ifdef __cplusplus
}
#endif

#endif /* HASH_TABLE_EXT_H */
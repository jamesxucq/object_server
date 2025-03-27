
/* 
 * File:   insta_cache.h
 * Author: James Xu
 *
 * Created on 2024.3.31, AM 9:43
 */

#ifndef INSTA_CACHE_H
#define INSTA_CACHE_H

#include "hash_table_ex.h"

#ifdef __cplusplus
extern "C" {
#endif

    //

    struct _inst_hmap_ {
        actionmap *lv2pid_hm; // lv2p key:decl value:lv2pme:attrib map
        actionmap *lv2pme_hm; // lv2p key:decl value:lv2pme map
    };

    typedef struct _inst_hmap_ inst_hmap;

    // instant

#define INSTA_CACHE_INITI(INSTA, LTME_DFUN, INST_DFUN, BACKET_SIZE) { \
    INSTA.lv2pid_hm = creat_actio(INST_DFUN, BACKET_SIZE); \
    INSTA.lv2pme_hm = creat_actio(LTME_DFUN, BACKET_SIZE); \
}

#define FINAL_INSTA_CACHE(INSTA) { \
    action_destroy(INSTA.lv2pme_hm); \
    action_destroy(INSTA.lv2pid_hm); \
}

#define CLEAR_INSTA_CACHE(INSTA) { \
    action_clear(INSTA->lv2pme_hm); \
    action_clear(INSTA->lv2pid_hm); \
}

    //

#ifdef __cplusplus
}
#endif

#endif /* INSTA_CACHE_H */


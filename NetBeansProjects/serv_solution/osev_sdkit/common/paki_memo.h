
/* 
 * File:   paki_memo.h
 * Author: James Xu
 *
 * Created on 2023.6.8, PM 3:10
 */

#ifndef PAKI_MEMO_H
#define PAKI_MEMO_H

#ifdef __cplusplus
extern "C" {
#endif

    //

    inline int pkite_mallo(PK_ITEM *item, size_t size) {
        item->data = (void *) malloc(size);
        if (!item->data) return -1;
        item->size = size;
        return 0x00;
    }

#define FREE_KITE(KITE) free((void *)(KITE)->data)

    // (PK_ITEM *)
    int reall_objec_pkite(PK_ITEM *objnod, PK_ITEM *svalu1, PK_ITEM *svalu2);

    //

    struct _paki_memo_t_ {
        size_t allo_size;
        PK_ITEM item;
        // size_t data_size;
    };
    typedef struct _paki_memo_t_ paki_memo_t;

    //

    inline int pkmem_mallo(paki_memo_t *imem, size_t size) {
        imem->item.data = (void *) malloc(size);
        if (!imem->item.data) return -1;
        imem->allo_size = size;
        return 0x00;
    }

#define FREE_PAKI(OBJ_NOD) free((void *)(OBJ_NOD)->item.data)

    // (paki_memo_t *)
    int reall_objec_pkmem(paki_memo_t *objnod, PK_ITEM *svalu1, PK_ITEM *svalu2);

#ifdef __cplusplus
}
#endif

#endif /* PAKI_MEMO_H */


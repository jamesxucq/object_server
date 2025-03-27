
#include "commo_header.h"

#include "paki_memo.h"

int reall_objec_pkite(PK_ITEM *objnod, PK_ITEM *svalu1, PK_ITEM *svalu2) {
    if (svalu1->size + svalu2->size > (objnod)->size - OBJE_IDENTI_BLEN) {
        uint32 real_szie = (OBJE_IDENTI_BLEN + svalu1->size + svalu2->size);
        void *real_memo = realloc((void *) ((PK_ITEM *) objnod)->data, real_szie);
        if (!real_memo) return -1;
        ((PK_ITEM *) objnod)->data = real_memo;
        ((PK_ITEM *) objnod)->size = real_szie;
    }
    return 0x00;
}

int reall_objec_pkmem(paki_memo_t *objnod, PK_ITEM *svalu1, PK_ITEM *svalu2) {
    if (svalu1->size + svalu2->size > ((paki_memo_t *) objnod)->allo_size) {
        uint32 real_szie = (svalu1->size + svalu2->size);
        void *real_memo = realloc((void *) ((paki_memo_t *) objnod)->item.data, real_szie);
        if (!real_memo) return -1;
        ((paki_memo_t *) objnod)->item.data = real_memo;
        ((paki_memo_t *) objnod)->allo_size = real_szie;
    }
    return 0x00;
}
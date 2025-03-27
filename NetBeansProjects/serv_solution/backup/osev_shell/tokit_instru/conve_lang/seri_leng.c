
#include "commo_header.h"
#include "../common/ccomm_types.h"

#include "seri_leng.h"

//

static inline unsigned int count_entit_size(DATA_TYPE notyp, unsigned int size) {
    unsigned int entit_size;
    entit_size = entit_leng_tab[notyp];
    if (!entit_size) entit_size = size;
    return entit_size;
}

//

unsigned long long count_seri_leng(lv2p_prop *lv2nod) {
    unsigned long long seri_leng = 0x00;
    unsigned int data_size;
    //
    for (; ACCE_COTRL_INVAL != lv2nod->access; ++lv2nod) {
        data_size = count_entit_size(lv2nod->potyp, lv2nod->size);
        if (!data_size) {
            seri_leng = 0x00;
            break;
        }
        seri_leng += data_size;
    }
    //
    return seri_leng;
}

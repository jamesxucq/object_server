
#include "rive_cache.h"
#include "rivfs.h"

//

uint32 cache_initial(riv_live *plive) {
    struct rive_list *rive_data = plive->entry_list;
//    key_cache hmap_key = plive->hmap_key;
    for (; rive_data;)
        // rive_insert(hmap_key(rive_data->item), rive_data, plive->cache_hmap);
    //
    return 0x00;
}

uint32 cache_final(riv_live *plive) {
    // rive_dele(plive->cache_hmap);
    return 0x00;
}



#include <pthread.h>

#include "commo_header.h"
#include "kcomm_header.h"
#include "base_cache.h"

#include "basev_obje.h"

//
basv_lsmp _base_cache_;
pthread_mutex_t _base_cache_mutex_ = PTHREAD_MUTEX_INITIALIZER;

//

int find_base_obid(OUT char *basen, osv_oid_t *find_boid) {
    OSEVPF("[FUNC]:find_base_obid\n");
    char *base_array[MAX_BASE_COUNT];
    char _base_line_[LARGE_CONTE_SIZE];
    if (list_base(base_array, _base_line_, _COMMO_DIRECTORY_))
        return -1;
    //
    osv_oid_t base_obid;
    char **base_namp = base_array;
    for (; base_namp[0x00]; ++base_namp) {
        parse_base_attri(&base_obid, base_namp[0x00]);
        if (OBID_EQUALI(find_boid, &base_obid)) {
            strcpy(basen, base_namp[0x00]);
            return 0x00;
        }
    }
    //
    return -1;
}

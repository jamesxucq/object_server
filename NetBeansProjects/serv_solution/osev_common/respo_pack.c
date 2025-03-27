#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "third_party.h"
#include "respo_pack.h"
#include "debug_funct_osv.h"

// compress data

int resp_data_pack(void *buffe, size_t *lenp, PK_ITEM *key, PK_ITEM *data) {
    // OSEVPF("[FUNC]:resp_data_pack\n");
    resp_node_t *resnod = (resp_node_t *) buffe;
    //
    memcpy(&(resnod->obid.stoid), key->data, sizeof (unsigned long long));
    resnod->leng = data->size;
    memcpy(resnod->data, data->data, data->size);
    //
    lenp[0x00] = RESPON_ATTACH_LENGTH + data->size;
    return 0x00;
}

// compress data

int resp_data_pack_obid(void *buffe, size_t *lenp, osv_oid_i *obid, PK_ITEM *data) {
    // OSEVPF("[FUNC]:resp_data_pack_obid\n");
    resp_node_t *resnod = (resp_node_t *) buffe;
    //
    memcpy(&(resnod->obid.stoid), &obid->stoid, sizeof (unsigned long long));
    resnod->leng = data->size;
    memcpy(resnod->data, data->data, data->size);
    //
    lenp[0x00] = RESPON_ATTACH_LENGTH + data->size;
    return 0x00;
}

//

int resp_data_unpack() {
    // OSEVPF("[FUNC]:resp_data_unpack\n");
    return 0x00;
}


//

int resp_data_size() {
    // OSEVPF("[FUNC]:resp_data_size\n");
    return 0x00;
}


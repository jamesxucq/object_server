
#include "commo_header.h"
#include "kcomm_header.h"
#include "conte_resou.h"
#include "rive_struct.h"

#include "stora_handl.h"

// FILL_UNIQUE_OBID((osv_oid_i *) & key_obid);

int load_proj_data(FILE *resul, riv_curso_t *proj_curso, rive_ha *stora_ha, osv_oid_t *key_obid) {
    // OSEVPF("1 --- proj_curso:%016X\n", proj_curso);
    PK_ITEM key, valu;
    stora_ha->set_sid_key(proj_curso, &((osv_oid_i *) & key_obid)->stoid);
    if (stora_ha->search_curso(proj_curso))
        return -1;
    //
    stora_ha->get_key(proj_curso, &key);
    stora_ha->get_value(proj_curso, &valu);
    // dylid->solve(obje_memp, (uint64 *) key.data, &valu);
    // 0x00 >= APPEND_DATAS(resul, obje_memp, dylid->data_size)
    PACKING_KEY_UNPACK(((osv_oid_i *) key_obid)->stoid, (uint64 *) key.data);
    if (build_objec_strea_ensi(resul, key_obid, &valu))
        return -1;
    //
    return 0x00;
}

#include "commo_header.h"
#include "kcomm_header.h"

#include "kcomm_struct.h"

#include "build_proje_renti.h"

//

int build_object_strea_rssi(FILE *proj_data, rive_ha *stora_ha, rsent_sing *robj_data, riv_curso_t *scurso) {
    OSEVPF("[FUNC]:build_object_strea_rssi\n");
    // OSEVPF("robj_data:%p scurso:%p\n", robj_data, scurso);
    // OSEVPF("rinde:%d renti:%llu\n", robj_data->rinde, robj_data->renti);
    PK_ITEM svalu;
    stora_ha->set_sid_key(scurso, &robj_data->senti);
    if (0x00 != stora_ha->search_curso(scurso))
        return -1;
    stora_ha->get_value(scurso, &svalu);
    //
    if (0x00 >= APPEND_DATAS(proj_data, svalu.data, svalu.size))
        return -1;
    //
    return svalu.size;
}

//

int build_object_strea_rsob(FILE *proj_data, rive_ha *stora_ha, rsent_sing *robj_data, riv_curso_t *scurso) {
    OSEVPF("[FUNC]:build_object_strea_rsob\n");
    // OSEVPF("robj_data:%p scurso:%p\n", robj_data, scurso);
    // OSEVPF("rinde:%d renti:%llu\n", robj_data->rinde, robj_data->renti);
    PK_ITEM svalu;
    stora_ha->set_sid_key(scurso, &robj_data->senti);
    if (0x00 != stora_ha->search_curso(scurso))
        return -1;
    stora_ha->get_value(scurso, &svalu);
    //
    if (0x00 >= APPEND_DATAS(proj_data, svalu.data, svalu.size))
        return -1;
    //
    return svalu.size;
}

//

int build_object_strea_rsco(FILE *proj_data, rive_ha *stora_ha, rsent_sing *robj_data, riv_curso_t *scurso) {
    OSEVPF("[FUNC]:build_object_strea_rsco\n");
    // OSEVPF("robj_data:%p scurso:%p\n", robj_data, scurso);
    // OSEVPF("rinde:%d renti:%llu\n", robj_data->rinde, robj_data->renti);
    PK_ITEM svalu;
    stora_ha->set_sid_key(scurso, &robj_data->senti);
    if (0x00 != stora_ha->search_curso(scurso))
        return -1;
    stora_ha->get_value(scurso, &svalu);
    //
    if (0x00 >= APPEND_DATAS(proj_data, svalu.data, svalu.size))
        return -1;
    //
    return svalu.size;
}

//

int build_object_strea_rdsi(FILE *proj_data, rive_ha *stora_ha, rdent_sing *robj_data, riv_curso_t *scurso) {
    OSEVPF("[FUNC]:build_object_strea_rdsi\n");
    // OSEVPF("robj_data:%p scurso:%p\n", robj_data, scurso);
    // OSEVPF("rinde:%d renti:%llu\n", robj_data->rinde, robj_data->renti);
    PK_ITEM svalu;
    stora_ha->set_sid_key(scurso, robj_data);
    if (0x00 != stora_ha->search_curso(scurso))
        return -1;
    stora_ha->get_value(scurso, &svalu);
    //
    if (0x00 >= APPEND_DATAS(proj_data, svalu.data, svalu.size))
        return -1;
    //
    return svalu.size;
}

//

int build_object_strea_rdob(FILE *proj_data, rive_ha *stora_ha, rdent_sing *robj_data, riv_curso_t *scurso) {
    OSEVPF("[FUNC]:build_object_strea_rdob\n");
    // OSEVPF("robj_data:%p scurso:%p\n", robj_data, scurso);
    // OSEVPF("rinde:%d renti:%llu\n", robj_data->rinde, robj_data->renti);
    PK_ITEM svalu;
    stora_ha->set_sid_key(scurso, robj_data);
    if (0x00 != stora_ha->search_curso(scurso))
        return -1;
    stora_ha->get_value(scurso, &svalu);
    //
    if (0x00 >= APPEND_DATAS(proj_data, svalu.data, svalu.size))
        return -1;
    //
    return svalu.size;
}

//

int build_object_strea_rdco(FILE *proj_data, rive_ha *stora_ha, rdent_sing *robj_data, riv_curso_t *scurso) {
    OSEVPF("[FUNC]:build_object_strea_rdco\n");
    // OSEVPF("robj_data:%p scurso:%p\n", robj_data, scurso);
    // OSEVPF("rinde:%d renti:%llu\n", robj_data->rinde, robj_data->renti);
    PK_ITEM svalu;
    stora_ha->set_sid_key(scurso, robj_data);
    if (0x00 != stora_ha->search_curso(scurso))
        return -1;
    stora_ha->get_value(scurso, &svalu);
    //
    if (0x00 >= APPEND_DATAS(proj_data, svalu.data, svalu.size))
        return -1;
    //
    return svalu.size;
}

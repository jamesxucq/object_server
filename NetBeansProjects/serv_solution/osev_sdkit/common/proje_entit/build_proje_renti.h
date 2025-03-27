
/* 
 * File:   build_proje_renti.h
 * Author: James Xu
 *
 * Created on 2024.6.6, PM 2:12
 */

#ifndef BUILD_PROJE_RENTI_H
#define BUILD_PROJE_RENTI_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    int build_object_strea_rssi(FILE *proj_data, rive_ha *stora_ha, rsent_sing *robj_data, riv_curso_t *scurso);
    int build_object_strea_rsob(FILE *proj_data, rive_ha *stora_ha, rsent_sing *robj_data, riv_curso_t *scurso);
    int build_object_strea_rsco(FILE *proj_data, rive_ha *stora_ha, rsent_sing *robj_data, riv_curso_t *scurso);

    //
    int build_object_strea_rdsi(FILE *proj_data, rive_ha *stora_ha, rdent_sing *robj_data, riv_curso_t *scurso);
    int build_object_strea_rdob(FILE *proj_data, rive_ha *stora_ha, rdent_sing *robj_data, riv_curso_t *scurso);
    int build_object_strea_rdco(FILE *proj_data, rive_ha *stora_ha, rdent_sing *robj_data, riv_curso_t *scurso);

#ifdef __cplusplus
}
#endif

#endif /* BUILD_PROJE_RENTI_H */


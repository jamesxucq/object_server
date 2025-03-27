
/* 
 * File:   stor_seio.h
 * Author: James Xu
 *
 * Created on 2017.2.7, AM 10:12
 */

#ifndef SESS_LIST_H
#define SESS_LIST_H

#include "rive_struct.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    stor_seio *activ_seion(seio_list **seio_lsth, rive_ha *stora_ha, riv_conne_t *conne);
    void quiet_seion(seio_list **seio_lsth, stor_seio *sto_seio);
    void destroy_seion(seio_list *selist, rive_ha *stora_ha);

    //

#ifdef __cplusplus
}
#endif

#endif /* SESS_LIST_H */


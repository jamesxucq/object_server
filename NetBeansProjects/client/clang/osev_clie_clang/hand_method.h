
#ifndef HAND_METHOD_H
#define HAND_METHOD_H

#include "reque_conne.h"
#include "reque_respo.h"

#ifdef __cplusplus
extern "C" {
#endif

    // 0x00:success -1:error
    int hand_reques(resp_head *res_had, int conne_sock, requ_data_t *req_dat);
    
    // 0x00:success -1:error
    int hand_respon(resp_data_t *res_dat, int conne_sock, requ_data_t *req_dat);

#ifdef __cplusplus
}
#endif

#endif /* HAND_METHOD_H */


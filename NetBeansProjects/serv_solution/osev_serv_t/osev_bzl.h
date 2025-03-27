#ifndef SERV_BZL_H_
#define SERV_BZL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "osev_obje.h"

    serv_config *servbzl_create(char *xml_config);
    int servbzl_destroy();

    //
    serv_config *get_serv_config();

    //

#define SET_MODTIME_BZL(BASEN, INVAL) \
    SET_FILE_MODTIME_EXT(BASEN, (char *)INVAL->_data_line_, INVAL->last_write)

#ifdef __cplusplus
}
#endif

#endif /* SERV_BZL_H_ */

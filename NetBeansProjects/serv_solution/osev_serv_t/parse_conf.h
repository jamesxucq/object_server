#ifndef _PARSECONF_H_
#define _PARSECONF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "commo_header.h"
#include "sconfig.h"

    //
    extern serv_config _serv_conf_;
    int serv_config_from_xml(serv_config *config, const char *xml_config);
    void serialize(char *sbuf, serv_config *config);

#ifdef __cplusplus
}
#endif

#endif /* _PARSECONF_H_ */

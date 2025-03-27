
#ifndef PROCESS_CYCLE_H
#define PROCESS_CYCLE_H

#include "parse_conf.h"

#ifdef __cplusplus
extern "C" {
#endif

//
int master_process_cycle(serv_config *config);
int single_process_cycle(serv_config *config);


#ifdef __cplusplus
}
#endif

#endif /* PROCESS_CYCLE_H */


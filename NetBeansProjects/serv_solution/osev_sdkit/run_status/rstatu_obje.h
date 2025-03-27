
/* 
 * File:   rstatu_obje.h
 * Author: James Xu
 *
 * Created on 2016.12.27, PM 1:52
 */

#ifndef RSTATU_OBJE_H
#define RSTATU_OBJE_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    extern char _osev_name_[OSEV_LENGTH];

    //
    
    inline void init_osev_name(char *osevn) {
        fprintf(stdout, "Set object server name OK!\n");
        strcpy(_osev_name_, osevn);
    }

    inline char *get_osev_name() {
        return _osev_name_;
    }

#ifdef __cplusplus
}
#endif

#endif /* RSTATU_OBJE_H */


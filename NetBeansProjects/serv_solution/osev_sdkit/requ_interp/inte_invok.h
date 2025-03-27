
/* 
 * File:   inte_invok.h
 * Author: James Xu
 *
 * Created on 2016.12.29, PM 1:51
 */

// the first level

#ifndef INTE_INVOK_H
#define INTE_INVOK_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
    void invok_post_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void invok_statu_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void invok_creat_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void invok_repla_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void invok_drop_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void invok_integra_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void invok_reload_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);

#ifdef __cplusplus
}
#endif

#endif /* INTE_INVOK_H */



/* 
 * File:   inte_query.h
 * Author: James Xu
 *
 * Created on 2016.12.29, PM 1:51
 */

#ifndef INTE_QUERY_H
#define INTE_QUERY_H

#include "commo_header.h"

// level foup 

#ifdef __cplusplus
extern "C" {
#endif

    // contain
    void query_post_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void query_statu_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void query_creat_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void query_drop_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void query_updat_inpe(pams_valu *pamvu, char *_data_line_, FILE *requ_stram);
    void query_inser_inpe(pams_valu *pamvu, char *_data_line_, FILE *requ_stram);
    void query_searc_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void query_invok_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void query_facto_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);




    //

#ifdef __cplusplus
}
#endif

#endif /* INTE_QUERY_H */



/* 
 * File:   inte_colle.h
 * Author: James Xu
 *
 * Created on 2021.5.8, AM 10:42
 */

// the second level

#ifndef INTE_COLLE_H
#define INTE_COLLE_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    void colle_post_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void colle_statu_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void colle_creat_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void colle_repla_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void colle_drop_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void colle_integra_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void colle_reload_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);



#ifdef __cplusplus
}
#endif

#endif /* INTE_COLLE_H */


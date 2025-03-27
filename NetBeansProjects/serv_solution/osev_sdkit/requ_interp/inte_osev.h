
/* 
 * File:   inte_osev.h
 * Author: James Xu
 *
 * Created on 2016.12.29, PM 1:51
 */

#ifndef INTE_OSEV_H
#define INTE_OSEV_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    void osev_authe_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    
    //
    void osev_post_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    
    //
    void osev_stat_echo_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void osev_stat_stati_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    
    // comand
    void osev_comd_open_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void osev_comd_close_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    
    //
    void osev_priv_list_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void osev_priv_role_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void osev_priv_user_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);

#ifdef __cplusplus
}
#endif

#endif /* INTE_OSEV_H */


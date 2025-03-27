
/* 
 * File:   inte_base.h
 * Author: James Xu
 *
 * Created on 2018.2.14, PM 2:03
 */

#ifndef INTE_BASE_H
#define INTE_BASE_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    //    extern char* (**parse_privile_tab[])(pams_valu *, char *, char *);
    //    int valid_privile();
    void base_authe_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);

    //
    void base_post_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);

    //
    void base_stat_echo_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void base_stat_stati_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);

    // void bstat_command_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void base_comd_open_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void base_comd_close_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);

    //
    void base_priv_list_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void base_priv_role_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);
    void base_priv_user_inpe(pams_valu *pamvu, char *_data_line_, char *requ_memo);


#ifdef __cplusplus
}
#endif

#endif /* INTE_BASE_H */


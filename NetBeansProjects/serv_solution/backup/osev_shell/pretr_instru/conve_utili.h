
/* 
 * File:   conve_utili.h
 * Author: Administrator
 *
 * Created on 2018.3.27, PM 3:01
 */

#ifndef CONVE_UTILI_H
#define CONVE_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    int ochk_status_pamvs(char **pamvp);
    int ochk_statis_pamvs(char **pamvp);
    int bchk_status_pamvs(char **pamvp);
    int bchk_statis_pamvs(char **pamvp);

    // osev
    int oconv_open_styl(char **pamvp);
    int oconv_close_styl(char **pamvp);
    int oconv_echo_styl(char **pamvp);
    int oconv_status_styl(char **pamvp);
    int oconv_statis_styl(char **pamvp);
    int oconv_list_pamvs(char **pamvp);
    int oconv_role_pamvs(char **pamvp, const char *objide);
    int oconv_user_pamvs(char **pamvp);

    // base
    int bconv_open_styl(char **pamvp, const char *objide, osev_clie *oclie);
    int bconv_close_styl(char **pamvp, const char *objide, char *_sline_, osev_clie *oclie);
    int bconv_echo_styl(char **pamvp, const char *objide, char *_sline_, osev_clie *oclie);
    int bconv_status_styl(char **pamvp, const char *objide, osev_clie *oclie);
    int bconv_statis_styl(char **pamvp, const char *objide, char *_sline_, osev_clie *oclie);
    int bconv_list_pamvs(char **pamvp);
    int bconv_role_pamvs(char **pamvp, const char *objide);
    int bconv_user_pamvs(char **pamvp);
    
    // contain level
    // lev1
    int lconv_levon_pamvs(unsigned int levivk, char **pamvp);
    int lconv_levon_exten(unsigned int levivk, char **pamvp, char *_sline_);
    // lv2p
    int lconv_levtp_pamvs(unsigned int levivk, char **pamvp);
    // lev3
    int lconv_levth_pamvs(unsigned int levivk, char **pamvp);
    int lconv_levth_exten(unsigned int levivk, char **pamvp, char *_sline_);
    // lv4p
    int lconv_levfp_pamvs(unsigned int levivk, char **pamvp);


#ifdef __cplusplus
}
#endif

#endif /* CONVE_UTILI_H */


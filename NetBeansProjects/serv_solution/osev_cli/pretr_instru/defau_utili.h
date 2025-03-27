
/* 
 * File:   defau_utili.h
 * Author: James Xu
 *
 * Created on 2018.4.25, AM 9:17
 */

#ifndef DEFAU_UTILI_H
#define DEFAU_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

    // osev
    void defva_opost(char **pamvp, char *_sline_);
    int defva_ocomd_open(char **pamvp, char *_sline_);
    int defva_ostat_echo(char **pamvp, char *_sline_);
    void defva_ostat_statis(char **pamvp, char *_sline_);
    int defva_opriv_list(char **pamvp);
    int defva_opriv_role(char **pamvp, const char *objide);
    int defva_opriv_user(char **pamvp);

    // base
    void defva_bpost(char **pamvp, char *_sline_);
    int defva_bcomd_open(char **pamvp, char *_sline_);
    int defva_bstat_echo(char **pamvp, char *_sline_);
    void defva_bstat_statis(char **pamvp, char *_sline_);
    int defva_bpriv_list(char **pamvp);
    int defva_bpriv_role(char **pamvp, const char *objide);
    int defva_bpriv_user(char **pamvp);

    // object level
    int defva_levon_exten(unsigned int levivk, char **pamvp, char *_sline_);
    int defva_levon_pamvs(unsigned int levivk, char **pamvp, char *_sline_);
    int defva_levtp_pamvs(unsigned int levivk, char **pamvp, char *_sline_);
    int defva_levth_exten(unsigned int levivk, char **pamvp, char *_sline_);
    int defva_levth_pamvs(unsigned int levivk, char **pamvp, char *_sline_);
    int defva_levfp_pamvs(unsigned int levivk, unsigned int invok, char **pamvp, char *_sline_);


#ifdef __cplusplus
}
#endif

#endif /* DEFAU_UTILI_H */


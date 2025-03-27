
/* 
 * File:   valid_logic.h
 * Author: James Xu
 *
 * Created on 2024.5.17, PM 4:05
 */

#ifndef VALID_LOGIC_H
#define VALID_LOGIC_H

#ifdef __cplusplus
extern "C" {
#endif

    //

    inline int cchk_clie_use(char **pamvp) {
        unsigned int inde = 0x00;
        for (; pamvp[0x00]; ++pamvp) ++inde;
        if ((0x01 != inde) && (0x03 != inde))
            return -1;
        return 0x00;
    }

    //
    int ochk_post(char **pamvp);
    int bchk_post(char **pamvp);
    //
    int ochk_statu_stati(char **pamvp);
    int bchk_statu_stati(char **pamvp);

    //
    int ochk_priv_role(char **pamvp, const char *objide);
    int bchk_priv_role(char **pamvp, const char *objide);
    int ochk_priv_user(char **pamvp);
    int bchk_priv_user(char **pamvp);
    int ochk_priv_list(char **pamvp);
    int bchk_priv_list(char **pamvp);

    //
    int valid_levon_exten(unsigned int levivk, char **pamvp);
    int valid_levon_pamvs(unsigned int levivk, char **pamvp);

    //
    int valid_levtp_pamvs(unsigned int levivk, unsigned int invok, char **pamvp);

    //
    int valid_levfp_pamvs(unsigned int levivk, unsigned int invok, char **pamvp);

#ifdef __cplusplus
}
#endif

#endif /* VALID_LOGIC_H */



/* 
 * File:   filli_conve.h
 * Author: Administrator
 *
 * Created on 2018.4.18, AM 8:45
 */

#ifndef FILLI_CONVE_H
#define FILLI_CONVE_H

#ifdef __cplusplus
extern "C" {
#endif

    //

    char *filli_creat_eobje_exte(char *cont_iden, char *comd_meth, char *line_str);
    char *filli_creat_eobje_redi(char *objide, char *comd_meth, char *line_str);
    char *filli_creat_cobje(char *objide, char *comd_meth, char *line_str);

    //

    char *filli_creat_class(char *objide, char *comd_meth, char *line_str);
    char *filli_creat_metho(char *objide, char *comd_meth, char *line_str);
    char *filli_creat_metho_exte(char *objide, char *comd_meth, char *line_str);
    // char *filli_base_stat(cli_inst *cinst, char *line_str, unsigned int stat_valu);


#ifdef __cplusplus
}
#endif

#endif /* FILLI_CONVE_H */


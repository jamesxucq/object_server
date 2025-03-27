
/* 
 * File:   compi_clang.h
 * Author: James Xu
 *
 * Created on 2022.11.22, PM 3:47
 */

#ifndef COMPI_CLANG_H
#define COMPI_CLANG_H

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_PARAM_CNT   32

    //

    int compi_clang_libra(char *libr_path, char *clan_path, char *comp_mesg);
    int compi_clang_objec(char *obje_path, char *clan_path, char *comp_mesg);
    int compi_objec_libra(char *libr_path, char **obje_namp, char *comp_mesg);


#ifdef __cplusplus
}
#endif

#endif /* COMPI_CLANG_H */


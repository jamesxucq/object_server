
/* 
 * File:   cfile_utili.h
 * Author: James Xu
 *
 * Created on 2022.11.11, AM 10:29
 */

#ifndef CFILE_UTILI_H
#define CFILE_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

    //    
    int delet_libra_file(char *basen, char *librn);
    int bakup_libra_file(char *basen, char *librn);
    int recov_libra_file(char *basen, char *librn);

#ifdef __cplusplus
}
#endif

#endif /* CFILE_UTILI_H */


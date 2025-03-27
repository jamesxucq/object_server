
/* 
 * File:   instru_utili.h
 * Author: james
 *
 * Created on 2023.4.15, AM 9:49
 */

#ifndef INSTRU_UTILI_H
#define INSTRU_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

    // finish_instru
    void clien_finis(clie_resu *resul, char *instru);
    void osev_finis(clie_resu *resul, unsigned int levivk);
    void base_finis(clie_resu *resul, unsigned int levivk);
    void level_finis(clie_resu *resul);


#ifdef __cplusplus
}
#endif

#endif /* INSTRU_UTILI_H */


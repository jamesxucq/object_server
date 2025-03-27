
/* 
 * File:   instru_utili.h
 * Author: James Xu
 *
 * Created on 2023.4.15, AM 9:49
 */

#ifndef INSTRU_UTILI_H
#define INSTRU_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

    // finish_instru
    void clien_finis(clit_resu *resul, char *instru);
    void osev_finis(clit_resu *resul, unsigned int levivk, unsigned int invok);
    void base_finis(clit_resu *resul, unsigned int levivk, unsigned int invok);
    void level_finis(clit_resu *resul);


#ifdef __cplusplus
}
#endif

#endif /* INSTRU_UTILI_H */



/* 
 * File:   defaul_objide.h
 * Author: James Xu
 *
 * Created on 2024.1.2, PM 2:55
 */

#ifndef DEFAUL_OBJIDE_H
#define DEFAUL_OBJIDE_H

#ifdef __cplusplus
extern "C" {
#endif

    inline void filli_defau_objid(char *objide, uint32 cli_mode, uint32 run_level) {
        switch (cli_mode) {
            case CITP_CLEV:
                if (LEVEL_EXTEND_SPACE & run_level)
                    strcpy(objide, _leve_defa_obje_.obje_iden);
                else strcpy(objide, BASE_DEFAULT_VALUE);
                break;
            case CITP_OSVB:
                strcpy(objide, OSEV_DEFAULT_VALUE);
                break;
            case CITP_CLIE:
                strcpy(objide, CLIE_DEFAULT_VALUE);
                break;
        }
    }

    //

    inline void filli_osev_objide(char *objide, char *levivk, char *invok) {
        strcpy(invok, levivk);
        strcpy(levivk, objide);
        strcpy(objide, OSEV_DEFAULT_VALUE);
    }


#ifdef __cplusplus
}
#endif

#endif /* DEFAUL_OBJIDE_H */


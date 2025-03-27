
/* 
 * File:   cinstru.h
 * Author: james
 *
 * Created on 2023.4.14, PM 3:44
 */

#ifndef CINSTRU_H
#define CINSTRU_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    // clie must handle, general is server handle, INST_CLIINF local handle

    enum _INSTRU_ {
        INST_INVAL = 0x00,
        INST_CONNE, // client conne (osev)
        INST_EXIT, // client exit (clie)
        INST_BYE, // client bye (clie)
        INST_CLIINF, // general (clie)
        INST_USE, // client use (clie)
        INST_QUIT, // client quit (clie)
        INST_OSEV, // osev general (osev)
        INST_BASE, // base general (osev)
        INST_CLILEV, // client level (clie) 
        INST_LEVO, // conta level (osev)
        INST_LVTP, // conta level (osev)
        INST_LEVT, // conta level (osev)
        INST_LVFP // conta level (osev)
    };

    typedef enum _INSTRU_ INSTRU;

#define ATTRI_INVALID      0x00
#define ATTRI_INSTRUC      0x00000001
#define ATTRI_TOOLKIT      0x00000002
    //

    enum _TOKIT_INST_ {
        KITS_INVAL = 0x00,
        KITS_LIST,
        KITS_LOAD,
        KITS_SAVE,
        KITS_CONVE,
        KITS_PRETTY,
        KITS_KEYVAL,
        KITS_FORMAT,
        KITS_EXPAND
    };

    typedef enum _TOKIT_INST_ TOKIT_INST;

    //

    struct _cli_inst_ {
        char coline[LARGE_TEXT_SIZE];
        unsigned int inst_levtyp; // levtyp
        unsigned int inst_attrib; //
        const char obje_iden[OBJN_LENGTH];
        char cont_levivk[LVON_LENGTH];
        unsigned int inst_levivk; // levivk
        char cont_invok[LVON_LENGTH];
        unsigned int inst_invok; // invok
        //
        char pamtyp[PARAM_COUNT];
        const char *pamcon[PARAM_COUNT];
        char _pline_[LARGE_CONTE_SIZE];
        int reserved;
    };

    typedef struct _cli_inst_ cli_inst;

#ifdef __cplusplus
}
#endif

#endif /* CINSTRU_H */



/* 
 * File:   boolean.h
 * Author: James Xu
 *
 * Created on 2024.4.25, AM 9:32
 */

#ifndef BOOLEAN_H
#define BOOLEAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

    //

    /*
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif
     */

    enum _bool_osv_ {
        FALSE_OSV = 0x00,
        TRUE_OSV = 0x01,
        INVAL_OSV = 0x02,
    };

    typedef enum _bool_osv_ bool_osv;

    //
    extern char *bool_stri_tab[];
    extern char *BOOL_STRI_TAB[];

    //

    inline bool_osv stri_bool(char *bstr) {
        if (!strcmp("true", bstr)) return TRUE_OSV;
        else if (!strcmp("false", bstr)) return FALSE_OSV;
        // _LOG_ERROR("stri_bool, bstr:%s", bstr);
        return FALSE_OSV;
    }

#define stri_bool_valu(VALUE, BOOL_STRI) { \
    if (!strcmp("true", BOOL_STRI)) VALUE = TRUE_OSV; \
    else if (!strcmp("false", BOOL_STRI)) VALUE = FALSE_OSV; \
    else VALUE = INVAL_OSV; \
    /* else _LOG_ERROR("stri_bool_valu, bstr:%s", BOOL_STRI); */\
}

    //

    inline bool_osv STRI_BOOL(char *bstr) {
        if (!strcmp("TRUE", bstr)) return TRUE_OSV;
        else if (!strcmp("FALSE", bstr)) return FALSE_OSV;
        // _LOG_ERROR("STRI_BOOL, bstr:%s", bstr);
        return INVAL_OSV;
    }

#define STRI_BOOL_VALU(VALUE, BOOL_STRI){ \
    if (!strcmp("TRUE", BOOL_STRI)) VALUE = TRUE_OSV; \
    else if (!strcmp("FALSE", BOOL_STRI)) VALUE = FALSE_OSV; \
    else VALUE = INVAL_OSV; \
    /* else _LOG_ERROR("STRI_BOOL_VALU, bstr:%s", BOOL_STRI); */\
}

    //

    inline bool_osv stri_BOOL(char *bstr) {
        if (!strcasecmp("true", bstr)) return TRUE_OSV;
        else if (!strcasecmp("false", bstr)) return FALSE_OSV;
        // _LOG_ERROR("stri_BOOL, bstr:%s", bstr);
        return INVAL_OSV;
    }

#define stri_BOOL_VALU(VALUE, BOOL_STRI) { \
    if (!strcasecmp("true", BOOL_STRI)) VALUE = TRUE_OSV; \
    else if (!strcasecmp("false", BOOL_STRI)) VALUE = FALSE_OSV; \
    else VALUE = INVAL_OSV; \
    /* else _LOG_ERROR("stri_BOOL_VALU, bstr:%s", BOOL_STRI); */\
}

    //

#ifdef __cplusplus
}
#endif

#endif /* BOOLEAN_H */


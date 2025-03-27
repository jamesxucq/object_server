
/* 
 * File:   xml_utili.h
 * Author: James Xu
 *
 * Created on 2017.5.25, PM2:11
 */

#ifndef XML_UTILI_H
#define XML_UTILI_H

#include "utility/stcstr.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
#define CHK_ELEMENT_VALUE(PARSE_TOKEN, LABEL_START, LABEL_END) { \
    char *elem_end, *elem_start; \
    if((elem_start = strstr(PARSE_TOKEN, LABEL_START.data))) { \
        elem_start += LABEL_START.slen; \
        if ((elem_end = strstr(elem_start, LABEL_END.data))) { \
            PARSE_TOKEN = elem_end + LABEL_END.slen; \
        } else PARSE_TOKEN = NULL; \
    } else PARSE_TOKEN = NULL; \
}

    //
#define GET_ELEMENT_VALUE(ELEMENT_VALUE, PARSE_TOKEN, LABEL_START, LABEL_END) { \
    char *elem_end, *elem_start; \
    if((elem_start = strstr(PARSE_TOKEN, LABEL_START.data))) { \
        elem_start += LABEL_START.slen; \
        if ((elem_end = strstr(elem_start, LABEL_END.data))) { \
            strzcpy(ELEMENT_VALUE, elem_start, elem_end - elem_start); \
            PARSE_TOKEN = elem_end + LABEL_END.slen; \
        } else PARSE_TOKEN = NULL; \
    } else PARSE_TOKEN = NULL; \
}

    //
    char *get_attval(char *valu, char *attstr, osv_str_t *alab);
    char *get_attval2(char *valu1, char *valu2, char *attstr, osv_str_t *alab1, osv_str_t *alab2);
    char *get_attval3(char *valu1, char *valu2, char *valu3, char *attstr, osv_str_t *alab1, osv_str_t *alab2, osv_str_t *alab3);
    char *get_attval4(char *valu1, char *valu2, char *valu3, char *attstr, char *valu4, osv_str_t *alab1, osv_str_t *alab2, osv_str_t *alab3, osv_str_t *alab4);

    //

#define GET_ATTRIB_VALUE(ATTRIB_VALUE, PARSE_TOKEN, LABEL_START, ATTRIB_LABEL) { \
    char *elem_end, *elem_start; \
    if((elem_start = strstr(PARSE_TOKEN, LABEL_START.data))) { \
        elem_start += LABEL_START.slen; \
        if ((elem_end = strchr(elem_start, '>'))) { \
            elem_end[0x00] = '\0'; \
            if(!get_attval(ATTRIB_VALUE, elem_start, &ATTRIB_LABEL)) \
                PARSE_TOKEN = NULL; \
            elem_end[0x00] = '>'; \
        } else PARSE_TOKEN = NULL; \
    } else PARSE_TOKEN = NULL; \
}

#define GET_TATTRIB_VALUE(OATTRIB_VALUE, TATTRIB_VALUE, PARSE_TOKEN, LABEL_START, OATTRIB_LABEL, TATTRIB_LABEL) { \
    char *elem_end, *elem_start; \
    if((elem_start = strstr(PARSE_TOKEN, LABEL_START.data))) { \
        elem_start += LABEL_START.slen; \
        if ((elem_end = strchr(elem_start, '>'))) { \
            elem_end[0x00] = '\0'; \
            if(!get_attval2(OATTRIB_VALUE, TATTRIB_VALUE, elem_start, &OATTRIB_LABEL, &TATTRIB_LABEL)) \
                PARSE_TOKEN = NULL; \
            elem_end[0x00] = '>'; \
        } else PARSE_TOKEN = NULL; \
    } else PARSE_TOKEN = NULL; \
}

    //
#define GET_ATTRIB_ELEMENT_VALUE(ATTRIB_VALUE, ELEMENT_VALUE, PARSE_TOKEN, LABEL_START, ATTRIB_LABEL, LABEL_END) { \
    char *elem_end, *elem_start; \
    if((elem_start = strstr(PARSE_TOKEN, LABEL_START.data))) { \
        elem_start += LABEL_START.slen; \
        if ((elem_end = strchr(elem_start, '>'))) { \
            elem_end[0x00] = '\0'; \
            if(get_attval(ATTRIB_VALUE, elem_start, &ATTRIB_LABEL)) { \
                elem_end[0x00] = '>'; \
                elem_start = ++elem_end; \
                if ((elem_end = strstr(elem_start, LABEL_END.data))) { \
                    strzcpy(ELEMENT_VALUE, elem_start, elem_end - elem_start); \
                    PARSE_TOKEN = elem_end + LABEL_END.slen; \
                } else PARSE_TOKEN = NULL; \
            } else { PARSE_TOKEN = NULL; elem_end[0x00] = '>'; } \
        } else PARSE_TOKEN = NULL; \
    } else PARSE_TOKEN = NULL; \
}

#define GET_TATTRIB_ELEMENT_VALUE(OATTRIB_VALUE, TATTRIB_VALUE, ELEMENT_VALUE, PARSE_TOKEN, LABEL_START, OATTRIB_LABEL, TATTRIB_LABEL, LABEL_END) { \
    char *elem_end, *elem_start; \
    if((elem_start = strstr(PARSE_TOKEN, LABEL_START.data))) { \
        elem_start += LABEL_START.slen; \
        if ((elem_end = strchr(elem_start, '>'))) { \
            elem_end[0x00] = '\0'; \
            if(get_attval2(OATTRIB_VALUE, TATTRIB_VALUE, elem_start, &OATTRIB_LABEL, &TATTRIB_LABEL)) { \
                elem_end[0x00] = '>'; \
                elem_start = ++elem_end; \
                if ((elem_end = strstr(elem_start, LABEL_END.data))) { \
                    strzcpy(ELEMENT_VALUE, elem_start, elem_end - elem_start); \
                    PARSE_TOKEN = elem_end + LABEL_END.slen; \
                } else PARSE_TOKEN = NULL; \
            } else { PARSE_TOKEN = NULL; elem_end[0x00] = '>'; } \
        } else PARSE_TOKEN = NULL; \
    } else PARSE_TOKEN = NULL; \
}

    //
#define GET_HATTRIB_ELEMENT_VALUE(OATTRIB_VALUE, TATTRIB_VALUE, HATTRIB_VALUE, ELEMENT_VALUE, PARSE_TOKEN, LABEL_START, OATTRIB_LABEL, TATTRIB_LABEL, HATTRIB_LABEL, LABEL_END) { \
    char *elem_end, *elem_start; \
    if((elem_start = strstr(PARSE_TOKEN, LABEL_START.data))) { \
        elem_start += LABEL_START.slen; \
        if ((elem_end = strchr(elem_start, '>'))) { \
            elem_end[0x00] = '\0'; \
            if(get_attval3(OATTRIB_VALUE, TATTRIB_VALUE, HATTRIB_VALUE, elem_start, &OATTRIB_LABEL, &TATTRIB_LABEL, &HATTRIB_LABEL)) { \
                elem_end[0x00] = '>'; \
                elem_start = ++elem_end; \
                if ((elem_end = strstr(elem_start, LABEL_END.data))) { \
                    strzcpy(ELEMENT_VALUE, elem_start, elem_end - elem_start); \
                    PARSE_TOKEN = elem_end + LABEL_END.slen; \
                } else PARSE_TOKEN = NULL; \
            } else { PARSE_TOKEN = NULL; elem_end[0x00] = '>'; } \
        } else PARSE_TOKEN = NULL; \
    } else PARSE_TOKEN = NULL; \
}

    //
#define GET_FATTRIB_ELEMENT_VALUE(OATTRIB_VALUE, TATTRIB_VALUE, HATTRIB_VALUE, FATTRIB_VALUE, ELEMENT_VALUE, PARSE_TOKEN, LABEL_START, OATTRIB_LABEL, TATTRIB_LABEL, HATTRIB_LABEL, FATTRIB_LABEL, LABEL_END) { \
    char *elem_end, *elem_start; \
    if((elem_start = strstr(PARSE_TOKEN, LABEL_START.data))) { \
        elem_start += LABEL_START.slen; \
        if ((elem_end = strchr(elem_start, '>'))) { \
            elem_end[0x00] = '\0'; \
            if(get_attval4(OATTRIB_VALUE, TATTRIB_VALUE, HATTRIB_VALUE, FATTRIB_VALUE, elem_start, &OATTRIB_LABEL, &TATTRIB_LABEL, &HATTRIB_LABEL, &FATTRIB_LABEL)) { \
                elem_end[0x00] = '>'; \
                elem_start = ++elem_end; \
                if ((elem_end = strstr(elem_start, LABEL_END.data))) { \
                    strzcpy(ELEMENT_VALUE, elem_start, elem_end - elem_start); \
                    PARSE_TOKEN = elem_end + LABEL_END.slen; \
                } else PARSE_TOKEN = NULL; \
            } else { PARSE_TOKEN = NULL; elem_end[0x00] = '>'; } \
        } else PARSE_TOKEN = NULL; \
    } else PARSE_TOKEN = NULL; \
}


#ifdef __cplusplus
}
#endif

#endif /* XML_UTILI_H */


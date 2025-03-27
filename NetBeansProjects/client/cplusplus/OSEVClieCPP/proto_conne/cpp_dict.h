
/* 
 * File:   cpp_dict.h
 * Author: James Xu
 *
 * Created on 2024.4.22, PM 4:27
 */

#ifndef CPP_DICT_H
#define CPP_DICT_H

#ifdef __cplusplus
extern "C" {
#endif

    //
#define LAYOU_CVALU(VALUE, DICTI, KEY) { \
    struct stui_node *item = (struct stui_node *) DICTI; \
    for(; item->stkey; ++item) { \
        if(!strcmp(item->stkey, (char *) KEY.c_str())) \
            break; \
    } \
        VALUE = item->uival; \
}


#define PAMVS_CVALU(KEYVAL, DICTI) { \
    struct stst_node *item = (struct stst_node *) DICTI; \
    for(; item->stkey; ++item) { \
        if(!strcmp(item->stkey, (char *) KEYVAL.c_str())) \
            break; \
    } \
    ((string &)KEYVAL).assign(item->stval); \
}


#ifdef __cplusplus
}
#endif

#endif /* CPP_DICT_H */


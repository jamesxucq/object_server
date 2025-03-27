
/* 
 * File:   array_dict.h // array dictionary
 * Author: James Xu
 *
 * Created on 2024.4.22, AM 9:40
 */

#ifndef ARRAY_DICT_H
#define ARRAY_DICT_H

#ifdef __cplusplus
extern "C" {
#endif

    /////////////////////////////////////////////
    // trans-serve

    struct stst_node {
        const char *stkey;
        char *stval;
    };

    // trans-serve
#define KV_STST_EQUA(VALUE, DICTI, KEY) { \
    struct stst_node *item = (struct stst_node *) DICTI; \
    for(; item->stkey; ++item) { \
        if(!strcasecmp(KEY, item->stkey)) \
            break; \
    } \
    VALUE = item->stval; \
}

#define KV_STST_COPY(VALUE, DICTI, KEY) { \
    struct stst_node *item = (struct stst_node *) DICTI; \
    for(; item->stkey; ++item) { \
        if(!strcasecmp(KEY, item->stkey)) { \
            strcpy(VALUE, item->stval); \
            break; \
        } \
    } \
}

#define PAMVS_VALUE(KEY_VAL, DICTI) { \
    struct stst_node *item = (struct stst_node *) DICTI; \
    for(; item->stkey; ++item) { \
        if(!strcmp(item->stkey, KEY_VAL)) \
            break; \
    } \
    strcpy((char *) KEY_VAL, item->stval); \
}

#define PAMVS_WORTH(KEY_VAL, DICTI) { \
    struct stst_node *item = (struct stst_node *) DICTI; \
    for(; item->stkey; ++item) { \
        if(!strcmp(item->stkey, KEY_VAL)) { \
            strcpy((char *) KEY_VAL, item->stval); \
            break; \
        }\
    } \
}

    // 0x00:not found, 0x01:found

    inline int found_conve_value(char *key_valu, struct stst_node *dicti) {
        for (; dicti->stkey; ++dicti) {
            if (!strcmp(dicti->stkey, key_valu)) {
                strcpy(key_valu, dicti->stval);
                return 0x01;
            }
        }
        return 0x00;
    }

    inline int found_value(char *key_valu, struct stst_node *dicti) {
        for (; dicti->stkey; ++dicti) {
            if (!strcmp(dicti->stkey, key_valu))
                return 0x01;
        }
        return 0x00;
    }

    /////////////////////////////////////////////
    // trans-serve

    struct stch_node {
        const char *stkey;
        char chval;
    };

#define KV_STCH_EQUA(VALUE, DICTI, KEY) { \
    struct stch_node *item = (struct stch_node *) DICTI; \
    for(; item->stkey; ++item) { \
        if(!strcasecmp(KEY, item->stkey)) \
            break; \
    } \
    VALUE = item->chval; \
}

    // trans-serve
#define KV_STCH_LCPY(VALUE, DICTI, KEY) { \
    struct stch_node *item = (struct stch_node *) DICTI; \
    for(; item->stkey; ++item) { \
        if(!strcasecmp(KEY, item->stkey)) \
            break; \
    } \
    VALUE = lccpy(VALUE, item->chval); \
}

    /////////////////////////////////////////////
    // trans-serve

    struct stin_node {
        const char *stkey;
        int inval;
    };

    // trans-serve
#define KV_STIN_EQUA(VALUE, DICTI, KEY) { \
    struct stin_node *item = (struct stin_node *) DICTI; \
    for(; item->stkey; ++item) { \
        if(!strcmp(KEY, item->stkey)) \
            break; \
    } \
    VALUE = item->inval; \
}

    //

    /////////////////////////////////////////////
    // trans-serve
#define KV_STIN_OR(VALUE, DICTI, KEY) { \
    struct stin_node *item = (struct stin_node *) DICTI; \
    for(; item->stkey; ++item) { \
        if(!strcmp(KEY, item->stkey)) \
            break; \
    } \
    VALUE |= item->inval; \
}

    /////////////////////////////////////////////

    struct stsi_node {
        const char *stkey;
        char *stval;
        int inval;
    };

#define KVV_STSI_EQUA(VALU1, VALU2, DICTI, KEY) { \
    struct stsi_node *item = (struct stsi_node *) DICTI; \
    for(; item->text; ++item) { \
        if(!strcasecmp(KEY, item->stkey)) \
            break; \
    } \
    VALU1 = item->stval; \
    VALU2 = item->inval;\
}

    /////////////////////////////////////////////
    // trans-serve

    struct chin_node {
        const char chkey;
        int inval;
    };
    // trans-serve
#define KV_CHIN_EQUA(VALUE, DICTI, KEY) { \
    struct chin_node *item = (struct chin_node *) DICTI; \
    for(; '\0' != item->chkey; ++item) { \
        if(KEY == item->chkey) \
            break; \
    } \
    VALUE = item->inval; \
}

    /////////////////////////////////////////////

    struct stui_node {
        const char *stkey;
        unsigned int uival;
    };

#define KV_STUI_EQUA(VALUE, DICTI, KEY) { \
    struct stui_node *item = (struct stui_node *) DICTI; \
    for(; item->stkey; ++item) { \
        if(!strcasecmp(KEY, item->stkey)) \
            break; \
    } \
    VALUE = item->uival; \
}

#define PRIVI_DICTI_VALUE(VALUE, DICTI, KEY) { \
    struct stui_node *item = (struct stui_node *) DICTI; \
    for(; item->stkey; ++item) { \
        if(!strcmp(item->stkey, KEY)) \
            break; \
    } \
    VALUE |= item->uival; \
}

    /////////////////////////////////////////////    

    //

    struct ssii_node {
        const char *stkey1;
        const char *stkey2;
        int inval1;
        int inval2;
    };

#define KKVV_SSII_EQUA(VALU1, VALU2, DICTI, KEY1, KEY2) { \
    struct ssii_node *item = (struct ssii_node *) DICTI; \
    for(; item->stkey1 && item->stkey2; ++item) { \
        if(!strcasecmp(KEY1, item->stkey1) && !strcasecmp(KEY2, item->stkey2)) \
            break; \
    }\
    VALU1 = item->inval1; \
    VALU2 = item->inval2; \
}

#define NKVI_SSII_EQUA(VALU1, VALU2, DICTI, KEY1, KEY2) { \
    struct ssii_node *item = (struct ssii_node *) DICTI; \
    for(; item->stkey2; ++item) { \
        if(item->stkey1) { \
            if(!strcasecmp(KEY1, item->stkey1) && !strcasecmp(KEY2, item->stkey2)) \
                break; \
        } else { \
            if(!strcasecmp(KEY2, item->stkey2)) \
                break; \
        } \
    }\
    VALU1 = item->inval1; \
    VALU2 = item->inval2; \
}

    /////////////////////////////////////////////    

    struct ssin_node {
        const char *stkey1;
        const char *stkey2;
        int value;
    };

#define KKV_SSIN_EQUA(VALUE, DICTI, KEY1, KEY2) { \
    struct ssin_node *item = (struct ssin_node *) DICTI; \
    for(; item->stkey1 && item->stkey2; ++item) \
        if(!strcasecmp(KEY1, item->stkey1) && !strcasecmp(KEY2, item->stkey2)) break; \
    VALUE = item->value; \
}

#define KV_SSIN_EQUA(VALUE, DICTI, KEY) { \
    struct ssin_node *item = (struct ssin_node *) DICTI; \
    for(; item->stkey1 && item->stkey2; ++item) \
        if(!strcasecmp(item->stkey1, KEY) || !strcasecmp(item->stkey2, KEY)) break; \
    VALUE = item->value; \
}

    /////////////////////////////////////////////    

    struct uist_node {
        unsigned int uikey;
        char *stval;
    };

    typedef struct uist_node excmsg;

#define EXCEP_DICTI_VALUE(VALUE, DICTI, KEY) { \
    struct uist_node *item = (struct uist_node *) DICTI; \
    for(; item->uikey; ++item) \
        if(KEY == item->uikey) break; \
    VALUE = item->stval; \
}

    ///////////////////////////////////////////// 

#ifdef __cplusplus
}
#endif

#endif /* ARRAY_DICT_H */


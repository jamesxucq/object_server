
#include "commo_header.h"

#include "stora_utili.h"

//
#define KEY_FORMAT_KEYWD    "key_format"
#define KEY_FORMAT_LENG     0x0a
#define VALUE_FORMAT_KEYWD  "value_format"
#define VALUE_FORMAT_LENG   0x0c   

// forma_types:|key_format=R, value_format=fSdi, columns=(stoid,role_type,role_name,priv_array,index)|
// d/f => R/x

static inline char *conv_keywd_type(char *keywd_type, char *forma) {
    char *fmtok = forma;
    for (; fmtok[0x00] && (',' != fmtok[0x00]); ++fmtok, ++keywd_type) {
        switch (fmtok[0x00]) {
            case 'd':
                keywd_type[0x00] = 'R';
                break;
            case 'f':
                keywd_type[0x00] = '4';
                (++keywd_type)[0x00] = 's';
                break;
            default:
                keywd_type[0x00] = fmtok[0x00];
                break;
        }
    }
    keywd_type[0x00] = fmtok[0x00];
    if (fmtok[0x00]) {
        (++keywd_type)[0x00] = '\0';
        ++fmtok;
    }
    //
    return fmtok;
}

void conve_forma_style(char *forma) {
    char form_type[TYPES_LENGTH];
    char keywd_type[MAX_TLENG];
    strcpy(form_type, forma);
    //
    char *toksp = form_type;
    char *key_word = strstr(toksp, KEY_FORMAT_KEYWD);
    if (!key_word) return;
    key_word += KEY_FORMAT_LENG;
    forma = lszcpy(forma, toksp, key_word - toksp);
    toksp = conv_keywd_type(keywd_type, key_word);
    forma = lscpy(forma, keywd_type);
    //
    key_word = strstr(toksp, VALUE_FORMAT_KEYWD);
    if (!key_word) return;
    key_word += VALUE_FORMAT_LENG;
    forma = lszcpy(forma, toksp, key_word - toksp);
    toksp = conv_keywd_type(keywd_type, key_word);
    forma = lscpy(forma, keywd_type);
    //
    lscpy(forma, toksp);
}

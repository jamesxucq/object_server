#include <string.h>
#include "sstri_utili.h"

//

char *shap_lscpy(char * dest, const char * src) {
    if (!dest) return NULL;
    register char *d = dest;
    register const char *s = src;
    while ((*d = *s++)) d++;
    return d;
}
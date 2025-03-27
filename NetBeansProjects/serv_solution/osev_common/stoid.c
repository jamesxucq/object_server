#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "stoid.h"
#include "debug_funct_osv.h"

//

char *sidstr(char *stoid_stri, osv_sid_t *stoid) {
    char *toksp = stoid_stri;
    unsigned char *tokst = (unsigned char *) stoid;
    unsigned int inde = 0x00;
    for (; inde < STOR_IDENTI_BLEN; ++inde, ++tokst, ++toksp) {
        sprintf(toksp, "%02x", *tokst);
        ++toksp;
    }
    // stoid_stri[24] = '\0';
    return stoid_stri;
}

#include "debug_funct_osv.h"
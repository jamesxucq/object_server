
#include <string.h>
#include "astri_utili.h"

// "base:contain"

uint32 split_conta(char *basen, char *contn, char *base_conta) {
    char *cotok;
    if ((cotok = strchr(base_conta, ':'))) {
        cotok[0x00] = '\0';
        strcpy(basen, base_conta);
        strcpy(contn, ++cotok);
    } else return -1;
    //
    return 0x00;
}

//


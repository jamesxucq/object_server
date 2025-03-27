#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"

#include "instda.h"

void dele_instda(void *insai) {
    if (insai) {
        free(((instda *) insai)->lv2p_decl);
        free(insai);
    }
}



#include "commo_header.h"

#include "conatt.h"

void dele_conat(void *data) {
    if (data) free(data);
}
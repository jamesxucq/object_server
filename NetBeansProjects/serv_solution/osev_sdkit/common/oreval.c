
#include "commo_header.h"

#include "oreval.h"

//

int type_rvlen_tab[15] = {
    OBJE_IDENTI_BLEN,
    OBJE_IDENTI_BLEN + sizeof (char),
    OBJE_IDENTI_BLEN + sizeof (unsigned char),
    OBJE_IDENTI_BLEN + sizeof (short),
    OBJE_IDENTI_BLEN + sizeof (unsigned short),
    OBJE_IDENTI_BLEN + sizeof (int),
    OBJE_IDENTI_BLEN + sizeof (unsigned int),
    OBJE_IDENTI_BLEN + sizeof (long),
    OBJE_IDENTI_BLEN + sizeof (unsigned long),
    OBJE_IDENTI_BLEN + sizeof (long long),
    OBJE_IDENTI_BLEN + sizeof (unsigned long long),
    OBJE_IDENTI_BLEN + sizeof (float),
    OBJE_IDENTI_BLEN + sizeof (double),
    OBJE_IDENTI_BLEN + sizeof (char*),
    OBJE_IDENTI_BLEN + sizeof (char*)
};

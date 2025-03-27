
#include "InvoRType.h"

using namespace IRKeyVal;

//

char *RTypChar::Deseri(RTypChar *obje, char *deseConte) {
    OBID_BINARY_COPY(&obje->obje_obid, (osv_oid_t *) deseConte)
    deseConte += OBJE_IDENTI_BLEN;
    obje->ivalu = *((char *) deseConte);
    return sizeof (char) +deseConte;
}

char *RTypUchar::Deseri(RTypUchar *obje, char *deseConte) {
    OBID_BINARY_COPY(&obje->obje_obid, (osv_oid_t *) deseConte)
    deseConte += OBJE_IDENTI_BLEN;
    obje->ivalu = *((unsigned char *) deseConte);
    return sizeof (unsigned char) +deseConte;
}

char *RTypInt16::Deseri(RTypInt16 *obje, char *deseConte) {
    OBID_BINARY_COPY(&obje->obje_obid, (osv_oid_t *) deseConte)
    deseConte += OBJE_IDENTI_BLEN;
    obje->ivalu = *((short *) deseConte);
    return sizeof (short) +deseConte;
}

char *RTypUint16::Deseri(RTypUint16 *obje, char *deseConte) {
    OBID_BINARY_COPY(&obje->obje_obid, (osv_oid_t *) deseConte)
    deseConte += OBJE_IDENTI_BLEN;
    obje->ivalu = *((unsigned short *) deseConte);
    return sizeof (unsigned short) +deseConte;
}

char *RTypInt32::Deseri(RTypInt32 *obje, char *deseConte) {
    OBID_BINARY_COPY(&obje->obje_obid, (osv_oid_t *) deseConte)
    deseConte += OBJE_IDENTI_BLEN;
    obje->ivalu = *((int *) deseConte);
    return sizeof (int) +deseConte;
}

char *RTypUint32::Deseri(RTypUint32 *obje, char *deseConte) {
    OBID_BINARY_COPY(&obje->obje_obid, (osv_oid_t *) deseConte)
    deseConte += OBJE_IDENTI_BLEN;
    obje->ivalu = *((unsigned int *) deseConte);
    return sizeof (unsigned int) +deseConte;
}

char *RTypInt64::Deseri(RTypInt64 *obje, char *deseConte) {
    OBID_BINARY_COPY(&obje->obje_obid, (osv_oid_t *) deseConte)
    deseConte += OBJE_IDENTI_BLEN;
    obje->ivalu = *((long long *) deseConte);
    return sizeof (long long) +deseConte;
}

char *RTypUInt64::Deseri(RTypUInt64 *obje, char *deseConte) {
    OBID_BINARY_COPY(&obje->obje_obid, (osv_oid_t *) deseConte)
    deseConte += OBJE_IDENTI_BLEN;
    obje->ivalu = *((unsigned long long *) deseConte);
    return sizeof (unsigned long long) +deseConte;
}

char *RTypObid::Deseri(RTypObid *obje, char *deseConte) {
    OBID_BINARY_COPY(&obje->obje_obid, (osv_oid_t *) deseConte)
    deseConte += OBJE_IDENTI_BLEN;
    OBID_BINARY_COPY(&obje->ivalu, (osv_oid_t *) deseConte)
    return sizeof (osv_oid_t) + deseConte;
}

char *RTypFloat::Deseri(RTypFloat *obje, char *deseConte) {
    OBID_BINARY_COPY(&obje->obje_obid, (osv_oid_t *) deseConte)
    deseConte += OBJE_IDENTI_BLEN;
    obje->ivalu = *((float *) deseConte);
    return sizeof (float) +deseConte;
}

char *RTypDouble::Deseri(RTypDouble *obje, char *deseConte) {
    OBID_BINARY_COPY(&obje->obje_obid, (osv_oid_t *) deseConte)
    deseConte += OBJE_IDENTI_BLEN;
    obje->ivalu = *((double *) deseConte);
    return sizeof (double) +deseConte;
}

//

RTypStri::RTypStri(unsigned long long sleng) {
    this->sleng = sleng;
    this->ivalu = (char *) malloc(sleng);
}

RTypStri::~RTypStri() {
    free(this->ivalu);
}

char *RTypStri::Deseri(RTypStri *obje, char *deseConte) {
    OBID_BINARY_COPY(&obje->obje_obid, (osv_oid_t *) deseConte)
    deseConte += OBJE_IDENTI_BLEN;
    memcpy(obje->ivalu, deseConte, obje->sleng);
    return obje->sleng + deseConte;
}

char *RTypStrz::Deseri(RTypStrz *obje, char *deseConte) {
    OBID_BINARY_COPY(&obje->obje_obid, (osv_oid_t *) deseConte)
    deseConte += OBJE_IDENTI_BLEN;
    obje->ivalu.assign(deseConte);
    return 0x01 + obje->ivalu.size() + deseConte;
}


#include "utility/checksum.h"
#include "utility/last_stri.h"

#include "hash_table_ex.h"

//

unsigned int none_hash(const void *stri) {
    return 0x00;
}

int equal_md5(const void *k1, const void *k2) {
    return (0x00 == strncmp((char *) k1, (char *) k2, MD5_DIGEST_LEN));
}

//

/*
unsigned int lh_obid_hash(const void *obid) {
    if (NULL == obid) return (0x00);
    int size = sizeof (osv_oid_t) / 2;
    unsigned short *src = (unsigned short *) obid;

    unsigned long ret = 0x00;
    unsigned int inde = 0x00;
    for (; inde < size; ++inde)
        ret ^= src[inde] << (inde & 0x0f);
    //
    return (ret);
}
 */

unsigned int lh_stri_hash(const void *stri) {
    if (NULL == stri) return (0x00);
    int remain = (strlen(stri) + 0x01);
    int count = (remain >> 0x03) << 0x02;
    //
    unsigned short *src = (unsigned short *) stri;
    unsigned long retv = 0x00;
    unsigned int inde = 0x00;
    for (; count > inde; ++inde, ++src) {
        retv ^= src[0x00] << (inde & 0x0f);
        retv ^= *(++src) << (++inde & 0x0f);
        retv ^= *(++src) << (++inde & 0x0f);
        retv ^= *(++src) << (++inde & 0x0f);
    }
    if (((0x01 << 0x03) - 0x01) & remain) {
        remain >>= 0x01;
        for (; remain > inde; ++inde, ++src)
            retv ^= src[0x00] << (inde & 0x0f);
    }
    //
    return (retv);
}

int equal_stri(const void *k1, const void *k2) {
    return (0x00 == strcmp((char *) k1, (char *) k2));
}

//

unsigned int lh_obid_hash(const void *obid) {
    if (NULL == obid) return (0x00);

    unsigned short *src = (unsigned short *) obid;
    unsigned long retv = 0x00;
    unsigned int inde = 0x00;
    retv ^= src[0x00] << (inde & 0x0f);
    retv ^= *(++src) << (++inde & 0x0f);
    retv ^= *(++src) << (++inde & 0x0f);
    retv ^= *(++src) << (++inde & 0x0f);
    retv ^= *(++src) << (++inde & 0x0f);
    retv ^= *(++src) << (++inde & 0x0f);
    //
    return (retv);
}

int equal_obid(const void *k1, const void *k2) {
    return (((osv_oid_i *) k1)->stoid == ((osv_oid_i *) k2)->stoid \
            && ((osv_oid_i *) k1)->osev_unique == ((osv_oid_i *) k2)->osev_unique);
}

//

unsigned int lh_ooid_hash(const void *obid1, const void *obid2) {
    if (NULL == obid1 || NULL == obid2) return (0x00);
    //
    unsigned short *src = (unsigned short *) obid1;
    unsigned long retv = 0x00;
    unsigned int inde = 0x00;
    retv ^= src[0x00] << (inde & 0x0f);
    retv ^= *(++src) << (++inde & 0x0f);
    retv ^= *(++src) << (++inde & 0x0f);
    retv ^= *(++src) << (++inde & 0x0f);
    retv ^= *(++src) << (++inde & 0x0f);
    retv ^= *(++src) << (++inde & 0x0f);
    //
    src = (unsigned short *) obid2;
    inde = 0x00;
    retv ^= src[0x00] << (inde & 0x0f);
    retv ^= *(++src) << (++inde & 0x0f);
    retv ^= *(++src) << (++inde & 0x0f);
    retv ^= *(++src) << (++inde & 0x0f);
    retv ^= *(++src) << (++inde & 0x0f);
    retv ^= *(++src) << (++inde & 0x0f);
    //
    return (retv);
}

int equal_ooid(const void *k1, const void *k2, const void *k3, const void *k4) {
    return (((osv_oid_i *) k1)->stoid == ((osv_oid_i *) k2)->stoid \
            && ((osv_oid_i *) k1)->osev_unique == ((osv_oid_i *) k2)->osev_unique \
            && ((osv_oid_i *) k3)->stoid == ((osv_oid_i *) k4)->stoid \
            && ((osv_oid_i *) k3)->osev_unique == ((osv_oid_i *) k4)->osev_unique);
}
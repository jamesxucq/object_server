
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "refer_utili.h"

//

void init_dynami_robj(void *obje_memp, int refe_coun) {
    osv_oid_i *obje_obid = (osv_oid_i *) obje_memp;
    unsigned int inde = -1;
    for (; refe_coun > inde; ++inde, ++obje_obid) {
        FILL_UNIQUE_OBID((osv_oid_i *) obje_obid);
    }
}

static int dyna_unpack_zero(void *obje_memp, PK_ITEM *key, PK_ITEM *valu) {
    return 0x00;
}

static int dyna_unpack_sing(void *obje_memp, PK_ITEM *key, PK_ITEM *valu) {
    osv_oid_i *obje_obid = (osv_oid_i *) obje_memp;
    obje_obid->stoid = *((uint64*) key->data);
    ++obje_obid;
    obje_obid->stoid = *((uint64*) valu->data);
    //
    return 0x00;
}

static int dyna_unpack_coup(void *obje_memp, PK_ITEM *key, PK_ITEM *valu) {
    osv_oid_i *obje_obid = (osv_oid_i *) obje_memp;
    uint64 *obje_stoid = (uint64 *) valu->data;
    obje_obid->stoid = *((uint64*) key->data);
    ++obje_obid;
    obje_obid->stoid = obje_stoid[0x00];
    ++obje_obid, ++obje_stoid;
    obje_obid->stoid = obje_stoid[0x00];
    //
    return 0x00;
}

static int dyna_unpack_trip(void *obje_memp, PK_ITEM *key, PK_ITEM *valu) {
    osv_oid_i *obje_obid = (osv_oid_i *) obje_memp;
    uint64 *obje_stoid = (uint64 *) valu->data;
    obje_obid->stoid = *((uint64*) key->data);
    ++obje_obid;
    obje_obid->stoid = obje_stoid[0x00];
    ++obje_obid, ++obje_stoid;
    obje_obid->stoid = obje_stoid[0x00];
    ++obje_obid, ++obje_stoid;
    obje_obid->stoid = obje_stoid[0x00];
    //
    return 0x00;
}

static int dyna_unpack_quad(void *obje_memp, PK_ITEM *key, PK_ITEM *valu) {
    osv_oid_i *obje_obid = (osv_oid_i *) obje_memp;
    uint64 *obje_stoid = (uint64 *) valu->data;
    obje_obid->stoid = *((uint64*) key->data);
    ++obje_obid;
    obje_obid->stoid = obje_stoid[0x00];
    ++obje_obid, ++obje_stoid;
    obje_obid->stoid = obje_stoid[0x00];
    ++obje_obid, ++obje_stoid;
    obje_obid->stoid = obje_stoid[0x00];
    ++obje_obid, ++obje_stoid;
    obje_obid->stoid = obje_stoid[0x00];
    //
    return 0x00;
}

//
int (*dynami_unpack_tab[])(void *, PK_ITEM *, PK_ITEM *) = {
    dyna_unpack_zero,
    dyna_unpack_sing,
    dyna_unpack_coup,
    dyna_unpack_trip,
    dyna_unpack_quad
};

//

void init_static_robj(void *obje_memp, int refe_coun) {
    osv_oid_i *obje_obid = (osv_oid_i *) obje_memp;
    unsigned int inde = -1;
    for (; refe_coun > inde; ++inde, ++obje_obid) {
        FILL_UNIQUE_OBID((osv_oid_i *) obje_obid);
    }
}

static int stat_unpack_zero(void *obje_memp, PK_ITEM *key, PK_ITEM *valu) {
    return 0x00;
}

static int stat_unpack_sing(void *obje_memp, PK_ITEM *key, PK_ITEM *valu) {
    osv_oid_i *obje_obid = (osv_oid_i *) obje_memp;
    obje_obid->stoid = *((uint64*) key->data);
    ++obje_obid;
    obje_obid->stoid = *((uint64*) valu->data);
    //
    return 0x00;
}

static int stat_unpack_coup(void *obje_memp, PK_ITEM *key, PK_ITEM *valu) {
    osv_oid_i *obje_obid = (osv_oid_i *) obje_memp;
    uint64 *obje_stoid = (uint64 *) valu->data;
    obje_obid->stoid = *((uint64*) key->data);
    ++obje_obid;
    obje_obid->stoid = obje_stoid[0x00];
    ++obje_obid, ++obje_stoid;
    obje_obid->stoid = obje_stoid[0x00];
    //
    return 0x00;
}

static int stat_unpack_trip(void *obje_memp, PK_ITEM *key, PK_ITEM *valu) {
    osv_oid_i *obje_obid = (osv_oid_i *) obje_memp;
    uint64 *obje_stoid = (uint64 *) valu->data;
    obje_obid->stoid = *((uint64*) key->data);
    ++obje_obid;
    obje_obid->stoid = obje_stoid[0x00];
    ++obje_obid, ++obje_stoid;
    obje_obid->stoid = obje_stoid[0x00];
    ++obje_obid, ++obje_stoid;
    obje_obid->stoid = obje_stoid[0x00];
    //
    return 0x00;
}

static int stat_unpack_quad(void *obje_memp, PK_ITEM *key, PK_ITEM *valu) {
    osv_oid_i *obje_obid = (osv_oid_i *) obje_memp;
    uint64 *obje_stoid = (uint64 *) valu->data;
    obje_obid->stoid = *((uint64*) key->data);
    ++obje_obid;
    obje_obid->stoid = obje_stoid[0x00];
    ++obje_obid, ++obje_stoid;
    obje_obid->stoid = obje_stoid[0x00];
    ++obje_obid, ++obje_stoid;
    obje_obid->stoid = obje_stoid[0x00];
    ++obje_obid, ++obje_stoid;
    obje_obid->stoid = obje_stoid[0x00];
    //
    return 0x00;
}

//
int (*static_unpack_tab[])(void *, PK_ITEM *, PK_ITEM *) = {
    stat_unpack_zero,
    stat_unpack_sing,
    stat_unpack_coup,
    stat_unpack_trip,
    stat_unpack_quad
};


#include "file_utili.h"
#include "debug_funct_osv.h"

//

void p_test_object(struct test *obje) {
    char obid_stri[25];
    oidstr(obid_stri, (osv_oid_t *) & obje->obje_obid);
    printf("|%s|%d|%d|%d|\n", obid_stri, obje->xx, obje->ax, obje->cx);
}

//

void p_osv_oid_t_stri(osv_oid_t *obje_obid) {
    fprintf(stdout, "------- p_osv_oid_t\n");
    char obid_stri[OBJE_IDENTI_ZLEN];
    oidstr(obid_stri, obje_obid);
    fprintf(stdout, "|%s|\n", obid_stri);
}

void p_osv_oid_t_08X(osv_oid_t *obje_obid) {
    printf("obid_stri:|%08x%08x%08x|\n"
            , ((osv_oid_t *) obje_obid)->osev_unique
            , ((osv_oid_t *) obje_obid)->time_stamp
            , ((osv_oid_t *) obje_obid)->counter);
}

void p_osv_oid_t_sid_stri(osv_oid_t *obje_obid, int size) {
    char stoid_stri[STOR_IDENTI_ZLEN];
    sidstr(stoid_stri, (osv_sid_t *)&((osv_oid_i *) obje_obid)->stoid);
    printf("|%s| size:%d counter:%u\n", stoid_stri, size, obje_obid->counter);
}

void p_osv_sid_t_stri(osv_sid_t *obje_stoid) {
    char stoid_stri[STOR_IDENTI_ZLEN];
    sidstr(stoid_stri, obje_stoid);
    printf("stoid:|%s| counter:%u\n", stoid_stri, obje_stoid->counter);
}

//

void p_stoid_stri(osv_sid_t *sid, int size) {
    char stoid_stri[STOR_IDENTI_ZLEN];
    sidstr(stoid_stri, sid);
    printf("|%s| size:%d counter:%u\n", stoid_stri, size, sid->counter);
}

// for debut

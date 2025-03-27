
#include "commo_header.h"
#include "kcomm_header.h"
#include "cqutili.h"
#include "../stora_handl.h"
#include "../conte_resou.h"

#include "data_compa.h"

// not equal

int data_text_noteq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, char *stri_valu) {
    OSEVPF("[FUNC]:data_text_noteq\n");
    OSEVPF("stri_valu:|%s|\n", stri_valu);
    PK_ITEM key, valu;
    const char *strval;
    osv_oid_i obje_obid;
    FILL_UNIQUE_OBID(&obje_obid);
    //
    while (!stora_ha->next_curso(lidcur)) {
        stora_ha->get_value(lidcur, &valu);
        if (paki_iunpak_stri(&valu, &strval))
            return -1;
        if (strcmp(stri_valu, strval)) {
            stora_ha->get_key(lidcur, &key);
            obje_obid.stoid = *(uint64 *) key.data;
            if (0x00 >= APPEND_DATAS(resul, &obje_obid, sizeof (osv_oid_i)))
                return -1;
        }
    }
    //
    return 0x00;
}

//

int data_lolo_noteq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, long long lolo_valu) {
    OSEVPF("[FUNC]:data_lolo_noteq\n");
    OSEVPF("lolo_valu:|%lld|\n", lolo_valu);
    PK_ITEM key, valu;
    long long llival;
    osv_oid_i obje_obid;
    FILL_UNIQUE_OBID(&obje_obid);
    //
    while (!stora_ha->next_curso(lidcur)) {
        stora_ha->get_value(lidcur, &valu);
        if (paki_iunpak_int64(&valu, (long int *) &llival))
            return -1;
        // OSEVPF("value:%d\n", llival);
        if (llival != lolo_valu) {
            stora_ha->get_key(lidcur, &key);
            obje_obid.stoid = *(uint64 *) key.data;
            // p_stoid_stri(&(obje_obid.stoid), sizeof (unsigned long long));
            if (0x00 >= APPEND_DATAS(resul, &obje_obid, sizeof (osv_oid_i)))
                return -1;
        }
    }
    //
    return 0x00;
}

int data_ullo_noteq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, unsigned long long ullo_valu) {
    OSEVPF("[FUNC]:data_ullo_noteq\n");
    OSEVPF("ullo_valu:|%llu|\n", ullo_valu);
    PK_ITEM key, valu;
    unsigned long long ullval;
    osv_oid_i obje_obid;
    FILL_UNIQUE_OBID(&obje_obid);
    //
    while (!stora_ha->next_curso(lidcur)) {
        stora_ha->get_value(lidcur, &valu);
        if (paki_iunpak_uint64(&valu, (long unsigned int *) &ullval))
            return -1;
        // OSEVPF("value:%d\n", llival);
        if (ullval != ullo_valu) {
            stora_ha->get_key(lidcur, &key);
            obje_obid.stoid = *(uint64 *) key.data;
            if (0x00 >= APPEND_DATAS(resul, &obje_obid, sizeof (osv_oid_i)))
                return -1;
        }
    }
    //
    return 0x00;
}

int data_doub_noteq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, double doub_valu) {
    OSEVPF("[FUNC]:data_doub_noteq\n");
    OSEVPF("doub_valu:|%f|\n", doub_valu);
    PK_ITEM key, valu;
    double douval;
    osv_oid_i obje_obid;
    FILL_UNIQUE_OBID(&obje_obid);
    //
    while (!stora_ha->next_curso(lidcur)) {
        stora_ha->get_value(lidcur, &valu);
        if (paki_iunpak_double(&valu, &douval))
            return -1;
        // OSEVPF("value:%d\n", dvalu);
        if (douval != doub_valu) {
            stora_ha->get_key(lidcur, &key);
            obje_obid.stoid = *(uint64 *) key.data;
            if (0x00 >= APPEND_DATAS(resul, &obje_obid, sizeof (osv_oid_i)))
                return -1;
        }
    }
    //
    return 0x00;
}

// equal

int data_text_equal(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, char *stri_valu) {
    OSEVPF("[FUNC]:data_text_equal\n");
    OSEVPF("stri_valu:|%s|\n", stri_valu);
    PK_ITEM key, valu;
    const char *strval;
    osv_oid_i obje_obid;
    FILL_UNIQUE_OBID(&obje_obid);
    //
    while (!stora_ha->next_curso(lidcur)) {
        stora_ha->get_value(lidcur, &valu);
        if (paki_iunpak_stri(&valu, &strval))
            return -1;
        if (!strcmp(stri_valu, strval)) {
            stora_ha->get_key(lidcur, &key);
            obje_obid.stoid = *(uint64 *) key.data;
            if (0x00 >= APPEND_DATAS(resul, &obje_obid, sizeof (osv_oid_i)))
                return -1;
        }
    }
    //
    return 0x00;
}

//

int data_lolo_equal(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, long long lolo_valu) {
    OSEVPF("[FUNC]:data_lolo_equal\n");
    OSEVPF("lolo_valu:|%lld|\n", lolo_valu);
    PK_ITEM key, valu;
    long long llival;
    osv_oid_i obje_obid;
    FILL_UNIQUE_OBID(&obje_obid);
    //
    while (!stora_ha->next_curso(lidcur)) {
        stora_ha->get_value(lidcur, &valu);
        if (paki_iunpak_int64(&valu, (long int *) &llival))
            return -1;
        OSEVPF("llival:%lld\n", llival);
        if (llival == lolo_valu) {
            stora_ha->get_key(lidcur, &key);
            obje_obid.stoid = *(uint64 *) key.data;
            if (0x00 >= APPEND_DATAS(resul, &obje_obid, sizeof (osv_oid_i)))
                return -1;
        }
    }
    //
    return 0x00;
}

int data_ullo_equal(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, unsigned long long ullo_valu) {
    OSEVPF("[FUNC]:data_lolo_equal\n");
    OSEVPF("ullo_valu:|%llu|\n", ullo_valu);
    PK_ITEM key, valu;
    unsigned long long ullval;
    osv_oid_i obje_obid;
    FILL_UNIQUE_OBID(&obje_obid);
    //
    while (!stora_ha->next_curso(lidcur)) {
        stora_ha->get_value(lidcur, &valu);
        if (paki_iunpak_uint64(&valu, (long unsigned int *) &ullval))
            return -1;
        // OSEVPF("value:%d\n", llival);
        if (ullval == ullo_valu) {
            stora_ha->get_key(lidcur, &key);
            obje_obid.stoid = *(uint64 *) key.data;
            if (0x00 >= APPEND_DATAS(resul, &obje_obid, sizeof (osv_oid_i)))
                return -1;
        }
    }
    //
    return 0x00;
}
//

int data_doub_equal(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, double doub_valu) {
    OSEVPF("[FUNC]:data_doub_equal\n");
    OSEVPF("doub_valu:|%f|\n", doub_valu);
    PK_ITEM key, valu;
    double douval;
    osv_oid_i obje_obid;
    FILL_UNIQUE_OBID(&obje_obid);
    //
    while (!stora_ha->next_curso(lidcur)) {
        stora_ha->get_value(lidcur, &valu);
        if (paki_iunpak_double(&valu, &douval))
            return -1;
        // OSEVPF("value:%d\n", dvalu);
        if (douval == doub_valu) {
            stora_ha->get_key(lidcur, &key);
            obje_obid.stoid = *(uint64 *) key.data;
            if (0x00 >= APPEND_DATAS(resul, &obje_obid, sizeof (osv_oid_i)))
                return -1;
        }
    }
    //
    return 0x00;
}

int data_rid_equal(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, char *rid_valu) {
    OSEVPF("[FUNC]:data_rid_equal\n");
    //
    return 0x00;
}

// great

int data_text_great(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, char *stri_valu) {
    OSEVPF("[FUNC]:data_text_great\n");
    OSEVPF("stri_valu:|%s|\n", stri_valu);
    PK_ITEM key, valu;
    const char *strval;
    osv_oid_i obje_obid;
    FILL_UNIQUE_OBID(&obje_obid);
    //
    while (!stora_ha->next_curso(lidcur)) {
        stora_ha->get_value(lidcur, &valu);
        if (paki_iunpak_stri(&valu, &strval))
            return -1;
        if (0x00 > strcmp(stri_valu, strval)) {
            stora_ha->get_key(lidcur, &key);
            obje_obid.stoid = *(uint64 *) key.data;
            if (0x00 >= APPEND_DATAS(resul, &obje_obid, sizeof (osv_oid_i)))
                return -1;
        }
    }
    //
    return 0x00;
}

int data_lolo_great(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, long long lolo_valu) {
    OSEVPF("[FUNC]:data_lolo_great\n");
    OSEVPF("lolo_valu:%lld\n", lolo_valu);
    PK_ITEM key, valu;
    long long llival;
    osv_oid_i obje_obid;
    FILL_UNIQUE_OBID(&obje_obid);
    //
    // OSEVPF("osev_unique:|%08x|\n", obje_obid.stoidosev_unique);
    while (!stora_ha->next_curso(lidcur)) {
        stora_ha->get_value(lidcur, &valu);
        if (paki_iunpak_int64(&valu, (long int *) &llival))
            return -1;
        // OSEVPF("value:%d\n", llival);
        if (llival > lolo_valu) {
            stora_ha->get_key(lidcur, &key);
            obje_obid.stoid = *(uint64 *) key.data;
            if (0x00 >= APPEND_DATAS(resul, &obje_obid, sizeof (osv_oid_i)))
                return -1;
        }
    }
    //
    return 0x00;
}

int data_ullo_great(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, unsigned long long ullo_valu) {
    OSEVPF("[FUNC]:data_lolo_great\n");
    OSEVPF("lolo_valu:%llu\n", ullo_valu);
    PK_ITEM key, valu;
    unsigned long long ullval;
    osv_oid_i obje_obid;
    FILL_UNIQUE_OBID(&obje_obid);
    //
    // OSEVPF("osev_unique:|%08x|\n", obje_obid.stoidosev_unique);
    while (!stora_ha->next_curso(lidcur)) {
        stora_ha->get_value(lidcur, &valu);
        if (paki_iunpak_uint64(&valu, (long unsigned int *) &ullval))
            return -1;
        // OSEVPF("value:%d\n", llival);
        if (ullval > ullo_valu) {
            stora_ha->get_key(lidcur, &key);
            obje_obid.stoid = *(uint64 *) key.data;
            if (0x00 >= APPEND_DATAS(resul, &obje_obid, sizeof (osv_oid_i)))
                return -1;
        }
    }
    //
    return 0x00;
}

int data_doub_great(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, double doub_valu) {
    OSEVPF("[FUNC]:data_doub_great\n");
    OSEVPF("doub_valu:|%f|\n", doub_valu);
    PK_ITEM key, valu;
    double douval;
    osv_oid_i obje_obid;
    FILL_UNIQUE_OBID(&obje_obid);
    //
    while (!stora_ha->next_curso(lidcur)) {
        stora_ha->get_value(lidcur, &valu);
        if (paki_iunpak_double(&valu, &douval))
            return -1;
        // OSEVPF("value:%d\n", dvalu);
        if (douval > doub_valu) {
            stora_ha->get_key(lidcur, &key);
            obje_obid.stoid = *(uint64 *) key.data;
            if (0x00 >= APPEND_DATAS(resul, &obje_obid, sizeof (osv_oid_i)))
                return -1;
        }
    }
    //
    return 0x00;
}

// less equal

int data_text_leseq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, char *stri_valu) {
    OSEVPF("[FUNC]:data_text_leseq\n");
    OSEVPF("stri_valu:|%s|\n", stri_valu);
    PK_ITEM key, valu;
    const char *strval;
    osv_oid_i obje_obid;
    FILL_UNIQUE_OBID(&obje_obid);
    //
    while (!stora_ha->next_curso(lidcur)) {
        stora_ha->get_value(lidcur, &valu);
        if (paki_iunpak_stri(&valu, &strval))
            return -1;
        if (0x00 <= strcmp(stri_valu, strval)) {
            stora_ha->get_key(lidcur, &key);
            obje_obid.stoid = *(uint64 *) key.data;
            if (0x00 >= APPEND_DATAS(resul, &obje_obid, sizeof (osv_oid_i)))
                return -1;
        }
    }
    //
    return 0x00;
}

int data_lolo_leseq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, long long lolo_valu) {
    OSEVPF("[FUNC]:data_lolo_leseq\n");
    OSEVPF("lolo_valu:|%lld|\n", lolo_valu);
    PK_ITEM key, valu;
    long long llival;
    osv_oid_i obje_obid;
    FILL_UNIQUE_OBID(&obje_obid);
    //
    while (!stora_ha->next_curso(lidcur)) {
        stora_ha->get_value(lidcur, &valu);
        if (paki_iunpak_int64(&valu, (long int *) &llival))
            return -1;
        // OSEVPF("value:%d\n", llival);
        if (llival <= lolo_valu) {
            stora_ha->get_key(lidcur, &key);
            obje_obid.stoid = *(uint64 *) key.data;
            if (0x00 >= APPEND_DATAS(resul, &obje_obid, sizeof (osv_oid_i)))
                return -1;
        }
    }
    //
    return 0x00;
}

int data_ullo_leseq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, unsigned long long ullo_valu) {
    OSEVPF("[FUNC]:data_lolo_leseq\n");
    OSEVPF("ullo_valu:|%llu|\n", ullo_valu);
    PK_ITEM key, valu;
    unsigned long long ullval;
    osv_oid_i obje_obid;
    FILL_UNIQUE_OBID(&obje_obid);
    //
    while (!stora_ha->next_curso(lidcur)) {
        stora_ha->get_value(lidcur, &valu);
        if (paki_iunpak_uint64(&valu, (long unsigned int *) &ullval))
            return -1;
        // OSEVPF("value:%d\n", llival);
        if (ullval <= ullo_valu) {
            stora_ha->get_key(lidcur, &key);
            obje_obid.stoid = *(uint64 *) key.data;
            if (0x00 >= APPEND_DATAS(resul, &obje_obid, sizeof (osv_oid_i)))
                return -1;
        }
    }
    //
    return 0x00;
}

int data_doub_leseq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, double doub_valu) {
    OSEVPF("[FUNC]:data_doub_leseq\n");
    OSEVPF("doub_valu:|%f|\n", doub_valu);
    PK_ITEM key, valu;
    double douval;
    osv_oid_i obje_obid;
    FILL_UNIQUE_OBID(&obje_obid);
    //
    while (!stora_ha->next_curso(lidcur)) {
        stora_ha->get_value(lidcur, &valu);
        if (paki_iunpak_double(&valu, &douval))
            return -1;
        // OSEVPF("value:%d\n", dvalu);
        if (douval <= doub_valu) {
            stora_ha->get_key(lidcur, &key);
            obje_obid.stoid = *(uint64 *) key.data;
            if (0x00 >= APPEND_DATAS(resul, &obje_obid, sizeof (osv_oid_i)))
                return -1;
        }
    }
    //
    return 0x00;
}


// less

int data_text_less(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, char *stri_valu) {
    OSEVPF("[FUNC]:data_text_less\n");
    OSEVPF("stri_valu:|%s|\n", stri_valu);
    PK_ITEM key, valu;
    const char *strval;
    osv_oid_i obje_obid;
    FILL_UNIQUE_OBID(&obje_obid);
    //
    while (!stora_ha->next_curso(lidcur)) {
        stora_ha->get_value(lidcur, &valu);
        if (paki_iunpak_stri(&valu, &strval))
            return -1;
        if (0x00 < strcmp(stri_valu, strval)) {
            stora_ha->get_key(lidcur, &key);
            obje_obid.stoid = *(uint64 *) key.data;
            if (0x00 >= APPEND_DATAS(resul, &obje_obid, sizeof (osv_oid_i)))
                return -1;
        }
    }
    //
    return 0x00;
}

int data_lolo_less(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, long long lolo_valu) {
    OSEVPF("[FUNC]:data_lolo_less\n");
    OSEVPF("lolo_valu:|%lld|\n", lolo_valu);
    PK_ITEM key, valu;
    long long llival;
    osv_oid_i obje_obid;
    FILL_UNIQUE_OBID(&obje_obid);
    //
    while (!stora_ha->next_curso(lidcur)) {
        stora_ha->get_value(lidcur, &valu);
        if (paki_iunpak_int64(&valu, (long int *) &llival))
            return -1;
        // OSEVPF("value:%d\n", llival);
        if (llival < lolo_valu) {
            stora_ha->get_key(lidcur, &key);
            obje_obid.stoid = *(uint64 *) key.data;
            if (0x00 >= APPEND_DATAS(resul, &obje_obid, sizeof (osv_oid_i)))
                return -1;
        }
    }
    //
    return 0x00;
}

int data_ullo_less(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, unsigned long long ullo_valu) {
    OSEVPF("[FUNC]:data_lolo_less, ullo_valu:|%llu|\n", ullo_valu);
    OSEVPF("ullo_valu:|%llu|\n", ullo_valu);
    PK_ITEM key, valu;
    unsigned long long ullval;
    osv_oid_i obje_obid;
    FILL_UNIQUE_OBID(&obje_obid);
    //
    while (!stora_ha->next_curso(lidcur)) {
        stora_ha->get_value(lidcur, &valu);
        if (paki_iunpak_uint64(&valu, (long unsigned int *) &ullval))
            return -1;
        // OSEVPF("value:%d\n", llival);
        if (ullval < ullo_valu) {
            stora_ha->get_key(lidcur, &key);
            obje_obid.stoid = *(uint64 *) key.data;
            if (0x00 >= APPEND_DATAS(resul, &obje_obid, sizeof (osv_oid_i)))
                return -1;
        }
    }
    //
    return 0x00;
}

int data_doub_less(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, double doub_valu) {
    OSEVPF("[FUNC]:data_doub_less\n");
    OSEVPF("doub_valu:|%f|\n", doub_valu);
    PK_ITEM key, valu;
    double douval;
    osv_oid_i obje_obid;
    FILL_UNIQUE_OBID(&obje_obid);
    //
    while (!stora_ha->next_curso(lidcur)) {
        stora_ha->get_value(lidcur, &valu);
        if (paki_iunpak_double(&valu, &douval))
            return -1;
        // OSEVPF("value:%d\n", dvalu);
        if (douval < doub_valu) {
            stora_ha->get_key(lidcur, &key);
            obje_obid.stoid = *(uint64 *) key.data;
            if (0x00 >= APPEND_DATAS(resul, &obje_obid, sizeof (osv_oid_i)))
                return -1;
        }
    }
    //
    return 0x00;
}

//

int data_text_greeq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, char *stri_valu) {
    OSEVPF("[FUNC]:data_text_greeq\n");
    OSEVPF("stri_valu:|%s|\n", stri_valu);
    PK_ITEM key, valu;
    const char *strval;
    osv_oid_i obje_obid;
    FILL_UNIQUE_OBID(&obje_obid);
    //
    while (!stora_ha->next_curso(lidcur)) {
        stora_ha->get_value(lidcur, &valu);
        if (paki_iunpak_stri(&valu, &strval))
            return -1;
        if (0x00 >= strcmp(stri_valu, strval)) {
            stora_ha->get_key(lidcur, &key);
            obje_obid.stoid = *(uint64 *) key.data;
            if (0x00 >= APPEND_DATAS(resul, &obje_obid, sizeof (osv_oid_i)))
                return -1;
        }
    }
    //
    return 0x00;
}

int data_lolo_greeq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, long long lolo_valu) {
    OSEVPF("[FUNC]:data_lolo_greeq\n");
    OSEVPF("lolo_valu:|%lld|\n", lolo_valu);
    PK_ITEM key, valu;
    long long llival;
    osv_oid_i obje_obid;
    FILL_UNIQUE_OBID(&obje_obid);
    //
    while (!stora_ha->next_curso(lidcur)) {
        stora_ha->get_value(lidcur, &valu);
        if (paki_iunpak_int64(&valu, (long int *) &llival))
            return -1;
        // OSEVPF("value:%d\n", llival);
        if (llival >= lolo_valu) {
            stora_ha->get_key(lidcur, &key);
            obje_obid.stoid = *(uint64 *) key.data;
            if (0x00 >= APPEND_DATAS(resul, &obje_obid, sizeof (osv_oid_i)))
                return -1;
        }
    }
    //
    return 0x00;
}

int data_ullo_greeq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, unsigned long long ullo_valu) {
    OSEVPF("[FUNC]:data_lolo_greeq\n");
    OSEVPF("ullo_valu:|%llu|\n", ullo_valu);
    PK_ITEM key, valu;
    unsigned long long ullval;
    osv_oid_i obje_obid;
    FILL_UNIQUE_OBID(&obje_obid);
    //
    while (!stora_ha->next_curso(lidcur)) {
        stora_ha->get_value(lidcur, &valu);
        if (paki_iunpak_uint64(&valu, (long unsigned int *) &ullval))
            return -1;
        // OSEVPF("value:%d\n", llival);
        if (ullval >= ullo_valu) {
            stora_ha->get_key(lidcur, &key);
            obje_obid.stoid = *(uint64 *) key.data;
            if (0x00 >= APPEND_DATAS(resul, &obje_obid, sizeof (osv_oid_i)))
                return -1;
        }
    }
    //
    return 0x00;
}

int data_doub_greeq(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, double doub_valu) {
    OSEVPF("[FUNC]:data_doub_greeq\n");
    OSEVPF("doub_valu:|%f|\n", doub_valu);
    PK_ITEM key, valu;
    double douval;
    osv_oid_i obje_obid;
    FILL_UNIQUE_OBID(&obje_obid);
    //
    while (!stora_ha->next_curso(lidcur)) {
        stora_ha->get_value(lidcur, &valu);
        if (paki_iunpak_double(&valu, &douval))
            return -1;
        // OSEVPF("value:%d\n", dvalu);
        if (douval >= doub_valu) {
            stora_ha->get_key(lidcur, &key);
            obje_obid.stoid = *(uint64 *) key.data;
            if (0x00 >= APPEND_DATAS(resul, &obje_obid, sizeof (osv_oid_i)))
                return -1;
        }
    }
    //
    return 0x00;
}

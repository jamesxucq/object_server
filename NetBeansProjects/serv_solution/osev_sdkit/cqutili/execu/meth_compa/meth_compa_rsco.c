
#include "commo_header.h"
#include "kcomm_header.h"
#include "cqutili.h"
#include "../stora_handl.h"
#include "../conte_resou.h"

#include "meth_compa_rsco.h"


// rsco
// not equal

int meth_text_noteq_rsco(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, char *stri_valu) {
    OSEVPF("[FUNC]:meth_text_noteq\n");
    valu_memo_t obje_memo;
    if (!valu_malloc(&obje_memo, lv1me->lv2me))
        return -1;
    FILL_UNIQUE_OBID((osv_oid_t *) obje_memo.data);
    //
    oreval rvalu;
    PK_ITEM key, valu;
    while (0x00 == stora_ha->next_curso(lidcur)) {
        stora_ha->get_key(lidcur, &key);
        stora_ha->get_value(lidcur, &valu);
        if (bound_objec_data(&obje_memo, (uint64 *) key.data, &valu, lv1me->lv2me)) {
            free_valu(&obje_memo);
            return -1;
        }
        lv1me->method.invoke(&rvalu, obje_memo.data, parm_oivk);
        if (strcmp(stri_valu, rvalu.reval.rchap)) {
            if (0x00 >= APPEND_DATAS(resul, (char *) obje_memo.data, sizeof (osv_oid_i))) {
                free_valu(&obje_memo);
                return -1;
            }
        }
    }
    //
    free_valu(&obje_memo);
    return 0x00;
}

int meth_lolo_noteq_rsco(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, long long lolo_valu) {
    OSEVPF("[FUNC]:meth_lolo_noteq\n");
    valu_memo_t obje_memo;
    if (!valu_malloc(&obje_memo, lv1me->lv2me))
        return -1;
    FILL_UNIQUE_OBID((osv_oid_t *) obje_memo.data);
    //
    oreval rvalu;
    PK_ITEM key, valu;
    while (0x00 == stora_ha->next_curso(lidcur)) {
        stora_ha->get_key(lidcur, &key);
        stora_ha->get_value(lidcur, &valu);
        if (bound_objec_data(&obje_memo, (uint64 *) key.data, &valu, lv1me->lv2me)) {
            free_valu(&obje_memo);
            return -1;
        }
        lv1me->method.invoke(&rvalu, obje_memo.data, parm_oivk);
        if (lolo_valu != rvalu.reval.rllong) {
            if (0x00 >= APPEND_DATAS(resul, (char *) obje_memo.data, sizeof (osv_oid_i))) {
                free_valu(&obje_memo);
                return -1;
            }
        }
    }
    //
    free_valu(&obje_memo);
    return 0x00;
}

int meth_ullo_noteq_rsco(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, unsigned long long ullo_valu) {
    OSEVPF("[FUNC]:meth_lolo_noteq\n");
    valu_memo_t obje_memo;
    if (!valu_malloc(&obje_memo, lv1me->lv2me))
        return -1;
    FILL_UNIQUE_OBID((osv_oid_t *) obje_memo.data);
    //
    oreval rvalu;
    PK_ITEM key, valu;
    while (0x00 == stora_ha->next_curso(lidcur)) {
        stora_ha->get_key(lidcur, &key);
        stora_ha->get_value(lidcur, &valu);
        if (bound_objec_data(&obje_memo, (uint64 *) key.data, &valu, lv1me->lv2me)) {
            free_valu(&obje_memo);
            return -1;
        }
        lv1me->method.invoke(&rvalu, obje_memo.data, parm_oivk);
        if (ullo_valu != rvalu.reval.rullon) {
            if (0x00 >= APPEND_DATAS(resul, (char *) obje_memo.data, sizeof (osv_oid_i))) {
                free_valu(&obje_memo);
                return -1;
            }
        }
    }
    //
    free_valu(&obje_memo);
    return 0x00;
}

int meth_doub_noteq_rsco(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, double doub_valu) {
    OSEVPF("[FUNC]:meth_doub_noteq\n");
    valu_memo_t obje_memo;
    if (!valu_malloc(&obje_memo, lv1me->lv2me))
        return -1;
    FILL_UNIQUE_OBID((osv_oid_t *) obje_memo.data);
    //
    oreval rvalu;
    PK_ITEM key, valu;
    while (0x00 == stora_ha->next_curso(lidcur)) {
        stora_ha->get_key(lidcur, &key);
        stora_ha->get_value(lidcur, &valu);
        if (bound_objec_data(&obje_memo, (uint64 *) key.data, &valu, lv1me->lv2me)) {
            free_valu(&obje_memo);
            return -1;
        }
        lv1me->method.invoke(&rvalu, obje_memo.data, parm_oivk);
        if (doub_valu != rvalu.reval.rdoub) {
            if (0x00 >= APPEND_DATAS(resul, (char *) obje_memo.data, sizeof (osv_oid_i))) {
                free_valu(&obje_memo);
                return -1;
            }
        }
    }
    //
    free_valu(&obje_memo);
    return 0x00;
}

// equal

int meth_text_equal_rsco(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, char *stri_valu) {
    OSEVPF("[FUNC]:meth_text_equal\n");
    valu_memo_t obje_memo;
    if (!valu_malloc(&obje_memo, lv1me->lv2me))
        return -1;
    FILL_UNIQUE_OBID((osv_oid_t *) obje_memo.data);
    //
    oreval rvalu;
    PK_ITEM key, valu;
    while (0x00 == stora_ha->next_curso(lidcur)) {
        stora_ha->get_key(lidcur, &key);
        stora_ha->get_value(lidcur, &valu);
        if (bound_objec_data(&obje_memo, (uint64 *) key.data, &valu, lv1me->lv2me)) {
            free_valu(&obje_memo);
            return -1;
        }
        lv1me->method.invoke(&rvalu, obje_memo.data, parm_oivk);
        if (!strcmp(stri_valu, rvalu.reval.rchap)) {
            if (0x00 >= APPEND_DATAS(resul, (char *) obje_memo.data, sizeof (osv_oid_i))) {
                free_valu(&obje_memo);
                return -1;
            }
        }
    }
    //
    free_valu(&obje_memo);
    return 0x00;
}

//

int meth_lolo_equal_rsco(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, long long lolo_valu) {
    OSEVPF("[FUNC]:meth_lolo_equal\n");
    valu_memo_t obje_memo;
    if (!valu_malloc(&obje_memo, lv1me->lv2me))
        return -1;
    FILL_UNIQUE_OBID((osv_oid_t *) obje_memo.data);
    //
    oreval rvalu;
    PK_ITEM key, valu;
    while (0x00 == stora_ha->next_curso(lidcur)) {
        stora_ha->get_key(lidcur, &key);
        stora_ha->get_value(lidcur, &valu);
        if (bound_objec_data(&obje_memo, (uint64 *) key.data, &valu, lv1me->lv2me)) {
            free_valu(&obje_memo);
            return -1;
        }
        lv1me->method.invoke(&rvalu, obje_memo.data, parm_oivk);
        if (lolo_valu == rvalu.reval.rllong) {
            if (0x00 >= APPEND_DATAS(resul, (char *) obje_memo.data, sizeof (osv_oid_i))) {
                free_valu(&obje_memo);
                return -1;
            }
        }
    }
    //
    free_valu(&obje_memo);
    return 0x00;
}

int meth_ullo_equal_rsco(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, unsigned long long ullo_valu) {
    OSEVPF("[FUNC]:meth_lolo_equal\n");
    valu_memo_t obje_memo;
    if (!valu_malloc(&obje_memo, lv1me->lv2me))
        return -1;
    FILL_UNIQUE_OBID((osv_oid_t *) obje_memo.data);
    //
    oreval rvalu;
    PK_ITEM key, valu;
    while (0x00 == stora_ha->next_curso(lidcur)) {
        stora_ha->get_key(lidcur, &key);
        stora_ha->get_value(lidcur, &valu);
        if (bound_objec_data(&obje_memo, (uint64 *) key.data, &valu, lv1me->lv2me)) {
            free_valu(&obje_memo);
            return -1;
        }
        lv1me->method.invoke(&rvalu, obje_memo.data, parm_oivk);
        if (ullo_valu == rvalu.reval.rullon) {
            if (0x00 >= APPEND_DATAS(resul, (char *) obje_memo.data, sizeof (osv_oid_i))) {
                free_valu(&obje_memo);
                return -1;
            }
        }
    }
    //
    free_valu(&obje_memo);
    return 0x00;
}
//

int meth_doub_equal_rsco(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, double doub_valu) {
    OSEVPF("[FUNC]:meth_doub_equal\n");
    valu_memo_t obje_memo;
    if (!valu_malloc(&obje_memo, lv1me->lv2me))
        return -1;
    FILL_UNIQUE_OBID((osv_oid_t *) obje_memo.data);
    //
    oreval rvalu;
    PK_ITEM key, valu;
    while (0x00 == stora_ha->next_curso(lidcur)) {
        stora_ha->get_key(lidcur, &key);
        stora_ha->get_value(lidcur, &valu);
        if (bound_objec_data(&obje_memo, (uint64 *) key.data, &valu, lv1me->lv2me)) {
            free_valu(&obje_memo);
            return -1;
        }
        lv1me->method.invoke(&rvalu, obje_memo.data, parm_oivk);
        if (doub_valu == rvalu.reval.rdoub) {
            if (0x00 >= APPEND_DATAS(resul, (char *) obje_memo.data, sizeof (osv_oid_i))) {
                free_valu(&obje_memo);
                return -1;
            }
        }
    }
    //
    free_valu(&obje_memo);
    return 0x00;
}

int meth_rid_equal_rsco(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, char *rid_valu) {
    OSEVPF("[FUNC]:meth_rid_equal\n");

    //
    return 0x00;
}

// great

int meth_text_great_rsco(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, char *stri_valu) {
    OSEVPF("[FUNC]:meth_text_great\n");
    valu_memo_t obje_memo;
    if (!valu_malloc(&obje_memo, lv1me->lv2me))
        return -1;
    FILL_UNIQUE_OBID((osv_oid_t *) obje_memo.data);
    //
    oreval rvalu;
    PK_ITEM key, valu;
    while (0x00 == stora_ha->next_curso(lidcur)) {
        stora_ha->get_key(lidcur, &key);
        stora_ha->get_value(lidcur, &valu);
        if (bound_objec_data(&obje_memo, (uint64 *) key.data, &valu, lv1me->lv2me)) {
            free_valu(&obje_memo);
            return -1;
        }
        lv1me->method.invoke(&rvalu, obje_memo.data, parm_oivk);
        if (0x00 > strcmp(stri_valu, rvalu.reval.rchap)) {
            if (0x00 >= APPEND_DATAS(resul, (char *) obje_memo.data, sizeof (osv_oid_i))) {
                free_valu(&obje_memo);
                return -1;
            }
        }
    }
    //
    free_valu(&obje_memo);
    return 0x00;
}

int meth_lolo_great_rsco(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, long long lolo_valu) {
    OSEVPF("[FUNC]:meth_lolo_great, lolo_valu:%lld\n", lolo_valu);
    valu_memo_t obje_memo;
    if (!valu_malloc(&obje_memo, lv1me->lv2me))
        return -1;
    FILL_UNIQUE_OBID((osv_oid_t *) obje_memo.data);
    //
    oreval rvalu;
    PK_ITEM key, valu;
    while (0x00 == stora_ha->next_curso(lidcur)) {
        stora_ha->get_key(lidcur, &key);
        stora_ha->get_value(lidcur, &valu);
        if (bound_objec_data(&obje_memo, (uint64 *) key.data, &valu, lv1me->lv2me)) {
            free_valu(&obje_memo);
            return -1;
        }
        lv1me->method.invoke(&rvalu, obje_memo.data, parm_oivk);
        if (lolo_valu < rvalu.reval.rllong) {
            if (0x00 >= APPEND_DATAS(resul, (char *) obje_memo.data, sizeof (osv_oid_i))) {
                free_valu(&obje_memo);
                return -1;
            }
        }
    }
    //
    free_valu(&obje_memo);
    return 0x00;
}

int meth_ullo_great_rsco(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, unsigned long long ullo_valu) {
    OSEVPF("[FUNC]:meth_lolo_great, lolo_valu:%llu\n", ullo_valu);
    valu_memo_t obje_memo;
    if (!valu_malloc(&obje_memo, lv1me->lv2me))
        return -1;
    FILL_UNIQUE_OBID((osv_oid_t *) obje_memo.data);
    //
    oreval rvalu;
    PK_ITEM key, valu;
    while (0x00 == stora_ha->next_curso(lidcur)) {
        stora_ha->get_key(lidcur, &key);
        stora_ha->get_value(lidcur, &valu);
        if (bound_objec_data(&obje_memo, (uint64 *) key.data, &valu, lv1me->lv2me)) {
            free_valu(&obje_memo);
            return -1;
        }
        lv1me->method.invoke(&rvalu, obje_memo.data, parm_oivk);
        if (ullo_valu < rvalu.reval.rullon) {
            if (0x00 >= APPEND_DATAS(resul, (char *) obje_memo.data, sizeof (osv_oid_i))) {
                free_valu(&obje_memo);
                return -1;
            }
        }
    }
    //
    free_valu(&obje_memo);
    return 0x00;
}

int meth_doub_great_rsco(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, double doub_valu) {
    OSEVPF("[FUNC]:meth_doub_great\n");
    valu_memo_t obje_memo;
    if (!valu_malloc(&obje_memo, lv1me->lv2me))
        return -1;
    FILL_UNIQUE_OBID((osv_oid_t *) obje_memo.data);
    //
    oreval rvalu;
    PK_ITEM key, valu;
    while (0x00 == stora_ha->next_curso(lidcur)) {
        stora_ha->get_key(lidcur, &key);
        stora_ha->get_value(lidcur, &valu);
        if (bound_objec_data(&obje_memo, (uint64 *) key.data, &valu, lv1me->lv2me)) {
            free_valu(&obje_memo);
            return -1;
        }
        lv1me->method.invoke(&rvalu, obje_memo.data, parm_oivk);
        if (doub_valu < rvalu.reval.rdoub) {
            if (0x00 >= APPEND_DATAS(resul, (char *) obje_memo.data, sizeof (osv_oid_i))) {
                free_valu(&obje_memo);
                return -1;
            }
        }
    }
    //
    free_valu(&obje_memo);
    return 0x00;
}

// less equal

int meth_text_leseq_rsco(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, char *stri_valu) {
    OSEVPF("[FUNC]:meth_text_leseq\n");
    valu_memo_t obje_memo;
    if (!valu_malloc(&obje_memo, lv1me->lv2me))
        return -1;
    FILL_UNIQUE_OBID((osv_oid_t *) obje_memo.data);
    //
    oreval rvalu;
    PK_ITEM key, valu;
    while (0x00 == stora_ha->next_curso(lidcur)) {
        stora_ha->get_key(lidcur, &key);
        stora_ha->get_value(lidcur, &valu);
        if (bound_objec_data(&obje_memo, (uint64 *) key.data, &valu, lv1me->lv2me)) {
            free_valu(&obje_memo);
            return -1;
        }
        lv1me->method.invoke(&rvalu, obje_memo.data, parm_oivk);
        if (0x00 <= strcmp(stri_valu, rvalu.reval.rchap)) {
            if (0x00 >= APPEND_DATAS(resul, (char *) obje_memo.data, sizeof (osv_oid_i))) {
                free_valu(&obje_memo);
                return -1;
            }
        }
    }
    //
    free_valu(&obje_memo);
    return 0x00;
}

int meth_lolo_leseq_rsco(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, long long lolo_valu) {
    OSEVPF("[FUNC]:meth_lolo_leseq\n");
    valu_memo_t obje_memo;
    if (!valu_malloc(&obje_memo, lv1me->lv2me))
        return -1;
    FILL_UNIQUE_OBID((osv_oid_t *) obje_memo.data);
    //
    oreval rvalu;
    PK_ITEM key, valu;
    while (0x00 == stora_ha->next_curso(lidcur)) {
        stora_ha->get_key(lidcur, &key);
        stora_ha->get_value(lidcur, &valu);
        if (bound_objec_data(&obje_memo, (uint64 *) key.data, &valu, lv1me->lv2me)) {
            free_valu(&obje_memo);
            return -1;
        }
        lv1me->method.invoke(&rvalu, obje_memo.data, parm_oivk);
        if (lolo_valu >= rvalu.reval.rllong) {
            if (0x00 >= APPEND_DATAS(resul, (char *) obje_memo.data, sizeof (osv_oid_i))) {
                free_valu(&obje_memo);
                return -1;
            }
        }
    }
    //
    free_valu(&obje_memo);
    return 0x00;
}

int meth_ullo_leseq_rsco(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, unsigned long long ullo_valu) {
    OSEVPF("[FUNC]:meth_lolo_leseq\n");
    valu_memo_t obje_memo;
    if (!valu_malloc(&obje_memo, lv1me->lv2me))
        return -1;
    FILL_UNIQUE_OBID((osv_oid_t *) obje_memo.data);
    //
    oreval rvalu;
    PK_ITEM key, valu;
    while (0x00 == stora_ha->next_curso(lidcur)) {
        stora_ha->get_key(lidcur, &key);
        stora_ha->get_value(lidcur, &valu);
        if (bound_objec_data(&obje_memo, (uint64 *) key.data, &valu, lv1me->lv2me)) {
            free_valu(&obje_memo);
            return -1;
        }
        lv1me->method.invoke(&rvalu, obje_memo.data, parm_oivk);
        if (ullo_valu >= rvalu.reval.rullon) {
            if (0x00 >= APPEND_DATAS(resul, (char *) obje_memo.data, sizeof (osv_oid_i))) {
                free_valu(&obje_memo);
                return -1;
            }
        }
    }
    //
    free_valu(&obje_memo);
    return 0x00;
}

int meth_doub_leseq_rsco(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, double doub_valu) {
    OSEVPF("[FUNC]:meth_doub_leseq\n");
    valu_memo_t obje_memo;
    if (!valu_malloc(&obje_memo, lv1me->lv2me))
        return -1;
    FILL_UNIQUE_OBID((osv_oid_t *) obje_memo.data);
    //
    oreval rvalu;
    PK_ITEM key, valu;
    while (0x00 == stora_ha->next_curso(lidcur)) {
        stora_ha->get_key(lidcur, &key);
        stora_ha->get_value(lidcur, &valu);
        if (bound_objec_data(&obje_memo, (uint64 *) key.data, &valu, lv1me->lv2me)) {
            free_valu(&obje_memo);
            return -1;
        }
        lv1me->method.invoke(&rvalu, obje_memo.data, parm_oivk);
        if (doub_valu >= rvalu.reval.rdoub) {
            if (0x00 >= APPEND_DATAS(resul, (char *) obje_memo.data, sizeof (osv_oid_i))) {
                free_valu(&obje_memo);
                return -1;
            }
        }
    }
    //
    free_valu(&obje_memo);
    return 0x00;
}


// less

int meth_text_less_rsco(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, char *stri_valu) {
    OSEVPF("[FUNC]:meth_text_less\n");
    valu_memo_t obje_memo;
    if (!valu_malloc(&obje_memo, lv1me->lv2me))
        return -1;
    FILL_UNIQUE_OBID((osv_oid_t *) obje_memo.data);
    //
    oreval rvalu;
    PK_ITEM key, valu;
    while (0x00 == stora_ha->next_curso(lidcur)) {
        stora_ha->get_key(lidcur, &key);
        stora_ha->get_value(lidcur, &valu);
        if (bound_objec_data(&obje_memo, (uint64 *) key.data, &valu, lv1me->lv2me)) {
            free_valu(&obje_memo);
            return -1;
        }
        lv1me->method.invoke(&rvalu, obje_memo.data, parm_oivk);
        if (0x00 < strcmp(stri_valu, rvalu.reval.rchap)) {
            if (0x00 >= APPEND_DATAS(resul, (char *) obje_memo.data, sizeof (osv_oid_i))) {
                free_valu(&obje_memo);
                return -1;
            }
        }
    }
    //
    free_valu(&obje_memo);
    return 0x00;
}

int meth_lolo_less_rsco(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, long long lolo_valu) {
    OSEVPF("[FUNC]:meth_lolo_less\n");
    valu_memo_t obje_memo;
    if (!valu_malloc(&obje_memo, lv1me->lv2me))
        return -1;
    FILL_UNIQUE_OBID((osv_oid_t *) obje_memo.data);
    //
    oreval rvalu;
    PK_ITEM key, valu;
    while (0x00 == stora_ha->next_curso(lidcur)) {
        stora_ha->get_key(lidcur, &key);
        stora_ha->get_value(lidcur, &valu);
        if (bound_objec_data(&obje_memo, (uint64 *) key.data, &valu, lv1me->lv2me)) {
            free_valu(&obje_memo);
            return -1;
        }
        lv1me->method.invoke(&rvalu, obje_memo.data, parm_oivk);
        if (lolo_valu > rvalu.reval.rllong) {
            if (0x00 >= APPEND_DATAS(resul, (char *) obje_memo.data, sizeof (osv_oid_i))) {
                free_valu(&obje_memo);
                return -1;
            }
        }
    }
    //
    free_valu(&obje_memo);
    return 0x00;
}

int meth_ullo_less_rsco(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, unsigned long long ullo_valu) {
    OSEVPF("[FUNC]:meth_lolo_less\n");
    valu_memo_t obje_memo;
    if (!valu_malloc(&obje_memo, lv1me->lv2me))
        return -1;
    FILL_UNIQUE_OBID((osv_oid_t *) obje_memo.data);
    //
    oreval rvalu;
    PK_ITEM key, valu;
    while (0x00 == stora_ha->next_curso(lidcur)) {
        stora_ha->get_key(lidcur, &key);
        stora_ha->get_value(lidcur, &valu);
        if (bound_objec_data(&obje_memo, (uint64 *) key.data, &valu, lv1me->lv2me)) {
            free_valu(&obje_memo);
            return -1;
        }
        lv1me->method.invoke(&rvalu, obje_memo.data, parm_oivk);
        if (ullo_valu > rvalu.reval.rullon) {
            if (0x00 >= APPEND_DATAS(resul, (char *) obje_memo.data, sizeof (osv_oid_i))) {
                free_valu(&obje_memo);
                return -1;
            }
        }
    }
    //
    free_valu(&obje_memo);
    return 0x00;
}

int meth_doub_less_rsco(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, double doub_valu) {
    OSEVPF("[FUNC]:meth_doub_less\n");
    valu_memo_t obje_memo;
    if (!valu_malloc(&obje_memo, lv1me->lv2me))
        return -1;
    FILL_UNIQUE_OBID((osv_oid_t *) obje_memo.data);
    //
    oreval rvalu;
    PK_ITEM key, valu;
    while (0x00 == stora_ha->next_curso(lidcur)) {
        stora_ha->get_key(lidcur, &key);
        stora_ha->get_value(lidcur, &valu);
        if (bound_objec_data(&obje_memo, (uint64 *) key.data, &valu, lv1me->lv2me)) {
            free_valu(&obje_memo);
            return -1;
        }
        lv1me->method.invoke(&rvalu, obje_memo.data, parm_oivk);
        if (doub_valu > rvalu.reval.rdoub) {
            if (0x00 >= APPEND_DATAS(resul, (char *) obje_memo.data, sizeof (osv_oid_i))) {
                free_valu(&obje_memo);
                return -1;
            }
        }
    }
    //
    free_valu(&obje_memo);
    return 0x00;
}

//

int meth_text_greeq_rsco(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, char *stri_valu) {
    OSEVPF("[FUNC]:meth_text_greeq\n");
    valu_memo_t obje_memo;
    if (!valu_malloc(&obje_memo, lv1me->lv2me))
        return -1;
    FILL_UNIQUE_OBID((osv_oid_t *) obje_memo.data);
    //
    oreval rvalu;
    PK_ITEM key, valu;
    while (0x00 == stora_ha->next_curso(lidcur)) {
        stora_ha->get_key(lidcur, &key);
        stora_ha->get_value(lidcur, &valu);
        if (bound_objec_data(&obje_memo, (uint64 *) key.data, &valu, lv1me->lv2me)) {
            free_valu(&obje_memo);
            return -1;
        }
        lv1me->method.invoke(&rvalu, obje_memo.data, parm_oivk);
        if (0x00 >= strcmp(stri_valu, rvalu.reval.rchap)) {
            if (0x00 >= APPEND_DATAS(resul, (char *) obje_memo.data, sizeof (osv_oid_i))) {
                free_valu(&obje_memo);
                return -1;
            }
        }
    }
    //
    free_valu(&obje_memo);
    return 0x00;
}

//

int meth_lolo_greeq_rsco(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, long long lolo_valu) {
    OSEVPF("[FUNC]:meth_lolo_greeq\n");
    valu_memo_t obje_memo;
    if (!valu_malloc(&obje_memo, lv1me->lv2me))
        return -1;
    FILL_UNIQUE_OBID((osv_oid_t *) obje_memo.data);
    //
    oreval rvalu;
    PK_ITEM key, valu;
    while (0x00 == stora_ha->next_curso(lidcur)) {
        stora_ha->get_key(lidcur, &key);
        stora_ha->get_value(lidcur, &valu);
        if (bound_objec_data(&obje_memo, (uint64 *) key.data, &valu, lv1me->lv2me)) {
            free_valu(&obje_memo);
            return -1;
        }
        lv1me->method.invoke(&rvalu, obje_memo.data, parm_oivk);
        if (lolo_valu <= rvalu.reval.rllong) {
            if (0x00 >= APPEND_DATAS(resul, (char *) obje_memo.data, sizeof (osv_oid_i))) {
                free_valu(&obje_memo);
                return -1;
            }
        }
    }
    //
    free_valu(&obje_memo);
    return 0x00;
}

int meth_ullo_greeq_rsco(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, unsigned long long ullo_valu) {
    OSEVPF("[FUNC]:meth_lolo_greeq\n");
    valu_memo_t obje_memo;
    if (!valu_malloc(&obje_memo, lv1me->lv2me))
        return -1;
    FILL_UNIQUE_OBID((osv_oid_t *) obje_memo.data);
    //
    oreval rvalu;
    PK_ITEM key, valu;
    while (0x00 == stora_ha->next_curso(lidcur)) {
        stora_ha->get_key(lidcur, &key);
        stora_ha->get_value(lidcur, &valu);
        if (bound_objec_data(&obje_memo, (uint64 *) key.data, &valu, lv1me->lv2me)) {
            free_valu(&obje_memo);
            return -1;
        }
        lv1me->method.invoke(&rvalu, obje_memo.data, parm_oivk);
        if (ullo_valu <= rvalu.reval.rullon) {
            if (0x00 >= APPEND_DATAS(resul, (char *) obje_memo.data, sizeof (osv_oid_i))) {
                free_valu(&obje_memo);
                return -1;
            }
        }
    }
    //
    free_valu(&obje_memo);
    return 0x00;
}

int meth_doub_greeq_rsco(FILE *resul, riv_curso_t *lidcur, rive_ha *stora_ha, lev1me *lv1me, char *parm_oivk, double doub_valu) {
    OSEVPF("[FUNC]:meth_doub_greeq\n");
    valu_memo_t obje_memo;
    if (!valu_malloc(&obje_memo, lv1me->lv2me))
        return -1;
    FILL_UNIQUE_OBID((osv_oid_t *) obje_memo.data);
    //
    oreval rvalu;
    PK_ITEM key, valu;
    while (0x00 == stora_ha->next_curso(lidcur)) {
        stora_ha->get_key(lidcur, &key);
        stora_ha->get_value(lidcur, &valu);
        if (bound_objec_data(&obje_memo, (uint64 *) key.data, &valu, lv1me->lv2me)) {
            free_valu(&obje_memo);
            return -1;
        }
        lv1me->method.invoke(&rvalu, obje_memo.data, parm_oivk);
        if (doub_valu <= rvalu.reval.rdoub) {
            if (0x00 >= APPEND_DATAS(resul, (char *) obje_memo.data, sizeof (osv_oid_i))) {
                free_valu(&obje_memo);
                return -1;
            }
        }
    }
    //
    free_valu(&obje_memo);
    return 0x00;
}



#include "commo_header.h"
#include "kcomm_header.h"

#include "rive_bzl.h"

#include "conattr.h"
#include "debug_funct/debug_funct_ca.h"

//

#ifndef INVA_INDE_VALU
#define INVA_INDE_VALU      ((unsigned int) - 1)
#endif

//

#define INIT_CONTA_ATTR(canod) \
        memset(&canod, '\0', sizeof(cont_atti_i)); \
        canod.sibling = INVA_INDE_VALU;

//

static FILE *crea_catti(char *basen) {
    char file_name[MAX_PATH * 3];
    CREAT_CONTAIN_FILE(file_name, basen, CONTA_CONTE_DATA)
    //
    FILE *attrp = fopen64(file_name, "wb+");
    if (!attrp) {
        _LOG_ERROR("creat file error! %s errno:%d", file_name, errno);
        return NULL;
    }
    //
    return attrp;
}

static FILE *open_catti(char *basen) {
    char file_name[MAX_PATH * 3];
    CREAT_CONTAIN_FILE(file_name, basen, CONTA_CONTE_DATA)
    //
    FILE *attrp = fopen64(file_name, "rb+");
    if (!attrp) {
        _LOG_ERROR("open file error! %s errno:%d", file_name, errno);
        return NULL;
    }
    //
    return attrp;
}
#define CLOSE_CATTRI(ATTRP) fclose(ATTRP)

//

static int fill_head(FILE *attrp) {
    cont_atti_i canod;
    INIT_CONTA_ATTR(canod)
    if (fseeko64(attrp, 0x00, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fwrite(&canod, sizeof (cont_atti_i), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

//

static int fill_idle(FILE *attrp) {
    cont_atti_i canod;
    INIT_CONTA_ATTR(canod)
    if (fseeko64(attrp, 0x00, SEEK_END)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fwrite(&canod, sizeof (cont_atti_i), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

static int read_atti(cont_atti_i *canod, FILE *attrp, unsigned int reind) {
    if (INVA_INDE_VALU == reind)
        return -1;
    if (fseeko64(attrp, (__off64_t) reind * sizeof (cont_atti_i), SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fread(canod, sizeof (cont_atti_i), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    // OSEVPF("end read_atti\n");
    return 0x00;
}
//

static int modi_sibli(unsigned int sibli, FILE *attrp, unsigned int moind) {
    // OSEVPF("[FUNC]:modi_sibli moind:&d\n", moind);
    __off64_t eose = (__off64_t) moind * sizeof (cont_atti_i);
    //
    cont_atti_i canod;
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fread(&canod, sizeof (cont_atti_i), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    canod.sibling = sibli;
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fwrite(&canod, sizeof (cont_atti_i), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    // OSEVPF("end modi_sibli\n");
    return 0x00;
}

#define MODI_RECYCL(RECYCL, ATTRP, AINDE) modi_sibli(RECYCL, ATTRP, AINDE)

//

static int activ_atti(unsigned int acind, FILE *attrp) {
    cont_atti_i canod;
    if (fseeko64(attrp, 0x00, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fread(&canod, sizeof (cont_atti_i), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    if (modi_sibli(canod.sibling, attrp, acind))
        return -1;
    //
    canod.sibling = acind;
    if (fseeko64(attrp, 0x00, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fwrite(&canod, sizeof (cont_atti_i), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

//

static int updat_atti(osv_oid_t *lv4p_obid, char *contn, osv_oid_t *lv2p_type, uint32 stora_type, FILE *attrp, unsigned int upind) {
    __off64_t eose = (__off64_t) upind * sizeof (cont_atti_i);
    //
    cont_atti_i canod;
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fread(&canod, sizeof (cont_atti_i), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    STOID_OBID_COPY(canod.cont_stoid, lv4p_obid)
    strcpy(canod.cont_name, contn);
    canod.contype = ENTIT_CONTA_NORMAL;
    STOID_OBID_COPY(canod.lv2p_type, lv2p_type);
    // canod.refe_coun = ENTITY_CONTAI_COUNT;
    // memset(canod.refe_cont, '\0', RCONT_CONUT_ZTAI * sizeof (osv_sid_i));
    // MK_ZERO(canod.condition);
    canod.stora_type = stora_type;
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fwrite(&canod, sizeof (cont_atti_i), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

//

static inline int updat_rsatti(osv_oid_t *lv4p_obid, char *contn, osv_oid_t *lv2p_type, uint32 refe_coun, uint32 stora_type, FILE *attrp, unsigned int upind) {
    __off64_t eose = (__off64_t) upind * sizeof (cont_atti_i);
    //
    cont_atti_i canod;
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fread(&canod, sizeof (cont_atti_i), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    STOID_OBID_COPY(canod.cont_stoid, lv4p_obid)
    strcpy(canod.cont_name, contn);
    canod.contype = REFER_CONTA_STATIC;
    STOID_OBID_COPY(canod.lv2p_type, lv2p_type);
    canod.refe_coun = refe_coun;
    memset(canod.refe_cont, '\0', RCONT_CONUT_ZTAI * sizeof (osv_sid_i));
    // MK_ZERO(canod.condition);
    canod.stora_type = stora_type;
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fwrite(&canod, sizeof (cont_atti_i), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

//

static inline int updat_rdatti(osv_oid_t *lv4p_obid, char *contn, osv_oid_t *lv2p_type, uint32 refe_coun, osv_oid_t *refe_cont, uint32 conditype, char *condition, uint32 stora_type, FILE *attrp, unsigned int upind) {
    // OSEVPF("[FUNC]:updat_rdatti\n");
    __off64_t eose = (__off64_t) upind * sizeof (cont_atti_i);
    //
    cont_atti_i canod;
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fread(&canod, sizeof (cont_atti_i), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    STOID_OBID_COPY(canod.cont_stoid, lv4p_obid)
    strcpy(canod.cont_name, contn);
    canod.contype = REFER_CONTA_DYNAMI;
    STOID_OBID_COPY(canod.lv2p_type, lv2p_type);
    canod.refe_coun = refe_coun;
    // memcpy(canod.refe_cont, refe_cont, refe_coun * sizeof (osv_oid_t));
    osv_sid_i *des_ref = canod.refe_cont;
    unsigned int inde = 0x00;
    for (; refe_coun > inde; ++inde, ++des_ref, ++refe_cont)
        STOID_OBID_COPY(des_ref[0x00], refe_cont);
    canod.conditype = conditype;
    if (CONDI_TYPE_OBJID == conditype) {
        osv_oid_t *enti_obid = (osv_oid_t *) condition;
        des_ref = (osv_sid_i *) canod.condition;
        for (inde = 0x00; refe_coun > inde; ++inde, ++des_ref, ++enti_obid)
            STOID_OBID_COPY(des_ref[0x00], enti_obid);
    } else strcpy(canod.condition, condition);
    canod.stora_type = stora_type;
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fwrite(&canod, sizeof (cont_atti_i), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

//

static int updat_rscont(cont_versi *rcove, FILE *attrp, unsigned int upind) {
    __off64_t eose = (__off64_t) upind * sizeof (cont_atti_i);
    //
    cont_atti_i canod;
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fread(&canod, sizeof (cont_atti_i), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    // memcpy(&(canod.refe_cont), refe_cont, RCONT_CONUT_ZTAI * sizeof (osv_oid_t));
    osv_sid_i *des_ref = canod.refe_cont;
    unsigned int inde = 0x00;
    for (; (MAX_RSCON_COUNT > inde) && CHK_ZERO_COVE(rcove); ++inde, ++des_ref, ++rcove) {
        OSEVPF("inde:%d\n", inde);
        STOID_OBID_COPY(des_ref[0x00], &(rcove->lv4p_obid));
    }
    MAKE_ZERO_STOID(des_ref);
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fwrite(&canod, sizeof (cont_atti_i), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

//

static unsigned int get_blank_atti(FILE *attrp) {
    cont_atti_i ianod;
    if (fseeko64(attrp, -(__off64_t)sizeof (cont_atti_i), SEEK_END)) {
        _LOG_ERROR("seek file error!");
        return INVA_INDE_VALU;
    }
    __off64_t eose = ftello64(attrp);
    if (0x00 >= fread(&ianod, sizeof (cont_atti_i), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return INVA_INDE_VALU;
    }
    // OSEVPF("ianod.recycle:%x\n", ianod.recycle);
    unsigned int binde = INVA_INDE_VALU;
    if (INVA_INDE_VALU == ianod.recycle) {
        binde = eose / sizeof (cont_atti_i);
        // OSEVPF("get_blank_attr binde:%x\n", binde);
        activ_atti(binde, attrp);
        fill_idle(attrp);
    } else {
        binde = ianod.recycle;
        cont_atti_i canod;
        if (read_atti(&canod, attrp, binde))
            return INVA_INDE_VALU;
        ianod.recycle = canod.recycle;
        activ_atti(binde, attrp);
        if (fseeko64(attrp, eose, SEEK_SET)) {
            _LOG_ERROR("seek file error!");
            return INVA_INDE_VALU;
        }
        if (0x00 >= fwrite(&ianod, sizeof (cont_atti_i), 0x01, attrp)) {
            _LOG_ERROR("fwrite file error!");
            return INVA_INDE_VALU;
        }
    }
    //
    return binde;
}

static int set_recycled(unsigned int reind, FILE *attrp) {
    // OSEVPF("[FUNC]:set_recycled reind:%d\n", reind);
    cont_atti_i canod;
    if (fseeko64(attrp, -(__off64_t)sizeof (cont_atti_i), SEEK_END)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    __off64_t eose = ftello64(attrp);
    if (0x00 >= fread(&canod, sizeof (cont_atti_i), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    if (MODI_RECYCL(canod.recycle, attrp, reind))
        return -1;
    //
    canod.recycle = reind;
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fwrite(&canod, sizeof (cont_atti_i), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    // OSEVPF("end set_recycled\n");
    return 0x00;
}

//

int creat_cont_atti(char *basen) {
    FILE *attrp = crea_catti(basen);
    if (!attrp) return -1;
    fill_head(attrp);
    fill_idle(attrp);
    //
    CLOSE_CATTRI(attrp);
    return 0x00;
}

//

static unsigned int find_posi_cobid(OUT unsigned int *preind, OUT cont_atti_i *conap, FILE *attrp, unsigned int sibli, osv_oid_t *cont_obid) {
    cont_atti_i canod;
    //
    preind[0x00] = 0x00;
    unsigned int reind = sibli;
    while (!read_atti(&canod, attrp, reind)) {
        if (OBID_STOID_EQUALI(cont_obid, &canod.cont_stoid)) {
            memcpy(conap, &canod, sizeof (cont_atti_i));
            return reind;
        }
        preind[0x00] = reind;
        reind = canod.sibling;
    }
    //
    return INVA_INDE_VALU;
}

static int find_atti_contn(cont_atti_i *conap, FILE *attrp, unsigned int sibli, char *contn) {
    cont_atti_i canod;
    //
    canod.sibling = sibli;
    while (!read_atti(&canod, attrp, canod.sibling)) {
        // OSEVPF("canod.cont_name:|%s| sibling:%u\n", canod.cont_name, canod.sibling);
        if (!strcmp(contn, canod.cont_name)) {
            memcpy(conap, &canod, sizeof (cont_atti_i));
            return 0x00;
        }
    }
    //
    return -1;
}

static unsigned int find_inde_rsobid(FILE *attrp, unsigned int sibli, osv_oid_t *rcon_obid) {
    cont_atti_i canod;
    //
    unsigned int reind = sibli;
    while (!read_atti(&canod, attrp, reind)) {
        // OSEVPF("canod.cont_name:|%s| sibling:%u\n", canod.cont_name, canod.sibling);
        if (OBID_STOID_EQUALI(rcon_obid, &(canod.cont_stoid))) {
            return reind;
        }
        reind = canod.sibling;
    }
    //
    return INVA_INDE_VALU;
}

static int find_atti_otype(cont_atti_i *conap, FILE *attrp, unsigned int posind, osv_oid_t *lv2p_type) {
    cont_atti_i canod;
    //
    canod.sibling = posind;
    while (!read_atti(&canod, attrp, canod.sibling)) {
        if (STOID_EQUALI(lv2p_type, &canod.lv2p_type)) {
            memcpy(conap, &canod, sizeof (cont_atti_i));
            return 0x00;
        }
    }
    //
    return -1;
}

static unsigned int find_sibli(FILE *attrp) {
    // OSEVPF("[FUNC]:find_sibli\n");
    cont_atti_i canod;
    if (fseeko64(attrp, 0x00, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return INVA_INDE_VALU;
    }
    if (0x00 >= fread(&canod, sizeof (cont_atti_i), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return INVA_INDE_VALU;
    }
    //
    return canod.sibling;
}

//

int addi_cont_atti(char *contn, osv_oid_t *lv2p_type, uint32 stora_type, char *basen) {
    FILE *attrp = open_catti(basen);
    if (!attrp) return -1;
    //
    unsigned int binde = get_blank_atti(attrp);
    osv_oid_t lv4p_obid;
    creat_objec_obid(&lv4p_obid);
    // OSEVPF("binde:%u\n", binde);
    // OSEVPF("stora_type:%u contn:|%s| lv2p_type:|%s|\n", stora_type, contn, lv2p_type);
    if (updat_atti(&lv4p_obid, contn, lv2p_type, stora_type, attrp, binde)) {
        CLOSE_CATTRI(attrp);
        return -1;
    }
    //
    CLOSE_CATTRI(attrp);
    return 0x00;
}

//

int addi_rscont_atti(char *contn, osv_oid_t *lv2p_type, uint32 refe_coun, uint32 stora_type, char *basen) {
    FILE *attrp = open_catti(basen);
    if (!attrp) return -1;
    //
    unsigned int binde = get_blank_atti(attrp);
    osv_oid_t lv4p_obid;
    creat_objec_obid(&lv4p_obid);
    // OSEVPF("binde:%u\n", binde);
    // OSEVPF("stora_type:%u contn:|%s| lv2p_type:|%s|\n", stora_type, contn, lv2p_type);
    if (updat_rsatti(&lv4p_obid, contn, lv2p_type, refe_coun, stora_type, attrp, binde)) {
        CLOSE_CATTRI(attrp);
        return -1;
    }
    //
    CLOSE_CATTRI(attrp);
    return 0x00;
}

//

int addi_rdcont_atti(char *contn, osv_oid_t *lv2p_type, uint32 refe_coun, osv_oid_t *refe_cont, uint32 conditype, char *condition, uint32 stora_type, char *basen) {
    // OSEVPF("[FUNC]:addi_rdcont_atti\n");
    FILE *attrp = open_catti(basen);
    if (!attrp) return -1;
    //
    unsigned int binde = get_blank_atti(attrp);
    osv_oid_t lv4p_obid;
    creat_objec_obid(&lv4p_obid);
    // OSEVPF("binde:%u\n", binde);
    // OSEVPF("stora_type:%u contn:|%s| lv2p_type:|%s|\n", stora_type, contn, lv2p_type);
    if (updat_rdatti(&lv4p_obid, contn, lv2p_type, refe_coun, refe_cont, conditype, condition, stora_type, attrp, binde)) {
        CLOSE_CATTRI(attrp);
        return -1;
    }
    //
    CLOSE_CATTRI(attrp);
    return 0x00;
}

//

int dele_cont_atti(osv_oid_t *cont_obid, char *basen) {
    // OSEVPF("[FUNC]:dele_cont_atti\n");
    FILE *attrp = open_catti(basen);
    if (!attrp) return -1;
    //
    cont_atti_i canod;
    unsigned int preind;
    unsigned int sibli = find_sibli(attrp);
    sibli = find_posi_cobid(&preind, &canod, attrp, sibli, cont_obid);
    if (INVA_INDE_VALU != sibli) {
        if (modi_sibli(canod.sibling, attrp, preind)) {
            CLOSE_CATTRI(attrp);
            return -1;
        }
        if (set_recycled(sibli, attrp)) {
            CLOSE_CATTRI(attrp);
            return -1;
        }
    }
    //
    CLOSE_CATTRI(attrp);
    return 0x00;
}

//

int find_cont_atti(cont_atti_i *conap, char *contn, char *basen) {
    FILE *attrp = open_catti(basen);
    if (!attrp) return -1;
    // OSEVPF("contn:|%s|\n", contn);
    unsigned int sibli = find_sibli(attrp);
    if (find_atti_contn(conap, attrp, sibli, contn)) {
        CLOSE_CATTRI(attrp);
        return -1; // not found
    }
    // found
    CLOSE_CATTRI(attrp);
    return 0x00;
}

// rcon_obid refe_cont

int updat_rscont_atti(contain *contp, char *basen) {
    OSEVPF("[FUNC]:updat_rscont_atti\n");
    FILE *attrp = open_catti(basen);
    if (!attrp) return -1;
    // OSEVPF("contn:|%s|\n", contn);
    unsigned int sibli = find_sibli(attrp);
    unsigned int upind = find_inde_rsobid(attrp, sibli, &contp->cont_obid);
    if (INVA_INDE_VALU == upind) {
        CLOSE_CATTRI(attrp);
        return -1; // not found
    }
    // found
    if (updat_rscont(contp->refe_cove, attrp, upind)) {
        CLOSE_CATTRI(attrp);
        return -1;
    }
    CLOSE_CATTRI(attrp);
    return 0x00;
}

//

int searc_conta_attri(char *resul, char *basen, char *contn, osv_oid_t *lv2p_type) {
    FILE *attrp = open_catti(basen);
    if (!attrp) return -1;
    //
    char cont_obid[OBJE_IDENTI_ZLEN];
    char type_obid[OBJE_IDENTI_ZLEN];
    cont_atti_i canod;
    unsigned int sibli;
    if (contn) {
        sibli = find_sibli(attrp);
        if (find_atti_contn(&canod, attrp, sibli, contn)) { // not found
            lsprif(resul, "Not found contain: %s\n", contn);
        } else { // found
            sid_stroid(cont_obid, (osv_sid_t *) & canod.cont_stoid);
            sid_stroid(type_obid, (osv_sid_t *) & canod.lv2p_type);
            lsprif(resul, "contain name:%s class type:%s obid:%s\n", canod.cont_name, type_obid, cont_obid);
        }
    }
    //

    int found = 0x00;
    if (lv2p_type) {
        canod.sibling = find_sibli(attrp);
        while (INVA_INDE_VALU != canod.sibling) {
            if (!find_atti_otype(&canod, attrp, canod.sibling, lv2p_type)) { // found
                found = 0x01;
                sid_stroid(cont_obid, (osv_sid_t *) & canod.cont_stoid);
                sid_stroid(type_obid, (osv_sid_t *) & canod.lv2p_type);
                lsprif(resul, "contain name:%s class type:%s obid:%s\n", canod.cont_name, type_obid, cont_obid);
            } else if (!found) {
                oidstr(type_obid, lv2p_type);
                lsprif(resul, "Not found class %s contain.\n", type_obid);
            }
        }
    }
    //
    CLOSE_CATTRI(attrp);
    return 0x00;
}

int check_catti_lv2p(char *basen, osv_oid_t *lv2p_type) {
    FILE *attrp = open_catti(basen);
    if (!attrp) return -1;
    //
    cont_atti_i canod;
    unsigned int sibli = find_sibli(attrp);
    if (find_atti_otype(&canod, attrp, sibli, lv2p_type)) {
        // not found
        CLOSE_CATTRI(attrp);
        return 0x01;
    }
    //
    CLOSE_CATTRI(attrp);
    return 0x00;
}

//

cont_list *load_catti_base(char *basen) {
    OSEVPF("[FUNC]:load_catti_base\n");
    FILE *attrp = open_catti(basen);
    if (!attrp) return NULL;
    //
    cont_list *clist = NULL;
    contain *contp;
    cont_atti_i canod;
    // pass head
    if (read_atti(&canod, attrp, 0x00)) {
        CLOSE_CATTRI(attrp);
        return NULL;
    }
    while (!read_atti(&canod, attrp, canod.sibling)) {
        contp = appe_clist_cont(&clist);
        if (!contp) {
            _LOG_ERROR("appe clist error!");
            dele_cont_list(clist);
            CLOSE_CATTRI(attrp);
            return NULL;
        }
        // p_cont_atti_i(&canod);
        // CONVE_CATTR_CONTA
        CONVE_CATTR_CONTA(contp, canod, basen);
    }
    // OSEVPF("[FUNC]:end load_catti_base\n");
    CLOSE_CATTRI(attrp);
    return clist;
}
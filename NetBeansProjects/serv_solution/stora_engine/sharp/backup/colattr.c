#include "colattr.h"
// #include "cona_list.h"

//
#define CONTA_ATTRIB        "colle_attri.sdo"
#define INVA_INDE_VALU      ((unsigned int)-1)

//

struct colle_attri {
    osv_oid_t oid;
    char conta_name[CONTA_LENGTH];
    unsigned int stora_type;
    char data_type[CLASS_LENGTH];

    union {
        unsigned int sibling;
        unsigned int recycle;
    };
};

#define INIT_CONTA_ATTR(colla) \
        memset(&colla, '\0', sizeof(struct colle_attri)); \
        colla.sibling = INVA_INDE_VALU;

//

static FILE *creat_cadat(char *osdb) {
    char file_name[MAX_PATH];
    CREAT_CONTAIN_FILE(file_name, osdb, CONTA_ATTRIB)
    //
    FILE *attrp = fopen64(file_name, "wb+");
    if (!attrp) {
        _LOG_ERROR("creat file error! %s errno:%d", file_name, errno);
        return NULL;
    }
    //
    return attrp;
}

static FILE *open_cadat(char *osdb) {
    char file_name[MAX_PATH];
    CREAT_CONTAIN_FILE(file_name, osdb, CONTA_ATTRIB)
    //
    FILE *attrp = fopen64(file_name, "rb+");
    if (!attrp) {
        _LOG_ERROR("open file error! %s errno:%d", file_name, errno);
        return NULL;
    }
    //
    return attrp;
}
#define close_colla(attrp) fclose(attrp)

//
#define LEVE_QOBJ_TOK "odb"

static int fill_head(FILE *attrp) {
    if (fseeko64(attrp, 0x00, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    //
    struct colle_attri colla;
    INIT_CONTA_ATTR(colla)
    strcpy(colla.conta_name, LEVE_QOBJ_TOK);
    if (0 >= fwrite(&colla, sizeof (struct colle_attri), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

//

static int fill_idle(FILE *attrp) {
    if (fseeko64(attrp, 0x00, SEEK_END)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    //
    struct colle_attri iattr;
    INIT_CONTA_ATTR(iattr)
    if (0 >= fwrite(&iattr, sizeof (struct colle_attri), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

static int read_attri(struct colle_attri *colla, FILE *attrp, unsigned int ainde) {
    if (fseeko64(attrp, (__off64_t) ainde * sizeof (struct colle_attri), SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0 >= fread(colla, sizeof (struct colle_attri), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    return 0x00;
}
//

static int modi_sibli(unsigned int sibli, FILE *attrp, unsigned int ainde) {
    __off64_t eose = (__off64_t) ainde * sizeof (struct colle_attri);
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    struct colle_attri colla;
    if (0 >= fread(&colla, sizeof (struct colle_attri), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    colla.sibling = sibli;
    if (0 >= fwrite(&colla, sizeof (struct colle_attri), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

#define modi_recycl(recycl, attrp, ainde) modi_sibli(recycl, attrp, ainde)

//

static int activ_attri(unsigned int ainde, FILE *attrp) {
    if (fseeko64(attrp, 0x00, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    struct colle_attri colla;
    if (0 >= fread(&colla, sizeof (struct colle_attri), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    modi_sibli(colla.sibling, attrp, ainde);
    //
    if (fseeko64(attrp, 0x00, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    colla.sibling = ainde;
    if (0 >= fwrite(&colla, sizeof (struct colle_attri), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

static int repla_attri(char *conta_name, uint32 stora_type, char *data_type, osv_oid_t *obje_id, FILE *attrp, unsigned int rinde) {
    __off64_t eose = (__off64_t) rinde * sizeof (struct colle_attri);
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    struct colle_attri colla;
    if (0 >= fread(&colla, sizeof (struct colle_attri), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    memcpy(&colla.oid, obje_id, sizeof (osv_oid_t));
    strcpy(colla.conta_name, conta_name);
    colla.stora_type = stora_type;
    strcpy(colla.data_type, data_type);
    if (0 >= fwrite(&colla, sizeof (struct colle_attri), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

//

static unsigned int get_blank_attr(FILE *attrp) {
    if (fseeko64(attrp, -(__off64_t)sizeof (struct colle_attri), SEEK_END)) {
        _LOG_ERROR("seek file error!");
        return INVA_INDE_VALU;
    }
    __off64_t eose = ftello64(attrp);
    //
    struct colle_attri iattr;
    if (0 >= fread(&iattr, sizeof (struct colle_attri), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return INVA_INDE_VALU;
    }
    // printf("iattr.recycle:%x\n", iattr.recycle);
    unsigned int binde = INVA_INDE_VALU;
    if (INVA_INDE_VALU == iattr.recycle) {
        binde = eose / sizeof (struct colle_attri);
printf("get_blank_attr binde:%x\n", binde);
        activ_attri(binde, attrp);
        fill_idle(attrp);
    } else {
        binde = iattr.recycle;
        struct colle_attri battr;
        read_attri(&battr, attrp, binde);
        iattr.recycle = battr.recycle;
        activ_attri(binde, attrp);
        if (fseeko64(attrp, eose, SEEK_SET)) {
            _LOG_ERROR("seek file error!");
            return INVA_INDE_VALU;
        }
        if (0 >= fwrite(&iattr, sizeof (struct colle_attri), 0x01, attrp)) {
            _LOG_ERROR("fwrite file error!");
            return INVA_INDE_VALU;
        }
    }
    //
    return binde;
}

static int set_recycled(unsigned int ainde, FILE *attrp) {
    if (fseeko64(attrp, -(__off64_t)sizeof (struct colle_attri), SEEK_END)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    __off64_t eose = ftello64(attrp);
    //
    struct colle_attri iattr;
    if (0 >= fread(&iattr, sizeof (struct colle_attri), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    if (fseeko64(attrp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    modi_recycl(iattr.recycle, attrp, ainde);
    iattr.recycle = ainde;
    if (0 >= fwrite(&iattr, sizeof (struct colle_attri), 0x01, attrp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

//

int creat_colla(char *osdb) {
    FILE *attrp = creat_cadat(osdb);
    if (!attrp) return -1;
    fill_head(attrp);
    fill_idle(attrp);
    //
    close_colla(attrp);
    return 0x00;
}

//

static unsigned int find_inde_name(unsigned int *preind, struct colle_attri *colla, FILE *attrp, unsigned int sibli, char *conta_name) {
    struct colle_attri canod;
    //
    unsigned int ainde = sibli;
    while (!read_attri(&canod, attrp, ainde)) {
        if (!strcmp(conta_name, canod.conta_name)) {
            memcpy(colla, &canod, sizeof (struct colle_attri));
            return ainde;
        }
        *preind = ainde;
        ainde = canod.sibling;
    }
    //
    return INVA_INDE_VALU;
}

static int find_attr_name(struct colle_attri *colla, FILE *attrp, unsigned int sibli, char *conta_name) {
    struct colle_attri canod;
    //
    unsigned int ainde = sibli;
    while (!read_attri(&canod, attrp, ainde)) {
        printf("ainde:%u\n", ainde);
        printf("canod.conta_name:%s sibling:%u\n", canod.conta_name, canod.sibling);
        if (!strcmp(conta_name, canod.conta_name)) {
            memcpy(colla, &canod, sizeof (struct colle_attri));
            return 0x00;
        }
        ainde = canod.sibling;
    }
    //
    return -1;
}

static unsigned int find_attr_type(struct colle_attri *colla, FILE *attrp, unsigned int posind, char *data_type) {
    struct colle_attri canod;
    //
    unsigned int ainde = posind;
    while (!read_attri(&canod, attrp, ainde)) {
        if (!strcmp(data_type, canod.data_type)) {
            memcpy(colla, &canod, sizeof (struct colle_attri));
            return ainde;
        }
        ainde = canod.sibling;
    }
    //
    return INVA_INDE_VALU;
}

static unsigned int find_sibli(FILE *attrp) {
    if (fseeko64(attrp, 0x00, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return INVA_INDE_VALU;
    }
    struct colle_attri colla;
    if (0 >= fread(&colla, sizeof (struct colle_attri), 0x01, attrp)) {
        _LOG_ERROR("read file error!");
        return INVA_INDE_VALU;
    }
    //
    return colla.sibling;
}

//

int addi_colla(char *conta_name, uint32 stora_type, char *data_type, char *osdb) {
    FILE *attrp = open_cadat(osdb);
    if (!attrp) return -1;
    //
    unsigned int binde = get_blank_attr(attrp);
    osv_oid_t obje_id;
    creat_objeid_obj(&obje_id);
    printf("binde:%u\n", binde);
    printf("stora_type:%s conta_name:%s data_type:%s\n", stora_type, conta_name, data_type);
    repla_attri(conta_name, stora_type, data_type, &obje_id, attrp, binde);
    //
    close_colla(attrp);
    return 0x00;
}

//

int dele_colla(char *conta_name, char *osdb) {
    FILE *attrp = open_cadat(osdb);
    if (!attrp) return -1;
    //
    unsigned int sibli = find_sibli(attrp);
    struct colle_attri colla;
    unsigned int preind;
    unsigned int ainde = find_inde_name(&preind, &colla, attrp, sibli, conta_name);
    if (INVA_INDE_VALU != ainde) {
        modi_sibli(colla.sibling, attrp, preind);
        set_recycled(ainde, attrp);
    }
    //
    close_colla(attrp);
    return 0x00;
}

//

int find_colla(osv_oid_t *oid, char *data_type, char *conta_name, char *osdb) {
    FILE *attrp = open_cadat(osdb);
    if (!attrp) return -1;
    printf("conta_name:%s\n", conta_name);
    struct colle_attri colla;
    if (find_attr_name(&colla, attrp, 0x00, conta_name)) return -1; // not found
    // found
    memcpy(oid, &colla.oid, sizeof (osv_oid_t));
    strcpy(data_type, colla.data_type);
    //
    return 0x00;
}

//

int sear_colla(char *result, char *osdb, char *conta_name, char *data_type) {
    FILE *attrp = open_cadat(osdb);
    if (!attrp) return -1;
    //
    char oid_stri[OID_LINE_LEN];
    struct colle_attri colla;
    unsigned int sibli = find_sibli(attrp);
    if (conta_name) {
        if (find_attr_name(&colla, attrp, sibli, conta_name)) { // not found
            lsprif(result, "Not found contain: %s\n", conta_name);
        } else { // found
            oidstr(oid_stri, &colla.oid);
            lsprif(result, "contain name:%s class type:%s oid:%s\n", colla.conta_name, colla.data_type, oid_stri);
        }
    }
    //
    int found = 0x00;
    unsigned int ainde = sibli;
    if (data_type) {
        while (INVA_INDE_VALU != ainde) {
            ainde = find_attr_type(&colla, attrp, ainde, data_type);
            if (INVA_INDE_VALU != ainde) { // found
                found = 0x01;
                oidstr(oid_stri, &colla.oid);
                lsprif(result, "contain name:%s class type:%s oid:%s\n", colla.conta_name, colla.data_type, oid_stri);
            } else if (!found) {
                lsprif(result, "Not found class %s contain.\n", data_type);
            }
        }
    }
    //
    close_colla(attrp);
    return 0x00;
}

//
#define CONVE_CATTR_CONTA(COLLE, OSDB, CANOD) { \
    memcpy(&COLLE->oid, &CANOD.oid, sizeof(osv_oid_t)); \
    strcpy(COLLE->osdb_name, OSDB); \
    strcpy(COLLE->data_type, CANOD.data_type); \
    strcpy(COLLE->conta_obje, CANOD.conta_name); \
}

struct conta_list *load_colla(char *osdb) {
    FILE *attrp = open_cadat(osdb);
    if (!attrp) return NULL;
    //
    struct conta_list *colist = NULL;
    struct contain *conta;
    struct colle_attri canod;
    //
    unsigned int ainde = 0x00;
    while (!read_attri(&canod, attrp, ainde)) {
        conta = appe_conta(&colist);
        CONVE_CATTR_CONTA(conta, osdb, canod)
        ainde = canod.sibling;
    }
    //
    close_colla(attrp);
    return colist;
}

#include "commo_header.h"
#include "kcomm_header.h"

#include "lv2p_conte.h"

//

#define INIT_LVTP_CONT(LTNOD) \
        memset(&LTNOD, '\0', sizeof(lv2p_cont_i)); \
        LTNOD.sibling = INVA_INDE_VALU;

//

static FILE *crea_conte(char *basen) {
    char file_name[MAX_PATH * 3];
    CREAT_LIBRARY_FILE(file_name, basen, LVTP_CONTE_DATA);
    //
    FILE *contp = fopen64(file_name, "wb+");
    if (!contp) {
        _LOG_ERROR("creat file error! %s", file_name);
        return NULL;
    }
    //
    return contp;
}

static FILE *open_conte(char *basen) {
    char file_name[MAX_PATH * 3];
    CREAT_LIBRARY_FILE(file_name, basen, LVTP_CONTE_DATA);
    //
    FILE *contp = fopen64(file_name, "rb+");
    if (!contp) {
        _LOG_ERROR("open file error! %s", file_name);
        return NULL;
    }
    //
    return contp;
}
#define CLOSE_DATTRI(ATTRP) if(ATTRP) fclose(ATTRP)

//

static int fill_head(FILE *contp) {
    lv2p_cont_i l2nod;
    INIT_LVTP_CONT(l2nod)
    if (fseeko64(contp, 0x00, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fwrite(&l2nod, sizeof (lv2p_cont_i), 0x01, contp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

static int fill_idle(FILE *contp) {
    lv2p_cont_i l2nod;
    INIT_LVTP_CONT(l2nod)
    if (fseeko64(contp, 0x00, SEEK_END)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fwrite(&l2nod, sizeof (lv2p_cont_i), 0x01, contp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

static int read_conte(lv2p_cont_i *l2nod, FILE *contp, unsigned int reind) {
    if (INVA_INDE_VALU == reind)
        return -1;
    if (fseeko64(contp, (__off64_t) reind * sizeof (lv2p_cont_i), SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fread(l2nod, sizeof (lv2p_cont_i), 0x01, contp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    return 0x00;
}

//

static int modi_sibli(unsigned int sibli, FILE *contp, unsigned int moind) {
    __off64_t eose = (__off64_t) moind * sizeof (lv2p_cont_i);
    //
    lv2p_cont_i l2nod;
    if (fseeko64(contp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fread(&l2nod, sizeof (lv2p_cont_i), 0x01, contp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    l2nod.sibling = sibli;
    if (fseeko64(contp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fwrite(&l2nod, sizeof (lv2p_cont_i), 0x01, contp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

#define MODI_RECYCL(RECYCL, ATTRP, AINDE) modi_sibli(RECYCL, ATTRP, AINDE)

//

static int activ_conte(unsigned int acind, FILE *contp) {
    lv2p_cont_i l2nod;
    if (fseeko64(contp, 0x00, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fread(&l2nod, sizeof (lv2p_cont_i), 0x01, contp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    if (modi_sibli(l2nod.sibling, contp, acind))
        return -1;
    //
    l2nod.sibling = acind;
    if (fseeko64(contp, 0x00, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fwrite(&l2nod, sizeof (lv2p_cont_i), 0x01, contp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

static int updat_conte(char *lv2pn, osv_oid_t *lv2p_obid, char *lv2p_fmtsd, uint64 data_size, FILE *contp, unsigned int upind) {
    __off64_t eose = (__off64_t) upind * sizeof (lv2p_cont_i);
    //
    lv2p_cont_i l2nod;
    if (fseeko64(contp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fread(&l2nod, sizeof (lv2p_cont_i), 0x01, contp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    strcpy(l2nod.lv2pn, lv2pn);
    STOID_OBID_COPY(l2nod.lv2p_stoid, lv2p_obid)
    //
    strcpy(l2nod.lv2p_fmtsd, lv2p_fmtsd);
    l2nod.data_size = data_size;
    if (fseeko64(contp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fwrite(&l2nod, sizeof (lv2p_cont_i), 0x01, contp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

//

static int updat_fmtsize(char *lv2p_fmtsd, uint64 data_size, FILE *contp, unsigned int upind) {
    __off64_t eose = (__off64_t) upind * sizeof (lv2p_cont_i);
    //
    lv2p_cont_i l2nod;
    if (fseeko64(contp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fread(&l2nod, sizeof (lv2p_cont_i), 0x01, contp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    strcpy(l2nod.lv2p_fmtsd, lv2p_fmtsd);
    l2nod.data_size = data_size;
    if (fseeko64(contp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fwrite(&l2nod, sizeof (lv2p_cont_i), 0x01, contp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

//

static unsigned int get_blank_cont(FILE *contp) {
    lv2p_cont_i ianod;
    if (fseeko64(contp, -(__off64_t)sizeof (lv2p_cont_i), SEEK_END)) {
        _LOG_ERROR("seek file error!");
        return INVA_INDE_VALU;
    }
    __off64_t eose = ftello64(contp);
    if (0x00 >= fread(&ianod, sizeof (lv2p_cont_i), 0x01, contp)) {
        _LOG_ERROR("read file error!");
        return INVA_INDE_VALU;
    }
    //
    unsigned int binde = INVA_INDE_VALU;
    if (INVA_INDE_VALU == ianod.recycle) {
        binde = eose / sizeof (lv2p_cont_i);
        activ_conte(binde, contp);
        fill_idle(contp);
    } else {
        binde = ianod.recycle;
        lv2p_cont_i l2nod;
        if (read_conte(&l2nod, contp, binde))
            return INVA_INDE_VALU;
        ianod.recycle = l2nod.recycle;
        activ_conte(binde, contp);
        if (fseeko64(contp, eose, SEEK_SET)) {
            _LOG_ERROR("seek file error!");
            return INVA_INDE_VALU;
        }
        if (0x00 >= fwrite(&ianod, sizeof (lv2p_cont_i), 0x01, contp)) {
            _LOG_ERROR("fwrite file error!");
            return INVA_INDE_VALU;
        }
    }
    //
    return binde;
}

static int set_recycled(unsigned int reind, FILE *contp) {
    lv2p_cont_i l2nod;
    if (fseeko64(contp, -(__off64_t)sizeof (lv2p_cont_i), SEEK_END)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    __off64_t eose = ftello64(contp);
    if (0x00 >= fread(&l2nod, sizeof (lv2p_cont_i), 0x01, contp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    if (MODI_RECYCL(l2nod.recycle, contp, reind))
        return -1;
    //
    l2nod.recycle = reind;
    if (fseeko64(contp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fwrite(&l2nod, sizeof (lv2p_cont_i), 0x01, contp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

//

int creat_lv2p_conte(char *basen) {
    FILE *contp = crea_conte(basen);
    if (!contp) return -1;
    fill_head(contp);
    fill_idle(contp);
    //
    CLOSE_DATTRI(contp);
    return 0x00;
}

//

static unsigned int find_posi_lv2pn(OUT unsigned int *preind, OUT lv2p_cont_i *cpnod, FILE *contp, unsigned int sibli, char *lv2pn) {
    lv2p_cont_i l2nod;
    //
    preind[0x00] = 0x00;
    unsigned int reind = sibli;
    while (!read_conte(&l2nod, contp, reind)) {
        if (!strcmp(lv2pn, l2nod.lv2pn)) {
            memcpy(cpnod, &l2nod, sizeof (lv2p_cont_i));
            return reind;
        }
        preind[0x00] = reind;
        reind = l2nod.sibling;
    }
    //
    return INVA_INDE_VALU;
}

static unsigned int find_inde_lv2pn(FILE *contp, unsigned int sibli, char *lv2pn) {
    lv2p_cont_i l2nod;
    //
    unsigned int reind = sibli;
    while (!read_conte(&l2nod, contp, reind)) {
        if (!strcmp(lv2pn, l2nod.lv2pn)) {
            return reind;
        }
        reind = l2nod.sibling;
    }
    //
    return INVA_INDE_VALU;
}

static unsigned int find_inde_obid(FILE *contp, unsigned int sibli, osv_oid_t *lv2p_obid) {
    lv2p_cont_i l2nod;
    //
    unsigned int reind = sibli;
    while (!read_conte(&l2nod, contp, reind)) {
        if (OBID_STOID_EQUALI(lv2p_obid, &l2nod.lv2p_stoid)) {
            return reind;
        }
        reind = l2nod.sibling;
    }
    //
    return INVA_INDE_VALU;
}

//

static unsigned int find_sibli(FILE *contp) {
    lv2p_cont_i l2nod;
    if (fseeko64(contp, 0x00, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return INVA_INDE_VALU;
    }
    if (0x00 >= fread(&l2nod, sizeof (lv2p_cont_i), 0x01, contp)) {
        _LOG_ERROR("read file error!");
        return INVA_INDE_VALU;
    }
    //
    return l2nod.sibling;
}

//

int appen_conte_lv2p(char *lv2pn, osv_oid_t *lv2p_obid, char *lv2p_fmtsd, uint64 data_size, char *basen) {
    // OSEVPF("[FUNC]:appen_conte_lv2p\n");
    FILE *contp = open_conte(basen);
    if (!contp) return -1;
    // OSEVPF("appen_conte_lv2p lv2pn:%s conte:%s\n", lv2pn, conte);
    unsigned int sibli = find_sibli(contp);
    sibli = find_inde_lv2pn(contp, sibli, lv2pn);
    if (INVA_INDE_VALU != sibli) {
        // OSEVPF("move l2nod\n");
        if (updat_fmtsize(lv2p_fmtsd, data_size, contp, sibli)) {
            CLOSE_DATTRI(contp);
            return -1;
        }
    } else {
        // OSEVPF("addi l2nod\n");
        unsigned int cinde = get_blank_cont(contp);
        if (updat_conte(lv2pn, lv2p_obid, lv2p_fmtsd, data_size, contp, cinde)) {
            CLOSE_DATTRI(contp);
            return -1;
        }
    }
    //
    CLOSE_DATTRI(contp);
    return 0x00;
}

//

int updat_conte_lv2p(osv_oid_t *lv2p_obid, char *lv2p_fmtsd, uint64 data_size, char *basen) {
    // OSEVPF("[FUNC]:updat_conte_lv2p\n");
    FILE *contp = open_conte(basen);
    if (!contp) return -1;
    // OSEVPF("appen_conte_lv2p lv2pn:%s conte:%s\n", lv2pn, conte);
    unsigned int sibli = find_sibli(contp);
    sibli = find_inde_obid(contp, sibli, lv2p_obid);
    if (INVA_INDE_VALU == sibli) {
        CLOSE_DATTRI(contp);
        return -1;
    }
    //
    if (updat_fmtsize(lv2p_fmtsd, data_size, contp, sibli)) {
        CLOSE_DATTRI(contp);
        return -1;
    }
    //
    CLOSE_DATTRI(contp);
    return 0x00;
}

//

int delet_conte_lv2p(char *lv2pn, char *basen) {
    // OSEVPF("[FUNC]:delet_conte_lv2p\n");
    FILE *contp = open_conte(basen);
    if (!contp) return -1;
    //
    lv2p_cont_i l2nod;
    unsigned int preind;
    unsigned int sibli = find_sibli(contp);
    sibli = find_posi_lv2pn(&preind, &l2nod, contp, sibli, lv2pn);
    if (INVA_INDE_VALU != sibli) {
        // OSEVPF("delete lv2pn:|%s|\n", lv2pn);
        if (modi_sibli(l2nod.sibling, contp, preind)) {
            CLOSE_DATTRI(contp);
            return -1;
        }
        if (set_recycled(sibli, contp)) {
            CLOSE_DATTRI(contp);
            return -1;
        }
    }
    //
    CLOSE_DATTRI(contp);
    return 0x00;
}

//

unsigned int open_conte_lv2p(lv2p_cont_t *dcont, char *basen) {
    dcont->contp = open_conte(basen);
    if (!dcont->contp)
        return INVA_INDE_VALU;
    return find_sibli(dcont->contp);
}

void close_conte_lv2p(lv2p_cont_t *dcont) {
    CLOSE_DATTRI(dcont->contp);
}

unsigned int read_conte_lv2p(lv2p_cont_t *dcont, unsigned int reind) {
    // OSEVPF("read_conte_lv2p reind:%u\n", reind);
    if (read_conte(&dcont->l2nod, dcont->contp, reind))
        return INVA_INDE_VALU;
    //
    return dcont->l2nod.sibling;
}
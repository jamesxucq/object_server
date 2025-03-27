
#include "commo_header.h"
#include "kcomm_header.h"

#include "lev1_conte.h"

//

#define INIT_LV0I_CONT(LONOD) \
        memset(&LONOD, '\0', sizeof(lev1_cont_i)); \
        LONOD.sibling = INVA_INDE_VALU;

//

static FILE *crea_conte(char *basen) {
    char file_name[MAX_PATH * 3];
    CREAT_LIBRARY_FILE(file_name, basen, LEVO_CONTE_DATA);
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
    CREAT_LIBRARY_FILE(file_name, basen, LEVO_CONTE_DATA);
    //
    FILE *contp = fopen64(file_name, "rb+");
    if (!contp) {
        _LOG_ERROR("open file error! %s", file_name);
        return NULL;
    }
    //
    return contp;
}
#define CLOSE_OATTRI(ATTRP) if(ATTRP) fclose(ATTRP)

//

static int fill_head(FILE *contp) {
    lev1_cont_i l1i_nod;
    INIT_LV0I_CONT(l1i_nod)
    if (fseeko64(contp, 0x00, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fwrite(&l1i_nod, sizeof (lev1_cont_i), 0x01, contp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

static int fill_idle(FILE *contp) {
    lev1_cont_i l1i_nod;
    INIT_LV0I_CONT(l1i_nod)
    if (fseeko64(contp, 0x00, SEEK_END)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fwrite(&l1i_nod, sizeof (lev1_cont_i), 0x01, contp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

static int read_conte(lev1_cont_i *l1i_nod, FILE *contp, unsigned int reind) {
    if (INVA_INDE_VALU == reind)
        return -1;
    if (fseeko64(contp, (__off64_t) reind * sizeof (lev1_cont_i), SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fread(l1i_nod, sizeof (lev1_cont_i), 0x01, contp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    return 0x00;
}

//

static int modi_sibli(unsigned int sibli, FILE *contp, unsigned int moind) {
    __off64_t eose = (__off64_t) moind * sizeof (lev1_cont_i);
    //
    lev1_cont_i l1i_nod;
    if (fseeko64(contp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fread(&l1i_nod, sizeof (lev1_cont_i), 0x01, contp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    l1i_nod.sibling = sibli;
    if (fseeko64(contp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fwrite(&l1i_nod, sizeof (lev1_cont_i), 0x01, contp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

#define MODI_RECYCL(RECYCL, ATTRP, AINDE) modi_sibli(RECYCL, ATTRP, AINDE)

//

static int activ_conte(unsigned int acind, FILE *contp) {
    lev1_cont_i l1i_nod;
    if (fseeko64(contp, 0x00, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fread(&l1i_nod, sizeof (lev1_cont_i), 0x01, contp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    if (modi_sibli(l1i_nod.sibling, contp, acind))
        return -1;
    //
    l1i_nod.sibling = acind;
    if (fseeko64(contp, 0x00, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fwrite(&l1i_nod, sizeof (lev1_cont_i), 0x01, contp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

//

static int updat_conte(char *lv2pn, lev1me *lv1me, char *lev1_librn, FILE *contp, unsigned int upind) {
    __off64_t eose = (__off64_t) upind * sizeof (lev1_cont_i);
    //
    lev1_cont_i l1i_nod;
    if (fseeko64(contp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fread(&l1i_nod, sizeof (lev1_cont_i), 0x01, contp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    strcpy(l1i_nod.lv2pn, lv2pn);
    strcpy(l1i_nod.lev1n, lv1me->lev1n);
    l1i_nod.oivk_retyp = lv1me->oivk_retyp_oe; // oivk return type 
    strcpy(l1i_nod.oivk_fmtsp, lv1me->oivk_fmtsp_oe);
    l1i_nod.oivk_size = lv1me->oivk_size_oe; // oivk struct length
    strcpy(l1i_nod.lev1_librn, lev1_librn);
    if (fseeko64(contp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fwrite(&l1i_nod, sizeof (lev1_cont_i), 0x01, contp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

//

static int updat_library(char *lev1_librn, FILE *contp, unsigned int upind) {
    __off64_t eose = (__off64_t) upind * sizeof (lev1_cont_i);
    //
    lev1_cont_i l1i_nod;
    if (fseeko64(contp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fread(&l1i_nod, sizeof (lev1_cont_i), 0x01, contp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    strcpy(l1i_nod.lev1_librn, lev1_librn);
    if (fseeko64(contp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fwrite(&l1i_nod, sizeof (lev1_cont_i), 0x01, contp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

//

static unsigned int get_blank_cont(FILE *contp) {
    lev1_cont_i l1i_and;
    if (fseeko64(contp, -(__off64_t)sizeof (lev1_cont_i), SEEK_END)) {
        _LOG_ERROR("seek file error!");
        return INVA_INDE_VALU;
    }
    __off64_t eose = ftello64(contp);
    if (0x00 >= fread(&l1i_and, sizeof (lev1_cont_i), 0x01, contp)) {
        _LOG_ERROR("read file error!");
        return INVA_INDE_VALU;
    }
    //
    unsigned int binde = INVA_INDE_VALU;
    if (INVA_INDE_VALU == l1i_and.recycle) {
        binde = eose / sizeof (lev1_cont_i);
        activ_conte(binde, contp);
        fill_idle(contp);
    } else {
        binde = l1i_and.recycle;
        lev1_cont_i l1i_nod;
        if (read_conte(&l1i_nod, contp, binde))
            return INVA_INDE_VALU;
        l1i_and.recycle = l1i_nod.recycle;
        activ_conte(binde, contp);
        if (fseeko64(contp, eose, SEEK_SET)) {
            _LOG_ERROR("seek file error!");
            return INVA_INDE_VALU;
        }
        if (0x00 >= fwrite(&l1i_and, sizeof (lev1_cont_i), 0x01, contp)) {
            _LOG_ERROR("fwrite file error!");
            return INVA_INDE_VALU;
        }
    }
    //
    return binde;
}

static int set_recycled(unsigned int reind, FILE *contp) {
    lev1_cont_i l1i_nod;
    if (fseeko64(contp, -(__off64_t)sizeof (lev1_cont_i), SEEK_END)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    __off64_t eose = ftello64(contp);
    if (0x00 >= fread(&l1i_nod, sizeof (lev1_cont_i), 0x01, contp)) {
        _LOG_ERROR("read file error!");
        return -1;
    }
    //
    if (MODI_RECYCL(l1i_nod.recycle, contp, reind))
        return -1;
    //
    l1i_nod.recycle = reind;
    if (fseeko64(contp, eose, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return -1;
    }
    if (0x00 >= fwrite(&l1i_nod, sizeof (lev1_cont_i), 0x01, contp)) {
        _LOG_ERROR("fwrite file error!");
        return -1;
    }
    //
    return 0x00;
}

//

int creat_lev1_conte(char *basen) {
    FILE *contp = crea_conte(basen);
    if (!contp) return -1;
    fill_head(contp);
    fill_idle(contp);
    //
    CLOSE_OATTRI(contp);
    return 0x00;
}

//

static unsigned int find_posi_lv1id(OUT unsigned int *preind, OUT lev1_cont_i *l1i_pnd, FILE *contp, unsigned int sibli, lev1id *lev1i) {
    lev1_cont_i l1i_nod;
    //
    preind[0x00] = 0x00;
    unsigned int reind = sibli;
    while (!read_conte(&l1i_nod, contp, reind)) {
        if (!strcmp(lev1i->crea_lv2pn, l1i_nod.lv2pn) && !strcmp(lev1i->crea_lev1n, l1i_nod.lev1n) && !strcmp(lev1i->oivk_fmtsp_oi, l1i_nod.oivk_fmtsp)) {
            memcpy(l1i_pnd, &l1i_nod, sizeof (lev1_cont_i));
            return reind;
        }
        preind[0x00] = reind;
        reind = l1i_nod.sibling;
    }
    //
    return INVA_INDE_VALU;
}

static unsigned int find_posi_lev1m(OUT unsigned int *preind, OUT lev1_cont_i *l1i_pnd, FILE *contp, unsigned int sibli, lev1_meta *lev1m) {
    lev1_cont_i l1i_nod;
    //
    preind[0x00] = 0x00;
    unsigned int reind = sibli;
    while (!read_conte(&l1i_nod, contp, reind)) {
        if (!strcmp(lev1m->lv2pn, l1i_nod.lv2pn) && !strcmp(lev1m->lev1n, l1i_nod.lev1n) && !strcmp(lev1m->oivk_fmtsp_om, l1i_nod.oivk_fmtsp)) {
            memcpy(l1i_pnd, &l1i_nod, sizeof (lev1_cont_i));
            return reind;
        }
        preind[0x00] = reind;
        reind = l1i_nod.sibling;
    }
    //
    return INVA_INDE_VALU;
}

static unsigned int find_inde_lv1me(FILE *contp, unsigned int sibli, char *lv2pn, lev1me *lv1me) {
    lev1_cont_i l1i_nod;
    //
    unsigned int reind = sibli;
    while (!read_conte(&l1i_nod, contp, reind)) {
        if (!strcmp(lv2pn, l1i_nod.lv2pn) && !strcmp(lv1me->lev1n, l1i_nod.lev1n) && !strcmp(lv1me->oivk_fmtsp_oe, l1i_nod.oivk_fmtsp)) {
            return reind;
        }
        reind = l1i_nod.sibling;
    }
    //
    return INVA_INDE_VALU;
}

//

static unsigned int find_sibli(FILE *contp) {
    lev1_cont_i l1i_nod;
    if (fseeko64(contp, 0x00, SEEK_SET)) {
        _LOG_ERROR("seek file error!");
        return INVA_INDE_VALU;
    }
    if (0x00 >= fread(&l1i_nod, sizeof (lev1_cont_i), 0x01, contp)) {
        _LOG_ERROR("read file error!");
        return INVA_INDE_VALU;
    }
    //
    return l1i_nod.sibling;
}

//

int appen_conte_lv1me(char *basen, char *lv2pn, lev1me *lv1me, char *lev1_librn) {
    FILE *contp = open_conte(basen);
    if (!contp) return -1;
    // OSEVPF("appen_conte_lv1me lv2pn:%s lv1n_fmts:%s lev1_librn:%s\n", lv2pn, lv1n_fmts, lev1_librn);
    unsigned int sibli = find_sibli(contp);
    sibli = find_inde_lv1me(contp, sibli, lv2pn, lv1me);
    if (INVA_INDE_VALU != sibli) {
        // OSEVPF("move l1i_nod!\n");
        if (updat_library(lev1_librn, contp, sibli)) {
            CLOSE_OATTRI(contp);
            return -1;
        }
    } else {
        // OSEVPF("addi l1i_nod!\n");
        unsigned int cinde = get_blank_cont(contp);
        if (updat_conte(lv2pn, lv1me, lev1_librn, contp, cinde)) {
            CLOSE_OATTRI(contp);
            return -1;
        }
    }
    //
    CLOSE_OATTRI(contp);
    return 0x00;
}

//

int updat_conte_lv1me(char *basen, char *lv2pn, lev1me *lv1me, char *lev1_librn) {
    FILE *contp = open_conte(basen);
    if (!contp) return -1;
    // OSEVPF("appen_conte_lv1me lv2pn:%s lv1n_fmts:%s lev1_librn:%s\n", lv2pn, lv1n_fmts, lev1_librn);
    unsigned int sibli = find_sibli(contp);
    sibli = find_inde_lv1me(contp, sibli, lv2pn, lv1me);
    if (INVA_INDE_VALU == sibli) {
        CLOSE_OATTRI(contp);
        return -1;
    }
    //
    if (updat_library(lev1_librn, contp, sibli)) {
        CLOSE_OATTRI(contp);
        return -1;
    }
    //
    CLOSE_OATTRI(contp);
    return 0x00;
}

//

int delet_conte_lv1id(char *basen, lev1id *lev1i) {
    // OSEVPF("[FUNC]:delet_conte_lev1\n");
    FILE *contp = open_conte(basen);
    if (!contp) return -1;
    //
    lev1_cont_i l1i_nod;
    unsigned int preind;
    unsigned int sibli = find_sibli(contp);
    sibli = find_posi_lv1id(&preind, &l1i_nod, contp, sibli, lev1i);
    if (INVA_INDE_VALU != sibli) {
        // OSEVPF("delete lv1n_fmts:|%s|\n", lv1n_fmts);
        if (modi_sibli(l1i_nod.sibling, contp, preind)) {
            CLOSE_OATTRI(contp);
            return -1;
        }
        if (set_recycled(sibli, contp)) {
            CLOSE_OATTRI(contp);
            return -1;
        }
    }
    //
    CLOSE_OATTRI(contp);
    return 0x00;
}

int delet_conte_lev1m(char *basen, lev1_meta *lev1m) {
    // OSEVPF("[FUNC]:delet_conte_lev1m\n");
    FILE *contp = open_conte(basen);
    if (!contp) return -1;
    //
    lev1_cont_i l1i_nod;
    unsigned int preind;
    unsigned int sibli = find_sibli(contp);
    sibli = find_posi_lev1m(&preind, &l1i_nod, contp, sibli, lev1m);
    if (INVA_INDE_VALU != sibli) {
        // OSEVPF("delete lv1n_fmts:|%s|\n", lv1n_fmts);
        if (modi_sibli(l1i_nod.sibling, contp, preind)) {
            CLOSE_OATTRI(contp);
            return -1;
        }
        if (set_recycled(sibli, contp)) {
            CLOSE_OATTRI(contp);
            return -1;
        }
    }
    //
    CLOSE_OATTRI(contp);
    return 0x00;
}

//

unsigned int open_conte_lev1(lev1_cont_t *ocont, char *basen) {
    ocont->contp = open_conte(basen);
    if (!ocont->contp) return INVA_INDE_VALU;
    return find_sibli(ocont->contp);
}

void close_conte_lev1(lev1_cont_t *ocont) {
    CLOSE_OATTRI(ocont->contp);
}

unsigned int read_conte_lev1(lev1_cont_t *ocont, unsigned int reind) {
    // OSEVPF("read_conte_lev1 reind:%u\n", reind);
    if (read_conte(&ocont->l1i_nod, ocont->contp, reind))
        return INVA_INDE_VALU;
    //
    return ocont->l1i_nod.sibling;
}
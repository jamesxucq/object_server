#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/file.h>

#include "shap_common.h"
#include "shap_struct.h"
#include "shap_utility.h"
#include "shap_entry.h"

//
#define HEAD_ATTRIB_ENTRY(ENTRY) \
        memset(&ENTRY, '\0', sizeof(struct entry_id)); \
        ENTRY.prev_sibli = 0x00; \
        ENTRY.next_sibli = INVA_INDE_VALU;

//

uint32 fill_head_iden(FILE *fpiden, int32 isize) {
    struct entry_id ident;
    HEAD_ATTRIB_ENTRY(ident)
    if (fseek(fpiden, 0x00, SEEK_END)) return 0x01;
    if (0 >= fwrite(&ident, sizeof (struct entry_id), 1, fpiden)) return 0x01;
    //
    char *idata = (char *) malloc(isize);
    memset(idata, '\0', isize);
    if (0 >= fwrite(idata, isize, 1, fpiden)) {
        free(idata);
        return 0x01;
    }
    free(idata);
    //
    return 0x00;
}

//
#define INIT_ATTRIB_ENTRY(ENTRY) \
        memset(&ENTRY, '\0', sizeof(struct entry_id)); \
        ENTRY.prev_sibli = INVA_INDE_VALU; \
        ENTRY.next_sibli = INVA_INDE_VALU;

uint32 fill_idle_iden(FILE *fpiden, int32 isize) {
    struct entry_id ident;
    INIT_ATTRIB_ENTRY(ident)
    if (fseek(fpiden, 0x00, SEEK_END)) return 0x01;
    if (0 >= fwrite(&ident, sizeof (struct entry_id), 1, fpiden)) return 0x01;
    //
    char *idata = (char *) malloc(isize);
    memset(idata, '\0', isize);
    if (0 >= fwrite(idata, isize, 1, fpiden)) {
        free(idata);
        return 0x01;
    }
    free(idata);
    //
    return 0x00;
}

//

static uint32 find_next_sibli(FILE *fpiden, int32 ainde, int32 isize) {
    struct entry_id ident;
    //
    if (fseek(fpiden, (sizeof (struct entry_id)+isize) * ainde, SEEK_SET))
        return INVA_INDE_VALU;
    if (0 >= fread(&ident, sizeof (struct entry_id), 1, fpiden))
        return INVA_INDE_VALU;
    //
    return ident.next_sibli;
}

//

static int32 prev_sibli_modify(FILE *fpiden, uint32 ainde, int32 isize, uint32 prev_sibli) {
    struct entry_id ident;
    if (INVA_INDE_VALU == ainde) return 0x00;
    //
    off_t eose = (sizeof (struct entry_id)+isize) * ainde;
    if (fseek(fpiden, eose, SEEK_SET)) return -1;
    if (0 >= fread(&ident, sizeof (struct entry_id), 1, fpiden))
        return -1;
    //
    ident.prev_sibli = prev_sibli;
    if (fseek(fpiden, eose, SEEK_SET)) return -1;
    if (0 >= fwrite(&ident, sizeof (struct entry_id), 1, fpiden))
        return -1;
    //
    return 0x00;
}

static int32 next_sibli_modify(FILE *fpiden, uint32 ainde, int32 isize, uint32 next_sibli) {
    struct entry_id ident;
    if (INVA_INDE_VALU == ainde) return 0x00;
    //
    off_t eose = (sizeof (struct entry_id)+isize) * ainde;
    if (fseek(fpiden, eose, SEEK_SET)) return -1;
    if (0 >= fread(&ident, sizeof (struct entry_id), 1, fpiden))
        return -1;
    //
    ident.next_sibli = next_sibli;
    if (fseek(fpiden, eose, SEEK_SET)) return -1;
    if (0 >= fwrite(&ident, sizeof (struct entry_id), 1, fpiden))
        return -1;
    //
    return 0x00;
}

//

static int32 appe_activ_iden(FILE *fpiden, int32 ainde, int32 isize) {
    struct entry_id ident;
    //
    if (fseek(fpiden, 0x00, SEEK_SET)) return -1;
    if (0 >= fread(&ident, sizeof (struct entry_id), 1, fpiden))
        return -1;
    uint32 sibling = ident.next_sibli;
    //
    ident.next_sibli = ainde;
    if (fseek(fpiden, 0x00, SEEK_SET)) return -1;
    if (0 >= fwrite(&ident, sizeof (struct entry_id), 1, fpiden))
        return -1;
    //
    ident.prev_sibli = 0x00;
    ident.next_sibli = sibling;
    if (fseek(fpiden, (sizeof (struct entry_id)+isize) * ainde, SEEK_SET))
        return -1;
    if (0 >= fwrite(&ident, sizeof (struct entry_id), 1, fpiden))
        return -1;
    //
    if (prev_sibli_modify(fpiden, sibling, isize, ainde))
        return -1;
    //
    return 0x00;
}

uint32 find_idle_iden(FILE *fpiden, int32 isize) {
    uint32 einde;
    struct entry_id ident;
    //
    if (fseek(fpiden, -(sizeof (struct entry_id)+isize), SEEK_END))
        return INVA_INDE_VALU;
    off_t eose = ftell(fpiden);
    if (0 >= fread(&ident, sizeof (struct entry_id), 1, fpiden))
        return INVA_INDE_VALU;
    //
    if (INVA_INDE_VALU != ident.next_sibli) {
        einde = ident.next_sibli;
        ident.next_sibli = find_next_sibli(fpiden, ident.next_sibli, isize);
        if (fseek(fpiden, eose, SEEK_SET)) return INVA_INDE_VALU;
        if (0 >= fwrite(&ident, sizeof (struct entry_id), 1, fpiden))
            return INVA_INDE_VALU;
    } else {
        if (fill_idle_iden(fpiden, isize)) return INVA_INDE_VALU;
        einde = eose / (sizeof (struct entry_id)+isize);
    }
    //
    if (appe_activ_iden(fpiden, einde, isize)) return INVA_INDE_VALU;
    //
    return einde;
}

//

static int32 dele_activ_iden(FILE *fpiden, int32 ainde, int32 isize) {
    struct entry_id ident;
    //
    if (fseek(fpiden, 0x00, SEEK_SET)) return -1;
    if (0 >= fread(&ident, sizeof (struct entry_id), 1, fpiden))
        return -1;
    //
    if (ainde == ident.next_sibli) {
        uint32 sibling = find_next_sibli(fpiden, ainde, isize);
        ident.next_sibli = sibling;
        if (fseek(fpiden, 0x00, SEEK_SET)) return -1;
        if (0 >= fwrite(&ident, sizeof (struct entry_id), 1, fpiden))
            return -1;
        //
        if (prev_sibli_modify(fpiden, sibling, isize, ainde))
            return -1;
    } else {
        if (fseek(fpiden, (sizeof (struct entry_id)+isize) * ainde, SEEK_SET)) return -1;
        if (0 >= fread(&ident, sizeof (struct entry_id), 1, fpiden))
            return -1;
        //
        if (next_sibli_modify(fpiden, ident.prev_sibli, isize, ident.next_sibli))
            return -1;
        if (prev_sibli_modify(fpiden, ident.next_sibli, isize, ident.prev_sibli))
            return -1;
    }
    //
    return 0x00;
}

uint32 addi_idle_iden(FILE *fpiden, int32 ainde, int32 isize) {
    if (dele_activ_iden(fpiden, ainde, isize)) return 0x01;
    //
    struct entry_id ident;
    if (fseek(fpiden, -(sizeof (struct entry_id)+isize), SEEK_END)) return 0x01;
    off_t eose = ftell(fpiden);
    if (0 >= fread(&ident, sizeof (struct entry_id), 1, fpiden)) return 0x01;
    //
    if (next_sibli_modify(fpiden, ainde, isize, ident.next_sibli))
        return -1;
    ident.next_sibli = ainde;
    if (fseek(fpiden, eose, SEEK_SET)) return 0x01;
    if (0 >= fwrite(&ident, sizeof (struct entry_id), 1, fpiden)) return 0x01;
    //
    fflush(fpiden);
    return 0x00;
}

//

uint32 read_iden_data(char *idata, int32 isize, FILE *fpiden, uint32 ainde) {
    off_t eose = (sizeof (struct entry_id)+isize) * ainde;
    if (fseek(fpiden, eose + sizeof (struct entry_id), SEEK_SET))
        return INVA_INDE_VALU;
    //
    if (0 >= fread(idata, isize, 1, fpiden))
        return INVA_INDE_VALU;
    //
    return ainde;
}

//

uint32 write_iden_data(FILE *fpiden, uint32 ainde, char *idata, int32 isize) {
    off_t eose = (sizeof (struct entry_id)+isize) * ainde;
    if (fseek(fpiden, eose + sizeof (struct entry_id), SEEK_SET))
        return INVA_INDE_VALU;
    //
    if (0 >= fwrite(idata, isize, 1, fpiden))
        return INVA_INDE_VALU;
    //
    fflush(fpiden);
    return ainde;
}

//


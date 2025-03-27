#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/file.h>

#include "riv_common.h"
#include "riv_stru.h"
#include "rive_utility.h"


#define INIT_ATTRIB_ENTRY(ENTRY) \
        memset(&ENTRY, '\0', sizeof(struct entry_id)); \
        ENTRY.sibling = INVA_INDE_VALU;

uint32 fill_idle_iden(FILE *fpiden, int32 line_size) {
    struct entry_id ident;
    INIT_ATTRIB_ENTRY(ident)
    if (fseeko64(fpiden, 0x00, SEEK_END)) return 0x01;
    if (0 >= fwrite(&ident, sizeof (struct entry_id), 1, fpiden)) return 0x01;
    //
    char *line_data = (char *) malloc(line_size);
    memset(line_data, '\0', line_size);
    if (0 >= fwrite(line_data, line_size, 1, fpiden)) {
        free(line_data);
        return 0x01;
    }
    free(line_data);
    //
    return 0x00;
}

//

uint64 find_sibli_iden(FILE *fpiden, uint64 ainde) {
    /*
        struct file_id ident;
        //
        uint64 eose = sizeof (struct file_id)*ainde;
        if (fseeko64(fpiden, eose, SEEK_SET)) return INVA_INDE_VALU;
        if (0 >= fread(&ident, sizeof (struct file_id), 1, fpiden))
            return INVA_INDE_VALU;
        uint64 sibli = ident.sibling;
        //
        memset(&ident.time_stamp, 0, sizeof (time_t));
        if (fseeko64(fpiden, eose, SEEK_SET)) return INVA_INDE_VALU;
        if (0 >= fwrite(&ident, sizeof (struct file_id), 1, fpiden))
            return INVA_INDE_VALU;
     */
    //
    // return sibli;
    return 0x00;
}

uint64 find_idle_iden(FILE *fpiden) {
    /*
        uint64 eind;
        struct file_id ident;
        //
        if (fseeko64(fpiden, -(__off64_t)sizeof (struct file_id), SEEK_END))
            return INVA_INDE_VALU;
        __off64_t eose = ftello64(fpiden);
        if (0 >= fread(&ident, sizeof (struct file_id), 1, fpiden))
            return INVA_INDE_VALU;
        //
        if (INVA_INDE_VALU != ident.sibling) {
            eind = ident.sibling;
            ident.sibling = find_sibli_iden(fpiden, ident.sibling);
            if (fseeko64(fpiden, eose, SEEK_SET)) return INVA_INDE_VALU;
            if (0 >= fwrite(&ident, sizeof (struct file_id), 1, fpiden))
                return INVA_INDE_VALU;
        } else {
            if (fill_idle_iden(fpiden)) return INVA_INDE_VALU;
            eind = eose / sizeof (struct file_id);
        }
     */
    //
    // return eind;
    return 0x00;
}

uint32 add_idle_iden(FILE *fpiden, uint64 ainde) {
    /*
        struct file_id ident;
        //
        if (fseeko64(fpiden, -(__off64_t)sizeof (struct file_id), SEEK_END)) return 0x01;
        __off64_t eose = ftello64(fpiden);
        if (0 >= fread(&ident, sizeof (struct file_id), 1, fpiden)) return 0x01;
        //
        iden_sibli_modify(fpiden, ainde, ident.sibling);
        ident.sibling = ainde;
        if (fseeko64(fpiden, eose, SEEK_SET)) return 0x01;
        if (0 >= fwrite(&ident, sizeof (struct file_id), 1, fpiden)) return 0x01;
     */
    //
    return 0x00;
}

/*
uint64 iden_read(struct file_id *pattb, FILE *fpiden, uint64 ainde) {
    if (fseeko64(fpiden, sizeof (struct file_id)*ainde, SEEK_SET))
        return INVA_INDE_VALU;
    if (0 >= fread(pattb, sizeof (struct file_id), 1, fpiden))
        return INVA_INDE_VALU;
    return ainde;
}
 */

/*
uint64 iden_write(FILE *fpiden, struct file_id *pattb, uint64 ainde) {
    if (fseeko64(fpiden, sizeof (struct file_id)*ainde, SEEK_SET))
        return INVA_INDE_VALU;
    if (0 >= fwrite(pattb, sizeof (struct file_id), 1, fpiden))
        return INVA_INDE_VALU;

    return ainde;
}
 */

uint64 iden_sibli_modify(FILE *fpiden, uint64 ainde, uint64 sibling) {
    /*
        struct file_id ident;
        //
        uint64 eose = sizeof (struct file_id) * ainde;
        if (fseeko64(fpiden, eose, SEEK_SET)) return INVA_INDE_VALU;
        if (0 >= fread(&ident, sizeof (struct file_id), 1, fpiden))
            return INVA_INDE_VALU;
        uint64 osibl = ident.sibling;
        //
        ident.sibling = sibling;
        if (fseeko64(fpiden, eose, SEEK_SET)) return INVA_INDE_VALU;
        if (0 >= fwrite(&ident, sizeof (struct file_id), 1, fpiden))
            return INVA_INDE_VALU;
     */
    //
    // return osibl;
    return 0x00;
}

uint64 iden_file_modify(FILE *fpiden, uint64 ainde, char *new_name) {
    /*
        struct file_id ident;
        //
        uint64 eose = sizeof (struct file_id) * ainde;
        if (fseeko64(fpiden, eose, SEEK_SET)) return INVA_INDE_VALU;
        if (0 >= fread(&ident, sizeof (struct file_id), 1, fpiden))
            return INVA_INDE_VALU;
        //
        strcpy(ident.file_name, new_name);
        if (fseeko64(fpiden, eose, SEEK_SET)) return INVA_INDE_VALU;
        if (0 >= fwrite(&ident, sizeof (struct file_id), 1, fpiden))
            return INVA_INDE_VALU;
     */
    //
    // return ainde;
    return 0x00;
}

//

/*
uint64 find_sibli_chks(FILE *fpchks, uint64 cinde) {
    struct ckchks cchks;
    if (INVA_INDE_VALU == cinde) return INVA_INDE_VALU;
    if (fseeko64(fpchks, sizeof (struct ckchks)*cinde, SEEK_SET))
        return INVA_INDE_VALU;
    if (0 >= fread(&cchks, sizeof (struct ckchks), 1, fpchks))
        return INVA_INDE_VALU;
    return cchks.sibling;
}

uint64 find_next_chks(FILE *fpchks, uint64 cinde) {
    struct ckchks cchks;
    //
    uint64 eose = sizeof (struct ckchks) * cinde;
    if (fseeko64(fpchks, eose, SEEK_SET)) return INVA_INDE_VALU;
    if (0 >= fread(&cchks, sizeof (struct ckchks), 1, fpchks))
        return INVA_INDE_VALU;
    uint64 sibli = cchks.sibling;
    //
    memset(&cchks.time_stamp, 0, sizeof (time_t));
    cchks.sibling = INVA_INDE_VALU;
    if (fseeko64(fpchks, eose, SEEK_SET)) return INVA_INDE_VALU;
    if (0 >= fwrite(&cchks, sizeof (struct ckchks), 1, fpchks))
        return INVA_INDE_VALU;
    //
    return sibli;
}

uint64 find_idle_chks(FILE *fpchks) {
    uint64 eind;
    struct ckchks cchks;
    //
    if (fseeko64(fpchks, -(__off64_t)sizeof (struct ckchks), SEEK_END))
        return INVA_INDE_VALU;
    __off64_t eose = ftello64(fpchks);
    if (0 >= fread(&cchks, sizeof (struct ckchks), 1, fpchks))
        return INVA_INDE_VALU;
    //
    if (INVA_INDE_VALU != cchks.sibling) {
        eind = cchks.sibling;
        cchks.sibling = find_next_chks(fpchks, cchks.sibling);
        //
        if (fseeko64(fpchks, eose, SEEK_SET)) return INVA_INDE_VALU;
        if (0 >= fwrite(&cchks, sizeof (struct ckchks), 1, fpchks))
            return INVA_INDE_VALU;
    } else {
        if (fill_idle_chks(fpchks)) return INVA_INDE_VALU;
        eind = eose / sizeof (struct ckchks);
    }
    //
    return eind;
}

uint32 add_idle_chks(FILE *fpchks, uint64 chks_hind) {
    struct ckchks cchks;
    //
    if (fseeko64(fpchks, -(__off64_t)sizeof (struct ckchks), SEEK_END)) return 0x01;
    __off64_t eose = ftello64(fpchks);
    if (0 >= fread(&cchks, sizeof (struct ckchks), 1, fpchks)) return 0x01;
    //
    if (INVA_INDE_VALU != cchks.sibling) {
        uint64 nind, sibli;
        for (nind = chks_hind; INVA_INDE_VALU != (sibli = find_sibli_chks(fpchks, nind)); nind = sibli);
        chks_sibli_modify(fpchks, nind, cchks.sibling);
    }
    //
    cchks.sibling = chks_hind;
    if (fseeko64(fpchks, eose, SEEK_SET)) return 0x01;
    if (0 >= fwrite(&cchks, sizeof (struct ckchks), 1, fpchks)) return 0x01;
    //
    return 0x00;
}

uint64 chks_read(struct ckchks *pcks, FILE *fpchks, uint64 cinde) {
    if (INVA_INDE_VALU == cinde) return INVA_INDE_VALU;
    if (fseeko64(fpchks, sizeof (struct ckchks)*cinde, SEEK_SET))
        return INVA_INDE_VALU;
    if (0 >= fread(pcks, sizeof (struct ckchks), 1, fpchks))
        return INVA_INDE_VALU;
    return cinde;
}

uint64 chks_write(FILE *fpchks, struct ckchks *pcks, uint64 cinde) {
    if (INVA_INDE_VALU == cinde) return INVA_INDE_VALU;
    if (fseeko64(fpchks, sizeof (struct ckchks)*cinde, SEEK_SET))
        return INVA_INDE_VALU;
    if (0 >= fwrite(pcks, sizeof (struct ckchks), 1, fpchks))
        return INVA_INDE_VALU;
    return cinde;
}

uint64 chks_sibli_modify(FILE *fpchks, uint64 cinde, uint64 sibling) {
    struct ckchks cchks;
    //
    if (INVA_INDE_VALU == cinde) return INVA_INDE_VALU;
    uint64 eose = sizeof (struct ckchks) * cinde;
    if (fseeko64(fpchks, eose, SEEK_SET)) return INVA_INDE_VALU;
    if (0 >= fread(&cchks, sizeof (struct ckchks), 1, fpchks))
        return INVA_INDE_VALU;
    uint64 osibl = cchks.sibling;
    //
    cchks.sibling = sibling;
    if (fseeko64(fpchks, eose, SEEK_SET)) return INVA_INDE_VALU;
    if (0 >= fwrite(&cchks, sizeof (struct ckchks), 1, fpchks))
        return INVA_INDE_VALU;
    //
    return osibl;
}

uint64 chks_stamp_modify(FILE *fpchks, time_t stamp, uint64 cinde) {
    struct ckchks ccks;
    //
    if (INVA_INDE_VALU == cinde) return INVA_INDE_VALU;
    uint64 eose = sizeof (struct ckchks) * cinde;
    if (fseeko64(fpchks, eose, SEEK_SET)) return INVA_INDE_VALU;
    if (0 >= fread(&ccks, sizeof (struct ckchks), 1, fpchks)) 
        return INVA_INDE_VALU;
    //
    ccks.time_stamp = stamp;
    if (fseeko64(fpchks, eose, SEEK_SET)) return INVA_INDE_VALU;
    if (0 >= fwrite(&ccks, sizeof (struct ckchks), 1, fpchks))
        return INVA_INDE_VALU;
    //
    return ccks.sibling;
}

//

void chunk_chks(unsigned char *pchks, FILE *fpchks, uint64 file_size, uint64 cinde) {
    struct pmap64 *buffer;
    uint64 inde, offset_end;
    RIV_MD5_CTX md;
    int32 remainder;

    uint64 offset = ((uint64)cinde) << 22;
    buffer = (struct pmap64 *) pmap_file64(fpchks, file_size, MAX_MAP_SIZE, CHKS_CHUNK);
    offset_end = offset + CHUNK_SIZE;
    if (offset_end > file_size) offset_end = file_size;

    RIV_MD5Init(&md);
    for (inde = offset; inde + CHKS_CHUNK <= offset_end; inde += CHKS_CHUNK) {
        RIV_MD5Update(&md, (uchar *) pmap_ptr64(buffer, inde, CHKS_CHUNK), CHKS_CHUNK);
    }
    remainder = (int32) (offset_end - inde);
    if (remainder > 0)
        RIV_MD5Update(&md, (uchar *) pmap_ptr64(buffer, inde, remainder), remainder);
    RIV_MD5Final(&md);
    memcpy(pchks, md.digest, MD5_DIGEST_LEN);

    unpmap_file64(buffer);
}
 */

//


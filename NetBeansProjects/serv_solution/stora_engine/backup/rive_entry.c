#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/file.h>

#include "riv_common.h"
#include "rive_utility.h"
#include "rive_entry.h"


/*
uint64 init_identi(FILE *fpiden, char *file_name) {
    struct file_id ident;
    memset(&ident, 0, sizeof (struct file_id));
    strcpy(ident.file_name, file_name);
    uint64 ainde = find_idle_iden(fpiden);
    iden_write(fpiden, &ident, ainde);
    return ainde;
}
*/
//

/*
uint64 init_cchks(FILE *fpchks) {
    struct ckchks cchks;
    memset(&cchks, 0, sizeof (struct ckchks));
    uint64 cinde = find_idle_chks(fpchks);
    chks_write(fpchks, &cchks, cinde);
    return cinde;
}
*/

// for test

/*
uint32 cchks_inde_numbe(FILE *fpchks, uint64 chks_hind) {
    struct ckchks cchks;
    uint32 ind;
    cchks.sibling = chks_hind;
    for (ind = 0; INVA_INDE_VALU != cchks.sibling; ind++) {
fprintf(stderr, "ind:%u cchks.sibling:%llu \n", ind, cchks.sibling);
        chks_read(&cchks, fpchks, cchks.sibling);
    }
    return ind;
}
*/

/*
void identi_idle_link(FILE *fpiden) {
    struct file_id ident;
    if (fseeko64(fpiden, -(__off64_t)sizeof (struct file_id), SEEK_END))
        return;
    __off64_t eose = ftello64(fpiden);
    uint64 eind = eose / sizeof (struct file_id);
    if (0 >= fread(&ident, sizeof (struct file_id), 1, fpiden))
        return;
fprintf(stderr, "file eind:%llu sibling:%llu\n", eind, ident.sibling);
    for (; INVA_INDE_VALU != ident.sibling;) {
fprintf(stderr, "ident.sibling:%llu\n", ident.sibling);
        iden_read(&ident, fpiden, ident.sibling);
    }
}
*/

/*
void cchks_idle_link(FILE *fpchks) {
    struct ckchks cchks;
    if (fseeko64(fpchks, -(__off64_t)sizeof (struct ckchks), SEEK_END))
        return;
    __off64_t eose = ftello64(fpchks);
    uint64 eind = eose / sizeof (struct ckchks);
    if (0 >= fread(&cchks, sizeof (struct ckchks), 1, fpchks))
        return;
fprintf(stderr, "chunk eind:%llu sibling:%llu\n", eind, cchks.sibling);
    for (; INVA_INDE_VALU != cchks.sibling;) {
fprintf(stderr, "cchks.sibling:%llu\n", cchks.sibling);
        chks_read(&cchks, fpchks, cchks.sibling);
    }
}
*/

//

/*
uint64 cchks_inde_read(struct ckchks *pchks, FILE *fpchks, uint64 chks_hind, uint32 cinde) {
    uint64 ckind;
    uint32 ind;
    if (INVA_INDE_VALU == chks_hind) return INVA_INDE_VALU;
    pchks->sibling = chks_hind;
    for (ind = 0; cinde >= ind; ind++) {
        ckind = chks_read(pchks, fpchks, pchks->sibling);
        if (INVA_INDE_VALU == ckind) break;
    }
    return ckind;
}
*/

/*
uint64 reset_ckchks_length(FILE *fpchks, uint64 chks_hind, uint32 old_clen, uint32 new_clen) {
    int32 diff_clen = new_clen - old_clen;
    uint32 ind;
    uint64 eind, nind, sibli;
    //
    if (0 < diff_clen) { // make long then old
        for (nind = chks_hind; INVA_INDE_VALU != (sibli = find_sibli_chks(fpchks, nind)); nind = sibli);
        //
        eind = find_idle_chks(fpchks);
        if (INVA_INDE_VALU == nind) chks_hind = eind;
        chks_sibli_modify(fpchks, nind, eind);
        nind = eind;
        //
        for (ind = 0x01; diff_clen > ind; ind++) {
            eind = find_idle_chks(fpchks);
            // fprintf(stderr, "nind:%llu eind:%llu\n", nind, eind);
            chks_sibli_modify(fpchks, nind, eind);
            nind = eind;
        }
    } else if (0 > diff_clen) { // make short
        nind = INVA_INDE_VALU;
        for (sibli = chks_hind, ind = 0x00; new_clen > ind; ind++) {
            nind = sibli;
            sibli = find_sibli_chks(fpchks, sibli);
        }
        add_idle_chks(fpchks, find_sibli_chks(fpchks, sibli));
        if (INVA_INDE_VALU == nind) chks_hind = INVA_INDE_VALU;
        else chks_sibli_modify(fpchks, nind, INVA_INDE_VALU);
    }
    //
    return chks_hind;
}
*/
//

// for test

/*
void p_chks(unsigned char *md5_chks, int inde) {
    char chks_str[64];
    int ind;
    for (ind = 0; ind < MD5_DIGEST_LEN; ind++)
        sprintf(chks_str + ind * 2, "%02x", md5_chks[ind]);
    chks_str[32] = '\0';
fprintf(stderr, "inde:%d chks:%s\n", inde, chks_str);
}
*/

// 0:pass 0x01:no content 0x02:not found 0x03:processing 0x04:server error
/*
uint32 file_chks_update(FILE *fpchks, char *file_name, uint64 chks_hind, struct stat64 *pstat) {
    struct ckchks cchks;
    uint64 ckind;
    uint32 ind, update_tatol = 0x01;
    //
    if (INVA_INDE_VALU == chks_hind) return 0x01;
    FILE *fpchuk = fopen64(file_name, "rb");
    if (!fpchuk) return 0x04;
    //
    cchks.sibling = chks_hind;
    for (ind = 0; INVA_INDE_VALU != cchks.sibling; ind++) {
        if (MAX_UPDATE_NUM < update_tatol) {
            if (fpchuk) fclose(fpchuk);
            return 0x03;
        }
        ckind = chks_read(&cchks, fpchks, cchks.sibling);
        if (pstat->st_mtime != cchks.time_stamp) {
            update_tatol++;
            chunk_chks(cchks.md5_chks, fpchuk, pstat->st_size, ind);
            cchks.time_stamp = pstat->st_mtime;
            chks_write(fpchks, &cchks, ckind);
fprintf(stderr, "update chks, ckind:%llu cchks.time_stamp:%ld\n", ckind, cchks.time_stamp);
        }
    }
    //
    if (fpchuk) fclose(fpchuk);
    return 0x00;
}
*/

// 0:pass 0x01:no content 0x02:not found 0x03:processing 0x04:server error
/*
uint32 file_chks_verify(FILE *fpchks, char *file_name, uint64 chks_hind, struct stat64 *pstat) {
    struct ckchks cchks;
    uint64 ckind;
    uint32 ind, verify_tatol = 0x01;
    //
    if (INVA_INDE_VALU == chks_hind) return 0x01;
    FILE *fpchuk = fopen64(file_name, "rb");
    if (!fpchuk) return 0x04;
    //
    cchks.sibling = chks_hind;
    for (ind = 0; INVA_INDE_VALU != cchks.sibling; ind++) {
        if (MAX_VERIFY_NUM < verify_tatol) {
            if (fpchuk) fclose(fpchuk);
            return 0x03;
        }
        ckind = chks_read(&cchks, fpchks, cchks.sibling);
        if (INVA_TIME_VALU != cchks.time_stamp) {
            verify_tatol++;
            chunk_chks(cchks.md5_chks, fpchuk, pstat->st_size, ind);
            cchks.time_stamp = INVA_TIME_VALU;
            chks_write(fpchks, &cchks, ckind);
fprintf(stderr, "update chks, ckind:%llu cchks.time_stamp:%ld\n", ckind, cchks.time_stamp);
        }
    }
    // succ: refresh time stamp
    if (fpchuk) fclose(fpchuk);
    ckind = chks_hind;
    while (INVA_INDE_VALU != ckind) {
fprintf(stderr, "modify pstat->st_mtime:%ld ckind:%llu\n", pstat->st_mtime, ckind);
        ckind = chks_stamp_modify(fpchks, pstat->st_mtime, ckind);
    }
    //
    return 0x00;
}
*/

//
// 0:pass 0x01:no content 0x02:not found 0x03:processing 0x04:server error
/*
uint32 file_chunk_update(FILE *fpchks, uint64 *ind_pos, char *file_name, uint64 chks_hind, uint32 cinde, struct stat64 *pstat) {
    struct ckchks cchks;
    uint64 ckind;
    uint32 ind, update_tatol = 0x01;
    //
    if (INVA_INDE_VALU == chks_hind) return 0x01;
    cchks.sibling = chks_hind;
    for (ind = 0; cinde > ind; ind++) {
        ckind = chks_read(&cchks, fpchks, cchks.sibling);
        if (INVA_INDE_VALU == ckind) return 0x02;
    }
    //
    FILE *fpchuk = fopen64(file_name, "rb");
    if (!fpchuk) return 0x04;
    //
    if (ind_pos) *ind_pos = cchks.sibling;
    for (; INVA_INDE_VALU != cchks.sibling; ind++) {
        if (MAX_UPDATE_NUM < update_tatol) {
            if (fpchuk) fclose(fpchuk);
            return 0x03;
        }
        ckind = chks_read(&cchks, fpchks, cchks.sibling);
        if (pstat->st_mtime != cchks.time_stamp) {
            update_tatol++;
            chunk_chks(cchks.md5_chks, fpchuk, pstat->st_size, ind);
            cchks.time_stamp = pstat->st_mtime;
            chks_write(fpchks, &cchks, ckind);
fprintf(stderr, "update chks, ckind:%llu cchks.time_stamp:%ld\n", ckind, cchks.time_stamp);
        }
    }
    //
    if (fpchuk) fclose(fpchuk);
    return 0x00;
}
*/

// 0:pass 0x01:no content 0x02:not found 0x03:processing 0x04:server error
/*
uint32 file_chunk_verify(FILE *fpchks, uint64 *ind_pos, char *file_name, uint64 chks_hind, uint32 cinde, struct stat64 *pstat) {
    struct ckchks cchks;
    uint64 ckind;
    uint32 ind, verify_tatol = 0x01;
    //
    if (INVA_INDE_VALU == chks_hind) return 0x01;
    cchks.sibling = chks_hind;
    for (ind = 0; cinde > ind; ind++) {
        ckind = chks_read(&cchks, fpchks, cchks.sibling);
        if (INVA_INDE_VALU == ckind) return 0x02;
    }
    //
    FILE *fpchuk = fopen64(file_name, "rb");
    if (!fpchuk) return 0x04;
    //
    uint64 inde = cchks.sibling;
    for (; INVA_INDE_VALU != cchks.sibling; ind++) {
        if (MAX_VERIFY_NUM < verify_tatol) {
            if (fpchuk) fclose(fpchuk);
            return 0x03;
        }
        ckind = chks_read(&cchks, fpchks, cchks.sibling);
        if (INVA_TIME_VALU != cchks.time_stamp) {
            verify_tatol++;
            chunk_chks(cchks.md5_chks, fpchuk, pstat->st_size, ind);
            cchks.time_stamp = INVA_TIME_VALU;
            chks_write(fpchks, &cchks, ckind);
            // fprintf(stderr, "verify chks, ckind:%llu cchks.time_stamp:%ld\n", ckind, cchks.time_stamp);
        }
    }
    // succ: refresh time stamp
    if (fpchuk) fclose(fpchuk);
    ckind = inde;
    while (INVA_INDE_VALU != ckind) {
        ckind = chks_stamp_modify(fpchks, pstat->st_mtime, ckind);
    }
    if (ind_pos) *ind_pos = inde;
    //
    return 0x00;
}

//

uint64 chunk_chks_update(FILE *fpchks, char *file_name, uint64 chks_hind, uint32 cinde, struct stat64 *pstat) {
    struct ckchks cchks;
    uint64 ckind;
    uint32 ind;
    //
    if (INVA_INDE_VALU == chks_hind) return INVA_INDE_VALU;
    cchks.sibling = chks_hind;
    for (ind = 0; cinde >= ind; ind++) {
        ckind = chks_read(&cchks, fpchks, cchks.sibling);
        if (INVA_INDE_VALU == ckind) return INVA_INDE_VALU;
    }
    //
    if (pstat->st_mtime != cchks.time_stamp) {
        FILE *fpchuk = fopen64(file_name, "rb");
        if (!fpchuk) return INVA_INDE_VALU;
        //
        chunk_chks(cchks.md5_chks, fpchuk, pstat->st_size, cinde);
        cchks.time_stamp = pstat->st_mtime;
        chks_write(fpchks, &cchks, ckind);
fprintf(stderr, "update chks, cinde:%u cchks.time_stamp:%ld\n", cinde, cchks.time_stamp);
        //
        if (fpchuk) fclose(fpchuk);
    }
    //
    return ckind;
}

uint64 chunk_chks_verify(FILE *fpchks, char *file_name, uint64 chks_hind, uint32 cinde, struct stat64 *pstat) {
    struct ckchks cchks;
    uint64 ckind;
    uint32 ind;
    //
    if (INVA_INDE_VALU == chks_hind) return INVA_INDE_VALU;
    cchks.sibling = chks_hind;
    for (ind = 0; cinde >= ind; ind++) {
        ckind = chks_read(&cchks, fpchks, cchks.sibling);
        if (INVA_INDE_VALU == ckind) return INVA_INDE_VALU;
    }
    //
    FILE *fpchuk = fopen64(file_name, "rb");
    if (!fpchuk) return INVA_INDE_VALU;
    //
    chunk_chks(cchks.md5_chks, fpchuk, pstat->st_size, cinde);
    cchks.time_stamp = pstat->st_mtime;
    chks_write(fpchks, &cchks, ckind);
fprintf(stderr, "verify chks, cinde:%u cchks.time_stamp:%ld\n", cinde, cchks.time_stamp);
    //
    if (fpchuk) fclose(fpchuk);
    //
    return ckind;
}
*/

//

/*
uint64 repod_identi(FILE *fpiden, uint64 ainde, char *new_name) {
    struct file_id ident;
    //
    if (INVA_INDE_VALU == iden_read(&ident, fpiden, ainde))
        return INVA_INDE_VALU;
    strcpy(ident.file_name, new_name);
    uint64 hinde = find_idle_iden(fpiden);
    iden_write(fpiden, &ident, hinde);
    //
    return hinde;
}

uint64 repod_ckchks(FILE *fpchks, uint64 chks_hind) {
    struct ckchks cchks;
    uint64 hinde = INVA_INDE_VALU;
    uint64 sibli, ckind = INVA_INDE_VALU;
    //
    if (INVA_INDE_VALU == chks_hind) return INVA_INDE_VALU;
    for (cchks.sibling = chks_hind; INVA_INDE_VALU != cchks.sibling; ckind = sibli) {
        chks_read(&cchks, fpchks, cchks.sibling);
        sibli = find_idle_chks(fpchks);
        if (INVA_INDE_VALU == hinde) hinde = sibli;
        chks_write(fpchks, &cchks, sibli);
        chks_sibli_modify(fpchks, ckind, sibli);
    }
    //
    return hinde;
}
//

uint32 file_sha1_chks(unsigned char *file_chks, FILE *fpchks, uint64 chks_hind) {
    struct ckchks cchks;
    riv_sha1_ctx cx[1];
    int chk_value = 0x00;
    int cinde;
    //
    riv_sha1_begin(cx);
    cchks.sibling = chks_hind;
    for (cinde = 0; INVA_INDE_VALU != cchks.sibling; cinde++) {
        if (INVA_INDE_VALU == chks_read(&cchks, fpchks, cchks.sibling)) {
            chk_value = 0x01;
            break;
        }
        riv_sha1_hash(cchks.md5_chks, MD5_DIGEST_LEN, cx);
    }
    riv_sha1_end(file_chks, cx);
    //
    return chk_value;
}
*/

// for test

/*
char *chks_str(unsigned char *md5_chks) {
    static char chks_str[64];
    int ind;
    for (ind = 0; ind < MD5_DIGEST_LEN; ind++)
        sprintf(chks_str + ind * 2, "%02x", md5_chks[ind]);
    chks_str[32] = '\0';
    return chks_str;
}

char *int64_str(unsigned char *int64_chks) {
    static char chks_str[64];
    int ind;
    for (ind = 0; ind < 8; ind++)
        sprintf(chks_str + ind * 2, "%02x", int64_chks[ind]);
    chks_str[16] = '\0';
    return chks_str;
}
*/

/*
uint32 file_rive_sha1(FILE *fpriv, unsigned char *file_chks) {
    struct riv_sha1 rsha1;
    memcpy(rsha1.sha1_chks, file_chks, SHA1_DIGEST_LEN);
    if (0 >= fwrite(&rsha1, sizeof (struct riv_sha1), 1, fpriv))
        return 0x01;
    return 0x00;
}

uint32 file_rive_chks(FILE *fpriv, FILE *fpchks, uint64 ind_pos, uint32 cinde) {
    struct ckchks cchks;
    struct riv_chks rchks;
    uint32 ind;
    //
    cchks.sibling = ind_pos;
    for (ind = cinde; INVA_INDE_VALU != cchks.sibling; ind++) {
        // fprintf(stderr, "read chks cinde:%lld ind:%d\n", cchks.sibling, ind);
        if (INVA_INDE_VALU == chks_read(&cchks, fpchks, cchks.sibling))
            return 0x01;
        memcpy(rchks.md5_chks, cchks.md5_chks, MD5_DIGEST_LEN);
        rchks.offset = ((uint64) ind) << 22;
fprintf(stderr, "rchks.offset:%llx cchks.md5_chks:%s\n", rchks.offset, chks_str(cchks.md5_chks));
        if (0 >= fwrite(&rchks, sizeof (struct riv_chks), 1, fpriv)) return 0x01;
    }
    return 0x00;
}
*/

/*
uint32 chunk_rive_chks(FILE *fpriv, FILE *fpchks, uint64 ind_pos, uint32 cinde) {
    struct ckchks cchks;
    struct riv_chks rchks;
    //
    // fprintf(stderr, "read chks cinde:%u ind:%d\n", cinde, ind);
    if (INVA_INDE_VALU == chks_read(&cchks, fpchks, ind_pos))
        return 0x01;
    memcpy(rchks.md5_chks, cchks.md5_chks, MD5_DIGEST_LEN);
    rchks.offset = ((uint64) cinde) << 22;
fprintf(stderr, "rchks.offset:%llx cchks.md5_chks:%s\n", rchks.offset, chks_str(cchks.md5_chks));
    if (0 >= fwrite(&rchks, sizeof (struct riv_chks), 1, fpriv)) return 0x01;
    //
    return 0x00;
}
*/

/* 
 * File:   strz_utili.h
 * Author: James Xu
 *
 * Created on 2023.6.14, AM 9:39
 */

#ifndef STRZ_UTILI_H
#define STRZ_UTILI_H

#ifdef __cplusplus
extern "C" {
#endif

#define VARI_OBJE_SIZE                  0x40000  // 256K
#define STRZ_TYPE_OSEV                  0x00
#define STRZ_TYPE_USER                  0x0f
#define STRZ_TYPE_STAT                  0xf0


#pragma pack(1)

    struct _strz_t_ {
        unsigned char type; // 0x00:osev 0x0f:user 0xf0:stat
        char *data;
        unsigned long long slen; // string leng
        unsigned long long asiz; // alloc size
    };

#pragma pack()

    typedef struct _strz_t_ strz_t;

    //

#define strz(STRI) {STRZ_TYPE_STAT, STRI, sizeof(STRI) - 0x01, sizeof(STRI)}
#define none_strz {STRZ_TYPE_STAT, NULL, 0x00, 0x00}

#define stzdel(STRI) if((STRI)->data && (STRZ_TYPE_USER & (STRI)->type)) free((STRI)->data);

    //

    inline strz_t *stzcpy(strz_t *dest, char *src) {
        dest->slen = strlen(src);
        if ((dest->asiz < dest->slen) || (STRZ_TYPE_STAT & dest->type)) {
            if (VARI_OBJE_SIZE > dest->slen) {
                dest->asiz = 0x01 + dest->slen << 0x01;
            } else dest->asiz = 0x01 + dest->slen;
            if (STRZ_TYPE_USER & dest->type) {
                char *real_memo = (char *) realloc(dest->data, dest->asiz);
                if (!real_memo) return NULL;
                dest->data = real_memo;
            } else {
                dest->data = (char *) malloc(dest->asiz);
                if (!dest->data) return NULL;
            }
            dest->type = STRZ_TYPE_USER;
        }
        strcpy(dest->data, src);
        return dest;
    }

    inline strz_t *stzcat(strz_t *dest, char *src) {
        dest->slen = dest->slen + strlen(src);
        if ((dest->asiz < dest->slen) || (STRZ_TYPE_STAT & dest->type)) {
            if (VARI_OBJE_SIZE > dest->slen) {
                dest->asiz = 0x01 + dest->slen << 0x01;
            } else dest->asiz = 0x01 + dest->slen;
            if (STRZ_TYPE_USER & dest->type) {
                char *real_memo = (char *) realloc(dest->data, dest->asiz);
                if (!real_memo) return NULL;
                dest->data = real_memo;
            } else {
                dest->data = (char *) malloc(dest->asiz);
                if (!dest->data) return NULL;
            }
            dest->type = STRZ_TYPE_USER;
        }
        strcat(dest->data, src);
        return dest;
    }

    //

    inline strz_t *stzcop(strz_t *dest, strz_t *src) {
        if ((dest->asiz < src->slen) || (STRZ_TYPE_STAT & dest->type)) {
            if (VARI_OBJE_SIZE > src->slen) {
                dest->asiz = 0x01 + src->slen << 0x01;
            } else dest->asiz = 0x01 + src->slen;
            if (STRZ_TYPE_USER & dest->type) {
                char *real_memo = (char *) realloc(dest->data, dest->asiz);
                if (!real_memo) return NULL;
                dest->data = real_memo;
            } else {
                dest->data = (char *) malloc(dest->asiz);
                if (!dest->data) return NULL;
            }
            dest->type = STRZ_TYPE_USER;
        }
        strcpy(dest->data, src->data);
        dest->slen = src->slen;
        return dest;
    }

    inline strz_t *stzapp(strz_t *dest, strz_t *src) {
        dest->slen = dest->slen + src->slen;
        if ((dest->asiz < dest->slen) || (STRZ_TYPE_STAT & dest->type)) {
            if (VARI_OBJE_SIZE > dest->slen) {
                dest->asiz = 0x01 + dest->slen << 0x01;
            } else dest->asiz = 0x01 + dest->slen;
            if (STRZ_TYPE_USER & dest->type) {
                char *real_memo = (char *) realloc(dest->data, dest->asiz);
                if (!real_memo) return NULL;
                dest->data = real_memo;
            } else {
                dest->data = (char *) malloc(dest->asiz);
                if (!dest->data) return NULL;
            }
            dest->type = STRZ_TYPE_USER;
        }
        strcat(dest->data, src->data);
        return dest;
    }

#ifdef __cplusplus
}
#endif

#endif /* STRZ_UTILI_H */


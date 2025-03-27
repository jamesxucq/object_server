
/* 
 * File:   respo_conne.h
 * Author: James Xu
 *
 * Created on 2016.12.28, AM 9:17
 */

#ifndef RESPO_CONNE_H
#define RESPO_CONNE_H

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(1)

    struct _resp_head_ {
        unsigned char status_code; // STATUS_CODE
        unsigned long long content_length;
    };
#pragma pack()

    typedef struct _resp_head_ resp_head;

 #define RESPON_HEAD \
        unsigned char status_code; \
        unsigned long long content_length;
 
    // response

#define RESP_HEAD_BLEN  sizeof(resp_head)

#ifdef __cplusplus
}
#endif

#endif /* RESPO_CONNE_H */


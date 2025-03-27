
/* 
 * File:   UserKits.h
 * Author: James Xu
 *
 * Created on 2023.12.9, PM 10:06
 */

#ifndef USER_KITS_H
#define USER_KITS_H

namespace UserKits {
    // resp_data_t *objeRespo
#define EUTI_PKPS_OPEN(PKPS, RESPO, FMTSTR) paki_stream_open(FMTSTR, (void *) (RESPO)->resp_memo, (RESPO)->content_length, &PKPS)
#define EUTI_PKPS_CLOSE(PKPS) paki_stream_close(PKPS, NULL)
    int LoopDeseri(PK_PACK_STREAM *pkps, char *sFmtstr, ...);
};

#endif /* USER_KITS_H */


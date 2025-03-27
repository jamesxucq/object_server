
/* 
 * File:   field_unpack.h
 * Author: James Xu
 *
 * Created on 2023.6.1, PM 2:59
 */

#ifndef FIELD_UNPACK_H
#define FIELD_UNPACK_H

#ifdef __cplusplus
extern "C" {
#endif

    //

    char *field_item_unpack(char *last_dat, PK_PACK_STREAM *pkps, char fmtok, uint64_t sleng);

    //

    inline char *field_item_pass(char *last_dat, char fmtok, uint64_t sleng) {
        switch (fmtok) {
            case 'b':
                last_dat += sizeof (int8_t);
                break;
            case 't':
            case 'B':
                last_dat += sizeof (uint8_t);
                break;
            case 'h':
                last_dat += sizeof (int16_t);
                break;
            case 'H':
                last_dat += sizeof (uint16_t);
                break;
            case 'i':
            case 'l':
                last_dat += sizeof (int32_t);
                break;
            case 'I':
            case 'L':
                last_dat += sizeof (uint32_t);
                break;
            case 'q':
                last_dat += sizeof (int64_t);
                break;
            case 'Q':
            case 'r':
                last_dat += sizeof (uint64_t);
                break;
            case 'R':
                last_dat += sizeof (uint64_t);
                break;
            case 'f':
                last_dat += sizeof (float);
                break;
            case 'd':
                last_dat += sizeof (double);
                break;
            case 's':
                last_dat += sleng;
                break;
            case 'S':
                last_dat += sizeof (strz_t);
                break;
            case 'u':
            default:
                _LOG_WARN("default: fmtok");
                break;
        }
        return last_dat;
    }

    //

    char *field_item_pack(PK_PACK_STREAM *pkps, char *last_dat, char fmtok, uint64_t sleng);
    //

#ifdef __cplusplus
}
#endif

#endif /* FIELD_UNPACK_H */



/* 
 * File:   pack_stream.h
 * Author: james
 *
 * Created on 2022.10.7, AM 9:23
 */

#ifndef PACK_STREAM_H
#define PACK_STREAM_H

#include "packing.h"

#ifdef __cplusplus
extern "C" {
#endif

    // Streaming interface to packing.
    // This allows applications to pack or unpack records one field at a time.

    struct __pk_pack_stream {
        PK_PACK pack;
        const uint8_t *end;
        uint8_t *p;
        const uint8_t *start;
    };

#ifdef __cplusplus
}
#endif

#endif /* PACK_STREAM_H */


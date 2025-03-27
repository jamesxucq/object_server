/* 
 * File:   third_party.h
 * Author: James Xu
 */

#ifndef THIRD_PARTY_H
#define THIRD_PARTY_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    // #include "tiny_mmap.h"
    // #include "pmmap64.h"
    // #include "binary_logger.h"
    // #include "jemalloc/jemalloc.h"
#include "packing/packing.h"

    //

#ifdef _OSEV_SDKIT
#include "logger.h"
#include "dmmap64.h"
#include "pmmap64.h"
#endif /* _OSEV_SDKIT */

#ifdef _OSEV_SERV
// #include "logger.h"
#include "access_log.h"
#endif /* _OSEV_SERV */

#ifdef _CLANG_CLIE
#include "logger.h"
#include "dmmap64.h"
#endif /* _CLANG_CLIE */

#ifdef _OSEV_CLIT
#include "linenoise.h"
#endif /* _OSEV_CLIT */

#ifdef _CPLUSPLUS_CLIE
#include "logger.h"
#include "dmmap64.h"
#endif /* _CPLUSPLUS_CLIE */

#ifdef __cplusplus
}
#endif

#endif /* THIRD_PARTY_H */



/* 
 * File:   debug_funct_cpp.h
 * Author: James Xu
 *
 * Created on 2023.11.2, AM 9:20
 */

#ifndef DEBUG_FUNCT_CPP_H
#define DEBUG_FUNCT_CPP_H

#ifdef __cplusplus
extern "C" {
#endif
    
    //
#ifdef _DEBUG
#define CLIEPF printf
#else 
#define CLIEPF(fmt, ...)
#endif



#ifdef __cplusplus
}
#endif

#endif /* DEBUG_FUNCT_CPP_H */


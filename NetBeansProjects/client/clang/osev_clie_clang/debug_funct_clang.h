
/* 
 * File:   debug_funct_clang.h
 * Author: James Xu
 *
 * Created on 2022.11.18, AM 9:06
 */

#ifndef DEBUG_FUNCT_CLANG_H
#define DEBUG_FUNCT_CLANG_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    void p_md5sum(unsigned char *md5sum);
    
#ifdef _DEBUG
#define PRIN_md5sum p_md5sum
#else
#define PRIN_md5sum(...)
#endif


#ifdef __cplusplus
}
#endif

#endif /* DEBUG_FUNCT_CLANG_H */


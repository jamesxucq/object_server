
/* 
 * File:   debug_funct_au.h
 * Author: James Xu
 *
 * Created on 2022.11.16, AM 9:40
 */

#ifndef DEBUG_FUNCT_AU_H
#define DEBUG_FUNCT_AU_H



#ifdef __cplusplus
extern "C" {
#endif

    //

    void prin_md5sum(unsigned char *md5sum);
    
#ifdef _DEBUG
#define PRIN_md5sum prin_md5sum
#else
#define PRIN_md5sum(...)
#endif
    
#ifdef __cplusplus
}
#endif

#endif /* DEBUG_FUNCT_AU_H */


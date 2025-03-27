
/* 
 * File:   debug_funct_os.h
 * Author: James Xu
 *
 * Created on 2022.11.18, AM 9:10
 */

#ifndef DEBUG_FUNCT_OS_H
#define DEBUG_FUNCT_OS_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    void p_md5sum_os(unsigned char *md5sum);
    void p_authen(inte_value *inval);

#ifdef _DEBUG
#define PRIN_md5sum_os p_md5sum_os
#define PRIN_authen p_authen
#else
#define PRIN_md5sum_os(...)
#define PRIN_authen(...)
#endif

#ifdef __cplusplus
}
#endif

#endif /* DEBUG_FUNCT_OS_H */


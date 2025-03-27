
/* 
 * File:   rive_obje.h
 * Author: James Xu
 *
 * Created on 2023.5.5, AM 10:16
 */

#ifndef RIVE_OBJE_H
#define RIVE_OBJE_H

#ifdef __cplusplus
extern "C" {
#endif

    //
#define SHARP_ENAME "sharp" // only object server    
#define IMEMO_ENAME "imemo"
#define LEAP_ENAME "leap"
#define WTIGER_ENAME "wiredtiger" // wiredtiger

    // rive_ha *_stora_hande_tab_[] = {&sharp_ha, &imemo_ha, &leap_ha, &wtiger_ha, NULL};
    extern rive_ha *_stora_hande_tab_[];


#ifdef __cplusplus
}
#endif

#endif /* RIVE_OBJE_H */


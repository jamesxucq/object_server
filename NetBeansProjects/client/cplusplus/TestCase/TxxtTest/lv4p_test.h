
/* 
 * File:   lv4p_test.h
 * Author: James Xu
 *
 * Created on 2023.11.10, PM 2:38
 */

#ifndef LV4P_TEST_H
#define LV4P_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    int LevFPEcho(OSEVConne &vmwaConne);
    //
    int LevFPCreate(OSEVConne &vmwaConne);
    int LevFPDrop(OSEVConne &vmwaConne);
    int LevFPUpdate(OSEVConne &vmwaConne);
    int LevFPInsert(OSEVConne &vmwaConne);
    int LevFPSearch(OSEVConne &vmwaConne);
    int LevFPInvoke(OSEVConne &vmwaConne);
    int LevFPFactory(OSEVConne &vmwaConne);

#ifdef __cplusplus
}
#endif

#endif /* LV4P_TEST_H */


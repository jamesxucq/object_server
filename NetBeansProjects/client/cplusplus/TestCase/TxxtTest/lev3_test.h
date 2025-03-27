
/* 
 * File:   lev3_test.h
 * Author: James Xu
 *
 * Created on 2023.11.10, PM 2:38
 */

#ifndef LEV3_TEST_H
#define LEV3_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

    //
    int LevThSearVecto(OSEVConne &vmwaConne);
    
    //
    int LevThObjeInserUpdat(OSEVConne &vmwaConne);
    
    //
    int LevThEcho(OSEVConne &vmwaConne);

    //
    int LevThCreate(OSEVConne &vmwaConne);
    int LevThDrop(OSEVConne &vmwaConne);
    int LevThUpdate(OSEVConne &vmwaConne);
    int LevThInsert(OSEVConne &vmwaConne);
    int LevThSearch(OSEVConne &vmwaConne);
    int LevThInvoke(OSEVConne &vmwaConne);
    

#ifdef __cplusplus
}
#endif

#endif /* LEV3_TEST_H */


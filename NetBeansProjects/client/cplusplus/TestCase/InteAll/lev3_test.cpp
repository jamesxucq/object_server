
#include <cstdlib>

using namespace std;

#include <vector>
using std::vector;

//
#include "earth_lv2p/EarthLvtpHeader.h"

//
#include "InteLevTh/LevTh_Create.h"
#include "InteLevTh/LevTh_Drop.h"
#include "InteLevTh/LevTh_Echo.h"
#include "InteLevTh/LevTh_Insert.h"
#include "InteLevTh/LevTh_Invoke.h"
#include "InteLevTh/LevTh_Search.h"
#include "InteLevTh/LevTh_Update.h"

//
#include "lev3_test.h"

//
// #define LEVTH_ECHO_TEST     0x01
// #define LEVTH_CREATE_TEST   0x01
// #define LEVTH_DROP_TEST     0x01
// #define LEVTH_INSERT_TEST   0x01
// #define LEVTH_UPDATE_TEST   0x01
// #define LEVTH_SEARCH_TEST   0x01
// #define LEVTH_INVOKE_TEST   0x01

//

int lev3_test(OSEVConne &vmwaConne) {
    // LevThEcho
#ifdef LEVTH_ECHO_TEST
    printf("--------------------------\n");
    if (LevThEcho(vmwaConne))
        printf("LevThEcho ERROR!\n");
#endif // LEVTH_ECHO_TEST

    // LevThCreate
#ifdef LEVTH_CREATE_TEST
    printf("--------------------------\n");
    if (LevThCreate(vmwaConne))
        printf("LevThCreate ERROR!\n");
#endif // LEVTH_CREATE_TEST

    // LevThDrop
#ifdef LEVTH_DROP_TEST
    printf("--------------------------\n");
    if (LevThDrop(vmwaConne))
        printf("LevThDrop ERROR!\n");
#endif // LEVTH_DROP_TEST

    // LevThUpdate
#ifdef LEVTH_UPDATE_TEST
    printf("--------------------------\n");
    if (LevThUpdate(vmwaConne))
        printf("LevThUpdate ERROR!\n");
#endif // LEVTH_UPDATE_TEST

    // LevThInsert
#ifdef LEVTH_INSERT_TEST
    printf("--------------------------\n");
    if (LevThInsert(vmwaConne))
        printf("LevThInsert ERROR!\n");
#endif // LEVTH_INSERT_TEST

    // LevThSearch
#ifdef LEVTH_SEARCH_TEST
    printf("--------------------------\n");
    if (LevThSearch(vmwaConne))
        printf("LevThSearch ERROR!\n");
#endif // LEVTH_SEARCH_TEST

    // LevThInvoke
#ifdef LEVTH_INVOKE_TEST
    printf("--------------------------\n");
    if (LevThInvoke(vmwaConne))
        printf("LevThInvoke ERROR!\n");
#endif // LEVTH_INVOKE_TEST
    //
    printf("--------------------------\n");
    return 0x00;
}










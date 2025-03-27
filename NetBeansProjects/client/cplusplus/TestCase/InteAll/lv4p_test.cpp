
#include <cstdlib>

using namespace std;

#include <vector>
using std::vector;

//
#include "earth_lv2p/EarthLvtpHeader.h"

//
#include "InteLevFP/LevFP_Create.h"
#include "InteLevFP/LevFP_Drop.h"
#include "InteLevFP/LevFP_Echo.h"
#include "InteLevFP/LevFP_Factory.h"
#include "InteLevFP/LevFP_Insert.h"
#include "InteLevFP/LevFP_Invoke.h"
#include "InteLevFP/LevFP_Search.h"
#include "InteLevFP/LevFP_Update.h"

//
#include "lv4p_test.h"

// #define LEVFP_ECHO_TEST     0x01
// #define LEVFP_CREATE_TEST   0x01
// #define LEVFP_DROP_TEST     0x01
#define LEVFP_INSERT_TEST   0x01
// #define LEVFP_UPDATE_TEST   0x01
// #define LEVFP_SEARCH_TEST   0x01
// #define LEVFP_INVOKE_TEST   0x01
// #define LEVFP_FACTORY_TEST  0x01

//

int lv4p_test(OSEVConne &vmwaConne) {
    // LevFPEcho
#ifdef LEVFP_ECHO_TEST
    printf("--------------------------\n");
    if (LevFPEcho(vmwaConne))
        printf("LevFPEcho ERROR!\n");
#endif // LEVFP_ECHO_TEST

    // LevFPCreate
#ifdef LEVFP_CREATE_TEST
    printf("--------------------------\n");
    if (LevFPCreate(vmwaConne))
        printf("LevThCreate ERROR!\n");
#endif // LEVFP_CREATE_TEST

    // LevFPDrop
#ifdef LEVFP_DROP_TEST
    printf("--------------------------\n");
    if (LevFPDrop(vmwaConne))
        printf("LevThDrop ERROR!\n");
#endif // LEVFP_DROP_TEST

    // LevFPUpdate
#ifdef LEVFP_UPDATE_TEST
    printf("--------------------------\n");
    if (LevFPUpdate(vmwaConne))
        printf("LevThUpdate ERROR!\n");
#endif // LEVFP_UPDATE_TEST

    // LevFPInsert
#ifdef LEVFP_INSERT_TEST
    printf("--------------------------\n");
    if (LevFPInsert(vmwaConne))
        printf("LevThInsert ERROR!\n");
#endif // LEVFP_INSERT_TEST

    // LevFPSearch
#ifdef LEVFP_SEARCH_TEST
    printf("--------------------------\n");
    if (LevFPSearch(vmwaConne))
        printf("LevThSearch ERROR!\n");
#endif // LEVFP_SEARCH_TEST

    // LevFPFactory
#ifdef LEVFP_FACTORY_TEST
    printf("--------------------------\n");
    if (LevFPFactory(vmwaConne))
        printf("LevThFactory ERROR!\n");
#endif // LEVFP_FACTORY_TEST

    // LevFPInvoke
#ifdef LEVFP_INVOKE_TEST
    printf("--------------------------\n");
    if (LevFPInvoke(vmwaConne))
        printf("LevThInvoke ERROR!\n");
#endif // LEVFP_INVOKE_TEST
    //
    printf("--------------------------\n");
    return 0x00;
}





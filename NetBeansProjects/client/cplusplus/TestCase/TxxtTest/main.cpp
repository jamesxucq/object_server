
/* 
 * File:   main.cpp
 * Author: James Xu
 *
 * Created on 2023.11.3, 上午9:18
 */

#include <cstdlib>

using namespace std;

#include <vector>
using std::vector;

//
#include "txxt.h"

//
#include "lev3_test.h"
#include "lv4p_test.h"
// object test

//

int main(int argc, char** argv) {
    // txxt类的版本号
    printf("clVersion:|%llu|\n", earth::lev2p::txxt::clVersion);
    // 本地检测服务器txxt类的属性变化计数
    printf("suChkVersiCount:|%u|\n", earth::lev2p::txxt::suChkVersiCount);
    printf("---------------------------------\n");
    /*
    // LevThObjeInserUpdat
        printf("---------------------------------\n");
        if (LevThObjeInserUpdat("dev1", "123abc", "192.168.0.127", 8848))
            printf("LevThObjeInserUpdat ERROR!\n");
     */
    // LevThSearVecto
    /*
            int inde = 0x00;
            for (; inde < 0x01; ++inde) {
                printf("--------------------------------- inde:%d\n", inde);
                if (LevThSearVecto("dev1", "123abc", "192.168.0.127", 8848))
                    printf("LevThSearVecto ERROR!\n");
                //
                printf("---------------------------------\n");
            }
     */
    // LevThEcho
    /*
        if (LevThEcho("dev1", "123abc", "192.168.0.127", 8848))
            printf("LevThEcho ERROR!\n");
        printf("---------------------------------\n");
        if (LevFPEcho("dev1", "123abc", "192.168.0.127", 8848))
            printf("LevFPEcho ERROR!\n");
     */
    //

    printf("---------------------------------\n");
    if (LevFPCreate("dev1", "123abc", "192.168.0.127", 8848))
        printf("LevThCreate ERROR!\n");
    printf("---------------------------------\n");
    if (LevThCreate("dev1", "123abc", "192.168.0.127", 8848))
        printf("LevThCreate ERROR!\n");
    printf("---------------------------------\n");

    /*
        printf("---------------------------------\n");
        if (LevThDrop("dev1", "123abc", "192.168.0.127", 8848))
            printf("LevThDrop ERROR!\n");
        printf("---------------------------------\n");
        if (LevFPDrop("dev1", "123abc", "192.168.0.127", 8848))
            printf("LevThDrop ERROR!\n");
        printf("---------------------------------\n");
     */
    /*
        printf("---------------------------------\n");
        if (LevThUpdate("dev1", "123abc", "192.168.0.127", 8848))
            printf("LevThUpdate ERROR!\n");
        printf("---------------------------------\n");
        if (LevFPUpdate("dev1", "123abc", "192.168.0.127", 8848))
            printf("LevThUpdate ERROR!\n");
        printf("---------------------------------\n");
     */
    /*
        printf("---------------------------------\n");
        if (LevThInsert("dev1", "123abc", "192.168.0.127", 8848))
            printf("LevThInsert ERROR!\n");
        printf("---------------------------------\n");
        if (LevFPInsert("dev1", "123abc", "192.168.0.127", 8848))
            printf("LevThInsert ERROR!\n");
        printf("---------------------------------\n");
     */
    /*
        printf("---------------------------------\n");
        if (LevThSearch("dev1", "123abc", "192.168.0.127", 8848))
            printf("LevThSearch ERROR!\n");
        printf("---------------------------------\n");
        if (LevFPSearch("dev1", "123abc", "192.168.0.127", 8848))
            printf("LevThSearch ERROR!\n");
        printf("---------------------------------\n");
     */
    /*
        printf("---------------------------------\n");
        if (LevThInvoke("dev1", "123abc", "192.168.0.127", 8848))
            printf("LevThInvoke ERROR!\n");
        printf("---------------------------------\n");
        if (LevFPInvoke("dev1", "123abc", "192.168.0.127", 8848))
            printf("LevThInvoke ERROR!\n");
        printf("---------------------------------\n");
     */
    /*
        printf("---------------------------------\n");
        if (LevFPFactory("dev1", "123abc", "192.168.0.127", 8848))
            printf("LevThFactory ERROR!\n");
        printf("---------------------------------\n");
     */
    //
    printf("---------------------------------\n");
    return 0x00;
}




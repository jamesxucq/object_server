
/* 
 * File:   main.cpp
 * Author: James Xu
 *
 * Created on 2023.12.9, PM 9:07
 */

#include <cstdlib>

using namespace std;

#include <string>
using std::string;

#include <vector>
using std::vector;

//
#include "earth_lv2p/EarthLvtpHeader.h"
#include "lev3_test.h"
#include "lv4p_test.h"

//
#define USER_NAME "dev1"
#define PASSWORD "123abc"
#define IP_ADDRESS "127.0.0.1"
#define PORT 8848
#define BASE_NAME "earth"

int main(int argc, char** argv) {
    printf("********************************* [FUNC]:main\n");
    // txxt类的版本号
    printf("clVersion:|%llu|\n", earth::lev2p::txxt::clVersion);
    // 本地检测服务器txxt类的属性变化计数
    printf("suChkAttribCount:|%u|\n", earth::lev2p::txxt::suChkAttribCount);
    // 构建一个服务器连接
    OSEVConne vmwaConne(USER_NAME, PASSWORD, IP_ADDRESS, PORT, BASE_NAME);
    printf("OSEVConne USER_NAME:  %s\n", USER_NAME);
    printf("          PASSWORD:   %s\n", PASSWORD);
    printf("          IP_ADDRESS: %s:%d\n", IP_ADDRESS, PORT);
    printf("          BASE_NAME:  %s\n", BASE_NAME);
    printf("********************************* [FUNC]:lev3_test\n");
    lev3_test(vmwaConne);
    printf("********************************* [FUNC]:lv4p_test\n");
    lv4p_test(vmwaConne);
    printf("********************************* END\n");
    //
    return 0x00;
}




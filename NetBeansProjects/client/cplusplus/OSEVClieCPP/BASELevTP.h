
/* 
 * File:   BASELevTP.h
 * Author: James Xu
 *
 * Created on 2023.11.3, AM 9:26
 */

#ifndef BASE_LVTPP_H
#define BASE_LVTPP_H

//
using namespace std;

#include <string>
using std::string;

#include <vector>
using std::vector;

//

class BASELevTP {
public:
    // OID BaseName ConneSocket
    osev_clie *mpOSEVClie;
public:
    BASELevTP();
    virtual ~BASELevTP();
};

#endif /* BASE_LVTPP_H */



/* 
 * File:   OSEVConne.h
 * Author: James Xu
 *
 * Created on 2023.10.2, AM 10:57
 */

#ifndef OSEV_CONNE_H
#define OSEV_CONNE_H

//
using namespace std;

#include <string>
using std::string;

// OSEVConne.h

class OSEVConne {
private:
    // UserName, Password, Address, Port, BaseName;
    osvp_auth moClieAuthe;
public:
    OSEVConne(const string &userName, const string &password, const string &address, int port, const string &database);
    OSEVConne(const OSEVConne& orig);
    virtual ~OSEVConne();
public:
    int GetBASELevFP(BASELevFP &objeLevFP);
    int GetBASELevTP(BASELevTP &objeLevTP, const string &lv2pName);
};

#endif /* OSEV_CONNE_H */


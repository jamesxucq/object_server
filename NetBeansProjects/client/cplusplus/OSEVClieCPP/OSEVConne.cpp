
/* 
 * File:   OSEVConne.cpp
 * Author: James Xu
 * 
 * Created on 2023.10.25, AM 10:57
 */

#include <vector>
using std::vector;

#include "third_party.h"
#include "osev_common/commo_header.h"
#include "utility/action_hmap.h"

#include "ClieMacro.h"
#include "ErcodClie.h"
#include "proto_conne/proto_conne.h"
#include "ChkLvtpAtti.h"
#include "ClieTokit/EntitKits.h"
#include "InvoRType.h"
#include "ClieTokit/InserKits.h"

#include "BASELevOn.h"
#include "BASELevTP.h"
#include "BASELevTh.h"
#include "BASELevFP.h"

#include "OSEVConne.h"
#include "debug_funct_cpp.h"

//

OSEVConne::OSEVConne(const string &userName, const string &password, const string &address, int port, const string &database) {
    strcpy(moClieAuthe.authe.user_name, (char *) userName.c_str());
    strcpy(moClieAuthe.authe.pass_word, (char *) password.c_str());
    strcpy(moClieAuthe.saddr.sin_addr, (char *) address.c_str());
    moClieAuthe.saddr.sin_port = port;
    strcpy(moClieAuthe.osev_base, (char *) database.c_str());
}

OSEVConne::OSEVConne(const OSEVConne& orig) {
}

OSEVConne::~OSEVConne() {
}

int OSEVConne::GetBASELevFP(BASELevFP &objeLevFP) {
    CLIEPF("[FUNC]:OSEVConne::GetBASELevFP => osev_clie_create\n");
    resp_data_t crea_resp;
    int creaValu = base_clie_create(&crea_resp, &objeLevFP.moOSEVClie, &moClieAuthe);
    if (creaValu) {
        OSCO_CLOSE(objeLevFP.moOSEVClie.conne_sock);
        CLIEPF("OSEV Client Create ERROR!\n");
        return creaValu;
    }
    // stroid(&objeLevFP.m_OID, crea_resp.resp_memo);
    strcpy(objeLevFP.moOSEVClie.clie_name, moClieAuthe.osev_base);
    OBID_BINARY_COPY(&objeLevFP.moOSEVClie.clie_obid, (osv_oid_t *) crea_resp.resp_memo)
            // CLIEPF("[DEBUG] osev_osdb:%s user_name:%s\n", authen->auth.osev_osdb, authen->auth.user_name);
#ifdef _DEBUG
            char temp[33];
#endif   
    CLIEPF("[DEBUG] objeLevFP.moOSEVClie.clie_obid:%s\n", oidstr(temp, &objeLevFP.moOSEVClie.clie_obid));
    CLIEPF("OSEV Client Create OK!\n");
    return 0x00;
}

//

int GetBASELevTP(BASELevTP &objeLevTP, const string &lv2pName) {
    //
    CLIEPF("OSEV Client Create OK!\n");
    return 0x00;
}

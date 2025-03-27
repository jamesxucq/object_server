
#include "../InvoRType.h"
#include "InserKits.h"

//

int InseKits::ChkInvalOBID(vector <IRKeyVal::RTypObid *> &kvObidVec) {
    vector <IRKeyVal::RTypObid *>::iterator iter;
    for (iter = kvObidVec.begin(); iter != kvObidVec.end(); ++iter) {
        if (IS_INVAL_OBID(&(*iter)->obje_obid))
            return -1;
    }
    //
    return 0x00;
}

//

int BuildKVMap(unordered_map <osv_oid_t, IRKeyVal::RTypObid *> &kvObidMap, vector <IRKeyVal::RTypObid *> &kvObidVec) {
    vector <IRKeyVal::RTypObid *>::iterator iter;
    for (iter = kvObidVec.begin(); iter != kvObidVec.end(); ++iter) {
        kvObidMap[(*iter)->ivalu] = (*iter);
    }
    //
    return 0x00;
}

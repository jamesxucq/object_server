
/* 
 * File:   InserKits.h
 * Author: James Xu
 *
 * Created on 2023.12.7, PM 4:37
 */

#ifndef INSER_KITS_H
#define INSER_KITS_H

//
using namespace std;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <unordered_map>
using std::unordered_map;

//

namespace InseKits {
    int ChkInvalOBID(vector <IRKeyVal::RTypObid *> &kvObidVec);
    template <class T> int RefreshOBID(vector <T *> &inserVec, vector <IRKeyVal::RTypObid *> &kvObidVec);
};

//

namespace std {

    template <> struct hash<osv_oid_t> {
    public:

        size_t operator()(const osv_oid_t &o) const {
            int i, l;
            unsigned long ret = 0;
            unsigned short *s;
            l = (sizeof (osv_oid_t) + 1) / 2;
            s = (unsigned short *) &o;

            for (i = 0; i < l; ++i)
                ret ^= s[i] << (i & 0x0f);
            //
            return (ret);
        }
    };

    template <> struct equal_to<osv_oid_t> {
    public:

        bool operator()(const osv_oid_t &o1, const osv_oid_t &o2) const {
            return (((osv_oid_i *) & o1)->stoid == ((osv_oid_i *) & o2)->stoid \
                    && (&o1)->osev_unique == (&o2)->osev_unique);
        }
    };
};


//

int BuildKVMap(unordered_map <osv_oid_t, IRKeyVal::RTypObid *> &kvObidMap, vector <IRKeyVal::RTypObid *> &kvObidVec);

//

template <class T> int InseKits::RefreshOBID(vector <T *> &inserVec, vector <IRKeyVal::RTypObid *> &kvObidVec) {
    unordered_map <osv_oid_t, IRKeyVal::RTypObid *> kvObidMap;
    if (BuildKVMap(kvObidMap, kvObidVec))
        return -1;
    //
    class vector <T *>::iterator inse_it;
    unordered_map <osv_oid_t, IRKeyVal::RTypObid *>::iterator kv_it;
    for (inse_it = inserVec.begin(); inse_it != inserVec.end(); ++inse_it) {
        kv_it = kvObidMap.find((*inse_it)->obje_obid);
        if (kvObidMap.end() != kv_it) {
            OBID_BINARY_COPY(&(*inse_it)->obje_obid, &(kv_it->second)->obje_obid)
        }
    }
    //
    return 0x00;
}

#endif /* INSER_KITS_H */


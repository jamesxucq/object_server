#ifndef TXXT_H
#define TXXT_H 

#include "third_party.h" 
#include "osev_common/obid.h" 
#include "LVTPDefine.h" 

namespace earth::lev2p {

    class txxt {
        LVTP_BASE_DEFINE(txxt, 2, 0x00, 36)
    public:
        osv_oid_t obje_obid;
    public:
        int32 xx;
        int32 ax;
        int32 cx;
    public: // construct 
        txxt();
        txxt(int32 xx, int32 ax, int32 cx);
        txxt(osv_oid_t obje_obid, int32 xx, int32 ax, int32 cx);
    public:
        int32 tpp(int32 xo, int32 ao);
    };
}

#endif /* TXXT_H */
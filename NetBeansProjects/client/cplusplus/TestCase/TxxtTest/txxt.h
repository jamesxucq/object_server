#ifndef TXXT_H
#define TXXT_H 

#include "OSEVClieCPP.h" 

namespace earth::lev2p {

    class txxt {
        LVTP_BASE_DEFINE(txxt, 2, 0x00, 36)
    public:
        osv_oid_t obje_oid;
    public:
        int xx;
        int ax;
        int cx;
    public: // construct 
        txxt();
    public:
        int tpp(int xo, int ao);
    };
}

#endif /* TXXT_H */ 

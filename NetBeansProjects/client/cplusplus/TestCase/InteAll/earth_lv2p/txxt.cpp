#include <string.h> 
#include "txxt.h" 

using namespace earth::lev2p;

const osv_oid_t txxt::soLevTPOBID = {0x18a7cee3, 0x685c5b2c, 0x00};
const char *txxt::spLevTPName = (char *) "txxt";
unsigned int txxt::suChkAttribCount;
const char *txxt::spFomtStri = (char *) "oiii";

int txxt::Serialize(PK_PACK_STREAM *pkps, txxt *obje) {
    if (paki_pack_obid(pkps, &obje->obje_obid)) return -1;
    if (paki_pack_int32(pkps, obje->xx)) return -1;
    if (paki_pack_int32(pkps, obje->ax)) return -1;
    if (paki_pack_int32(pkps, obje->cx)) return -1;
    return 0x00;
}

int txxt::Deserialize(txxt *obje, PK_PACK_STREAM *pkps) {
    if (paki_unpack_OBID(pkps, &obje->obje_obid)) return -1;
    if (paki_unpack_int32(pkps, &obje->xx)) return -1;
    if (paki_unpack_int32(pkps, &obje->ax)) return -1;
    if (paki_unpack_int32(pkps, &obje->cx)) return -1;
    return 0x00;
}

txxt::txxt() {
}

txxt::txxt(int32 xx, int32 ax, int32 cx) {
    this->xx = xx;
    this->ax = ax;
    this->cx = cx;
}

txxt::txxt(osv_oid_t obje_obid, int32 xx, int32 ax, int32 cx) {
    OBID_BINARY_COPY(&this->obje_obid, &obje_obid)
    this->xx = xx;
    this->ax = ax;
    this->cx = cx;
}

int32 txxt::tpp(int32 xo, int32 ao) {
    this->xx = xo;
    this->ax = ao;
    return this->cx;
}

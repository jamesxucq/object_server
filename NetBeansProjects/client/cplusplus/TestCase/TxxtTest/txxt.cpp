#include <string.h> 
#include "txxt.h" 
using namespace earth::lev2p;
const osv_oid_t txxt::soLevTPOID = {0xfbdc7dbb, 0x6503b4ae, 0x00};
const char *txxt::spLevTPName = (char *) "txxt";
unsigned int txxt::suChkVersiCount;
const char *txxt::spDeseFomtStri = (char *) "oiii";

char *txxt::Serialize(char *obje_psts, unsigned long long *sleng, txxt *obje) {
    char *last_str = obje_psts;
    last_str = binary_pstyl(last_str, &obje->obje_oid, sizeof (osv_oid_t));
    last_str = int_pstyl(last_str, obje->xx);
    last_str = int_pstyl(last_str, obje->ax);
    last_str = int_pstyl(last_str, obje->cx);
    sleng[0x00] += txxt::clSeriLength ? txxt::clSeriLength : last_str - obje_psts;
    return last_str;
}

int txxt::Deserialize(txxt *obje, PK_PACK_STREAM *pkps) {
    if (paki_unpack_OBID(pkps, &obje->obje_oid)) return -1;
    if (paki_unpack_int32(pkps, &obje->xx)) return -1;
    if (paki_unpack_int32(pkps, &obje->ax)) return -1;
    if (paki_unpack_int32(pkps, &obje->cx)) return -1;
    return 0x00;
}

txxt::txxt() {
}

int txxt::tpp(int xo, int ao) {
    this->cx = xo;
    this->ax = ao;
    return this->xx;
}



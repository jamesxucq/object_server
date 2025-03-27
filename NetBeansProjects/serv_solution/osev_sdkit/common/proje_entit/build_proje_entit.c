
#include "commo_header.h"
// #include "kcomm_header.h"
#include "kcomm_struct.h"
#include "paki_memo.h"

#include "build_proje_entit.h"
#include "paki_memo.h"

//

/*
b         int8_t    byte         int            signed byte
B         uint8_t   byte         int            unsigned byte
h         int16_t   short        int            signed 16-bit
H         uint16_t  short        int            unsigned 16-bit
i         int32_t   int          int            signed 32-bit
I         uint32_t  int          int            unsigned 32-bit
l         int32_t   int          int            signed 32-bit
L         uint32_t  int          int            unsigned 32-bit
q         int64_t   long         int            signed 64-bit
Q         uint64_t  long         int            unsigned 64-bit
r         uint64_t  long         int            record number
s         char[]    String       str            fixed-length string
S         char[]    String       str            NUL-terminated string
t         uint8_t   byte         int            fixed-length bit field
u         WT_ITEM * byte[]       str            raw byte array
// extend
f         float       
d         double  
 */

//

int build_objec_strea_ensi(FILE *proj_data, osv_oid_t *key_obid, PK_ITEM *svalu) {
    // OSEVPF("[FUNC]:build_objec_strea_nosi\n");
    if (0x00 >= APPEND_DATAS(proj_data, key_obid, OBJE_IDENTI_BLEN))
        return -1;
    if (0x00 >= APPEND_DATAS(proj_data, svalu->data, svalu->size))
        return -1;
    // OSEVPF("end build_objec_strea_nosi\n");
    return 0x00;
}

int build_objec_strea_enob(FILE *proj_data, osv_oid_t *key_obid, PK_ITEM *svalu) {
    // OSEVPF("[FUNC]:build_objec_strea_nosi\n");
    if (0x00 >= APPEND_DATAS(proj_data, key_obid, OBJE_IDENTI_BLEN))
        return -1;
    if (0x00 >= APPEND_DATAS(proj_data, svalu->data, svalu->size))
        return -1;
    // OSEVPF("end build_objec_strea_nosi\n");
    return 0x00;
}

//

#define PACK_STREAM_CLOSE_III(PKPST, PKPSO, PKPSD) \
    paki_stream_close(PKPST, NULL); \
    paki_stream_close(PKPSO, NULL); \
    paki_stream_close(PKPSD, NULL);

//

int build_proje_strea_enco(FILE *proj_data, PK_ITEM *objnod, PK_ITEM *svalu1, PK_ITEM *svalu2, field_resul_co *fieres) {
    OSEVPF("[FUNC]:build_proje_strea_noco\n");
    PK_PACK_STREAM *pkpsd;
    if (paki_stream_open(fieres->fmtstd_co, PASS_OBIDEN_SECTI(objnod->data), objnod->size - OBJE_IDENTI_BLEN, &pkpsd))
        return -1;
    PK_PACK_STREAM *pkps1;
    PK_PACK_STREAM *pkps2;
    if (paki_stream_open(fieres->rfmtst1, svalu1->data, svalu1->size, &pkps1)) {
        paki_stream_close(pkpsd, NULL);
        return -1;
    }
    if (paki_stream_open(fieres->rfmtst2, svalu2->data, svalu2->size, &pkps2)) {
        paki_stream_close(pkps1, NULL);
        paki_stream_close(pkpsd, NULL);
        return -1;
    }
    //
    PK_NODE node;
    unsigned char *rescod = fieres->rescod;
    for (; rescod[0x00]; ++rescod) {
        OSEVPF("rescod:|%08x|\n", rescod[0x00]);
        if (FIELD_FROM_ONE & rescod[0x00]) {
            if (paki_unpack_node(pkps1, &node)) {
                PACK_STREAM_CLOSE_III(pkps2, pkps1, pkpsd);
                // OSEVPF("222222\n");
                return -1;
            }
            // OSEVPF("ONE item.data:%d\n", item.data);
        } else if (FIELD_FROM_TWO & rescod[0x00]) {
            if (paki_unpack_node(pkps2, &node)) {
                PACK_STREAM_CLOSE_III(pkps2, pkps1, pkpsd);
                // OSEVPF("222222\n");
                return -1;
            }
        }
        //
        if (paki_pack_node(pkpsd, &node)) {
            PACK_STREAM_CLOSE_III(pkps2, pkps1, pkpsd);
            // OSEVPF("333333\n");
            return -1;
        }
    }
    // objnod->size = ;
    if (0x00 >= APPEND_DATAS(proj_data, objnod->data, paki_stream_leng(pkpsd))) {
        PACK_STREAM_CLOSE_III(pkps2, pkps1, pkpsd);
        return -1;
    }
    //
    PACK_STREAM_CLOSE_III(pkps2, pkps1, pkpsd);
    OSEVPF("end build_proje_strea_noco\n");
    return 0x00;
}

//

int build_proje_objec_enco(paki_memo_t *objnod, PK_ITEM *svalu1, PK_ITEM *svalu2, field_resul_co *fieres) {
    OSEVPF("[FUNC]:build_proje_objec_noco\n");
    PK_PACK_STREAM *pkpsd;
    if (paki_stream_open(fieres->fmtstd_co, objnod->item.data, objnod->allo_size, &pkpsd))
        return -1;
    PK_PACK_STREAM *pkps1;
    PK_PACK_STREAM *pkps2;
    if (paki_stream_open(fieres->rfmtst1, svalu1->data, svalu1->size, &pkps1)) {
        paki_stream_close(pkpsd, NULL);
        return -1;
    }
    if (paki_stream_open(fieres->rfmtst2, svalu2->data, svalu2->size, &pkps2)) {
        paki_stream_close(pkps1, NULL);
        paki_stream_close(pkpsd, NULL);
        return -1;
    }
    //
    PK_NODE node;
    unsigned char *rescod = fieres->rescod;
    for (; rescod[0x00]; ++rescod) {
        OSEVPF("rescod:|%08x|\n", rescod[0x00]);
        if (FIELD_FROM_ONE & rescod[0x00]) {
            if (paki_unpack_node(pkps1, &node)) {
                PACK_STREAM_CLOSE_III(pkps2, pkps1, pkpsd);
                // OSEVPF("222222\n");
                return -1;
            }
            // OSEVPF("ONE item.data:%d\n", item.data);
        } else if (FIELD_FROM_TWO & rescod[0x00]) {
            if (paki_unpack_node(pkps2, &node)) {
                PACK_STREAM_CLOSE_III(pkps2, pkps1, pkpsd);
                // OSEVPF("222222\n");
                return -1;
            }
        }
        //
        if (paki_pack_node(pkpsd, &node)) {
            PACK_STREAM_CLOSE_III(pkps2, pkps1, pkpsd);
            // OSEVPF("333333\n");
            return -1;
        }
    }
    objnod->item.size = paki_stream_leng(pkpsd);
    //
    PACK_STREAM_CLOSE_III(pkps2, pkps1, pkpsd);
    OSEVPF("end build_proje_objec_noco\n");
    return 0x00;
}

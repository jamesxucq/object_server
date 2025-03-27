
/* 
 * File:   LVTPDefine.h
 * Author: James Xu
 *
 * Created on 2017.9.10
 */

#ifndef LVTP_DEFINE_H
#define LVTP_DEFINE_H

// 

#define LVTP_BASE_DEFINE(LVTP_NAME, VERSION, INTEGRALITY, SERILENGTH) \
    protected: \
        static const osv_oid_t soLevTPOBID; \
        /* 0x00:not fixed >0x00:fixed */ \
        static const unsigned long long clSeriLength = SERILENGTH; \
        /* 0x01:true 0x00:false */ \
        static const int ciIntegrity = INTEGRALITY; \
    public: \
        static const char *spLevTPName; \
        /* 0x00:disable >0x00:is version */ \
        static const unsigned long long clVersion = VERSION; \
        static unsigned int suChkAttribCount; \
        static const char *spFomtStri;\
    public: \
        static int Serialize(PK_PACK_STREAM *pkps, LVTP_NAME *obje); \
        static int Deserialize(LVTP_NAME *obje, PK_PACK_STREAM *pkps);

#endif /* LVTP_DEFINE_H */


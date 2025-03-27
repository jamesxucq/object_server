
/* 
 * File:   InvoRType.h
 * Author: James Xu
 *
 * Created on 2023.11.14, PM 4:21
 */

#ifndef INVO_RTYPE_H
#define INVO_RTYPE_H

//
#include <string>
using std::string;

#include "osev_common/obid.h"

#ifdef __cplusplus
extern "C" {
#endif

    namespace IRKeyVal {

        struct RTypChar {
        public:
            osv_oid_t obje_obid;
            char ivalu;
        public:
            static char *Deseri(RTypChar *obje, char *deseConte);
        };

        struct RTypUchar {
        public:
            osv_oid_t obje_obid;
            unsigned char ivalu;
        public:
            static char *Deseri(RTypUchar *obje, char *deseConte);
        };

        struct RTypInt16 {
        public:
            osv_oid_t obje_obid;
            short ivalu;
        public:
            static char *Deseri(RTypInt16 *obje, char *deseConte);
        };

        struct RTypUint16 {
        public:
            osv_oid_t obje_obid;
            unsigned short ivalu;
        public:
            static char *Deseri(RTypUint16 *obje, char *deseConte);
        };

        struct RTypInt32 {
        public:
            osv_oid_t obje_obid;
            int ivalu;
        public:
            static char *Deseri(RTypInt32 *obje, char *deseConte);
        };

        struct RTypUint32 {
        public:
            osv_oid_t obje_obid;
            unsigned int ivalu;
        public:
            static char *Deseri(RTypUint32 *obje, char *deseConte);
        };

        struct RTypInt64 {
        public:
            osv_oid_t obje_obid;
            long long ivalu;
        public:
            static char *Deseri(RTypInt64 *obje, char *deseConte);
        };

        struct RTypUInt64 {
        public:
            osv_oid_t obje_obid;
            unsigned long long ivalu;
        public:
            static char *Deseri(RTypUInt64 *obje, char *deseConte);
        };

        struct RTypObid {
        public:
            osv_oid_t obje_obid;
            osv_oid_t ivalu;
        public:
            static char *Deseri(RTypObid *obje, char *deseConte);
        };

        struct RTypFloat {
        public:
            osv_oid_t obje_obid;
            float ivalu;
        public:
            static char *Deseri(RTypFloat *obje, char *deseConte);
        };

        struct RTypDouble {
        public:
            osv_oid_t obje_obid;
            double ivalu;
        public:
            static char *Deseri(RTypDouble *obje, char *deseConte);
        };

        struct RTypStri {
        private:
            unsigned long long sleng;
        public:
            RTypStri(unsigned long long sleng);
            virtual ~RTypStri();
        public:
            osv_oid_t obje_obid;
            char *ivalu;
        public:
            static char *Deseri(RTypStri *obje, char *deseConte);
        };

        struct RTypStrz {
        public:
            osv_oid_t obje_obid;
            std::string ivalu;
        public:
            static char *Deseri(RTypStrz *obje, char *deseConte);
        };


    };

#ifdef __cplusplus
}
#endif

#endif /* INVO_RTYPE_H */


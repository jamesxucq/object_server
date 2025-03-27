
/* 
 * File:   ChkLvtpAtti.h
 * Author: James Xu
 *
 * Created on 2024.5.17, PM 2:24
 */

#ifndef CHK_LVTP_ATTI_H
#define CHK_LVTP_ATTI_H

#ifdef __cplusplus
extern "C" {
#endif

    //
#if defined(_CHECK_VERSION_EVERYTIME)

    /* _CHECK_VERSION_EVERYTIME */
#define CHECK_LVTP_ATTRIBU(VERSIO, OCLIE, LVTP_NAME, CHKA_COUNT) { \
        /* CLIEPF("_CHECK_VERSION_EVERYTIME\n"); */ \
        unsigned long long lv2p_versi; \
        if (lv2p_colle_versi(&lv2p_versi, OCLIE, LVTP_NAME)) { \
            /* CLIEPF("lv2p_colle_versio ERROR!\n"); */ \
            return ERR_COLLE_VERSIO; \
        } \
        if (VERSIO != lv2p_versi) { \
            /* CLIEPF("check version ERROR!\n"); */ \
            /* CLIEPF("clie versi:%llu serv versi:%llu\n", VERSIO, lv2p_versi); */ \
            return ERR_COMPA_VERSIO; \
        } \
        /* CLIEPF("PASS CHECK VERSIO!\n"); */ \
    }

#elif defined(_CHECK_VERSION_INTERVAL)

    /* _CHECK_VERSION_INTERVAL */
#define CHECK_LVTP_ATTRIBU(VERSIO, OCLIE, LVTP_NAME, CHKA_COUNT) { \
        /* CLIEPF("_CHECK_VERSION_INTERVAL\n"); */ \
        if(!(CHECK_ATTRIBU_FREQUENCY & CHKA_COUNT)) { \
            unsigned long long lv2p_versi; \
            if (lv2p_colle_versi(&lv2p_versi, OCLIE, LVTP_NAME)) { \
                /* CLIEPF("lv2p_colle_versio ERROR!\n"); */ \
                CHKA_COUNT = 0x00; \
                return ERR_COLLE_VERSIO; \
            } \
            if (VERSIO != lv2p_versi) { \
                /* CLIEPF("CHECK VERSIO ERROR!\n"); */ \
                /* CLIEPF("clie versi:%llu serv versi:%llu\n", VERSIO, lv2p_versi); */ \
                CHKA_COUNT = 0x00; \
                return ERR_COMPA_VERSIO; \
            } \
        } \
        ++CHKA_COUNT; \
        /* CLIEPF("PASS VERSIO CHECK!\n"); */ \
    }

#elif defined(_CHECK_ATTRIBU_EVERYTIME)

    /* _CHECK_ATTRIBU_EVERYTIME */
#define CHECK_LVTP_ATTRIBU(VERSIO, OCLIE, LVTP_NAME, CHKA_COUNT) { \
        /* CLIEPF("_CHECK_ATTRIBU_EVERYTIME\n"); */ \
        unsigned long long lv2p_versi; \
        unsigned int lv2p_extern; \
        if (lv2p_colle_attrib(&lv2p_versi, &lv2p_extern, OCLIE, LVTP_NAME)) { \
            /* CLIEPF("lv2p_colle_attrib ERROR!\n"); */ \
            return ERR_COLLE_ATTRI; \
        } \
        if ((VERSIO != lv2p_versi) || !lv2p_extern) { \
            /* CLIEPF("check version ERROR!\n"); */ \
            /* CLIEPF("clie versi:%llu serv versi:%llu\n", VERSIO, lv2p_versi); */ \
            return ERR_COMPA_ATTRI; \
        } \
        /* CLIEPF("PASS CHECK VERSIO!\n"); */ \
    }

#elif defined(_CHECK_ATTRIBU_INTERVAL)

    /* _CHECK_ATTRIBU_INTERVAL */
#define CHECK_LVTP_ATTRIBU(VERSIO, OCLIE, LVTP_NAME, CHKA_COUNT) { \
        /* CLIEPF("_CHECK_ATTRIBU_INTERVAL\n"); */ \
        if(!(CHECK_ATTRIBU_FREQUENCY & CHKA_COUNT)) { \
            unsigned long long lv2p_versi; \
            unsigned int lv2p_extern; \
            if (lv2p_colle_attrib(&lv2p_versi, &lv2p_extern, OCLIE, LVTP_NAME)) { \
                /* CLIEPF("lv2p_colle_attrib ERROR!\n"); */ \
                CHKA_COUNT = 0x00; \
                return ERR_COLLE_ATTRI; \
            } \
            if ((VERSIO != lv2p_versi) || !lv2p_extern) { \
                /* CLIEPF("CHECK VERSIO ERROR!\n"); */ \
                /* CLIEPF("clie versi:%llu serv versi:%llu\n", VERSIO, lv2p_versi); */ \
                CHKA_COUNT = 0x00; \
                return ERR_COMPA_ATTRI; \
            } \
        } \
        ++CHKA_COUNT; \
        /* CLIEPF("PASS VERSIO CHECK!\n"); */ \
    }

#elif defined(_DONOT_CHECK_ATTRIBU)

    /* _DONOT_CHECK_ATTRIBU */
#define CHECK_LVTP_ATTRIBU(VERSIO, OCLIE, LVTP_NAME, CHKA_COUNT) { \
        /* CLIEPF("_DONOT_CHECK_ATTRIBU\n"); */ \
    }

#endif 

#ifdef __cplusplus
}
#endif

#endif /* CHK_LVTP_ATTI_H */


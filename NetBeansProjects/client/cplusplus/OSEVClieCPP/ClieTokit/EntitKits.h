
/* 
 * File:   EntitKits.h
 * Author: James Xu
 *
 * Created on 2017.9.6
 */

#ifndef ENTIT_KITS_H
#define ENTIT_KITS_H

//
using namespace std;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "../proto_conne/reque_respo.h"

//
namespace EntitKits {
    template <class T> int DeseObje(T &deseObje, resp_data_t *objeRespo);
    template <class T> int DeseObjeVect(vector <T *> &deseVec, resp_data_t *objeRespo);
    //
    template <class T> int SeriObje(char *objePsts, unsigned long long *seriLeng, T &seriObje);
    template <class T> int SeriObjeVect(char *objePsts, unsigned long long *seriLeng, vector <T *> &seriVec);
    //
    int DeseOBID(osv_oid_t &deseOBID, resp_data_t *objeRespo);
    template <class T> int DeseRKV(T &deseObje, resp_data_t *objeRespo);
    template <class T> int DeseRKVVect(vector <T *> &deseVec, resp_data_t *objeRespo);
    //
    template <class T> static void ClearVecto(vector <T *> &cleaVecto);
};

//

template <class T> int EntitKits::DeseObje(T &deseObje, resp_data_t *objeRespo) {
    PK_PACK_STREAM *pkps;
    if (paki_stream_open(T::spFomtStri, (void *) objeRespo->resp_memo, objeRespo->content_length, &pkps))
        return -1;
    //
    if (T::Deserialize(&deseObje, pkps)) {
        paki_stream_close(pkps, NULL);
        return -1;
    }
    //
    paki_stream_close(pkps, NULL);
    return 0x00;
}

template <class T> int EntitKits::DeseObjeVect(vector <T *> &deseVec, resp_data_t *objeRespo) {
    PK_PACK_STREAM *pkps;
    if (paki_stream_open(T::spFomtStri, (void *) objeRespo->resp_memo, objeRespo->content_length, &pkps))
        return -1;
    //
    T *unobje;
    while (objeRespo->content_length > paki_stream_leng(pkps)) {
        paki_stream_reset(pkps, RESET_STREAM_FORMAT);
        unobje = new T();
        if (T::Deserialize(unobje, pkps)) {
            paki_stream_close(pkps, NULL);
            ClearVecto(deseVec);
            return -1;
        }
        deseVec.push_back(unobje);
    }
    //
    paki_stream_close(pkps, NULL);
    return 0x00;
}

//

template <class T> int EntitKits::SeriObje(char *objePsts, unsigned long long *seriLeng, T &seriObje) {
    PK_PACK_STREAM *pkps;
    if (paki_stream_open(T::spFomtStri, objePsts, seriLeng[0x00], &pkps))
        return -1;
    //
    if (T::Serialize(pkps, &seriObje)) {
        paki_stream_close(pkps, NULL);
        return -1;
    }
    //
    seriLeng[0x00] = paki_stream_leng(pkps);
    paki_stream_close(pkps, NULL);
    return 0x00;
}

template <class T> int EntitKits::SeriObjeVect(char *objePsts, unsigned long long *seriLeng, vector <T *> &seriVec) {
    PK_PACK_STREAM *pkps;
    if (paki_stream_open(T::spFomtStri, objePsts, seriLeng[0x00], &pkps))
        return -1;
    //
    class vector <T *>::iterator iter;
    for (iter = seriVec.begin(); iter != seriVec.end(); ++iter) {
        paki_stream_reset(pkps, RESET_STREAM_FORMAT);
        if (T::Serialize(pkps, *iter)) {
            paki_stream_close(pkps, NULL);
            return -1;
        }
    }
    //
    seriLeng[0x00] = paki_stream_leng(pkps);
    paki_stream_close(pkps, NULL);
    return 0x00;
}

//

inline int EntitKits::DeseOBID(osv_oid_t &deseOBID, resp_data_t *objeRespo) {
    if (sizeof (osv_oid_t) != objeRespo->content_length)
        return -1;
    OBID_BINARY_COPY(&deseOBID, (osv_oid_t *) objeRespo->resp_memo)
    return 0x00;
}

//

template <class T> inline int EntitKits::DeseRKV(T &deseObje, resp_data_t *objeRespo) {
    T::Deseri(&deseObje, objeRespo->resp_memo);
    return 0x00;
}

template <class T> int EntitKits::DeseRKVVect(vector <T *> &deseVec, resp_data_t *objeRespo) {
    char *endPosi = objeRespo->content_length + objeRespo->resp_memo;
    //
    T *unobje;
    char *proPosi = objeRespo->resp_memo;
    while (endPosi > proPosi) {
        unobje = new T();
        proPosi = T::Deseri(unobje, proPosi);
        deseVec.push_back(unobje);
    }
    //
    return 0x00;
}

//

template <class T> void EntitKits::ClearVecto(vector <T *> &cleaVecto) {
    class vector <T *>::iterator iter;
    for (iter = cleaVecto.begin(); iter != cleaVecto.end(); ++iter)
        delete (*iter);
    cleaVecto.clear();
}

#endif /* ENTIT_KITS_H */


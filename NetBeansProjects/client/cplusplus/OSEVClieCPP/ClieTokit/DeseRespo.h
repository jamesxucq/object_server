
/* 
 * File:   DeseRespo.h
 * Author: James Xu
 *
 * Created on 2024.4.18, PM 3:33
 */

#ifndef DESERESPO_H
#define DESERESPO_H

class DeseRespo {
public:
    DeseRespo();
    DeseRespo(const DeseRespo& orig);
    DeseRespo(resp_data_t *querResp, const string &sFmtstr);
    virtual ~DeseRespo();
private:
    PK_PACK_STREAM *m_pkps;
    char m_sFmtstr[FMTST_COUNT_ZTAI];
public:
    void Reset();
    int Initial(resp_data_t *querResp, const string &sFmtstr);
    int Final(size_t *usedp);
public:
    int LoopDeseri(osv_oid_t *resp_obid, ...);
};

#endif /* DESERESPO_H */


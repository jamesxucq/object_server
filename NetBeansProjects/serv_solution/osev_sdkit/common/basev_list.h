
/* 
 * File:   basev_list.h
 * Author: James Xu
 *
 * Created on 2017.1.11, PM 2:21
 */

#ifndef BASEV_LIST_H
#define BASEV_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

    // base list

    struct _basv_list_ {
        osv_oid_t *_oid_; // base obid
        char *_base_; // base name
        base_valu basval; // base info
        //
        struct _basv_list_ *next;
    };

    typedef struct _basv_list_ basv_list;

    //
    basv_list *creat_basv_list();

#define APPEND_BASE_LIST(BLSTH, BLSTND) LL_APPEND(*(BLSTH), BLSTND)

    void destr_basv_list(basv_list *blist);

    void dele_base_list(basv_list *blist);

    //

    inline basv_list *find_blstn(basv_list *blist, char *basen) {
        for (; blist; blist = blist->next) {
            if (!strcmp(basen, blist->_base_))
                return blist;
        }
        return NULL;
    }

    inline basv_list *find_blsto(basv_list *blist, osv_oid_t *base_obid) {
        for (; blist; blist = blist->next) {
            if (OBID_EQUALI(base_obid, blist->_oid_))
                return blist;
        }
        return NULL;
    }

    void dele_blist(basv_list **blsth, basv_list *blist);

#ifdef __cplusplus
}
#endif

#endif /* BASEV_LIST_H */


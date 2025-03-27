
/* 
 * File:   stat_respo.h
 * Author: James Xu
 *
 * Created on 20211010, AM9:01
 */

#ifndef STAT_RESPO_H
#define STAT_RESPO_H


#include "commo_header.h"
#include "lv2p_list.h"

#ifdef __cplusplus
extern "C" {
#endif

    // trans-serve
#define LIST_XML_HEAD "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"

    //

    /*
    <?xml version="1.0" encoding="UTF-8"?>
        <lv2p>
            <name>roles</name>
            <obid>dd6d7f0ec35d116401000000</obid>
        </lv2p>
     */

    inline void list_lv2p_objid(respo_ctrl *resctl, lv2p_attri *lv2ai) {
        char obid_stri[OBJE_IDENTI_ZLEN];
        char *last_str = lscpy(resctl->posi_resp, LIST_XML_HEAD);
        last_str = lscpy(last_str, "<lv2p><name>");
        last_str = lscpy(last_str, lv2ai->lv2pn);
        last_str = lscpy(last_str, "</name><obid>");
        last_str = lscpy(last_str, oidstr(obid_stri, &lv2ai->lv2p_obid));
        last_str = lscpy(last_str, "</obid></lv2p>");
        PDAT_LASTPOS_PCAT(resctl, last_str)
    }

    /*
    <?xml version="1.0" encoding="UTF-8"?>
        <lv2p_list>
            <lv2p obid="dd6d7f0ec35d116401000000">role</lv2p>
            <lv2p obid="dd6d7f0ec35d116401000000">role</lv2p>
            <lv2p obid="dd6d7f0ec35d116401000000">role</lv2p>
            <lv2p obid="dd6d7f0ec35d116401000000">role</lv2p>
        </lv2p_list>
     */
    inline void stai_l2noi_head(respo_ctrl *resctl) {
        char *last_str = lscpy(resctl->posi_resp, LIST_XML_HEAD);
        last_str = lscpy(last_str, "<lv2p_list>");
        PDAT_LASTPOS_PCAT(resctl, last_str)
    }

    inline void stai_l2noi_end(respo_ctrl *resctl) {
        char *last_str = lscpy(resctl->posi_resp, "</lv2p_list>");
        PDAT_LASTPOS_PCAT(resctl, last_str)
    }

    inline void stai_lv2pn_objid(respo_ctrl *resctl, char *lv2pn, osv_oid_t *lv2p_obid) {
        char obid_stri[OBJE_IDENTI_ZLEN];
        char *last_str = lscpy(resctl->posi_resp, "<lv2p obid=\"");
        last_str = lscpy(last_str, oidstr(obid_stri, lv2p_obid));
        last_str = lscpy(last_str, "\">");
        last_str = lscpy(last_str, lv2pn);
        last_str = lscpy(last_str, "</lv2p>\n");
        PDAT_LASTPOS_PCAT(resctl, last_str)
    }

    //

    void list_lv2p_attri(respo_ctrl *resctl, lv2p_attri *lv2ai);

    //

    inline void list_lv2p_inheri(respo_ctrl *resctl, lv2p_attri *lv2ai) {
        char *last_str = resctl->posi_resp;
        inherit *ilist = lv2ai->inher_list;
        for (; ilist; ilist = ilist->next) {
            last_str = lsprif(last_str, "<inherit range=\"%d\" lev1n=\"%s\">%s</inherit>", ilist->rang_type, ilist->lev1n, ilist->lv2pn);
        }
        last_str = lccpy(last_str, '\n');
        PDAT_LASTPOS_PCAT(resctl, last_str)
    }

    void list_lv2p_meta(respo_ctrl *resctl, lv2p_decl_i *lv2di);
    void list_lv2p_expand(respo_ctrl *resctl, lv2p_expa_t *lv2expt);

    //
    void list_lv2p_lolst(respo_ctrl *resctl, integra *olist);

    // xml
    /*
    <?xml version="1.0" encoding="UTF-8"?>
        <integrality>
            <lv2pn>taat</lv2pn>
        </integrality>
     */
#define LIST_LVTP_INTEG_HEAD(RESCTL) \
    (RESCTL)->posi_resp = lscpy((RESCTL)->posi_resp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?><integrality>");
#define LIST_LVTP_INTEG_TAIL(RESCTL) \
    (RESCTL)->posi_resp = lscpy((RESCTL)->posi_resp, "</integrality>");

    inline void list_lv2p_integ(respo_ctrl *resctl, char *clas_inte) {
        char *last_str = lscpy(resctl->posi_resp, "<lv2pn>");
        last_str = lscpy(last_str, clas_inte);
        resctl->posi_resp = lscpy(last_str, "</lv2pn>");
    }

    //
    /*
    <?xml version="1.0" encoding="UTF-8"?>
        <integrality>
            <lev1 lv2pn="taat">tpp</lev1>
        </integrality>
     */
#define LIST_LEVO_INTEG_HEAD(RESCTL) \
    (RESCTL)->posi_resp = lscpy((RESCTL)->posi_resp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?><integrality>");
#define LIST_LEVO_INTEG_BODY(RESCTL, ONNOD) \
    (RESCTL)->posi_resp = lsprif((RESCTL)->posi_resp, "<lev1 lv2pn=\"%s\">%s</lev1>", (ONNOD)->lv2pn, (ONNOD)->lev1n);
#define LIST_LEVO_INTEG_TAIL(RESCTL) \
    (RESCTL)->posi_resp = lscpy((RESCTL)->posi_resp, "</integrality>");

    //
    void list_lev1_lv2p(respo_ctrl *resctl, lv1_cont *l1lsnd);
    void list_lev1_iden(respo_ctrl *resctl, char *lev1n, lv1_cont *l1lsnd);
    void list_lev1_fmtsp(respo_ctrl *resctl, char *lev1n, char *fmtsop, lv1_cont *l1lsnd);

    //

    /*
<?xml version="1.0" encoding="UTF-8"?>
<lv2sta>
    <lv2p>txxt</lv2p>
    <statis>
    <lev1>tpp<(xo int32, ao int32)int32, (ci int32, ai int32, xi int32)></lev1>
    </statis>
</lv2sta>
     */
    inline void stat_lev1_stai(respo_ctrl *resctl, char *lv2pn, lev1_list *l1lst) {
        char *last_str = lscpy((char *) resctl->resp_memo, LIST_XML_HEAD);
        last_str = lscpy(last_str, "<lv2sta><lv2p>");
        last_str = lscpy(last_str, lv2pn);
        last_str = lscpy(last_str, "</lv2p>");
        last_str = lscpy(last_str, "<statis>");
        for (; l1lst; l1lst = l1lst->next) {
            last_str = lscpy(last_str, "<lev1>");
            last_str = lscpy(last_str, l1lst->lev1m.lev1n);
            last_str = lscpy(last_str, l1lst->lev1m.decla);
            last_str = lscpy(last_str, "</lev1>");
        }
        last_str = lscpy(last_str, "</statis></lv2sta>");
        PDAT_PRODUCEM_TAIL(resctl, last_str - ((char *) resctl->resp_memo))
    }


#ifdef __cplusplus
}
#endif

#endif /* STAT_RESPO_H */


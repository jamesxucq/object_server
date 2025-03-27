
/* 
 * File:   statq_respo.h
 * Author: James Xu
 *
 * Created on 2023.5.3, PM 4:24
 */

#ifndef STATQ_RESPO_H
#define STATQ_RESPO_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

    //
#define ECHQ_XML_HEAD "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"

    //

    /*
    <?xml version="1.0" encoding="UTF-8"?>
        <contain>
            <name>roles_con</name>
            <obid>dd6d7f0ec35d116401000000</obid>
        </contain>
     */

    inline void fill_oechq_ensi(respo_ctrl *resctl, contain *contp) {
        char obid_stri[OBJE_IDENTI_ZLEN];
        char *last_str = lscpy((char *) resctl->resp_memo, ECHQ_XML_HEAD);
        last_str = lscpy(last_str, "<contain><name>");
        last_str = lscpy(last_str, contp->cont_name);
        last_str = lscpy(last_str, "</name><obid>");
        last_str = lscpy(last_str, oidstr(obid_stri, &contp->cont_obid));
        last_str = lscpy(last_str, "</obid></contain>");
        PDAT_PRODUCEM_TAIL(resctl, last_str - ((char *) resctl->resp_memo))
    }

    void fill_oechq_mult(respo_ctrl *resctl, cont_list *clist);
    void fill_cstiq_mult(respo_ctrl *resctl, cont_list *clist);
    int fill_oechq_perm(respo_ctrl *resctl, user_privi *uepriv, cont_list *clist);

    //

    /*
    <?xml version="1.0" encoding="UTF-8"?>
        <contain>
            <name>roles_con</name>
            <obid>dd6d7f0ec35d116401000000</obid>
        </contain>
     */

    inline void fill_nechq_ensi(respo_ctrl *resctl, contain *contp) {
        char obid_stri[OBJE_IDENTI_ZLEN];
        char *last_str = lscpy((char *) resctl->resp_memo, ECHQ_XML_HEAD);
        last_str = lscpy(last_str, "<contain><name>");
        last_str = lscpy(last_str, contp->cont_name);
        last_str = lscpy(last_str, "</name><obid>");
        last_str = lscpy(last_str, oidstr(obid_stri, &contp->cont_obid));
        last_str = lscpy(last_str, "</obid></contain>");
        PDAT_PRODUCEM_TAIL(resctl, last_str - ((char *) resctl->resp_memo))
    }

    //

    void fill_nechq_mult(respo_ctrl *resctl, cont_list *clist);
    int fill_nechq_perm(respo_ctrl *resctl, user_privi *uepriv, cont_list *clist);

    //

    inline char *fill_qatti_rscon(char *last_xml, contain *contp, cont_lsmp *conda_stm) {
        last_xml = lscpy(last_xml, "<referen type=\"static\">");
        last_xml = lsprif(last_xml, "<refe_cont count=\"%d\">", contp->refe_coun);
        //
        contain *rscop;
        cont_versi *rcove = contp->refe_cove;
        unsigned int inde = 0x00;
        for (; (MAX_RSCON_COUNT > inde) && CHK_ZERO_COVE(rcove); ++inde, ++rcove) {
            rscop = (contain *) cache_value(&rcove->lv4p_obid, conda_stm->lev3o_hm);
            last_xml = lscpy(last_xml, "<contain>");
            if (rscop) last_xml = lscpy(last_xml, rscop->cont_name);
            last_xml = lscpy(last_xml, "</contain>");
        }
        last_xml = lscpy(last_xml, "</refe_cont>");
        last_xml = lscpy(last_xml, "</referen>");
        //
        return last_xml;
    }

    //

    char *fill_qatti_rdcon(char *last_xml, contain *contp, cont_lsmp *conda_stm);

    /*
<?xml version="1.0" encoding="UTF-8"?>
<conatt>
    <name>txxt_con</name>
    <obid>ff7f5d14a6ba306602000000</obid>
    <attrib>
        <lv2p_type fmtst="iii" dasiz="24">txxt</lv2p_type>
        <referen type="dynamic">
            <refe_cont count="2">
                <contain>contname1</contain>
                <contain>contname2</contain>
            </refe_cont>
            <condit>xx>2 AND yy < 3</condit>
        </referen>
        <stora_engine>wiredtiger</stora_engine>
    </attrib>
</conatt>
     */

    // [txxt_con]lev3> :echo:attrib() | kits:format(XML);

    void fill_statq_atti(respo_ctrl *resctl, contain *contp, lv2pme *lv2me, cont_lsmp *conda_stm);

    //
    /*
<?xml version="1.0" encoding="UTF-8"?>
<consta>
    <name>txxt_con</name>
    <obid>ff7f5d14a6ba306602000000</obid>
    <statis>
        <lv2p_type fmtst="iii" dasiz="24">txxt</lv2p_type>
    </statis>
</consta>
     */
    void fill_statq_stai(respo_ctrl *resctl, contain *contp, lv2pme *lv2me, cont_lsmp *conda_stm);

#ifdef __cplusplus
}
#endif

#endif /* STATQ_RESPO_H */



/* 
 * File:   stato_respo.h
 * Author: James Xu
 *
 * Created on 2023.5.3, PM 4:53
 */

#ifndef STATO_RESPO_H
#define STATO_RESPO_H

#include "commo_header.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ECHE_XML_HEAD "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"

    //

    /*
    <?xml version="1.0" encoding="UTF-8"?>
        <contain>
            <name>roles_con</name>
            <obid>dd6d7f0ec35d116401000000</obid>
        </contain>
     */

    inline void fill_state_echo(respo_ctrl *resctl, contain *contp) {
        char obid_stri[OBJE_IDENTI_ZLEN];
        char *last_str = lscpy((char *) resctl->resp_memo, ECHE_XML_HEAD);
        last_str = lscpy(last_str, "<contain><name>");
        last_str = lscpy(last_str, contp->cont_name);
        last_str = lscpy(last_str, "</name><obid>");
        last_str = lscpy(last_str, oidstr(obid_stri, &contp->cont_obid));
        last_str = lscpy(last_str, "</obid></contain>");
        PDAT_PRODUCEM_TAIL(resctl, last_str - ((char *) resctl->resp_memo))
    }

    //

    inline char *fill_eatti_rscon(char *last_xml, contain *contp, cont_lsmp *conda_stm) {
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

    char *fill_eatti_rdcon(char *last_xml, contain *contp, cont_lsmp *conda_stm);

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

    void fill_state_atti(respo_ctrl *resctl, contain *contp, lv2pme *lv2me, cont_lsmp *conda_stm);

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
    void fill_state_stai(respo_ctrl *resctl, contain *contp, lv2pme *lv2me, cont_lsmp *conda_stm);


#ifdef __cplusplus
}
#endif

#endif /* STATO_RESPO_H */


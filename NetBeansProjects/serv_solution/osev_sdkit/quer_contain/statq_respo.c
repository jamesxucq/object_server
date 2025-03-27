#include "commo_header.h"
#include "kcomm_header.h"

#include "chk_privi_bzl.h"

#include "statq_respo.h"

//

/*
<?xml version="1.0" encoding="UTF-8"?>
    <cont_list>
        <cont obid="dd6d7f0ec35d116401000000">relos_con</cont>
        <cont obid="dd6d7f0ec35d116401000000">osev_user_con</cont>
        <cont obid="dd6d7f0ec35d116401000000">base_user_con</cont>
    </cont_list>
 */

void fill_oechq_mult(respo_ctrl *resctl, cont_list *clist) {
    OSEVPF("[FUNC]:fill_oechq_mult\n");
    char obid_stri[OBJE_IDENTI_ZLEN];
    char *last_str = lscpy((char *) resctl->resp_memo, ECHQ_XML_HEAD);
    //
    last_str = lscpy(last_str, "<cont_list>");
    for (; clist; clist = clist->next) {
        last_str = lscpy(last_str, "<cont obid=\"");
        last_str = lscpy(last_str, oidstr(obid_stri, &clist->contp->cont_obid));
        last_str = lscpy(last_str, "\">");
        last_str = lscpy(last_str, clist->contp->cont_name);
        last_str = lscpy(last_str, "</cont>");
    }
    last_str = lscpy(last_str, "</cont_list>");
    PDAT_PRODUCEM_TAIL(resctl, last_str - ((char *) resctl->resp_memo))
}

void fill_cstiq_mult(respo_ctrl *resctl, cont_list *clist) {
    OSEVPF("[FUNC]:fill_cstiq_mult\n");
    char obid_stri[OBJE_IDENTI_ZLEN];
    char *last_str = lscpy((char *) resctl->resp_memo, ECHQ_XML_HEAD);
    //
    last_str = lscpy(last_str, "<cont_list>");
    for (; clist; clist = clist->next) {
        last_str = lscpy(last_str, "<cont obid=\"");
        last_str = lscpy(last_str, oidstr(obid_stri, &clist->contp->cont_obid));
        last_str = lscpy(last_str, "\">");
        last_str = lscpy(last_str, clist->contp->cont_name);
        last_str = lscpy(last_str, "</cont>");
    }
    last_str = lscpy(last_str, "</cont_list>");
    PDAT_PRODUCEM_TAIL(resctl, last_str - ((char *) resctl->resp_memo))
}

int fill_oechq_perm(respo_ctrl *resctl, user_privi *uepriv, cont_list *clist) {
    OSEVPF("[FUNC]:fill_oechq_perm\n");
    char obid_stri[OBJE_IDENTI_ZLEN];
    char *last_str = lscpy((char *) resctl->resp_memo, ECHQ_XML_HEAD);
    //
    unsigned int inde = 0x00;
    last_str = lscpy(last_str, "<cont_list>");
    for (; clist; clist = clist->next) {
#ifndef NOAUTH
        if (!mechq_privile_bzl(uepriv, &clist->contp->cont_obid, QUEP_STATU)) {
#endif // NOAUTH
            ++inde;
            last_str = lscpy(last_str, "<cont obid=\"");
            last_str = lscpy(last_str, oidstr(obid_stri, &clist->contp->cont_obid));
            last_str = lscpy(last_str, "\">");
            last_str = lscpy(last_str, clist->contp->cont_name);
            last_str = lscpy(last_str, "</cont>");
#ifndef NOAUTH
        }
#endif // NOAUTH
    }
    last_str = lscpy(last_str, "</cont_list>");
    PDAT_PRODUCEM_TAIL(resctl, last_str - ((char *) resctl->resp_memo))
    return inde;
}

//

/*
<?xml version="1.0" encoding="UTF-8"?>
    <cont_list>
        <cont obid="dd6d7f0ec35d116401000000">relos_con</cont>
        <cont obid="dd6d7f0ec35d116401000000">osev_user_con</cont>
        <cont obid="dd6d7f0ec35d116401000000">base_user_con</cont>
    </cont_list>
 */

void fill_nechq_mult(respo_ctrl *resctl, cont_list *clist) {
    OSEVPF("[FUNC]:fill_nechq_mult\n");
    char obid_stri[OBJE_IDENTI_ZLEN];
    char *last_str = lscpy((char *) resctl->resp_memo, ECHQ_XML_HEAD);
    //
    last_str = lscpy(last_str, "<cont_list>");
    for (; clist; clist = clist->next) {
        last_str = lscpy(last_str, "<cont obid=\"");
        last_str = lscpy(last_str, oidstr(obid_stri, &clist->contp->cont_obid));
        last_str = lscpy(last_str, "\">");
        last_str = lscpy(last_str, clist->contp->cont_name);
        last_str = lscpy(last_str, "</cont>");
    }
    last_str = lscpy(last_str, "</cont_list>");
    PDAT_PRODUCEM_TAIL(resctl, last_str - ((char *) resctl->resp_memo))
}

int fill_nechq_perm(respo_ctrl *resctl, user_privi *uepriv, cont_list *clist) {
    OSEVPF("[FUNC]:fill_nechq_perm\n");
    char obid_stri[OBJE_IDENTI_ZLEN];
    char *last_str = lscpy((char *) resctl->resp_memo, ECHQ_XML_HEAD);
    //
    unsigned int inde = 0x00;
    last_str = lscpy(last_str, "<cont_list>");
    for (; clist; clist = clist->next) {
#ifndef NOAUTH
        if (!mechq_privile_bzl(uepriv, &clist->contp->cont_obid, QUEP_STATU)) {
#endif // NOAUTH
            ++inde;
            last_str = lscpy(last_str, "<cont obid=\"");
            last_str = lscpy(last_str, oidstr(obid_stri, &clist->contp->cont_obid));
            last_str = lscpy(last_str, "\">");
            last_str = lscpy(last_str, clist->contp->cont_name);
            last_str = lscpy(last_str, "</cont>");
#ifndef NOAUTH
        }
#endif // NOAUTH
    }
    last_str = lscpy(last_str, "</cont_list>");
    PDAT_PRODUCEM_TAIL(resctl, last_str - ((char *) resctl->resp_memo))
    return inde;
}

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

void fill_statq_atti(respo_ctrl *resctl, contain *contp, lv2pme *lv2me, cont_lsmp *conda_stm) {
    char obid_stri[OBJE_IDENTI_ZLEN];
    char *last_str = lscpy((char *) resctl->resp_memo, ECHQ_XML_HEAD);
    last_str = lscpy(last_str, "<conatt><name>");
    last_str = lscpy(last_str, contp->cont_name);
    last_str = lscpy(last_str, "</name><obid>");
    last_str = lscpy(last_str, oidstr(obid_stri, &contp->cont_obid));
    last_str = lscpy(last_str, "</obid><attrib>");
    last_str = lscpy(last_str, "<lv2p_type fmtst=\"");
    last_str = lscpy(last_str, lv2me->lv2p_fmtsd_tm);
    last_str = lsprif(last_str, "\" dasiz=\"%lld\">", lv2me->data_size);
    last_str = lscpy(last_str, lv2me->lv2pn);
    last_str = lscpy(last_str, "</lv2p_type>");
    if (REFER_CONTA_STATIC == contp->contype) {
        last_str = fill_qatti_rscon(last_str, contp, conda_stm);
    } else if (REFER_CONTA_DYNAMI == contp->contype)
        last_str = fill_qatti_rdcon(last_str, contp, conda_stm);
    last_str = lscpy(last_str, "<stora_engine>");
    last_str = lscpy(last_str, contp->stora_ha->storage_name);
    last_str = lscpy(last_str, "</stora_engine></attrib></conatt>");
    PDAT_PRODUCEM_TAIL(resctl, last_str - ((char *) resctl->resp_memo))
}

//

char *fill_qatti_rdcon(char *last_xml, contain *contp, cont_lsmp *conda_stm) {
    last_xml = lscpy(last_xml, "<referen type=\"dynamic\">");
    last_xml = lsprif(last_xml, "<refe_cont count=\"%d\">", contp->refe_coun);
    //
    contain *rdcop;
    cont_versi *rcove = contp->refe_cove;
    unsigned int inde = 0x00;
    for (; contp->refe_coun > inde; ++inde, ++rcove) {
        rdcop = (contain *) cache_value(&rcove->lv4p_obid, conda_stm->lev3o_hm);
        last_xml = lscpy(last_xml, "<contain>");
        if (rdcop) last_xml = lscpy(last_xml, rdcop->cont_name);
        last_xml = lscpy(last_xml, "</contain>");
    }
    last_xml = lscpy(last_xml, "</refe_cont>");
    //
    switch (contp->conditype) {
        case CONDI_TYPE_TRAVE:
            last_xml = lsprif(last_xml, "<condit type=\"trave\">%s</condit>", contp->condition);
            break;
        case CONDI_TYPE_OBJID:
            char obid_stri[OBJE_IDENTI_ZLEN];
            osv_oid_t *enti_obid = (osv_oid_t *) contp->condition;
            last_xml = lscpy(last_xml, "<condit type=\"objid\">");
            last_xml = lscpy(last_xml, oidstr(obid_stri, enti_obid));
            for (inde = 0x01, ++enti_obid; contp->refe_coun > inde; ++inde, ++enti_obid) {
                last_xml = lccpy(last_xml, ',');
                last_xml = lscpy(last_xml, oidstr(obid_stri, enti_obid));
            }
            last_xml = lscpy(last_xml, "</condit>");
            break;
        case CONDI_TYPE_PREDI:
            last_xml = lsprif(last_xml, "<condit type=\"predi\">%s</condit>", contp->condition);
            break;
        default:
            break;
    }
    last_xml = lscpy(last_xml, "</referen>");
    //
    return last_xml;
}

void fill_statq_stai(respo_ctrl *resctl, contain *contp, lv2pme *lv2me, cont_lsmp *conda_stm) {
    char obid_stri[OBJE_IDENTI_ZLEN];
    char *last_str = lscpy((char *) resctl->resp_memo, ECHQ_XML_HEAD);
    last_str = lscpy(last_str, "<consta><name>");
    last_str = lscpy(last_str, contp->cont_name);
    last_str = lscpy(last_str, "</name><obid>");
    last_str = lscpy(last_str, oidstr(obid_stri, &contp->cont_obid));
    last_str = lscpy(last_str, "</obid><statis>");
    last_str = lscpy(last_str, "<lv2p_type fmtst=\"");
    last_str = lscpy(last_str, lv2me->lv2p_fmtsd_tm);
    last_str = lsprif(last_str, "\" dasiz=\"%lld\">", lv2me->data_size);
    last_str = lscpy(last_str, lv2me->lv2pn);
    last_str = lscpy(last_str, "</lv2p_type>");
    last_str = lscpy(last_str, "</statis></consta>");
    PDAT_PRODUCEM_TAIL(resctl, last_str - ((char *) resctl->resp_memo))
}

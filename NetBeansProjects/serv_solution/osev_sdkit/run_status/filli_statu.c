#include "commo_header.h"
#include "kcomm_header.h"

#include "rstat_utili.h"
#include "rstatu_obje.h"
#include "basev_bzl.h"

#include "filli_statu.h"

///
/*
<?xml version="1.0" encoding="UTF-8"?>
    <base_statis>
        <base obid="dd6d7f0ec35d116401000000" clean="yes" running="yes">xodb</base>
        <base obid="dd6d7f0eee3c086401000000" running="no">todb</base>
    </osev_statis>
 */

#define STAT_XML_HEAD "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"

static char *prin_base_opened(char *stati_txt, osv_oid_t *base_obid, char *basen, int clean) {
    char obid_stri[OBJE_IDENTI_ZLEN];
    //
    stati_txt = lscpy(stati_txt, "<base obid=\"");
    stati_txt = lscpy(stati_txt, oidstr(obid_stri, base_obid));
    if (!clean) stati_txt = lscpy(stati_txt, "\" clean=\"yes\" ");
    else stati_txt = lscpy(stati_txt, "\" clean=\"no\" ");
    stati_txt = lscpy(stati_txt, "running=\"yes\">");
    stati_txt = lscpy(stati_txt, basen);
    stati_txt = lscpy(stati_txt, "</base>");
    //
    return stati_txt;
}

static char *prin_base_closed(char *stati_txt, osv_oid_t *base_obid, char *basen) {
    char obid_stri[OBJE_IDENTI_ZLEN];
    //  
    stati_txt = lscpy(stati_txt, "<base obid=\"");
    stati_txt = lscpy(stati_txt, oidstr(obid_stri, base_obid));
    stati_txt = lscpy(stati_txt, "\" running=\"no\">");
    stati_txt = lscpy(stati_txt, basen);
    stati_txt = lscpy(stati_txt, "</base>");
    //
    return stati_txt;
}

// obid, authen status, running level, running status

/*
 <?xml version="1.0" encoding="UTF-8"?>
<base_status name="earth">
    <base_obid>bfff1d8bcdb7546403000000</base_obid>
    <authen status="ON"/>
    <running="yes"/>
    <running_level>00007777</running_level>
</base_status>
 */

void filli_bstat_echo_stopped(respo_ctrl *resctl, char *basen, osv_oid_t *base_obid, int auth_stat) {
    char obid_stri[OBJE_IDENTI_ZLEN];
    char *last_str = lscpy((char *) resctl->resp_memo, STAT_XML_HEAD);
    //
    last_str = lsprif(last_str, "<base_status name=\"%s\">", basen);
    last_str = lsprif(last_str, "<base_obid>%s</base_obid>", oidstr(obid_stri, base_obid));
    if (auth_stat)
        last_str = lscpy(last_str, "<authen status=\"OFF\"/>");
    else last_str = lscpy(last_str, "<authen status=\"ON\"/>");
    last_str = lscpy(last_str, "<running=\"no\"/>");
    last_str = lscpy(last_str, "</base_status>");
    PDAT_PRODUCEO_TAIL(resctl, last_str - ((char *) resctl->resp_memo))
}

void filli_bstat_echo_running(respo_ctrl *resctl, char *basen, osv_oid_t *base_obid, int auth_stat, base_rstat *rstatu) {
    char obid_stri[OBJE_IDENTI_ZLEN];
    char *last_str = lscpy((char *) resctl->resp_memo, STAT_XML_HEAD);
    //
    last_str = lsprif(last_str, "<base_status name=\"%s\">", basen);
    last_str = lsprif(last_str, "<base_obid>%s</base_obid>", oidstr(obid_stri, base_obid));
    if (auth_stat)
        last_str = lscpy(last_str, "<authen status=\"OFF\"/>");
    else last_str = lscpy(last_str, "<authen status=\"ON\"/>");
    last_str = lscpy(last_str, "<running=\"yes\"/>");
    last_str = lsprif(last_str, "<running_level>%08x</running_level>", rstatu->running_level);
    last_str = lscpy(last_str, "</base_status>");
    PDAT_PRODUCEO_TAIL(resctl, last_str - ((char *) resctl->resp_memo))
}

// #define AUTHEN_ON   0x00
// #define AUTHEN_OFF  0x01

void filli_ostat_echo(respo_ctrl *resctl, osv_oid_t *osev_obid, int auth_stat) {
    char obid_stri[OBJE_IDENTI_ZLEN];
    char *last_str = lscpy((char *) resctl->resp_memo, STAT_XML_HEAD);
    //
    last_str = lsprif(last_str, "<osev_status name=\"%s\">", get_osev_name());
    last_str = lsprif(last_str, "<osev_obid>%s</osev_obid>", oidstr(obid_stri, osev_obid));
    if (auth_stat)
        last_str = lscpy(last_str, "<authen status=\"OFF\"/>");
    else last_str = lscpy(last_str, "<authen status=\"ON\"/>");
    last_str = lscpy(last_str, "</osev_status>");
    PDAT_PRODUCEO_TAIL(resctl, last_str - ((char *) resctl->resp_memo))
}

// obid, authen status

void filli_ostai_osev(respo_ctrl *resctl, osv_oid_t *osev_obid, int auth_stat) {
    char obid_stri[OBJE_IDENTI_ZLEN];
    char *last_str = lscpy((char *) resctl->resp_memo, STAT_XML_HEAD);
    //
    last_str = lsprif(last_str, "<osev_statis name=\"%s\">", get_osev_name());
    last_str = lsprif(last_str, "<osev_obid>%s</osev_obid>", oidstr(obid_stri, osev_obid));
    if (auth_stat)
        last_str = lscpy(last_str, "<authen status=\"OFF\"/>");
    else last_str = lscpy(last_str, "<authen status=\"ON\"/>");
    last_str = lscpy(last_str, "</osev_statis>");
    PDAT_PRODUCEO_TAIL(resctl, last_str - ((char *) resctl->resp_memo))
}

void filli_ostai_base(respo_ctrl *resctl, char **basnp) {
    osv_oid_t base_obid;
    int clean;
    char *last_str = lscpy((char *) resctl->resp_memo, STAT_XML_HEAD);
    //
    char **base_namp = basnp;
    last_str = lscpy(last_str, "<base_statis>");
    for (; base_namp[0x00]; ++base_namp) {
        parse_base_attri(&base_obid, base_namp[0x00]);
        if (valid_base_opened(base_namp[0x00]))
            last_str = prin_base_closed(last_str, &base_obid, base_namp[0x00]);
        else {
            clean = VALID_BCLEAN_BZL(base_namp[0x00]);
            last_str = prin_base_opened(last_str, &base_obid, base_namp[0x00], clean);
        }
    }
    last_str = lscpy(last_str, "</base_statis>");
    PDAT_PRODUCEO_TAIL(resctl, last_str - ((char *) resctl->resp_memo))
}

//

char *filli_bstai_base(respo_ctrl *resctl, char *basen, osv_oid_t *base_obid) {
    int clean;
    char *last_str = lscpy((char *) resctl->resp_memo, STAT_XML_HEAD);
    //
    last_str = lscpy(last_str, "<base_statis>");
    if (valid_base_opened(basen))
        last_str = prin_base_closed(last_str, base_obid, basen);
    else {
        clean = VALID_BCLEAN_BZL(basen);
        last_str = prin_base_opened(last_str, base_obid, basen, clean);
    }
    last_str = lscpy(last_str, "</base_statis>");
    // OSEVPF("(char *) resctl->resp_memo:|%s|\n", (char *) resctl->resp_memo);
    PDAT_PRODUCEO_TAIL(resctl, last_str - ((char *) resctl->resp_memo))
    return last_str;
}

char *filli_qstai_base(respo_ctrl *resctl, char *basen, osv_oid_t *base_obid) {
    int clean;
    char *last_str = lscpy((char *) resctl->resp_memo, STAT_XML_HEAD);
    //
    last_str = lscpy(last_str, "<base_statis>");
    if (valid_base_opened(basen))
        last_str = prin_base_closed(last_str, base_obid, basen);
    else {
        clean = VALID_BCLEAN_BZL(basen);
        last_str = prin_base_opened(last_str, base_obid, basen, clean);
    }
    last_str = lscpy(last_str, "</base_statis>");
    // OSEVPF("(char *) resctl->resp_memo:|%s|\n", (char *) resctl->resp_memo);
    PDAT_PRODUCEM_TAIL(resctl, last_str - ((char *) resctl->resp_memo))
    return last_str;
}

//

void filli_obje_iden(respo_ctrl *resctl, osv_oid_t *base_obid) {
    OBID_BINARY_COPY((osv_oid_t *) resctl->resp_memo, base_obid)
    PDAT_PRODUCEO_TAIL(resctl, OBJE_IDENTI_BLEN)
}
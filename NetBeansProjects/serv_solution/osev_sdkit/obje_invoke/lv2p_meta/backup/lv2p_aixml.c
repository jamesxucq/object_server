#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "kcomm_header.h"


#define "lv2p_aixml.h"

//

int build_lv2p_attrib(char *lv2p_attri, osv_oid_t *lv2p_obid, char *lv2pn, unsigned long version, integri *olist) {
    MK_ZERO(lv2p_attri);
    char *last_str = lscpy(lv2p_attri, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
    char plai_sid[STOR_IDENTI_ZLEN];
    last_str = lsprif(last_str, "<lv2p_metada><stora_id>%s</stora_id>", oid_sidstr(plai_sid, lv2p_obid));
    OSEVPF("oid_sidstr(plai_sid, lv2p_obid):|%s|\n", plai_sid);
    last_str = lsprif(last_str, "<lv2p_name>%s</lv2p_name>", lv2pn);
    last_str = lscpy(last_str, "<lv2p_atti>");
    last_str = lsprif(last_str, "<version>%lu</version>", version);
    last_str = lscpy(last_str, "<integrity>");
    for (; olist; olist = olist->next)
        last_str = lsprif(last_str, "<lev1 range=\"%d\" lv2pn=\"%s\">%s</lev1>", olist->rang_type, olist->lv2pn, olist->lev1n);
    last_str = lscpy(last_str, "</integrity>");
    last_str = lscpy(last_str, "</lv2p_atti></lv2p_metada>\n");
    //
    OSEVPF("[FUNC]:save_lv2p_attrib attrib_cont:\n|%s|\n", attrib_cont);
    return 0x00;
}

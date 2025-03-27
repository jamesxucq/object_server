
#include "commo_header.h"
#include "kcomm_header.h"

#include "live_utili.h"
#include "privile_obje.h"

#include "filli_privi.h"

//
#define PRIV_XML_HEAD "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"

// <role obid="91d971f466d82b6407000000" type="OSEV">admin</role>

static char *list_role_privi(char *last_str, role_privi *ropriv) {
    char obid_stri[OBJE_IDENTI_ZLEN];
    last_str = lscpy(last_str, "<role obid=\"");
    last_str = lscpy(last_str, oidstr(obid_stri, &ropriv->role_obid));
    last_str = lscpy(last_str, "\" type=\"");
    if (ROLE_TYPE_OSEV == ropriv->role_type)
        last_str = lscpy(last_str, OSEV_CAPITAL_VALUE);
    else if (ROLE_TYPE_BASE == ropriv->role_type)
        last_str = lscpy(last_str, BASE_CAPITAL_VALUE);
    last_str = lscpy(last_str, "\">");
    last_str = lscpy(last_str, ropriv->role_name);
    last_str = lscpy(last_str, "</role>");
    //
    return last_str;
}

//

/*
<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<role_list>
    <role obid="91d971f466d82b6407000000" type="OSEV">admin</role>
    <role obid="91d971f466d82b6407000000" type="OSEV">admin</role>
</role_list>
 */

void oprin_role_all(respo_ctrl *resctl, liv_list *role_list) {
    OSEVPF("[FUNC]:oprin_role_all\n");
    char *last_str = lscpy((char *) resctl->resp_memo, PRIV_XML_HEAD);
    //
    role_privi *ropriv;
    liv_list *rlist = role_list;
    last_str = lscpy(last_str, "<role_list>");
    for (; rlist; rlist = rlist->next) {
        ropriv = (role_privi *) rlist->liv_data;
        if (ROLE_TYPE_OSEV == ropriv->role_type)
            last_str = list_role_privi(last_str, ropriv);
    }
    last_str = lscpy(last_str, "</role_list>");
    PDAT_PRODUCEO_TAIL(resctl, last_str - ((char *) resctl->resp_memo))
}

// <privi obid="91d971f466d82b6407000000" priv_code="01000700"/>

static char *list_dist_privi(char *last_str, dist_privi *priv_poin) {
    char obid_stri[OBJE_IDENTI_ZLEN];
    last_str = lscpy(last_str, "<privi obid=\"");
    last_str = lscpy(last_str, oidstr(obid_stri, &priv_poin->dist_obid));
    last_str = lscpy(last_str, "\" priv_code=\"");
    last_str = lsprif(last_str, "%08X", priv_poin->privile_code);
    last_str = lscpy(last_str, "\"/>");
    //
    return last_str;
}

/*
<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<role_privi>
    <role obid="91d971f466d82b6407000000" type="OSEV">admin</role>
    <privi_list>
        <privi obid="91d971f466d82b6407000000" priv_code="01000700"/>
        <privi obid="91d971f466d82b6407000000" priv_code="01000700"/>
        <privi obid="91d971f466d82b6407000000" priv_code="01000700"/>
    </privi_list>
</role_privi>
 */

void oprin_role_name(respo_ctrl *resctl, role_privi *ropriv) {
    OSEVPF("[FUNC]:oprin_role_name\n");
    char *last_str = lscpy((char *) resctl->resp_memo, PRIV_XML_HEAD);
    last_str = lscpy(last_str, "<role_privi>");
    last_str = list_role_privi(last_str, ropriv);
    //
    dist_privi *priv_poin = ropriv->priv_array;
    last_str = lscpy(last_str, "<privi_list>");
    int priv_inde = 0x00;
    for (; (MAX_PRIVI_SIZE > priv_inde) && DIST_PRIVI_NOT_ZERO(priv_poin); ++priv_inde, ++priv_poin) {
#ifdef _DEBUG
        char obid_stri[OBJE_IDENTI_ZLEN];
        OSEVPF("--- %s %08X\n", oidstr(obid_stri, &priv_poin->dist_obid), priv_poin->privile_code);
#endif
        FILL_UNIQUE_OBID(&priv_poin->dist_obid);
        last_str = list_dist_privi(last_str, priv_poin);
    }
    last_str = lscpy(last_str, "</privi_list>");
    last_str = lscpy(last_str, "</role_privi>");
    PDAT_PRODUCEO_TAIL(resctl, last_str - ((char *) resctl->resp_memo))
}

/*
<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<role_privi>
    <role obid="91d971f466d82b6407000000" type="OSEV">admin</role>
    <privi_list>
        <privi obid="91d971f466d82b6407000000" priv_code="01000700"/>
        <privi obid="91d971f466d82b6407000000" priv_code="01000700"/>
        <privi obid="91d971f466d82b6407000000" priv_code="01000700"/>
    </privi_list>
</role_privi>
 */

void bprin_role_name(respo_ctrl *resctl, role_privi *ropriv, role_privi *sto_ropri) {
    OSEVPF("[FUNC]:bprin_role_name\n");
    char *last_str = lscpy((char *) resctl->resp_memo, PRIV_XML_HEAD);
    last_str = lscpy(last_str, "<role_privi>");
    last_str = list_role_privi(last_str, ropriv);
    //
    dist_privi *priv_poin = sto_ropri->priv_array;
    last_str = lscpy(last_str, "<privi_list>");
    int priv_inde = 0x00;
    for (; (MAX_PRIVI_SIZE > priv_inde) && DIST_PRIVI_NOT_ZERO(priv_poin); ++priv_inde, ++priv_poin) {
        FILL_UNIQUE_OBID(&priv_poin->dist_obid);
        last_str = list_dist_privi(last_str, priv_poin);
    }
    last_str = lscpy(last_str, "</privi_list>");
    //
    priv_poin = ropriv->priv_array;
    last_str = lscpy(last_str, "<cache_privi>");
    priv_inde = 0x00;
    for (; (MAX_PRIVI_SIZE > priv_inde) && DIST_PRIVI_NOT_ZERO(priv_poin); ++priv_inde, ++priv_poin) {
        // FILL_UNIQUE_OBID(&priv_poin->dist_obid);
        last_str = list_dist_privi(last_str, priv_poin);
    }
    last_str = lscpy(last_str, "</cache_privi>");
    last_str = lscpy(last_str, "</role_privi>");
    PDAT_PRODUCEO_TAIL(resctl, last_str - ((char *) resctl->resp_memo))
    OSEVPF("end bprin_role_name\n");
}

//

/*
<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<role_list>
    <role obid="91d971f466d82b6407000000" type="OSEV">admin</role>
    <role obid="91d971f466d82b6407000000" type="OSEV">admin</role>
</user_list>
 */

void bprin_role_all(respo_ctrl *resctl, liv_list *role_list) {
    OSEVPF("[FUNC]:bprin_role_all\n");
    char *last_str = lscpy((char *) resctl->resp_memo, PRIV_XML_HEAD);
    //
    role_privi *ropriv;
    liv_list *rlist = role_list;
    last_str = lscpy(last_str, "<role_list>");
    for (; rlist; rlist = rlist->next) {
        ropriv = (role_privi *) rlist->liv_data;
        if (ROLE_TYPE_BASE == ropriv->role_type)
            last_str = list_role_privi(last_str, ropriv);
    }
    last_str = lscpy(last_str, "</role_list>");
    PDAT_PRODUCEO_TAIL(resctl, last_str - ((char *) resctl->resp_memo))
}

// <user obid="91d971f466d82b6407000000">rtd3</user>

static char *list_user_privi(char *last_str, user_privi *uepriv) {
    char obid_stri[OBJE_IDENTI_ZLEN];
    last_str = lscpy(last_str, "<user obid=\"");
    last_str = lscpy(last_str, oidstr(obid_stri, &uepriv->user_obid));
    last_str = lscpy(last_str, "\">");
    last_str = lscpy(last_str, uepriv->user_name);
    last_str = lscpy(last_str, "</user>");
    //
    return last_str;
}

/*
<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<user_list>
    <user obid="91d971f466d82b6407000000">rtd3</user>
    <user obid="91d971f466d82b6407000000">rtd3</user>
    <user obid="91d971f466d82b6407000000">rtd3</user>
</user_list>
 */

void filli_user_all(respo_ctrl *resctl, liv_list *ouse_list) {
    OSEVPF("[FUNC]:filli_user_all\n");
    char *last_str = lscpy((char *) resctl->resp_memo, PRIV_XML_HEAD);
    //
    liv_list *ulist = ouse_list;
    last_str = lscpy(last_str, "<user_list>");
    for (; ulist; ulist = ulist->next) {
        last_str = list_user_privi(last_str, (user_privi *) ulist->liv_data);
    }
    last_str = lscpy(last_str, "</user_list>");
    PDAT_PRODUCEO_TAIL(resctl, last_str - ((char *) resctl->resp_memo))
}

// <role obid="91d971f466d82b6407000000" type="OSEV">admin</role>

static char *list_user_role(char *last_str, role_privi *ropriv) {
    OSEVPF("[FUNC]:list_user_role, ropriv:|%p|\n", ropriv);
    char obid_stri[OBJE_IDENTI_ZLEN];
    last_str = lscpy(last_str, "<role obid=\"");
    OSEVPF("1 xxxxxxxxxxx\n");
    last_str = lscpy(last_str, oidstr(obid_stri, &ropriv->role_obid));
    OSEVPF("2 xxxxxxxxxxx\n");
    last_str = lscpy(last_str, "\" type=\"");
    if (ROLE_TYPE_OSEV == ropriv->role_type)
        last_str = lscpy(last_str, OSEV_CAPITAL_VALUE);
    else if (ROLE_TYPE_BASE == ropriv->role_type)
        last_str = lscpy(last_str, BASE_CAPITAL_VALUE);
    last_str = lscpy(last_str, "\">");
    last_str = lscpy(last_str, ropriv->role_name);
    last_str = lscpy(last_str, "</role>");
    //
    OSEVPF("end list_user_role\n");
    return last_str;
}

/*
<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<user_role>
    <user obid="91d971f466d82b6407000000">rtd3</user>
    <role_list>
        <role obid="91d971f466d82b6407000000" type="OSEV">admin</role>
        <role obid="91d971f466d82b6407000000" type="OSEV">admin</role>
        <role obid="91d971f466d82b6407000000" type="OSEV">admin</role>
    </user_list>
</user_role>
 */

void filli_user_name(respo_ctrl *resctl, user_privi *uepriv) {
    OSEVPF("[FUNC]:filli_user_name\n");
    char *last_str = lscpy((char *) resctl->resp_memo, PRIV_XML_HEAD);
    last_str = lscpy(last_str, "<user_role>");
    last_str = list_user_privi(last_str, uepriv);
    //
    role_privi **ropriv = uepriv->ropriv;
    last_str = lscpy(last_str, "<role_list>");
    unsigned int inde = 0x00;
    OSEVPF("[FUNC]:MAX_ROLE_SIZE\n");
    for (; (MAX_ROLE_SIZE > inde) && ropriv[0x00]; ++inde, ++ropriv)
        last_str = list_user_role(last_str, ropriv[0x00]);
    last_str = lscpy(last_str, "</role_list>");
    last_str = lscpy(last_str, "</user_role>");
    OSEVPF("end filli_user_name\n");
    PDAT_PRODUCEO_TAIL(resctl, last_str - ((char *) resctl->resp_memo))
}

//

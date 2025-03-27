
#include "commo_header.h"

#include "debug_funct_cp.h"
#include "liv_list.h"

//

char *p_role_privi(char *last_str, role_privi *ropriv) {
    char obid_stri[OBJE_IDENTI_ZLEN];
    last_str = lccpy(last_str, '|');
    last_str = lscpy(last_str, oidstr(obid_stri, &ropriv->role_obid));
    last_str = lccpy(last_str, '|');
    last_str = lscpy(last_str, ropriv->role_name);
    last_str = lccpy(last_str, '|');
    if (ROLE_TYPE_OSEV == ropriv->role_type)
        last_str = lscpy(last_str, "OSEV");
    else if (ROLE_TYPE_BASE == ropriv->role_type)
        last_str = lscpy(last_str, "ODB");
    last_str = lscpy(last_str, "|\n");
    //
    return last_str;
}

void p_role_privi_list(liv_list *role_list) {
    printf("[FUNC]:p_role_privi_list\n");
    char temp[512];
    liv_list * rlist = role_list;
    printf("role_privi_list -------------\n");
    for (; rlist; rlist = rlist->next) {
        p_role_privi(temp, (role_privi *) rlist->liv_data);
        printf("%s", temp);
    }
}

static char *p_user_privi(char *last_str, user_privi *uepriv) {
    char obid_stri[OBJE_IDENTI_ZLEN];
    last_str = lccpy(last_str, '|');
    last_str = lscpy(last_str, oidstr(obid_stri, &uepriv->user_obid));
    last_str = lccpy(last_str, '|');
    last_str = lscpy(last_str, uepriv->user_name);
    last_str = lscpy(last_str, "|\n");
    return last_str;
}

/*
static char *p_user_role(char *last_str, role_privi *ropriv) {
    char obid_stri[OBJE_IDENTI_ZLEN];
    last_str = lscpy(last_str, "    |");
    last_str = lscpy(last_str, oidstr(obid_stri, &ropriv->role_obid));
    last_str = lccpy(last_str, '|');
    last_str = lscpy(last_str, ropriv->role_name);
    last_str = lccpy(last_str, '|');
    if (ROLE_TYPE_OSEV == ropriv->role_type)
        last_str = lscpy(last_str, "OSEV");
    else if (ROLE_TYPE_BASE == ropriv->role_type)
        last_str = lscpy(last_str, "ODB");
    last_str = lscpy(last_str, "|\n");
    //
    return last_str;
}
 */

static char *p_user_role(char *last_str, osv_oid_t *role_obid) {
    char obid_stri[OBJE_IDENTI_ZLEN];
    last_str = lscpy(last_str, "    |");
    last_str = lscpy(last_str, oidstr(obid_stri, role_obid));
    last_str = lscpy(last_str, "|\n");
    return last_str;
}

void p_user_privi_list(liv_list *user_list) {
    char temp[512];
    liv_list * ulist = user_list;
    printf("user_privi_list -------------\n");
    for (; ulist; ulist = ulist->next) {
        char *last_str = p_user_privi(temp, (user_privi *) ulist->liv_data);
        //
        osv_oid_t *role_obid = ((user_privi *) ulist->liv_data)->role_obid;
        unsigned int inde = 0x00;
        for (; (MAX_ROLE_SIZE > inde) && CHK_ZERO_OBID(role_obid); ++inde, ++role_obid)
            last_str = p_user_role(last_str, role_obid);
        //
        printf("%s", temp);
    }
    printf("------------- user_privi_list\n");
}

void p_user_all(liv_list *ouse_list) {
    printf("[FUNC]:p_user_all\n");
    char obid_stri[OBJE_IDENTI_ZLEN];
    liv_list *ulist = ouse_list;
    for (; ulist; ulist = ulist->next) {
        printf("--------------------------\n");
        user_privi *uepriv = (user_privi *) ulist->liv_data;
        printf("%s %s\n", oidstr(obid_stri, &uepriv->user_obid), uepriv->user_name);
    }
}

void p_dist_privi(dist_privi *priv_poin) {
    printf("[FUNC]:p_dist_privi\n");
    char obid_stri[OBJE_IDENTI_ZLEN];
    printf("priv_poin->dist_obid:|%s|\n", oidstr(obid_stri, &priv_poin->dist_obid));
    printf("priv_poin->privile_code:|%08x|\n", priv_poin->privile_code);
}

// for debug

char *echo_role_privi(char *last_str, role_privi *ropriv) {
    char obid_stri[OBJE_IDENTI_ZLEN];
    last_str = lccpy(last_str, '|');
    last_str = lscpy(last_str, oidstr(obid_stri, &ropriv->role_obid));
    last_str = lccpy(last_str, '|');
    last_str = lscpy(last_str, ropriv->role_name);
    last_str = lccpy(last_str, '|');
    if (ROLE_TYPE_OSEV == ropriv->role_type)
        last_str = lscpy(last_str, "OSEV");
    else if (ROLE_TYPE_BASE == ropriv->role_type)
        last_str = lscpy(last_str, "ODB");
    last_str = lscpy(last_str, "|\n");
    //
    return last_str;
}

char *echo_dist_privi(char *last_str, dist_privi *priv_poin) {
    char obid_stri[OBJE_IDENTI_ZLEN];
    last_str = lscpy(last_str, "    |");
    last_str = lscpy(last_str, oidstr(obid_stri, &priv_poin->dist_obid));
    last_str = lccpy(last_str, '|');
    last_str = lsprif(last_str, "%08X", priv_poin->privile_code);
    last_str = lscpy(last_str, "|\n");
    //
    return last_str;
}

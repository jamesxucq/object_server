#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commo_header.h"
#include "osev_clie_clang.h"
#include "clit_macro.h"

#include "osvp_utili.h"
#include "debug_funct_sh.h"

//
#define UNAME_DEFAULT_VALUE  "uname"
#define PASWD_DEFAULT_VALUE  "paswd"

//
// osvp://host[:port]/[database]?[uname=xxx&paswd=12345]
// osvp://10.0.0.103:8848/?uname=james&paswd=123456
#define OSVP_HEAD "osvp://"

int get_conne_type(char *osvp_uri) {
    osvp_uri = strstr(osvp_uri, OSVP_HEAD);
    if (!osvp_uri) return NULL_CONNE;
    //
    osvp_uri = strchr(osvp_uri + sslen(OSVP_HEAD), '/');
    if (!osvp_uri) return OSEV_CONNE;
    for (++osvp_uri; '\0' != osvp_uri[0x00]; ++osvp_uri) {
        if (' ' != osvp_uri[0x00]) break;
    }
    char *tokep = strchr(osvp_uri, '?');
    if (tokep) {
        if (tokep[0x00] == osvp_uri[0x00] || !strncmp(OSEV_DEFAULT_VALUE, osvp_uri, sslen(OSEV_DEFAULT_VALUE)))
            return OSEV_CONNE;
    } else {
        if ('\0' == osvp_uri[0x00] || !strncmp(OSEV_DEFAULT_VALUE, osvp_uri, sslen(OSEV_DEFAULT_VALUE)))
            return OSEV_CONNE;
    }
    //
    return BASE_CONNE;
}

// osvp://192.168.1.105:8888/?uname=james&paswd=123456
// osvp://192.168.1.105:8888/?uname=james&paswd=******

char *hide_instru(char *line_str) {
    char *lstok = line_str;
    lstok = strstr(lstok, OSVP_HEAD);
    if (!lstok) return NULL;
    lstok = strchr(lstok + sslen(OSVP_HEAD), '?');
    if (!lstok) return NULL;
    lstok = strstr(++lstok, PASWD_DEFAULT_VALUE);
    if (!lstok) return NULL;
    lstok += sslen(PASWD_DEFAULT_VALUE);
    for (; lstok[0x00] && (' ' == lstok[0x00] || '=' == lstok[0x00]); ++lstok);
    for (; lstok[0x00] && (' ' != lstok[0x00] && '&' != lstok[0x00]); ++lstok)
        lstok[0x00] = '*';
    //
    return line_str;
}

//

static char *parse_host(serv_addr *saddr, char *addr_text) {
    char *delmi = strchr(addr_text, ':');
    if (delmi) {
        delmi[0x00] = '\0';
        strcpy(saddr->sin_addr, addr_text);
        kill_blank(saddr->sin_addr);
        kill_blank(++delmi);
        saddr->sin_port = atoi(delmi);
    } else {
        strcpy(saddr->sin_addr, addr_text);
        kill_blank(saddr->sin_addr);
        saddr->sin_port = OSEV_DEFAULT_PORT;
    }
    return addr_text;
}

//

static char *split_authe(char *user_name, char *password, char *auth_text) {
    char *delmi = strchr(auth_text, '&');
    if (!delmi) return NULL;
    delmi[0x00] = '\0';
    //
    char *toksp;
    PASS_TBLANK(toksp, auth_text)
            char *tokep = strchr(toksp, '=');
    if (!tokep) return NULL;
    tokep[0x00] = '\0';
    if (strncmp(UNAME_DEFAULT_VALUE, toksp, sslen(UNAME_DEFAULT_VALUE))) {
        if (!strncmp(PASWD_DEFAULT_VALUE, toksp, sslen(PASWD_DEFAULT_VALUE))) {
            strcpy(password, tokep + 0x01);
            kill_blank(password);
        } else return NULL;
    } else {
        strcpy(user_name, tokep + 0x01);
        kill_blank(user_name);
    }
    // strcpy(password, ++delmi);
    PASS_TBLANK(toksp, delmi + 0x01)
    tokep = strchr(toksp, '=');
    if (!tokep) return NULL;
    tokep[0x00] = '\0';
    if (strncmp(PASWD_DEFAULT_VALUE, toksp, sslen(PASWD_DEFAULT_VALUE))) {
        if (!strncmp(UNAME_DEFAULT_VALUE, toksp, sslen(UNAME_DEFAULT_VALUE))) {
            strcpy(user_name, tokep + 0x01);
            kill_blank(user_name);
        } else return NULL;
    } else {
        strcpy(password, tokep + 0x01);
        kill_blank(password);
    }
    //
    return delmi;
}

static char *split_base(char *osev_base, char *resou_text) {
    strcpy(osev_base, resou_text);
    kill_blank(osev_base);
    return osev_base;
}

// osvp://192.168.1.105:8888/odb?uname=james&paswd=123456

static int parse_ospuri(serv_addr *saddr, auth_meta *authm, char *osev_base, const char *osvp_uri) {
    char osvp_body[OSVPURI_LENGTH];
    char *toksp, *tokep;
    //
    toksp = strstr(osvp_uri, OSVP_HEAD);
    if (!toksp) return OSVPURI_ILLEGAL;
    strcpy(osvp_body, toksp + sslen(OSVP_HEAD));
    //
    toksp = strchr(osvp_body, '/');
    tokep = strchr(osvp_body, '?');
    if (tokep && toksp) {
        // osvp://10.0.0.103:8848/todb?uname=james&paswd=123456
        toksp[0x00] = '\0';
        tokep[0x00] = '\0';
        parse_host(saddr, osvp_body);
        split_base(osev_base, toksp + 0x01);
        if (!split_authe(authm->user_name, authm->pass_word, tokep + 0x01))
            return OSVPURI_ILLEGAL;
        return USER_HOST_BASE;
    } else if (tokep && !toksp) {
        // osvp://10.0.0.103:8848?uname=james&paswd=123456
        tokep[0x00] = '\0';
        parse_host(saddr, osvp_body);
        osev_base[0x00] = '\0';
        if (!split_authe(authm->user_name, authm->pass_word, tokep + 0x01))
            return OSVPURI_ILLEGAL;
        return USER_HOST_URI;
    } else if (!tokep && toksp) {
        // osvp://10.0.0.103:8848/todb
        toksp[0x00] = '\0';
        parse_host(saddr, osvp_body);
        split_base(osev_base, toksp + 0x01);
        MAKE_AUTH_ZERO(authm)
        return HOST_BASE_URI;
    } else if (!tokep && !toksp) {
        // osvp://10.0.0.103:8848
        parse_host(saddr, osvp_body);
        osev_base[0x00] = '\0';
        MAKE_AUTH_ZERO(authm)
        return HOST_ONLY_URI;
    }
    //
    return OSVPURI_ILLEGAL;
}

//

int parse_conne_ospuri(osvp_auth *clie_auth, const char *osvp_uri) {
    CLIT_PF("[FUNC]:parse_conne_ospuri\n");
    char osev_base[OSEV_LENGTH];
    int parval = parse_ospuri(&clie_auth->saddr, &clie_auth->authe, osev_base, osvp_uri);
    if (OSVPURI_ILLEGAL == parval) return OSVPURI_ILLEGAL;
    if (NOT_ZERO(osev_base))
        strcpy(clie_auth->osev_base, osev_base);
    else strcpy(clie_auth->osev_base, OSEV_DEFAULT_VALUE);
    //
#ifdef _DEBUG
    PRIN_clit_auth(clie_auth, osvp_uri);
#endif
    return parval;
}

//

char *split_ospuri_base(char *osev_base, const char *osvp_uri) {
    char *toksp, *tokep;
    //
    toksp = strstr(osvp_uri, OSVP_HEAD);
    if (!toksp) return NULL;
    toksp += sslen(OSVP_HEAD);
    //
    toksp = strchr(toksp, '/');
    if (toksp) {
        tokep = strchr(++toksp, '?');
        if (tokep) {
            strzcpy(osev_base, toksp, tokep - toksp);
        } else strcpy(osev_base, toksp);
        kill_blank(osev_base);
    } else if (!toksp) osev_base[0x00] = '\0';
    //
    return osev_base;
}














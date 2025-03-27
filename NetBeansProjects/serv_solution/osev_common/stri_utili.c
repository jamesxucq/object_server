#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdarg.h>

#include "utility/strptime.h"
#include "utility/last_stri.h"
#include "commo_macro.h"
#include "osev_datyp.h"
#include "osev_macro.h"
#include "stri_utili.h"
#include "debug_funct_osv.h"

char *utc_time_text(time_t utctime) { // Wed, 15 Nov 1995 04:58:08 GMT
    static char timestr[TIME_LENGTH];
    struct tm *utctm;
    //
    if (!utctime) utctime = time(NULL);
    utctm = gmtime(&utctime);
    if (!strftime(timestr, TIME_LENGTH, "%a, %d %b %Y %H:%M:%S %Z", utctm))
        return NULL;
    //
    return timestr;
}

time_t utc_time_value(char *timestr) { // Wed, 15 Nov 1995 04:58:08 GMT
    struct tm utctm;
    //
    if (!timestr) return 0;
    memset(&utctm, '\0', sizeof (struct tm));
    _strptime(&utctm, timestr);
    time_t calender = _mktime(&utctm);
    //
    return calender;
}

char *random_seion_id() {
    static char rand_str[MIN_TLENG];
    static unsigned int tatol;
    snprintf(rand_str, MIN_TLENG, "%d-%u-%d", getpid(), (uint32) time(NULL), ++tatol);
    return rand_str;
}

char *random_valid() {
    static char rand_str[MIN_TLENG];
    static long int last_seed;
    char code_array[62] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    //
    if (!last_seed) last_seed = time(NULL);
    int tatol = 0x00;
    for (; 20 > tatol; ++tatol) {
        srandom((unsigned int) last_seed);
        last_seed = random();
        rand_str[tatol] = code_array[last_seed % 62];
    }
    rand_str[tatol] = '\0';
    //
    return rand_str;
}

char *random_accesskey() {
    static char rand_str[MIN_TLENG];
    static long int last_seed;
    char code_array[62] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    //
    if (!last_seed) last_seed = time(NULL);
    int tatol = 0x00;
    for (; 20 > tatol; ++tatol) {
        srandom((unsigned int) last_seed);
        last_seed = random();
        rand_str[tatol] = code_array[last_seed % 62];
    }
    rand_str[tatol] = '\0';
    //
    return rand_str;
}

void saddr_split(serv_addr *saddr, const char *addr_txt) {
    char *satok = NULL;
    memset(saddr, '\0', sizeof (serv_addr));
    satok = strchr(addr_txt, ':');
    if (satok) {
        strncpy(saddr->sin_addr, addr_txt, satok - addr_txt);
        saddr->sin_port = atoi(++satok);
    } else strcpy(saddr->sin_addr, addr_txt);
}

char *next_dirpath(char *path, char *subdir) {
    static char *ditok, *toksp;
    static char fullpath[MAX_PATH * 3];
    char dirpath[MAX_PATH * 3];
    //
    if (!subdir) {
        if (!ditok) return NULL;
    } else toksp = ditok = subdir;
    ditok = strchr(++ditok, '/');
    //
    strcpy(fullpath, path);
    if (ditok) {
        strncpy(dirpath, toksp, ditok - toksp);
        strcat(fullpath, dirpath);
    } else strcat(fullpath, toksp);
    //
    return fullpath;
}

char *bakup_folder(time_t bak_time) { // Nov_15_1995_GMT
    static char folder[TIME_LENGTH];
    struct tm *utctm;
    //
    if (!bak_time) bak_time = time(NULL);
    utctm = gmtime(&bak_time);
    if (!strftime(folder, TIME_LENGTH, "%b_%d_%Y_%Z", utctm))
        return NULL;
    //
    return folder;
}

//

char *name_value(char **namep, char *stri, const char delim) {
    char *toksp;
    static char *tokep;
    //
    if (!stri) {
        if (!tokep) return NULL;
        toksp = tokep + 1;
    } else toksp = stri;
    //
    tokep = strchr(toksp, delim);
    if (tokep) *tokep = '\0';
    //
    if (namep) *namep = toksp;
    char *value = strchr(toksp, '=');
    if (value) {
        *value = '\0';
        ++value;
    } else value = toksp;
    //
    return value;
}

//


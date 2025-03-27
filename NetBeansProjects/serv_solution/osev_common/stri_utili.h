#ifndef STRI_UTILI_H_
#define STRI_UTILI_H_

#include <string.h>
#include <time.h>

#include "utility/last_stri.h"
#include "serv_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

    // char *last_bakup(char *path, char *subdir, time_t bak_time);
    char *bakup_folder(time_t bak_time);
#define LAST_BAKUP(BAKPATH, PATH, SUBDIR, BAKTIME) \
         sprintf(BAKPATH, "%s/backup/%s%s_%x", PATH, bakup_folder(BAKTIME), strrchr(SUBDIR, '/'), (uint32)BAKTIME)
#define BAKUP_PATH(BAKPATH, PATH, BAKTIME, SUBDIR) \
        sprintf(BAKPATH, "%s/backup/%s%s", PATH, bakup_folder(BAKTIME), SUBDIR + 1)

    //

    char *utc_time_text(time_t utctime);
    // Wed, 15 Nov 1995 04:58:08 GMT
#define UTC_TIME_TEXT(TIMESTR, UTCTIME) { \
    if (!strftime(TIMESTR, TIME_LENGTH, "%a, %d %b %Y %H:%M:%S %Z", gmtime(&UTCTIME))) \
        { _LOG_WARN("strftime error:%d", UTCTIME); } \
}
    time_t utc_time_value(char *timestr);
    // Wed, 15 Nov 1995 04:58:08 GMT
#define UTC_TIME_VALUE(CALENDER, TIMESTR) { \
    struct tm utctm; \
    memset(&utctm, '\0', sizeof (struct tm)); \
    _strptime(&utctm, TIMESTR); \
    CALENDER = _mktime(&utctm); \
}

    // return session id
    char *random_seion_id();
    // return valid string
    char *random_valid();
    // return access key
    char *random_accesskey();

    // 10.0.0.103:8848 return, sin_addr=10.0.0.103 , sin_port=8848
    void saddr_split(serv_addr *saddr, const char *addr_txt);

    /*Check path string contains invalid characters.*/
#define VALID_FILE_PATH(PATH) \
    ('\0' == *PATH || strlen(PATH) >= PATH_MAX || strpbrk(PATH, "\\:*?\"<>|"))

    // data move hlen length,

    inline char *inser_head(char *data, int slen, int hlen) {
        char *toksp = data + slen;
        char *tokep = toksp + hlen;
        for (; data <= toksp; --toksp, --tokep)
            tokep[0x00] = toksp[0x00];
        return data;
    }

    // next char of last end

    inline void expand_tail(char **strp, char *last) {
        strp[0x00] = (char *) strend(last);
        ++(strp[0x00]);
    }

    // name=value, namep=name, return value
    char *name_value(char **namep, char *stri, const char delim);


#ifdef __cplusplus
}
#endif

#endif /* STRI_UTILI_H_ */

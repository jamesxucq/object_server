#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "strptime.h"

//
static const char *abmon[12] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

// Wed, 15 Nov 1995 04:58:08 GMT

int _strptime(struct tm *tp, char *ts) {
    char *s = " :";
    char *toke, *prev;
    char timestr[32];
    //
    strcpy(timestr, ts);
    prev = timestr;
    int i, count = 0;
    do {
        toke = strpbrk(prev, s);
        if (toke) toke[0] = '\0';
        switch (count) {
            case 1:
                tp->tm_mday = atoi(prev);
                break;
            case 2:
                for (i = 0; i < 12; ++i) {
                    if (!strcmp(abmon[i], prev)) tp->tm_mon = i;
                }
                break;
            case 3:
                tp->tm_year = atoi(prev) - 1900;
                break;
            case 4:
                tp->tm_hour = atoi(prev);
                break;
            case 5:
                tp->tm_min = atoi(prev);
                break;
            case 6:
                tp->tm_sec = atoi(prev);
                break;
        }
        ++count;
        if (toke) prev = toke + 1;
    } while (toke);
    //
    return 0;
}

//

unsigned long _mktime(struct tm *tp) {
    unsigned int mon = tp->tm_mon + 1, year = tp->tm_year + 1900;
    /* 1..12 -> 11,12,1..10 */
    if (0 >= (int) (mon -= 2)) {
        mon += 12; /* Puts Feb last since it has leap day */
        year -= 1;
    }
    //
    return ((((unsigned long)
            (year / 4 - year / 100 + year / 400 + 367 * mon / 12 + tp->tm_mday) +
            year * 365 - 719499)*24 + tp->tm_hour)*60 + tp->tm_min)*60 + tp->tm_sec;
}

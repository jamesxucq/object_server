#ifndef _STRPTIME_H_
#define _STRPTIME_H_

#ifdef	__cplusplus
extern "C" {
#endif

#include <time.h>

    int _strptime(struct tm *tp, char *ts);
    unsigned long _mktime(struct tm *tp);

#ifdef	__cplusplus
}
#endif

#endif /* _STRPTIME_H_ */
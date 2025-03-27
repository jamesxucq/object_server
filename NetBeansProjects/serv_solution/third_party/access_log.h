
/* 
 * File:   access_logger.h
 * Author: James Xu
 *
 * Created on 2012
 */

#ifndef ACCESS_LOGGER_H
#define	ACCESS_LOGGER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

    //
    void access_initial(char *logfile);
    void access_final();
    void access_printf(const char *fmt, ...);

    //
#ifdef _DEBUG
#define LOG_ACCESS(fmt, ...)  \
	access_printf("[%s %d %s]:"fmt"\n", __FILE__, __LINE__,\
		   	__FUNCTION__, ##__VA_ARGS__)
#else
#define LOG_ACCESS(fmt, ...)  \
	access_printf(":"fmt"\n", ##__VA_ARGS__)
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* ACCESS_LOGGER_H */


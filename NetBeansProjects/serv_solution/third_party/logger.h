#ifndef LOGGER_H_
#define LOGGER_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif

    //

    enum _LOG_LVL_T_ {
        LOG_LVL_FATAL = 0,
        LOG_LVL_ERROR,
        LOG_LVL_WARN,
        LOG_LVL_INFO,
        //
        LOG_LVL_DEBUG,
        LOG_LVL_TRACE,
        LOG_LVL_MAX
    };

    typedef enum _LOG_LVL_T_ LOG_LVL_T;

    //
    void log_initial(char *logfile, LOG_LVL_T log_lvl);
    void log_final();
    void log_printf_c(LOG_LVL_T log_lvl, const char *fmt, ...);
    void log_printf_cpp(LOG_LVL_T log_lvl, const char *fmt, ...);

    //
#ifdef _DEBUG
#define _LOG_FATAL(fmt, ...)  \
        log_printf_c(LOG_LVL_FATAL, "[%s %d %s]:"fmt"\n", __FILE__, __LINE__, \
                        __FUNCTION__, ##__VA_ARGS__)
#else
#define _LOG_FATAL(fmt, ...)  \
        log_printf_c(LOG_LVL_FATAL, ":"fmt"\n", ##__VA_ARGS__)
#endif

    //
#ifdef _DEBUG
#define _LOG_ERROR(fmt, ...)  \
        log_printf_c(LOG_LVL_ERROR, "[%s %d %s]:"fmt"\n", __FILE__, __LINE__, \
                        __FUNCTION__, ##__VA_ARGS__)
#else
#define _LOG_ERROR(fmt, ...)  \
        log_printf_c(LOG_LVL_ERROR, ":"fmt"\n", ##__VA_ARGS__)
#endif

    //
#ifdef __cplusplus
#define _LOG_WARN(fmt, ...)  \
        log_printf_cpp(LOG_LVL_WARN, fmt, ##__VA_ARGS__)
#else /* __cplusplus */
#ifdef _DEBUG
#define _LOG_WARN(fmt, ...)  \
        log_printf_c(LOG_LVL_WARN, "[%s %d %s]:"fmt"\n", __FILE__, __LINE__, \
                        __FUNCTION__, ##__VA_ARGS__)
#else /* _DEBUG */
#define _LOG_WARN(fmt, ...)  \
        log_printf_c(LOG_LVL_WARN, ":"fmt"\n", ##__VA_ARGS__)
#endif /* _DEBUG */
#endif /* __cplusplus */

    //
#ifdef __cplusplus
#define _LOG_INFO(fmt, ...)  \
        log_printf_cpp(LOG_LVL_INFO, fmt, ##__VA_ARGS__)
#else /* __cplusplus */
#ifdef _DEBUG
#define _LOG_INFO(fmt, ...)  \
        log_printf_c(LOG_LVL_INFO, "[%s %d %s]:"fmt"\n", __FILE__, __LINE__, \
                        __FUNCTION__, ##__VA_ARGS__)
#else /* _DEBUG */
#define _LOG_INFO(fmt, ...)  \
        log_printf_c(LOG_LVL_INFO, ":"fmt"\n", ##__VA_ARGS__)
#endif /* _DEBUG */
#endif /* __cplusplus */

    //

#ifdef _DEBUG
#ifdef __cplusplus
#define _LOG_DEBUG(fmt, ...)  \
        log_printf_cpp(LOG_LVL_DEBUG, fmt, ##__VA_ARGS__)
#else /* __cplusplus */    
#define _LOG_DEBUG(fmt, ...)  \
        log_printf_c(LOG_LVL_DEBUG, "[%s %d %s]:"fmt"\n", __FILE__, __LINE__,\
		   	__FUNCTION__, ##__VA_ARGS__)
#endif /* __cplusplus */
#else
#define _LOG_DEBUG(fmt, ...)
#endif

    //

#ifdef _DEBUG
#ifdef __cplusplus
#define _LOG_TRACE(fmt, ...)  \
        log_printf_cpp(LOG_LVL_TRACE, fmt, ##__VA_ARGS__)
#else /* __cplusplus */   
#define _LOG_TRACE(fmt, ...)  \
        log_printf_c(LOG_LVL_TRACE, "[%s %d %s]:"fmt"\n", __FILE__, __LINE__, \
                        __FUNCTION__, ##__VA_ARGS__)
#endif /* __cplusplus */
#else
#define _LOG_TRACE(fmt, ...)
#endif


#ifdef __cplusplus
}
#endif

#endif /* LOGGER_H_ */


/* 
 * File:   error.h
 * Author: james
 *
 * Created on 2022.9.27, PM 4:16
 */

#ifndef ERROR_H
#define ERROR_H

#ifdef __cplusplus
extern "C" {
#endif

    //
#define __pk_panic(error, ...) \
    __pk_panic_func(error, __func__, __LINE__, __VA_ARGS__)

    // Set "ret" and branch-to-err-label tests. 
#define PK_ERR(a)             \
    do {                      \
        if ((ret = (a)) != 0) \
            goto err;         \
    } while (0)

    // Return tests
#define PK_RET(a)               \
    do {                        \
        int __ret;              \
        if ((__ret = (a)) != 0) \
            return (__ret);     \
    } while (0)


#define PK_RET_MSG(v, ...)                     \
    do {                                       \
        int __ret = (v);                       \
        /*_LOG_WARN(__VA_ARGS__);*/            \
        return (__ret);                        \
    } while (0)

    //
#define PK_RET_TEST(a, v) \
    do {                  \
        if (a)            \
            return (v);   \
    } while (0)

#define PK_RET_ERROR_OK(a, e)                           \
    do {                                                \
        int __ret = (a);                                \
        PK_RET_TEST(__ret != 0 && __ret != (e), __ret); \
    } while (0)

    //
#define PK_RET_NOTFOUND_OK(a) PK_RET_ERROR_OK(a, PK_NOTFOUND)


#ifdef __cplusplus
}
#endif

#endif /* ERROR_H */


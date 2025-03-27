
/* 
 * File:   linux_os.h
 * Author: James Xu
 *
 * Created on 2016.12.1, PM 6:31
 */

#ifndef LINUX_OS_H
#define LINUX_OS_H

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

int find_user_group(const char *user, const char *group, uid_t *uid, gid_t *gid);
int network_info(char *netw_info);

#ifdef __cplusplus
}
#endif

#endif /* LINUX_OS_H */


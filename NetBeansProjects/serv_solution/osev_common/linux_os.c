
#include <stdlib.h>
#include <string.h>

#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <netinet/in.h>

#include "third_party.h"

#include <grp.h>
#include <pwd.h>
#include "utility/last_stri.h"
#include "osev_macro.h"
#include "stri_utili.h"

int find_user_group(const char *user, const char *group, uid_t *uid, gid_t *gid) {
    struct passwd *my_pwd = getpwnam(user);
    if (NULL == my_pwd) {
        _LOG_ERROR("getpwnam(\"%s\") failed", user);
        return -1;
    }
    struct group *my_grp = getgrnam(group);
    if (NULL == my_grp) {
        _LOG_ERROR("can't find group name %s", group);
        return -1;
    }
    if (0 == my_grp->gr_gid) {
        _LOG_WARN("I will not set gid to 0");
        return 0;
    }
    //
    *uid = my_pwd->pw_uid;
    *gid = my_grp->gr_gid;
    return 0;
}

//

int network_info(char *netw_info) {
    struct ifreq ifr;
    struct ifconf ifc;
    char buff[2048];
    //
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (sock == -1) {
        _LOG_WARN("socket error");
        return -1;
    }
    //
    ifc.ifc_len = sizeof (buff);
    ifc.ifc_buf = buff;
    if (ioctl(sock, SIOCGIFCONF, &ifc) == -1) {
        _LOG_WARN("ioctl error");
        return -1;
    }
    //
    struct ifreq* it = ifc.ifc_req;
    const struct ifreq * const end = it + (ifc.ifc_len / sizeof (struct ifreq));
    char szMac[64];
    for (; it != end; ++it) {
        strcpy(ifr.ifr_name, it->ifr_name);
        if (ioctl(sock, SIOCGIFFLAGS, &ifr) == 0) {
            if (!(ifr.ifr_flags & IFF_LOOPBACK)) { // don't count loopback
                if (ioctl(sock, SIOCGIFHWADDR, &ifr) == 0) {
                    unsigned char * ptr;
                    ptr = (unsigned char *) &ifr.ifr_ifru.ifru_hwaddr.sa_data[0x00];
                    snprintf(szMac, 64, "%02X%02X%02X%02X%02X%02X", *ptr, *(ptr + 1), *(ptr + 2), *(ptr + 3), *(ptr + 4), *(ptr + 5));
                    netw_info = lscpy(netw_info, ifr.ifr_name);
                    netw_info = lscpy(netw_info, szMac);
                }
            }
        } else {
            _LOG_WARN("get mac info error");
            return -1;
        }
    }
    //
    return 0x00;
}
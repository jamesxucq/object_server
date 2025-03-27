
#include <errno.h>
#include "pack_api.h"

#include "os_errno.h"


// __wt_errno -- Return errno, or WT_ERROR if errno not set.

int __pk_errno(void) {
    // Called when we know an error occurred, and we want the system error code, but there's some
    // chance it's not set.
    return (errno == 0 ? PK_ERROR : errno);
}
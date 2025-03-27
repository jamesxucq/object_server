
#include <stdbool.h>

// #define __USE_MISC
#include <ctype.h>

#include "misc.h"

// __pk_isalnum --
// Wrap the ctype function without sign extension.

static inline bool __pk_isalnum(u_char c) {
    return (isalnum(c) != 0);
}

// __pk_isalpha --
// Wrap the ctype function without sign extension.

static inline bool __pk_isalpha(u_char c) {
    return (isalpha(c) != 0);
}

// __pk_isascii --
// Wrap the ctype function without sign extension.

static inline bool __pk_isascii(u_char c) {
    return (isascii(c) != 0);
}

// __pk_isdigit --
// Wrap the ctype function without sign extension.

static inline bool __pk_isdigit(u_char c) {
    return (isdigit(c) != 0);
}

// __pk_isprint --
// Wrap the ctype function without sign extension.

static inline bool __pk_isprint(u_char c) {
    return (isprint(c) != 0);
}

// __pk_isspace --
// Wrap the ctype function without sign extension.

static inline bool __pk_isspace(u_char c) {
    return (isspace(c) != 0);
}

// __pk_tolower --
// Wrap the ctype function without sign extension.

static inline u_char __pk_tolower(u_char c) {
    return ((u_char) tolower(c));
}


#include <stdlib.h>
#include <errno.h>
#include <stddef.h>

#include "pack_api.h"
#include "error.h"
#include "config.h"

// __pk_config_initn --
// Initialize a config handle, used to iterate through a config string of specified length.

void __pk_config_initn(PK_CONFIG *conf, const char *str, size_t len) {
    conf->orig = conf->cur = str;
    conf->end = str + len;
    conf->depth = 0;
    conf->top = -1;
    conf->go = NULL;
}

//

// __config_err --
// Error message and return for config string parse failures.

static int
__config_err(PK_CONFIG *conf, const char *msg, int err) {
    PK_RET_MSG(err, "Error parsing '%.*s' at offset %" PK_PTRDIFFT_FMT ": %s",
            (int) (conf->end - conf->orig), conf->orig, conf->cur - conf->orig, msg);
}


//
#define PUSH(i, t)                                                                           \
    do {                                                                                     \
        if (conf->top == -1)                                                                 \
            conf->top = conf->depth;                                                         \
        if (conf->depth == conf->top) {                                                      \
            if (out->len > 0)                                                                \
                return (__config_err(conf, "New value starts without a separator", EINVAL)); \
            out->type = (t);                                                                 \
            out->str = (conf->cur + (i));                                                    \
        }                                                                                    \
    } while (0)

#define CAP(i)                                                     \
    do {                                                           \
        if (conf->depth == conf->top)                              \
            out->len = (size_t)((conf->cur + (i) + 1) - out->str); \
    } while (0)

typedef enum {
    A_LOOP,
    A_BAD,
    A_DOWN,
    A_UP,
    A_VALUE,
    A_NEXT,
    A_QDOWN,
    A_QUP,
    A_ESC,
    A_UNESC,
    A_BARE,
    A_NUMBARE,
    A_UNBARE,
    A_UTF8_2,
    A_UTF8_3,
    A_UTF8_4,
    A_UTF_CONTINUE
} CONFIG_ACTION;

//
/*
 *	static void *gostring[] =
 *	{
 *		[0 ... 31] = &&l_bad, [127] = &&l_bad,
 *		[32 ... 126] = &&l_loop,
 *		['\\'] = &&l_esc, ['"'] = &&l_qdown,
 *		[128 ... 191] = &&l_bad,
 *		[192 ... 223] = &&l_utf8_2,
 *		[224 ... 239] = &&l_utf8_3,
 *		[240 ... 247] = &&l_utf8_4,
 *		[248 ... 255] = &&l_bad
 *	};
 */
static const int8_t gostring[256] = {A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_LOOP, A_LOOP, A_QDOWN, A_LOOP,
    A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP,
    A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP,
    A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP,
    A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP,
    A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_ESC, A_LOOP, A_LOOP, A_LOOP,
    A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP,
    A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP,
    A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_UTF8_2, A_UTF8_2, A_UTF8_2, A_UTF8_2, A_UTF8_2, A_UTF8_2, A_UTF8_2,
    A_UTF8_2, A_UTF8_2, A_UTF8_2, A_UTF8_2, A_UTF8_2, A_UTF8_2, A_UTF8_2, A_UTF8_2, A_UTF8_2,
    A_UTF8_2, A_UTF8_2, A_UTF8_2, A_UTF8_2, A_UTF8_2, A_UTF8_2, A_UTF8_2, A_UTF8_2, A_UTF8_2,
    A_UTF8_2, A_UTF8_2, A_UTF8_2, A_UTF8_2, A_UTF8_2, A_UTF8_2, A_UTF8_2, A_UTF8_3, A_UTF8_3,
    A_UTF8_3, A_UTF8_3, A_UTF8_3, A_UTF8_3, A_UTF8_3, A_UTF8_3, A_UTF8_3, A_UTF8_3, A_UTF8_3,
    A_UTF8_3, A_UTF8_3, A_UTF8_3, A_UTF8_3, A_UTF8_3, A_UTF8_4, A_UTF8_4, A_UTF8_4, A_UTF8_4,
    A_UTF8_4, A_UTF8_4, A_UTF8_4, A_UTF8_4, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD};

/*
 * static void *gostruct[] = {
 *		[0 ... 255] = &&l_bad,
 *		['\t'] = &&l_loop, [' '] = &&l_loop,
 *		['\r'] = &&l_loop, ['\n'] = &&l_loop,
 *		['"'] = &&l_qup,
 *		[':'] = &&l_value, ['='] = &&l_value,
 *		[','] = &&l_next,
 *		// tracking [] and {} individually would allow fuller
 *		// validation but is really messy
 *		['('] = &&l_up, [')'] = &&l_down,
 *		['['] = &&l_up, [']'] = &&l_down,
 *		['{'] = &&l_up, ['}'] = &&l_down,
 *		// bare identifiers
 *		['-'] = &&l_numbare,
 *		['0' ... '9'] = &&l_numbare,
 *		['_'] = &&l_bare,
 *		['A' ... 'Z'] = &&l_bare, ['a' ... 'z'] = &&l_bare,
 *		['/'] = &&l_bare,
 *	};
 */
static const int8_t gostruct[256] = {A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_LOOP, A_LOOP, A_BAD, A_BAD, A_LOOP, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_LOOP, A_BAD, A_QUP, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_UP, A_DOWN, A_BAD, A_BAD, A_NEXT, A_NUMBARE, A_BARE, A_BARE,
    A_NUMBARE, A_NUMBARE, A_NUMBARE, A_NUMBARE, A_NUMBARE, A_NUMBARE, A_NUMBARE, A_NUMBARE, A_NUMBARE,
    A_NUMBARE, A_VALUE, A_BAD, A_BAD, A_VALUE, A_BAD, A_BAD, A_BAD, A_BARE, A_BARE, A_BARE, A_BARE,
    A_BARE, A_BARE, A_BARE, A_BARE, A_BARE, A_BARE, A_BARE, A_BARE, A_BARE, A_BARE, A_BARE, A_BARE,
    A_BARE, A_BARE, A_BARE, A_BARE, A_BARE, A_BARE, A_BARE, A_BARE, A_BARE, A_BARE, A_UP, A_BAD,
    A_DOWN, A_BAD, A_BARE, A_BAD, A_BARE, A_BARE, A_BARE, A_BARE, A_BARE, A_BARE, A_BARE, A_BARE,
    A_BARE, A_BARE, A_BARE, A_BARE, A_BARE, A_BARE, A_BARE, A_BARE, A_BARE, A_BARE, A_BARE, A_BARE,
    A_BARE, A_BARE, A_BARE, A_BARE, A_BARE, A_BARE, A_UP, A_BAD, A_DOWN, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD};

/*
 *	static void *gobare[] =
 *	{
 *		[0 ... 31] = &&l_bad,
 *		// could be more pedantic/validation-checking
 *		[32 ... 126] = &&l_loop,
 *		['\t'] = &&l_unbare, [' '] = &&l_unbare,
 *		['\r'] = &&l_unbare, ['\n'] = &&l_unbare,
 *		[':'] = &&l_unbare, ['='] = &&l_unbare,
 *		[','] = &&l_unbare,
 *		[')'] = &&l_unbare, [']'] = &&l_unbare, ['}'] = &&l_unbare,
 *		[127 ... 255] = &&l_bad
 *	};
 */
static const int8_t gobare[256] = {A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_UNBARE, A_UNBARE, A_BAD, A_BAD, A_UNBARE, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_UNBARE, A_LOOP,
    A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_UNBARE, A_LOOP, A_LOOP, A_UNBARE,
    A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP,
    A_LOOP, A_UNBARE, A_LOOP, A_LOOP, A_UNBARE, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP,
    A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP,
    A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP,
    A_LOOP, A_UNBARE, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP,
    A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP,
    A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_LOOP, A_UNBARE, A_LOOP, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD};

/*
 *	static void *goutf8_continue[] =
 *	{
 *		[0 ... 127] = &&l_bad,
 *		[128 ... 191] = &&l_utf_continue,
 *		[192 ... 255] = &&l_bad
 *	};
 */
static const int8_t goutf8_continue[256] = {A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_UTF_CONTINUE, A_UTF_CONTINUE,
    A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE,
    A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE,
    A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE,
    A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE,
    A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE,
    A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE,
    A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE,
    A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE,
    A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE,
    A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE, A_UTF_CONTINUE,
    A_UTF_CONTINUE, A_UTF_CONTINUE, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD};

/*
 *	static void *goesc[] =
 *	{
 *		[0 ... 255] = &&l_bad,
 *		['"'] = &&l_unesc, ['\\'] = &&l_unesc,
 *		['/'] = &&l_unesc, ['b'] = &&l_unesc,
 *		['f'] = &&l_unesc, ['n'] = &&l_unesc,
 *		['r'] = &&l_unesc, ['t'] = &&l_unesc, ['u'] = &&l_unesc
 *	};
 */
static const int8_t goesc[256] = {A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_UNESC, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_UNESC, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_UNESC, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_UNESC, A_BAD, A_BAD, A_BAD, A_UNESC, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_UNESC, A_BAD, A_BAD, A_BAD, A_UNESC, A_BAD, A_UNESC,
    A_UNESC, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD,
    A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD, A_BAD};

// __config_next --
// Get the next config item in the string without processing the value.

static int __config_next(PK_CONFIG *conf, PK_CONFIG_ITEM *key, PK_CONFIG_ITEM *value) {
    PK_CONFIG_ITEM *out;
    int utf8_remain;
    static const PK_CONFIG_ITEM true_value = {"", 0, 1, PK_CONFIG_ITEM_BOOL};

    // Keys with no value default to true.
    *value = true_value;

    out = key;
    utf8_remain = 0;
    key->len = 0;

    if (conf->go == NULL)
        conf->go = gostruct;

    while (conf->cur < conf->end) {
        switch (conf->go[*(const uint8_t *) conf->cur]) {
            case A_LOOP:
                break;

            case A_BAD:
                return (__config_err(conf, "Unexpected character", EINVAL));

            case A_DOWN:
                if (conf->top == -1)
                    return (__config_err(conf, "Unbalanced brackets", EINVAL));
                --conf->depth;
                CAP(0);
                break;

            case A_UP:
                if (conf->top == -1)
                    conf->top = 1;
                PUSH(0, PK_CONFIG_ITEM_STRUCT);
                ++conf->depth;
                break;

            case A_VALUE:
                if (conf->depth == conf->top) {
                    // Special case: ':' is permitted in unquoted values.
                    if (out == value && *conf->cur != ':')
                        return (__config_err(conf, "Value already complete", EINVAL));
                    out = value;
                }
                break;

            case A_NEXT:
                // If we're at the top level and we have a complete key (and optional value), we're done.
                if (conf->depth == conf->top && key->len > 0) {
                    ++conf->cur;
                    return (0);
                } else
                    break;

            case A_QDOWN:
                CAP(-1);
                conf->go = gostruct;
                break;

            case A_QUP:
                PUSH(1, PK_CONFIG_ITEM_STRING);
                conf->go = gostring;
                break;

            case A_ESC:
                conf->go = goesc;
                break;

            case A_UNESC:
                conf->go = gostring;
                break;

            case A_BARE:
                PUSH(0, PK_CONFIG_ITEM_ID);
                conf->go = gobare;
                break;

            case A_NUMBARE:
                PUSH(0, PK_CONFIG_ITEM_NUM);
                conf->go = gobare;
                break;

            case A_UNBARE:
                CAP(-1);
                conf->go = gostruct;
                continue;

            case A_UTF8_2:
                conf->go = goutf8_continue;
                utf8_remain = 1;
                break;

            case A_UTF8_3:
                conf->go = goutf8_continue;
                utf8_remain = 2;
                break;

            case A_UTF8_4:
                conf->go = goutf8_continue;
                utf8_remain = 3;
                break;

            case A_UTF_CONTINUE:
                if (!--utf8_remain)
                    conf->go = gostring;
                break;
        }

        conf->cur++;
    }

    // Might have a trailing key/value without a closing brace
    if (conf->go == gobare) {
        CAP(-1);
        conf->go = gostruct;
    }

    // Did we find something? 
    if (conf->depth <= conf->top && key->len > 0)
        return (0);

    // We're either at the end of the string or we failed to parse.
    if (conf->depth == 0)
        return (PK_NOTFOUND);

    return (__config_err(conf, "Unbalanced brackets", EINVAL));
}

// Arithmetic shift of a negative number is undefined by ISO/IEC 9899, and the WiredTiger API
// supports negative numbers. Check it's not a negative number, and then cast the shift out of
// paranoia.

#define PK_SHIFT_INT64(v, s)                     \
    do {                                         \
        if ((v) < 0)                             \
            goto nonum;                          \
        (v) = (int64_t)(((uint64_t)(v)) << (s)); \
        if ((v) < 0)                             \
            goto nonum;                          \
    } while (0)

// __config_process_value --
// Deal with special config values like true / false.

static void __config_process_value(PK_CONFIG_ITEM *value) {
    char *endptr;

    // Empty values are okay: we can't do anything interesting with them.
    if (value->len == 0)
        return;

    if (value->type == PK_CONFIG_ITEM_ID) {
        if (PK_STRING_MATCH("false", value->str, value->len)) {
            value->type = PK_CONFIG_ITEM_BOOL;
            value->val = 0;
        } else if (PK_STRING_MATCH("true", value->str, value->len)) {
            value->type = PK_CONFIG_ITEM_BOOL;
            value->val = 1;
        }
    } else if (value->type == PK_CONFIG_ITEM_NUM) {
        errno = 0;
        value->val = strtoll(value->str, &endptr, 10);

        // If we parsed the string but the number is out of range, treat the value as an identifier.
        // If an integer is expected, that will be caught by __pk_config_check.
        if (value->type == PK_CONFIG_ITEM_NUM && errno == ERANGE)
            goto nonum;

        // Check any leftover characters.
        while (endptr < value->str + value->len)
            switch (*endptr++) {
                case 'b':
                case 'B':
                    // Byte: no change.
                    break;
                case 'k':
                case 'K':
                    PK_SHIFT_INT64(value->val, 10);
                    break;
                case 'm':
                case 'M':
                    PK_SHIFT_INT64(value->val, 20);
                    break;
                case 'g':
                case 'G':
                    PK_SHIFT_INT64(value->val, 30);
                    break;
                case 't':
                case 'T':
                    PK_SHIFT_INT64(value->val, 40);
                    break;
                case 'p':
                case 'P':
                    PK_SHIFT_INT64(value->val, 50);
                    break;
                default:
                    goto nonum;
            }
    }

    if (0) {
nonum:
        // We didn't get a well-formed number. That might be okay, the required type will be checked
        // by __pk_config_check.
        value->type = PK_CONFIG_ITEM_ID;
    }
}

// __pk_config_next --
// Get the next config item in the string and process the value.

int __pk_config_next(PK_CONFIG *conf, PK_CONFIG_ITEM *key, PK_CONFIG_ITEM *value) {
    PK_RET(__config_next(conf, key, value));
    __config_process_value(value);
    return (0);
}
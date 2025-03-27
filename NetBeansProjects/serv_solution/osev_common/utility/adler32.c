#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "adler32.h"

//
#define BASE 65521      /* largest prime smaller than 65536 */
#define NMAX 5552
/* NMAX is the largest n such that 255n(n+1)/2 + (n+1)(BASE-1) <= 2^32-1 */

#define DO1(buf,i)  {adler += (buf)[i]; sum2 += adler;}
#define DO2(buf,i)  DO1(buf,i); DO1(buf,i+1);
#define DO4(buf,i)  DO2(buf,i); DO2(buf,i+2);
#define DO8(buf,i)  DO4(buf,i); DO4(buf,i+4);
#define DO16(buf)   DO8(buf,0); DO8(buf,8);

/* use NO_DIVIDE if your processor does not do division in hardware --
   try it both ways to see which is faster */
#ifdef NO_DIVIDE
/* note that this assumes BASE is 65521, where 65536 % 65521 == 15
   (thank you to John Reiser for pointing this out) */
#define CHOP(a) \
    do { \
        unsigned long tmp = a >> 16; \
        a &= 0xffffUL; \
        a += (tmp << 4) - tmp; \
    } while (0)
#define MOD28(a) \
    do { \
        CHOP(a); \
        if (a >= BASE) a -= BASE; \
    } while (0)
#define MOD(a) \
    do { \
        CHOP(a); \
        MOD28(a); \
    } while (0)
#define MOD63(a) \
    do { /* this assumes a is not negative */ \
        z_off64_t tmp = a >> 32; \
        a &= 0xffffffffL; \
        a += (tmp << 8) - (tmp << 5) + tmp; \
        tmp = a >> 16; \
        a &= 0xffffL; \
        a += (tmp << 4) - tmp; \
        tmp = a >> 16; \
        a &= 0xffffL; \
        a += (tmp << 4) - tmp; \
        if (a >= BASE) a -= BASE; \
    } while (0)
#else
#define MOD(a) a %= BASE
#define MOD28(a) a %= BASE
#define MOD63(a) a %= BASE
#endif

/* ========================================================================= */
unsigned int adler32_chksum(unsigned int adler, const unsigned char *buff, unsigned int len) {
    unsigned int sum2;
    unsigned int n;

    /* split Adler-32 into component sums */
    sum2 = (adler >> 16) & 0xffff;
    adler &= 0xffff;

    /* in case user likes doing a byte at a time, keep it fast */
    if (len == 1) {
        adler += buff[0];
        if (adler >= BASE)
            adler -= BASE;
        sum2 += adler;
        if (sum2 >= BASE)
            sum2 -= BASE;
        return adler | (sum2 << 16);
    }

    /* initial Adler-32 value (deferred check for len == 1 speed) */
    if (buff == NULL)
        return 0x01;

    /* in case short lengths are provided, keep it somewhat fast */
    if (len < 16) {
        while (len--) {
            adler += *buff++;
            sum2 += adler;
        }
        if (adler >= BASE)
            adler -= BASE;
        MOD28(sum2); /* only added so many BASE's */
        return adler | (sum2 << 16);
    }

    /* do length NMAX blocks -- requires just one modulo operation */
    while (len >= NMAX) {
        len -= NMAX;
        n = NMAX / 16; /* NMAX is divisible by 16 */
        do {
            DO16(buff); /* 16 sums unrolled */
            buff += 16;
        } while (--n);
        MOD(adler);
        MOD(sum2);
    }

    /* do remaining bytes (less than NMAX, still just one modulo) */
    if (len) { /* avoid modulos if none remaining */
        while (len >= 16) {
            len -= 16;
            DO16(buff);
            buff += 16;
        }
        while (len--) {
            adler += *buff++;
            sum2 += adler;
        }
        MOD(adler);
        MOD(sum2);
    }
    // _LOG_DEBUG(_T("recount adler:%u sum2:%u"), adler, sum2);
    /* return recombined sums */
    return adler | (sum2 << 16);
}

/*
 * adler32_chksum(X0, ..., Xn), X0, Xn+1 ----> adler32_chksum(X1, ..., Xn+1)
 * where chksum is adler32_chksum(X0, ..., Xn), c1 is X0, c2 is Xn+1
 */
unsigned int adler32_rolling(unsigned int adler, unsigned int len, unsigned char c1, unsigned char c2) {
    unsigned int sum2;
    //
    /* split Adler-32 into component sums */
    sum2 = (adler >> 16) & 0xffff;
    adler &= 0xffff;
    //
    // _LOG_DEBUG(_T("c1:%u c2:%u"), c1, c2);
    adler -= ((int) (c1 - c2) - BASE);
    sum2 -= ((int) (len * c1 + 1 - adler) % BASE - BASE);
    MOD(adler);
    MOD(sum2);
    //
    // _LOG_DEBUG(_T("rolling adler:%u sum2:%u"), adler, sum2);
    return adler | (sum2 << 16);
}

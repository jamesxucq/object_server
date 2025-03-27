#ifndef _ADLER32_H
#define _ADLER32_H

#ifdef	__cplusplus
extern "C" {
#endif
    
unsigned int adler32_chksum(unsigned int adler, const unsigned char *buff, unsigned int len);
unsigned int adler32_rolling(unsigned int adler, unsigned int len, unsigned char c1, unsigned char c2);

#ifdef	__cplusplus
}
#endif

#endif

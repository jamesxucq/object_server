/* 
 * File:   binary_logger.h
 * Author: David
 *
 * Created on 2011
 */

#ifndef BINARYLOGGER_H
#define	BINARYLOGGER_H

#ifdef	__cplusplus
extern "C" {
#endif

void log_binary_code(unsigned char *binary_code, int length);
void log_binary_file(unsigned char *binary_code, int length, char *logfile);

#ifdef	__cplusplus
}
#endif

#endif	/* BINARYLOGGER_H */


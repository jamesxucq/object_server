#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binary_logger.h"

void log_binary_code(unsigned char *binary_code, int length) {
    FILE *code_stre = NULL;
    if (!binary_code || length < 0) return;
    code_stre = fopen64("./binary_code.bin", "a");
    if (!code_stre) return;
    fwrite(binary_code, length, 0x01, code_stre);
    fclose(code_stre);
}

//
void log_binary_file(unsigned char *binary_code, int length, char *logfile) {
    FILE *code_stre = NULL;
    if (!binary_code || length < 0) return;
    code_stre = fopen64(logfile, "a");
    if (!code_stre) return;
    fwrite(binary_code, length, 0x01, code_stre);
    fclose(code_stre);
}
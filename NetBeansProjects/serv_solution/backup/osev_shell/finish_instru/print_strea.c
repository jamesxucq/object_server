
#include "commo_header.h"

#include "print_strea.h"


#define BUFF_SIZE                        0x2000

void print_stream(FILE *strem, uint64 slen) {
    // printf("[FUNC]:print_stream, slen:%llu\n", slen);
    char buffer[BUFF_SIZE];
    rewind(strem);
    uint64 step_leng = 0x00;
    uint32 realen;
    for (; slen > step_leng; step_leng += realen) {
        realen = fread(buffer, 0x01, BUFF_SIZE - 0x01, strem);
        if (0x00 >= realen) break;
        if (slen < (realen + step_leng)) {
            buffer[slen - step_leng] = '\0';
        } else buffer[realen] = '\0';
        fprintf(stdout, "%s", buffer);
    }
}


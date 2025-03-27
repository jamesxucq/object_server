
#include "hex.h"

// __pk_hex2byte --
// Convert a pair of hex characters into a byte.

int __pk_hex2byte(const u_char *from, u_char *to) {
    uint8_t byte;

    switch (from[0]) {
        case '0':
            byte = 0;
            break;
        case '1':
            byte = 1 << 4;
            break;
        case '2':
            byte = 2 << 4;
            break;
        case '3':
            byte = 3 << 4;
            break;
        case '4':
            byte = 4 << 4;
            break;
        case '5':
            byte = 5 << 4;
            break;
        case '6':
            byte = 6 << 4;
            break;
        case '7':
            byte = 7 << 4;
            break;
        case '8':
            byte = 8 << 4;
            break;
        case '9':
            byte = 9 << 4;
            break;
        case 'A':
            byte = 10 << 4;
            break;
        case 'B':
            byte = 11 << 4;
            break;
        case 'C':
            byte = 12 << 4;
            break;
        case 'D':
            byte = 13 << 4;
            break;
        case 'E':
            byte = 14 << 4;
            break;
        case 'F':
            byte = 15 << 4;
            break;
        case 'a':
            byte = 10 << 4;
            break;
        case 'b':
            byte = 11 << 4;
            break;
        case 'c':
            byte = 12 << 4;
            break;
        case 'd':
            byte = 13 << 4;
            break;
        case 'e':
            byte = 14 << 4;
            break;
        case 'f':
            byte = 15 << 4;
            break;
        default:
            return (1);
    }

    switch (from[1]) {
        case '0':
            break;
        case '1':
            byte |= 1;
            break;
        case '2':
            byte |= 2;
            break;
        case '3':
            byte |= 3;
            break;
        case '4':
            byte |= 4;
            break;
        case '5':
            byte |= 5;
            break;
        case '6':
            byte |= 6;
            break;
        case '7':
            byte |= 7;
            break;
        case '8':
            byte |= 8;
            break;
        case '9':
            byte |= 9;
            break;
        case 'A':
            byte |= 10;
            break;
        case 'B':
            byte |= 11;
            break;
        case 'C':
            byte |= 12;
            break;
        case 'D':
            byte |= 13;
            break;
        case 'E':
            byte |= 14;
            break;
        case 'F':
            byte |= 15;
            break;
        case 'a':
            byte |= 10;
            break;
        case 'b':
            byte |= 11;
            break;
        case 'c':
            byte |= 12;
            break;
        case 'd':
            byte |= 13;
            break;
        case 'e':
            byte |= 14;
            break;
        case 'f':
            byte |= 15;
            break;
        default:
            return (1);
    }
    *to = byte;
    return (0);
}
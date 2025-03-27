/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/testFiles/simpletest.c to edit this template
 */

/*
 * File:   apisimpletest.c
 * Author: james
 *
 * Created on 2022.10.4, PM 2:20
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pack_api.h"

/*
int unpack() {
    //
    int i, j, k;
    //
    size_t size;
    char buf[50];
    memset(buf, 0, sizeof (buf));

    paki_struct_size(&size, "iii", 4200, 1000, -9);
    if (size > sizeof (buf)) {
        // Allocate a bigger buffer.
    }
    paki_struct_pack(buf, size, "iii", 4200, 1000, -9);
    paki_struct_unpack(buf, size, "iii", &i, &j, &k);

    printf("sizeof(int):%ld\n", sizeof (int));
    printf("size:%ld\n", size);
    printf("i:%d j:%d k:%d\n", i, j, k);

    printf("-------------------------------\n");
    size_t lenp;
    char *pppp = buf;
    paki_struct_unpack(pppp, size, "i", &i);
    paki_struct_size(&lenp, "i", i);
    printf("lenp:%lu\n", lenp);
    pppp += lenp;
    char *xxx = "i";
    paki_struct_unpack(pppp, size, xxx, &j);
    paki_struct_unpack(pppp, size, "i", &k);
    printf("i:%d\n", i);
    printf("j:%d\n", j);
    printf("k:%d\n", k);
    paki_struct_size(&lenp, "i", 2);
    printf("lenp:%lu\n", lenp);
    paki_struct_size(&lenp, "i", 20000);
    printf("lenp:%lu\n", lenp);
    printf("-------------------------------\n");
    //
    printf("buf[0x00]:%d\n", buf[0x00]);
    printf("buf[0x01]:%d\n", buf[0x01]);
    printf("buf[0x02]:%d\n", buf[0x02]);
    printf("buf[0x03]:%d\n", buf[0x03]);
    printf("buf[0x04]:%d\n", buf[0x04]);
    printf("buf[0x05]:%d\n", buf[0x05]);

    //
    return (EXIT_SUCCESS);
}
 */

int stream() {
    printf("stream.\n");
    //
    size_t size = 128;
    char buffe[size];
    memset(buffe, 0, sizeof (buffe));
    PK_PACK_STREAM *ps;
    int retval = paki_pack_start("iii", (void *) buffe, size, &ps);
    if (retval) printf("paki_pack_start error.\n");

    paki_pack_int(ps, 3300);
    paki_pack_int(ps, 1000);
    paki_pack_int(ps, -2);

    paki_stream_close(ps, NULL);

    //
    PK_PACK_STREAM *unps;
    retval = paki_stream_open("iii", (void *) buffe, size, &unps);
    if (retval) printf("paki_stream_open error.\n");

    int64_t valu;
    retval = paki_unpack_int(unps, &valu);
    printf("retval:%d valu:%ld\n", retval, valu);
    retval = paki_unpack_int(unps, &valu);
    printf("retval:%d valu:%ld\n", retval, valu);
    retval = paki_unpack_int(unps, &valu);
    printf("retval:%d valu:%ld\n", retval, valu);
    retval = paki_unpack_int(unps, &valu);
    printf("retval:%d valu:%ld\n", retval, valu);

    paki_stream_close(unps, NULL);

    //
    printf("stream end./n");
    return 0x00;
}

/*
 * Simple C Test Suite
 */

void test1() {
    printf("apisimpletest test 1\n");
}

void test2() {
    printf("apisimpletest test 2\n");
    printf("%%TEST_FAILED%% time=0 testname=test2 (apisimpletest) message=error message sample\n");
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% apisimpletest\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%% test1 (apisimpletest)\n");
    test1();
    printf("%%TEST_FINISHED%% time=0 test1 (apisimpletest) \n");

    printf("%%TEST_STARTED%% test2 (apisimpletest)\n");
    test2();
    printf("%%TEST_FINISHED%% time=0 test2 (apisimpletest) \n");

    printf("%%SUITE_FINISHED%% time=0\n");

    // unpack();
    stream();

    return (EXIT_SUCCESS);
}


//



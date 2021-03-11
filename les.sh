#!/bin/bash
mips-linux-gnu-gcc -mfp32 -o testing_MIPS/test_program.o -c testing_MIPS/t.s
mips-linux-gnu-gcc -mfp32 -static -o testing_MIPS/test_program testing_MIPS/test_program.o testing_MIPS/test.c
qemu-mips testing_MIPS/test_program
echo $?
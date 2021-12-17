#!/bin/bash
arm-none-eabi-gcc -Wall -O0 -mcpu=arm7tdmi-s -marm -c Startup.s -o Startup.o
arm-none-eabi-gcc -Wall -O0 -mcpu=arm7tdmi-s -marm -c lpc21xx.c -o lpc21xx.o
arm-none-eabi-gcc -Wall -O0 -mcpu=arm7tdmi-s -marm -c assembly.s -o assembly.o
arm-none-eabi-gcc -Wall -O0 -mcpu=arm7tdmi-s -marm -c main.c -o main.o
arm-none-eabi-ld *.o -TLPC2129.ld -o main.elf
arm-none-eabi-objcopy -O ihex main.elf main.hex

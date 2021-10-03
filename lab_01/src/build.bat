@echo off
gcc -std=c99 -Wall -Werror -c main.c
gcc -std=c99 -Wall -Werror -c correct_check.c
gcc -std=c99 -Wall -Werror -c division.c
gcc -std=c99 -Wall -Werror -c input.c
gcc -std=c99 -Wall -Werror -c output.c
gcc -o main.exe main.o correct_check.o division.o input.o output.o

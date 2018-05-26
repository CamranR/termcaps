/*
** EPITECH PROJECT, 2017
** my.h
** File description:
** my.h
*/

#ifndef MY_H_
#define MY_H_

#include "my_printf.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>
#include <term.h>
#include <curses.h>
#include <sys/ioctl.h>
#include <termios.h>

#define RED		"\033[01;31m"
#define YELLOW		"\033[01;32m"
#define GREEN		"\033[01;33m"
#define WHITE		"\033[0m"
#define UNDERLINE	"\033[01;34m"
#define CYAN		"\x1b[36m"

typedef struct termline_t {
	char *str;
	char *del;
	char *clear;
	int pos;
	int len;
	int check;
} termline_s;

char *read_file(char *path);

#endif	/* MY_Y_ */

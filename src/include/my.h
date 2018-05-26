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
#define CYAN		"\033[01;34m"
#define UNDERLINE	"\033[4m"

typedef struct termline_t {
	char *str;
	char *del;
	char *clear;
	int pos;
	int len;
	int check;
} termline_s;

	void	my_putchar(char);
	int	my_isneg(int);
	int	my_put_nbr(int);
	int	my_put_unsigned_nbr(unsigned int);
	int	my_swap(int * , int *);
	int	my_putstr(char const *);
	int	my_strlen(char const *);
	int	my_getnbr(char const *);
	void	my_sort_int_array(int *, int );
	int	my_compute_power_rec(int, int);
	int	my_compute_square_root(int);
	int	my_is_prime(int);
	int	my_find_prime_sup(int);
	char	*my_strcpy(char *, char const *);
	char	*my_strncpy(char *, char const *, int);
	char	*my_revstr(char *);
	char	*my_strstr(char const *, char const *);
	int	my_strcmp(char const *, char const *);
	int	my_strncmp(char const *, char const *, int);
	char	*my_strupcase(char *);
	char	*my_strlowcase(char *);
	int	my_str_isalpha(char const *);
	int	my_put_nbr_base(unsigned int, char const *);
	int	my_put_pointer(unsigned long);
	int	my_str_isnum(char const *);
	int	my_str_islower(char const *);
	int	my_str_isupper(char const *);
	int	my_str_isprintable(char const *);
	int	my_showstr(char const *);
	int	my_showmem(char const *, int);
	char	*my_strcat(char *, char const *);
	char	*my_strdup(char *);
	char	*my_strncat(char *, char const *, int);
	int	my_put_nbr_binary(unsigned int);
	int	my_printf(char*, ...);
	char	**my_str_to_word_array(char const *str, char delim);
	char	*clean_str(char *str);
	char	*read_file(char *path);

#endif	/* MY_Y_ */

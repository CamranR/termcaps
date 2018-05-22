/*
** EPITECH PROJECT, 2017
** print_fct3.c
** File description:
** print_fct3
*/

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../../include/my_printf.h"
#include "../../../include/my.h"

static int get_int_size_space(int original)
{
	int i = original;
	int size;

	i < 0 ? (size = 2) : (size = 0);
	while (i > 9) {
		size++;
		i = i / 10;
	}
	return (size + 1);
}

void print_space_padding(va_list list, ctx_printf_t *ctx)
{
	va_list copy;
	int i;
	char num[10];
	int nb_zero = 0;
	int x = 0;

	va_copy(copy, list);
	i = va_arg(copy, int);
	ctx->i++;
	for (int y = 0; y <= 10; y++)
		num[y] = 0;
	for (; ctx->s[ctx->i] >= '0' && ctx->s[ctx->i] <= '9'; x++) {
		num[x] = ctx->s[ ctx->i];
		ctx->i++;
	}
	num[x + 1] = '\0';
	x = my_getnbr(num);
	nb_zero = x - get_int_size_space(i);
	for (int z = 0; z < nb_zero; z++)
		ctx->counter += my_putstr(" ");
}

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

void print_unsigned_nbr(va_list list, ctx_printf_t *ctx)
{
	unsigned int i = va_arg(list, unsigned int);

	ctx->counter += my_put_unsigned_nbr(i);
}

void print_sign(va_list list, ctx_printf_t *ctx)
{
	int i = va_arg(list, int);

	if (i >= 0)
		ctx->counter += my_putstr("+");
	ctx->counter += my_put_nbr(i);
}

void print_base(va_list list, ctx_printf_t *ctx)
{
	(void) list;
	int i = ctx->i;

	if (ctx->s[i + 1] == 'x')
		ctx->counter += my_putstr("0x");
	if (ctx->s[i + 1] == 'X')
		ctx->counter += my_putstr("0X");
	if (ctx->s[i + 1] == 'o')
		ctx->counter += my_putstr("0");
	ctx->i++;
}

static int get_int_size(int original, ctx_printf_t *ctx)
{
	int i = original;
	int size = 0;

	if (i < 0) {
		ctx->counter += my_putstr("-");
		ctx->mode = 1;
		size += 2;
	}
	while (i > 9) {
		size++;
		i = i / 10;
	}
	return (size + 1);
}

void print_zero_padding(va_list list, ctx_printf_t *ctx)
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
	nb_zero = x - get_int_size(i, ctx);
	for (int z = 0; z < nb_zero; z++)
		ctx->counter += my_putstr("0");
}

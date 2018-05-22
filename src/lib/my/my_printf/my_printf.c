/*
** EPITECH PROJECT, 2017
** my_printf
** File description:
** printf
*/

#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../../include/my_printf.h"
#include "../../../include/my.h"

static function_t fptr_d[]=
{
	{'%', print_mod},
	{'+', print_sign},
	{'#', print_base},
	{'0', print_zero_padding},
	{' ', print_space_padding},
	{'s', print_str},
	{'S', print_octstr},
	{'c', print_char},
	{'i', print_nbr},
	{'d', print_nbr},
	{'u', print_unsigned_nbr},
	{'x', print_hex},
	{'X', print_hex_maj},
	{'o', print_oct},
	{'b', print_bin},
	{'p', print_pointer},
	{'\0', NULL}
};

static function_t fptr_l[]=
{
	{'%', print_mod},
	{'+', print_sign},
	{'#', print_base},
	{'0', print_zero_padding},
	{' ', print_space_padding},
	{'s', print_str},
	{'S', print_octstr},
	{'c', print_char},
	{'i', print_nbr},
	{'d', print_nbr},
	{'u', print_unsigned_nbr},
	{'x', print_hex},
	{'X', print_hex_maj},
	{'o', print_oct},
	{'b', print_bin},
	{'p', print_pointer},
	{'\0', NULL}
};

static function_t fptr_ll[]=
{
	{'%', print_mod},
	{'+', print_sign},
	{'#', print_base},
	{'0', print_zero_padding},
	{' ', print_space_padding},
	{'s', print_str},
	{'S', print_octstr},
	{'c', print_char},
	{'i', print_nbr},
	{'d', print_nbr},
	{'u', print_unsigned_nbr},
	{'x', print_hex},
	{'X', print_hex_maj},
	{'o', print_oct},
	{'b', print_bin},
	{'p', print_pointer},
	{'\0', NULL}
};

static function_t fptr_h[]=
{
	{'%', print_mod},
	{'+', print_sign},
	{'#', print_base},
	{'0', print_zero_padding},
	{' ', print_space_padding},
	{'s', print_str},
	{'S', print_octstr},
	{'c', print_char},
	{'i', print_nbr},
	{'d', print_nbr},
	{'u', print_unsigned_nbr},
	{'x', print_hex},
	{'X', print_hex_maj},
	{'o', print_oct},
	{'b', print_bin},
	{'p', print_pointer},
	{'\0', NULL}
};

static format_t format_selector[]=
{
	{"int", fptr_d},
	{"l\0", fptr_l},
	{"ll\0", fptr_ll},
	{"h\0", fptr_h}
};

void check_type(ctx_printf_t *ctx, va_list list, function_t *function)
{
	for (int j = 0; function[j].flag != '\0'; j++) {
		if (ctx->s[ctx->i] == function[j].flag) {
			function[j].print_fct(list, ctx);
		}
	}
}

void check_format(ctx_printf_t *ctx, va_list list)
{
	check_type(ctx, list, format_selector[0].my_function);
}

static ctx_printf_t *init_printf_ctx(ctx_printf_t *ctx, char *s)
{
	ctx->counter = 0;
	ctx->i = 0;
	ctx->s = s;
	ctx->mode = 0;
	return (ctx);
}

int my_printf(char * s, ...)
{
	va_list list;
	ctx_printf_t ctx;

	va_start(list, s);
	init_printf_ctx(&ctx, s);
	while (ctx.s[ctx.i] != '\0') {
		if (s[ctx.i] == '%') {
			ctx.i++;
			check_format(&ctx, list);
			ctx.i++;
			ctx.s[ctx.i - 1] == '+' ? ctx.i++ : ctx.i;
		} else {
			my_putchar(ctx.s[ctx.i]);
			ctx.i++;
			ctx.counter++;
		}
	}
	va_end(list);
	return (ctx.counter);
}

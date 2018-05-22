/*
** EPITECH PROJECT, 2017
** print_fct.c
** File description:
** print_fct
*/

#include <stdarg.h>
#include <unistd.h>
#include "../../../include/my_printf.h"
#include "../../../include/my.h"

void print_char(va_list list, ctx_printf_t *ctx)
{
	char c = (char)va_arg(list, int);

	my_putchar(c);
	ctx->counter++;
}

void print_str(va_list list, ctx_printf_t *ctx)
{
	char *s = va_arg(list, char *);

	if (!s) {
		my_putstr("(null)");
		ctx->counter += 6;
		return;
	}
	ctx->counter += my_putstr(s);
}

void print_octstr(va_list list, ctx_printf_t *ctx)
{
	char *s = va_arg(list, char *);

	ctx->counter += my_showstr(s);
}

void print_nbr(va_list list, ctx_printf_t *ctx)
{
	long long i = va_arg(list, long long);

	if (ctx->mode == 1 && i < 0)
		i *= -1;
	ctx->counter += my_put_nbr(i);
}

void print_mod(va_list list, ctx_printf_t *ctx)
{
	(void) list;
	my_putchar('%');
	ctx->counter++;
}

/*
** EPITECH PROJECT, 2017
** printf_fct2.c
** File description:
** print_fct2
*/

#include <stdarg.h>
#include <unistd.h>
#include "../../../include/my_printf.h"
#include "../../../include/my.h"

void print_hex(va_list list, ctx_printf_t *ctx)
{
	int i = va_arg(list, int);

	ctx->counter += my_put_nbr_base(i, "0123456789abcdef");
}

void print_hex_maj(va_list list, ctx_printf_t *ctx)
{
	int i = va_arg(list, int);

	ctx->counter += my_put_nbr_base(i, "0123456789ABCDEF");
}

void print_oct(va_list list, ctx_printf_t *ctx)
{
	int i = va_arg(list, int);

	ctx->counter += my_put_nbr_base(i, "01234567");
}

void print_bin(va_list list, ctx_printf_t *ctx)
{
	unsigned int i = va_arg(list, unsigned int);

	ctx->counter += my_put_nbr_binary(i);
}

void print_pointer(va_list list, ctx_printf_t *ctx)
{
	unsigned long i = va_arg(list, unsigned long);

	if (!i) {
		my_putstr("(nil)");
		ctx->counter += 5;
		return;
	}
	ctx->counter += my_putstr("0x");
	ctx->counter += my_put_pointer(i);
}

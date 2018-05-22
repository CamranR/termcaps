/*
** EPITECH PROJECT, 2017
** my_printf.h
** File description:
** my_printf.h
*/

#ifndef MY_PRINTF_H_
#define MY_PRINTF_H_

#include "stdarg.h"

typedef struct ctx_printf_s {
	va_list list;
	long long counter;
	int i;
	char *s;
	int mode;
} ctx_printf_t;

typedef void (*func)(va_list args, ctx_printf_t *ctx);

typedef struct function_s {
	char flag;
	func print_fct;
} function_t;

typedef struct format_s {
	char *format;
	function_t *my_function;
} format_t;

void print_str(va_list, ctx_printf_t *);
void print_octstr(va_list, ctx_printf_t *);
void print_char(va_list, ctx_printf_t *);
void print_nbr(va_list, ctx_printf_t *);
void print_unsigned_nbr(va_list, ctx_printf_t *);
void print_mod(va_list, ctx_printf_t *);
void print_hex(va_list, ctx_printf_t *);
void print_hex_maj(va_list, ctx_printf_t *);
void print_oct(va_list, ctx_printf_t *);
void print_bin(va_list, ctx_printf_t *);
void print_pointer(va_list, ctx_printf_t *);
void print_sign(va_list, ctx_printf_t *);
void print_base(va_list, ctx_printf_t *);
void print_zero_padding(va_list, ctx_printf_t *);
void print_space_padding(va_list, ctx_printf_t *);

#endif	/* MY_PRINTF_H */

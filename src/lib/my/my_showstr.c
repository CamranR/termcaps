/*
** EPITECH PROJECT, 2017
** my_showstr.c
** File description:
** my_showstr
*/

#include "../../include/my.h"

int my_isprintable(char a)
{
	if (a >= 32 && a <= 126)
		return (1);
	else
		return (0);
}

int check_inf_16(char const *str, int i, int counter)
{
	counter = 0;
	if (str[i] <= 7) {
		my_putchar('0');
		counter++;
	}
	return (counter);
}

int my_showstr(char const *str)
{
	int i = 0;
	int counter = 0;

	while (!(str[i] == '\0')) {
		if (my_isprintable(str[i]) == 0) {
			my_putchar(92);
			counter++;
			my_putchar('0');
			counter++;
			counter += check_inf_16(str, i, counter);
			counter += my_put_nbr_base(str[i], "01234567");
			i++;
		} else if (my_isprintable(str[i]) == 1) {
			my_putchar(str[i]);
			counter++;
			i++;
		}
	}
	return (counter);
}

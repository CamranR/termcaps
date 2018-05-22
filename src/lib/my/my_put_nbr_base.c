/*
** EPITECH PROJECT, 2017
** my_put_nbr_base.c
** File description:
** my_put_nbr_base
*/

#include "../../include/my.h"

int my_put_nbr_base(unsigned int nbr, char const *base)
{
	int counter = 0;
	int converted_nbr[64];
	int i = 0;
	int base_nb = my_strlen(base);

	for (; nbr != 0 && i != base_nb; i++) {
		converted_nbr[i] = nbr % base_nb;
		nbr = nbr / base_nb;
	}
	--i;
	for (; i >= 0; i--) {
		my_putchar(base[converted_nbr[i]]);
		counter++;
	}
	return (counter);
}

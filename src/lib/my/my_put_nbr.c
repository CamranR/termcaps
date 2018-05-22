/*
** EPITECH PROJECT, 2017
** put_nbr.c
** File description:
** put_nbr
*/

#include "../../include/my.h"

int check_int(int nb, int counter)
{
	if (nb == -2147483648) {
		my_putchar('-');
		counter++;
		my_putchar('2');
		counter++;
		my_put_nbr(147483648);
	} else
		my_put_nbr(nb);
	return (counter);
}

int  my_put_nbr (int nbr)
{
	static int counter = 0;
	int start_value;
	int end_value;

	if (nbr == -2147483648)
		counter = check_int(nbr, counter);
	else if (nbr < 0) {
		my_putchar ('-');
		counter++;
		my_put_nbr (nbr * -1);
	} else {
		end_value = nbr % 10;
		start_value = nbr / 10;
		if (start_value != 0){
			my_put_nbr(start_value);
		}
		my_putchar(end_value + '0');
		counter++;
	}
	return (counter);
}

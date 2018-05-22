/*
** EPITECH PROJECT, 2017
** my_put_unsgined_nbr.c
** File description:
** my_put_usigned_nbr
*/

#include "../../include/my.h"

int  my_put_unsigned_nbr(unsigned int nbr)
{
	static int counter = 0;
	unsigned int start_value;
	unsigned int end_value;

	end_value = nbr % 10;
	start_value = nbr / 10;
	if (start_value != 0){
		my_put_unsigned_nbr(start_value);
	}
	my_putchar(end_value + '0');
	counter++;
	return (counter);
}
